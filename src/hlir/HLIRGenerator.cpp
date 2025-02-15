#include "../headers/HLIRGenerator.h"
#include "../headers/Analyser.h"
#include "../headers/Files.h"
#include "../headers/Hlir.h"
#include "../scope/ScopeManager.h"


namespace hlir
{
    bool hasVariableOrArg(const std::shared_ptr<Function> &F, const std::string &varName)
    {
        if (auto v = F->getStatement()->findVarByName(varName))
            return true;
        if (auto a = F->getFunctionArgs()->findArgByName(varName))
            return true;
        return false;
    }

    void ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var)
    {
        if (hasVariableOrArg(F, var->getVarName()))
            return;

        const auto parentF = F->getParentFunction();
        if (!parentF)
        {
            throw HLIRException(util::format("Variable {} not found", var->getVarName()));
        }

        ensureVariableCaptured(parentF, var);

        if (!hasVariableOrArg(F, var->getVarName()))
        {
            const auto functionArgs = F->getFunctionArgs();
            const auto newArg = std::make_shared<Arg>()->set(var->getVarName(), var->getVarType());
            functionArgs->addArg(newArg);
        }
    }

    std::pair<int, std::shared_ptr<Variable>> findVarByScope(std::shared_ptr<Function> currentFunction,
                                                             const std::string &varName)
    {
        int scopeNumber = 0;

        // Enquanto existirem escopos para subir
        while (currentFunction)
        {
            // 1. Tenta achar como variável local
            if (auto variable = currentFunction->getStatement()->findVarByName(varName))
            {
                // Se subimos algum nível, marque a variável como estando em outro escopo
                if (scopeNumber > 0)
                {
                    variable->changeToAnotherScope();
                }
                return {scopeNumber, variable};
            }

            // 2. Tenta achar como argumento
            if (const auto arg = currentFunction->getFunctionArgs()->findArgByName(varName))
            {
                // Cria um objeto Variable baseado no Arg encontrado
                auto variable = std::make_shared<Variable>()->set(arg->name, arg->type);

                // Se subimos algum nível, marque a variável como estando em outro escopo
                if (scopeNumber > 0)
                {
                    variable->changeToAnotherScope();
                }
                return {scopeNumber, variable};
            }

            // 3. Se não achou nem variável local, nem argumento,
            //    subimos para o próximo escopo (função pai)
            const auto parentFunction = currentFunction->getParentFunction();
            if (!parentFunction)
            {
                // Não há mais escopos para subir: variável não existe
                break;
            }

            scopeNumber++;
            currentFunction = parentFunction;
        }

        // 4. Se chegar aqui, não encontrou a variável em nenhum escopo
        throw HLIRException(util::format("Undefined variable: {} in expression", varName));
    }

    HLIRGenerator::HLIRGenerator(
            const std::shared_ptr<IronParser> &parser, const std::__1::shared_ptr<Context> &context,
            const std::shared_ptr<config::Configuration> &config,
            const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts) :
        parser(parser), context(context), config(config), exportContexts(exportContexts)
    {
        if (!parser)
        {
            throw HLIRException("The parser can't be nullptr");
        }

        if (!context)
        {
            throw HLIRException("The context can't be nullptr");
        }

        if (!config)
        {
            throw HLIRException("The config can't be nullptr");
        }

        if (!exportContexts)
        {
            throw HLIRException("The exportContexts can't be nullptr");
        }
    }

    HLIRGenerator::~HLIRGenerator() = default;

    void HLIRGenerator::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        const auto functionName = ctx->functionName->getText();
        // PUBLIC? FUNCTION functionName = IDENTIFIER functionSignature L_CURLY statementList R_CURLY;
        // std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType

        const auto functionArgs = std::make_shared<FunctionArgs>();
        const auto functionReturnType = std::make_shared<Type>();
        const auto statement = std::make_shared<Statement>();

        const auto function =
                std::make_shared<Function>()->set(functionName, functionArgs, functionReturnType, statement);
        context->addFunction(function);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
        }

        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList(), statement);
        }
    }

    void HLIRGenerator::visitStatementList(const IronParser::StatementListContext *ctx,
                                           const std::shared_ptr<Statement> &statement)
    {
        for (const auto child: ctx->children)
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration, statement);
            }
            // if (const auto assignment = dynamic_cast<IronParser::AssignmentContext *>(child))
            // {
            //     visitAssignment(assignment, statement);
            // }
            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression, statement);
            }
            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                auto call = visitFunctionCall(funcCall, statement);
                statement->addStatement(call);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx, statement);
            }

        }
    }

    void HLIRGenerator::visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                            const std::shared_ptr<Statement> &statement)
    {
        const std::string varName = ctx->varName->getText();

        if (const std::string varType = ctx->varTypes()->getText();
            tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        {
            const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("Error: std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            const auto alias = iron::createFunctionName(currentFunction->getFunctionName(), varName);

            if (auto aliasFunction = context->getFunctionByName(alias); !aliasFunction)
            {
                if (ctx->assignment())
                {
                    visitAssignment(ctx->assignment(), statement);
                }
            }
            else
            {
                auto funcPtr = std::make_shared<FunctionPtr>()->set(aliasFunction);
                const auto variable = std::make_shared<Variable>()->set(
                        varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                const auto value =
                        std::make_shared<Value>()->set(aliasFunction, std::make_shared<Type>(tokenMap::FUNCTION_PTR));
                auto assign = std::make_shared<Assign>()->set(variable, value);

                statement->addStatement(assign);
            }
        }
        else if (ctx->assignment())
        {

            visitAssignment(ctx->assignment(), statement);
        }
    }

    void HLIRGenerator::visitVarAssignment(IronParser::VarAssignmentContext *ctx, std::shared_ptr<Statement> statement)
    {
    }

    std::pair<std::string, int> HLIRGenerator::visitBoolExpr(IronParser::BoolExprContext *ctx)
    {

    }

    std::string HLIRGenerator::visitExpr(IronParser::ExprContext *ctx, const std::shared_ptr<Statement> &statement)
    {
        const int line = ctx->getStart()->getLine();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (auto child: ctx->children)
            {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
                {
                    return visitExpr(subExpr, statement);
                }
            }
        }

        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            std::string strLeftVar = visitExpr(ctx->left, statement);
            std::string strRightVar = visitExpr(ctx->right, statement);

            auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            auto [_, right] = findVarByScope(currentFunction, strRightVar);
            auto [__, left] = findVarByScope(currentFunction, strLeftVar);

            auto rightVar = right;
            auto leftVar = left;

            if (!rightVar)
            {
                throw hlir::HLIRException(util::format("Undefined right variable: {} in expression", strRightVar));
            }

            if (!leftVar)
            {
                throw hlir::HLIRException(util::format("Undefined left variable: {} in expression", strLeftVar));
            }

            if (rightVar->isAnotherScope())
            {
                ensureVariableCaptured(currentFunction, rightVar);
            }

            if (leftVar->isAnotherScope())
            {
                ensureVariableCaptured(currentFunction, leftVar);
            }

            int higherType = tokenMap::getHigherPrecedenceType(leftVar->getVarType()->getType(),
                                                               rightVar->getVarType()->getType());

            if (leftVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = statement->getNewVarName();

                auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(higherType));
                auto cast = std::make_shared<Cast>()->apply(leftVar, std::make_shared<Type>(higherType));
                auto expr = std::make_shared<Expr>()->set(tempVar, cast);

                statement->addStatement(expr);
                strLeftVar = tempVarStr;
            }

            if (rightVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = statement->getNewVarName();

                auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(higherType));
                auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(higherType));
                auto expr = std::make_shared<Expr>()->set(tempVar, cast);
                statement->addStatement(expr);

                strRightVar = tempVarStr;
            }

            std::string tempVarStr = statement->getNewVarName();

            auto newLeftVar = std::make_shared<Variable>()->set(strLeftVar, std::make_shared<Type>(higherType));
            auto newRightVar = std::make_shared<Variable>()->set(strRightVar, std::make_shared<Type>(higherType));
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(higherType));

            if (ctx->mult)
            {
                auto operation = std::make_shared<Mult>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->div)
            {
                auto operation = std::make_shared<Div>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->plus)
            {
                auto operation = std::make_shared<Plus>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->minus)
            {
                auto operation = std::make_shared<Minus>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            return tempVarStr;
        }

        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            return varName;
        }

        if (ctx->number())
        {
            std::string tempVarStr = statement->getNewVarName();
            std::string numberLiteral = ctx->number()->getText();
            int dataType = tokenMap::determineType(numberLiteral);

            if (dataType == tokenMap::REAL_NUMBER)
            {
                dataType = tokenMap::determineFloatType(numberLiteral);
            }

            auto type = std::make_shared<Type>(dataType);
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, type);
            auto value = std::make_shared<Value>()->set(numberLiteral, type);
            auto assign = std::make_shared<Assign>()->set(tempVar, value);

            statement->addStatement(assign);

            return tempVarStr;
        }

        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();

            auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            if (auto globalFunction = context->getFunctionByName(functionName))
            {
                std::string strTempVar = statement->getNewVarName();

                auto tempVar = std::make_shared<Variable>()->set(
                        strTempVar, std::make_shared<Type>(globalFunction->getFunctionReturnType()->getType()));

                auto functionCall = visitFunctionCall(ctx->functionCall(), statement);
                auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
                statement->addStatement(expr);

                return strTempVar;
            }
            else
            {
                const std::string localFunctionName =
                        iron::createFunctionName(currentFunction->getFunctionName(), functionName);

                auto localFunction = context->getFunctionByName(localFunctionName);

                if (!localFunction)
                {
                    throw HLIRException("hlir::visitExpr. function not found");
                }

                std::string strTempVar = statement->getNewVarName();

                auto tempVar = std::make_shared<Variable>()->set(
                        strTempVar, std::make_shared<Type>(localFunction->getFunctionReturnType()->getType()));

                auto functionCall = visitFunctionCall(ctx->functionCall(), statement);
                auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
                statement->addStatement(expr);

                return strTempVar;
            }
        }

        throw hlir::HLIRException(util::format("Invalid expression. Line: {}", line));
    }

    void HLIRGenerator::visitAssignment(IronParser::AssignmentContext *ctx, std::shared_ptr<Statement> statement)
    {

        auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());

        if (!currentFunction)
        {
            throw HLIRException("HLIRGenerator::visitAssignment. The current function not found.");
        }

        if (ctx->dataFormat())
        {
            // Caso 1: a atribuição está sendo feita a um argumento de função
            if (auto *functionArg = dynamic_cast<IronParser::FunctionArgContext *>(ctx->parent))
            {
                std::string argName = functionArg->varName->getText();
                std::string argType = functionArg->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();

                //*sb << util::format("{}:{} = {}", argName, argType, literalValue);
            }



            // Caso 2: a atribuição está sendo feita a uma variável declarada
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();

                // int literalType = tokenMap::determineType(literalValue);

                // if (literalType == tokenMap::REAL_NUMBER) {
                //     tokenMap::determineFloatType(literalValue);
                // }

                auto variable = std::make_shared<Variable>()->set(
                        varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                auto value = std::make_shared<Value>()->set(literalValue,
                                                            std::make_shared<Type>(tokenMap::getTokenType(varType)));
                auto assign = std::make_shared<Assign>()->set(variable, value);

                statement->addStatement(assign);
            }
        }

        if (ctx->varName)
        {




            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {

                const auto anotherVar = ctx->varName->getText();
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();

                auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
                if (!currentFunction)
                {
                    throw HLIRException("HLIRGenerator::visitAssignment. The current function not found.");
                }

                const auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                const auto [__, anotherVariable] = findVarByScope(currentFunction, anotherVar);
                auto value = std::make_shared<Value>()->set(anotherVariable, anotherVariable->getVarType());
                auto assign = std::make_shared<Assign>()->set(variable, value);
                statement->addStatement(assign);
            }
        }

        if (ctx->expr())
        {

            const auto strRightVarName = visitExpr(ctx->expr(), statement);
            auto variable = findVarByScope(currentFunction, strRightVarName);
            auto rightVar = variable.second;

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string strLeftVarName = varDecl->varName->getText();
                std::string strLeftvarTypeName = varDecl->varTypes()->getText();

                int leftDataTypeType = tokenMap::getTokenType(strLeftvarTypeName);
                auto leftVar =
                        std::make_shared<Variable>()->set(strLeftVarName, std::make_shared<Type>(leftDataTypeType));

                if (rightVar->isAnotherScope())
                {
                    auto functionArgs = currentFunction->getFunctionArgs();
                    auto arg = std::make_shared<Arg>()->set(rightVar->getVarName(), rightVar->getVarType());
                    functionArgs->addArg(arg);
                }

                if (leftVar->isAnotherScope())
                {
                    auto functionArgs = currentFunction->getFunctionArgs();
                    auto arg = std::make_shared<Arg>()->set(leftVar->getVarName(), leftVar->getVarType());
                    functionArgs->addArg(arg);
                }

                if (leftDataTypeType != rightVar->getVarType()->getType())
                {
                    std::string strTempVar = statement->getNewVarName();

                    auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(leftDataTypeType));
                    auto tempVariable =
                            std::make_shared<Variable>()->set(strTempVar, std::make_shared<Type>(leftDataTypeType));

                    auto expr = std::make_shared<Expr>()->set(tempVariable, cast);
                    statement->addStatement(expr);

                    auto value = std::make_shared<Value>()->set(tempVariable, tempVariable->getVarType());
                    auto assign = std::make_shared<Assign>()->set(leftVar, value);
                    statement->addStatement(assign);
                }
                else
                {
                    auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                    auto assign = std::make_shared<Assign>()->set(leftVar, value);
                    statement->addStatement(assign);
                }
            }
        }

        if (ctx->arrowFunctionBlock())
        {
            visitArrowFunctionBlock(ctx->arrowFunctionBlock(), statement);
        }
        else if (ctx->arrowFunctionInline())
        {
            visitArrowFunctionInline(ctx->arrowFunctionInline(), statement);
        }
    }

    void HLIRGenerator::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx,
                                               std::shared_ptr<FunctionArgs> functionArgs,
                                               std::shared_ptr<Type> functionReturnType)
    {
        if (ctx->functionArgs())
        {
            visitFunctionArgs(ctx->functionArgs(), functionArgs);
        }

        if (ctx->functionReturnType())
        {
            // ctx->functionReturnType()->varTypes()->getText();
            functionReturnType->set(tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText()));
        }
        else
        {
            functionReturnType->set(tokenMap::VOID);
        }
    }

    void HLIRGenerator::visitFunctionArgs(IronParser::FunctionArgsContext *ctx,
                                          std::shared_ptr<FunctionArgs> functionArgs)
    {
        for (auto child: ctx->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(funcDecl, functionArgs);
            }
        }
    }

    void HLIRGenerator::visitFunctionArg(IronParser::FunctionArgContext *ctx,
                                         std::shared_ptr<FunctionArgs> functionArgs)
    {
        auto argName = ctx->varName->getText();
        auto type = std::make_shared<Type>();
        type->set(tokenMap::getTokenType(ctx->varTypes()->getText()));
        functionArgs->addArg(std::make_shared<Arg>()->set(argName, type));
    }

    std::shared_ptr<FunctionCall> HLIRGenerator::visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                                                   std::shared_ptr<Statement> statement)
    {
        auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
        if (!currentFunction)
        {
            throw HLIRException("HLIRGenerator::visitFunctionCall. currentFunction is null");
        }

        const auto functionName = ctx->functionName->getText();

        if (const auto globalFunction = context->getFunctionByName(functionName))
        {
            const auto callArgs = std::make_shared<FunctionCallArgs>();
            auto call = std::make_shared<FunctionCall>()->set(globalFunction, callArgs);

            if (ctx->functionCallArgs())
            {
                visitFunctionCallArgs(ctx->functionCallArgs(), callArgs, statement);
            }

            return call;
        }
        else
        {
            const std::string inlineFunctionName =
                    iron::createFunctionName(currentFunction->getFunctionName(), functionName);
            auto inlineFunction = context->getFunctionByName(inlineFunctionName);

            if (!inlineFunction)
            {
                throw hlir::HLIRException(util::format("HLIR Error: Function fn {} not found", functionName));
            }

            // util::printf("{}", inlineFunction->getFunctionArgs()->getText());

            auto callArgs = std::make_shared<FunctionCallArgs>();
            auto call = std::make_shared<FunctionCall>()->set(inlineFunction, callArgs);

            if (ctx->functionCallArgs())
            {
                // for (auto funcArg : inlineFunction->getFunctionArgs()->getArgs())
                // {
                //     callArgs->addCallArg(std::make_shared<FunctionCallArg>()->set(funcArg->name, funcArg->type));
                // }

                visitFunctionCallArgs(ctx->functionCallArgs(), callArgs, statement);
            }

            const auto funcArgSize = inlineFunction->getFunctionArgs()->getArgs().size();

            if (const auto callArgSize = callArgs->getCallArgs().size(); funcArgSize > callArgSize)
            {
                // auto diff = funcArgSize - callArgSize;
                for (size_t i = callArgSize; i < funcArgSize; i++)
                {
                    const auto arg = inlineFunction->getFunctionArgs()->getArgs()[i];
                    auto [fst, snd] = findVarByScope(inlineFunction, arg->name);
                    auto variable = snd;

                    if (!variable)
                    {
                        throw HLIRException("HLIRGenerator::visitFunctionCall. Variable not found");
                    }

                    auto value = std::make_shared<Value>()->set(variable, variable->getVarType());
                    auto callArg = std::make_shared<FunctionCallArg>(arg->name, variable->getVarType(), value);
                    callArgs->addCallArg(callArg);
                }
            }

            return call;
        }
    }

    void HLIRGenerator::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx,
                                              const std::shared_ptr<FunctionCallArgs> &callArgs,
                                              const std::shared_ptr<Statement> &statement)
    {
        for (const auto child: ctx->children)
        {
            if (auto *arg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                visitFunctionCallArg(arg, callArgs, statement);
            }
        }
    }

    void HLIRGenerator::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                             const std::shared_ptr<FunctionCallArgs> &callArgs,
                                             const std::shared_ptr<Statement> &statement)
    {
        auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
        auto argName = ctx->varName->getText();
        auto callFunction = std::dynamic_pointer_cast<FunctionCall>(callArgs->getParent());
        if (!callFunction)
        {
            throw HLIRException("HLIRGenerator::visitFunctionCallArg. The callFunction not found");
        }

        // printf("callFunction %s\n", callFunction->getFunction()->getFunctionName().c_str());

        if (ctx->dataFormat())
        {
            std::string strValue = ctx->dataFormat()->getText();

            int realType;
            if (auto definedType = tokenMap::determineType(strValue); definedType == tokenMap::REAL_NUMBER)
            {
                realType = tokenMap::determineFloatType(strValue);
            }
            else
            {
                realType = definedType;
            }

            auto strAnotherVar = statement->getNewVarName();
            auto type = std::make_shared<Type>(realType);

            auto anotherVar = std::make_shared<Variable>()->set(strAnotherVar, type);
            auto value = std::make_shared<Value>()->set(strValue, std::make_shared<Type>(realType));
            auto assign = std::make_shared<Assign>()->set(anotherVar, value);

            auto variableValue = std::make_shared<Value>()->set(anotherVar, std::make_shared<Type>(realType));
            // auto value = std::make_shared<Value>()->set(anotherVar, type);
            callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, type, variableValue));

            // auto expr = std::make_shared<Expr>()->set(anotherVar, assign);
            statement->addStatement(assign);

            // callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, std::make_shared<Type>(realType),
            // value));
        }

        if (ctx->anotherVarName)
        {
            // util::printf("ctx->anotherVarName {}", ctx->anotherVarName->getText());

            if (dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent->parent))
            {
                // std::string anotherVar = ctx->anotherVarName->getText();
                std::string inlineFunctionName = callFunction->getFunction()->getFunctionName();

                // util::printf("inlineFunctionName {}", inlineFunctionName);

                auto function = context->getFunctionByName(inlineFunctionName);
                if (!function)
                {
                    throw HLIRException("HLIRGenerator::visitFunctionCallArg. Function not found");
                }

                if (auto arg = function->getFunctionArgs()->findArgByName(argName); !arg)
                {
                    if (!callFunction->getFunction()->isExternal() && !callFunction->getFunction()->isVariedArguments())
                    {
                        throw HLIRException("HLIRGenerator::visitFunctionCallArg. Arg not found");
                    }
                }


                auto anotherVar = statement->findVarByName(ctx->anotherVarName->getText());
                if (!anotherVar)
                {
                    auto [_, variable] = findVarByScope(currentFunction, ctx->anotherVarName->getText());

                    if (!variable)
                    {
                        throw HLIRException("HLIRGenerator::visitFunctionCallArg. Variable not found");
                    }

                    ensureVariableCaptured(currentFunction, variable);

                    anotherVar = variable;
                }

                auto type = anotherVar->getVarType();
                auto value = std::make_shared<Value>()->set(anotherVar, type);
                callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, type, value));

                // if (callFunction->getFunction()->isExternal() && callFunction->getFunction()->isVariedArguments())
                // {
                //     auto type = anotherVar->getVarType();
                //     auto value = std::make_shared<Value>()->set(anotherVar, type);
                //     callArgs->addCallArg(std::make_shared<FunctionCallArg>(
                //             argName, type, value));
                // } else
                // {
                //     auto value = std::make_shared<Value>()->set(anotherVar,
                //     std::make_shared<Type>(arg->type->getType()));
                //     callArgs->addCallArg(std::make_shared<FunctionCallArg>(
                //             argName, std::make_shared<Type>(arg->type->getType()), value));
                // }
            }
        }

        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();
            auto calledFunction = context->getFunctionByName(functionName);

            // util::printf("functionName {}", callFunction->getFunction()->getFunctionName());

            if (!calledFunction)
            {
                auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
                auto inlineFunctionName = iron::createFunctionName(currentFunction->getFunctionName(), functionName);

                calledFunction = context->getFunctionByName(inlineFunctionName);

                if (!calledFunction)
                {
                    throw HLIRException("HLIRGenerator::visitFunctionCallArg. Function not found");
                }
            }

            auto localCallFunction = visitFunctionCall(ctx->functionCall(), statement);

            auto strAnotherVar = statement->getNewVarName();
            auto anotherVar = std::make_shared<Variable>()->set(strAnotherVar, calledFunction->getFunctionReturnType());
            auto expr = std::make_shared<Expr>()->set(anotherVar, localCallFunction);
            statement->addStatement(expr);

            auto arg = callFunction->getFunction()->getFunctionArgs()->findArgByName(argName);
            if (!arg)
            {
                if (!callFunction->getFunction()->isExternal() && !callFunction->getFunction()->isVariedArguments())
                {
                    throw HLIRException("HLIRGenerator::visitFunctionCallArg. Arg not found");
                }
            }

            callFunction->getFunction()->isVariedArguments();

            if (callFunction->getFunction()->isExternal() && callFunction->getFunction()->isVariedArguments())
            {
                const auto type = anotherVar->getVarType();
                auto value = std::make_shared<Value>()->set(anotherVar, std::make_shared<Type>(type->getType()));
                callArgs->addCallArg(
                        std::make_shared<FunctionCallArg>(argName, std::make_shared<Type>(type->getType()), value));
            }
            else
            {
                auto value = std::make_shared<Value>()->set(anotherVar, std::make_shared<Type>(arg->type->getType()));
                callArgs->addCallArg(std::make_shared<FunctionCallArg>(
                        argName, std::make_shared<Type>(arg->type->getType()), value));
            }
        }
    }

    void HLIRGenerator::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx,
                                                 const std::shared_ptr<Statement> &statement)
    {
        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            // Nome "original" da arrow function
            const std::string arrowFuncName = varDeclaration->varName->getText();

            const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            // Cria um nome único para a função no escopo global
            std::string inlineFunctionName =
                    iron::createFunctionName(currentFunction->getFunctionName(), arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType())
            {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            }
            else
            {
                returnTypeStr = tokenMap::getTokenText(tokenMap::VOID);
            }

            const auto functionArgs = std::make_shared<FunctionArgs>();
            const auto functionReturnType = std::make_shared<Type>(tokenMap::getTokenType(returnTypeStr));
            auto statement = std::make_shared<Statement>();

            auto inlineFunction =
                    std::make_shared<Function>()->set(inlineFunctionName, functionArgs, functionReturnType, statement);
            inlineFunction->enableInline();
            context->addFunction(inlineFunction);

            if (ctx->functionSignature()->functionArgs())
            {
                visitFunctionArgs(ctx->functionSignature()->functionArgs(), functionArgs);
            }

            if (ctx->expr())
            {
                const auto varName = visitExpr(ctx->expr(), statement);
                auto [_, variable] = findVarByScope(inlineFunction, varName);

                if (functionReturnType->getType() != tokenMap::VOID)
                {
                    auto funcReturn = std::make_shared<FuncReturn>(inlineFunction, variable);
                    inlineFunction->getStatement()->addStatement(funcReturn);
                }
            }
        }
    }

    void HLIRGenerator::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx,
                                                const std::shared_ptr<Statement> &statement)
    {
        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (const auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            // Nome "original" da arrow function
            const std::string arrowFuncName = varDeclaration->varName->getText();

            const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            // Cria um nome único para a função no escopo global
            const std::string inlineFunctionName =
                    iron::createFunctionName(currentFunction->getFunctionName(), arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType())
            {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            }
            else
            {
                returnTypeStr = tokenMap::getTokenText(tokenMap::VOID);
            }

            const auto functionArgs = std::make_shared<FunctionArgs>();
            const auto functionReturnType = std::make_shared<Type>(tokenMap::getTokenType(returnTypeStr));
            const auto statement = std::make_shared<Statement>();

            const auto inlineFunction =
                    std::make_shared<Function>()->set(inlineFunctionName, functionArgs, functionReturnType, statement);
            inlineFunction->enableInline();
            context->addFunction(inlineFunction);

            if (ctx->functionSignature()->functionArgs())
            {
                visitFunctionArgs(ctx->functionSignature()->functionArgs(), functionArgs);
            }

            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList(), statement);
            }
        }
    }

    void HLIRGenerator::visitReturn(IronParser::ReturnStatementContext *ctx,
                                    const std::shared_ptr<Statement> &statement)
    {
        const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
        if (!currentFunction)
        {
            throw HLIRException("Error: std::dynamic_pointer_cast<Function>(statement->getParent())");
        }

        if (ctx->dataFormat())
        {
            const auto strValue = ctx->dataFormat()->getText();
            auto valueType = tokenMap::determineType(strValue);
            if (valueType == tokenMap::REAL_NUMBER)
            {
                valueType = tokenMap::determineFloatType(strValue);
            }

            const auto varName = currentFunction->getStatement()->getNewVarName();
            const auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(valueType));

            const auto value = std::make_shared<Value>()->set(strValue, variable->getVarType());
            const auto assign = std::make_shared<Assign>()->set(variable, value);
            currentFunction->getStatement()->addStatement(assign);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }

        if (ctx->varName)
        {
            auto [_, variable] = findVarByScope(currentFunction, ctx->varName->getText());
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }

        if (ctx->expr())
        {
            const auto varName = visitExpr(ctx->expr(), statement);
            auto [_, variable] = findVarByScope(currentFunction, varName);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }

        if (ctx->functionCall())
        {
            const auto varName = currentFunction->getStatement()->getNewVarName();

            const auto funcCall = visitFunctionCall(ctx->functionCall(), statement);
            const auto funcReturnType = funcCall->getFunction()->getFunctionReturnType();
            const auto variable = std::make_shared<Variable>()->set(varName, funcReturnType);
            const auto expr = std::make_shared<Expr>()->set(variable, funcCall);
            currentFunction->getStatement()->addStatement(expr);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }
    }

    std::shared_ptr<Context> HLIRGenerator::getContext()
    {
        IronParser::ProgramContext *programContext = parser->program();

        for (const auto importStmt: programContext->importStatement())
        {
            visitImportStatement(importStmt);
        }

        if (programContext->externBlock())
        {
            visitExternBlock(programContext->externBlock());
        }

        for (const auto child: programContext->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        return context;
    }

    void HLIRGenerator::visitImportStatement(IronParser::ImportStatementContext *ctx)
    {
        if (ctx->qualifiedName())
        {
            const std::string import = ctx->qualifiedName()->getText();
            const auto [path, element] = iron::convertImportPath(import);
            const std::string fullPath = util::format("{}{}", config->stdFolder(), path);

            if (const auto it = exportContexts->find(fullPath); it != exportContexts->end())
            {
                if (auto foundContext = it->second)
                {
                    auto externalFunction = foundContext->getFunctionByName(element);
                    registerExternalFunction(externalFunction);
                }
            }
            else
            {
                const iron::Analyser analyser(config);
                const auto parentContext = analyser.hlir(fullPath, exportContexts);
                exportContexts->emplace(fullPath, parentContext);

                const auto hlirPath = util::format("{}{}", config->outputHLIR(), path);
                const auto pathAndFile = iron::saveToFile(parentContext->getText(), hlirPath, "hlir");

                // hilirFiles->push_back(pathAndFile);

                for (const auto &externalFunction: parentContext->getFunctions())
                {

                    if (externalFunction->getFunctionName() != element)
                    {
                        continue;
                    }
                    registerExternalFunction(externalFunction);
                }
            }
        }
    }

    void HLIRGenerator::registerExternalFunction(const std::shared_ptr<Function>& function) const
    {
        if (function) {

            const auto externalFunction = function->clone();
            externalFunction->changeToExternal();
            if (function->isVariedArguments())
            {
                externalFunction->changeToVariedArguments();
            }

            externalFunction->setLanguageType(function->getLanguageType());

            context->addExternalFunction(externalFunction);
        }
    }

    void HLIRGenerator::visitExternBlock(IronParser::ExternBlockContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::ExternFunctionDeclarationContext *>(child))
            {
                visitExternFunctionDeclaration(funcDecl);
            }
        }
    }

    void HLIRGenerator::visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx)
    {
        const std::string functionName = ctx->exterFunctionName->getText();

        const auto functionArgs = std::make_shared<FunctionArgs>();
        const auto functionReturnType = std::make_shared<Type>();
        const auto statement = std::make_shared<Statement>();

        const auto function =
                std::make_shared<Function>()->set(functionName, functionArgs, functionReturnType, statement);
        function->setLanguageType(tokenMap::C_LANG);
        function->changeToExternal();
        if (ctx->varied)
        {
            function->changeToVariedArguments();
        }

        context->addFunction(function);

        functionReturnType->set(tokenMap::VOID);
        if (ctx->functionReturnType())
        {
            functionReturnType->set(tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText()));
        }

        if (ctx->externFunctionArgs())
        {
            visitExternFunctionArgs(ctx->externFunctionArgs(), functionArgs);
        }
    }

    void HLIRGenerator::visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                                const std::shared_ptr<FunctionArgs> &argsList)
    {
        for (const auto arg: ctx->externFunctionArg())
        {
            visitExternFunctionArg(arg, argsList);
        }
    }

    void HLIRGenerator::visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                               const std::shared_ptr<FunctionArgs> &argsList)
    {
        const auto argName = ctx->varName->getText();
        const auto type = std::make_shared<Type>();


        if (ctx->ptr)
        {
            const auto ptrType = tokenMap::getTokenType(ctx->cTypes()->getText());
            // if (ptrType == tokenMap::TYPE_CHAR; ptrType = tokenMap::PTR_TYPE_CHAR)
            // {
            // }
            type->set(ptrType);
        }
        else
        {
            type->set(tokenMap::getTokenType(ctx->cTypes()->getText()));
        }

        argsList->addArg(std::make_shared<Arg>()->set(argName, type));
    }


} // namespace hlir

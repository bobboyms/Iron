#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"


namespace hlir
{
    void HLIRGenerator::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        const auto functionName = ctx->functionName->getText();

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

    void HLIRGenerator::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx,
                                               const std::shared_ptr<FunctionArgs> &functionArgs,
                                               const std::shared_ptr<Type> &functionReturnType)
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

    void HLIRGenerator::visitFunctionArgs(const IronParser::FunctionArgsContext *ctx,
                                          const std::shared_ptr<FunctionArgs> &functionArgs)
    {
        for (const auto child: ctx->children)
        {
            if (const auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(functionArg, functionArgs);
            }
        }
    }

    void HLIRGenerator::visitFunctionArg(IronParser::FunctionArgContext *ctx,
                                         const std::shared_ptr<FunctionArgs> &functionArgs)
    {
        const auto argName = ctx->varName->getText();
        const auto type = std::make_shared<Type>();
        type->set(tokenMap::getTokenType(ctx->varTypes()->getText()));
        functionArgs->addArg(std::make_shared<Arg>()->set(argName, type));
    }

    std::shared_ptr<FunctionCall> HLIRGenerator::visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                                                   const std::shared_ptr<Statement> &statement)
    {
        if (const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent()); !currentFunction)
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

        const auto arrowFunction = gatArrowFunction(statement, functionName);

        const auto callArgs = std::make_shared<FunctionCallArgs>();
        auto call = std::make_shared<FunctionCall>()->set(arrowFunction, callArgs);

        if (ctx->functionCallArgs())
        {
            visitFunctionCallArgs(ctx->functionCallArgs(), callArgs, statement);
        }

        const auto funcArgSize = arrowFunction->getFunctionArgs()->getArgs().size();

        if (const auto callArgSize = callArgs->getCallArgs().size(); funcArgSize > callArgSize)
        {
            // auto diff = funcArgSize - callArgSize;
            for (size_t i = callArgSize; i < funcArgSize; i++)
            {
                const auto arg = arrowFunction->getFunctionArgs()->getArgs()[i];
                auto [_, variable] = findVarByScope(statement, arg->name);
                // auto variable = snd;

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

    void HLIRGenerator::visitFunctionCallArgs(const IronParser::FunctionCallArgsContext *ctx,
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
        const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
        if (!currentFunction)
        {
            throw HLIRException("HLIRGenerator::visitFunctionCallArg. The currentFunction not found");
        }

        auto argName = ctx->varName->getText();
        auto callFunction = std::dynamic_pointer_cast<FunctionCall>(callArgs->getParent());
        if (!callFunction)
        {
            throw HLIRException("HLIRGenerator::visitFunctionCallArg. The callFunction not found");
        }

        if (ctx->dataFormat())
        {
            const auto strValue = ctx->dataFormat()->getText();

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
            // statement->setParent(anotherVar);
            statement->addDeclaredVariable(anotherVar);
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

            if (dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent->parent))
            {
                const auto inlineFunctionName = callFunction->getFunction()->getFunctionName();
                const auto function = context->getFunctionByName(inlineFunctionName);
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
                    auto [_, variable] = findVarByScope(statement, ctx->anotherVarName->getText());

                    if (!variable)
                    {
                        throw HLIRException("HLIRGenerator::visitFunctionCallArg. Variable not found");
                    }

                    anotherVar = variable;
                }

                auto type = anotherVar->getVarType();
                auto value = std::make_shared<Value>()->set(anotherVar, type);
                callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, type, value));
            }
        }

        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();
            auto calledFunction = context->getFunctionByName(functionName);

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
            statement->addDeclaredVariable(anotherVar);
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
        if (const auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            const auto arrowFuncName = varDeclaration->varName->getText();
            const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
            const auto variable = std::make_shared<Variable>()->set(arrowFuncName, type);
            statement->addDeclaredVariable(variable);

            const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            // Cria um nome único para a função no escopo global
            const auto inlineFunctionName = iron::createFunctionName(currentFunction->getFunctionName(), arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType())
            {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            }
            else
            {
                returnTypeStr = getTokenText(tokenMap::VOID);
            }

            const auto functionArgs = std::make_shared<FunctionArgs>();
            const auto functionReturnType = std::make_shared<Type>(tokenMap::getTokenType(returnTypeStr));
            const auto inlineStatement = std::make_shared<Statement>();

            const auto arrowFunction = std::make_shared<Function>()->set(inlineFunctionName, functionArgs, functionReturnType,
                                                                   inlineStatement);

            const auto value = std::make_shared<Value>()->set(arrowFunction, type);
            const auto assign = std::make_shared<Assign>()->set(variable, value);
            statement->addStatement(assign);

            arrowFunction->enableInline();
            context->addFunction(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature(),functionArgs, functionReturnType);
            }

            // if (ctx->functionSignature())
            // {
            //     visitFunctionArgs(ctx->functionSignature()->functionArgs(), functionArgs);
            // }

            if (ctx->expr())
            {
                // const auto varName = visitExpr(ctx->expr(), statement);
                // auto [_, variable] = findVarByScope(inlineFunction, varName);

                const auto varName = visitExpr(ctx->expr(), inlineStatement);
                const auto [_, variable] = findVarByScope(inlineStatement, varName);

                if (functionReturnType->getType() != tokenMap::VOID)
                {
                    auto funcReturn = std::make_shared<FuncReturn>(arrowFunction, variable);
                    arrowFunction->getStatement()->addStatement(funcReturn);
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
            const auto arrowFuncName = varDeclaration->varName->getText();
            const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
            const auto variable = std::make_shared<Variable>()->set(arrowFuncName, type);
            statement->addDeclaredVariable(variable);

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
                returnTypeStr = getTokenText(tokenMap::VOID);
            }

            const auto functionArgs = std::make_shared<FunctionArgs>();
            const auto functionReturnType = std::make_shared<Type>(tokenMap::getTokenType(returnTypeStr));
            const auto inlineStatement = std::make_shared<Statement>();


            auto arrowFunction = std::make_shared<Function>()->set(inlineFunctionName, functionArgs, functionReturnType,
                                                                   inlineStatement);
            const auto value = std::make_shared<Value>()->set(arrowFunction, type);
            const auto assign = std::make_shared<Assign>()->set(variable, value);
            statement->addStatement(assign);

            // Configure o parent do inlineStatement para ser a própria função block
            // inlineStatement->setParent(arrowFunction);
            //
            // // Registre esse Statement na função block:
            // arrowFunction->setStatement(inlineStatement);

            arrowFunction->enableInline();
            context->addFunction(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
            }

            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList(), inlineStatement);
            }
        }
    }

    void HLIRGenerator::visitReturn(IronParser::ReturnStatementContext *ctx,
                                    const std::shared_ptr<Statement> &statement)
    {
        auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
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

            auto varName = currentFunction->getStatement()->getNewVarName();
            auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(valueType));
            statement->addDeclaredVariable(variable);

            const auto value = std::make_shared<Value>()->set(strValue, variable->getVarType());
            const auto assign = std::make_shared<Assign>()->set(variable, value);
            currentFunction->getStatement()->addStatement(assign);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }

        if (ctx->varName)
        {
            auto [_, variable] = findVarByScope(statement, ctx->varName->getText());
            if (variable->isAnotherScope())
            {
                ensureVariableCaptured(currentFunction,variable);
            }

            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }


        if (ctx->expr())
        {
            const auto varName = visitExpr(ctx->expr(), currentFunction->getStatement());
            auto [_, variable] = findVarByScope(statement, varName);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }

        if (ctx->functionCall())
        {
            const auto varName = currentFunction->getStatement()->getNewVarName();


            const auto funcCall = visitFunctionCall(ctx->functionCall(), statement);


            const auto funcReturnType = funcCall->getFunction()->getFunctionReturnType();
            const auto variable = std::make_shared<Variable>()->set(varName, funcReturnType);
            statement->addDeclaredVariable(variable);
            const auto expr = std::make_shared<Expr>()->set(variable, funcCall);
            currentFunction->getStatement()->addStatement(expr);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            currentFunction->getStatement()->addStatement(funcReturn);
        }
    }
} // namespace hlir

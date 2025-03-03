#include "../../headers/HLIRGenerator.h"
#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/Hlir.h"

namespace hlir
{

    void createMathExprAssign(const std::string &leftVarName, const std::string &leftVarTypeName,
                              const std::shared_ptr<Variable> &rightVar,
                              const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        int leftDataTypeType = tokenMap::getTokenType(leftVarTypeName);
        const auto leftVar = currentFunction->findVarAllScopesAndArg(leftVarName);

        if (leftDataTypeType != rightVar->getVarType()->getType())
        {
            const std::string strTempVar = currentFunction->generateVarName();

            const auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(leftDataTypeType));
            auto tempVariable = std::make_shared<Variable>()->set(strTempVar, std::make_shared<Type>(leftDataTypeType));
            statement->addDeclaredVariable(tempVariable);


            auto expr = std::make_shared<Expr>()->set(tempVariable, cast);
            statement->addStatement(expr);

            const auto value = std::make_shared<Value>()->set(tempVariable, tempVariable->getVarType());
            auto assign = std::make_shared<Assign>()->set(leftVar, value);
            statement->addStatement(assign);
        }
        else
        {
            const auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
            auto assign = std::make_shared<Assign>()->set(leftVar, value);
            statement->addStatement(assign);
        }
    }

    // Construtor: inicializa os membros conforme declarado no cabeçalho.
    HLIRGenerator::HLIRGenerator(
            const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context,
            const std::shared_ptr<config::Configuration> &config,
            const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts) :
        parser(parser), context(context), config(config), exportContexts(exportContexts)
    {
        // Qualquer inicialização adicional necessária pode ser feita aqui.
    }

    // Destrutor: pode ser padrão se não houver liberação manual de recursos.
    HLIRGenerator::~HLIRGenerator() = default;

    // Método getContext(): retorna o contexto armazenado.
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

    std::pair<bool, bool> HLIRGenerator::visitStatementList(const IronParser::StatementListContext *ctx,
                                                            const std::shared_ptr<Function> &currentFunction,
                                                            const std::shared_ptr<Jump> &endJump)
    {
        bool hasBreak{false};
        bool hasReturn{false};
        const auto statement = currentFunction->getCurrentLocalScope();
        for (const auto child: ctx->children)
        {

            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration, currentFunction);
            }

            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression, currentFunction);
            }

            if (const auto expression = dynamic_cast<IronParser::BoolExprContext *>(child))
            {
                visitBoolExpr(expression, currentFunction);
            }

            if (const auto IfStatement = dynamic_cast<IronParser::IfStatementContext *>(child))
            {
                const auto endLabel = currentFunction->generateLabel("end");
                visitIfStatement(IfStatement, currentFunction, endLabel, endJump);
            }

            if (const auto whileLoop = dynamic_cast<IronParser::WhileStatementContext *>(child))
            {
                visitWhileStatement(whileLoop, currentFunction);
            }
            if (const auto forLoop = dynamic_cast<IronParser::ForStatementContext *>(child))
            {
                visitForStatement(forLoop, currentFunction);
            }
            if (const auto repeatLoop = dynamic_cast<IronParser::RepeatStatementContext *>(child))
            {
                visitRepeatStatement(repeatLoop, currentFunction);
            }

            if (const auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment, currentFunction);
            }

            if (dynamic_cast<IronParser::BreakStatementContext *>(child))
            {
                if (endJump)
                {
                    statement->addStatement(endJump);
                }

                hasBreak = true;
            }

            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                auto call = visitFunctionCall(funcCall, currentFunction);
                statement->addStatement(call);
            }

            if (const auto re_turn = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(re_turn, currentFunction);
                hasReturn = true;
            }
        }

        return std::make_pair(hasBreak, hasReturn);
    }

    void HLIRGenerator::visitVarAssignment(IronParser::VarAssignmentContext *ctx,
                                           const std::shared_ptr<Function> &currentFunction)
    {

        const auto leftVarName = ctx->varName->getText();
        const auto leftVariable = currentFunction->findVarAllScopesAndArg(leftVarName);
        if (!leftVariable)
        {
            throw std::runtime_error("leftVariable name not found");
        }

        if (ctx->expr())
        {
            const auto rightVarName = visitExpr(ctx->expr(), currentFunction);
            const auto rightVar = currentFunction->findVarAllScopesAndArg(rightVarName);
            if (!rightVar)
            {
                throw std::runtime_error("VrightVar not found");
            }

            createMathExprAssign(leftVarName, tokenMap::getTokenText(leftVariable->getVarType()->getType()), rightVar,
                                 currentFunction);
        }
    }

    void HLIRGenerator::visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                            const std::shared_ptr<Function> &currentFunction)
    {
        const std::string varName = ctx->varName->getText();
        const std::string varType = ctx->varTypes()->getText();
        const auto statement = currentFunction->getCurrentLocalScope();

        const auto variable =
                std::make_shared<Variable>()->set(varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
        statement->addDeclaredVariable(variable);
        variable->changeRealName(currentFunction->generateVarName());

        // statement->addStatement(std::make_shared<DeclareVariable>(variable));

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment(), currentFunction);
        }
    }

    void HLIRGenerator::visitAssignment(IronParser::AssignmentContext *ctx,
                                        const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        if (ctx->dataFormat())
        {
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();

                // std::make_shared<Variable>()->set(
                //         varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                const auto variable = statement->findVarByName(varName);
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
                const auto anotherVarName = ctx->varName->getText();
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();

                const auto variable = statement->findVarByName(varName);
                if (!variable)
                {
                    throw HLIRException("HLIRGenerator::visitAssignment. Variable not found");
                }

                const auto isVariableFunction = variable->getVarType()->getType() == tokenMap::FUNCTION;
                const auto anotherVariable = currentFunction->findVarAllScopesAndArg(anotherVarName);
                if (!anotherVariable && !isVariableFunction)
                {
                    throw HLIRException("HLIRGenerator::visitAssignment. Variable not found");
                }

                if (anotherVariable)
                {
                    if (anotherVariable->isAnotherScope())
                    {
                        ensureVariableCaptured(currentFunction, anotherVariable);
                    }
                }

                if (isVariableFunction)
                {

                    std::shared_ptr<Function> localFunction;
                    if (!anotherVariable)
                    {
                        localFunction = context->getFunctionByName(anotherVarName);
                    }
                    else
                    {
                        localFunction = getFunctionValue(currentFunction, anotherVariable->getVarName());
                    }

                    if (!localFunction)
                    {
                        throw HLIRException("HLIRGenerator::visitAssignment. Function not found");
                    }

                    const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
                    auto value = std::make_shared<Value>()->set(localFunction, type);
                    auto assign = std::make_shared<Assign>()->set(variable, value);
                    statement->addStatement(assign);
                }
                else
                {
                    auto value = std::make_shared<Value>()->set(anotherVariable, anotherVariable->getVarType());
                    auto assign = std::make_shared<Assign>()->set(variable, value);
                    statement->addStatement(assign);
                }
            }
        }

        if (ctx->boolExpr())
        {

            const auto rightVarStr = visitBoolExpr(ctx->boolExpr(), currentFunction);
            const auto rightVar = currentFunction->findVarAllScopesAndArg(rightVarStr);

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const auto strLeftVarName = varDecl->varName->getText();
                const auto strLeftVarTypeName = varDecl->varTypes()->getText();

                auto leftVar = currentFunction->findVarAllScopesAndArg(strLeftVarName);

                auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                auto assign = std::make_shared<Assign>()->set(leftVar, value);
                statement->addStatement(assign);
            }
        }

        if (ctx->expr())
        {

            const auto strRightVarName = visitExpr(ctx->expr(), currentFunction);
            const auto rightVar = currentFunction->findVarAllScopesAndArg(strRightVarName);

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string leftVarName = varDecl->varName->getText();
                std::string leftVarTypeName = varDecl->varTypes()->getText();

                createMathExprAssign(leftVarName, leftVarTypeName, rightVar, currentFunction);

                // std::string strLeftVarName = varDecl->varName->getText();
                // std::string strLeftVarTypeName = varDecl->varTypes()->getText();
                //
                // int leftDataTypeType = tokenMap::getTokenType(strLeftVarTypeName);
                // auto leftVar = currentFunction->findVarAllScopesAndArg(strLeftVarName);
                //
                // if (leftDataTypeType != rightVar->getVarType()->getType())
                // {
                //     std::string strTempVar = currentFunction->generateVarName();
                //
                //     auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(leftDataTypeType));
                //     auto tempVariable =
                //             std::make_shared<Variable>()->set(strTempVar, std::make_shared<Type>(leftDataTypeType));
                //     statement->addDeclaredVariable(tempVariable);
                //
                //     auto expr = std::make_shared<Expr>()->set(tempVariable, cast);
                //     statement->addStatement(expr);
                //
                //     auto value = std::make_shared<Value>()->set(tempVariable, tempVariable->getVarType());
                //     auto assign = std::make_shared<Assign>()->set(leftVar, value);
                //     statement->addStatement(assign);
                // }
                // else
                // {
                //     auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                //     auto assign = std::make_shared<Assign>()->set(leftVar, value);
                //     statement->addStatement(assign);
                // }
            }
        }

        if (ctx->functionCall())
        {
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varTypeStr = varDecl->varTypes()->getText();
                const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);

                const auto calledFunction = visitFunctionCall(ctx->functionCall(), currentFunction);
                const auto expr = std::make_shared<Expr>()->set(variable, calledFunction);
                statement->addStatement(expr);
            }
        }

        else if (ctx->arrowFunctionInline())
        {
            visitArrowFunctionInline(ctx->arrowFunctionInline(), currentFunction);
        }
    }

    void HLIRGenerator::ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var)
    {

        if (F->findVarCurrentScopeAndArg(var->getVarName()))
        {
            return;
        }

        if (!F->findVarCurrentScopeAndArg(var->getVarName()))
        {
            const auto functionArgs = F->getFunctionArgs();
            const auto newArg = std::make_shared<Arg>()->set(var->getVarName(), var->getVarType(), var->getSignature());
            functionArgs->addArg(newArg);
        }

        if (const auto parentF = F->getParentFunction())
        {
            ensureVariableCaptured(parentF, var);
        }
    }


    // ... (continua com os demais métodos)
} // namespace hlir

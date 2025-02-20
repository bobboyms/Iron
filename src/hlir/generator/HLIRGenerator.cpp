#include "../../headers/HLIRGenerator.h"
#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/Hlir.h"

namespace hlir {

    // Construtor: inicializa os membros conforme declarado no cabeçalho.
    HLIRGenerator::HLIRGenerator(
            const std::shared_ptr<IronParser>& parser,
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<config::Configuration>& config,
            const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>>& exportContexts)
        : parser(parser), context(context), config(config), exportContexts(exportContexts)
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

    void HLIRGenerator::visitStatementList(const IronParser::StatementListContext *ctx,
                                           const std::shared_ptr<Function> &currentFunction)
    {

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
                visitIfStatement(IfStatement, currentFunction);
            }

            // if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            // {
            //     auto call = visitFunctionCall(funcCall, statement);
            //     statement->addStatement(call);
            // }
            // if (const auto re_turn = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            // {
            //     visitReturn(re_turn, statement);
            // }
        }

    }

    void HLIRGenerator::visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                            const std::shared_ptr<Function> &currentFunction)
    {
        const std::string varName = ctx->varName->getText();
        const std::string varType = ctx->varTypes()->getText();
        const auto statement =currentFunction->getCurrentLocalScope();

        const auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
        statement->addDeclaredVariable(variable);

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
                if (!variable) {
                    throw HLIRException("HLIRGenerator::visitAssignment. Variable not found");
                }

                const auto anotherVariable = currentFunction->findVarAllScopesAndArg(anotherVarName);
                if (!anotherVariable) {
                    throw HLIRException("HLIRGenerator::visitAssignment. Another Variable not found");
                }

                if (anotherVariable->isAnotherScope())
                {
                    ensureVariableCaptured(currentFunction, anotherVariable);
                }
//
                auto value = std::make_shared<Value>()->set(anotherVariable, anotherVariable->getVarType());
                auto assign = std::make_shared<Assign>()->set(variable, value);
                statement->addStatement(assign);
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

                int leftDataTypeType = tokenMap::getTokenType(strLeftVarTypeName);
                auto leftVar =
                        std::make_shared<Variable>()->set(strLeftVarName, std::make_shared<Type>(leftDataTypeType));
                statement->addDeclaredVariable(leftVar);

                auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                auto assign = std::make_shared<Assign>()->set(leftVar, value);
                statement->addStatement(assign);
            }
        }




    }

    bool HLIRGenerator::hasVariableOrArg(const std::shared_ptr<Function> &F, const std::string &varName)
    {
        // if (auto v = F->fin)
        // {
        //     return true;
        // }
        //
        // if (auto a = F->getFunctionArgs()->findArgByName(varName))
        // {
        //     return true;
        // }

        return false;
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
            const auto newArg = std::make_shared<Arg>()->set(var->getVarName(), var->getVarType());
            functionArgs->addArg(newArg);
        }
        //
        const auto parentF = F->getParentFunction();
        if (!parentF)
        {
            throw HLIRException("Variável não encontrada em escopo global");
        }

        ensureVariableCaptured(parentF, var);
    }



    // ... (continua com os demais métodos)
} // namespace hlir

//
// Created by Thiago Rodrigues on 18/02/25.
//

#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"


namespace hlir
{


    // Métodos auxiliares privados na classe HLIRGenerator

// Executa o bloco e retorna se há um comando de retorno nele.
bool HLIRGenerator::visitBlockAndCheckReturn(IronParser::IfBlockContext* blockCtx,
                                             const std::shared_ptr<Function>& currentFunction)
{
    currentFunction->enterLocalScope(std::make_shared<Statement>());
    visitIfBlock(blockCtx, currentFunction);
    const bool hasReturn = currentFunction->getCurrentLocalScope()->haveReturn();
    currentFunction->exitLocalScope();
    return hasReturn;
}

// Adiciona um bloco de fim, criando um jump se necessário.
void HLIRGenerator::handleEndBlock(const std::shared_ptr<Function>& currentFunction,
                                   const std::shared_ptr<Statement>& statement,
                                   const std::string &endLabel,
                                   const bool haveReturn)
{
    auto endBlock = std::make_shared<Block>()->set(endLabel);
    if (!haveReturn)
    {
        auto endJump = std::make_shared<Jump>(endBlock);
        statement->addStatement(endJump);
    }
    endBlock->changeToEndBlock();
    statement->addStatement(endBlock);
}

// Função de visita ao bloco simples
void HLIRGenerator::visitIfBlock(IronParser::IfBlockContext *ctx,
                                 const std::shared_ptr<Function> &currentFunction)
{
    if (ctx->statementList())
    {
        visitStatementList(ctx->statementList(), currentFunction);
    }
}

void HLIRGenerator::visitIfStatement(IronParser::IfStatementContext *ctx,
                                     const std::shared_ptr<Function> &currentFunction,
                                     const std::string &endLabel)
{
    const auto statement = currentFunction->getCurrentLocalScope();

    const std::string varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
    const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
    if (!variable)
    {
        throw HLIRException("Variable '" + varName + "' not found");
    }

    const std::string thenLabel = currentFunction->generateLabel("then");
    const std::string elseLabel = currentFunction->generateLabel("else");

    auto conditional = std::make_shared<Conditional>()->set(variable);
    conditional->setTrueLabel(thenLabel);
    conditional->setFalseLabel(elseLabel);
    statement->addStatement(conditional);

    // Bloco 'then'
    auto thenBlock = std::make_shared<Block>()->set(thenLabel);
    statement->addStatement(thenBlock);

    const bool haveReturn = ctx->ifBlock() ? visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction)
                                     : false;

    if (ctx->elseStatement())
    {
        // Adiciona jump para o bloco de fim se necessário
        if (!haveReturn)
        {
            auto endBlock = std::make_shared<Block>()->set(endLabel);
            auto endJump = std::make_shared<Jump>(endBlock);
            statement->addStatement(endJump);
        }
        visitElseStatement(ctx->elseStatement(), currentFunction, elseLabel, endLabel);
    }
    else
    {
        // Se não houver else, ajusta a label falsa e trata o bloco de fim
        conditional->setFalseLabel(endLabel);
        handleEndBlock(currentFunction, statement, endLabel, haveReturn);
    }
}

void HLIRGenerator::visitElseStatement(IronParser::ElseStatementContext *ctx,
                                       const std::shared_ptr<Function> &currentFunction,
                                       const std::string &label, const std::string &endLabel)
{
    const auto statement = currentFunction->getCurrentLocalScope();
    auto block = std::make_shared<Block>()->set(label);
    statement->addStatement(block);

    if (ctx->ifStatement())
    {
        visitIfStatement(ctx->ifStatement(), currentFunction, endLabel);
    }
    else if (ctx->ifBlock())
    {
        const bool haveReturn = visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction);
        handleEndBlock(currentFunction, statement, endLabel, haveReturn);
    }
}


//     void HLIRGenerator::visitIfBlock(IronParser::IfBlockContext *ctx, const std::shared_ptr<Function> &currentFunction)
//     {
//         if (ctx->statementList())
//         {
//             visitStatementList(ctx->statementList(), currentFunction);
//         }
//     }
//
//     void HLIRGenerator::visitIfStatement(IronParser::IfStatementContext *ctx, const std::shared_ptr<Function> &currentFunction, const std::string &endLabel)
//     {
//
//         const auto statement = currentFunction->getCurrentLocalScope();
//
//         const auto varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
//         const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
//         if (!variable)
//         {
//             throw HLIRException("Variable '" + varName + "' not found");
//         }
//
//         const std::string thenLabel = currentFunction->generateLabel("then");
//         const std::string elseLabel = currentFunction->generateLabel("else");
//         // const std::string endLabel = currentFunction->generateLabel("end");
//
//         const auto conditional = std::make_shared<Conditional>()->set(variable);
//         conditional->setTrueLabel(thenLabel);
//         conditional->setFalseLabel(elseLabel);
//
//         statement->addStatement(conditional);
//         const auto thenBlock = std::make_shared<Block>()->set(thenLabel);
//         statement->addStatement(thenBlock);
//
//         //condicional else
//
//
//
//         const auto elseBlock = std::make_shared<Block>()->set(elseLabel);
//         bool haveReturn{false};
//         {
//             currentFunction->enterLocalScope(std::make_shared<Statement>());
//             visitIfBlock(ctx->ifBlock(), currentFunction);
//             if (currentFunction->getCurrentLocalScope()->haveReturn())
//             {
//                 haveReturn = true;
//             }
//             currentFunction->exitLocalScope();
//         }
//
//
//         if (ctx->elseStatement())
//         {
//             const auto hasIfStatement = ctx->elseStatement()->ifStatement() != nullptr;
//
//             if (hasIfStatement)
//             {
//                 if (!haveReturn)
//                 {
//                     const auto endBlock = std::make_shared<Block>()->set(endLabel);
//                     const auto endJump = std::make_shared<Jump>(endBlock);
//                     statement->addStatement(endJump);
//                 }
//             } else
//             {
//                 if (!haveReturn)
//                 {
//                     const auto endBlock = std::make_shared<Block>()->set(endLabel);
//                     const auto endJump = std::make_shared<Jump>(endBlock);
//                     statement->addStatement(endJump);
//                 }
//             }
//
//             visitElseStatement(ctx->elseStatement(), currentFunction, elseLabel, endLabel);
//         }
//         else
//         {
//             conditional->setFalseLabel(endLabel);
//             const auto block = std::make_shared<Block>()->set(endLabel);
//             if (!haveReturn)
//             {
//                 const auto endJump = std::make_shared<Jump>(block);
//                 statement->addStatement(endJump);
//             }
//
//             block->changeToEndBlock();
//             statement->addStatement(block);
//         }
//     }
//
//     void HLIRGenerator::visitElseStatement(IronParser::ElseStatementContext *ctx,
//                                            const std::shared_ptr<Function> &currentFunction, const std::string &label, const std::string &endLabel)
//     {
//
//         const auto statement = currentFunction->getCurrentLocalScope();
//
//         const auto block = std::make_shared<Block>()->set(label);
//         statement->addStatement(block);
//
//         if (ctx->ifStatement())
//         {
//             visitIfStatement(ctx->ifStatement(), currentFunction, endLabel);
//         }
//         else if (ctx->ifBlock())
//         {
//             bool haveReturn{false};
//             {
//                 currentFunction->enterLocalScope(std::make_shared<Statement>());
//                 visitIfBlock(ctx->ifBlock(), currentFunction);
//                 if (currentFunction->getCurrentLocalScope()->haveReturn())
//                 {
//                     haveReturn = true;
//                 }
//                 currentFunction->exitLocalScope();
//             }
//
//             const auto block = std::make_shared<Block>()->set(endLabel);
//             if (!haveReturn)
//             {
//                 const auto endJump = std::make_shared<Jump>(block);
//                 statement->addStatement(endJump);
//             }
//
//             block->changeToEndBlock();
//             statement->addStatement(block);
//         }
//     }
//
} // namespace hlir



//
// Created by Thiago Rodrigues on 18/02/25.
//

#include <tuple>


#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"


namespace hlir
{


    // Métodos auxiliares privados na classe HLIRGenerator

// Executa o bloco e retorna se há um comando de retorno nele.
std::pair<bool, bool> HLIRGenerator::visitBlockAndCheckReturn(IronParser::IfBlockContext* blockCtx,
                                             const std::shared_ptr<Function>& currentFunction,
                                             const std::shared_ptr<Jump> &endJump)
{
    currentFunction->enterLocalScope(std::make_shared<Statement>());
    const auto [hasBreak, hasReturn] = visitIfBlock(blockCtx, currentFunction, endJump);
    // const bool hasReturn = currentFunction->getCurrentLocalScope()->haveReturn();
    currentFunction->exitLocalScope();
    return std::make_tuple(hasBreak, hasReturn);
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
std::pair<bool, bool> HLIRGenerator::visitIfBlock(IronParser::IfBlockContext *ctx,
                                 const std::shared_ptr<Function> &currentFunction,
                                 const std::shared_ptr<Jump> &endJump)
{

    if (ctx->statementList())
    {
        return visitStatementList(ctx->statementList(), currentFunction, endJump);
    }

    return std::make_pair(false, false);

}

std::pair<bool, bool>  HLIRGenerator::visitIfStatement(IronParser::IfStatementContext *ctx,
                                     const std::shared_ptr<Function> &currentFunction,
                                     const std::string &endLabel,
                                     const std::shared_ptr<Jump> &endJump)
{
    const auto statement = currentFunction->getCurrentLocalScope();

    const std::string varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
    const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
    if (!variable)
    {
        throw HLIRException(util::format("HLIRGenerator::visitIfStatement. Variable '{}' does not exist", varName));
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

    // = ctx->ifBlock() ? visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction, endJump) : false;

    bool hasBreak{false};
    bool hasReturn{false};
    if (ctx->ifBlock())
    {
        std::tie(hasBreak,hasReturn) = visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction, endJump);
    }


    if (ctx->elseStatement())
    {
        // Adiciona jump para o bloco de fim se necessário
        if (!hasReturn and !hasBreak)
        {
            auto endBlock = std::make_shared<Block>()->set(endLabel);
            auto endJump = std::make_shared<Jump>(endBlock);
            statement->addStatement(endJump);
        }
        std::tie(hasBreak,hasReturn) = visitElseStatement(ctx->elseStatement(), currentFunction, elseLabel, endLabel, endJump);
    }
    else
    {
        // Se não houver else, ajusta a label falsa e trata o bloco de fim
        conditional->setFalseLabel(endLabel);
        const auto haveReturn = hasReturn or hasBreak;
        handleEndBlock(currentFunction, statement, endLabel, haveReturn);
    }

    return std::make_pair(hasBreak, hasReturn);
}

std::pair<bool, bool> HLIRGenerator::visitElseStatement(IronParser::ElseStatementContext *ctx,
                                       const std::shared_ptr<Function> &currentFunction,
                                       const std::string &label, const std::string &endLabel,
                                       const std::shared_ptr<Jump> &endJump)
{
    const auto statement = currentFunction->getCurrentLocalScope();
    auto block = std::make_shared<Block>()->set(label);
    statement->addStatement(block);

    if (ctx->ifStatement())
    {
        return visitIfStatement(ctx->ifStatement(), currentFunction, endLabel, endJump);
    }

    if (ctx->ifBlock())
    {
        printf("endLabel 2 %s\n", endLabel.c_str());
        const auto [hasBreak, hasReturn] =
                visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction, endJump);
        const auto haveReturn = hasBreak or hasReturn;

        handleEndBlock(currentFunction, statement, endLabel, haveReturn);
        return std::make_pair(hasBreak, hasReturn);
    }
}

} // namespace hlir



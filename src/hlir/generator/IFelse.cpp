//
// Created by Thiago Rodrigues on 18/02/25.
//

#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"


namespace hlir
{
    void HLIRGenerator::visitIfBlock(IronParser::IfBlockContext *ctx, const std::shared_ptr<Function> &currentFunction)
    {
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList(), currentFunction);
        }
    }

    void HLIRGenerator::visitIfStatement(IronParser::IfStatementContext *ctx, const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        const auto varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
        const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
        if (!variable)
        {
            throw HLIRException("Variable '" + varName + "' not found");
        }

        const std::string thenLabel = currentFunction->generateLabel("then");

        const auto conditional = std::make_shared<Conditional>()->set(variable);
        conditional->setTrueLabel(thenLabel);
        statement->addStatement(conditional);

        const auto block = std::make_shared<Block>()->set(thenLabel);
        statement->addStatement(block);
        visitIfBlock(ctx->ifBlock(), currentFunction);



        if (ctx->elseStatement())
        {
            const auto elseLabel = currentFunction->generateLabel("else");
            conditional->setFalseLabel(elseLabel);
            visitElseStatement(ctx->elseStatement(), currentFunction, elseLabel);
        }
        else
        {
            const auto endLabel = currentFunction->generateLabel("end");
            conditional->setFalseLabel(endLabel);
            const auto block = std::make_shared<Block>()->set(endLabel);
            const auto endJump = std::make_shared<Jump>(block);
            statement->addStatement(endJump);
            block->changeToEndBlock();
            statement->addStatement(block);
        }
    }

    void HLIRGenerator::visitElseStatement(IronParser::ElseStatementContext *ctx,
                                           const std::shared_ptr<Function> &currentFunction, const std::string &label)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        const auto block = std::make_shared<Block>()->set(label);
        statement->addStatement(block);

        if (ctx->ifStatement())
        {
            visitIfStatement(ctx->ifStatement(), currentFunction);
        }
        else if (ctx->ifBlock())
        {
            visitIfBlock(ctx->ifBlock(), currentFunction);
        }
    }

} // namespace hlir

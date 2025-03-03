//
// Created by Thiago Rodrigues on 01/03/25.
//
#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"

namespace hlir
{
    void HLIRGenerator::visitWhileStatement(IronParser::WhileStatementContext *ctx,
                                            const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        const std::string whileCond = currentFunction->generateLabel("while_cond");
        const std::string whileBody = currentFunction->generateLabel("while_body");
        const std::string whileEnd = currentFunction->generateLabel("while_end");

        auto condBlock = std::make_shared<Block>()->set(whileCond);

        auto condJump = std::make_shared<Jump>(condBlock);
        statement->addStatement(condJump);
        statement->addStatement(condBlock);

        auto conditional = std::make_shared<Conditional>();
        conditional->setTrueLabel(whileBody);
        conditional->setFalseLabel(whileEnd);

        const auto varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
        const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
        if (!variable)
        {
            throw HLIRException(util::format("HLIRGenerator::visitWhileStatement. Variable '{}' does not exist", varName));
        }

        // statement->addDeclaredVariable(variable);

        conditional->set(variable);
        statement->addStatement(conditional);
        auto whileBodyBlock = std::make_shared<Block>()->set(whileBody);
        auto whileEndBlock = std::make_shared<Block>()->set(whileEnd);

        statement->addStatement(whileBodyBlock);
        auto endJump = std::make_shared<Jump>(whileEndBlock);

        bool hasBreak{false};
        bool hasReturn{false};
        if (ctx->statementList())
        {
           std::tie(hasBreak, hasReturn) = visitStatementList(ctx->statementList(), currentFunction, endJump);
        }

        if (!hasBreak && !hasReturn)
        {
            statement->addStatement(condJump);
        }

        statement->addStatement(whileEndBlock);


    }

    void HLIRGenerator::visitRepeatStatement(IronParser::RepeatStatementContext *ctx,
                                             const std::shared_ptr<Function> &currentFunction)
    {
    }

    void HLIRGenerator::visitForStatement(IronParser::ForStatementContext *ctx,
                                          const std::shared_ptr<Function> &currentFunction)
    {
    }

    // std::pair<bool,bool> HLIRGenerator::visitLoopStatementList(IronParser::LoopStatementListContext *ctx,
    //                                            const std::shared_ptr<Function> &currentFunction)
    // {
    //     const auto statement = currentFunction->getCurrentLocalScope();
    //     for (const auto child: ctx->children)
    //     {
    //
    //         if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
    //         {
    //             visitVarDeclaration(varDeclaration, currentFunction);
    //         }
    //
    //         if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
    //         {
    //             visitExpr(expression, currentFunction);
    //         }
    //
    //         if (const auto expression = dynamic_cast<IronParser::BoolExprContext *>(child))
    //         {
    //             visitBoolExpr(expression, currentFunction);
    //         }
    //
    //         if (dynamic_cast<IronParser::BreakStatementContext *>(child))
    //         {
    //
    //         }
    //
    //         if (const auto IfStatement = dynamic_cast<IronParser::IfStatementContext *>(child))
    //         {
    //             const auto endLabel = currentFunction->generateLabel("end");
    //             visitIfStatement(IfStatement, currentFunction, endLabel);
    //         }
    //
    //         if (const auto whileLoop = dynamic_cast<IronParser::WhileStatementContext *>(child))
    //         {
    //             visitWhileStatement(whileLoop, currentFunction);
    //         }
    //         if (const auto forLoop = dynamic_cast<IronParser::ForStatementContext *>(child))
    //         {
    //             visitForStatement(forLoop, currentFunction);
    //         }
    //         if (const auto repeatLoop = dynamic_cast<IronParser::RepeatStatementContext *>(child))
    //         {
    //             visitRepeatStatement(repeatLoop, currentFunction);
    //         }
    //
    //         if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
    //         {
    //             auto call = visitFunctionCall(funcCall, currentFunction);
    //             statement->addStatement(call);
    //         }
    //
    //         if (const auto re_turn = dynamic_cast<IronParser::ReturnStatementContext *>(child))
    //         {
    //             visitReturn(re_turn, currentFunction);
    //         }
    //     }
    //
    //     return {true, false};
    // }
}
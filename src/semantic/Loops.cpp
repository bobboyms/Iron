//
// Created by Thiago Rodrigues on 28/02/25.
//

#include "../headers/SemanticAnalysis.h"
#include <iostream>
#include <utility>
#include "../headers/Analyser.h"
#include "../headers/Files.h"

namespace iron
{
    void SemanticAnalysis::visitWhileStatement(IronParser::WhileStatementContext *ctx)
    {
        visitBoolExpr(ctx->boolExpr());
        if (ctx->loopStatementList())
        {
            visitLoopStatementList(ctx->loopStatementList());
        }
    }
    void SemanticAnalysis::visitRepeatStatement(IronParser::RepeatStatementContext *ctx)
    {
    }
    void SemanticAnalysis::visitForStatement(IronParser::ForStatementContext *ctx)
    {
    }
    void SemanticAnalysis::visitLoopStatementList(IronParser::LoopStatementListContext *ctx)
    {
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, -7);

        const auto currentFunction = getCurrentFunction();

        currentFunction->enterLocalScope(std::make_shared<scope::Statements>());

        for (const auto child: ctx->children)
        {

            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration);
            }
            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall);
            }
            if (const auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
            }
            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression);
            }
            if (const auto whileLoop = dynamic_cast<IronParser::WhileStatementContext *>(child))
            {
                visitWhileStatement(whileLoop);
            }
            if (const auto forLoop = dynamic_cast<IronParser::ForStatementContext *>(child))
            {
                visitForStatement(forLoop);
            }
            if (const auto repeatLoop = dynamic_cast<IronParser::RepeatStatementContext *>(child))
            {
                visitRepeatStatement(repeatLoop);
            }
            if (const auto IfStatement = dynamic_cast<IronParser::IfStatementContext *>(child))
            {
                visitIfStatement(IfStatement);
            }
            if (const auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
            }
        }
        currentFunction->exitLocalScope();
    }
}
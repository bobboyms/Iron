#include "../headers/SemanticAnalysis.h"

namespace iron
{

    void SemanticAnalysis::visitIfBlock(IronParser::IfBlockContext *ctx)
    {
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList());
        }
    }

    void SemanticAnalysis::visitIfStatement(IronParser::IfStatementContext *ctx)
    {
        // : IF L_PAREN boolExpr R_PAREN ifBlock (ELSE elseStatement)?
        if (!ctx->boolExpr())
        {
            throw std::runtime_error("If statement must be a boolean expression");
        }

        visitBoolExpr(ctx->boolExpr());

        if (ctx->ifBlock())
        {
            visitIfBlock(ctx->ifBlock());
        }

        if (ctx->elseStatement())
        {
            visitElseStatement(ctx->elseStatement());
        }
    }

    void SemanticAnalysis::visitElseStatement(IronParser::ElseStatementContext *ctx)
    {
    //     : ifStatement
    // | ifBlock

        if (ctx->ifStatement())
        {
            visitIfStatement(ctx->ifStatement());
        }

        if (ctx->ifBlock())
        {
            visitIfBlock(ctx->ifBlock());
        }
    }

} // namespace iron

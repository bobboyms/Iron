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
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList());
        }
    }
    void SemanticAnalysis::visitRepeatStatement(IronParser::RepeatStatementContext *ctx)
    {
    }
    void SemanticAnalysis::visitForStatement(IronParser::ForStatementContext *ctx)
    {
    }
}
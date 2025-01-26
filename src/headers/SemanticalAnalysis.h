#ifndef SEMANTICAL_ANALYSIS_H
#define SEMANTICAL_ANALYSIS_H

#include "../scope/ScopeManager.h"
#include "../parsers/IronParser.h"
#include "TokenMap.h"
#include "Exceptions.h"
#include "Colors.h"
#include "Utils.h"
// #include "Visitors.h"
#include <memory>
#include <stack>

namespace iron
{
    class SemanticalAnalysis
    {
    private:
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<scope::ScopeManager> scopeManager;

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);
        void visitStatementList(IronParser::StatementListContext *ctx);
        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx);
        void visitVarAssignment(IronParser::VarAssignmentContext *ctx);

        void visitExpr(IronParser::ExprContext *ctx);
        void visitAssignment(IronParser::AssignmentContext *ctx);

        void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx);
        void visitFunctionArgs(IronParser::FunctionArgsContext *ctx);
        void visitFunctionArg(IronParser::FunctionArgContext *ctx);

        void visitFunctionCall(IronParser::FunctionCallContext *ctx);

        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx);

        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx);

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx);
        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx);
        void visitReturn(IronParser::ReturnStatementContext *ctx);

    public:
        SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<scope::ScopeManager> scopeManager);
        ~SemanticalAnalysis();
        void analyze();
    };
}

#endif // SEMANTICAL_ANALYSIS_H

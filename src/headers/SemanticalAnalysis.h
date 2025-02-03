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
        std::vector<std::string> sourceLines;

        std::pair<std::string, std::string> getCodeLineAndCaretLine(int line, int col, int steps);
        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);
        void visitFunctionBody(IronParser::FunctionDeclarationContext *ctx);
        void visitStatementList(IronParser::StatementListContext *ctx);
        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx);
        void visitVarAssignment(IronParser::VarAssignmentContext *ctx);

        std::pair<std::string, int> visitExpr(IronParser::ExprContext *ctx);
        void visitAssignment(IronParser::AssignmentContext *ctx);

        void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx);
        void visitFunctionArgs(IronParser::FunctionArgsContext *ctx);
        void visitFunctionArg(IronParser::FunctionArgContext *ctx);

        void visitFunctionCall(IronParser::FunctionCallContext *ctx);

        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx);

        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx);

        std::shared_ptr<scope::Function> getCurrentFunction();
        std::shared_ptr<scope::Function> visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx);
        std::shared_ptr<scope::Function> visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx);
        void visitReturn(IronParser::ReturnStatementContext *ctx);

    public:
        SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<scope::ScopeManager> scopeManager, std::vector<std::string> sourceLines);
        ~SemanticalAnalysis();
        void analyze();
    };
}

#endif // SEMANTICAL_ANALYSIS_H

#ifndef SEMANTICAL_ANALYSIS_H
#define SEMANTICAL_ANALYSIS_H

#include "../parsers/IronParser.h"
#include "ScopeManager.h"
#include "Visitors.h"
#include <memory>
#include <stack>

namespace iron
{
    class SemanticalAnalysis : public Visitors
    {
    private:
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<ScopeManager> scopeManager;

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) override;
        void visitStatementList(IronParser::StatementListContext *ctx) override;
        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx) override;
        void visitVarAssignment(IronParser::VarAssignmentContext *ctx) override;

        void visitExpr(IronParser::ExprContext *ctx) override;
        void visitAssignment(IronParser::AssignmentContext *ctx) override;

        void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx) override;
        void visitFunctionArgs(IronParser::FunctionArgsContext *ctx) override;
        void visitFunctionArg(IronParser::FunctionArgContext *ctx) override;

        void visitFunctionCall(IronParser::FunctionCallContext *ctx,
                               const std::string &actualFunctionName,
                               std::shared_ptr<SymbolTable> parentScope) override;

        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx,
                                   const std::string &actualFunctionName,
                                   std::shared_ptr<SymbolTable> parentScope) override;

        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                  const std::string &actualFunctionName,
                                  std::shared_ptr<SymbolTable> parentScope) override;

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) override;
        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx) override;
        void visitReturn(IronParser::ReturnStatementContext *ctx) override;

    public:
        SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager);
        ~SemanticalAnalysis();
        void analyze();
    };
}

#endif // SEMANTICAL_ANALYSIS_H

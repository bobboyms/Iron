#ifndef SEMANTICAL_ANALYSIS_H
#define SEMANTICAL_ANALYSIS_H

#include "../parsers/IronParser.h"
#include "../scope/ScopeManager.h"
#include "Configuration.h"
#include "TokenMap.h"
#include "Utils.h"

namespace iron
{
    class SemanticAnalysis
    {
    private:
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<scope::ScopeManager> scopeManager;
        std::vector<std::string> sourceLines;
        std::shared_ptr<config::Configuration> config;

        std::pair<std::string, std::string> getCodeLineAndCaretLine(uint line, uint col, int steps);

        void visitExternBlock(IronParser::ExternBlockContext *ctx);

        void visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx);

        void visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                     std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList);

        void visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                    std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList);

        std::pair<std::string, int> visitBoolExpr(IronParser::BoolExprContext *ctx);

        void visitIfBlock(IronParser::IfBlockContext *ctx);
        void visitIfStatement(IronParser::IfStatementContext *ctx);
        void visitElseStatement(IronParser::ElseStatementContext *ctx);

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);

        void visitFunctionBody(IronParser::FunctionDeclarationContext *ctx);
        static std::shared_ptr<scope::Signature> getSignature(IronParser::FunctionSignatureContext *ctx);

        void visitStatementList(const IronParser::StatementListContext *ctx);

        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx);

        void visitVarAssignment(IronParser::VarAssignmentContext *ctx);

        void visitImportStatement(IronParser::ImportStatementContext *ctx);

        std::pair<std::string, int> visitExpr(IronParser::ExprContext *ctx);

        void visitAssignment(IronParser::AssignmentContext *ctx);

        void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx);

        void visitFunctionArgs(IronParser::FunctionArgsContext *ctx);

        void visitFunctionArg(IronParser::FunctionArgContext *ctx) const;

        void visitFunctionCall(IronParser::FunctionCallContext *ctx);
        void validateFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                     const std::shared_ptr<scope::FunctionArg> &arg);

        void visitFunctionCallArgs(const IronParser::FunctionCallArgsContext *ctx);

        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx);

        static bool validateSignature(const std::shared_ptr<scope::Signature> &signature,
                               const std::shared_ptr<scope::Function> &function);

        std::shared_ptr<scope::Function> getCurrentFunction();

        std::shared_ptr<scope::Function> visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx);

        std::shared_ptr<scope::Function> visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx);

        void visitReturn(IronParser::ReturnStatementContext *ctx);

        std::vector<std::pair<std::string, int>>

        parseFormatSpecifiers(const std::string &format, uint line, const std::string &caretLine,
                              const std::string &codeLine) const;


    public:
        explicit SemanticAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<scope::ScopeManager> scopeManager,
                                  const std::vector<std::string> &sourceLines,
                                  const std::shared_ptr<config::Configuration> &config);

        ~SemanticAnalysis();

        std::vector<std::shared_ptr<scope::Function>> analyze();
    };
} // namespace iron

#endif // SEMANTICAL_ANALYSIS_H

#ifndef VISITORS_H
#define VISITORS_H

#include <memory>
#include "../parsers/IronParser.h"
#include "../scope/ScopeManager.h"
#include "SymbolTable.h"

namespace iron
{
    class Visitors
    {
    public:
        virtual ~Visitors() = default;

        // Cada método "visit" é um contrato que a classe concreta deve implementar
        virtual void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;
        virtual void visitStatementList(IronParser::StatementListContext *ctx) = 0;
        virtual void visitVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;
        virtual void visitVarAssignment(IronParser::VarAssignmentContext *ctx) = 0;
        virtual void visitExpr(IronParser::ExprContext *ctx) = 0;
        virtual void visitAssignment(IronParser::AssignmentContext *ctx) = 0;
        virtual void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx) = 0;
        virtual void visitFunctionArgs(IronParser::FunctionArgsContext *ctx) = 0;
        virtual void visitFunctionArg(IronParser::FunctionArgContext *ctx) = 0;
        virtual void visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                       const std::string &actualFunctionName,
                                       std::shared_ptr<scope::Function> parentScope) = 0;
        virtual void visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx,
                                           const std::string &actualFunctionName,
                                           std::shared_ptr<SymbolTable> parentScope) = 0;
        virtual void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                          const std::string &actualFunctionName,
                                          std::shared_ptr<SymbolTable> parentScope) = 0;
        virtual void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) = 0;
        virtual void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx) = 0;
        virtual void visitReturn(IronParser::ReturnStatementContext *ctx) = 0;
        // Você pode (opcionalmente) incluir também a função "analyze"
        // como parte do contrato, dependendo do design
        // virtual void analyze() = 0;
    };
}

#endif

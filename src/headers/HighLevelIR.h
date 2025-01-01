#ifndef HLIR_H
#define HLIR_H

#include "../parsers/IronParser.h"
#include "ScopeManager.h"
#include "Visitors.h"
#include <memory>
#include <stack>

namespace iron {

    class HighLevelIR {
    private:
        std::stringstream sb;
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<ScopeManager> scopeManager;

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx);
        void visitStatementList(IronParser::StatementListContext* ctx) ;
        void visitVarDeclaration(IronParser::VarDeclarationContext* ctx) ;
        void visitVarAssignment(IronParser::VarAssignmentContext* ctx) ;

        void visitExpr(IronParser::ExprContext* ctx) ;
        void visitAssignment(IronParser::AssignmentContext* ctx) ;

        void visitFunctionSignature(IronParser::FunctionSignatureContext* ctx) ;
        void visitFunctionArgs(IronParser::FunctionArgsContext* ctx) ;
        void visitFunctionArg(IronParser::FunctionArgContext* ctx, bool comma);

        void visitFunctionCall(IronParser::FunctionCallContext* ctx,
                            const std::string& actualFunctionName,
                            std::shared_ptr<SymbolTable> parentScope) ;

        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx,
                                const std::string& actualFunctionName,
                                std::shared_ptr<SymbolTable> parentScope) ;

        void visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                                const std::string& actualFunctionName,
                                std::shared_ptr<SymbolTable> parentScope) ;

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx) ;
        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext* ctx) ;
        void visitReturn(IronParser::ReturnContext* ctx) ;
        

        

    public:
        HighLevelIR(std::shared_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager);
        ~HighLevelIR();
        std::string generateCode();
    };
}



#endif // HLIR_H

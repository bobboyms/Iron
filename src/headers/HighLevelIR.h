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
        std::stringstream* localSb;
        std::stringstream* globalSb;
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<ScopeManager> scopeManager;
        int tempVarCounter = 0;


        std::string generateTempVar();

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx, std::stringstream* sb);
        void visitStatementList(IronParser::StatementListContext* ctx, std::stringstream* sb) ;
        void visitVarDeclaration(IronParser::VarDeclarationContext* ctx) ;
        void visitVarAssignment(IronParser::VarAssignmentContext* ctx) ;

        std::string visitExpr(IronParser::ExprContext* ctx, std::stringstream* sb) ;
        void visitAssignment(IronParser::AssignmentContext* ctx, std::stringstream* sb) ;

        void visitFunctionSignature(IronParser::FunctionSignatureContext* ctx, std::stringstream* sb) ;
        void visitFunctionArgs(IronParser::FunctionArgsContext* ctx, std::stringstream* sb) ;
        void visitFunctionArg(IronParser::FunctionArgContext* ctx, bool comma, std::stringstream* sb);

        void visitFunctionCall(IronParser::FunctionCallContext* ctx,
                            const std::string& actualFunctionName,
                            std::shared_ptr<SymbolTable> parentScope) ;

        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx,
                                const std::string& actualFunctionName,
                                std::shared_ptr<SymbolTable> parentScope) ;

        void visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                                const std::string& actualFunctionName,
                                std::shared_ptr<SymbolTable> parentScope) ;

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx, std::stringstream* sb) ;
        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext* ctx) ;
        void visitReturn(IronParser::ReturnContext* ctx) ;
        

        

    public:
        HighLevelIR(std::shared_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager);
        ~HighLevelIR();
        std::string generateCode();
    };
}



#endif // HLIR_H

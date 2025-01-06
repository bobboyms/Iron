#ifndef HLIR_H
#define HLIR_H

#include "WriterCodeHLIR.h"
#include "../parsers/IronParser.h"
#include "ScopeManager.h"
#include "Visitors.h"
#include <memory>
#include <stack>

namespace iron {

    class HighLevelIR {
    private:
        //std::stringstream* localSb;
        //std::stringstream* globalSb;
        int tempVarCounter = 0;
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<ScopeManager> scopeManager;
        std::unique_ptr<WriterCodeHLIR> writerCodeHLIR;

        std::string generateTempVar();

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx);
        void visitStatementList(IronParser::StatementListContext* ctx, std::shared_ptr<std::stringstream>  sb) ;
        void visitVarDeclaration(IronParser::VarDeclarationContext* ctx, std::shared_ptr<std::stringstream>  sb) ;
        void visitVarAssignment(IronParser::VarAssignmentContext* ctx) ;

        std::string visitExpr(IronParser::ExprContext* ctx, std::shared_ptr<std::stringstream>  sb) ;
        void visitAssignment(IronParser::AssignmentContext* ctx, std::shared_ptr<std::stringstream>  sb) ;

        void visitFunctionSignature(IronParser::FunctionSignatureContext* ctx, std::shared_ptr<std::stringstream>  sb) ;
        void visitFunctionArgs(IronParser::FunctionArgsContext* ctx, std::shared_ptr<std::stringstream>  sb) ;
        void visitFunctionArg(IronParser::FunctionArgContext* ctx, bool comma, std::shared_ptr<std::stringstream> sb);

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

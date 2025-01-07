#ifndef LLVMIR_H
#define LLVMIR_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include "../parsers/HightLavelIRParser.h"
#include "../parsers/HightLavelIRLexer.h" 
#include "ScopeManager.h"
#include "Visitors.h"
#include <memory>
#include <stack>

namespace iron {

    class LLVMIR {
    private:

        std::string hlirCode;
        std::unique_ptr<ScopeManager> scopeManager;
        llvm::LLVMContext context;
        llvm::IRBuilder<> builder;
        std::unique_ptr<llvm::Module> module;

        void visitStatementList(HightLavelIRParser::StatementListContext* ctx) ;
        void visitExpr(HightLavelIRParser::ExprContext* ctx) ;
        void visitCast(HightLavelIRParser::CastContext* ctx);
        void visitOp(HightLavelIRParser::OpContext* ctx);
        void visitMathOp(HightLavelIRParser::Math_opContext* ctx);


        void visitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext* ctx);


        void visitFunctionSignature(HightLavelIRParser::FunctionSignatureContext* ctx) ;
        void visitFunctionArgs(HightLavelIRParser::FunctionArgsContext* ctx) ;
        void visitFunctionArg(HightLavelIRParser::FunctionArgContext* ctx);
        void visitFunctionCall(HightLavelIRParser::FunctionCallContext* ctx) ;
        void visitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext* ctx) ;
        void visitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext* ctx) ;
        

    public:
        LLVMIR(std::string hlirCode, std::unique_ptr<ScopeManager> scopeManager);
        ~LLVMIR();
        std::string generateCode();
    };
}



#endif // LLVMIR

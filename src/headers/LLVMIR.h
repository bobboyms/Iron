/**
 * @file LLVMIR.h
 * @brief Declaration of the LLVMIR class for generating LLVM Intermediate Representation (IR).
 */

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
#include "Exceptions.h"
#include "Utils.h"
#include "Hlir.h"
#include "TokenMap.h"
#include <memory>
#include <stack>

namespace iron
{
    class LLVM
    {
    private:
        std::shared_ptr<hlir::Context> hlirContext;
        llvm::LLVMContext llvmContext;        /**< LLVM context used for IR generation. */
        llvm::IRBuilder<> builder;            /**< LLVM IRBuilder used to create LLVM instructions. */
        std::unique_ptr<llvm::Module> module; /**< LLVM Module that holds the generated IR. */

    public:
        LLVM(std::shared_ptr<hlir::Context> hlirContext);
        ~LLVM();

        std::string generateCode();
        /**
         * @brief Maps a custom type from the HLIR to the corresponding LLVM Type.
         *
         * Converts types defined in TokenMap (e.g., TYPE_INT, TYPE_FLOAT) to their equivalent LLVM
         * Type representations. Throws an exception if the type is unknown.
         *
         * @param type The integer representation of the type from TokenMap.
         * @return Pointer to the corresponding LLVM Type.
         *
         * @throws LLVMException If the provided type is unknown or unsupported.
         */
        llvm::Type *mapType(const int type);
        void generateTerminator(llvm::Type *functionReturnType);
        void assignValue(std::shared_ptr<hlir::Variable> variable, std::shared_ptr<hlir::Value> value, llvm::AllocaInst *allocaVariable);
        void assignVariable(std::shared_ptr<hlir::Value> value, llvm::AllocaInst *allocaVariable, llvm::Function *function);
        llvm::AllocaInst *allocaVariable(std::shared_ptr<hlir::Variable> variable);
        llvm::AllocaInst *findAllocaByName(llvm::Function *function, const std::string &varName);
        llvm::Argument *findArgByName(llvm::Function *function, const std::string &argname);

        llvm::Value *executeMult(std::shared_ptr<hlir::Mult> mult, llvm::Function *currentFunction);
        llvm::Value *executeDiv(std::shared_ptr<hlir::Div> div, llvm::Function *currentFunction);
        llvm::Value *executePlus(std::shared_ptr<hlir::Plus> plus, llvm::Function *currentFunction);
        llvm::Value *executeMinus(std::shared_ptr<hlir::Minus> minus, llvm::Function *currentFunction);
        llvm::Value *numberCasting(std::shared_ptr<hlir::Variable> variable, std::shared_ptr<hlir::Type> type, llvm::Function *currentFunction);
        std::pair<llvm::LoadInst *, llvm::LoadInst *> operationLoad(std::shared_ptr<hlir::BinaryOperation> op, llvm::Function *currentFunction);
        llvm::AllocaInst *promoteArgumentToAlloca(llvm::Function *function, llvm::Argument *arg);
        llvm::AllocaInst *getOrPromoteToAlloca(const std::string &varName, llvm::Function *function);
        llvm::Value *createConstValue(std::shared_ptr<hlir::Type> type, std::shared_ptr<hlir::Value> value);

        void declareFunction(std::shared_ptr<hlir::Function> hlirFunction);

        void visitFunction(std::shared_ptr<hlir::Function> hlirFunction);
        void visitStatement(std::shared_ptr<hlir::Statement> hlirStatement);
        void visitExpr(std::shared_ptr<hlir::Expr> hlirExpr);
        void visitAssignment(std::shared_ptr<hlir::Assign> hlirAssignment);
        llvm::Value *visitFunctionCall(std::shared_ptr<hlir::FunctionCall> functionCall);
    };

} // namespace iron

#endif // LLVMIR_H

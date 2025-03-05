#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    /**
     * @brief Loads left and right operands of a binary operation from their allocations
     * 
     * @param op The binary operation containing variable references
     * @param currentFunction The current function context
     * @return std::pair<llvm::LoadInst *, llvm::LoadInst *> Pair of load instructions for left and right variables
     * @throws LLVMException if any operand cannot be loaded
     */
    std::pair<llvm::LoadInst *, llvm::LoadInst *> LLVM::operationLoad(const std::shared_ptr<hlir::BinaryOperation>& op,
                                                                      llvm::Function *currentFunction)
    {
        if (!op) {
            throw LLVMException("operationLoad: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("operationLoad: currentFunction is null");
        }
        
        if (!op->getVarLeft() || !op->getVarRight()) {
            throw LLVMException("operationLoad: one or both operation variables are null");
        }
        
        // Get variable allocations
        llvm::AllocaInst *leftVar = getOrPromoteToAlloca(op->getVarLeft()->getRealName(), currentFunction);
        llvm::AllocaInst *rightVar = getOrPromoteToAlloca(op->getVarRight()->getRealName(), currentFunction);

        // Get allocation types
        llvm::Type *leftAllocatedType = leftVar->getAllocatedType();
        llvm::Type *rightAllocatedType = rightVar->getAllocatedType();

        // Create load instructions
        llvm::LoadInst *loadLeftVar =
                builder.CreateLoad(leftAllocatedType, leftVar, util::format("load_{}", op->getVarLeft()->getRealName()));
        llvm::LoadInst *loadRightVar = builder.CreateLoad(rightAllocatedType, rightVar,
                                                          util::format("load_{}", op->getVarRight()->getRealName()));

        return std::make_pair(loadLeftVar, loadRightVar);
    }

    /**
     * @brief Creates a logical AND operation
     * 
     * @param _and The AND operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the AND operation
     */
    llvm::Value *LLVM::executeAND(const std::shared_ptr<hlir::AND> &_and, llvm::Function *currentFunction)
    {
        if (!_and) {
            throw LLVMException("executeAND: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeAND: currentFunction is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(_and, currentFunction);
        return builder.CreateAnd(loadLeftVar, loadRightVar, "and_");
    }

    /**
     * @brief Creates a logical OR operation
     * 
     * @param _or The OR operation details 
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the OR operation
     */
    llvm::Value *LLVM::executeOR(const std::shared_ptr<hlir::OR> &_or, llvm::Function *currentFunction)
    {
        if (!_or) {
            throw LLVMException("executeOR: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeOR: currentFunction is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(_or, currentFunction);
        return builder.CreateOr(loadLeftVar, loadRightVar, "or_");
    }

    /**
     * @brief Creates a logical NOT operation (implemented as XOR with true)
     * 
     * @param _not The NOT operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the NOT operation
     */
    llvm::Value *LLVM::executeNOT(const std::shared_ptr<hlir::_NOT> &_not, llvm::Function *currentFunction)
    {
        if (!_not) {
            throw LLVMException("executeNOT: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeNOT: currentFunction is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(_not, currentFunction);
        return builder.CreateXor(loadLeftVar, loadRightVar, "not_");
    }

    /**
     * @brief Creates a comparison operation
     * 
     * This function handles various comparison operators for both floating point
     * and integer types.
     * 
     * @param cmp The comparison operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the comparison operation (i1 value)
     * @throws LLVMException for unsupported operators
     */
    llvm::Value *LLVM::executeCMP(const std::shared_ptr<hlir::CMP> &cmp, llvm::Function *currentFunction)
    {
        if (!cmp) {
            throw LLVMException("executeCMP: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeCMP: currentFunction is null");
        }
        
        if (!cmp->getVarLeft() || !cmp->getVarLeft()->getVarType()) {
            throw LLVMException("executeCMP: left variable or its type is null");
        }
        
        if (!cmp->getOpType()) {
            throw LLVMException("executeCMP: operation type is null");
        }
        
        // Load operands
        auto [loadLeftVar, loadRightVar] = operationLoad(cmp, currentFunction);

        // Determine if we're working with floating point types
        const auto varType = cmp->getVarLeft()->getVarType()->getType();
        const bool isFloating = (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE);

        // Get operation type
        const int opType = cmp->getOpType()->getType();

        // Handle floating point comparisons
        if (isFloating)
        {
            switch (opType)
            {
                case tokenMap::EQEQ: // '=='
                    return builder.CreateFCmpOEQ(loadLeftVar, loadRightVar, "cmp_eq");
                case tokenMap::NEQ: // '!='
                    return builder.CreateFCmpONE(loadLeftVar, loadRightVar, "cmp_neq");
                case tokenMap::LT: // '<'
                    return builder.CreateFCmpOLT(loadLeftVar, loadRightVar, "cmp_lt");
                case tokenMap::LTE: // '<='
                    return builder.CreateFCmpOLE(loadLeftVar, loadRightVar, "cmp_lte");
                case tokenMap::GT: // '>'
                    return builder.CreateFCmpOGT(loadLeftVar, loadRightVar, "cmp_gt");
                case tokenMap::GTE: // '>='
                    return builder.CreateFCmpOGE(loadLeftVar, loadRightVar, "cmp_gte");
                default:
                    throw LLVMException(util::format(
                        "Unsupported floating-point comparison operator: {}", 
                        tokenMap::getTokenText(opType)));
            }
        }
        
        // Handle integer comparisons
        switch (opType)
        {
            case tokenMap::EQEQ: // '=='
                return builder.CreateICmpEQ(loadLeftVar, loadRightVar, "cmp_eq");
            case tokenMap::NEQ: // '!='
                return builder.CreateICmpNE(loadLeftVar, loadRightVar, "cmp_neq");
            case tokenMap::LT: // '<'
                return builder.CreateICmpSLT(loadLeftVar, loadRightVar, "cmp_lt");
            case tokenMap::LTE: // '<='
                return builder.CreateICmpSLE(loadLeftVar, loadRightVar, "cmp_lte");
            case tokenMap::GT: // '>'
                return builder.CreateICmpSGT(loadLeftVar, loadRightVar, "cmp_gt");
            case tokenMap::GTE: // '>='
                return builder.CreateICmpSGE(loadLeftVar, loadRightVar, "cmp_gte");
            default:
                throw LLVMException(util::format(
                    "Unsupported integer comparison operator: {}", 
                    tokenMap::getTokenText(opType)));
        }
    }

    /**
     * @brief Creates a multiplication operation
     * 
     * @param mult The multiplication operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the multiplication
     */
    llvm::Value *LLVM::executeMult(const std::shared_ptr<hlir::Mult> &mult, llvm::Function *currentFunction)
    {
        if (!mult) {
            throw LLVMException("executeMult: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeMult: currentFunction is null");
        }
        
        if (!mult->getVarLeft() || !mult->getVarLeft()->getVarType()) {
            throw LLVMException("executeMult: left variable or its type is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(mult, currentFunction);

        // Check if we're dealing with floating point values
        const auto varType = mult->getVarLeft()->getVarType()->getType();
        
        if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE) {
            return builder.CreateFMul(loadLeftVar, loadRightVar, "rmult");
        }
        
        return builder.CreateMul(loadLeftVar, loadRightVar, "rmult");
    }

    /**
     * @brief Creates a division operation
     * 
     * @param div The division operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the division
     */
    llvm::Value *LLVM::executeDiv(const std::shared_ptr<hlir::Div> &div, llvm::Function *currentFunction)
    {
        if (!div) {
            throw LLVMException("executeDiv: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeDiv: currentFunction is null");
        }
        
        if (!div->getVarLeft() || !div->getVarLeft()->getVarType()) {
            throw LLVMException("executeDiv: left variable or its type is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(div, currentFunction);

        // Check if we're dealing with floating point values
        const auto varType = div->getVarLeft()->getVarType()->getType();
        
        if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE) {
            return builder.CreateFDiv(loadLeftVar, loadRightVar, "rdiv");
        }
        
        // TODO: Consider adding a check for division by zero here
        return builder.CreateSDiv(loadLeftVar, loadRightVar, "rdiv");
    }

    /**
     * @brief Creates an addition operation
     * 
     * @param plus The addition operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the addition
     */
    llvm::Value *LLVM::executePlus(const std::shared_ptr<hlir::Plus> &plus, llvm::Function *currentFunction)
    {
        if (!plus) {
            throw LLVMException("executePlus: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executePlus: currentFunction is null");
        }
        
        if (!plus->getVarLeft() || !plus->getVarLeft()->getVarType()) {
            throw LLVMException("executePlus: left variable or its type is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(plus, currentFunction);

        // Check if we're dealing with floating point values
        const auto varType = plus->getVarLeft()->getVarType()->getType();
        
        if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE) {
            return builder.CreateFAdd(loadLeftVar, loadRightVar, "rplus");
        }
        
        return builder.CreateAdd(loadLeftVar, loadRightVar, "rplus");
    }

    /**
     * @brief Creates a subtraction operation
     * 
     * @param minus The subtraction operation details
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the subtraction
     */
    llvm::Value *LLVM::executeMinus(const std::shared_ptr<hlir::Minus> &minus, llvm::Function *currentFunction)
    {
        if (!minus) {
            throw LLVMException("executeMinus: operation is null");
        }
        
        if (!currentFunction) {
            throw LLVMException("executeMinus: currentFunction is null");
        }
        
        if (!minus->getVarLeft() || !minus->getVarLeft()->getVarType()) {
            throw LLVMException("executeMinus: left variable or its type is null");
        }
        
        auto [loadLeftVar, loadRightVar] = operationLoad(minus, currentFunction);

        // Check if we're dealing with floating point values
        const auto varType = minus->getVarLeft()->getVarType()->getType();
        
        if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE) {
            return builder.CreateFSub(loadLeftVar, loadRightVar, "rminus");
        }
        
        return builder.CreateSub(loadLeftVar, loadRightVar, "rminus");
    }
} // namespace iron

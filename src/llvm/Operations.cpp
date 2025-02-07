#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    std::pair<llvm::LoadInst *, llvm::LoadInst *> LLVM::operationLoad(std::shared_ptr<hlir::BinaryOperation> op,
                                                                      llvm::Function *currentFunction)
    {
        llvm::AllocaInst *leftVar = getOrPromoteToAlloca(op->getVarLeft()->getVarName(), currentFunction);
        llvm::AllocaInst *rightVar = getOrPromoteToAlloca(op->getVarRight()->getVarName(), currentFunction);

        auto varType = op->getVarLeft()->getVarType()->getType();

        llvm::Type *leftAllocatedType = leftVar->getAllocatedType();
        llvm::Type *rightAllocatedType = rightVar->getAllocatedType();

        llvm::LoadInst *loadLeftVar =
                builder.CreateLoad(leftAllocatedType, leftVar, util::format("load_{}", op->getVarLeft()->getVarName()));
        llvm::LoadInst *loadRightVar = builder.CreateLoad(rightAllocatedType, rightVar,
                                                          util::format("load_{}", op->getVarRight()->getVarName()));

        return std::make_pair(loadLeftVar, loadRightVar);
    }

    llvm::Value *LLVM::executeMult(const std::shared_ptr<hlir::Mult> &mult, llvm::Function *currentFunction)
    {
        auto [loadLeftVar, loadRightVar] = operationLoad(mult, currentFunction);

        if (auto varType = mult->getVarLeft()->getVarType()->getType();
            varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
        {
            llvm::Value *result = builder.CreateFMul(loadLeftVar, loadRightVar, util::format("rmult", ""));

            return result;
        }
        else
        {
            llvm::Value *result = builder.CreateMul(loadLeftVar, loadRightVar, util::format("rmult", ""));

            return result;
        }
    }

    llvm::Value *LLVM::executeDiv(const std::shared_ptr<hlir::Div> &div, llvm::Function *currentFunction)
    {
        auto [loadLeftVar, loadRightVar] = operationLoad(div, currentFunction);

        if (const auto varType = div->getVarLeft()->getVarType()->getType();
            varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
        {
            llvm::Value *result = builder.CreateFDiv(loadLeftVar, loadRightVar, util::format("rdiv", ""));

            return result;
        }
        else
        {
            llvm::Value *result = builder.CreateSDiv(loadLeftVar, loadRightVar, util::format("rdiv", ""));

            return result;
        }
    }

    llvm::Value *LLVM::executePlus(std::shared_ptr<hlir::Plus> plus, llvm::Function *currentFunction)
    {
        auto [loadLeftVar, loadRightVar] = operationLoad(plus, currentFunction);

        if (const auto varType = plus->getVarLeft()->getVarType()->getType();
            varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
        {
            llvm::Value *result = builder.CreateFAdd(loadLeftVar, loadRightVar, util::format("rplus", ""));
            return result;
        }
        else
        {
            llvm::Value *result = builder.CreateAdd(loadRightVar, loadRightVar, util::format("rplus", ""));
            return result;
        }
    }

    llvm::Value *LLVM::executeMinus(const std::shared_ptr<hlir::Minus> &minus, llvm::Function *currentFunction)
    {
        auto [loadLeftVar, loadRightVar] = operationLoad(minus, currentFunction);

        if (const auto varType = minus->getVarLeft()->getVarType()->getType();
            varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
        {
            llvm::Value *result = builder.CreateFSub(loadLeftVar, loadRightVar, util::format("rminus", ""));
            return result;
        }
        else
        {
            llvm::Value *result = builder.CreateSub(loadLeftVar, loadRightVar, util::format("rminus", ""));
            return result;
        }
    }
} // namespace iron

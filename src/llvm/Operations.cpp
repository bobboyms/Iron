#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    std::pair<llvm::LoadInst *, llvm::LoadInst *> LLVM::operationLoad(const std::shared_ptr<hlir::BinaryOperation>& op,
                                                                      llvm::Function *currentFunction)
    {
        llvm::AllocaInst *leftVar = getOrPromoteToAlloca(op->getVarLeft()->getRealName(), currentFunction);
        llvm::AllocaInst *rightVar = getOrPromoteToAlloca(op->getVarRight()->getRealName(), currentFunction);

        llvm::Type *leftAllocatedType = leftVar->getAllocatedType();
        llvm::Type *rightAllocatedType = rightVar->getAllocatedType();

        llvm::LoadInst *loadLeftVar =
                builder.CreateLoad(leftAllocatedType, leftVar, util::format("load_{}", op->getVarLeft()->getRealName()));
        llvm::LoadInst *loadRightVar = builder.CreateLoad(rightAllocatedType, rightVar,
                                                          util::format("load_{}", op->getVarRight()->getRealName()));

        return std::make_pair(loadLeftVar, loadRightVar);
    }

    llvm::Value *LLVM::executeAND(const std::shared_ptr<hlir::AND> &_and, llvm::Function *currentFunction)
    {
        // Carrega os operandos esquerdo e direito
        auto [loadLeftVar, loadRightVar] = operationLoad(_and, currentFunction);
        return builder.CreateAnd(loadLeftVar, loadRightVar, "and_");
    }

    llvm::Value *LLVM::executeOR(const std::shared_ptr<hlir::OR> &_or, llvm::Function *currentFunction)
    {
        // Carrega os operandos esquerdo e direito
        auto [loadLeftVar, loadRightVar] = operationLoad(_or, currentFunction);
        return builder.CreateOr(loadLeftVar, loadRightVar, "or_");
    }

    llvm::Value *LLVM::executeNOT(const std::shared_ptr<hlir::_NOT> &_not, llvm::Function *currentFunction)
    {
        // Carrega os operandos esquerdo e direito
        auto [loadLeftVar, loadRightVar] = operationLoad(_not, currentFunction);
        return builder.CreateXor(loadLeftVar, loadRightVar, "not_");
    }

    llvm::Value *LLVM::executeCMP(const std::shared_ptr<hlir::CMP> &cmp, llvm::Function *currentFunction)
    {
        // Carrega os operandos esquerdo e direito
        auto [loadLeftVar, loadRightVar] = operationLoad(cmp, currentFunction);

        // Obtém o tipo da variável para decidir se é ponto flutuante ou inteiro
        const auto varType = cmp->getVarLeft()->getVarType()->getType();
        const bool isFloating = (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE);

        // Obtém o tipo de operação (ex: GT, LT, EQEQ, etc.)
        const int opType = cmp->getOpType()->getType();

        if (isFloating)
        {
            // Para operandos em ponto flutuante, usamos as comparações do tipo fcmp
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
                    llvm_unreachable("Operador de ponto flutuante não suportado");
            }
        }
        // Para operandos inteiros, usamos as comparações do tipo icmp
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
                llvm_unreachable("Operador inteiro não suportado");
        }
    }


    llvm::Value *LLVM::executeMult(const std::shared_ptr<hlir::Mult> &mult, llvm::Function *currentFunction)
    {
        auto [loadLeftVar, loadRightVar] = operationLoad(mult, currentFunction);

        if (const auto varType = mult->getVarLeft()->getVarType()->getType();
            varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
        {
            llvm::Value *result = builder.CreateFMul(loadLeftVar, loadRightVar, util::format("rmult", ""));

            return result;
        }
        llvm::Value *result = builder.CreateMul(loadLeftVar, loadRightVar, util::format("rmult", ""));

        return result;
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

        llvm::Value *result = builder.CreateSDiv(loadLeftVar, loadRightVar, util::format("rdiv", ""));

        return result;
    }

    llvm::Value *LLVM::executePlus(const std::shared_ptr<hlir::Plus> &plus, llvm::Function *currentFunction)
    {
        auto [loadLeftVar, loadRightVar] = operationLoad(plus, currentFunction);

        if (const auto varType = plus->getVarLeft()->getVarType()->getType();
            varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
        {
            llvm::Value *result = builder.CreateFAdd(loadLeftVar, loadRightVar, util::format("rplus", ""));
            return result;
        }

        llvm::Value *result = builder.CreateAdd(loadLeftVar, loadRightVar, util::format("rplus", ""));
        return result;
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
        llvm::Value *result = builder.CreateSub(loadLeftVar, loadRightVar, util::format("rminus", ""));
        return result;
    }
} // namespace iron

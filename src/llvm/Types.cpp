#include "../headers/LLVMIR.h"
#include "../headers/Exceptions.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{

    void LLVM::assignVariable(std::shared_ptr<hlir::Value> value, llvm::AllocaInst *allocaVariable, llvm::Function *function)
    {

        std::visit(
            [this, function, allocaVariable](auto &&variable)
            {
                using T = std::decay_t<decltype(variable)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                {
                    if (variable)
                    {

                        auto anotherAlloca = this->findAllocaByName(function, variable->getVarName());
                        llvm::LoadInst *loadInst = builder.CreateLoad(builder.getInt32Ty(), anotherAlloca, util::format("load_{}", variable->getVarName()));
                        builder.CreateStore(loadInst, allocaVariable);
                    }
                }
            },
            value->getValue());
    }

    void LLVM::assignValue(std::shared_ptr<hlir::Variable> variable, std::shared_ptr<hlir::Value> value, llvm::AllocaInst *allocaVariable)
    {
        llvm::Value *valueToStore = nullptr;

        switch (variable->getVarType()->getType())
        {
        case tokenMap::TYPE_INT:
        {

            // Convert string to int
            int num = std::stoi(value->getText());

            // Create a 32-bit integer constant
            llvm::Constant *constInt = llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(llvmContext),
                num,
                true // Signed
            );
            valueToStore = constInt;
            break;
        }

        case tokenMap::TYPE_FLOAT:
        {
            // Convert string to float
            float num = std::stof(value->getText());
            llvm::APFloat apFloatValue(num);
            llvm::Constant *constFP = llvm::ConstantFP::get(llvmContext, apFloatValue);
            valueToStore = constFP;
            break;
        }

        case tokenMap::TYPE_DOUBLE:
        {
            // Convert string to double
            double num = std::stod(value->getText());
            llvm::APFloat apFloatValue(num);
            llvm::Constant *constFP = llvm::ConstantFP::get(llvmContext, apFloatValue);
            valueToStore = constFP;
            break;
        }

        default:
        {
            throw iron::LLVMException(util::format("Unsupported type for number literal: {}", value->getText()));
        }
        }
        builder.CreateStore(valueToStore, allocaVariable);
    }

    void LLVM::generateTerminator(llvm::Type *functionReturnType)
    {
        // Caso float
        if (functionReturnType->isFloatTy())
        {
            builder.CreateRet(
                llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0f)));
        }
        // Caso double
        else if (functionReturnType->isDoubleTy())
        {
            builder.CreateRet(
                llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0)));
        }
        // Caso boolean (i1)
        else if (functionReturnType->isIntegerTy(1))
        {
            builder.CreateRet(
                llvm::ConstantInt::get(functionReturnType, 0, /*isSigned=*/false));
        }
        // Caso char (i8)
        else if (functionReturnType->isIntegerTy(8))
        {
            builder.CreateRet(
                llvm::ConstantInt::get(functionReturnType, 0, /*isSigned=*/false));
        }
        // Caso int (i32) - se quiser diferenciar int32 de outros ints
        else if (functionReturnType->isIntegerTy(32))
        {
            builder.CreateRet(
                llvm::ConstantInt::get(functionReturnType, 0));
        }
        else if (functionReturnType->isVoidTy())
        {
            builder.CreateRetVoid();
        }
        // Demais tipos não tratados
        else
        {
            throw LLVMException("LLVM::generateTerminator: Type not handled");
        }
    }

    // Converte tipos do HighLevelIR para o LLVM Type
    llvm::Type *LLVM::mapType(const int type)
    {
        if (type == tokenMap::TYPE_INT)
        {
            return llvm::Type::getInt32Ty(llvmContext);
        }
        else if (type == tokenMap::TYPE_FLOAT)
        {
            return llvm::Type::getFloatTy(llvmContext);
        }
        else if (type == tokenMap::TYPE_DOUBLE)
        {
            return llvm::Type::getDoubleTy(llvmContext);
        }
        else if (type == tokenMap::TYPE_CHAR)
        {
            return llvm::Type::getInt8Ty(llvmContext);
        }
        else if (type == tokenMap::TYPE_BOOLEAN)
        {
            return llvm::Type::getInt1Ty(llvmContext);
        }
        else if (type == tokenMap::VOID)
        {
            return llvm::Type::getVoidTy(llvmContext);
        }
        // Adicione outros tipos conforme necessário
        throw LLVMException(util::format("Unknown data type: {}", tokenMap::getTokenText(type)));
    }

    llvm::Argument *LLVM::findArgByName(llvm::Function *function, const std::string &argname)
    {
        if (!function)
        {
            throw LLVMException(
                util::format("{} Function {} not found", "LLVM::findArgByName"));
        }

        for (auto &arg : function->args())
        {
            if (arg.getName().str() == argname)
            {
                return &arg;
            }
        }

        return nullptr;
    }

    // Função auxiliar para obter ou promover uma variável para AllocaInst
    llvm::AllocaInst *LLVM::getOrPromoteToAlloca(const std::string &varName, std::shared_ptr<hlir::BinaryOperation> op, llvm::Function *function)
    {
        llvm::AllocaInst *var = findAllocaByName(function, varName);
        if (!var)
        {
            llvm::Argument *arg = findArgByName(function, varName);
            if (!arg)
            {
                throw LLVMException(util::format("LLVM::getOrPromoteToAlloca. Variable %s not found", varName));
            }
            var = promoteArgumentToAlloca(function, arg);
        }
        return var;
    }

    llvm::AllocaInst *LLVM::promoteArgumentToAlloca(llvm::Function *function, llvm::Argument *arg)
    {
        if (!arg)
        {
            throw LLVMException("promoteArgumentToAlloca. Argument is null");
        }

        llvm::BasicBlock &entryBB = function->getEntryBlock();
        auto insertPoint = entryBB.getFirstInsertionPt();
        llvm::IRBuilder<> tempBuilder(&entryBB, insertPoint);

        llvm::AllocaInst *argAlloca = tempBuilder.CreateAlloca(
            arg->getType(), nullptr, arg->getName() + "_alloca");
        builder.CreateStore(arg, argAlloca);

        return argAlloca;
    }

    // Função para buscar uma AllocaInst por nome
    llvm::AllocaInst *LLVM::findAllocaByName(llvm::Function *function, const std::string &varName)
    {
        for (auto &block : *function)
        {
            for (auto &inst : block)
            {
                if (auto allocaInst = llvm::dyn_cast<llvm::AllocaInst>(&inst))
                {

                    if (allocaInst->getName() == varName)
                    {
                        return allocaInst;
                    }
                }
            }
        }

        return nullptr;
    }

    llvm::AllocaInst *LLVM::allocaVariable(std::shared_ptr<hlir::Variable> variable)
    {
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();

        llvm::BasicBlock &entryBlock = currentFunction->getEntryBlock();
        llvm::IRBuilder<> tmpBuilder(&entryBlock, entryBlock.begin());

        llvm::Type *llvmType = mapType(variable->getVarType()->getType());
        llvm::AllocaInst *allocaVariable = tmpBuilder.CreateAlloca(llvmType, nullptr, variable->getVarName());
        return allocaVariable;
    }

    llvm::Value *LLVM::numberCasting(std::shared_ptr<hlir::Variable> variable, std::shared_ptr<hlir::Type> type, llvm::Function *currentFunction)
    {
        auto castVar = findAllocaByName(currentFunction, variable->getVarName());
        llvm::Type *allocatedType = castVar->getAllocatedType();
        llvm::LoadInst *loadedVar = builder.CreateLoad(allocatedType, castVar, util::format("load_{}", variable->getVarName()));

        llvm::Type *desiredType = mapType(type->getType());

        llvm::Value *value;

        // Converter float
        if (variable->getVarType()->getType() == tokenMap::TYPE_FLOAT && type->getType() == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", variable->getVarName()));
        }
        else if (variable->getVarType()->getType() == tokenMap::TYPE_FLOAT && type->getType() == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateFPExt(loadedVar, desiredType, util::format("cast_{}", variable->getVarName()));
        }
        // Converter int
        else if (variable->getVarType()->getType() == tokenMap::TYPE_INT && type->getType() == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", variable->getVarName()));
        }
        else if (variable->getVarType()->getType() == tokenMap::TYPE_INT && type->getType() == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", variable->getVarName()));
        }
        // Converter double
        else if (variable->getVarType()->getType() == tokenMap::TYPE_DOUBLE && type->getType() == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateFPTrunc(loadedVar, desiredType, util::format("cast_{}", variable->getVarName()));
        }
        else if (variable->getVarType()->getType() == tokenMap::TYPE_DOUBLE && type->getType() == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", variable->getVarName()));
        }
        // Caso não definido
        else
        {
            throw LLVMException("LLVM::numberCasting. Type conversion not defined.");
        }

        return value;
    }

    //******************************************************************** */
    // Converte tipos do HighLevelIR para o LLVM Type
    llvm::Type *LLVMIR::mapType(const int type)
    {
        if (type == tokenMap::TYPE_INT)
        {
            return llvm::Type::getInt32Ty(context);
        }
        else if (type == tokenMap::TYPE_FLOAT)
        {
            return llvm::Type::getFloatTy(context);
        }
        else if (type == tokenMap::TYPE_DOUBLE)
        {
            return llvm::Type::getDoubleTy(context);
        }
        else if (type == tokenMap::TYPE_CHAR)
        {
            return llvm::Type::getInt8Ty(context);
        }
        else if (type == tokenMap::TYPE_BOOLEAN)
        {
            return llvm::Type::getInt1Ty(context);
        }
        else if (type == tokenMap::VOID)
        {
            return llvm::Type::getVoidTy(context);
        }
        // Adicione outros tipos conforme necessário
        throw LLVMException(util::format("Unknown data type: {}", tokenMap::getTokenText(type)));
    }
}

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
                        auto type = mapType(variable->getVarType()->getType());
                        auto anotherAlloca = this->findAllocaByName(function, variable->getVarName());
                        llvm::LoadInst *loadInst = builder.CreateLoad(type, anotherAlloca, util::format("load_{}", variable->getVarName()));
                        builder.CreateStore(loadInst, allocaVariable);
                    }
                }
            },
            value->getValue());
    }

    void LLVM::assignValue(std::shared_ptr<hlir::Variable> variable, std::shared_ptr<hlir::Value> value, llvm::AllocaInst *allocaVariable)
    {
        // Verificações iniciais de validade
        if (!variable)
        {
            throw iron::LLVMException("LLVM::assignValue: 'variable' is a null pointer.");
        }

        if (!value)
        {
            throw iron::LLVMException("LLVM::assignValue: 'value' is a null pointer.");
        }

        if (!allocaVariable)
        {
            throw iron::LLVMException("LLVM::assignValue: 'allocaVariable' is a null pointer.");
        }

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

        // Verifica a consistência de tipos antes de armazenar
        if (valueToStore->getType() != allocaVariable->getAllocatedType())
        {
            throw iron::LLVMException(util::format("LLVM::assignValue: Type mismatch", ""));
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
                util::format("{} Function not found", "LLVM::findArgByName"));
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
    llvm::AllocaInst *LLVM::getOrPromoteToAlloca(const std::string &varName, llvm::Function *function)
    {
        llvm::AllocaInst *var = findAllocaByName(function, varName);
        if (!var)
        {
            llvm::Argument *arg = findArgByName(function, varName);
            if (!arg)
            {
                throw LLVMException(util::format("LLVM::getOrPromoteToAlloca. Variable {} not found", varName));
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

    llvm::Value *LLVM::createConstValue(std::shared_ptr<hlir::Type> hlirType, std::shared_ptr<hlir::Value> value)
    {
        llvm::Value *callArg = std::visit([this, hlirType](auto &&argValue) -> llvm::Value *
                                          {
            using T = std::decay_t<decltype(argValue)>;
            if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>) {
                throw LLVMException("LLVM::createConstValue. Function type arguments not yet implemented.");
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>) {
                
                
                if (argValue->getVarName().empty()) {
                    throw std::invalid_argument("Variable name is empty");
                }

                
                llvm::AllocaInst *allocaVar = getOrPromoteToAlloca(argValue->getVarName(), builder.GetInsertBlock()->getParent());
                
                llvm::Type *type = allocaVar->getAllocatedType();
                if (type == nullptr) {
                    throw std::runtime_error("Failed to retrieve allocated type");
                }


                llvm::Value *loadedVar = builder.CreateLoad(allocaVar->getAllocatedType(), allocaVar, util::format("load_{}", argValue->getVarName()));

                return loadedVar;
            }
            else if constexpr (std::is_same_v<T, std::string>) {
                
                auto argType = hlirType->getType();
                
                llvm::Type *type = mapType(argType);
                if (!type) {
                    throw LLVMException("LLVM::createConstValue. Unknown type for argument.");
                }

                if (argType == tokenMap::TYPE_INT)
                {
                    return llvm::ConstantInt::get(type, std::stoi(argValue), true);
                }
                else if (argType == tokenMap::TYPE_FLOAT)
                {
                    float floatVal = std::stof(argValue);
                    return llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(floatVal));
                }
                else if (argType == tokenMap::TYPE_DOUBLE)
                {
                    double doubleVal = std::stod(argValue);
                    return llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(doubleVal));
                }
                else if (argType == tokenMap::TYPE_CHAR)
                {
                    if (argValue.empty()) {
                        throw LLVMException("LLVM::createConstValue. Empty string for char type.");
                    }
                    return llvm::ConstantInt::get(type, static_cast<int>(argValue[0]), true);
                }
                else if (argType == tokenMap::TYPE_BOOLEAN)
                {
                    bool boolVal = (argValue == "true");
                    return llvm::ConstantInt::get(type, boolVal ? 1 : 0, false);
                }
                else
                {
                    throw LLVMException("LLVM::createConstValue. Unsupported argument type.");
                }

            }
            else {
                throw LLVMException("LLVM::createConstValue. Unsupported type in value.");
            } }, value->getValue());

        return callArg;
    }

    llvm::AllocaInst *LLVM::allocaVariable(std::shared_ptr<hlir::Variable> variable)
    {
        if (!variable)
        {
            throw LLVMException("allocaVariable: variable is null");
        }
        if (!variable->getVarType())
        {
            throw LLVMException("allocaVariable: variable->getVarType() is null");
        }

        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("allocaVariable: currentFunction is null");
        }

        llvm::BasicBlock &entryBlock = currentFunction->getEntryBlock();
        llvm::IRBuilder<> tmpBuilder(&entryBlock, entryBlock.begin());

        llvm::Type *llvmType = mapType(variable->getVarType()->getType());
        llvm::AllocaInst *allocaVariable = tmpBuilder.CreateAlloca(llvmType, nullptr, variable->getVarName());
        return allocaVariable;
    }

    llvm::Value *LLVM::numberCasting(
        std::shared_ptr<hlir::Variable> variable,
        std::shared_ptr<hlir::Type> type,
        llvm::Function *currentFunction)
    {
        // Initial check of input pointers
        if (!variable)
        {
            throw LLVMException("LLVM::numberCasting: 'variable' is a null pointer.");
        }

        if (!type)
        {
            throw LLVMException("LLVM::numberCasting: 'type' is a null pointer.");
        }

        if (!currentFunction)
        {
            throw LLVMException("LLVM::numberCasting: 'currentFunction' is a null pointer.");
        }

        // Check if the variable name is not empty
        std::string varName = variable->getVarName();
        if (varName.empty())
        {
            throw LLVMException("LLVM::numberCasting: 'variable->getVarName()' is empty.");
        }

        // Find the corresponding AllocaInst for the variable
        auto castVar = getOrPromoteToAlloca(varName, currentFunction);
        if (!castVar)
        {
            throw LLVMException(util::format("LLVM::numberCasting: AllocaInst for variable '{}' was not found.", varName));
        }

        // Get the allocated type and verify it's valid
        llvm::Type *allocatedType = castVar->getAllocatedType();
        if (!allocatedType)
        {
            throw LLVMException(util::format("LLVM::numberCasting: 'getAllocatedType()' returned a null pointer for variable '{}'.", varName));
        }

        // Create the load instruction and verify it was successful
        llvm::LoadInst *loadedVar = builder.CreateLoad(allocatedType, castVar, util::format("load_{}", varName));
        if (!loadedVar)
        {
            throw LLVMException(util::format("LLVM::numberCasting: Failed to create LoadInst for variable '{}'.", varName));
        }

        // Map the desired type and verify it was mapped correctly
        llvm::Type *desiredType = mapType(type->getType());
        if (!desiredType)
        {
            throw LLVMException(util::format("LLVM::numberCasting: 'mapType' returned a null pointer for the type of variable '{}'.", varName));
        }

        llvm::Value *value = nullptr;

        // Check if the variable type is not null before accessing
        auto varType = variable->getVarType();
        if (!varType)
        {
            throw LLVMException(util::format("LLVM::numberCasting: 'variable->getVarType()' is a null pointer for variable '{}'.", varName));
        }

        int varTypeInt = varType->getType();
        int desiredTypeInt = type->getType();

        // Perform casting based on types
        if (varTypeInt == tokenMap::TYPE_FLOAT && desiredTypeInt == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (varTypeInt == tokenMap::TYPE_FLOAT && desiredTypeInt == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateFPExt(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (varTypeInt == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (varTypeInt == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (varTypeInt == tokenMap::TYPE_DOUBLE && desiredTypeInt == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateFPTrunc(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (varTypeInt == tokenMap::TYPE_DOUBLE && desiredTypeInt == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else
        {
            throw LLVMException("LLVM::numberCasting: Type conversion not defined.");
        }

        // Verify if the cast instruction was created correctly
        if (!value)
        {
            throw LLVMException(util::format("LLVM::numberCasting: Failed to create the cast instruction for variable '{}'.", varName));
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

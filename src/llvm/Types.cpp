#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{

    void LLVM::assignVariable(const std::shared_ptr<hlir::Value> &value, llvm::AllocaInst *allocaVariable,
                              llvm::Function *function)
    {

        std::visit(
                [this, function, allocaVariable](auto &&value)
                {
                    using T = std::decay_t<decltype(value)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                    {
                        if (value)
                        {
                            auto type = mapType(value->getVarType()->getType());
                            auto anotherAlloca = this->findAllocaByName(function, value->getVarName());
                            llvm::LoadInst *loadInst = builder.CreateLoad(type, anotherAlloca,
                                                                          util::format("load_{}", value->getVarName()));
                            builder.CreateStore(loadInst, allocaVariable);
                        }
                    }
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {
                        if (value)
                        {
                            // auto type = mapType(value->getVarType()->getType());
                            // auto anotherAlloca = this->findAllocaByName(function, value->getVarName());
                            // llvm::LoadInst *loadInst = builder.CreateLoad(
                            //         type, anotherAlloca, util::format("load_{}", value->getVarName()));
                            // builder.CreateStore(loadInst, allocaVariable);
                        }
                    }
                },
                value->getValue());
    }

    void LLVM::assignValue(const std::shared_ptr<hlir::Variable> &variable, const std::shared_ptr<hlir::Value> &value,
                           llvm::AllocaInst *allocaVariable)
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
                const int num = std::stoi(value->getText());

                // Create a 32-bit integer constant
                llvm::Constant *constInt = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), num,
                                                                  true // Signed
                );
                valueToStore = constInt;
                break;
            }

            case tokenMap::TYPE_FLOAT:
            {
                // Convert string to float
                const float num = std::stof(value->getText());
                const llvm::APFloat apFloatValue(num);
                llvm::Constant *constFP = llvm::ConstantFP::get(llvmContext, apFloatValue);
                valueToStore = constFP;
                break;
            }

            case tokenMap::TYPE_DOUBLE:
            {
                // Convert string to double
                const double num = std::stod(value->getText());
                const llvm::APFloat apFloatValue(num);
                llvm::Constant *constFP = llvm::ConstantFP::get(llvmContext, apFloatValue);
                valueToStore = constFP;
                break;
            }

            case tokenMap::TYPE_BOOLEAN:
            {
                const bool boolValue = (value->getText() == "true");
                llvm::Constant *constBool =
                        llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvmContext), boolValue, false);
                valueToStore = constBool;
                break;
            }

            case tokenMap::TYPE_STRING:
            {
                valueToStore =
                        llvm::ConstantDataArray::getString(llvmContext, normalizeUserString(value->getText()), true);
                break;
            }

            default:
            {
                throw iron::LLVMException(util::format("Unsupported type for number literal: {}", value->getText()));
            }
        }


        if (variable->getVarType()->getType() == tokenMap::TYPE_STRING)
        {
            builder.CreateStore(valueToStore, allocaVariable);
        }
        else
        {
            if (valueToStore->getType() != allocaVariable->getAllocatedType())
            {
                throw iron::LLVMException(util::format("LLVM::assignValue: Type mismatch", ""));
            }
            builder.CreateStore(valueToStore, allocaVariable);
        }
    }

    void LLVM::generateTerminator(llvm::Type *functionReturnType)
    {
        // Caso float
        if (functionReturnType->isFloatTy())
        {
            builder.CreateRet(llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0f)));
        }
        // Caso double
        else if (functionReturnType->isDoubleTy())
        {
            builder.CreateRet(llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0)));
        }
        // Caso boolean (i1)
        else if (functionReturnType->isIntegerTy(1))
        {
            builder.CreateRet(llvm::ConstantInt::get(functionReturnType, 0, /*isSigned=*/false));
        }
        // Caso char (i8)
        else if (functionReturnType->isIntegerTy(8))
        {
            builder.CreateRet(llvm::ConstantInt::get(functionReturnType, 0, /*isSigned=*/false));
        }
        // Caso int (i32) - se quiser diferenciar int32 de outros ints
        else if (functionReturnType->isIntegerTy(32))
        {
            builder.CreateRet(llvm::ConstantInt::get(functionReturnType, 0));
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
    llvm::Type *LLVM::mapType(const int type) const
    {
        if (type == tokenMap::TYPE_INT)
        {
            return llvm::Type::getInt32Ty(llvmContext);
        }
        if (type == tokenMap::PTR_TYPE_INT)
        {
            return llvm::PointerType::get(llvm::Type::getInt32Ty(llvmContext), 0);
        }
        if (type == tokenMap::TYPE_FLOAT)
        {
            return llvm::Type::getFloatTy(llvmContext);
        }
        if (type == tokenMap::PTR_TYPE_FLOAT)
        {
            return llvm::PointerType::get(llvm::Type::getFloatTy(llvmContext), 0);
        }
        if (type == tokenMap::TYPE_DOUBLE)
        {
            return llvm::Type::getDoubleTy(llvmContext);
        }
        if (type == tokenMap::PTR_TYPE_DOUBLE)
        {
            return llvm::PointerType::get(llvm::Type::getDoubleTy(llvmContext), 0);
        }
        if (type == tokenMap::TYPE_CHAR)
        {
            return llvm::Type::getInt8Ty(llvmContext);
        }
        if (type == tokenMap::PTR_TYPE_CHAR)
        {
            return llvm::PointerType::get(llvm::Type::getInt8Ty(llvmContext), 0);
        }
        if (type == tokenMap::TYPE_BOOLEAN)
        {
            return llvm::Type::getInt1Ty(llvmContext);
        }
        if (type == tokenMap::PTR_TYPE_BOOLEAN)
        {
            return llvm::PointerType::get(llvm::Type::getInt1Ty(llvmContext), 0);
        }
        if (type == tokenMap::TYPE_STRING)
        {
            return llvm::PointerType::get(llvm::Type::getInt8Ty(llvmContext), 0);
        }
        if (type == tokenMap::VOID)
        {
            return llvm::Type::getVoidTy(llvmContext);
        }
        // Adicione outros tipos conforme necessário
        throw LLVMException(util::format("Unknown data type: {}", tokenMap::getTokenText(type)));
    }

    llvm::Argument *LLVM::findArgByName(llvm::Function *function, const std::string &argName)
    {
        if (!function)
        {
            throw LLVMException(util::format("{} Function not found", "LLVM::findArgByName"));
        }

        for (auto &arg: function->args())
        {
            if (arg.getName().str() == argName)
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
        const auto insertPoint = entryBB.getFirstInsertionPt();
        llvm::IRBuilder<> tempBuilder(&entryBB, insertPoint);

        llvm::AllocaInst *argAlloca = tempBuilder.CreateAlloca(arg->getType(), nullptr, arg->getName() + "_alloca");
        builder.CreateStore(arg, argAlloca);

        return argAlloca;
    }

    // Função para buscar uma AllocaInst por nome
    llvm::AllocaInst *LLVM::findAllocaByName(llvm::Function *function, const std::string &varName)
    {
        for (auto &block: *function)
        {
            for (auto &inst: block)
            {
                if (const auto allocaInst = llvm::dyn_cast<llvm::AllocaInst>(&inst))
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

    llvm::Value *LLVM::createConstValue(const std::shared_ptr<hlir::Type> &hlirType,
                                        const std::shared_ptr<hlir::Value> &value)
    {

        llvm::Value *callArg = std::visit(
                [this, hlirType](auto &&argValue) -> llvm::Value *
                {
                    using T = std::decay_t<decltype(argValue)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {
                        throw LLVMException("LLVM::createConstValue. Function type arguments not yet implemented.");
                    }
                    else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                    {

                        if (argValue->getVarName().empty())
                        {
                            throw std::invalid_argument("Variable name is empty");
                        }


                        llvm::AllocaInst *allocaVar =
                                getOrPromoteToAlloca(argValue->getVarName(), builder.GetInsertBlock()->getParent());

                        if (const llvm::Type *type = allocaVar->getAllocatedType(); type == nullptr)
                        {
                            throw std::runtime_error("Failed to retrieve allocated type");
                        }


                        if (hlirType->getType() == tokenMap::TYPE_STRING)
                        {
                            llvm::ConstantInt *zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), 0);
                            return builder.CreateGEP(allocaVar->getAllocatedType(), allocaVar, {zero, zero}, "str_ptr");
                        }

                        llvm::Value *loadedVar = builder.CreateLoad(allocaVar->getAllocatedType(), allocaVar,
                                                                    util::format("load_{}", argValue->getVarName()));
                        return loadedVar;
                    }
                    else if constexpr (std::is_same_v<T, std::string>)
                    {

                        const auto argType = hlirType->getType();

                        llvm::Type *type = mapType(argType);
                        if (!type)
                        {
                            throw LLVMException("LLVM::createConstValue. Unknown type for argument.");
                        }

                        if (argType == tokenMap::TYPE_INT)
                        {
                            return llvm::ConstantInt::get(type, std::stoi(argValue), true);
                        }
                        if (argType == tokenMap::TYPE_FLOAT)
                        {
                            const float floatVal = std::stof(argValue);
                            return llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(floatVal));
                        }
                        if (argType == tokenMap::TYPE_DOUBLE)
                        {
                            const double doubleVal = std::stod(argValue);
                            return llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(doubleVal));
                        }
                        if (argType == tokenMap::TYPE_CHAR)
                        {
                            if (argValue.empty())
                            {
                                throw LLVMException("LLVM::createConstValue. Empty string for char type.");
                            }
                            return llvm::ConstantInt::get(type, static_cast<int>(argValue[0]), true);
                        }
                        if (argType == tokenMap::TYPE_BOOLEAN)
                        {
                            const bool boolVal = (argValue == "true");
                            return llvm::ConstantInt::get(type, boolVal ? 1 : 0, false);
                        }
                        // TODO: Aqui ajustar
                        // if (argType == tokenMap::TYPE_STRING)
                        // {
                        //
                        // }
                        else
                        {
                            throw LLVMException("LLVM::createConstValue. Unsupported argument type.");
                        }
                    }
                    else
                    {
                        throw LLVMException("LLVM::createConstValue. Unsupported type in value.");
                    }
                },
                value->getValue());

        return callArg;
    }

    llvm::AllocaInst *LLVM::allocaVariableStr(const std::shared_ptr<hlir::Variable> &variable, const std::string &value)
    {
        if (!variable)
        {
            throw LLVMException("allocaVariable: variable is null");
        }
        if (!variable->getVarType())
        {
            throw LLVMException("allocaVariable: variable->getVarType() is null");
        }
        if (value.empty())
        {
            throw LLVMException("allocaVariable: value is null");
        }

        const unsigned strSize = value.size() + 1;
        llvm::ArrayType *strArrType = llvm::ArrayType::get(llvm::Type::getInt8Ty(llvmContext), strSize);
        llvm::AllocaInst *localStr = builder.CreateAlloca(strArrType, nullptr, variable->getVarName());
        return localStr;
    }

    llvm::AllocaInst *LLVM::allocaVariableFuncPtr(const std::shared_ptr<hlir::Variable> &variable,
                                                  const std::shared_ptr<hlir::Function> &function)
    {
        if (!variable)
        {
            throw LLVMException("allocaVariableFuncPtr: variable is null");
        }
        if (!function)
        {
            throw LLVMException("allocaVariableFuncPtr: function is null");
        }

        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("allocaVariableFuncPtr: currentFunction is null");
        }

        llvm::BasicBlock &entryBlock = currentFunction->getEntryBlock();
        llvm::IRBuilder<> tmpBuilder(&entryBlock, entryBlock.begin());

        const llvm::Function *calledFunction = module->getFunction(function->getFunctionName());
        if (!calledFunction)
        {
            throw LLVMException("allocaVariableFuncPtr: calledFunction is null");
        }

        llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(calledFunction->getFunctionType());
        return builder.CreateAlloca(funcPtrType, nullptr, variable->getVarName());

    }

    llvm::AllocaInst *LLVM::allocaVariable(const std::shared_ptr<hlir::Variable> &variable)
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

    llvm::Value *LLVM::numberCasting(const std::shared_ptr<hlir::Variable> &variable,
                                     const std::shared_ptr<hlir::Type> &type, llvm::Function *currentFunction)
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
        const std::string varName = variable->getVarName();
        if (varName.empty())
        {
            throw LLVMException("LLVM::numberCasting: 'variable->getVarName()' is empty.");
        }

        // Find the corresponding AllocaInst for the variable
        const auto castVar = getOrPromoteToAlloca(varName, currentFunction);
        if (!castVar)
        {
            throw LLVMException(
                    util::format("LLVM::numberCasting: AllocaInst for variable '{}' was not found.", varName));
        }

        // Get the allocated type and verify it's valid
        llvm::Type *allocatedType = castVar->getAllocatedType();
        if (!allocatedType)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: 'getAllocatedType()' returned a null pointer for variable '{}'.", varName));
        }

        // Create the load instruction and verify it was successful
        llvm::LoadInst *loadedVar = builder.CreateLoad(allocatedType, castVar, util::format("load_{}", varName));
        if (!loadedVar)
        {
            throw LLVMException(
                    util::format("LLVM::numberCasting: Failed to create LoadInst for variable '{}'.", varName));
        }

        // Map the desired type and verify it was mapped correctly
        llvm::Type *desiredType = mapType(type->getType());
        if (!desiredType)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: 'mapType' returned a null pointer for the type of variable '{}'.", varName));
        }

        llvm::Value *value = nullptr;

        // Check if the variable type is not null before accessing
        const auto varType = variable->getVarType();
        if (!varType)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: 'variable->getVarType()' is a null pointer for variable '{}'.", varName));
        }

        const int variableType = varType->getType();


        // if (variableType == tokenMap::TYPE_BOOLEAN)
        // {
        //     printf("%u\n", tokenMap::getTokenText(variable->getVarType()->getType()).c_str());
        // }

        // Perform casting based on types
        if (const int desiredTypeInt = type->getType();
            variableType == tokenMap::TYPE_FLOAT && desiredTypeInt == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_FLOAT && desiredTypeInt == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateFPExt(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_BOOLEAN)
        {
            value = builder.CreateICmpNE(loadedVar, llvm::ConstantInt::get(loadedVar->getType(), 0),
                                         util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_DOUBLE && desiredTypeInt == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateFPTrunc(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_DOUBLE && desiredTypeInt == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        else if (variableType == tokenMap::TYPE_BOOLEAN &&
                 (desiredTypeInt == tokenMap::TYPE_FLOAT || desiredTypeInt == tokenMap::TYPE_DOUBLE))
        {
            // Converte bool para float/double: se true retorna 1.0, senão 0.0
            value = builder.CreateSelect(loadedVar, llvm::ConstantFP::get(desiredType, 1.0),
                                         llvm::ConstantFP::get(desiredType, 0.0), util::format("cast_{}", varName));
        }
        else if ((variableType == tokenMap::TYPE_FLOAT || variableType == tokenMap::TYPE_DOUBLE) &&
                 desiredTypeInt == tokenMap::TYPE_BOOLEAN)
        {
            // Converte float/double para bool: compara se o valor é diferente de 0.0
            value = builder.CreateFCmpONE(loadedVar, llvm::ConstantFP::get(loadedVar->getType(), 0.0),
                                          util::format("cast_{}", varName));
        }

        else
        {
            throw LLVMException("LLVM::numberCasting: Type conversion not defined.");
        }

        // Verify if the cast instruction was created correctly
        if (!value)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: Failed to create the cast instruction for variable '{}'.", varName));
        }

        return value;
    }

    std::string LLVM::normalizeUserString(const std::string &input)
    {
        std::string output;
        output.reserve(input.size());

        // Se a string começa e termina com aspas, remova-as
        size_t start = 0;
        size_t end = input.size();
        if (!input.empty() && input.front() == '\"' && input.back() == '\"')
        {
            start = 1;
            end = input.size() - 1;
        }

        // Processa a string caractere a caractere, interpretando sequências de escape comuns
        for (size_t i = start; i < end; ++i)
        {
            if (input[i] == '\\' && i + 1 < end)
            {
                char next = input[i + 1];
                switch (next)
                {
                    case 'n':
                        output.push_back('\n');
                        i++; // pula o próximo caractere
                        break;
                    case 't':
                        output.push_back('\t');
                        i++;
                        break;
                    case '\"':
                        output.push_back('\"');
                        i++;
                        break;
                    case '\\':
                        output.push_back('\\');
                        i++;
                        break;
                    // Você pode adicionar mais casos, se necessário.
                    default:
                        // Se não for uma sequência conhecida, apenas copia os dois caracteres
                        output.push_back(input[i]);
                        // output.push_back(input[i+1]); // opcional, dependendo do que você deseja
                        i++; // pula o próximo caractere
                        break;
                }
            }
            else
            {
                output.push_back(input[i]);
            }
        }

        return output;
    }

} // namespace iron

#include <iostream>

// Função para normalizar a string de entrada


// int main() {
//     // Exemplo 1: String com aspas delimitadoras e escapes literais
//     std::string test1 = "\"Resultado: %i\\n\"";
//     std::string normalized1 = normalizeUserString(test1);
//     std::cout << "Normalized 1:" << std::endl;
//     std::cout << normalized1 << std::endl;
//
//     // Exemplo 2: String sem aspas e já com nova linha real
//     std::string test2 = "Resultado: %i\n";
//     std::string normalized2 = normalizeUserString(test2);
//     std::cout << "Normalized 2:" << std::endl;
//     std::cout << normalized2 << std::endl;
//
//     return 0;
// }

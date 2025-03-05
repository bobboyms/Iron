#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    /**
     * @brief Assigns a value from another variable to the given allocation
     *
     * @param value Source value to assign
     * @param allocaVariable Destination allocation instruction
     * @param function Current function where the assignment takes place
     * @throws LLVMException if any required pointers are null
     */
    void LLVM::assignVariable(const std::shared_ptr<hlir::Value> &value, llvm::AllocaInst *allocaVariable,
                              llvm::Function *function)
    {
        if (!value)
        {
            throw LLVMException("assignVariable: value is null");
        }

        if (!allocaVariable)
        {
            throw LLVMException("assignVariable: allocaVariable is null");
        }

        if (!function)
        {
            throw LLVMException("assignVariable: function is null");
        }

        std::visit(
                [this, function, allocaVariable](auto &&value)
                {
                    using T = std::decay_t<decltype(value)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                    {
                        if (value)
                        {
                            auto type = mapType(value->getVarType()->getType());
                            auto anotherAlloca = this->findAllocaByName(function, value->getRealName());
                            llvm::LoadInst *loadInst = builder.CreateLoad(
                                    type, anotherAlloca, util::format("load_{}", value->getRealName()));
                            builder.CreateStore(loadInst, allocaVariable);
                        }
                    }
                    // Future support for function type
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {
                        if (value)
                        {
                            // TODO: Implement function value assignment
                        }
                    }
                },
                value->getValue());
    }

    /**
     * @brief Assigns a constant value to a variable allocation
     *
     * @param variable The variable receiving the value
     * @param value The value to assign
     * @param allocaVariable The allocation instruction for the variable
     * @throws LLVMException for null pointers, type mismatches, or unsupported types
     */
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

        if (!variable->getVarType())
        {
            throw iron::LLVMException("LLVM::assignValue: 'variable->getVarType()' is a null pointer.");
        }

        llvm::Value *valueToStore = nullptr;
        const int varType = variable->getVarType()->getType();

        try
        {
            // Handle different types of constants based on the variable type
            switch (varType)
            {
                case tokenMap::TYPE_INT:
                {
                    const int num = std::stoi(value->getText());
                    valueToStore = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), num, true);
                    break;
                }
                case tokenMap::TYPE_FLOAT:
                {
                    const float num = std::stof(value->getText());
                    valueToStore = llvm::ConstantFP::get(llvmContext, llvm::APFloat(num));
                    break;
                }
                case tokenMap::TYPE_DOUBLE:
                {
                    const double num = std::stod(value->getText());
                    valueToStore = llvm::ConstantFP::get(llvmContext, llvm::APFloat(num));
                    break;
                }
                case tokenMap::TYPE_BOOLEAN:
                {
                    const bool boolValue = (value->getText() == "true");
                    valueToStore = llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvmContext), boolValue, false);
                    break;
                }
                case tokenMap::TYPE_STRING:
                {
                    valueToStore = llvm::ConstantDataArray::getString(llvmContext,
                                                                      normalizeUserString(value->getText()), true);
                    break;
                }
                default:
                {
                    throw iron::LLVMException(util::format("Unsupported type for literal: {}", value->getText()));
                }
            }
        }
        catch (const std::exception &e)
        {
            throw iron::LLVMException(util::format("Error converting value '{}' to type {}: {}", value->getText(),
                                                   tokenMap::getTokenText(varType), e.what()));
        }

        // String types are handled differently
        if (varType == tokenMap::TYPE_STRING)
        {
            builder.CreateStore(valueToStore, allocaVariable);
        }
        else
        {
            // Verify type compatibility before storing
            if (valueToStore->getType() != allocaVariable->getAllocatedType())
            {
                throw iron::LLVMException(util::format("Type mismatch: expected {}, got {}",
                                                       allocaVariable->getAllocatedType()->getTypeID(),
                                                       valueToStore->getType()->getTypeID()));
            }
            builder.CreateStore(valueToStore, allocaVariable);
        }
    }

    /**
     * @brief Generates a default return value based on the function return type
     *
     * @param functionReturnType The LLVM type that represents the function's return type
     * @throws LLVMException if the type is not supported
     */
    void LLVM::generateTerminator(llvm::Type *functionReturnType)
    {
        if (!functionReturnType)
        {
            throw LLVMException("LLVM::generateTerminator: 'functionReturnType' is a null pointer.");
        }

        // Generate appropriate return instruction based on type
        if (functionReturnType->isFloatTy())
        {
            builder.CreateRet(llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0f)));
        }
        else if (functionReturnType->isDoubleTy())
        {
            builder.CreateRet(llvm::ConstantFP::get(llvmContext, llvm::APFloat(0.0)));
        }
        else if (functionReturnType->isIntegerTy(1)) // boolean
        {
            builder.CreateRet(llvm::ConstantInt::get(functionReturnType, 0, false));
        }
        else if (functionReturnType->isIntegerTy(8)) // char
        {
            builder.CreateRet(llvm::ConstantInt::get(functionReturnType, 0, false));
        }
        else if (functionReturnType->isIntegerTy(32)) // int32
        {
            builder.CreateRet(llvm::ConstantInt::get(functionReturnType, 0));
        }
        else if (functionReturnType->isVoidTy())
        {
            builder.CreateRetVoid();
        }
        else
        {
            throw LLVMException(
                    util::format("LLVM::generateTerminator: Type not handled: {}", functionReturnType->getTypeID()));
        }
    }

    /**
     * @brief Maps Iron language types to LLVM types
     *
     * @param type The Iron type token
     * @return llvm::Type* The corresponding LLVM type
     * @throws LLVMException if the type is unknown
     */
    llvm::Type *LLVM::mapType(const int type) const
    {
        switch (type)
        {
            case tokenMap::TYPE_INT:
                return llvm::Type::getInt32Ty(llvmContext);
            case tokenMap::PTR_TYPE_INT:
                return llvm::PointerType::get(llvm::Type::getInt32Ty(llvmContext), 0);
            case tokenMap::TYPE_FLOAT:
                return llvm::Type::getFloatTy(llvmContext);
            case tokenMap::PTR_TYPE_FLOAT:
                return llvm::PointerType::get(llvm::Type::getFloatTy(llvmContext), 0);
            case tokenMap::TYPE_DOUBLE:
                return llvm::Type::getDoubleTy(llvmContext);
            case tokenMap::PTR_TYPE_DOUBLE:
                return llvm::PointerType::get(llvm::Type::getDoubleTy(llvmContext), 0);
            case tokenMap::TYPE_CHAR:
                return llvm::Type::getInt8Ty(llvmContext);
            case tokenMap::PTR_TYPE_CHAR:
                return llvm::PointerType::get(llvm::Type::getInt8Ty(llvmContext), 0);
            case tokenMap::TYPE_BOOLEAN:
                return llvm::Type::getInt1Ty(llvmContext);
            case tokenMap::PTR_TYPE_BOOLEAN:
                return llvm::PointerType::get(llvm::Type::getInt1Ty(llvmContext), 0);
            case tokenMap::TYPE_STRING:
                return llvm::PointerType::get(llvm::Type::getInt8Ty(llvmContext), 0);
            case tokenMap::VOID:
                return llvm::Type::getVoidTy(llvmContext);
            default:
                throw LLVMException(util::format("Unknown data type: {}", tokenMap::getTokenText(type)));
        }
    }

    /**
     * @brief Finds a function argument by name
     *
     * @param function The function to search in
     * @param argName The name of the argument to find
     * @return llvm::Argument* Pointer to the argument or nullptr if not found
     * @throws LLVMException if function is null
     */
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

    /**
     * @brief Finds an allocation instruction or promotes an argument to an allocation
     *
     * @param varName The name of the variable to find
     * @param function The function to search in
     * @return llvm::AllocaInst* The allocation instruction
     * @throws LLVMException if variable not found
     */
    llvm::AllocaInst *LLVM::getOrPromoteToAlloca(const std::string &varName, llvm::Function *function)
    {
        if (!function)
        {
            throw LLVMException("LLVM::getOrPromoteToAlloca: function is null");
        }

        llvm::AllocaInst *var = findAllocaByName(function, varName);
        if (!var)
        {
            llvm::Argument *arg = findArgByName(function, varName);
            if (!arg)
            {
                throw LLVMException(util::format("LLVM::getOrPromoteToAlloca: Variable {} not found", varName));
            }

            var = promoteArgumentToAlloca(function, arg);
        }
        return var;
    }

    /**
     * @brief Promotes a function argument to an allocation in the entry block
     *
     * @param function The function containing the argument
     * @param arg The argument to promote
     * @return llvm::AllocaInst* The allocation instruction
     * @throws LLVMException if arg is null
     */
    llvm::AllocaInst *LLVM::promoteArgumentToAlloca(llvm::Function *function, llvm::Argument *arg)
    {
        if (!function)
        {
            throw LLVMException("LLVM::promoteArgumentToAlloca: function is null");
        }

        if (!arg)
        {
            throw LLVMException("promoteArgumentToAlloca: Argument is null");
        }

        llvm::BasicBlock &entryBB = function->getEntryBlock();
        const auto insertPoint = entryBB.getFirstInsertionPt();
        llvm::IRBuilder<> tempBuilder(&entryBB, insertPoint);

        llvm::AllocaInst *argAlloca = tempBuilder.CreateAlloca(arg->getType(), nullptr, arg->getName() + "_alloca");
        builder.CreateStore(arg, argAlloca);

        return argAlloca;
    }

    /**
     * @brief Finds an allocation instruction by name in a function
     *
     * @param function The function to search in
     * @param varName The name of the variable to find
     * @return llvm::AllocaInst* The allocation instruction or nullptr if not found
     */
    llvm::AllocaInst *LLVM::findAllocaByName(llvm::Function *function, const std::string &varName)
    {
        if (!function)
        {
            return nullptr;
        }

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

    /**
     * @brief Creates a constant value based on type information
     *
     * @param hlirType The HLIR type information
     * @param value The value to create
     * @return llvm::Value* The LLVM constant value
     * @throws Various exceptions for type errors and conversion errors
     */
    llvm::Value *LLVM::createConstValue(const std::shared_ptr<hlir::Type> &hlirType,
                                        const std::shared_ptr<hlir::Value> &value)
    {
        if (!hlirType)
        {
            throw LLVMException("LLVM::createConstValue: hlirType is null");
        }

        if (!value)
        {
            throw LLVMException("LLVM::createConstValue: value is null");
        }

        llvm::Value *callArg = std::visit(
                [this, hlirType](auto &&argValue) -> llvm::Value *
                {
                    using T = std::decay_t<decltype(argValue)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {
                        if (!argValue)
                        {
                            throw LLVMException("LLVM::createConstValue: function value is null");
                        }
                        return module->getFunction(argValue->getFunctionName());
                    }
                    else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                    {
                        if (!argValue)
                        {
                            throw LLVMException("LLVM::createConstValue: variable value is null");
                        }

                        if (argValue->getRealName().empty())
                        {
                            throw std::invalid_argument("Variable name is empty");
                        }

                        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
                        if (!currentFunction)
                        {
                            throw LLVMException("LLVM::createConstValue: Unable to get current function");
                        }

                        llvm::AllocaInst *allocaVar = getOrPromoteToAlloca(argValue->getRealName(), currentFunction);
                        if (!allocaVar)
                        {
                            throw LLVMException(util::format(
                                    "LLVM::createConstValue: Unable to find or create allocation for variable '{}'",
                                    argValue->getRealName()));
                        }

                        if (const llvm::Type *type = allocaVar->getAllocatedType(); type == nullptr)
                        {
                            throw std::runtime_error("Failed to retrieve allocated type");
                        }

                        // Handle string type differently
                        if (hlirType->getType() == tokenMap::TYPE_STRING)
                        {
                            llvm::ConstantInt *zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), 0);
                            return builder.CreateGEP(allocaVar->getAllocatedType(), allocaVar, {zero, zero}, "str_ptr");
                        }

                        // Load value from allocation
                        llvm::Value *loadedVar = builder.CreateLoad(allocaVar->getAllocatedType(), allocaVar,
                                                                    util::format("load_{}", argValue->getRealName()));
                        return loadedVar;
                    }
                    else if constexpr (std::is_same_v<T, std::string>)
                    {
                        // Create constants based on the string value and type
                        const auto argType = hlirType->getType();
                        llvm::Type *type = mapType(argType);

                        if (!type)
                        {
                            throw LLVMException("LLVM::createConstValue: Unknown type for argument.");
                        }

                        // Handle different constant types
                        try
                        {
                            switch (argType)
                            {
                                case tokenMap::TYPE_INT:
                                    return llvm::ConstantInt::get(type, std::stoi(argValue), true);
                                case tokenMap::TYPE_FLOAT:
                                    return llvm::ConstantFP::get(builder.getContext(),
                                                                 llvm::APFloat(std::stof(argValue)));
                                case tokenMap::TYPE_DOUBLE:
                                    return llvm::ConstantFP::get(builder.getContext(),
                                                                 llvm::APFloat(std::stod(argValue)));
                                case tokenMap::TYPE_CHAR:
                                    if (argValue.empty())
                                    {
                                        throw LLVMException("LLVM::createConstValue: Empty string for char type.");
                                    }
                                    return llvm::ConstantInt::get(type, static_cast<int>(argValue[0]), true);
                                case tokenMap::TYPE_BOOLEAN:
                                    return llvm::ConstantInt::get(type, (argValue == "true") ? 1 : 0, false);
                                case tokenMap::TYPE_STRING:
                                    // TODO: Implement proper string handling
                                    throw LLVMException(
                                            "LLVM::createConstValue: String type not fully implemented yet.");
                                default:
                                    throw LLVMException(
                                            util::format("LLVM::createConstValue: Unsupported argument type: {}",
                                                         tokenMap::getTokenText(argType)));
                            }
                        }
                        catch (const std::exception &e)
                        {
                            throw LLVMException(
                                    util::format("LLVM::createConstValue: Error converting '{}' to type {}: {}",
                                                 argValue, tokenMap::getTokenText(argType), e.what()));
                        }
                    }
                    else
                    {
                        throw LLVMException(
                                util::format("LLVM::createConstValue: Unsupported type variant: {}", typeid(T).name()));
                    }
                },
                value->getValue());

        return callArg;
    }

    /**
     * @brief Allocates a string variable
     *
     * @param variable The variable to allocate
     * @param value The string value
     * @return llvm::AllocaInst* The allocation instruction
     * @throws LLVMException for various error conditions
     */
    llvm::AllocaInst *LLVM::allocaVariableStr(const std::shared_ptr<hlir::Variable> &variable, const std::string &value)
    {
        if (!variable)
        {
            throw LLVMException("allocaVariableStr: variable is null");
        }
        if (!variable->getVarType())
        {
            throw LLVMException("allocaVariableStr: variable->getVarType() is null");
        }
        if (value.empty())
        {
            throw LLVMException("allocaVariableStr: value is empty");
        }

        const unsigned strSize = value.size() + 1; // +1 for null terminator
        llvm::ArrayType *strArrType = llvm::ArrayType::get(llvm::Type::getInt8Ty(llvmContext), strSize);
        llvm::AllocaInst *localStr = builder.CreateAlloca(strArrType, nullptr, variable->getRealName());
        return localStr;
    }

    /**
     * @brief Allocates a function pointer variable
     *
     * @param variable The variable to allocate
     * @param function The function to point to
     * @return llvm::AllocaInst* The allocation instruction
     * @throws LLVMException for various error conditions
     */
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
            throw LLVMException(util::format("allocaVariableFuncPtr: function '{}' not found in module",
                                             function->getFunctionName()));
        }

        llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(calledFunction->getFunctionType());
        return builder.CreateAlloca(funcPtrType, nullptr, variable->getRealName());
    }

    /**
     * @brief Allocates a variable in the entry block of the current function
     *
     * @param variable The variable to allocate
     * @return llvm::AllocaInst* The allocation instruction
     * @throws LLVMException for various error conditions
     */
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
        llvm::AllocaInst *allocaVar = tmpBuilder.CreateAlloca(llvmType, nullptr, variable->getRealName());
        return allocaVar;
    }

    /**
     * @brief Creates a type cast operation
     *
     * This method handles various type conversions between Iron language types.
     *
     * @param variable The variable to cast
     * @param type The target type
     * @param currentFunction The current function context
     * @return llvm::Value* The result of the cast operation
     * @throws LLVMException for various error conditions
     */
    llvm::Value *LLVM::numberCasting(const std::shared_ptr<hlir::Variable> &variable,
                                     const std::shared_ptr<hlir::Type> &type, llvm::Function *currentFunction)
    {
        // Check inputs
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

        // Get variable name
        const std::string varName = variable->getRealName();
        if (varName.empty())
        {
            throw LLVMException("LLVM::numberCasting: 'variable->getVarName()' is empty.");
        }

        // Get variable allocation
        const auto castVar = getOrPromoteToAlloca(varName, currentFunction);
        if (!castVar)
        {
            throw LLVMException(
                    util::format("LLVM::numberCasting: AllocaInst for variable '{}' was not found.", varName));
        }

        // Get variable type
        llvm::Type *allocatedType = castVar->getAllocatedType();
        if (!allocatedType)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: 'getAllocatedType()' returned a null pointer for variable '{}'.", varName));
        }

        // Load variable value
        llvm::LoadInst *loadedVar = builder.CreateLoad(allocatedType, castVar, util::format("load_{}", varName));
        if (!loadedVar)
        {
            throw LLVMException(
                    util::format("LLVM::numberCasting: Failed to create LoadInst for variable '{}'.", varName));
        }

        // Get target type
        llvm::Type *desiredType = mapType(type->getType());
        if (!desiredType)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: 'mapType' returned a null pointer for the type of variable '{}'.", varName));
        }

        // Check source type
        const auto varType = variable->getVarType();
        if (!varType)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: 'variable->getVarType()' is a null pointer for variable '{}'.", varName));
        }

        const int variableType = varType->getType();
        const int desiredTypeInt = type->getType();

        // Perform appropriate type cast based on source and target types
        llvm::Value *value = nullptr;

        // Float -> Int
        if (variableType == tokenMap::TYPE_FLOAT && desiredTypeInt == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        // Float -> Double
        else if (variableType == tokenMap::TYPE_FLOAT && desiredTypeInt == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateFPExt(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        // Int -> Float
        else if (variableType == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        // Int -> Double
        else if (variableType == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        // Int -> Boolean
        else if (variableType == tokenMap::TYPE_INT && desiredTypeInt == tokenMap::TYPE_BOOLEAN)
        {
            value = builder.CreateICmpNE(loadedVar, llvm::ConstantInt::get(loadedVar->getType(), 0),
                                         util::format("cast_{}", varName));
        }
        // Double -> Float
        else if (variableType == tokenMap::TYPE_DOUBLE && desiredTypeInt == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateFPTrunc(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        // Double -> Int
        else if (variableType == tokenMap::TYPE_DOUBLE && desiredTypeInt == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", varName));
        }
        // Boolean -> Float/Double
        else if (variableType == tokenMap::TYPE_BOOLEAN &&
                 (desiredTypeInt == tokenMap::TYPE_FLOAT || desiredTypeInt == tokenMap::TYPE_DOUBLE))
        {
            value = builder.CreateSelect(loadedVar, llvm::ConstantFP::get(desiredType, 1.0),
                                         llvm::ConstantFP::get(desiredType, 0.0), util::format("cast_{}", varName));
        }
        // Float/Double -> Boolean
        else if ((variableType == tokenMap::TYPE_FLOAT || variableType == tokenMap::TYPE_DOUBLE) &&
                 desiredTypeInt == tokenMap::TYPE_BOOLEAN)
        {
            value = builder.CreateFCmpONE(loadedVar, llvm::ConstantFP::get(loadedVar->getType(), 0.0),
                                          util::format("cast_{}", varName));
        }
        else
        {
            throw LLVMException(util::format("LLVM::numberCasting: Type conversion not defined: {} to {}",
                                             tokenMap::getTokenText(variableType),
                                             tokenMap::getTokenText(desiredTypeInt)));
        }

        // Verify cast result
        if (!value)
        {
            throw LLVMException(util::format(
                    "LLVM::numberCasting: Failed to create the cast instruction for variable '{}'.", varName));
        }

        return value;
    }

    /**
     * @brief Normalizes a string by processing escape sequences
     *
     * @param input The input string to normalize
     * @return std::string The normalized string
     */
    std::string LLVM::normalizeUserString(const std::string &input)
    {
        std::string output;
        output.reserve(input.size());

        // Remove surrounding quotes if present
        size_t start = 0;
        size_t end = input.size();
        if (!input.empty() && input.front() == '\"' && input.back() == '\"')
        {
            start = 1;
            end = input.size() - 1;
        }

        // Process escape sequences
        for (size_t i = start; i < end; ++i)
        {
            if (input[i] == '\\' && i + 1 < end)
            {
                char next = input[i + 1];
                switch (next)
                {
                    case 'n': // Newline
                        output.push_back('\n');
                        i++;
                        break;
                    case 't': // Tab
                        output.push_back('\t');
                        i++;
                        break;
                    case '\"': // Quote
                        output.push_back('\"');
                        i++;
                        break;
                    case '\\': // Backslash
                        output.push_back('\\');
                        i++;
                        break;
                    case 'r': // Carriage return
                        output.push_back('\r');
                        i++;
                        break;
                    case '0': // Null character
                        output.push_back('\0');
                        i++;
                        break;
                    default: // Unknown escape sequence
                        output.push_back(input[i]);
                        i++;
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

    /**
     * @brief Retrieves a declared struct by its name.
     *
     * This method searches the LLVM context for a struct type that matches the provided name.
     * If the struct type is not found, an LLVMException is thrown.
     *
     * @param name The name of the struct to retrieve.
     * @return llvm::StructType* Pointer to the retrieved struct type.
     * @throws LLVMException If the struct with the specified name is not found in the context.
     */
    llvm::StructType *LLVM::getStructByName(const std::string &name) const
    {
        const auto structType = llvm::StructType::getTypeByName(llvmContext, util::format("struct.{}", name));
        if (!structType)
        {
            throw LLVMException(util::format("LLVM::getStructByName: Struct type '{}' not found.", name));
        }
        return structType;
    }

    /**
 * @brief Extracts a Variable object from a Value container
 *
 * This method extracts a Variable from a Value object's variant storage.
 * It performs thorough validation to ensure the variable exists and is valid.
 *
 * @param value The value container that should hold a variable
 * @return std::shared_ptr<hlir::Variable> The extracted variable
 * @throws LLVMException if value is null, contains no variable, or contains a null variable
 */
std::shared_ptr<hlir::Variable> LLVM::getVariableFromValue(const std::shared_ptr<hlir::Value> &value) const
{
    llvm_utils::checkNotNull(value, "value", "getVariableFromValue");

    std::shared_ptr<hlir::Variable> variable;
    const auto &valueData = value->getValue();

    std::visit(
            [&variable](auto &&arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                {
                    variable = arg;
                    if (!variable)
                    {
                        throw LLVMException("getVariableFromValue: variable in variant is null");
                    }
                }
            },
            valueData);

    if (!variable)
    {
        throw LLVMException("getVariableFromValue: no variable found in value variant");
    }

    return variable;
}

   /**
     * @brief Initializes a struct with field values
     *
     * This method handles the initialization of a struct by assigning values to each field.
     * It supports both string and non-string field types.
     *
     * @param currentFunction The current function context
     * @param structInit The struct initialization data
     * @param variable The variable that will receive the struct
     * @throws LLVMException if struct allocation or field assignments fail
     */
    void LLVM::structInit(llvm::Function *currentFunction, const std::shared_ptr<hlir::StructInit> &structInit,
                          const std::shared_ptr<hlir::Variable> &variable)
    {
        llvm_utils::checkNotNull(currentFunction, "currentFunction", "structInit");
        llvm_utils::checkNotNull(structInit, "structInit", "structInit");
        llvm_utils::checkNotNull(variable, "variable", "structInit");
        
        const auto structName = structInit->getStruct()->getName();
        const auto structType = getStructByName(structName);
        const auto structAlloca = findAllocaByName(currentFunction, variable->getRealName());
        
        if (!structAlloca)
        {
            throw LLVMException(llvm_utils::formatError("structInit", 
                "Failed to find allocated variable for struct"));
        }

        uint index = 0;
        for (auto const &assign: structInit->getAssigns())
        {
            llvm_utils::checkNotNull(assign, "field assignment", "structInit");
            llvm_utils::checkNotNull(assign->getVariable(), "field variable", "structInit");
            llvm_utils::checkNotNull(assign->getVariable()->getVarType(), "field type", "structInit");
            
            const auto fieldName = assign->getVariable()->getRealName();
            const auto sourceVar = getVariableFromValue(assign->getValue());
            
            // Get the value from the source variable and store it directly in the struct field
            llvm::Value *sourceValue = loadVariable(sourceVar, currentFunction);
            llvm::Value *field = builder.CreateStructGEP(structType, structAlloca, index, fieldName);
            builder.CreateStore(sourceValue, field);

            index++;
        }
    }

} // namespace iron

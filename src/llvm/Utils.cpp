#include "../headers/Utils.h"
#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"

namespace iron
{
    /**
     * @brief Creates a load instruction for a variable
     *
     * This utility method handles finding a variable's allocation and creating
     * a load instruction for it. It ensures consistent handling of variables
     * across the codebase.
     *
     * @param variable The variable to load
     * @param function The function context
     * @return llvm::LoadInst* The load instruction
     * @throws LLVMException if the variable can't be found or loaded
     */
    llvm::LoadInst *LLVM::loadVariable(const std::shared_ptr<hlir::Variable> &variable, llvm::Function *function)
    {
        llvm_utils::checkNotNull(variable, "variable", "loadVariable");
        llvm_utils::checkNotNull(function, "function", "loadVariable");
        llvm_utils::checkNotNull(variable->getVarType(), "variable type", "loadVariable");

        const auto varName = variable->getRealName();
        if (varName.empty())
        {
            throw LLVMException(llvm_utils::formatError("loadVariable", "Variable name is empty"));
        }

        // Find the variable's allocation
        llvm::AllocaInst *alloca = getOrPromoteToAlloca(varName, function);
        if (!alloca)
        {
            throw LLVMException(
                    llvm_utils::formatError("loadVariable", util::format("Variable '{}' not found", varName)));
        }

        // Map the type and create the load instruction
        if (variable->getVarType()->getType() == tokenMap::STRUCT)
        {
            const auto loadType = getStructByName(variable->getVarType()->getTypeName());
            return builder.CreateLoad(loadType, alloca, util::format("load_{}", varName));
        }

        llvm::Type *loadType = mapType(variable->getVarType()->getType());
        return builder.CreateLoad(loadType, alloca, util::format("load_{}", varName));
    }

    /**
     * @brief Creates a struct field access and loads its value
     *
     * This utility method handles accessing and loading a field from a struct,
     * with proper error handling and type mapping.
     *
     * @param structVar Variable containing the struct
     * @param fieldName Name of the field to access
     * @param fieldIndex Index of the field in the struct
     * @param fieldType Type of the field
     * @param function Current function context
     * @return llvm::Value* The loaded field value
     * @throws LLVMException if the struct variable can't be found or accessed
     */
    llvm::Value *LLVM::loadStructField(const std::shared_ptr<hlir::Variable> &structVar, const std::string &fieldName,
                                       const unsigned fieldIndex, const int fieldType, llvm::Function *function)
    {
        llvm_utils::checkNotNull(structVar, "struct variable", "loadStructField");
        llvm_utils::checkNotNull(function, "function", "loadStructField");

        if (fieldName.empty())
        {
            throw LLVMException(llvm_utils::formatError("loadStructField", "Field name is empty"));
        }

        // Get the struct type and allocation
        // We'll use the variable's name as the struct name since Type doesn't have getTypeName()
        // Note: In Iron language, struct type names should match the struct variable's type text
        const auto structName = structVar->getVarType()->getText();
        const auto structType = getStructByName(structName);
        const auto structAlloca = findAllocaByName(function, structVar->getRealName());

        if (!structAlloca)
        {
            throw LLVMException(llvm_utils::formatError(
                    "loadStructField", util::format("Struct '{}' not found", structVar->getRealName())));
        }

        // Create the GEP instruction to access the field
        llvm::Value *field = builder.CreateStructGEP(structType, structAlloca, fieldIndex, fieldName);

        // Load the field based on its type
        llvm::Type *fieldLLVMType = mapType(fieldType);
        return builder.CreateLoad(fieldLLVMType, field, util::format("load_{}", fieldName));
    }

    /**
     * @brief Validates all operation inputs before execution
     *
     * This method centralizes the validation logic for binary operations,
     * ensuring consistent error handling and validation across all operations.
     *
     * @param operation The operation to validate
     * @param function The function context
     * @param funcName The name of the calling function for error messages
     * @throws LLVMException if any validation fails
     */
    void LLVM::validateOperationInputs(const std::shared_ptr<hlir::BinaryOperation> &operation,
                                       llvm::Function *function, const std::string &funcName)
    {
        llvm_utils::checkNotNull(operation, "operation", funcName);
        llvm_utils::checkNotNull(function, "function", funcName);

        // Validate left and right variables
        const auto leftVar = operation->getVarLeft();
        const auto rightVar = operation->getVarRight();

        llvm_utils::checkNotNull(leftVar, "left variable", funcName);
        llvm_utils::checkNotNull(rightVar, "right variable", funcName);

        // Validate types
        llvm_utils::checkNotNull(leftVar->getVarType(), "left variable type", funcName);
        llvm_utils::checkNotNull(rightVar->getVarType(), "right variable type", funcName);

        // Ensure both variables have names
        if (leftVar->getRealName().empty())
        {
            throw LLVMException(llvm_utils::formatError(funcName, "Left variable name is empty"));
        }

        if (rightVar->getRealName().empty())
        {
            throw LLVMException(llvm_utils::formatError(funcName, "Right variable name is empty"));
        }
    }
} // namespace iron

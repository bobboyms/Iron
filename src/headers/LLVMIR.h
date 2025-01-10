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
#include "ScopeManager.h"
#include "Visitors.h"
#include <memory>
#include <stack>

namespace iron
{

    /**
     * @class LLVMIR
     * @brief Generates LLVM Intermediate Representation (IR) from high-level IR code.
     *
     * The LLVMIR class is responsible for parsing high-level intermediate representation (HLIR) code,
     * managing scopes, handling type mappings, performing type casting, converting literals, and
     * generating mathematical operations and assignments in LLVM IR. It leverages LLVM's IRBuilder
     * to create and manipulate LLVM instructions and modules.
     */
    class LLVMIR
    {
    private:
        std::string hlirCode;                       /**< High-level intermediate representation code to be converted to LLVM IR. */
        std::unique_ptr<ScopeManager> scopeManager; /**< Manages variable scopes and symbol tables. */
        llvm::LLVMContext context;                  /**< LLVM context used for IR generation. */
        llvm::IRBuilder<> builder;                  /**< LLVM IRBuilder used to create LLVM instructions. */
        std::unique_ptr<llvm::Module> module;       /**< LLVM Module that holds the generated IR. */

        /**
         * @brief Visits and processes a list of statements in the HLIR context.
         *
         * Iterates through each expression in the statement list and delegates processing
         * to the appropriate handler based on the expression type.
         *
         * @param ctx Pointer to the StatementListContext containing the list of statements.
         *
         * @throws LLVMException If an unsupported expression is encountered.
         */
        void visitStatementList(HightLavelIRParser::StatementListContext *ctx);

        /**
         * @brief Visits and processes a single expression in the HLIR context.
         *
         * Determines the type of expression (e.g., number, mathematical operation, assignment, cast)
         * and invokes the corresponding handler to generate the appropriate LLVM IR.
         *
         * @param ctx Pointer to the ExprContext containing the expression details.
         *
         * @throws LLVMException If an unsupported expression is encountered.
         */
        void visitExpr(HightLavelIRParser::ExprContext *ctx);

        /**
         * @brief Visits and processes a cast expression in the HLIR context.
         *
         * Handles type casting between different variable types, ensuring that the correct LLVM
         * casting instructions are generated based on the source and target types.
         *
         * @param ctx Pointer to the CastContext containing the casting details.
         */
        void visitCast(HightLavelIRParser::CastContext *ctx);

        /**
         * @brief Visits and processes an operator expression in the HLIR context.
         *
         * Handles operations such as addition, subtraction, multiplication, and division by
         * generating the corresponding LLVM IR instructions.
         *
         * @param ctx Pointer to the OpContext containing the operator details.
         */
        void visitOp(HightLavelIRParser::OpContext *ctx);

        /**
         * @brief Visits and processes a mathematical operation in the HLIR context.
         *
         * Generates LLVM IR for mathematical operations by loading operand values, performing
         * the operation, and storing the result in the designated variable.
         *
         * @param ctx Pointer to the Math_opContext containing the mathematical operation details.
         */
        void visitMathOp(HightLavelIRParser::MathOpContext *ctx);

        /**
         * @brief Visits and processes a function declaration in the HLIR context.
         *
         * Handles the creation of LLVM function definitions, including setting up the function
         * signature, parameters, and entry block. It also manages the scope for function variables.
         *
         * @param ctx Pointer to the FunctionDeclarationContext containing the function declaration details.
         *
         * @throws LLVMException If the function return type is not defined or if the LLVM module is invalid.
         */
        void visitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext *ctx);

        /**
         * @brief Visits and processes a function signature in the HLIR context.
         *
         * Extracts the return type and arguments of a function, mapping them to LLVM types and names.
         *
         * @param ctx Pointer to the FunctionSignatureContext containing the function signature details.
         * @param functionReturnType Reference to an LLVM Type pointer to store the function's return type.
         * @param argTypes Reference to a vector to store the LLVM Types of the function's arguments.
         * @param argNames Reference to a vector to store the names of the function's arguments.
         */
        void visitFunctionSignature(
            HightLavelIRParser::FunctionSignatureContext *ctx,
            llvm::Type *&functionReturnType,
            std::vector<llvm::Type *> &argTypes,
            std::vector<std::string> &argNames);

        /**
         * @brief Visits and processes multiple function arguments in the HLIR context.
         *
         * Iterates through each function argument and maps them to their corresponding LLVM types and names.
         *
         * @param ctx Pointer to the FunctionArgsContext containing the list of function arguments.
         * @param argTypes Reference to a vector to store the LLVM Types of the arguments.
         * @param argNames Reference to a vector to store the names of the arguments.
         */
        void visitFunctionArgs(
            HightLavelIRParser::FunctionArgsContext *ctx,
            std::vector<llvm::Type *> &argTypes,
            std::vector<std::string> &argNames);

        /**
         * @brief Visits and processes a single function argument in the HLIR context.
         *
         * Maps a single function argument's type and name to LLVM types and names.
         *
         * @param ctx Pointer to the FunctionArgContext containing the argument details.
         * @param argTypes Reference to a vector to store the LLVM Type of the argument.
         * @param argNames Reference to a vector to store the name of the argument.
         */
        void visitFunctionArg(
            HightLavelIRParser::FunctionArgContext *ctx,
            std::vector<llvm::Type *> &argTypes,
            std::vector<std::string> &argNames);

        /**
         * @brief Visits and processes a function call in the HLIR context.
         *
         * Generates LLVM IR for calling a function, including setting up arguments and handling return values.
         *
         * @param ctx Pointer to the FunctionCallContext containing the function call details.
         */
        void visitFunctionCall(HightLavelIRParser::FunctionCallContext *ctx);

        /**
         * @brief Visits and processes multiple arguments in a function call within the HLIR context.
         *
         * Iterates through each function call argument and prepares them for the LLVM function call instruction.
         *
         * @param ctx Pointer to the FunctionCallArgsContext containing the list of call arguments.
         */
        void visitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext *ctx);

        /**
         * @brief Visits and processes a single argument in a function call within the HLIR context.
         *
         * Maps a single function call argument to its corresponding LLVM value.
         *
         * @param ctx Pointer to the FunctionCallArgContext containing the call argument details.
         */
        void visitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext *ctx);

        /**
         * @brief Visits and processes the return type of a function in the HLIR context.
         *
         * Determines the LLVM type of a function's return type based on the HLIR context.
         *
         * @param ctx Pointer to the FunctionReturnTypeContext containing the return type details.
         * @param functionReturnType Reference to an LLVM Type pointer to store the function's return type.
         */
        void visitFunctionReturnType(
            HightLavelIRParser::FunctionReturnTypeContext *ctx,
            llvm::Type *&functionReturnType);

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

        /**
         * @brief Performs type casting between numeric types.
         *
         * This function casts a variable from one numeric type to another as specified in the
         * expression context. It handles conversions between int, float, and double types.
         *
         * @param ctx Pointer to the expression context containing casting information.
         * @param allocaVariable The LLVM AllocaInst where the casted value will be stored.
         *
         * @throws LLVMException If the source variable is not found or if the type conversion is undefined.
         */
        void numberCasting(HightLavelIRParser::ExprContext *ctx, llvm::AllocaInst *allocaVariable);

        /**
         * @brief Converts a string literal to a numeric LLVM constant and stores it.
         *
         * This function takes a string representation of a literal value, converts it to the specified
         * numeric type (int, float, or double), creates an LLVM constant for it, and stores the value
         * in the provided AllocaInst.
         *
         * @param varType The type of the variable as defined in TokenMap (e.g., TYPE_INT, TYPE_FLOAT).
         * @param literalValue The string representation of the literal value to be converted.
         * @param allocaVariable The LLVM AllocaInst where the converted value will be stored.
         *
         * @throws LLVMException If the variable type is unsupported or if the literal value is invalid.
         */
        void literalToRealNumber(int varType, std::string literalValue, llvm::AllocaInst *allocaVariable);

        /**
         * @brief Generates LLVM IR for mathematical operations.
         *
         * This function handles the creation of LLVM instructions for basic mathematical operations
         * such as addition, subtraction, multiplication, and division. It supports both integer and
         * floating-point types.
         *
         * @param ctx Pointer to the expression context containing mathematical operation information.
         * @param allocaVariable The LLVM AllocaInst where the result of the operation will be stored.
         * @param varType The type of the variable resulting from the operation (e.g., TYPE_INT, TYPE_FLOAT).
         * @param varName The name of the variable to store the result.
         * @param llvmType The LLVM Type corresponding to varType.
         *
         * @throws LLVMException If either operand variable is not found or if the operation is unsupported.
         */
        void mathematicalOperations(HightLavelIRParser::ExprContext *ctx, llvm::AllocaInst *allocaVariable, int varType, std::string varName, llvm::Type *llvmType);

        /**
         * @brief Generates LLVM IR for variable assignments.
         *
         * This function handles the assignment of values from one variable to another within the LLVM IR.
         * It ensures that both the source and destination variables exist within the current scope.
         *
         * @param ctx Pointer to the expression context containing assignment information.
         * @param varName The name of the variable to which the value will be assigned.
         * @param llvmType The LLVM Type of the variable being assigned.
         *
         * @throws LLVMException If either the source or destination variable is not found.
         */
        void assignment(HightLavelIRParser::ExprContext *ctx, std::string varName, llvm::Type *llvmType);

        llvm::Argument *getArgumentByName(llvm::Function *func, const std::string &argName);

    public:
        /**
         * @brief Constructs a new LLVMIR object.
         *
         * Initializes the LLVMIR instance with the provided high-level IR code and scope manager.
         * Sets up the LLVM module with a default target triple.
         *
         * @param hlirCode The high-level intermediate representation code to be converted to LLVM IR.
         * @param scopeManager A unique pointer to the ScopeManager responsible for managing scopes and symbols.
         */
        LLVMIR(std::string hlirCode, std::unique_ptr<ScopeManager> scopeManager);

        /**
         * @brief Destructs the LLVMIR object.
         *
         * Cleans up any resources used by the LLVMIR instance. As most members are managed by smart pointers,
         * explicit cleanup is generally not required.
         */
        ~LLVMIR();

        /**
         * @brief Generates LLVM IR code from the high-level IR code.
         *
         * Parses the high-level IR code, processes function declarations and statements,
         * verifies the generated LLVM module, and returns the LLVM IR as a string.
         *
         * @return A string containing the generated LLVM Intermediate Representation.
         *
         * @throws LLVMException If the HLIR code is not initialized properly, if the LLVM module is invalid,
         *                        or if there are issues during code generation.
         */
        std::string generateCode();
    };

} // namespace iron

#endif // LLVMIR_H

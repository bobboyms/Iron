/**
 * @file LLVMIR.h
 * @brief Declaration of the LLVMIR class for generating LLVM Intermediate Representation (IR).
 */

#ifndef LLVMIR_H
#define LLVMIR_H

#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <stack>
#include "../headers/Hlir.h"
#include "Exceptions.h"
#include "Hlir.h"
#include "TokenMap.h"
#include "Utils.h"

namespace iron
{
    /**
     * @brief Utility functions for LLVM code generation
     * 
     * This namespace contains common utility functions used across the LLVM code generation.
     */
    namespace llvm_utils
    {
        /**
         * @brief Check if a pointer is null and throw a consistent exception if it is
         * 
         * @tparam T Type of the pointer to check
         * @param ptr The pointer to check for null
         * @param paramName The name of the parameter for error messaging
         * @param funcName The name of the calling function
         * @throws LLVMException if the pointer is null
         */
        template<typename T>
        void checkNotNull(const T& ptr, const std::string& paramName, const std::string& funcName) {
            if (!ptr) {
                throw LLVMException(util::format("{}: {} is null", funcName, paramName));
            }
        }
        
        /**
         * @brief Format an error message with consistent style
         * 
         * @param funcName The name of the function raising the error
         * @param message The error message
         * @return std::string Formatted error message
         */
        inline std::string formatError(const std::string& funcName, const std::string& message) {
            return util::format("{}: {}", funcName, message);
        }
        
        /**
         * @brief Check if two values are equal and throw an exception if not
         * 
         * @tparam T Type of the values to compare
         * @param actual The actual value
         * @param expected The expected value
         * @param message The error message
         * @param funcName The name of the calling function
         * @throws LLVMException if the values are not equal
         */
        template<typename T>
        void checkEqual(const T& actual, const T& expected, const std::string& message, const std::string& funcName) {
            if (actual != expected) {
                throw LLVMException(formatError(funcName, message));
            }
        }
    }

    /**
     * @class LLVM
     * @brief Main class for generating LLVM IR code from HLIR (High-Level IR) representation
     * 
     * The LLVM class serves as a bridge between the Iron language's high-level IR (HLIR) and 
     * LLVM's intermediate representation. It traverses the HLIR structure and generates 
     * equivalent LLVM IR code that can be compiled and executed.
     *
     * The class provides methods to:
     * - Process high-level language constructs (functions, expressions, statements)
     * - Generate low-level LLVM IR instructions
     * - Map Iron language types to LLVM types
     * - Manage memory allocations and variable assignments
     * - Handle operations, function calls, and control flow
     * - Compile, link, and execute the generated code
     *
     * It serves as the core backend compiler component for the Iron language.
     */
    class LLVM
    {
    private:
        /** HLIR context containing parsed program structure */
        std::shared_ptr<hlir::Context> hlirContext;
        
        /** LLVM context used for IR generation */
        llvm::LLVMContext &llvmContext;
        
        /** LLVM IRBuilder used to create LLVM instructions */
        llvm::IRBuilder<> builder;
        
        /** LLVM Module that holds the generated IR */
        std::unique_ptr<llvm::Module> module;
        
        /** Source filename for the current module */
        std::string filename;
        
        //---------------------------------------------------------------------
        // Utility methods for internal use
        //---------------------------------------------------------------------
        
        /**
         * @brief Creates a load instruction for a variable
         *
         * @param variable The variable to load
         * @param function The function context
         * @return llvm::LoadInst* The load instruction
         * @throws LLVMException if the variable can't be found or loaded
         */
        llvm::LoadInst* loadVariable(const std::shared_ptr<hlir::Variable>& variable, llvm::Function* function);
        
        /**
         * @brief Validates all operation inputs before execution
         *
         * @param operation The operation to validate
         * @param function The function context
         * @param funcName The name of the calling function
         * @throws LLVMException if any validation fails
         */
        void validateOperationInputs(const std::shared_ptr<hlir::BinaryOperation>& operation, 
                                    llvm::Function* function, 
                                    const std::string& funcName);
                                    
        /**
         * @brief Creates a struct field access and loads its value
         * 
         * @param structVar Variable containing the struct
         * @param fieldName Name of the field to access
         * @param fieldIndex Index of the field in the struct
         * @param fieldType Type of the field 
         * @param function Current function context
         * @return llvm::Value* The loaded field value
         */
        llvm::Value* loadStructField(
            const std::shared_ptr<hlir::Variable>& structVar,
            const std::string& fieldName,
            unsigned fieldIndex,
            int fieldType,
            llvm::Function* function);

    public:
        /**
         * @brief Constructs an LLVM code generator
         * @param hlirContext The HLIR context containing the parsed program
         * @param context The LLVM context to use for IR generation
         * @param filename The source filename for the module
         */
        explicit LLVM(const std::shared_ptr<hlir::Context> &hlirContext, llvm::LLVMContext &context,
                      const std::string &filename);
        
        /**
         * @brief Destructor
         */
        ~LLVM();

        void visitStruct(const std::shared_ptr<hlir::Struct> & struct_) const;
        /**
         * @brief Generates LLVM IR code from the HLIR context
         * @return Unique pointer to the generated LLVM module
         * @throws LLVMException if code generation fails
         */
        std::unique_ptr<llvm::Module> generateCode();

        //---------------------------------------------------------------------
        // Type Handling
        //---------------------------------------------------------------------
        
        /**
         * @brief Maps Iron language types to LLVM types
         * @param type The Iron type token
         * @return The corresponding LLVM type
         * @throws LLVMException if the type is unknown
         */
        llvm::Type *mapType(int type) const;
        
        /**
         * @brief Generates a default return value based on function return type
         * @param functionReturnType The function's return type
         * @throws LLVMException if the type is not supported
         */
        void generateTerminator(llvm::Type *functionReturnType);
        
        /**
         * @brief Creates a type cast operation
         * @param variable The variable to cast
         * @param type The target type
         * @param currentFunction The current function context
         * @return The result of the cast operation
         * @throws LLVMException for various error conditions
         */
        llvm::Value *numberCasting(const std::shared_ptr<hlir::Variable> &variable,
                                   const std::shared_ptr<hlir::Type> &type, 
                                   llvm::Function *currentFunction);

        //---------------------------------------------------------------------
        // String Handling
        //---------------------------------------------------------------------
        
        /**
         * @brief Normalizes a string by processing escape sequences
         * @param input The input string to normalize
         * @return The normalized string
         */
        static std::string normalizeUserString(const std::string &input);
        llvm::StructType *getStructByName(const std::string &name) const;
        std::shared_ptr<hlir::Variable> getVariableFromValue(const std::shared_ptr<hlir::Value> &value) const;
        void structInit(llvm::Function *currentFunction, const std::shared_ptr<hlir::StructInit> &structInit,
                        const std::shared_ptr<hlir::Variable> &variable);

        //---------------------------------------------------------------------
        // Variable Handling
        //---------------------------------------------------------------------
        
        /**
         * @brief Assigns a constant value to a variable allocation
         * @param variable The variable receiving the value
         * @param value The value to assign
         * @param allocaVariable The allocation instruction for the variable
         * @throws LLVMException for null pointers, type mismatches, or unsupported types
         */
        void assignValue(const std::shared_ptr<hlir::Variable> &variable, 
                         const std::shared_ptr<hlir::Value> &value,
                         llvm::AllocaInst *allocaVariable);

        /**
         * @brief Assigns a value from another variable to the given allocation
         * @param value Source value to assign
         * @param allocaVariable Destination allocation instruction
         * @param function Current function where the assignment takes place
         * @throws LLVMException if any required pointers are null
         */
        void assignVariable(const std::shared_ptr<hlir::Value> &value, 
                            llvm::AllocaInst *allocaVariable,
                            llvm::Function *function);

        /**
         * @brief Allocates space for a variable in the current function
         * @param variable The variable to allocate
         * @return The allocation instruction
         * @throws LLVMException for various error conditions
         */
        llvm::AllocaInst *allocaVariable(const std::shared_ptr<hlir::Variable> &variable);

        /**
         * @brief Finds an allocation instruction by name in a function
         * @param function The function to search in
         * @param varName The name of the variable to find
         * @return The allocation instruction or nullptr if not found
         */
        static llvm::AllocaInst *findAllocaByName(llvm::Function *function, const std::string &varName);

        /**
         * @brief Finds a function argument by name
         * @param function The function to search in
         * @param argName The name of the argument to find
         * @return Pointer to the argument or nullptr if not found
         * @throws LLVMException if function is null
         */
        llvm::Argument *findArgByName(llvm::Function *function, const std::string &argName);

        /**
         * @brief Promotes a function argument to an allocation in the entry block
         * @param function The function containing the argument
         * @param arg The argument to promote
         * @return The allocation instruction
         * @throws LLVMException if arg is null
         */
        llvm::AllocaInst *promoteArgumentToAlloca(llvm::Function *function, llvm::Argument *arg);

        /**
         * @brief Finds an allocation instruction or promotes an argument to an allocation
         * @param varName The name of the variable to find
         * @param function The function to search in
         * @return The allocation instruction
         * @throws LLVMException if variable not found
         */
        llvm::AllocaInst *getOrPromoteToAlloca(const std::string &varName, llvm::Function *function);

        /**
         * @brief Creates a constant value based on type information
         * @param hlirType The HLIR type information
         * @param value The value to create
         * @return The LLVM constant value
         * @throws Various exceptions for type errors and conversion errors
         */
        llvm::Value *createConstValue(const std::shared_ptr<hlir::Type> &hlirType,
                                      const std::shared_ptr<hlir::Value> &value);
                                      
        /**
         * @brief Allocates a string variable
         * @param variable The variable to allocate
         * @param value The string value
         * @return The allocation instruction
         * @throws LLVMException for various error conditions
         */
        llvm::AllocaInst *allocaVariableStr(const std::shared_ptr<hlir::Variable> &variable, 
                                            const std::string &value);
                                            
        /**
         * @brief Allocates a function pointer variable
         * @param variable The variable to allocate
         * @param function The function to point to
         * @return The allocation instruction
         * @throws LLVMException for various error conditions
         */
        llvm::AllocaInst *allocaVariableFuncPtr(const std::shared_ptr<hlir::Variable> &variable,
                                                const std::shared_ptr<hlir::Function> &function);

        //---------------------------------------------------------------------
        // Operation Handling
        //---------------------------------------------------------------------
        
        /**
         * @brief Loads left and right operands of a binary operation
         * @param op The binary operation
         * @param currentFunction The current function context
         * @return Pair of load instructions for left and right variables
         * @throws LLVMException if any operand cannot be loaded
         */
        std::pair<llvm::LoadInst *, llvm::LoadInst *> operationLoad(
            const std::shared_ptr<hlir::BinaryOperation> &op,
            llvm::Function *currentFunction);
            
        /**
         * @brief Creates a logical AND operation
         * @param _and The AND operation details
         * @param currentFunction The current function context
         * @return The result of the AND operation
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeAND(const std::shared_ptr<hlir::AND> &_and, 
                               llvm::Function *currentFunction);
                               
        /**
         * @brief Creates a logical OR operation
         * @param _or The OR operation details
         * @param currentFunction The current function context
         * @return The result of the OR operation
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeOR(const std::shared_ptr<hlir::OR> &_or, 
                              llvm::Function *currentFunction);
                              
        /**
         * @brief Creates a logical NOT operation
         * @param _not The NOT operation details
         * @param currentFunction The current function context
         * @return The result of the NOT operation
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeNOT(const std::shared_ptr<hlir::_NOT> &_not, 
                               llvm::Function *currentFunction);
                               
        /**
         * @brief Creates a comparison operation
         * @param cmp The comparison operation details
         * @param currentFunction The current function context
         * @return The result of the comparison operation
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeCMP(const std::shared_ptr<hlir::CMP> &cmp, 
                               llvm::Function *currentFunction);

        /**
         * @brief Creates a multiplication operation
         * @param mult The multiplication operation details
         * @param currentFunction The current function context
         * @return The result of the multiplication
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeMult(const std::shared_ptr<hlir::Mult> &mult, 
                                llvm::Function *currentFunction);

        /**
         * @brief Creates a division operation
         * @param div The division operation details
         * @param currentFunction The current function context
         * @return The result of the division
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeDiv(const std::shared_ptr<hlir::Div> &div, 
                               llvm::Function *currentFunction);

        /**
         * @brief Creates an addition operation
         * @param plus The addition operation details
         * @param currentFunction The current function context
         * @return The result of the addition
         * @throws LLVMException if operation is null
         */
        llvm::Value *executePlus(const std::shared_ptr<hlir::Plus> &plus, 
                                llvm::Function *currentFunction);

        /**
         * @brief Creates a subtraction operation
         * @param minus The subtraction operation details
         * @param currentFunction The current function context
         * @return The result of the subtraction
         * @throws LLVMException if operation is null
         */
        llvm::Value *executeMinus(const std::shared_ptr<hlir::Minus> &minus, 
                                 llvm::Function *currentFunction);

        //---------------------------------------------------------------------
        // Function and Control Flow Handling
        //---------------------------------------------------------------------
        
        /**
         * @brief Declares a function in the LLVM module
         * @param hlirFunction The HLIR function to declare
         * @throws LLVMException if function is null
         */
        void declareFunction(const std::shared_ptr<hlir::Function> &hlirFunction) const;

        /**
         * @brief Processes a function definition and generates its LLVM IR
         * @param hlirFunction The HLIR function to process
         * @throws LLVMException if function is null
         */
        void visitFunction(const std::shared_ptr<hlir::Function> &hlirFunction);

        /**
         * @brief Processes statements in a scope
         * @param statements The statements to process
         * @throws LLVMException if statements is null
         */
        void visitStatement(const std::shared_ptr<hlir::Statement> &statements);

        /**
         * @brief Processes a function return statement
         * @param funcReturn The function return statement to process
         * @throws LLVMException if funcReturn is null
         */
        void visitFuncReturn(const std::shared_ptr<hlir::FuncReturn> &funcReturn);
        
        /**
         * @brief Finds a basic block by name in a function
         * @param blockName The name of the block to find
         * @param currentFunction The function to search in
         * @return The found basic block
         * @throws LLVMException if the block is not found
         */
        static llvm::BasicBlock *getBasicBlock(const std::string &blockName, 
                                              llvm::Function *currentFunction);
        
        /**
         * @brief Processes an unconditional jump to a block
         * @param jump The jump statement to process
         * @throws LLVMException if jump is null
         */
        void visitJump(const std::shared_ptr<hlir::Jump> &jump);
        
        /**
         * @brief Sets the insertion point to a specific block
         * @param block The block to set as current
         * @throws LLVMException if block is null
         */
        void visitBlock(const std::shared_ptr<hlir::Block> &block);
        
        /**
         * @brief Creates a conditional branch based on a boolean condition
         * @param conditional The conditional statement to process
         * @throws LLVMException if conditional is null
         */
        void visitConditional(const std::shared_ptr<hlir::Conditional> &conditional);

        /**
         * @brief Processes an expression
         * @param hlirExpr The expression to process
         * @throws LLVMException if expression is null
         */
        void visitExpr(const std::shared_ptr<hlir::Expr> &hlirExpr);

        /**
         * @brief Processes an assignment statement
         * @param hlirAssignment The assignment to process
         * @throws LLVMException if assignment is null
         */
        void visitAssignment(const std::shared_ptr<hlir::Assign> &hlirAssignment);

        /**
         * @brief Processes a function call to a function passed as an argument
         * @param functionCall The function call details
         * @param funcArg The function argument value
         * @return The result of the function call
         * @throws LLVMException if functionCall is null
         */
        llvm::Value *visitFunctionCallArg(const std::shared_ptr<hlir::FunctionCall> &functionCall,
                                          llvm::Value *funcArg);
                                          
        /**
         * @brief Processes a function call
         * @param functionCall The function call details
         * @return The result of the function call
         * @throws LLVMException if functionCall is null
         */
        llvm::Value *visitFunctionCall(const std::shared_ptr<hlir::FunctionCall> &functionCall);
        
        /**
         * @brief Creates an LLVM function type
         * @param functionReturnType The function return type
         * @param argTypes Vector of argument types
         * @param isVariedArguments Whether the function has variadic arguments
         * @return The created function type
         * @throws LLVMException if functionReturnType is null
         */
        llvm::FunctionType *createFuncType(llvm::Type *functionReturnType, 
                                          const std::vector<llvm::Type *> &argTypes,
                                          bool isVariedArguments) const;
                                           
        /**
         * @brief Creates an LLVM function type from HLIR signature
         * @param signature The HLIR function signature
         * @return The created function type
         * @throws LLVMException if signature is null
         */
        llvm::FunctionType *createFuncTypeFromSignature(
            const std::shared_ptr<hlir::Signature>& signature) const;
            
        /**
         * @brief Processes function arguments and creates LLVM types
         * @param args Vector of function arguments
         * @return Pair of argument types and names
         * @throws LLVMException for invalid arguments
         */
        std::pair<std::vector<llvm::Type *>, std::vector<std::string>>
        createFunctionArgs(const std::vector<std::shared_ptr<hlir::Arg>> &args) const;

        //---------------------------------------------------------------------
        // Code Generation and Execution
        //---------------------------------------------------------------------
        
        /**
         * @brief Links object files into an executable
         * @param objects Vector of object file paths to link
         * @param exeName Name of the output executable
         * @param arch Target architecture
         * @param macosxVersionMin Minimum macOS version
         * @throws std::runtime_error if linking fails
         */
        static void linkExecutable(const std::vector<std::string> &objects, 
                                  const std::string &exeName,
                                  const std::string &arch, 
                                  const std::string &macosxVersionMin);

        /**
         * @brief Merges multiple LLVM modules into a single module
         * @param modules Vector of modules to merge
         * @return The merged module
         * @throws LLVMException if merging fails
         */
        static std::unique_ptr<llvm::Module> mergeModules(
            std::vector<std::unique_ptr<llvm::Module>> modules);
            
        /**
         * @brief Generates an object file from an LLVM module
         * @param module The module to compile
         * @param filename The output filename
         * @throws LLVMException if compilation fails
         */
        static void emitObjectFile(llvm::Module *module, const std::string &filename);
        
        /**
         * @brief Executes an LLVM module using JIT compilation
         * @param mainModule The module to execute
         * @throws LLVMException if execution fails
         */
        static void executeModule(std::unique_ptr<llvm::Module> mainModule);
    };
} // namespace iron

#endif // LLVMIR_H

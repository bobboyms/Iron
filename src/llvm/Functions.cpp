#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    /**
     * @brief Processes a function definition and generates its LLVM IR
     * 
     * @param hlirFunction The HLIR function to process
     * @throws LLVMException for various error conditions
     */
    void LLVM::visitFunction(const std::shared_ptr<hlir::Function> &hlirFunction)
    {
        if (!hlirFunction)
        {
            throw LLVMException("LLVM::visitFunction: VisitFunction called with null hlirFunction");
        }

        // Skip external function declarations
        if (hlirFunction->isExternal())
        {
            return;
        }

        // Find the LLVM function object
        llvm::Function *function = module->getFunction(hlirFunction->getFunctionName());
        if (!function)
        {
            throw LLVMException(
                    util::format("LLVM::visitFunction: Function {} not found", hlirFunction->getFunctionName()));
        }

        // Get function return type
        if (!hlirFunction->getFunctionReturnType())
        {
            throw LLVMException(
                    util::format("LLVM::visitFunction: Function {} has null return type", hlirFunction->getFunctionName()));
        }
        
        const llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        
        // Create entry block and set insertion point
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvmContext, "entry", function);
        builder.SetInsertPoint(entry);

        // Create all basic blocks needed for the function
        for (const auto& block: hlirFunction->getAllBlocks())
        {
            if (!block) {
                continue; // Skip null blocks
            }
            
            llvm::BasicBlock::Create(llvmContext, block->getLabel(), function);
        }

        // Process function body
        visitStatement(hlirFunction->getRootScope());
        
        // Add return void for void functions if needed
        if (functionReturnType->isVoidTy())
        {
            builder.CreateRetVoid();
        }
    }

    /**
     * @brief Processes a function return statement
     * 
     * @param funcReturn The function return statement to process
     * @throws LLVMException for various error conditions
     */
    void LLVM::visitFuncReturn(const std::shared_ptr<hlir::FuncReturn> &funcReturn)
    {
        if (!funcReturn) {
            throw LLVMException("LLVM::visitFuncReturn: funcReturn is null");
        }
        
        if (!funcReturn->getVariable()) {
            throw LLVMException("LLVM::visitFuncReturn: return variable is null");
        }
        
        if (!funcReturn->getVariable()->getVarType()) {
            throw LLVMException("LLVM::visitFuncReturn: return variable type is null");
        }
        
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("LLVM::visitFuncReturn: currentFunction is null");
        }

        // Get the variable name and its allocation
        const auto varName = funcReturn->getVariable()->getRealName();
        const auto allocaVariable = findAllocaByName(currentFunction, varName);
        if (!allocaVariable) {
            throw LLVMException(util::format("LLVM::visitFuncReturn: Variable {} not found", varName));
        }

        // Map the variable type to LLVM type
        const auto type = mapType(funcReturn->getVariable()->getVarType()->getType());

        // Load the variable value and create a return instruction
        llvm::Value *varValue = builder.CreateLoad(type, allocaVariable, util::format("load_{}", varName));
        builder.CreateRet(varValue);
    }

    /**
     * @brief Finds a basic block by name in the current function
     * 
     * @param blockName The name of the block to find
     * @param currentFunction The function to search in
     * @return llvm::BasicBlock* The found basic block
     * @throws LLVMException if the block is not found
     */
    llvm::BasicBlock *LLVM::getBasicBlock(const std::string &blockName, llvm::Function *currentFunction)
    {
        if (blockName.empty()) {
            throw LLVMException("LLVM::getBasicBlock: blockName is empty");
        }
        
        if (!currentFunction) {
            throw LLVMException("LLVM::getBasicBlock: currentFunction is null");
        }
        
        for (auto &BB: *currentFunction)
        {
            if (BB.getName() == blockName)
            {
                return &BB;
            }
        }

        throw LLVMException(util::format("LLVM::getBasicBlock: Block {} not found", blockName));
    }

    /**
     * @brief Processes an unconditional jump to a block
     * 
     * @param jump The jump statement to process
     * @throws LLVMException for various error conditions
     */
    void LLVM::visitJump(const std::shared_ptr<hlir::Jump> &jump)
    {
        if (!jump) {
            throw LLVMException("LLVM::visitJump: jump is null");
        }
        
        if (!jump->getBlock()) {
            throw LLVMException("LLVM::visitJump: target block is null");
        }
        
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("LLVM::visitJump: currentFunction is null");
        }

        // Find the target block and create a branch instruction
        const auto basicBlock = getBasicBlock(jump->getBlock()->getLabel(), currentFunction);
        builder.CreateBr(basicBlock);
    }

    /**
     * @brief Sets the insertion point to a specific block
     * 
     * @param block The block to set as current
     * @throws LLVMException for various error conditions
     */
    void LLVM::visitBlock(const std::shared_ptr<hlir::Block> &block)
    {
        if (!block) {
            throw LLVMException("LLVM::visitBlock: block is null");
        }
        
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("LLVM::visitBlock: currentFunction is null");
        }

        // Find the block and set it as the current insertion point
        const auto basicBlock = getBasicBlock(block->getLabel(), currentFunction);
        builder.SetInsertPoint(basicBlock);
    }

    /**
     * @brief Creates a conditional branch based on a boolean condition
     * 
     * @param conditional The conditional statement to process
     * @throws LLVMException for various error conditions
     */
    void LLVM::visitConditional(const std::shared_ptr<hlir::Conditional> &conditional)
    {
        if (!conditional)
        {
            throw LLVMException("LLVM::visitConditional: conditional is null");
        }
        
        if (!conditional->getVariable()) {
            throw LLVMException("LLVM::visitConditional: condition variable is null");
        }
        
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("LLVM::visitConditional: currentFunction is null");
        }

        // Get the condition variable and load its value
        const auto variable = getOrPromoteToAlloca(conditional->getVariable()->getRealName(), currentFunction);
        auto *cond = builder.CreateLoad(builder.getInt1Ty(), variable, "cond_");

        // Find the true and false target blocks
        llvm::BasicBlock *thenBB = getBasicBlock(conditional->getTrueLabel(), currentFunction);
        llvm::BasicBlock *elseBB = getBasicBlock(conditional->getFalseLabel(), currentFunction);

        // Create the conditional branch
        builder.CreateCondBr(cond, thenBB, elseBB);
    }

    /**
     * @brief Helper function to find a function argument by name
     * 
     * @param F The function to search
     * @param name The name of the argument
     * @return llvm::Value* The argument value or nullptr if not found
     */
    llvm::Value *getArgumentByName(llvm::Function *F, const llvm::StringRef name)
    {
        if (!F) {
            return nullptr;
        }
        
        for (auto &Arg: F->args())
        {
            if (Arg.getName() == name)
                return &Arg;
        }
        return nullptr;
    }

    /**
     * @brief Handles calling a function that was passed as an argument
     * 
     * @param functionCall The function call details
     * @param funcArg The function argument value
     * @return llvm::Value* The result of the function call
     * @throws LLVMException for various error conditions
     */
    llvm::Value *LLVM::visitFunctionCallArg(const std::shared_ptr<hlir::FunctionCall> &functionCall,
                                            llvm::Value *funcArg)
    {
        if (!functionCall) {
            throw LLVMException("LLVM::visitFunctionCallArg: functionCall is null");
        }
        
        if (!funcArg) {
            throw LLVMException("LLVM::visitFunctionCallArg: funcArg is null");
        }
        
        if (!functionCall->getCallArgs()) {
            throw LLVMException("LLVM::visitFunctionCallArg: callArgs is null");
        }

        // Get the current function context
        const llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("LLVM::visitFunctionCallArg: currentFunction is null");
        }

        // Get parent function information
        const auto parentFunctionName = currentFunction->getName().str();
        const auto functionCallName = functionCall->getFunctionCallName();

        const auto parentFunction = hlirContext->getFunctionByName(parentFunctionName);
        if (!parentFunction)
        {
            throw LLVMException("LLVM::visitFunctionCallArg: parentFunction is null");
        }

        const auto variable = parentFunction->findVarAllScopesAndArg(functionCallName);
        if (!variable)
        {
            throw LLVMException(util::format(
                "LLVM::visitFunctionCallArg: Variable {} not found", functionCallName));
        }

        if (!variable->getSignature())
        {
            throw LLVMException(util::format(
                "LLVM::visitFunctionCallArg: Signature for {} is null", functionCallName));
        }

        // Create the function type from signature
        const auto targetFuncType = createFuncTypeFromSignature(variable->getSignature());

        // Process the function call arguments
        std::vector<llvm::Value *> args;
        for (const auto &arg: functionCall->getCallArgs()->getCallArgs())
        {
            if (!arg || !arg->value || !arg->value->getValueType()) {
                throw LLVMException("LLVM::visitFunctionCallArg: Invalid argument");
            }
            
            const auto value = createConstValue(arg->value->getValueType(), arg->value);
            args.push_back(value);
        }

        // Create the function call
        return builder.CreateCall(targetFuncType, funcArg, args, "call_func_arg");
    }

    /**
     * @brief Processes a function call
     * 
     * @param functionCall The function call details
     * @return llvm::Value* The result of the function call, or nullptr for void functions
     * @throws LLVMException for various error conditions
     */
    llvm::Value *LLVM::visitFunctionCall(const std::shared_ptr<hlir::FunctionCall> &functionCall)
    {
        if (!functionCall)
        {
            throw LLVMException("LLVM::visitFunctionCall: functionCall is null");
        }

        if (!functionCall->getFunction())
        {
            throw LLVMException("LLVM::visitFunctionCall: functionCall->getFunction() is null");
        }

        if (!functionCall->getCallArgs())
        {
            throw LLVMException("LLVM::visitFunctionCall: functionCall->getCallArgs() is null");
        }

        // Get current function context
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("LLVM::visitFunctionCall: currentFunction is null");
        }

        // Get the target function name
        const auto functionName = functionCall->getFunction()->getFunctionName();

        // Find the function in the module
        llvm::Function *function = module->getFunction(functionName);
        if (!function)
        {
            // If not found, check if it's a function argument
            const auto funcArg = getArgumentByName(currentFunction, functionName);
            if (!funcArg)
            {
                throw LLVMException(util::format("LLVM::visitFunctionCall: Function {} not found", functionName));
            }

            // Handle function pointer call
            return visitFunctionCallArg(functionCall, funcArg);
        }

        // Check if this is a call via function pointer (arrow function)
        const auto arrowFunction = findAllocaByName(currentFunction, functionCall->getFunctionCallName());

        // Process the function call arguments
        std::vector<llvm::Value *> args;
        for (const auto &arg: functionCall->getCallArgs()->getCallArgs())
        {
            if (!arg || !arg->value || !arg->value->getValueType()) {
                throw LLVMException(util::format(
                    "LLVM::visitFunctionCall: Invalid argument for function {}", functionName));
            }
            
            const auto value = createConstValue(arg->value->getValueType(), arg->value);
            args.push_back(value);
        }

        // Verify argument count for non-variadic functions
        if (!functionCall->getFunction()->isVariedArguments())
        {
            if (function->arg_size() != args.size())
            {
                throw LLVMException(util::format(
                    "LLVM::visitFunctionCall: Argument count mismatch for function {}: expected {}, got {}",
                    functionName, function->arg_size(), args.size()));
            }
        }

        // Handle void functions
        if (function->getReturnType()->isVoidTy())
        {
            if (arrowFunction)
            {
                // Call via function pointer
                llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(function->getFunctionType());
                llvm::Value *arrowLoaded =
                        builder.CreateLoad(funcPtrType, arrowFunction,
                                           util::format("arrow_{}_loaded", functionCall->getFunctionCallName()));
                builder.CreateCall(function->getFunctionType(), arrowLoaded, args);
            }
            else
            {
                // Direct call
                builder.CreateCall(function, args);
            }
            return nullptr;
        }

        // Handle non-void functions
        if (arrowFunction)
        {
            // Call via function pointer
            llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(function->getFunctionType());
            llvm::Value *arrowLoaded = builder.CreateLoad(
                    funcPtrType, arrowFunction, util::format("arrow_{}_loaded", functionCall->getFunctionCallName()));
            return builder.CreateCall(function->getFunctionType(), arrowLoaded, args,
                                      util::format("call_{}", functionCall->getFunctionCallName()));
        }

        // Direct call
        return builder.CreateCall(function, args, "call_" + functionName);
    }

    /**
     * @brief Creates an LLVM function type
     * 
     * @param functionReturnType The function return type
     * @param argTypes Vector of argument types
     * @param isVariedArguments Whether the function has variadic arguments
     * @return llvm::FunctionType* The created function type
     */
    llvm::FunctionType *LLVM::createFuncType(llvm::Type *functionReturnType, const std::vector<llvm::Type *> &argTypes,
                                             const bool isVariedArguments) const
    {
        if (!functionReturnType) {
            throw LLVMException("LLVM::createFuncType: functionReturnType is null");
        }
        
        // Create function type with or without arguments
        if (!argTypes.empty())
        {
            return llvm::FunctionType::get(functionReturnType, argTypes, isVariedArguments);
        }
        else
        {
            return llvm::FunctionType::get(functionReturnType, llvm::ArrayRef<llvm::Type *>(), isVariedArguments);
        }
    }

    /**
     * @brief Creates an LLVM function type from HLIR signature
     * 
     * @param signature The HLIR function signature
     * @return llvm::FunctionType* The created function type
     * @throws LLVMException for null signature
     */
    llvm::FunctionType *LLVM::createFuncTypeFromSignature(const std::shared_ptr<hlir::Signature> &signature) const
    {
        if (!signature) {
            throw LLVMException("LLVM::createFuncTypeFromSignature: signature is null");
        }
        
        if (!signature->getReturnType()) {
            throw LLVMException("LLVM::createFuncTypeFromSignature: return type is null");
        }
        
        // Map return type and process arguments
        llvm::Type *functionReturnType = mapType(signature->getReturnType()->getType());
        const auto [innerArgTypes, _] = createFunctionArgs(signature->getArgs());
        return createFuncType(functionReturnType, innerArgTypes, false);
    }

    /**
     * @brief Processes function arguments and creates LLVM types
     * 
     * @param args Vector of function arguments
     * @return std::pair<std::vector<llvm::Type *>, std::vector<std::string>> Pair of argument types and names
     * @throws LLVMException for invalid arguments
     */
    std::pair<std::vector<llvm::Type *>, std::vector<std::string>>
    LLVM::createFunctionArgs(const std::vector<std::shared_ptr<hlir::Arg>> &args) const
    {
        std::vector<llvm::Type *> argTypes{};
        std::vector<std::string> argNames{};

        // Process each argument
        for (const auto &arg: args)
        {
            if (!arg) {
                continue; // Skip null arguments
            }
            
            if (!arg->type) {
                throw LLVMException("LLVM::createFunctionArgs: argument type is null");
            }

            // Handle function pointer arguments
            if (arg->type->getType() == tokenMap::FUNCTION)
            {
                if (!arg->signature)
                {
                    throw LLVMException(
                        util::format("LLVM::createFunctionArgs: function argument '{}' does not have a signature", 
                                    arg->name));
                }

                const llvm::FunctionType *funcType = createFuncTypeFromSignature(arg->signature);
                argTypes.push_back(funcType->getPointerTo());
                argNames.push_back(arg->name);
            }
            else
            {
                // Handle regular arguments
                argTypes.push_back(mapType(arg->type->getType()));
                argNames.push_back(arg->name);
            }
        }

        return std::make_pair(argTypes, argNames);
    }

    /**
     * @brief Declares a function in the LLVM module
     * 
     * @param hlirFunction The HLIR function to declare
     * @throws LLVMException for various error conditions
     */
    void LLVM::declareFunction(const std::shared_ptr<hlir::Function> &hlirFunction) const
    {
        if (!hlirFunction) {
            throw LLVMException("LLVM::declareFunction: hlirFunction is null");
        }
        
        if (!hlirFunction->getFunctionReturnType()) {
            throw LLVMException(
                util::format("LLVM::declareFunction: Function {} has null return type", 
                            hlirFunction->getFunctionName()));
        }
        
        if (!hlirFunction->getFunctionArgs()) {
            throw LLVMException(
                util::format("LLVM::declareFunction: Function {} has null args", 
                            hlirFunction->getFunctionName()));
        }

        // Skip if function already exists
        if (module->getFunction(hlirFunction->getFunctionName()))
        {
            return;
        }

        const auto functionName = hlirFunction->getFunctionName();
        
        // Map return type and process arguments
        llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        const auto [argTypes, argNames] = createFunctionArgs(hlirFunction->getFunctionArgs()->getArgs());

        // Create function type
        llvm::FunctionType *funcType = createFuncType(functionReturnType, argTypes, hlirFunction->isVariedArguments());

        // Set linkage type
        constexpr llvm::Function::LinkageTypes linkage = llvm::Function::ExternalLinkage;

        // Create the function in the module
        llvm::Function *function =
                llvm::Function::Create(funcType, linkage, functionName, module.get());

        // Set argument names
        if (!argTypes.empty())
        {
            unsigned idx = 0;
            for (auto &arg: function->args())
            {
                if (idx < argNames.size())
                {
                    const std::string &argName = argNames[idx++];
                    arg.setName(argName);
                }
            }
        }
    }
} // namespace iron

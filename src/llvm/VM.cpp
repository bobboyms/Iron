#include "../headers/LLVMIR.h"
#include "../headers/Exceptions.h"
#include "llvm/IR/Module.h"
#include "llvm/Linker/Linker.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

namespace iron {

    /**
     * @brief Merges multiple LLVM modules into a single module
     * 
     * @param modules Vector of unique LLVM modules to merge
     * @return std::unique_ptr<llvm::Module> The merged module
     * @throws LLVMException If the modules can't be linked together
     */
    std::unique_ptr<llvm::Module> LLVM::mergeModules(std::vector<std::unique_ptr<llvm::Module>> modules)
    {
        if (modules.empty()) {
            throw LLVMException("mergeModules: No modules provided");
        }

        // Use the first module as the main module
        if (!modules[0]) {
            throw LLVMException("mergeModules: First module is null");
        }
        
        std::unique_ptr<llvm::Module> mainModule = std::move(modules[0]);

        // Create a Linker for the main module
        llvm::Linker linker(*mainModule);

        // Link the remaining modules to the main module
        for (size_t i = 1; i < modules.size(); ++i) {
            if (!modules[i]) {
                llvm::errs() << "Warning: Module " << i << " is null, skipping\n";
                continue;
            }
            
            if (linker.linkInModule(std::move(modules[i]))) {
                throw LLVMException(util::format("Failed to link module {} into main module", i));
            }
        }
        
        return mainModule;
    }

    /**
     * @brief Executes an LLVM module using the MCJIT execution engine
     * 
     * This function initializes the execution environment, finds the main function,
     * and executes it with the JIT compiler.
     * 
     * @param mainModule The LLVM module to execute
     * @throws LLVMException If the module can't be executed
     */
    void LLVM::executeModule(std::unique_ptr<llvm::Module> mainModule) {
        if (!mainModule) {
            throw LLVMException("executeModule: Module is null");
        }
        
        try {
            // Initialize the native target and components
            llvm::InitializeNativeTarget();
            llvm::InitializeNativeTargetAsmPrinter();
            llvm::InitializeNativeTargetAsmParser();

            // Create an ExecutionEngine for the module
            std::string errorMsg;
            const std::unique_ptr<llvm::ExecutionEngine> engine(
                llvm::EngineBuilder(std::move(mainModule))
                    .setErrorStr(&errorMsg)
                    .setEngineKind(llvm::EngineKind::JIT)
                    .create()
            );

            if (!engine) {
                throw LLVMException(util::format("Failed to create ExecutionEngine: {}", errorMsg));
            }

            // Finalize the object for execution preparation
            engine->finalizeObject();

            // Find the "main" function in the module
            llvm::Function *mainFunc = engine->FindFunctionNamed("main");
            if (!mainFunc) {
                throw LLVMException("No 'main' function found in the module");
            }

            // Prepare the arguments (assuming no arguments for now)
            const std::vector<llvm::GenericValue> args;

            // Execute the "main" function
            const llvm::GenericValue result = engine->runFunction(mainFunc, args);

            // Print the result (assuming it's an int)
            llvm::outs() << "Program executed successfully. Exit code: " << result.IntVal << "\n";
        }
        catch (const std::exception& e) {
            throw LLVMException(util::format("Error during module execution: {}", e.what()));
        }
    }

} // namespace iron

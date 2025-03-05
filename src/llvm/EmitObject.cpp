#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/MC/TargetRegistry.h"  // Required for LLVM 20

#include <optional>
#include <stdexcept>

namespace iron {

    /**
     * @brief Generates an object file from an LLVM module
     * 
     * This function takes an LLVM module and outputs it as a compiled object file
     * for the current native target architecture.
     * 
     * @param module The LLVM module to compile
     * @param filename The output object file path
     * @throws LLVMException if any step of the object file generation fails
     */
    void LLVM::emitObjectFile(llvm::Module *module, const std::string &filename) {
        if (!module) {
            throw LLVMException("emitObjectFile: module is null");
        }
        
        if (filename.empty()) {
            throw LLVMException("emitObjectFile: filename is empty");
        }
        
        try {
            // Initialize the native target and its components
            llvm::InitializeNativeTarget();
            llvm::InitializeNativeTargetAsmPrinter();
            llvm::InitializeNativeTargetAsmParser();

            // Get or set the target triple
            std::string targetTriple = module->getTargetTriple();
            if (targetTriple.empty()) {
                // Default for ARM64 Apple macOS
                targetTriple = "arm64-apple-macosx15.0.0";
                module->setTargetTriple(targetTriple);
            }

            // Look up the target using the triple
            std::string errorMsg;
            const llvm::Target *target = llvm::TargetRegistry::lookupTarget(targetTriple, errorMsg);
            if (!target) {
                throw LLVMException(
                    util::format("Failed to find target for triple '{}': {}", targetTriple, errorMsg));
            }

            // Create target machine with options
            const llvm::TargetOptions opt;
            constexpr std::optional<llvm::Reloc::Model> RM; // Default relocation model
            const std::unique_ptr<llvm::TargetMachine> targetMachine(
                target->createTargetMachine(targetTriple, "generic", "", opt, RM)
            );
            
            if (!targetMachine) {
                throw LLVMException("Failed to create TargetMachine");
            }

            // Set the module's data layout according to the target machine
            module->setDataLayout(targetMachine->createDataLayout());

            // Open a file stream for the output object file
            std::error_code EC;
            llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OF_None);
            if (EC) {
                throw LLVMException(
                    util::format("Could not open file '{}': {}", filename, EC.message()));
            }

            // Configure PassManager to emit the object file
            llvm::legacy::PassManager pass;
            using CodeGenFileType = llvm::CodeGenFileType;

            if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, CodeGenFileType::ObjectFile)) {
                throw LLVMException(
                    util::format("TargetMachine cannot emit object file of this type for '{}'", filename));
            }

            // Run passes on the module to generate the object file
            pass.run(*module);
            dest.flush();

            llvm::outs() << "Successfully generated object file: " << filename << "\n";
        }
        catch (const std::exception &e) {
            throw LLVMException(
                util::format("Error during object file generation for '{}': {}", filename, e.what()));
        }
    }
}

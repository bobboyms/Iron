#include "../headers/LLVMIR.h"
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

namespace iron {
    void LLVM::mergeModulesAndExecute(std::vector<std::unique_ptr<llvm::Module>> modules) {
        if (modules.empty()) {
            llvm::errs() << "No modules provided.\n";
            return;
        }

        // Usa o primeiro módulo como módulo principal.
        std::unique_ptr<llvm::Module> mainModule = std::move(modules[0]);

        // Cria um Linker para o módulo principal.
        llvm::Linker linker(*mainModule);

        // Linka os demais módulos ao módulo principal.
        for (size_t i = 1; i < modules.size(); ++i) {
            // O método linkInModule espera um unique_ptr para transferir a propriedade.
            if (linker.linkInModule(std::move(modules[i]))) {
                llvm::errs() << "Error linking module " << i << "\n";
                return;
            }
        }

        // Inicializa o target nativo.
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();

        // Cria um ExecutionEngine para o módulo mesclado.
        std::string errStr;
        const std::unique_ptr<llvm::ExecutionEngine> engine(
            llvm::EngineBuilder(std::move(mainModule))
                .setErrorStr(&errStr)
                .setEngineKind(llvm::EngineKind::JIT)
                .create()
        );

        if (!engine) {
            llvm::errs() << "Failed to create ExecutionEngine: " << errStr << "\n";
            return;
        }

        // Finaliza a criação do objeto para preparação da execução.
        engine->finalizeObject();

        // Procura a função "main" no módulo mesclado.
        llvm::Function *mainFunc = engine->FindFunctionNamed("main");
        if (!mainFunc) {
            llvm::errs() << "No 'main' function found in the merged module.\n";
            return;
        }

        // Prepara os argumentos (aqui, assumindo que não há argumentos).
        std::vector<llvm::GenericValue> args;

        // Executa a função "main".
        const llvm::GenericValue result = engine->runFunction(mainFunc, args);

        // Imprime o resultado (por exemplo, se for um int).
        llvm::outs() << "Program exited with code: " << result.IntVal << "\n";
    }

} // namespace iron

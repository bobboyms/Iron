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
#include "llvm/MC/TargetRegistry.h"  // Esse header é necessário em LLVM 20

#include <optional>  // Para std::optional

namespace iron {

    void LLVM::emitObjectFile(llvm::Module *module, const std::string &filename) {
        // Inicializa o target nativo e seus componentes.
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();

        // Obtém o target triple do módulo (ou define um se não estiver definido)
        std::string targetTriple = module->getTargetTriple();
        if (targetTriple.empty()) {
            // Exemplo: para um sistema ARM64 Apple macOS
            targetTriple = "arm64-apple-macosx15.0.0";
            module->setTargetTriple(targetTriple);
        }

        // Busca o target usando o target triple.
        std::string error;
        const llvm::Target *target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
        if (!target) {
            llvm::errs() << "Falha ao procurar target: " << error << "\n";
            return;
        }

        // Cria opções e o TargetMachine.
        const llvm::TargetOptions opt;
        constexpr std::optional<llvm::Reloc::Model> RM; // modelo de relocação padrão (std::optional, em C++17)
        const std::unique_ptr<llvm::TargetMachine> targetMachine(
            target->createTargetMachine(targetTriple, "generic", "", opt, RM)
        );
        if (!targetMachine) {
            llvm::errs() << "Não foi possível criar o TargetMachine.\n";
            return;
        }

        // Define o data layout do módulo de acordo com o TargetMachine.
        module->setDataLayout(targetMachine->createDataLayout());

        // Abre um raw_fd_ostream para o arquivo objeto.
        std::error_code EC;
        llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OF_None);
        if (EC) {
            llvm::errs() << "Não foi possível abrir o arquivo: " << EC.message() << "\n";
            return;
        }

        // Configura o PassManager para emitir o arquivo objeto.
        llvm::legacy::PassManager pass;
        // Use o enumerador da TargetMachine para indicar que queremos emitir um arquivo objeto.
        using CodeGenFileType = llvm::CodeGenFileType;

        if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, CodeGenFileType::ObjectFile)) {
            llvm::errs() << "O TargetMachine não consegue emitir um arquivo objeto desse tipo\n";
            return;
        }


        // Executa os passes sobre o módulo para gerar o arquivo objeto.
        pass.run(*module);
        dest.flush();

        llvm::outs() << "Arquivo objeto gerado com sucesso: " << filename << "\n";
    }
}

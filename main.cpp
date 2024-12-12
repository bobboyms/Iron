#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include "antlr4-runtime.h"

int main() {
    llvm::LLVMContext context;
    llvm::Module module("test", context);
    llvm::IRBuilder<> builder(context);

    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function *mainFunction = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, "main", module
    );

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entry);
    builder.CreateRet(builder.getInt32(0));

    module.print(llvm::outs(), nullptr);

    std::cout << "Olá, mundo!" << std::endl; 
    
    return 0;
}

// /usr/bin/clang++

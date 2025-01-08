#include "headers/LLVMIR.h"
#include "headers/IronExceptions.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"

namespace iron {
    // Converte tipos do HightLevelIR para o LLVM Type
    llvm::Type* LLVMIR::mapType(const int type) {
            if (type == TokenMap::TYPE_INT) {
                return llvm::Type::getInt32Ty(context);
            } else if (type == TokenMap::TYPE_FLOAT) {
                return llvm::Type::getFloatTy(context);
            } else if (type == TokenMap::TYPE_DOUBLE) {
                return llvm::Type::getDoubleTy(context);
            } else if (type == TokenMap::TYPE_CHAR) {
                return llvm::Type::getInt8Ty(context);
            } else if (type == TokenMap::TYPE_BOOLEAN) {
                return llvm::Type::getInt1Ty(context);
            } else if (type == TokenMap::VOID) {
                return llvm::Type::getVoidTy(context);
            }
            // Adicione outros tipos conforme necessário
            throw LLVMException(format("Unknown data type: {}",type));
    }
}


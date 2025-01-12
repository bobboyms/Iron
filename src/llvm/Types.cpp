#include "../headers/LLVMIR.h"
#include "../headers/Exceptions.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    // Converte tipos do HighLevelIR para o LLVM Type
    llvm::Type *LLVMIR::mapType(const int type)
    {
        if (type == tokenMap::TYPE_INT)
        {
            return llvm::Type::getInt32Ty(context);
        }
        else if (type == tokenMap::TYPE_FLOAT)
        {
            return llvm::Type::getFloatTy(context);
        }
        else if (type == tokenMap::TYPE_DOUBLE)
        {
            return llvm::Type::getDoubleTy(context);
        }
        else if (type == tokenMap::TYPE_CHAR)
        {
            return llvm::Type::getInt8Ty(context);
        }
        else if (type == tokenMap::TYPE_BOOLEAN)
        {
            return llvm::Type::getInt1Ty(context);
        }
        else if (type == tokenMap::VOID)
        {
            return llvm::Type::getVoidTy(context);
        }
        // Adicione outros tipos conforme necessário
        throw LLVMException(util::format("Unknown data type: {}", tokenMap::getTokenText(type)));
    }
}

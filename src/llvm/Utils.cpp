#include "../headers/LLVMIR.h"
#include "../headers/IronExceptions.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    llvm::Argument *LLVMIR::getArgumentByName(llvm::Function *func, const std::string &argName)
    {
        for (auto &arg : func->args())
        {
            if (arg.getName() == argName)
            {
                return &arg;
            }
        }
        return nullptr;
    }
}
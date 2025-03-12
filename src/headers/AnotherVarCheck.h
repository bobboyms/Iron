//
// Created by Thiago Rodrigues on 10/03/25.
//

#ifndef ANOTHERVARCHECK_H
#define ANOTHERVARCHECK_H
#include <memory>

#include "../scope/ScopeManager.h"

namespace iron
{
    class AnotherVarCheck
    {
    private:
        int line;
        int codeLine;
        std::string &caretLine;
        std::shared_ptr<scope::ScopeManager> scopeManager;
    public:
        void checkWhenFunction(const std::string &varName,
                                      const std::string  &anotherVarName);
        AnotherVarCheck();
    };
} // namespace iron

#endif // ANOTHERVARCHECK_H

#include "../headers/SemanticalAnalysis.h"

#include <iostream>

namespace iron
{

    std::pair<std::string, std::shared_ptr<scope::Function>> SemanticalAnalysis::getCalledFunction(std::shared_ptr<scope::Function> currentFunction, std::string functionCalledName)
    {
        std::string functionName;
        std::shared_ptr<scope::Function> calledFunction;
        auto functionPtr = currentFunction->findVarCurrentScopeAndArg(functionCalledName);
        if (!functionPtr)
        {
            functionPtr = currentFunction->findVarAllScopesAndArg(functionCalledName);
            if (!functionPtr)
            {
                auto scope = scopeManager->getScopeByName(functionCalledName);
                if (!scope)
                {
                    throw ScopeNotFoundException("SemanticalAnalysis::getCalledFunction. Current scope not found");
                }

                auto function = std::dynamic_pointer_cast<scope::Function>(scope);
                if (!function)
                {
                    throw FunctionNotFoundException(util::format("The called function: {} not found", functionCalledName));
                }

                calledFunction = function;
                functionName = functionCalledName;
            }
            else
            {
                calledFunction = functionPtr->function;
                if (!calledFunction)
                {
                    throw SemanticException("SemanticalAnalysis::getCalledFunction. Invalid function ptr");
                }
                functionName = functionPtr->name;
            }
        }
        else
        {
            calledFunction = functionPtr->function;
            if (!calledFunction)
            {
                throw SemanticException("SemanticalAnalysis::visitFunctionCallArg. Invalid function ptr");
            }
            functionName = functionPtr->name;
        }
        return std::pair(functionName, calledFunction);
    }

}
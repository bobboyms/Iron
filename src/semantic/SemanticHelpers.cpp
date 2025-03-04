#include "../headers/SemanticAnalysis.h"

namespace iron
{
    // Helper function to get context information for error messages
    ErrorContext SemanticAnalysis::getErrorContext(uint line, uint col, int caretOffset)
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, caretOffset);
        return {line, col, codeLine, caretLine, scopeManager->currentScopeName()};
    }

    // Helper function to verify if a variable exists and throw a formatted exception if not
    std::shared_ptr<scope::Variable> SemanticAnalysis::verifyVariableExists(const std::string &varName, uint line,
                                                                            uint col, const std::string &contextInfo)
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);
        auto currentFunction = getCurrentFunction();
        auto variable = currentFunction->findVarAllScopesAndArg(varName);

        if (!variable)
        {
            throw VariableNotFoundException(util::format(
                    "Variable '{}' not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n{}",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                    contextInfo.empty() ? "" : "\n\n" + contextInfo));
        }

        return variable;
    }

    // Helper function to verify if a function exists and throw a formatted exception if not
    std::shared_ptr<scope::Function> SemanticAnalysis::verifyFunctionExists(const std::string &functionName, uint line,
                                                                            uint col)
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);
        auto calledFunction = scopeManager->getFunctionDeclarationByName(functionName);

        if (!calledFunction)
        {
            // Try to find it as a variable (function pointer)
            auto currentFunction = getCurrentFunction();
            auto variable = currentFunction->findVarAllScopesAndArg(functionName);

            if (variable && variable->type == tokenMap::FUNCTION && variable->function)
            {
                return variable->function;
            }

            throw FunctionNotFoundException(util::format(
                    "Function {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(functionName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        return calledFunction;
    }

    // Helper function to verify if two types match and throw a formatted exception if not
    void SemanticAnalysis::verifyTypesMatch(int typeA, int typeB, const std::string &nameA, const std::string &nameB,
                                            uint line, uint col, const std::string &errorContextMsg) const
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        if (typeA != typeB)
        {
            throw TypeMismatchException(util::format(
                    "{}: {} of type {} is incompatible with {} of type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    errorContextMsg, color::colorText(nameA, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(typeA), color::BOLD_GREEN),
                    color::colorText(nameB, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(typeB), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    // Helper function to determine the type of a value, handling real numbers appropriately
    int SemanticAnalysis::determineValueType(const std::string &value)
    {
        int type = tokenMap::determineType(value);
        if (type == tokenMap::REAL_NUMBER)
        {
            type = tokenMap::determineFloatType(value);
        }
        return type;
    }

    std::shared_ptr<scope::Variable>
    SemanticAnalysis::checkAnotherTypes(const std::string &varName, const std::string &anotherTypeName, const bool mut,
                                        const int line, const std::string &codeLine, const std::string &caretLine) const
    {
        if (const auto structStemt = scopeManager->getStructDeclarationByName(anotherTypeName))
        {
            const auto variable = std::make_shared<scope::Variable>(varName, tokenMap::STRUCT, mut);
            variable->structStemt = structStemt;
            return variable;
        }

        throw TypeNotFoundException(util::format("Undefined type error: The Type '{}' is not defined.\n"
                                                 "Line: {}, Scope: {}\n\n"
                                                 "{}\n"
                                                 "{}\n\n",
                                                 color::colorText(anotherTypeName, color::BOLD_GREEN),
                                                 color::colorText(std::to_string(line), color::YELLOW),
                                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                                 caretLine, codeLine));
    }
} // namespace iron

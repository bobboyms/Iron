#include <antlr4-runtime.h>
#include "../headers/Hlir.h"
#include "../headers/SemanticAnalysis.h"

namespace iron
{
    /**
     * @brief Creates context information for error reporting
     *
     * This function collects all information needed for providing rich error messages,
     * including source code context, line number, and scope name.
     *
     * @param lineNumber Current line number in source code
     * @param columnPosition Current column position in source code
     * @param caretOffset Offset for positioning the caret under the error
     * @return ErrorContext Struct containing all error context information
     */
    ErrorContext SemanticAnalysis::getErrorContext(uint lineNumber, uint columnPosition, int caretOffset)
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, caretOffset);
        return {lineNumber, columnPosition, codeLine, caretLine, scopeManager->currentScopeName()};
    }

    /**
     * @brief Verifies if a variable exists and throws a formatted exception if not
     *
     * Searches for the variable in the current function's scope hierarchy, including
     * arguments and local variables. Throws a detailed exception if not found.
     *
     * @param variableName Name of the variable to verify
     * @param lineNumber Line number where the variable is referenced
     * @param columnPosition Column position where the variable is referenced
     * @param contextInfo Additional context information for error messages
     * @return std::shared_ptr<scope::Variable> The variable if found
     * @throws VariableNotFoundException if the variable does not exist
     */
    std::shared_ptr<scope::Variable> SemanticAnalysis::verifyVariableExists(const std::string &variableName,
                                                                            uint lineNumber, uint columnPosition,
                                                                            const std::string &contextInfo)
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        const auto currentFunction = getCurrentFunction();
        auto variable = currentFunction->findVarAllScopesAndArg(variableName);

        if (!variable)
        {
            throw VariableNotFoundException(
                    util::format("Variable '{}' not found.\n"
                                 "Line: {}, Scope: {}\n\n"
                                 "{}\n"
                                 "{}\n{}",
                                 color::colorText(variableName, color::BOLD_GREEN),
                                 color::colorText(std::to_string(lineNumber), color::YELLOW),
                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                 caretLine, contextInfo.empty() ? "" : "\n\n" + contextInfo));
        }

        return variable;
    }

    /**
     * @brief Verifies if a function exists and throws a formatted exception if not
     *
     * Searches for the function in the global scope. If not found there, checks if it
     * might be a function pointer variable. Throws a detailed exception if not found.
     *
     * @param functionName Name of the function to verify
     * @param lineNumber Line number where the function is called
     * @param columnPosition Column position where the function is called
     * @return std::shared_ptr<scope::Function> The function if found
     * @throws FunctionNotFoundException if the function does not exist
     */
    std::shared_ptr<scope::Function> SemanticAnalysis::verifyFunctionExists(const std::string &functionName,
                                                                            uint lineNumber, uint columnPosition)
    {
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
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
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        return calledFunction;
    }

    /**
     * @brief Verifies if two types match and throws a formatted exception if not
     *
     * Checks type compatibility between two variables or expressions. If types don't match,
     * throws a detailed exception with context information and clear error message.
     *
     * @param typeA First type to compare
     * @param typeB Second type to compare
     * @param nameA Name of first variable/expression
     * @param nameB Name of second variable/expression
     * @param lineNumber Line number where the comparison happens
     * @param columnPosition Column position where the comparison happens
     * @param errorContextMsg Additional context message for the error
     * @throws TypeMismatchException if types don't match
     */
    void SemanticAnalysis::verifyTypesMatch(const int typeA, const int typeB, const std::string &nameA,
                                            const std::string &nameB, uint lineNumber, uint columnPosition,
                                            const std::string &errorContextMsg) const
    {
        if (typeA == typeB)
        {
            return; // Types match, no exception needed
        }

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        throw TypeMismatchException(util::format("{}: {} of type {} is incompatible with {} of type {}.\n"
                                                 "Line: {}, Scope: {}\n\n"
                                                 "{}\n"
                                                 "{}\n",
                                                 errorContextMsg, color::colorText(nameA, color::BOLD_GREEN),
                                                 color::colorText(tokenMap::getTokenText(typeA), color::BOLD_GREEN),
                                                 color::colorText(nameB, color::BOLD_BLUE),
                                                 color::colorText(tokenMap::getTokenText(typeB), color::BOLD_BLUE),
                                                 color::colorText(std::to_string(lineNumber), color::YELLOW),
                                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                                 codeLine, caretLine));
    }

    /**
     * @brief Determines the type of a literal value
     *
     * Analyzes a literal string and determines its Iron language type.
     * Handles special case for floating point numbers to determine precision.
     *
     * @param valueString String representation of the literal
     * @return int Token type representing the value's type
     */
    int SemanticAnalysis::determineValueType(const std::string &valueString)
    {
        const int baseType = tokenMap::determineType(valueString);
        if (baseType == tokenMap::REAL_NUMBER)
        {
            // Determine if this is a float or double based on precision
            return tokenMap::determineFloatType(valueString);
        }
        return baseType;
    }

    /**
     * @brief Validates and creates a variable for custom types like structs
     *
     * Checks if a custom type name is a valid declared type (currently only structs)
     * and creates a properly typed variable if it is. Throws an exception with
     * detailed error information if the type doesn't exist.
     *
     * @param variableName Name for the new variable
     * @param typeName Name of the custom type
     * @param isMutable Whether the variable is mutable
     * @param lineNumber Line number for error reporting
     * @param codeLine Source code line for error reporting
     * @param caretLine Caret line for error reporting
     * @return std::shared_ptr<scope::Variable> The newly created variable
     * @throws TypeNotFoundException if the type doesn't exist
     */
    std::shared_ptr<scope::Variable> SemanticAnalysis::checkAnotherTypes(const std::string &variableName,
                                                                         const std::string &typeName,
                                                                         const bool isMutable, const int lineNumber,
                                                                         const std::string &codeLine,
                                                                         const std::string &caretLine) const
    {
        // Check if it's a struct type
        if (const auto structDefinition = scopeManager->getStructDeclarationByName(typeName))
        {
            auto variable = std::make_shared<scope::Variable>(variableName, tokenMap::STRUCT, isMutable);
            variable->structStemt = structDefinition;
            return variable;
        }

        // Type not found, throw a detailed error
        throw TypeNotFoundException(util::format("Undefined type error: The Type '{}' is not defined.\n"
                                                 "Line: {}, Scope: {}\n\n"
                                                 "{}\n"
                                                 "{}\n\n",
                                                 color::colorText(typeName, color::BOLD_GREEN),
                                                 color::colorText(std::to_string(lineNumber), color::YELLOW),
                                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                                 caretLine, codeLine));
    }

    /**
     * @brief Retrieves the final struct definition and the target field from a nested struct field access.
     *
     * This function resolves a chain of nested field accesses starting from a base variable that is expected to be a
     * struct. The access chain is provided as a vector of TerminalNode pointers, where the first identifier represents
     * the base variable name and subsequent identifiers represent the fields to access. For intermediate identifiers,
     * the accessed field must be of struct type (i.e., must have a valid struct definition) to allow further nested
     * field access.
     *
     * @param identifiers A vector of pointers to TerminalNode objects representing the identifiers in the field access
     * chain. The vector must contain at least two elements: the base variable name and at least one field name.
     *
     * @return A std::pair containing:
     *         - A shared pointer to the struct definition (scope::StructStemt) that contains the final field.
     *         - A shared pointer to the variable (scope::Variable) corresponding to the final field in the access
     * chain.
     *
     * @throws std::invalid_argument if the identifiers vector has fewer than two elements.
     * @throws TypeNotFoundException if the base variable is not of a defined struct type.
     * @throws FieldNotFoundException if a field in the access chain is not found within the current struct.
     * @throws TypeMismatchException if an intermediate field is not of struct type when further nested access is
     * required.
     */
    std::pair<std::shared_ptr<scope::StructStemt>, std::shared_ptr<scope::Variable>>
    SemanticAnalysis::getStructAndField(std::vector<antlr4::tree::TerminalNode *> identifiers)
    {
        const auto function = getCurrentFunction();
        // We must have at least two identifiers: [struct, field] or [struct, field, nested_field, ...]
        if (identifiers.size() < 2)
        {
            throw std::invalid_argument(
                    util::format("Invalid struct field access: expected at least a struct name and field name.",
                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
        }

        // Get the base struct name and prepare to traverse the hierarchy
        std::string baseName = identifiers[0]->getText();

        const auto baseVariable = function->findVarAllScopesAndArg(baseName);
        // Look up the initial struct in the scope
        if (!baseVariable->structStemt)
        {
            auto [caretLine, codeLine] = getCodeLineAndCaretLine(
                    identifiers[0]->getSymbol()->getLine(), identifiers[0]->getSymbol()->getCharPositionInLine(), 0);

            throw TypeNotFoundException(util::format(
                    "Struct '%s' not defined.\n"
                    "Line: %s, Scope: %s\n\n"
                    "%s\n"
                    "%s",
                    color::colorText(baseName, color::BOLD_GREEN),
                    color::colorText(std::to_string(identifiers[0]->getSymbol()->getLine()), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        // For each field in the access chain, traversing the struct hierarchy
        std::shared_ptr<scope::Variable> field;
        std::shared_ptr<scope::StructStemt> lastStruct = baseVariable->structStemt;
        std::string accessPath = baseName;

        // Start from index 1 (first field after struct name)
        for (size_t i = 1; i < identifiers.size(); i++)
        {
            const std::string fieldName = identifiers[i]->getText();
            accessPath += "." + fieldName;

            // Get the field from the current struct
            field = lastStruct->getVarByName(fieldName);

            if (!field)
            {
                auto [caretLine, codeLine] =
                        getCodeLineAndCaretLine(identifiers[i]->getSymbol()->getLine(),
                                                identifiers[i]->getSymbol()->getCharPositionInLine(), 0);

                throw FieldNotFoundException(util::format(
                        "Field '{}' not found in struct '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}",
                        color::colorText(fieldName, color::BOLD_BLUE),
                        color::colorText(lastStruct->name, color::BOLD_GREEN),
                        color::colorText(std::to_string(identifiers[i]->getSymbol()->getLine()), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            // If this is not the last field in the chain, ensure it's a struct for further traversal
            if (i < identifiers.size() - 1)
            {
                if (field->type != tokenMap::STRUCT || !field->structStemt)
                {
                    auto [caretLine, codeLine] =
                            getCodeLineAndCaretLine(identifiers[i]->getSymbol()->getLine(),
                                                    identifiers[i]->getSymbol()->getCharPositionInLine(), 0);

                    throw TypeMismatchException(util::format(
                            "Cannot access field '%s' as a struct: '%s' is not a struct type.\n"
                            "Line: %s, Scope: %s\n\n"
                            "%s\n"
                            "%s",
                            color::colorText(identifiers[i + 1]->getText(), color::BOLD_BLUE),
                            color::colorText(fieldName, color::BOLD_GREEN),
                            color::colorText(std::to_string(identifiers[i]->getSymbol()->getLine()), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }

                // Move to the nested struct for next iteration
                lastStruct = field->structStemt;
            }
        }

        return std::make_pair(lastStruct, field);
    }


} // namespace iron

#include "../headers/Analyser.h"
#include "../headers/SemanticAnalysis.h"

namespace iron
{
    /**
     * @brief Registers a struct declaration in the scope manager
     *
     * First phase of struct processing that registers the struct name
     * in the scope manager. The struct fields are processed in a separate pass.
     *
     * @param ctx The struct statement context from the parser
     */
    void SemanticAnalysis::visitStructDeclaration(IronParser::StructStatementContext *ctx) const
    {
        const auto structName = ctx->IDENTIFIER()->getText();
        const auto structDefinition = std::make_shared<scope::StructStemt>(structName);
        scopeManager->addStructDeclaration(structDefinition);
    }

    /**
     * @brief Processes a struct's body and adds its fields
     *
     * Second phase of struct processing that adds field definitions to a previously
     * registered struct. Extracts field names, types, and mutability flags.
     *
     * @param ctx The struct statement context from the parser
     * @throws std::runtime_error if the struct was not previously registered
     */
    void SemanticAnalysis::visitStructStatement(IronParser::StructStatementContext *ctx) const
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        // Collect field definitions
        std::vector<std::shared_ptr<scope::Variable>> fieldVariables;
        const auto structName = ctx->IDENTIFIER()->getText();

        // Find the struct definition from the first pass
        const auto structDefinition = scopeManager->getStructDeclarationByName(structName);
        if (!structDefinition)
        {
            throw StructNotFoundException(util::format(
                    "Internal error: Struct '{}' not found in scope manager.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(structName, color::BOLD_GREEN),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        // Process each field in the struct body
        for (const auto &structBody: ctx->structBody())
        {
            const auto fieldName = structBody->varName->getText();
            const bool isMutable = structBody->MUT() != nullptr;
            if (structBody->anotherType)
            {
                const auto anotherType = structBody->anotherType->getText();
                const auto anotherStruct = scopeManager->getStructDeclarationByName(anotherType);
                if (!anotherStruct)
                {
                    throw StructNotFoundException(
                            util::format("Internal error: Struct '{}' not found in scope manager.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(anotherType, color::BOLD_GREEN),
                                         color::colorText(std::to_string(lineNumber), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
                auto fieldVariable = std::make_shared<scope::Variable>(fieldName, tokenMap::STRUCT, isMutable);
                fieldVariable->structStemt = anotherStruct;
                fieldVariables.push_back(fieldVariable);

                continue;
            }

            const auto fieldTypeStr = structBody->varTypes()->getText();
            int fieldType = tokenMap::getTokenType(fieldTypeStr);
            auto fieldVariable = std::make_shared<scope::Variable>(fieldName, fieldType, isMutable);

            fieldVariables.push_back(fieldVariable);
        }

        // Set all field variables at once
        structDefinition->setVariables(fieldVariables);
    }

    /**
     * @brief Processes a struct initialization expression
     *
     * Iterates through all field initializations in a struct initialization
     * expression and validates each one.
     *
     * @param ctx The struct initialization context from the parser
     * @param parentStructDef Optional parent struct definition for validation
     */
    void SemanticAnalysis::visitStructInit(IronParser::StructInitContext *ctx,
                                           const std::shared_ptr<scope::StructStemt>& parentStructDef)
    {
        for (const auto &fieldInitialization: ctx->structInitBody())
        {
            visitStructInitBody(fieldInitialization, parentStructDef);
        }
    }

    /**
     * @brief Validates if a field exists in a struct and throws an exception if not
     *
     * @param fieldName The name of the field to check
     * @param parentStructDef The struct definition to check against
     * @param lineNumber The line number for error reporting
     * @param columnPosition The column position for error reporting
     * @throws VariableNotFoundException if the field doesn't exist
     */
    void SemanticAnalysis::validateStructField(const std::string &fieldName,
                                               const std::shared_ptr<scope::StructStemt>& parentStructDef,
                                               const uint lineNumber, const uint columnPosition) const
    {
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        if (const auto field = parentStructDef->getVarByName(fieldName); !field)
        {
            throw FieldNotFoundException(util::format(
                    "Field '{}' not found in struct '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(fieldName, color::BOLD_GREEN),
                    color::colorText(parentStructDef->name, color::BOLD_GREEN),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    /**
     * @brief Validates a literal value assigned to a struct field
     *
     * @param ctx The struct initialization body context
     * @param field The field to validate against
     * @throws TypeMismatchException if the value type doesn't match the field type
     */
    void SemanticAnalysis::validateStructFieldValue(IronParser::StructInitBodyContext *ctx,
                                                     const std::shared_ptr<scope::Variable> &field)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        const auto fieldName = ctx->varName->getText();
        const auto currentFunction = getCurrentFunction();

        if (!ctx->dataFormat())
            return;

        const auto literalValue = ctx->dataFormat()->getText();

        if (const auto valueType = determineValueType(literalValue); valueType != field->type)
        {
            throw TypeMismatchException(util::format(
                    "Type mismatch: field '{}' has type '{}' but assigned value '{}' has type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(fieldName, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                    color::colorText(literalValue, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    /**
     * @brief Generic value validation for struct field assignment
     *
     * @param fieldName The name of the field
     * @param field The field variable
     * @param valueType The type of the value being assigned
     * @param valueDesc Description of the value (for error messages)
     * @param valueTypeDesc Description of the value type (for error messages)
     * @param lineNumber Line number for error reporting
     * @param columnPosition Column position for error reporting
     * @throws TypeMismatchException if the value type doesn't match the field type
     */
    void SemanticAnalysis::validateStructFieldAssignment(const std::string &fieldName,
                                                   const std::shared_ptr<scope::Variable> &field, const int valueType,
                                                   const std::string &valueDesc, const std::string &valueTypeDesc,
                                                   const uint lineNumber, const uint columnPosition)
    {
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        const auto currentFunction = getCurrentFunction();

        if (valueType != field->type)
        {
            throw TypeMismatchException(util::format(
                    "Type mismatch: field '{}' has type '{}' but {} '{}' has type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(fieldName, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN), valueDesc,
                    color::colorText(valueTypeDesc, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    /**
     * @brief Validates nested struct field values against their types
     *
     * @param ctx The struct initialization context
     * @param field The field containing the struct
     * @throws Various exceptions for type mismatches
     */
    void SemanticAnalysis::validateNestedStructValues(IronParser::StructInitContext *ctx,
                                                      const std::shared_ptr<scope::Variable>& field)
    {
        // Verify field is a struct type
        if (!field->structStemt)
        {
            const auto lineNumber = ctx->getStart()->getLine();
            const auto columnPosition = ctx->getStart()->getCharPositionInLine();
            auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

            throw TypeNotFoundException(util::format(
                    "Field '{}' is not a struct type but is being initialized as a struct.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(field->name, color::BOLD_GREEN),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        // Verify direct literal field values in the nested struct before recursing
        for (const auto &nestedFieldCtx: ctx->structInitBody())
        {
            const auto nestedFieldName = nestedFieldCtx->varName->getText();

            // Field existence will be checked by the recursive call, but we check literal value types here
            if (auto nestedField = field->structStemt->getVarByName(nestedFieldName);
                nestedField && nestedFieldCtx->dataFormat())
            {
                validateStructFieldValue(nestedFieldCtx, nestedField);
            }
        }
    }

    /**
     * @brief Finds the parent struct definition for a nested struct initialization
     *
     * @param ctx The struct initialization body context
     * @return std::shared_ptr<scope::StructStemt> The parent struct definition or nullptr if not found
     */
    std::shared_ptr<scope::StructStemt>
    SemanticAnalysis::findParentStructDefForNestedInit(IronParser::StructInitBodyContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        // Find the parent context to determine which struct this is part of
        if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent->parent))
        {
            // Direct initialization in a variable declaration
            const auto variableName = varDeclaration->varName->getText();

            if (auto parentStructVar = getCurrentFunction()->findVarAllScopesAndArg(variableName);
                parentStructVar && parentStructVar->structStemt)
            {
                return parentStructVar->structStemt;
            }
        }
        else if (const auto structInitBodyCtx = dynamic_cast<IronParser::StructInitBodyContext *>(ctx->parent->parent))
        {
            // Nested struct field in another struct initialization
            const auto parentFieldName = structInitBodyCtx->varName->getText();

            // Find the parent struct variable
            if (const auto grandParentCtx =
                        dynamic_cast<IronParser::VarDeclarationContext *>(structInitBodyCtx->parent->parent->parent))
            {
                const auto rootVarName = grandParentCtx->varName->getText();

                if (auto rootStructVar = getCurrentFunction()->findVarAllScopesAndArg(rootVarName);
                    rootStructVar && rootStructVar->structStemt)
                {
                    // Get the parent field which should be a struct type
                    if (auto parentField = rootStructVar->structStemt->getVarByName(parentFieldName);
                        parentField && parentField->structStemt)
                    {
                        return parentField->structStemt;
                    }
                }
            }
            else
            {
                // Handle deeper nesting by recursively finding the parent struct
                auto currentCtx = structInitBodyCtx;
                std::vector<std::string> fieldPath;
                fieldPath.push_back(parentFieldName);

                // Traverse up the context tree to find the root variable declaration
                while (currentCtx != nullptr)
                {
                    if (auto parentStructCtx =
                                dynamic_cast<IronParser::StructInitBodyContext *>(currentCtx->parent->parent))
                    {
                        fieldPath.push_back(parentStructCtx->varName->getText());
                        currentCtx = parentStructCtx;
                    }
                    else if (auto varDeclCtx = dynamic_cast<IronParser::VarDeclarationContext *>(
                                     currentCtx->parent->parent->parent))
                    {
                        // Found the root variable
                        const auto rootVarName = varDeclCtx->varName->getText();

                        if (auto rootVar = getCurrentFunction()->findVarAllScopesAndArg(rootVarName);
                            rootVar && rootVar->structStemt)
                        {
                            // Now we traverse down the field path to find the correct struct field
                            auto currentStruct = rootVar->structStemt;

                            // Reverse the path since we collected it from leaf to root
                            std::reverse(fieldPath.begin(), fieldPath.end());

                            // Follow the path except for the last element (which is the current field)
                            for (size_t i = 0; i < fieldPath.size() - 1; i++)
                            {
                                if (auto field = currentStruct->getVarByName(fieldPath[i]); field && field->structStemt)
                                {
                                    currentStruct = field->structStemt;
                                }
                                else
                                {
                                    // Path is invalid
                                    break;
                                }
                            }

                            return currentStruct;
                        }
                        break;
                    }
                    else
                    {
                        break; // Unknown parent context type
                    }
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief Processes direct struct initialization in a variable declaration
     *
     * @param ctx The struct initialization body context
     * @param variableName The name of the variable being initialized
     * @param structVariable The struct variable
     */
    void SemanticAnalysis::processDirectStructInitialization(IronParser::StructInitBodyContext *ctx,
                                                             const std::string &variableName,
                                                             const std::shared_ptr<scope::Variable> &structVariable)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        const auto fieldName = ctx->varName->getText();

        // Find the field in the struct
        const auto field = structVariable->structStemt->getVarByName(fieldName);
        if (!field)
        {
            throw FieldNotFoundException(util::format(
                    "Field '{}' not found in struct '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(fieldName, color::BOLD_GREEN),
                    color::colorText(structVariable->structStemt->name, color::BOLD_GREEN),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        // Handle different kinds of field initializers
        if (ctx->dataFormat())
        {
            // Literal value initialization
            validateStructFieldValue(ctx, field);
        }
        else if (ctx->anotherVarName)
        {
            // Variable-to-field assignment
            const std::string sourceVarName = ctx->anotherVarName->getText();
            const auto sourceVariable = verifyVariableExists(
                    sourceVarName, lineNumber, columnPosition,
                    "Hint: The variable must be declared before using it in a struct initialization.");

            validateStructFieldAssignment(fieldName, field, sourceVariable->type, "variable", sourceVarName, lineNumber,
                                    columnPosition);
        }
        else if (ctx->functionCall())
        {
            // Function call result assignment
            const std::string functionName = ctx->functionCall()->functionName->getText();
            const auto function = verifyFunctionExists(functionName, lineNumber, columnPosition);

            validateStructFieldAssignment(fieldName, field, function->getReturnType(), "function", functionName, lineNumber,
                                    columnPosition);

            // Process the function call
            visitFunctionCall(ctx->functionCall());
        }
        else if (ctx->arrowFunctionInline())
        {
            // Arrow function assignment

            // For functions, we have special handling
            if (const auto arrowFunction = visitArrowFunctionInline(ctx->arrowFunctionInline());
                field->type != tokenMap::FUNCTION && field->type != arrowFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch: field '{}' has type '{}' but arrow function returns type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(fieldName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(arrowFunction->getReturnType()), color::BOLD_BLUE),
                        color::colorText(std::to_string(lineNumber), color::YELLOW),
                        color::colorText(getCurrentFunction()->getFunctionName(), color::BOLD_YELLOW), codeLine,
                        caretLine));
            }
        }
    }

    /**
     * @brief Processes a nested struct field initialization within another struct
     *
     * @param ctx The struct initialization body context
     */
    void SemanticAnalysis::processNestedStructFieldInit(IronParser::StructInitBodyContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        const auto fieldName = ctx->varName->getText();

        // Find the parent struct initialization context
        if (auto parentStructInitBody = dynamic_cast<IronParser::StructInitBodyContext *>(ctx->parent->parent);
            !parentStructInitBody)
            return;

        // Find the root struct variable
        auto rootCtx = ctx;
        std::vector<std::string> fieldPath;
        fieldPath.push_back(fieldName);

        // Build the field path from current to root
        while (true)
        {
            auto parentBodyCtx = dynamic_cast<IronParser::StructInitBodyContext *>(rootCtx->parent->parent);
            if (!parentBodyCtx)
                break;

            fieldPath.push_back(parentBodyCtx->varName->getText());
            rootCtx = parentBodyCtx;
        }

        // Find the variable declaration at the root
        if (auto varDeclCtx = dynamic_cast<IronParser::VarDeclarationContext *>(rootCtx->parent->parent->parent))
        {
            const auto rootVarName = varDeclCtx->varName->getText();

            if (auto rootVar = getCurrentFunction()->findVarAllScopesAndArg(rootVarName);
                rootVar && rootVar->structStemt)
            {
                // Now navigate down the struct hierarchy
                std::reverse(fieldPath.begin(), fieldPath.end());

                std::shared_ptr<scope::StructStemt> currentStruct = rootVar->structStemt;
                std::shared_ptr<scope::Variable> currentField = nullptr;

                // Follow the path to find the correct field and parent struct
                for (size_t i = 0; i < fieldPath.size() - 1; i++)
                {
                    currentField = currentStruct->getVarByName(fieldPath[i]);
                    if (!currentField || !currentField->structStemt)
                    {
                        auto [codeLine, caretLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
                        throw TypeNotFoundException(
                                util::format("Field '{}' is not a struct type but is being initialized as a struct.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(fieldPath[i], color::BOLD_GREEN),
                                             color::colorText(std::to_string(lineNumber), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                    }
                    currentStruct = currentField->structStemt;
                }

                // Now validate the current field initialization
                if (ctx->dataFormat())
                {
                    // Literal value initialization
                    const auto field = currentStruct->getVarByName(fieldPath.back());
                    if (!field)
                    {
                        throw FieldNotFoundException(
                                util::format("Field '{}' not found in struct '{}'.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(fieldPath.back(), color::BOLD_GREEN),
                                             color::colorText(currentStruct->name, color::BOLD_GREEN),
                                             color::colorText(std::to_string(lineNumber), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                    }

                    validateStructFieldValue(ctx, field);
                }
                else if (ctx->anotherVarName)
                {
                    // Handle variable assignment
                    const std::string sourceVarName = ctx->anotherVarName->getText();
                    auto sourceVariable = verifyVariableExists(
                            sourceVarName, lineNumber, columnPosition,
                            "Hint: The variable must be declared before using it in a struct initialization.");

                    // Find the field in the current struct
                    const auto field = currentStruct->getVarByName(fieldPath.back());
                    if (!field)
                    {
                        throw FieldNotFoundException(
                                util::format("Field '{}' not found in struct '{}'.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(fieldPath.back(), color::BOLD_GREEN),
                                             color::colorText(currentStruct->name, color::BOLD_GREEN),
                                             color::colorText(std::to_string(lineNumber), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                    }

                    validateStructFieldAssignment(fieldPath.back(), field, sourceVariable->type, "variable", sourceVarName,
                                            lineNumber, columnPosition);
                }
                // Similar handlers for function calls and arrow functions would go here
            }
        }
    }

    /**
     * @brief Processes a single field initialization in a struct initializer
     *
     * Validates that the field exists in the struct and that the assigned value
     * has a compatible type. Handles different kinds of value expressions including
     * literals, variables, function calls, and arrow functions.
     *
     * @param ctx The struct initialization body context from the parser
     * @param parentStructDef Optional parent struct definition for validation
     * @throws Various exceptions for type mismatches and undefined field errors
     */
    void SemanticAnalysis::visitStructInitBody(IronParser::StructInitBodyContext *ctx,
                                               std::shared_ptr<scope::StructStemt> parentStructDef)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        const auto fieldName = ctx->varName->getText();

        // If we have a parent struct definition, validate the field exists in it
        if (parentStructDef)
        {
            // Validate field exists in parent struct
            const auto field = parentStructDef->getVarByName(fieldName);
            validateStructField(fieldName, parentStructDef, lineNumber, columnPosition);

            // Check literal value type
            if (ctx->dataFormat())
            {
                validateStructFieldValue(ctx, field);
            }
        }

        // Process nested struct initialization
        if (ctx->structInit())
        {
            // If we don't already have a parent struct definition, try to find it
            if (!parentStructDef)
            {
                parentStructDef = findParentStructDefForNestedInit(ctx);
            }

            // Verify the field exists in the parent struct and is a struct type
            if (parentStructDef)
            {
                // Validate field exists in parent struct
                validateStructField(fieldName, parentStructDef, lineNumber, columnPosition);
                const auto field = parentStructDef->getVarByName(fieldName);

                // Validate nested field has struct type and check value types
                validateNestedStructValues(ctx->structInit(), field);

                // Process the nested struct initialization with the correct struct type
                visitStructInit(ctx->structInit(), field->structStemt);
            }
            else
            {
                // If we couldn't determine the parent struct, just process without validation
                visitStructInit(ctx->structInit(), nullptr);
            }
            return;
        }

        // Find the variable declaration this initialization belongs to
        if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent->parent))
        {
            // Get the struct variable being initialized
            const auto variableName = varDeclaration->varName->getText();
            const auto structVariable = getCurrentFunction()->findVarAllScopesAndArg(variableName);

            if (!structVariable)
            {
                auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
                throw VariableNotFoundException(util::format(
                        "Variable '{}' not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(variableName, color::BOLD_GREEN),
                        color::colorText(std::to_string(lineNumber), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            // Verify the variable is a struct
            if (!structVariable->structStemt)
            {
                auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
                throw TypeNotFoundException(util::format(
                        "The variable '{}' is not a struct type.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(variableName, color::BOLD_GREEN), color::colorText("struct", color::BOLD_BLUE),
                        color::colorText(std::to_string(lineNumber), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            // Process the direct struct initialization with different field initializers
            processDirectStructInitialization(ctx, variableName, structVariable);
        }
        else
        {
            // This is a nested struct initialization in another struct init
            processNestedStructFieldInit(ctx);
        }
    }
} // namespace iron

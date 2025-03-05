#include "../headers/Analyser.h"
#include "../headers/Files.h"
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
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();

        // Create the struct definition and register it
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
    void SemanticAnalysis::visitStructInit(IronParser::StructInitContext *ctx, std::shared_ptr<scope::StructStemt> parentStructDef)
    {
        for (const auto &fieldInitialization: ctx->structInitBody())
        {
            visitStructInitBody(fieldInitialization, parentStructDef);
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
    void SemanticAnalysis::visitStructInitBody(IronParser::StructInitBodyContext *ctx, std::shared_ptr<scope::StructStemt> parentStructDef)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        // Get field name and current function context
        const auto fieldName = ctx->varName->getText();
        const auto currentFunction = getCurrentFunction();
        
        // If we have a parent struct definition, validate the field exists in it
        if (parentStructDef) {
            auto field = parentStructDef->getVarByName(fieldName);
            if (!field) {
                throw VariableNotFoundException(
                        util::format("Field '{}' not found in struct '{}'.\n"
                                    "Line: {}, Scope: {}\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(fieldName, color::BOLD_GREEN),
                                    color::colorText(parentStructDef->name, color::BOLD_GREEN),
                                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                    codeLine, caretLine));
            }
            
            // Add type checking for direct value assignments
            if (ctx->dataFormat()) {
                const auto literalValue = ctx->dataFormat()->getText();
                auto valueType = determineValueType(literalValue);
                
                if (valueType != field->type) {
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
                        color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW),
                        codeLine, caretLine));
                }
            }
        }

        // Process nested struct initialization
        if (ctx->structInit())
        {
            // If we already have a parent struct definition passed in, use it directly
            if (!parentStructDef) {
                // Handle nested struct initialization
                std::shared_ptr<scope::Variable> parentStructVar = nullptr;
                
                // Find the parent context to determine which struct this is part of
                if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent->parent))
                {
                    // Direct initialization in a variable declaration
                    const auto variableName = varDeclaration->varName->getText();
                    parentStructVar = getCurrentFunction()->findVarAllScopesAndArg(variableName);
                    
                    if (parentStructVar && parentStructVar->structStemt) {
                        parentStructDef = parentStructVar->structStemt;
                    }
                }
                else if (const auto structInitBodyCtx = dynamic_cast<IronParser::StructInitBodyContext *>(ctx->parent->parent))
                {
                    // Nested struct field in another struct initialization
                    const auto parentFieldName = structInitBodyCtx->varName->getText();
                    
                    // Find the parent struct variable
                    if (const auto grandParentCtx = dynamic_cast<IronParser::VarDeclarationContext *>(
                            structInitBodyCtx->parent->parent->parent))
                    {
                        const auto rootVarName = grandParentCtx->varName->getText();
                        auto rootStructVar = getCurrentFunction()->findVarAllScopesAndArg(rootVarName);
                        
                        if (rootStructVar && rootStructVar->structStemt) {
                            // Get the parent field which should be a struct type
                            auto parentField = rootStructVar->structStemt->getVarByName(parentFieldName);
                            if (parentField && parentField->structStemt) {
                                parentStructDef = parentField->structStemt;
                            }
                        }
                    }
                    else {
                        // Handle deeper nesting by recursively finding the parent struct
                        auto currentCtx = structInitBodyCtx;
                        std::vector<std::string> fieldPath;
                        fieldPath.push_back(parentFieldName);
                        
                        // Traverse up the context tree to find the root variable declaration
                        while (currentCtx != nullptr) {
                            if (auto parentStructCtx = dynamic_cast<IronParser::StructInitBodyContext *>(
                                    currentCtx->parent->parent)) {
                                fieldPath.push_back(parentStructCtx->varName->getText());
                                currentCtx = parentStructCtx;
                            }
                            else if (auto varDeclCtx = dynamic_cast<IronParser::VarDeclarationContext *>(
                                    currentCtx->parent->parent->parent)) {
                                // Found the root variable
                                const auto rootVarName = varDeclCtx->varName->getText();
                                auto rootVar = getCurrentFunction()->findVarAllScopesAndArg(rootVarName);
                                
                                if (rootVar && rootVar->structStemt) {
                                    // Now we traverse down the field path to find the correct struct field
                                    auto currentStruct = rootVar->structStemt;
                                    
                                    // Reverse the path since we collected it from leaf to root
                                    std::reverse(fieldPath.begin(), fieldPath.end());
                                    
                                    // Follow the path except for the last element (which is the current field)
                                    for (size_t i = 0; i < fieldPath.size() - 1; i++) {
                                        auto field = currentStruct->getVarByName(fieldPath[i]);
                                        if (field && field->structStemt) {
                                            currentStruct = field->structStemt;
                                        }
                                        else {
                                            // Path is invalid
                                            break;
                                        }
                                    }
                                    
                                    parentStructDef = currentStruct;
                                }
                                break;
                            }
                            else {
                                break; // Unknown parent context type
                            }
                        }
                    }
                }
            }
            
            // Verify the field exists in the parent struct and is a struct type
            if (parentStructDef) {
                auto field = parentStructDef->getVarByName(fieldName);
                if (!field) {
                    throw VariableNotFoundException(
                            util::format("Field '{}' not found in struct '{}'.\n"
                                        "Line: {}, Scope: {}\n\n"
                                        "{}\n"
                                        "{}\n",
                                        color::colorText(fieldName, color::BOLD_GREEN),
                                        color::colorText(parentStructDef->name, color::BOLD_GREEN),
                                        color::colorText(std::to_string(lineNumber), color::YELLOW),
                                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                        codeLine, caretLine));
                }
                
                // Verify field is a struct type
                if (!field->structStemt) {
                    throw TypeNotFoundException(util::format(
                            "Field '{}' is not a struct type but is being initialized as a struct.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(fieldName, color::BOLD_GREEN),
                            color::colorText(std::to_string(lineNumber), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                            codeLine, caretLine));
                }
                
                // Verify direct literal field values in the nested struct before recursing
                for (const auto &nestedFieldCtx : ctx->structInit()->structInitBody()) {
                    const auto nestedFieldName = nestedFieldCtx->varName->getText();
                    auto nestedField = field->structStemt->getVarByName(nestedFieldName);
                    
                    // Field existence will be checked by the recursive call, but we check literal value types here
                    if (nestedField && nestedFieldCtx->dataFormat()) {
                        const auto literalValue = nestedFieldCtx->dataFormat()->getText();
                        auto valueType = determineValueType(literalValue);
                        
                        if (valueType != nestedField->type) {
                            throw TypeMismatchException(util::format(
                                "Type mismatch: field '{}' has type '{}' but assigned value '{}' has type '{}'.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n"
                                "{}\n",
                                color::colorText(nestedFieldName, color::BOLD_GREEN),
                                color::colorText(tokenMap::getTokenText(nestedField->type), color::BOLD_GREEN),
                                color::colorText(literalValue, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                                color::colorText(std::to_string(nestedFieldCtx->getStart()->getLine()), color::YELLOW),
                                color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW),
                                codeLine, caretLine));
                        }
                    }
                }
                
                // Pass the field's struct definition to the nested struct initialization
                // This is the key fix - ensures field validation uses the correct struct type
                visitStructInit(ctx->structInit(), field->structStemt);
            } else {
                // If we couldn't determine the parent struct, just process the init without validation
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
                throw TypeNotFoundException(util::format(
                        "The variable '{}' is not a struct type.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(variableName, color::BOLD_GREEN), color::colorText("struct", color::BOLD_BLUE),
                        color::colorText(std::to_string(lineNumber), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            // Handle different kinds of field initializers
            if (ctx->dataFormat())
            {
                // Literal value initialization
                const auto literalValue = ctx->dataFormat()->getText();
                auto valueType = determineValueType(literalValue);

                // Find the field in the struct
                const auto field = structVariable->structStemt->getVarByName(fieldName);
                if (!field)
                {
                    throw VariableNotFoundException(
                            util::format("Field '{}' not found in struct '{}'.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(fieldName, color::BOLD_GREEN),
                                         color::colorText(structVariable->structStemt->name, color::BOLD_GREEN),
                                         color::colorText(std::to_string(lineNumber), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                if (valueType != field->type)
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
                            color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
            else if (ctx->anotherVarName)
            {
                // Variable-to-field assignment
                const std::string sourceVarName = ctx->anotherVarName->getText();
                auto sourceVariable = verifyVariableExists(
                        sourceVarName, lineNumber, columnPosition,
                        "Hint: The variable must be declared before using it in a struct initialization.");

                // Find the field in the struct
                const auto field = structVariable->structStemt->getVarByName(fieldName);
                if (!field)
                {
                    throw VariableNotFoundException(
                            util::format("Field '{}' not found in struct '{}'.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(fieldName, color::BOLD_GREEN),
                                         color::colorText(structVariable->structStemt->name, color::BOLD_GREEN),
                                         color::colorText(std::to_string(lineNumber), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                // Verify type compatibility
                if (sourceVariable->type != field->type)
                {
                    throw TypeMismatchException(util::format(
                            "Type mismatch: field '{}' has type '{}' but variable '{}' has type '{}'.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(fieldName, color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                            color::colorText(sourceVarName, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(sourceVariable->type), color::BOLD_BLUE),
                            color::colorText(std::to_string(lineNumber), color::YELLOW),
                            color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
            else if (ctx->functionCall())
            {
                // Function call result assignment
                const std::string functionName = ctx->functionCall()->functionName->getText();
                auto function = verifyFunctionExists(functionName, lineNumber, columnPosition);

                // Find the field in the struct
                const auto field = structVariable->structStemt->getVarByName(fieldName);
                if (!field)
                {
                    throw VariableNotFoundException(
                            util::format("Field '{}' not found in struct '{}'.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(fieldName, color::BOLD_GREEN),
                                         color::colorText(structVariable->structStemt->name, color::BOLD_GREEN),
                                         color::colorText(std::to_string(lineNumber), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                // Verify type compatibility
                if (function->getReturnType() != field->type)
                {
                    throw TypeMismatchException(util::format(
                            "Type mismatch: field '{}' has type '{}' but function '{}' returns type '{}'.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(fieldName, color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                            color::colorText(functionName, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(function->getReturnType()), color::BOLD_BLUE),
                            color::colorText(std::to_string(lineNumber), color::YELLOW),
                            color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }

                // Process the function call
                visitFunctionCall(ctx->functionCall());
            }
            else if (ctx->arrowFunctionInline())
            {
                // Arrow function assignment
                auto arrowFunction = visitArrowFunctionInline(ctx->arrowFunctionInline());

                // Find the field in the struct
                const auto field = structVariable->structStemt->getVarByName(fieldName);
                if (!field)
                {
                    throw VariableNotFoundException(
                            util::format("Field '{}' not found in struct '{}'.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(fieldName, color::BOLD_GREEN),
                                         color::colorText(structVariable->structStemt->name, color::BOLD_GREEN),
                                         color::colorText(std::to_string(lineNumber), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                // Verify type compatibility - for functions we may need special handling
                if (field->type != tokenMap::FUNCTION && field->type != arrowFunction->getReturnType())
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
                            color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
        }
        else
        {
            // This is a nested struct initialization in another struct init
            
            // Find the parent struct initialization context
            auto parentStructInitBody = dynamic_cast<IronParser::StructInitBodyContext *>(ctx->parent->parent);
            if (parentStructInitBody) {
                const auto parentFieldName = parentStructInitBody->varName->getText();
                
                // Find the root struct variable
                auto rootCtx = ctx;
                std::vector<std::string> fieldPath;
                fieldPath.push_back(fieldName);
                
                // Build the field path from current to root
                while (true) {
                    auto parentBodyCtx = dynamic_cast<IronParser::StructInitBodyContext *>(rootCtx->parent->parent);
                    if (!parentBodyCtx) break;
                    
                    fieldPath.push_back(parentBodyCtx->varName->getText());
                    rootCtx = parentBodyCtx;
                }
                
                // Find the variable declaration at the root
                if (auto varDeclCtx = dynamic_cast<IronParser::VarDeclarationContext *>(
                        rootCtx->parent->parent->parent)) {
                    const auto rootVarName = varDeclCtx->varName->getText();
                    auto rootVar = getCurrentFunction()->findVarAllScopesAndArg(rootVarName);
                    
                    if (rootVar && rootVar->structStemt) {
                        // Now navigate down the struct hierarchy
                        std::reverse(fieldPath.begin(), fieldPath.end());
                        
                        std::shared_ptr<scope::StructStemt> currentStruct = rootVar->structStemt;
                        std::shared_ptr<scope::Variable> currentField = nullptr;
                        
                        // Follow the path to find the correct field and parent struct
                        for (size_t i = 0; i < fieldPath.size() - 1; i++) {
                            currentField = currentStruct->getVarByName(fieldPath[i]);
                            if (!currentField || !currentField->structStemt) {
                                throw TypeNotFoundException(util::format(
                                    "Field '{}' is not a struct type but is being initialized as a struct.\n"
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
                        if (ctx->dataFormat()) {
                            // Literal value initialization
                            const auto literalValue = ctx->dataFormat()->getText();
                            auto valueType = determineValueType(literalValue);
                            
                            // Find the field in the current struct
                            const auto field = currentStruct->getVarByName(fieldPath.back());
                            if (!field) {
                                throw VariableNotFoundException(
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
                            
                            if (valueType != field->type) {
                                throw TypeMismatchException(util::format(
                                    "Type mismatch: field '{}' has type '{}' but assigned value '{}' has type '{}'.\n"
                                    "Line: {}, Scope: {}\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(fieldPath.back(), color::BOLD_GREEN),
                                    color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                                    color::colorText(literalValue, color::BOLD_BLUE),
                                    color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                                    color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW),
                                    codeLine, caretLine));
                            }
                        }
                        else if (ctx->anotherVarName) {
                            // Handle variable assignment similar to above
                            const std::string sourceVarName = ctx->anotherVarName->getText();
                            auto sourceVariable = verifyVariableExists(
                                sourceVarName, lineNumber, columnPosition,
                                "Hint: The variable must be declared before using it in a struct initialization.");
                                
                            // Find the field in the current struct
                            const auto field = currentStruct->getVarByName(fieldPath.back());
                            if (!field) {
                                throw VariableNotFoundException(
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
                            
                            if (sourceVariable->type != field->type) {
                                throw TypeMismatchException(util::format(
                                    "Type mismatch: field '{}' has type '{}' but variable '{}' has type '{}'.\n"
                                    "Line: {}, Scope: {}\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(fieldPath.back(), color::BOLD_GREEN),
                                    color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                                    color::colorText(sourceVarName, color::BOLD_BLUE),
                                    color::colorText(tokenMap::getTokenText(sourceVariable->type), color::BOLD_BLUE),
                                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                                    color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW),
                                    codeLine, caretLine));
                            }
                        }
                        // Similar checks for function calls and arrow functions would go here
                    }
                }
            }
        }
    }
} // namespace iron

//
// Created by Thiago Rodrigues on 12/03/25.
//
#include "../headers/Analyser.h"
#include "../headers/SemanticAnalysis.h"


namespace iron
{
    void SemanticAnalysis::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();

        // Obter contexto para mensagens de erro
        const auto errorCtx = getErrorContext(line, col, 0);
        const std::string &codeLine = errorCtx.codeLine;
        const std::string &caretLine = errorCtx.caretLine;

        // Obter nome da variável e verificar se ela existe
        const std::string varName = ctx->variableQualifiedName()->base->getText();
        auto variable = verifyVariableExists(
                varName, line, col,
                "Hint: Check for typos in the variable name or declare the variable before using it.");

        // Verificar se a variável é mutável
        if (!variable->mut)
        {
            throw VariableCannotBeChangedException(util::format(
                    "Immutable variable error: Cannot assign a new value to '{}' because it is immutable.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: Add the '{}' keyword before 'let' in the variable's declaration to make it mutable: '{}let "
                    "{} = ...'",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(errorCtx.scopeName, color::BOLD_YELLOW), caretLine, codeLine,
                    color::colorText("mut", color::BOLD_BLUE), color::colorText("mut ", color::BOLD_BLUE),
                    color::colorText(varName, color::BOLD_GREEN)));
        }

        // Delegar o tratamento conforme o tipo de atribuição
        if (ctx->structInit())
        {
            handleStructInitialization(ctx, variable, line, col, codeLine, caretLine);
        }
        else if (ctx->anotherVarName)
        {
            handleAnotherVarAssignment(ctx, variable, line, col, codeLine, caretLine);
        }
        else if (ctx->dataFormat())
        {
            handleDataFormatAssignment(ctx, variable, line, col, codeLine, caretLine);
        }
        else if (ctx->functionCall())
        {
            handleFunctionCallAssignment(ctx, variable, line, col, codeLine, caretLine);
        }
        else if (ctx->arrowFunctionInline())
        {
            handleArrowFunctionAssignment(ctx, variable, line, col, codeLine, caretLine);
        }
        else if (ctx->expr())
        {
            handleExpressionAssignment(ctx, variable, line, col, codeLine, caretLine);
        }
    }

    // Tratamento para inicialização de struct
    void SemanticAnalysis::handleStructInitialization(IronParser::VarAssignmentContext *ctx,
                                                      const std::shared_ptr<scope::Variable> &variable, const uint line,
                                                      const uint col, const std::string &codeLine,
                                                      const std::string &caretLine)
    {
        // Verifica se há qualificação (atribuição a campo de struct)
        if (!ctx->variableQualifiedName()->rest.empty())
        {
            auto [parentStructDef, field] = getStructAndField(ctx->variableQualifiedName());

            // Verifica se o campo é mutável
            if (!field->mut)
            {
                throw VariableCannotBeChangedException(util::format(
                        "Immutable field error: Cannot assign a new value to field '{}' because it is immutable.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: Add the '{}' keyword before the field name in the struct definition to make it mutable",
                        color::colorText(field->name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                        color::colorText("mut", color::BOLD_BLUE)));
            }

            // Verifica se o campo é de tipo struct
            if (!field->structStemt)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign a struct value to field '{}' which is not a struct type.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The field must be of a struct type to receive a struct initialization.",
                        color::colorText(field->name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            visitStructInit(ctx->structInit(), field->structStemt);
        }
        else
        {
            // Inicialização de struct para a própria variável
            if (!variable->structStemt)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign a struct value to variable '{}' which is not a struct "
                        "type.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The variable must be declared as a struct type to receive a struct initialization.",
                        color::colorText(variable->name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            visitStructInit(ctx->structInit(), variable->structStemt);
        }
    }

    // Tratamento para atribuição via outra variável
    void SemanticAnalysis::handleAnotherVarAssignment(IronParser::VarAssignmentContext *ctx,
                                                      const std::shared_ptr<scope::Variable> &variable, const uint line,
                                                      const uint col, const std::string &codeLine,
                                                      const std::string &caretLine)
    {
        const std::string anotherVarName = ctx->anotherVarName->getText();
        auto anotherVariable = verifyVariableExists(
                anotherVarName, line, col,
                "Hint: Check for typos in the variable name or declare the variable before using it.");

        // Verifica se os tipos são compatíveis
        verifyTypesMatch(variable->type, anotherVariable->type, variable->name, anotherVarName, line, col,
                         "Type mismatch error: Cannot assign a value of type to a variable of type");
    }

    // Tratamento para atribuição de valor literal
    void SemanticAnalysis::handleDataFormatAssignment(IronParser::VarAssignmentContext *ctx,
                                                      const std::shared_ptr<scope::Variable> &variable, const uint line,
                                                      const uint col, const std::string &codeLine,
                                                      const std::string &caretLine)
    {
        const std::string value = ctx->dataFormat()->getText();

        if (!ctx->variableQualifiedName()->rest.empty())
        {
            // Atribuição a campo de struct
            auto [structDef, field] = getStructAndField(ctx->variableQualifiedName());
            if (!field->mut)
            {
                throw VariableCannotBeChangedException(util::format(
                        "Immutable field error: Cannot assign a new value to field '{}' because it is immutable.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: Add the '{}' keyword before the field name in the struct definition to make it mutable",
                        color::colorText(field->name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                        color::colorText("mut", color::BOLD_BLUE)));
            }

            if (const int valueType = determineValueType(value); field->type != valueType)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign a value of type '{}' to a field of type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The literal '{}' (type: {}) cannot be assigned to field '{}' (type: {}). Use the "
                        "correct type or cast the value.",
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                        color::colorText(value, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(field->name, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN)));
            }
        }
        else
        {
            // Atribuição literal à variável
            if (const int valueType = determineValueType(value); variable->type != valueType)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign a value of type '{}' to a variable of type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The literal '{}' (type: {}) cannot be assigned to variable '{}' (type: {}). Use the "
                        "correct type or cast the value.",
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                        color::colorText(value, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(variable->name, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN)));
            }
        }
    }

    // Tratamento para atribuição via chamada de função
    void SemanticAnalysis::handleFunctionCallAssignment(IronParser::VarAssignmentContext *ctx,
                                                        const std::shared_ptr<scope::Variable> &variable, const uint line,
                                                        const uint col, const std::string &codeLine,
                                                        const std::string &caretLine)
    {
        const std::string functionName = ctx->functionCall()->functionName->getText();
        if (const auto calledFunction = verifyFunctionExists(functionName, line, col);
            variable->type != calledFunction->getReturnType())
        {
            throw TypeMismatchException(util::format(
                    "Type mismatch error: Cannot assign result of function '{}' returning type '{}' to variable '{}' "
                    "of type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: Function return type and variable type must match for assignment.",
                    color::colorText(functionName, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
                    color::colorText(variable->name, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
        visitFunctionCall(ctx->functionCall());
    }

    // Tratamento para atribuição via arrow function
    void SemanticAnalysis::handleArrowFunctionAssignment(IronParser::VarAssignmentContext *ctx,
                                                         const std::shared_ptr<scope::Variable> &variable, const uint line,
                                                         const uint col, const std::string &codeLine,
                                                         const std::string &caretLine)
    {
        auto arrowFunction = visitArrowFunctionInline(ctx->arrowFunctionInline());
        if (variable->type != arrowFunction->getReturnType() && variable->type != tokenMap::FUNCTION)
        {
            throw TypeMismatchException(util::format(
                    "Type mismatch error: Cannot assign a function returning type '{}' to variable '{}' of type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: Variable type must be 'function' or match the function's return type.",
                    color::colorText(tokenMap::getTokenText(arrowFunction->getReturnType()), color::BOLD_BLUE),
                    color::colorText(variable->name, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    // Tratamento para atribuição via expressão
    void SemanticAnalysis::handleExpressionAssignment(IronParser::VarAssignmentContext *ctx,
                                                      const std::shared_ptr<scope::Variable> &variable, const uint line,
                                                      const uint col, const std::string &codeLine,
                                                      const std::string &caretLine)
    {
        if (auto [exprResult, exprType] = visitExpr(ctx->expr()); variable->type != exprType)
        {
            throw TypeMismatchException(util::format(
                    "Type mismatch error: Cannot assign expression result of type '{}' to variable '{}' of type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: Expression result type must match variable type for assignment.",
                    color::colorText(tokenMap::getTokenText(exprType), color::BOLD_BLUE),
                    color::colorText(variable->name, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

} // namespace iron

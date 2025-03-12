//
// Created by Thiago Rodrigues on 12/03/25.
//
#include "../headers/Analyser.h"
#include "../headers/SemanticAnalysis.h"


namespace iron
{

    void SemanticAnalysis::handleDataFormatAssignment(IronParser::AssignmentContext *ctx, const uint line,
                                                      const std::string &codeLine, const std::string &caretLine) const
    {
        if (const auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
        {
            const std::string varName = varDecl->varName->getText();
            const std::string value = ctx->dataFormat()->getText();
            const std::string varType = varDecl->varTypes()->getText();

            if (tokenMap::determineType(value) == tokenMap::REAL_NUMBER)
            {
                if (tokenMap::getTokenType(varType) != tokenMap::determineFloatType(value))
                {
                    const auto valueType = tokenMap::getTokenText(tokenMap::determineFloatType(value));
                    throw TypeMismatchException(util::format(
                            "Type mismatch error: Cannot assign a float value '{}' to a variable of type '{}'.\n"
                            "Line: {}, Scope: {}\n\n{} \n{} \n\n"
                            "Hint: The float value's precision ({}) doesn't match the variable's type ({}). Use the "
                            "correct type or cast the value.",
                            color::colorText(value, color::BOLD_BLUE), color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                            color::colorText(valueType, color::BOLD_BLUE),
                            color::colorText(varType, color::BOLD_GREEN)));
                }
            }
            else
            {
                if (tokenMap::getTokenType(varType) != tokenMap::determineType(value))
                {
                    const auto valueType = tokenMap::getTokenText(tokenMap::determineType(value));
                    throw TypeMismatchException(util::format(
                            "Type mismatch error: Cannot assign a value of type '{}' to a variable of type '{}'.\n"
                            "Line: {}, Scope: {}\n\n{} \n{} \n\n"
                            "Hint: The literal '{}' (type: {}) cannot be assigned to variable '{}' (type: {}). Use the "
                            "correct type or cast the value.",
                            color::colorText(valueType, color::BOLD_BLUE), color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                            color::colorText(value, color::BOLD_BLUE), color::colorText(valueType, color::BOLD_BLUE),
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(varType, color::BOLD_GREEN)));
                }
            }
        }
    }

    void SemanticAnalysis::handleFunctionCallAssignment(IronParser::AssignmentContext *ctx, const uint line,
                                                        const std::string &codeLine, const std::string &caretLine,
                                                        const std::shared_ptr<scope::Function> &currentFunction)
    {

        if (const auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
        {
            const std::string varName = varDecl->varName->getText();
            const std::string varType = varDecl->varTypes()->getText();
            const std::string functionName = ctx->functionCall()->functionName->getText();

            if (const auto variable = currentFunction->findVarAllScopesAndArg(functionName))
            {
                // Caso: variável identificada representa uma função (ainda sem instância).
                if (variable->type == tokenMap::FUNCTION && !variable->function)
                {
                    const auto arg = currentFunction->getArgByName(functionName);
                    if (!arg || !arg->signature)
                    {
                        throw FunctionNotFoundException(
                                util::format("Function not found error: Function '{}' is not defined in current scope "
                                             "or standard library.\n"
                                             "Line: {}, Scope: {}\n\n{} \n{} \n\n"
                                             "Hint: Check for typos in the function name or import the module that "
                                             "contains this function.",
                                             color::colorText(functionName, color::BOLD_GREEN),
                                             color::colorText(std::to_string(line), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                    }
                    if (arg->signature->getReturnType() != tokenMap::getTokenType(varType))
                    {
                        throw TypeMismatchException(util::format(
                                "Return type mismatch error: Cannot assign result of function '{}' to variable '{}'.\n"
                                "Line: {}, Scope: {}\n\n{} \n{} \n\n"
                                "Hint: Function '{}' returns type '{}' but variable '{}' is of type '{}'. These types "
                                "are incompatible.",
                                color::colorText(functionName, color::BOLD_BLUE),
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                caretLine, color::colorText(functionName, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(variable->function->getReturnType()),
                                                 color::BOLD_BLUE),
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(varType, color::BOLD_GREEN)));
                    }
                    visitFunctionCall(ctx->functionCall());
                    return;
                }

                if (!variable->function)
                {
                    throw FunctionNotFoundException(
                            util::format("Function {} not found.\n"
                                         "Line: {}, Scope: {}\n\n{} \n{} \n",
                                         color::colorText(functionName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                if (variable->function->getReturnType() != tokenMap::getTokenType(varType))
                {
                    throw TypeMismatchException(util::format(
                            "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
                            "Line: {}, Scope: {}\n\n{} \n{} \n",
                            color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(functionName, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(variable->function->getReturnType()),
                                             color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
            else
            {
                const auto function = scopeManager->getFunctionDeclarationByName(functionName);
                if (!function)
                {
                    throw FunctionNotFoundException(
                            util::format("Function {} not found.\n"
                                         "Line: {}, Scope: {}\n\n{} \n{} \n",
                                         color::colorText(functionName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
                if (function->getReturnType() != tokenMap::getTokenType(varType))
                {
                    throw TypeMismatchException(util::format(
                            "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
                            "Line: {}, Scope: {}\n\n{} \n{} \n",
                            color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(functionName, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(function->getReturnType()), color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
        }
        visitFunctionCall(ctx->functionCall());
    }

    void SemanticAnalysis::handleAnotherVarNameAssignment(IronParser::AssignmentContext *ctx, const uint line,
                                                          const std::string &codeLine, const std::string &caretLine,
                                                          const std::shared_ptr<scope::Function> &currentFunction)
    {
        auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent);
        if (!varDeclaration)
        {
            // Se não for uma declaração de variável, pode ser outro tipo de atribuição.
            return;
        }

        const std::string anotherVarName = ctx->variableQualifiedName()->base->getText();
        const std::string varName = varDeclaration->varName->getText();

        auto anotherVariable = getCurrentFunction()->findVarAllScopesAndArg(anotherVarName);
        auto variable = currentFunction->findVarAllScopesAndArg(varName);

        // Se há qualificação (ex.: acesso a campo de struct)
        if (!ctx->variableQualifiedName()->rest.empty())
        {
            handleQualifiedNameAssignment(ctx, line, codeLine, caretLine, varName, anotherVarName, variable,
                                          anotherVariable);
            return;
        }

        const std::string varType = varDeclaration->varTypes()->getText();

        // Tratamento específico para atribuição de função
        if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        {
            handleFunctionAssignment(line, codeLine, caretLine, varName, anotherVarName, anotherVariable,
                                     currentFunction, variable);
            return;
        }

        // Caso de atribuição simples entre variáveis
        handleVariableAssignment(line, codeLine, caretLine, varName, varType, variable, anotherVariable);
    }

    void SemanticAnalysis::handleQualifiedNameAssignment(IronParser::AssignmentContext *ctx, const uint line,
                                                         const std::string &codeLine, const std::string &caretLine,
                                                         const std::string &varName, const std::string &anotherVarName,
                                                         const std::shared_ptr<scope::Variable> &variable,
                                                         const std::shared_ptr<scope::Variable> &anotherVariable)
    {
        if (!anotherVariable)
        {
            throw VariableNotFoundException(util::format(
                    "Variable {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        if (anotherVariable->type == tokenMap::STRUCT)
        {
            if (ctx->variableQualifiedName()->rest.size() >= 1)
            {
                auto [structStmt, field] = getStructAndField(ctx->variableQualifiedName());
                if (field->type != variable->type)
                {
                    throw TypeMismatchException(
                            util::format("The variable {} of type {} is incompatible with the field {} of type {}.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(varName, color::BOLD_GREEN),
                                         color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                                         color::colorText(field->name, color::BOLD_BLUE),
                                         color::colorText(tokenMap::getTokenText(field->type), color::BOLD_BLUE),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                if (field->structStemt->name != variable->structStemt->name)
                {
                    throw TypeMismatchException(
                            util::format("The variable {} of type {} is incompatible with the field {} of type {}.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(varName, color::BOLD_GREEN),
                                         color::colorText(variable->structStemt->name, color::BOLD_GREEN),
                                         color::colorText(field->name, color::BOLD_BLUE),
                                         color::colorText(field->structStemt->name, color::BOLD_BLUE),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }
        }
    }

    void SemanticAnalysis::handleFunctionAssignment(const uint line, const std::string &codeLine,
                                                    const std::string &caretLine, const std::string &varName,
                                                    const std::string &anotherVarName,
                                                    const std::shared_ptr<scope::Variable> &anotherVariable,
                                                    const std::shared_ptr<scope::Function> &currentFunction,
                                                    const std::shared_ptr<scope::Variable> &variable) const
    {
        std::shared_ptr<scope::Function> functionPtr;
        if (!anotherVariable)
        {
            const auto function = scopeManager->getFunctionDeclarationByName(anotherVarName);
            if (!function)
            {
                throw FunctionNotFoundException(util::format(
                        "Function {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(anotherVarName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
            functionPtr = function;
        }
        else
        {
            if (!anotherVariable->function)
            {
                throw TypeMismatchException(util::format(
                        "The variable {} of type {} is incompatible with the variable {} of type {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(tokenMap::FUNCTION), color::BOLD_GREEN),
                        color::colorText(anotherVariable->name, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(anotherVariable->type), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
            functionPtr = anotherVariable->function;
        }
        variable->function = functionPtr;
    }

    void SemanticAnalysis::handleVariableAssignment(const uint line, const std::string &codeLine,
                                                    const std::string &caretLine, const std::string &varName,
                                                    const std::string &varType,
                                                    const std::shared_ptr<scope::Variable> &variable,
                                                    const std::shared_ptr<scope::Variable> &anotherVariable) const
    {
        if (!anotherVariable)
        {
            throw VariableNotFoundException(util::format(
                    "Variable {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
        if (!variable)
        {
            throw VariableNotFoundException(util::format(
                    "Variable '{}' not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
        if (variable->type != tokenMap::getTokenType(varType))
        {
            throw TypeMismatchException(util::format(
                    "The variable {} of type {} is incompatible with the variable {} of type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
                    color::colorText(variable->name, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }


    void SemanticAnalysis::handleExprAssignment(IronParser::AssignmentContext *ctx, const uint line,
                                                const std::string &codeLine, const std::string &caretLine)
    {
        if (const auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
        {
            const std::string varName = varDecl->varName->getText();
            const std::string varType = varDecl->varTypes()->getText();
            if (const auto [_, exprType] = visitExpr(ctx->expr()); exprType != tokenMap::getTokenType(varType))
            {
                throw TypeMismatchException(util::format(
                        "The variable {} of type {} is incompatible with the return of expression of type {}.\n"
                        "Line: {}, Scope: {}\n\n{} \n{} \n",
                        color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(exprType), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }
    }

    void SemanticAnalysis::handleBoolExprAssignment(IronParser::AssignmentContext *ctx, const uint line,
                                                    const std::string &codeLine, const std::string &caretLine)
    {
        if (const auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
        {
            const std::string varName = varDecl->varName->getText();
            const std::string varType = varDecl->varTypes()->getText();
            if (tokenMap::getTokenType(varType) != tokenMap::TYPE_BOOLEAN)
            {
                throw TypeMismatchException(util::format(
                        "The variable {} type need be {} to receive the value of a boolean expression\n"
                        "Line: {}, Scope: {}\n\n{} \n{} \n",
                        color::colorText(varName, color::BOLD_GREEN), color::colorText("boolean", color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
            visitBoolExpr(ctx->boolExpr());
        }
    }

} // namespace iron

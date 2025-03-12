//
// Created by Thiago Rodrigues on 12/03/25.
//
#include "../headers/Analyser.h"
#include "../headers/SemanticAnalysis.h"


namespace iron
{

    void SemanticAnalysis::handleDataFormatFunctionArg(IronParser::FunctionCallArgContext *ctx,
                                                       const std::shared_ptr<scope::Function> &calledFunction,
                                                       const std::shared_ptr<scope::FunctionArg> &funcArg,
                                                       const std::string &argName, const int line,
                                                       const std::string &codeLine, const std::string &caretLine)
    {
        const std::string value = ctx->dataFormat()->getText();
        int valueType = tokenMap::determineType(value);
        if (valueType == tokenMap::REAL_NUMBER)
        {
            valueType = tokenMap::determineFloatType(value);
        }

        if (!calledFunction->isExternal() && !calledFunction->isVariedArguments())
        {
            if (valueType != funcArg->type)
            {
                throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the value {} type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(value, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(calledFunction->getFunctionName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }
    }

    void SemanticAnalysis::handleAnotherVarFunctionArg(IronParser::FunctionCallArgContext *ctx,
                                                       const std::shared_ptr<scope::Function> &currentFunction,
                                                       const std::shared_ptr<scope::Function> &calledFunction,
                                                       const std::shared_ptr<scope::FunctionArg> &funcArg,
                                                       const std::string &argName, const int line, int col,
                                                       const std::string &codeLine, const std::string &caretLine) const
    {
        const std::string anotherVarName = ctx->anotherVarName->getText();
        const auto anotherVariable = currentFunction->findVarAllScopesAndArg(anotherVarName);

        // Se a função chamada for externa, não há validação adicional
        if (calledFunction->isExternal())
            return;

        // Se o argumento for do tipo função e possuir uma assinatura,
        // valida se a assinatura da função atribuída coincide
        if (funcArg->type == tokenMap::FUNCTION && funcArg->signature)
        {
            if (!anotherVariable)
            {
                auto function = scopeManager->getFunctionDeclarationByName(anotherVarName);
                if (!function)
                {
                    throw FunctionNotFoundException(
                            util::format("Function {} not found.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(anotherVarName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
                if (!validateSignature(funcArg->signature, function))
                {
                    throw SignatureMismatchException(
                            util::format("The signature of argument {} does not match the signature of function {}.\n"
                                         "At line {} in scope {}.\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(argName, color::BOLD_GREEN),
                                         color::colorText(anotherVarName, color::BOLD_BLUE),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(calledFunction->getFunctionName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }
            else
            {
                if (!anotherVariable->function)
                {
                    throw FunctionNotFoundException(
                            util::format("Function {} not found.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(anotherVarName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
                if (!validateSignature(funcArg->signature, anotherVariable->function))
                {
                    throw SignatureMismatchException(
                            util::format("The signature of argument {} does not match the signature of function {}.\n"
                                         "At line {} in scope {}.\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(argName, color::BOLD_GREEN),
                                         color::colorText(anotherVarName, color::BOLD_BLUE),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(calledFunction->getFunctionName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }
            return;
        }

        if (!anotherVariable)
        {
            throw VariableNotFoundException(util::format(
                    "The variable {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(calledFunction->getFunctionName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        if (!calledFunction->isExternal() && !calledFunction->isVariedArguments())
        {
            if (anotherVariable->type != funcArg->type)
            {
                throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the variable {} type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(anotherVariable->name, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(anotherVariable->type), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(calledFunction->getFunctionName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }
    }

    void SemanticAnalysis::handleNestedFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                                       const std::shared_ptr<scope::Function> &currentFunction,
                                                       const std::shared_ptr<scope::Function> &calledFunction,
                                                       const std::shared_ptr<scope::FunctionArg> &funcArg,
                                                       const std::string &argName, const int line, int col,
                                                       const std::string &codeLine, const std::string &caretLine)
    {
        std::string nestedFuncName = ctx->functionCall()->functionName->getText();
        auto localCalledFunction = scopeManager->getFunctionDeclarationByName(nestedFuncName);
        if (!localCalledFunction)
        {
            auto functionPtr = currentFunction->findVarAllScopesAndArg(nestedFuncName);
            if (!functionPtr)
            {
                throw FunctionNotFoundException(util::format(
                        "Function {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(nestedFuncName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
            localCalledFunction = functionPtr->function;
        }

        if (!calledFunction->isExternal() && !calledFunction->isVariedArguments())
        {
            if (funcArg->type != localCalledFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the function {} return type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(localCalledFunction->getFunctionName(), color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(localCalledFunction->getReturnType()),
                                         color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(calledFunction->getFunctionName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }
        visitFunctionCall(ctx->functionCall());
    }

} // namespace iron

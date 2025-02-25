#include "../headers/SemanticAnalysis.h"

namespace iron
{

    void SemanticAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {

        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();

        if (auto globalScope = scopeManager->getFunctionDeclarationByName(functionName))
        {

            throw FunctionRedefinitionException(util::format("Function {} already declared."
                                                             "Line: {}, Scope: {}\n\n"
                                                             "{}\n"
                                                             "{}\n",
                                                             color::colorText(functionName, color::BOLD_GREEN),
                                                             color::colorText(std::to_string(line), color::YELLOW),
                                                             color::colorText("Global", color::BOLD_YELLOW), codeLine,
                                                             caretLine));
        }

        auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();

        int returnType = tokenMap::VOID;
        if (ctx->functionSignature()->functionReturnType())
        {
            const std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            returnType = tokenMap::getTokenType(type);
        }

        const auto function = std::make_shared<scope::Function>(functionName, funcArgs, returnType);
        scopeManager->addFunctionDeclaration(function);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature());
        }
    }

    void SemanticAnalysis::visitFunctionBody(IronParser::FunctionDeclarationContext *ctx)
    {

        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        const std::string functionName = ctx->functionName->getText();
        const auto function = scopeManager->getFunctionDeclarationByName(functionName);
        if (!function)
        {
            throw FunctionRedefinitionException(util::format("Function {} not found."
                                                             "Line: {}, Scope: {}\n\n"
                                                             "{}\n"
                                                             "{}\n",
                                                             color::colorText(functionName, color::BOLD_GREEN),
                                                             color::colorText(std::to_string(line), color::YELLOW),
                                                             color::colorText("Global", color::BOLD_YELLOW), codeLine,
                                                             caretLine));
        }

        scopeManager->enterScope(function);


        for (const auto child: ctx->children)
        {
            if (const auto statementList = dynamic_cast<IronParser::StatementListContext *>(child))
            {
                visitStatementList(statementList);
            }
        }


        scopeManager->exitScope();
    }

    std::shared_ptr<scope::Signature> SemanticAnalysis::getSignature(IronParser::FunctionSignatureContext *ctx)
    {
        int returnType = tokenMap::VOID;
        if (ctx->functionReturnType())
        {
            returnType = tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText());
        }

        std::vector<std::shared_ptr<scope::FunctionArg>> arguments{};
        for (const auto child: ctx->children)
        {
            if (const auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext *>(child))
            {
                for (const auto child: functionArgs->children)
                {
                    if (const auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
                    {
                        const std::string argType = functionArg->varTypes()->getText();
                        const std::string argName = functionArg->varName->getText();

                        const auto arg = std::make_shared<scope::FunctionArg>(argName, tokenMap::getTokenType(argType));
                        arguments.push_back(arg);
                    }
                }
            }
        }

        return std::make_shared<scope::Signature>(returnType, arguments);
    }

    void SemanticAnalysis::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext *>(child))
            {
                visitFunctionArgs(functionArgs);
            }
        }
    }

    void SemanticAnalysis::visitFunctionArgs(IronParser::FunctionArgsContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(functionArg);
            }
        }
    }

    void SemanticAnalysis::visitFunctionArg(IronParser::FunctionArgContext *ctx) const
    {

        const uint line = ctx->getStart()->getLine();

        const auto currentFunction = scopeManager->currentFunctionDeclaration();
        if (!currentFunction)
        {
            throw ScopeNotFoundException(util::format("visitFunctionArg. Scope current not found. Line: {}",
                                                      color::colorText(std::to_string(line), color::BOLD_GREEN)));
        }

        const auto argsList = currentFunction->getArgs();
        std::string argName = ctx->varName->getText();
        if (auto arg = currentFunction->getArgByName(argName))
        {
            throw VariableRedefinitionException(util::format(
                    "Function arg {} already declared. Line: {}, Scope: fn {}",
                    color::colorText(argName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW)));
        }

        if (ctx->fnsignature())
        {
            // visitFunctionSignature(ctx->fnsignature()->functionSignature());
            const auto signature = getSignature(ctx->fnsignature()->functionSignature());
            if (!signature)
            {
                throw std::runtime_error("SemanticAnalysis::visitFunctionArg. Function signature is empty.");
            }

            argsList->push_back(std::make_shared<scope::FunctionArg>(argName, tokenMap::FUNCTION, signature));
        }
        else
        {
            const std::string argType = ctx->varTypes()->getText();
            argsList->push_back(std::make_shared<scope::FunctionArg>(argName, tokenMap::getTokenType(argType)));
        }
    }

    void SemanticAnalysis::visitFunctionCall(IronParser::FunctionCallContext *ctx)
    {

        std::string functionName = ctx->functionName->getText();

        const auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticAnalysis::visitFunctionCall. Current scope not found");
        }

        if (const auto function = std::dynamic_pointer_cast<scope::Function>(currentScope); !function)
        {
            throw ScopeNotFoundException("SemanticAnalysis::visitFunctionCall. Current scope is not a function");
        }


        if (ctx->functionCallArgs())
        {
            visitFunctionCallArgs(ctx->functionCallArgs());
        }
    }

    void SemanticAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx)
    {
        // Obtém informações de linha e coluna para mensagens de erro
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        const auto functionCall = dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent);
        if (!functionCall)
        {
            return;
        }

        const std::string functionCalledName = functionCall->functionName->getText();
        const auto calledFunction = scopeManager->getFunctionDeclarationByName(functionCalledName);
        if (!calledFunction)
        {

            throw FunctionNotFoundException(util::format(
                    "Function {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(functionCalledName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        const auto functionArgs = calledFunction->getArgs();

        // Coleta os nomes dos argumentos e processa cada um
        std::vector<std::string> argNames;
        for (const auto child: ctx->children)
        {
            if (const auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                const auto varName = functionCallArg->varName->getText();
                argNames.push_back(varName);
                visitFunctionCallArg(functionCallArg);

                if (calledFunction->isExternal() && calledFunction->isVariedArguments())
                {
                    if (!calledFunction->findVarCurrentScopeAndArg(varName))
                    {
                        const auto arg = std::make_shared<scope::FunctionArg>(varName, tokenMap::VOID);
                        functionArgs->push_back(arg);
                    }
                }
            }
        }

        // Obtém a função corrente do escopo e verifica se ela é válida
        const auto currentFunction = getCurrentFunction();

        // Verifica se a quantidade de argumentos está correta
        if (functionArgs->size() != argNames.size())
        {

            if (!calledFunction->isVariedArguments())
            {
                throw ArgumentCountMismatchException(util::format(
                        "Function '{}' expects {} arguments, but {} were provided.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(functionCalledName, color::BOLD_GREEN),
                        color::colorText(std::to_string(functionArgs->size()), color::BOLD_GREEN),
                        color::colorText(std::to_string(argNames.size()), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }

        // Verifica se a ordem dos argumentos está correta
        for (size_t i = 0; i < functionArgs->size(); ++i)
        {
            if (const auto &expectedArg = (*functionArgs)[i]; expectedArg->name != argNames[i])
            {

                if (!calledFunction->isVariedArguments())
                {
                    throw ArgumentOrderMismatchException(
                            util::format("Argument order mismatch in Function '{}'. Expected '{}', but got '{}'.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(functionCalledName, color::BOLD_GREEN),
                                         color::colorText(expectedArg->name, color::BOLD_GREEN),
                                         color::colorText(argNames[i], color::BOLD_BLUE),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }
        }
    }

    void SemanticAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx)
    {
        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentFunction = getCurrentFunction();

        auto argName = ctx->varName->getText();

        if (auto functionCall = dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent->parent))
        {
            auto functionCalledName = functionCall->functionName->getText();
            auto calledFunction = scopeManager->getFunctionDeclarationByName(functionCalledName);
            if (!calledFunction)
            {
                throw FunctionNotFoundException(util::format(
                        "Function {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(functionCalledName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
            auto funcArg = calledFunction->getArgByName(argName);
            if (!funcArg)
            {
                if (!calledFunction->isExternal() && !calledFunction->isVariedArguments())
                {
                    throw FunctionArgNotFoundException(
                            util::format("The argument {} not found.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(argName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }


            if (ctx->dataFormat())
            {

                auto value = ctx->dataFormat()->getText();
                auto valueType = tokenMap::determineType(value);
                if (valueType == tokenMap::REAL_NUMBER)
                {
                    valueType = tokenMap::determineFloatType(value);
                }

                if (!calledFunction->isExternal() && !calledFunction->isVariedArguments())
                {
                    // if (funcArg->type == tokenMap::TYPE_CHAR && valueType == tokenMap::TYPE_STRING)
                    // {
                    //     return;
                    // }
                    if (valueType != funcArg->type)
                    {

                        throw TypeMismatchException(util::format(
                                "The function argument {} type is {} and the value {} type is {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n" // Exibe a linha de código
                                "{}\n", // Exibe a setinha '^'
                                color::colorText(argName, color::BOLD_GREEN),
                                color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                                color::colorText(value, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
                    }

                    if (valueType != funcArg->type)
                    {

                        throw TypeMismatchException(util::format(
                                "The function argument {} type is {} and the value {} type is {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n" // Exibe a linha de código
                                "{}\n", // Exibe a setinha '^'
                                color::colorText(argName, color::BOLD_GREEN),
                                color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                                color::colorText(value, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
                    }
                }
            }


            if (ctx->anotherVarName)
            {

                auto anotherVarName = ctx->anotherVarName->getText();
                auto anotherVariable = currentFunction->findVarAllScopesAndArg(anotherVarName);

                const auto arg = calledFunction->getArgByName(argName);
                if (!arg)
                {
                    throw std::runtime_error("Argument not found.\n");
                }

                if (arg->type == tokenMap::FUNCTION)
                {
                    if (!funcArg->signature)
                    {
                        throw std::runtime_error("The variable need a signature");
                    }

                    if (!anotherVariable)
                    {
                        const auto function = scopeManager->getFunctionDeclarationByName(anotherVarName);
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
                            throw SignatureMismatchException(util::format(
                                    "The signature of argument {} does not match the signature of "
                                    "function {}.\n"
                                    "At line {} in scope {}.\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(argName, color::BOLD_GREEN),
                                    color::colorText(anotherVarName, color::BOLD_BLUE),
                                    color::colorText(std::to_string(line), color::YELLOW),
                                    color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
                        }
                    } else
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
                            throw SignatureMismatchException(util::format(
                                    "The signature of argument {} does not match the signature of "
                                    "function {}.\n"
                                    "At line {} in scope {}.\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(argName, color::BOLD_GREEN),
                                    color::colorText(anotherVarName, color::BOLD_BLUE),
                                    color::colorText(std::to_string(line), color::YELLOW),
                                    color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
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
                            color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
                }

                if (!calledFunction->isExternal() && !calledFunction->isVariedArguments())
                {
                    if (anotherVariable->type != funcArg->type)
                    {
                        throw TypeMismatchException(util::format(
                                "The function argument {} type is {} and the variable {} type is {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n" // Exibe a linha de código
                                "{}\n", // Exibe a setinha '^'
                                color::colorText(argName, color::BOLD_GREEN),
                                color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                                color::colorText(anotherVariable->name, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(anotherVariable->type), color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
                    }
                }




                // if (funcArg->type == tokenMap::FUNCTION)
                // {
                //     calledFunction->getArgByName(funcArg->);
                // }
            }

            if (ctx->functionCall())
            {


                auto calledFunctionName = ctx->functionCall()->functionName->getText();
                auto localCalledFunction = scopeManager->getFunctionDeclarationByName(calledFunctionName);
                if (!localCalledFunction)
                {
                    auto functionPtr = currentFunction->findVarAllScopesAndArg(calledFunctionName);
                    if (!functionPtr)
                    {
                        throw FunctionNotFoundException(
                                util::format("Function {} not found.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(calledFunctionName, color::BOLD_GREEN),
                                             color::colorText(std::to_string(line), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
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
                                "{}\n" // Exibe a linha de código
                                "{}\n", // Exibe a setinha '^'
                                color::colorText(argName, color::BOLD_GREEN),
                                color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                                color::colorText(calledFunction->getName(), color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()),
                                                 color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(functionCalledName, color::BOLD_YELLOW), codeLine, caretLine));
                    }
                }

                visitFunctionCall(ctx->functionCall());
            }
        }
    }

    bool SemanticAnalysis::validateSignature(const std::shared_ptr<scope::Signature> &signature,
                                             const std::shared_ptr<scope::Function> &function)
    {
        if (signature->getArguments().size() != function->getArgs()->size())
        {
            return false;
        }

        const uint size = signature->getArguments().size();
        const auto signA = signature->getArguments();
        const auto signB = *function->getArgs();
        for (uint i = 0; i < size; i++)
        {
            if (signA[i]->type != signB[i]->type)
            {
                return false;
            }
        }

        if (signature->getReturnType() != function->getReturnType())
        {
            return false;
        }

        return true;
    }

    std::shared_ptr<scope::Function>
    SemanticAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx)
    {

        const int line = ctx->getStart()->getLine();
        const int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        // auto currentScope = scopeManager->currentScope();
        // if (!currentScope)
        // {
        //     throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current scope not found");
        // }

        const auto currentFunction = getCurrentFunction();
        // if (!currentFunction)
        // {
        //     throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current function not found");
        // }

        if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            const auto varName = varDeclaration->varName->getText();
            auto functionName = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();
            int returnType = tokenMap::VOID;
            if (ctx->functionSignature()->functionReturnType())
            {
                const std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                returnType = tokenMap::getTokenType(type);
            }

            const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
            auto arrowFunction = std::make_shared<scope::Function>(functionName, funcArgs, returnType);
            arrowFunction->setAlias(variable);

            scopeManager->addFunctionDeclaration(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            auto currentStatement =
                    std::dynamic_pointer_cast<scope::Statements>(currentFunction->getCurrentLocalScope());
            if (!currentStatement)
            {
                throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current statement not found");
            }

            currentStatement->addFunctionAlias(varName, arrowFunction);
            arrowFunction->setUpperFunction(currentFunction);

            scopeManager->enterScope(arrowFunction);
            if (ctx->expr())
            {
                visitExpr(ctx->expr());
            }
            scopeManager->exitScope();
            // currentFunction->exitLocalScope();

            return arrowFunction;
        }

        throw SemanticException("SemanticAnalysis::visitArrowFunctionInline error.");
    }

    std::shared_ptr<scope::Function>
    SemanticAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx)
    {
        const int line = ctx->getStart()->getLine();
        const int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        const auto currentFunction = getCurrentFunction();

        if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            const auto varName = varDeclaration->varName->getText();
            auto functionName = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();
            int returnType = tokenMap::VOID;
            if (ctx->functionSignature()->functionReturnType())
            {
                const std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                returnType = tokenMap::getTokenType(type);
            }

            const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
            auto arrowFunction = std::make_shared<scope::Function>(functionName, funcArgs, returnType);
            arrowFunction->setAlias(variable);
            scopeManager->addFunctionDeclaration(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            auto currentStatement =
                    std::dynamic_pointer_cast<scope::Statements>(currentFunction->getCurrentLocalScope());
            if (!currentStatement)
            {
                throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current statement not found");
            }

            currentStatement->addFunctionAlias(varName, arrowFunction);
            arrowFunction->setUpperFunction(currentFunction);

            scopeManager->enterScope(arrowFunction);
            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList());
            }
            scopeManager->exitScope();


            return arrowFunction;
        }

        throw SemanticException("SemanticAnalysis::visitArrowFunctionInline error.");
    }

    // Helper para obter o escopo da função atual
    std::shared_ptr<scope::Function> SemanticAnalysis::getCurrentFunction()
    {
        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticAnalysis::getCurrentFunction. Current scope not found");
        }

        auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope);

        if (!currentFunction)
        {
            throw ScopeNotFoundException("SemanticAnalysis::getCurrentFunction. No current function found");
        }
        return currentFunction;
    }

} // namespace iron

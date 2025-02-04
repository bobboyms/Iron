#include "../headers/SemanticalAnalysis.h"

#include <iostream>

namespace iron
{

    void SemanticAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();

        auto globalScope = scopeManager->getFunctionDeclarationByName(functionName);
        if (globalScope)
        {

            throw FunctionRedefinitionException(util::format(
                "Function {} already declared."
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText("Global", color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();

        int returnType = tokenMap::VOID;
        if (ctx->functionSignature()->functionReturnType())
        {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            returnType = tokenMap::getTokenType(type);
        }

        auto function = std::make_shared<scope::Function>(functionName, funcArgs, returnType);
        scopeManager->addFunctionDeclaration(function);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature());
        }
    }

    void SemanticAnalysis::visitFunctionBody(IronParser::FunctionDeclarationContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();
        auto function = scopeManager->getFunctionDeclarationByName(functionName);
        if (!function)
        {
            throw FunctionRedefinitionException(util::format(
                "Function {} not found."
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText("Global", color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        scopeManager->enterScope(function);

        for (auto child : ctx->children)
        {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext *>(child))
            {

                visitStatementList(statementList);
            }
        }

        scopeManager->exitScope();
    }

    void SemanticAnalysis::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext *>(child))
            {
                visitFunctionArgs(functionArgs);
            }
        }
    }

    void SemanticAnalysis::visitFunctionArgs(IronParser::FunctionArgsContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(functionArg);
            }
        }
    }

    void SemanticAnalysis::visitFunctionArg(IronParser::FunctionArgContext *ctx)
    {
        std::string argName = ctx->varName->getText();
        std::string argType = ctx->varTypes()->getText();
        int line = ctx->getStart()->getLine();

        const auto function = scopeManager->currentFunctionDeclarationBy();
        if (!function)
        {
            throw ScopeNotFoundException(util::format(
                "visitFunctionArg. Scope current not found. Line: {}",
                color::colorText(std::to_string(line), color::BOLD_GREEN)));
        }

        auto arg = function->getArgByName(argName);
        if (arg)
        {
            throw VariableRedefinitionException(util::format(
                "Function arg {} already declared. Line: {}, Scope: fn {}",
                color::colorText(argName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(function->getFunctionName(), color::BOLD_YELLOW)));
        }

        auto argsList = function->getArgs();
        argsList->push_back(std::make_shared<scope::FunctionArg>(argName, tokenMap::getTokenType(argType)));

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
    }

    void SemanticAnalysis::visitFunctionCall(IronParser::FunctionCallContext *ctx)
    {

        std::string functionName = ctx->functionName->getText();
        int line = ctx->getStart()->getLine();

        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticAnalysis::visitFunctionCall. Current scope not found");
        }

        auto function = std::dynamic_pointer_cast<scope::Function>(currentScope);
        if (!function)
        {
            throw ScopeNotFoundException("SemanticAnalysis::visitFunctionCall. Current scope is not a function");
        }

        // Verificar argumentos e outras validações conforme necessário
        // Exemplo:
        if (ctx->functionCallArgs())
        {
            visitFunctionCallArgs(ctx->functionCallArgs());
        }

        // Implementação adicional conforme necessário
    }

    void SemanticAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx)
    {
        // Coleta os nomes dos argumentos e processa cada um
        std::vector<std::string> argNames;
        for (auto child : ctx->children)
        {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                argNames.push_back(functionCallArg->varName->getText());
                visitFunctionCallArg(functionCallArg);
            }
        }

        auto functionCall = dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent);
        if (!functionCall)
        {
            return;
        }

        // Obtém informações de linha e coluna para mensagens de erro
        const int line = ctx->getStart()->getLine();
        const int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        // Obtém a função corrente do escopo e verifica se ela é válida
        auto currentFunction = getCurrentFunction();

        // Recupera o nome da função chamada e obtém a função correspondente
        const std::string functionCalledName = functionCall->functionName->getText();
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
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        // Armazena os argumentos esperados da função chamada
        auto functionArgs = calledFunction->getArgs();

        // Verifica se a quantidade de argumentos está correta
        if (functionArgs->size() != argNames.size())
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
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        // Verifica se a ordem dos argumentos está correta
        for (size_t i = 0; i < functionArgs->size(); ++i)
        {
            const auto &expectedArg = (*functionArgs)[i];
            if (expectedArg->name != argNames[i])
            {
                throw ArgumentOrderMismatchException(util::format(
                    "Argument order mismatch in Function '{}'. Expected '{}', but got '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(functionCalledName, color::BOLD_GREEN),
                    color::colorText(expectedArg->name, color::BOLD_GREEN),
                    color::colorText(argNames[i], color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
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
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            auto funcArg = calledFunction->getArgByName(argName);
            if (!funcArg)
            {
                throw FunctionArgNotFoundException(util::format(
                    "The argument {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(argName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            if (ctx->dataFormat())
            {

                auto value = ctx->dataFormat()->getText();
                auto valueType = tokenMap::determineType(value);
                if (valueType == tokenMap::REAL_NUMBER)
                {
                    valueType = tokenMap::determineFloatType(value);
                }

                if (valueType != funcArg->type)
                {

                    throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the value {} type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"  // Exibe a linha de código
                        "{}\n", // Exibe a setinha '^'
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(value, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionCalledName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }
            }

            if (ctx->anotherVarName)
            {
                auto varName = ctx->anotherVarName->getText();
                auto variable = currentFunction->findVarAllScopesAndArg(varName);
                if (!variable)
                {
                    throw VariableNotFoundException(util::format(
                        "The variable {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionCalledName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }

                if (variable->type != funcArg->type)
                {
                    throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the variable {} type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"  // Exibe a linha de código
                        "{}\n", // Exibe a setinha '^'
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(variable->name, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionCalledName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }
            }

            if (ctx->functionCall())
            {
                auto calledFunctionName = ctx->functionCall()->functionName->getText();
                auto calledFunction = scopeManager->getFunctionDeclarationByName(calledFunctionName);
                if (!calledFunction)
                {
                    auto functionPtr = currentFunction->findVarAllScopesAndArg(calledFunctionName);
                    if (!functionPtr)
                    {
                        throw ScopeNotFoundException("SemanticAnalysis::visitFunctionCallArg. No current function scope found");
                    }

                    calledFunction = functionPtr->function;
                }

                if (funcArg->type != calledFunction->getReturnType())
                {
                    throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the function {} return type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"  // Exibe a linha de código
                        "{}\n", // Exibe a setinha '^'
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(calledFunction->getName(), color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionCalledName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }

                visitFunctionCall(ctx->functionCall());
            }
        }

        // if (ctx->varName)
        // {
        // }

        // if (ctx->functionCall())
        // {
        //     visitFunctionCall(ctx->functionCall());
        // }

        // Implementação adicional conforme necessário
    }

    std::shared_ptr<scope::Function> SemanticAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        // auto currentScope = scopeManager->currentScope();
        // if (!currentScope)
        // {
        //     throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current scope not found");
        // }

        auto currentFunction = getCurrentFunction();
        // if (!currentFunction)
        // {
        //     throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current function not found");
        // }

        if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            auto varName = varDeclaration->varName->getText();
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();
            int returnType = tokenMap::VOID;
            if (ctx->functionSignature()->functionReturnType())
            {
                std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                returnType = tokenMap::getTokenType(type);
            }

            auto arrowFunction = std::make_shared<scope::Function>(alias, funcArgs, returnType);
            scopeManager->addFunctionDeclaration(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            auto currentStatement = std::dynamic_pointer_cast<scope::Statements>(currentFunction->getCurrentLocalScope());
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

    std::shared_ptr<scope::Function> SemanticAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx)
    {
        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        // auto currentScope = scopeManager->currentScope();
        // if (!currentScope)
        // {
        //     throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current scope not found");
        // }

        auto currentFunction = getCurrentFunction();
        // if (!currentFunction)
        // {
        //     throw ScopeNotFoundException("SemanticAnalysis::visitArrowFunctionInline. Current function not found");
        // }

        if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            auto varName = varDeclaration->varName->getText();
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();
            int returnType = tokenMap::VOID;
            if (ctx->functionSignature()->functionReturnType())
            {
                std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                returnType = tokenMap::getTokenType(type);
            }

            auto arrowFunction = std::make_shared<scope::Function>(alias, funcArgs, returnType);
            scopeManager->addFunctionDeclaration(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            auto currentStatement = std::dynamic_pointer_cast<scope::Statements>(currentFunction->getCurrentLocalScope());
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

}
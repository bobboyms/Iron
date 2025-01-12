#include "../headers/SemanticalAnalysis.h"
#include "../headers/Exceptions.h"
#include "../headers/Colors.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"
#include <iostream>

// Construtor

namespace iron
{

    SemanticalAnalysis::SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<iron::ScopeManager> scopeManager)
        : parser(parser), scopeManager(std::move(scopeManager))
    {
    }

    // Destrutor
    SemanticalAnalysis::~SemanticalAnalysis()
    {
    }

    // Método principal para análise semântica
    void SemanticalAnalysis::analyze()
    {
        // Inicializa o escopo global

        scopeManager->enterScope(tokenMap::getTokenText(tokenMap::GLOBAL)); // start(tokenMap::getTokenText(tokenMap::GLOBAL));
        IronParser::ProgramContext *programContext = parser->program();

        // Processa todas as declarações no programa
        for (auto child : programContext->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        // Finaliza o escopo global após processar todas as declarações
        scopeManager->exitScope(tokenMap::getTokenText(tokenMap::GLOBAL));
    }

    void SemanticalAnalysis::visitStatementList(IronParser::StatementListContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration);
            }
            if (auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {

                const int line = ctx->start->getLine();
                auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
                std::string functionName = funcCall->functionName->getText();

                auto globalFunctionNameOpt = globalScope->lookup(functionName);

                if (!globalFunctionNameOpt.has_value())
                {
                    auto functionCallOpt = scopeManager->currentScope()->lookup(functionName);
                    if (functionCallOpt.has_value())
                    {
                        auto symbolInfo = functionCallOpt.value();
                        if (!(symbolInfo.dataType == tokenMap::FUNCTION))
                        {
                            throw FunctionNotFoundException(util::format(
                                "The variable {} does not point to any function. Line: {}, Scope: {}",
                                color::colorText(functionName, color::BOLD_GREEN),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(
                                    util::format("{} {}",
                                                 tokenMap::getTokenText(tokenMap::FUNCTION),
                                                 scopeManager->currentScope()->getName()),
                                    color::BOLD_YELLOW)));
                        }

                        visitFunctionCall(funcCall, symbolInfo.alias, scopeManager->currentScope());
                    }
                    else
                    {
                        throw FunctionNotFoundException(util::format(
                            "The variable {} does not point to any function. Line: {}, Scope: {}",
                            color::colorText(functionName, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                util::format("{} {}",
                                             tokenMap::getTokenText(tokenMap::FUNCTION),
                                             scopeManager->currentScope()->getName()),
                                color::BOLD_YELLOW)));
                    }
                }
                else
                {
                    visitFunctionCall(funcCall, functionName, scopeManager->currentScope());
                }
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
            }
        }
    }

    void SemanticalAnalysis::visitExpr(IronParser::ExprContext *ctx)
    {
        // Estrutura que armazena informações sobre a última expressão/variável/função visitada
        struct LastExpressionInfo
        {
            std::string identifier; // Nome da variável, número ou função
            int dataType;           // Tipo de dado (ex.: TYPE_INT, NUMBER, FUNCTION, etc.)
            int symbolType;         // Tipo de símbolo (ex.: VARIABLE, FUNCTION, NUMBER, etc.)
        };

        // Mantido estático para preservar estado entre visitas dentro da mesma expressão
        static LastExpressionInfo lastExpr;

        int line = ctx->getStart()->getLine();

        // Função local para validar compatibilidade entre a "última expressão" e a expressão atual
        auto validateCompatibility = [&](const std::string &currentIdentifier,
                                         int currentDataType,
                                         int currentSymbolType,
                                         const std::string &scope)
        {
            // Verifica se a última expressão ainda existe no escopo
            auto optPreviousSymbol = scopeManager->currentScope()->lookup(lastExpr.identifier);
            if (!optPreviousSymbol.has_value())
            {
                // Se não existe mais, limpamos a referência
                lastExpr.identifier.clear();
            }
            else
            {
                SymbolInfo previousSymbol = optPreviousSymbol.value();

                // Exemplo de regra: se um é numérico e o outro não é, gera incompatibilidade
                bool isCurrentNumber = tokenMap::isNumber(currentDataType);
                bool isPreviousNumber = tokenMap::isNumber(previousSymbol.dataType);

                if (isCurrentNumber != isPreviousNumber)
                {
                    std::string errorMessage;
                    util::printf("currentSymbolType: {}, {}", currentIdentifier, tokenMap::getTokenText(currentDataType));
                    if (currentSymbolType == tokenMap::FUNCTION)
                    {
                        errorMessage = "Return type of function '{}' is incompatible with variable '{}'. Line: {}, Scope: {}";
                    }
                    else if (currentSymbolType == tokenMap::VARIABLE)
                    {
                        errorMessage = "Variable '{}' is incompatible with variable '{}'. Line: {}, Scope: {}";
                    }
                    else if (currentSymbolType == tokenMap::NUMBER)
                    {
                        errorMessage = "Number '{}' is incompatible with variable '{}'. Line: {}, Scope: {}";
                    }

                    throw TypeMismatchException(util::format(
                        errorMessage,
                        color::colorText(currentIdentifier, color::BOLD_GREEN),
                        color::colorText(lastExpr.identifier, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            util::format("{} {}",
                                         tokenMap::getTokenText(tokenMap::FUNCTION),
                                         scope),
                            color::BOLD_YELLOW)));
                }
            }
        };

        // 1. Se o nó é apenas um nome de variável
        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            std::string currentScopeName = scopeManager->currentScopeName();
            auto optSymbolInfo = scopeManager->currentScope()->lookup(varName);

            if (!optSymbolInfo.has_value())
            {
                throw VariableNotFoundException(util::format(
                    "Variable '{}' not found. Line: {}",
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }

            // Verifica compatibilidade com a última expressão visitada (se houver)
            if (!lastExpr.identifier.empty())
            {
                SymbolInfo symbolInfo = optSymbolInfo.value();
                if (lastExpr.dataType == tokenMap::NUMBER)
                {
                    // Exemplo de validação: se a última expressão era "NUMBER" literal,
                    // e esta é uma variável não-numérica, dá erro.
                    if (!tokenMap::isNumber(symbolInfo.dataType))
                    {
                        throw TypeMismatchException(util::format(
                            "Variable '{}' is incompatible with number '{}'. Line: {}, Scope: {}",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(lastExpr.identifier, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                util::format("{} {}",
                                             tokenMap::getTokenText(tokenMap::FUNCTION),
                                             currentScopeName),
                                color::BOLD_YELLOW)));
                    }
                }
                else
                {
                    validateCompatibility(varName, symbolInfo.dataType, symbolInfo.type, currentScopeName);
                }
            }

            // Atualiza o "último símbolo" com as infos desta variável
            SymbolInfo newSymbol = optSymbolInfo.value();
            lastExpr.identifier = varName;
            lastExpr.dataType = newSymbol.dataType;
            lastExpr.symbolType = tokenMap::VARIABLE;
        }

        // 2. Se o nó é um número (literal)
        if (ctx->number())
        {
            std::string numberLiteral = ctx->number()->getText();
            std::string currentScopeName = scopeManager->currentScopeName();

            // Se há uma última expressão, valida compatibilidade
            if (!lastExpr.identifier.empty())
            {
                validateCompatibility(numberLiteral, tokenMap::NUMBER, tokenMap::NUMBER, currentScopeName);
            }

            // Atualiza o "último símbolo"
            lastExpr.identifier = numberLiteral;
            lastExpr.dataType = tokenMap::NUMBER;
            lastExpr.symbolType = tokenMap::NUMBER;
        }

        // 3. Se o nó é uma chamada de função
        if (ctx->functionCall())
        {
            std::string fnName = ctx->functionCall()->functionName->getText();
            std::string currentScopeName = scopeManager->currentScopeName();
            auto currentScope = scopeManager->currentScope();
            auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));

            std::string globalFunctionName;
            std::optional<SymbolInfo> optGlobalFunction;

            // Verifica se a função está declarada localmente com alias ou no global
            auto localLookup = currentScope->lookup(fnName);
            if (localLookup.has_value())
            {
                if (localLookup.value().dataType == tokenMap::FUNCTION)
                {
                    globalFunctionName = localLookup->alias;
                    optGlobalFunction = globalScope->lookup(globalFunctionName);
                }
                else
                {
                    // Se não é FUNCTION, tenta lookup no global direto
                    globalFunctionName = fnName;
                    optGlobalFunction = globalScope->lookup(globalFunctionName);
                }
            }
            else
            {
                throw FunctionNotFoundException(util::format(
                    "Function '{}' not found. Line: {}, Scope: {}",
                    color::colorText(fnName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(
                        util::format("{} {}",
                                     tokenMap::getTokenText(tokenMap::FUNCTION),
                                     currentScopeName),
                        color::BOLD_YELLOW)));
            }

            if (!optGlobalFunction.has_value())
            {
                throw FunctionNotFoundException(util::format(
                    "Function '{}' not found. Line: {}, Scope: {}",
                    color::colorText(fnName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(
                        util::format("{} {}",
                                     tokenMap::getTokenText(tokenMap::FUNCTION),
                                     currentScopeName),
                        color::BOLD_YELLOW)));
            }

            // Verifica argumentos entrando no escopo da função
            const SymbolInfo &globalFunction = optGlobalFunction.value();
            scopeManager->enterScope(globalFunctionName);
            visitFunctionCall(ctx->functionCall(), globalFunctionName, currentScope);
            scopeManager->exitScope(globalFunctionName);

            // Verifica compatibilidade com a última expressão, se existir
            if (!lastExpr.identifier.empty())
            {
                if (lastExpr.dataType == tokenMap::NUMBER)
                {
                    // Se a última expressão era um número literal,
                    // a função deve retornar tipo numérico
                    if (!tokenMap::isNumber(globalFunction.dataType))
                    {
                        throw TypeMismatchException(util::format(
                            "Return type of function '{}' is incompatible with number '{}'. Line: {}, Scope: {}",
                            color::colorText(fnName, color::BOLD_GREEN),
                            color::colorText(lastExpr.identifier, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                util::format("{} {}",
                                             tokenMap::getTokenText(tokenMap::FUNCTION),
                                             currentScope),
                                color::BOLD_YELLOW)));
                    }
                }
                else
                {
                    // Caso contrário, usamos a função de validação
                    validateCompatibility(globalFunctionName, globalFunction.dataType, tokenMap::FUNCTION, currentScopeName);
                }
            }

            // Atualiza o "último símbolo"
            lastExpr.identifier = globalFunctionName;
            lastExpr.dataType = globalFunction.dataType;
            lastExpr.symbolType = tokenMap::FUNCTION;
        }

        // 4. Visita subexpressões recursivamente
        for (auto child : ctx->children)
        {
            if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(subExpr);
            }
        }

        // 5. Se este nó não tem pai (ou seja, é raiz na subárvore), limpamos o "último símbolo"
        if (ctx->parent == nullptr)
        {
            lastExpr.identifier.clear();
        }
    }

    void SemanticalAnalysis::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {
        std::string varName = ctx->varName->getText();
        int line = ctx->getStart()->getLine();

        const std::string scope = scopeManager->currentScopeName();
        auto result = scopeManager->currentScope()->lookup(varName);

        if (result.has_value())
        {
            SymbolInfo symbolInfo = result.value();
        }
        else
        {
            throw VariableNotFoundException(util::format(
                "Variable '{}' not found. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    util::format("{} {}",
                                 tokenMap::getTokenText(tokenMap::FUNCTION),
                                 scope),
                    color::BOLD_YELLOW)));
        }
    }

    void SemanticalAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    {
        int line = ctx->getStart()->getLine();

        // Visita todos os filhos que podem ser expressão ou arrow function
        for (auto child : ctx->children)
        {
            if (auto expr = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expr);
            }
            else if (auto arrowInline = dynamic_cast<IronParser::ArrowFunctionInlineContext *>(child))
            {
                visitArrowFunctionInline(arrowInline);
            }
            else if (auto arrowBlock = dynamic_cast<IronParser::ArrowFunctionBlockContext *>(child))
            {
                visitArrowFunctionBlock(arrowBlock);
            }
        }

        // Se houver um formato de dado literal (ex.: "3.14", "42", etc.)
        if (ctx->dataFormat())
        {
            // Caso 1: a atribuição está sendo feita a um argumento de função
            if (auto *functionArg = dynamic_cast<IronParser::FunctionArgContext *>(ctx->parent))
            {
                std::string argName = functionArg->varName->getText();
                std::string argType = functionArg->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType = tokenMap::determineType(literalValue);

                // Se o argumento da função é um tipo real (float/double), mas o literal não é real
                if (tokenMap::isRealNumber(tokenMap::getTokenType(argType)))
                {
                    if (tokenMap::REAL_NUMBER != literalType)
                    {
                        throw TypeMismatchException(util::format(
                            "The argument '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                            color::colorText(argName, color::BOLD_GREEN),
                            color::colorText(argType, color::BOLD_GREEN),
                            color::colorText(literalValue, color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(literalType), color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                util::format("fn {}", scopeManager->currentScopeName()),
                                color::YELLOW)));
                    }
                }
                // Se não for real, mas o tipo determinado do literal difere do tipo declarado
                else if (tokenMap::getTokenType(argType) != literalType)
                {
                    throw TypeMismatchException(util::format(
                        "The argument '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(argType, color::BOLD_GREEN),
                        color::colorText(literalValue, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(literalType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            util::format("fn {}", scopeManager->currentScopeName()),
                            color::YELLOW)));
                }
            }

            // Caso 2: a atribuição está sendo feita a uma variável declarada
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType = tokenMap::determineType(literalValue);

                // Se a variável é um tipo real, mas o literal não é real
                if (tokenMap::isRealNumber(tokenMap::getTokenType(varType)))
                {
                    if (tokenMap::REAL_NUMBER != literalType)
                    {
                        throw TypeMismatchException(util::format(
                            "The variable '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(literalValue, color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(literalType), color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                util::format("fn {}", scopeManager->currentScopeName()),
                                color::YELLOW)));
                    }
                }
                // Se não for real, mas o tipo determinado do literal difere do tipo declarado
                else if (tokenMap::getTokenType(varType) != literalType)
                {
                    throw TypeMismatchException(util::format(
                        "The variable '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(varType, color::BOLD_GREEN),
                        color::colorText(literalValue, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(literalType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            util::format("fn {}", scopeManager->currentScopeName()),
                            color::YELLOW)));
                }
            }
        }
    }

    // Visita uma declaração de variável e verifica duplicatas
    void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext *ctx)
    {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        int line = ctx->getStart()->getLine();

        const std::string scopeName = scopeManager->currentScopeName();
        auto existingSymbol = scopeManager->currentScope()->lookupNoParent(varName);

        if (existingSymbol.has_value())
        {
            throw VariableRedefinitionException(util::format(
                "Variable {} already declared. Line: {}, Scope: {}, Type: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeName, color::BOLD_YELLOW),
                color::colorText(std::to_string(existingSymbol->type), color::CYAN)));
        }

        // auto arrowFunctionName = varDeclaration->varName->getText());
        if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        {
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            // util::printf("VarName {} scopeName: {}", varName, scopeName);
            // auto localScope = scopeManager->getScopeByName(scopeName);
            scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr, {}, alias});
        }
        else
        {
            scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr});
        }

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
        else
        {
            throw UninitializedVariableException(util::format(
                "Variable {} has not been initialized. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
        }

        for (auto child : ctx->children)
        {
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();
        int line = ctx->functionName->getLine();

        // Verifica duplicata no escopo global antes de iniciar um novo escopo
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        auto result = globalScope->lookup(functionName);

        if (result.has_value())
        {
            throw FunctionRedefinitionException(util::format(
                "Function {} already declared. Line: {}, Scope: {}",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
        }

        if (ctx->functionSignature()->functionReturnType())
        {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(functionName, {tokenMap::FUNCTION, tokenMap::getTokenType(type), nullptr});
        }
        else
        {
            globalScope->addSymbol(functionName, {tokenMap::FUNCTION, tokenMap::VOID, nullptr});
        }

        scopeManager->enterScope(functionName);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature());
        }

        for (auto child : ctx->children)
        {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext *>(child))
            {
                visitStatementList(statementList);
            }
        }

        scopeManager->exitScope(functionName);
    }

    void SemanticalAnalysis::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext *>(child))
            {
                visitFunctionArgs(functionArgs);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionArgs(IronParser::FunctionArgsContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(functionArg);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionArg(IronParser::FunctionArgContext *ctx)
    {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();
        int line = ctx->getStart()->getLine();

        const std::string scope = scopeManager->currentScopeName();
        auto result = scopeManager->currentScope()->lookupNoParent(varName);

        if (result.has_value())
        {
            SymbolInfo symbolInfo = result.value();

            if (symbolInfo.type == tokenMap::ARGUMENT)
            {
                throw VariableRedefinitionException(util::format(
                    "Function arg {} already declared. Line: {}, Scope: fn {}",
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scope, color::BOLD_YELLOW),
                    color::colorText(tokenMap::getTokenText(symbolInfo.type), color::CYAN)));
            }
        }

        // adciona argumento da função ao escopo atual
        scopeManager->currentScope()->addSymbol(varName, {tokenMap::ARGUMENT, tokenMap::getTokenType(varType), nullptr});

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }

        // adicionao argumento da função ao escopo global
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));

        if (auto *globalFunctionPtr = globalScope->lookupPtr(scopeManager->currentScopeName()))
        {
            globalFunctionPtr->args.emplace_back(varName, tokenMap::getTokenType(varType));
        }
    }

    void SemanticalAnalysis::visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                               const std::string &actualFunctionName,
                                               std::shared_ptr<SymbolTable> parentScope)
    {

        auto line = ctx->getStart()->getLine();
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        auto globalFunctionSymbalInfo = globalScope->lookup(ctx->functionName->getText());

        // std::cout << parentScope->getName() << actualFunctionName << std::endl;

        // parentScope->lookup()

        auto functionSymbolInfoOpt = globalScope->lookup(actualFunctionName);
        if (!functionSymbolInfoOpt.has_value())
        {
            throw FunctionNotFoundException(util::format(
                "Function 'fn {}' not found. Line: {}",
                color::colorText(actualFunctionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }

        auto functionSymbolInfo = functionSymbolInfoOpt.value();
        auto globalArgsSize = functionSymbolInfo.args.size();

        // Se a call tem argumentos
        if (ctx->functionCallArgs())
        {

            int callArgsSize = 0;
            for (auto child : ctx->functionCallArgs()->children)
            {
                if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
                {
                    callArgsSize += 1;
                }
            }

            std::string aliasName = !functionSymbolInfo.alias.empty() ? functionSymbolInfo.alias : actualFunctionName;

            if (globalArgsSize != callArgsSize)
            {
                throw ArgumentCountMismatchException(util::format(
                    "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                    color::colorText(
                        util::format("fn {}", aliasName), color::BOLD_GREEN),
                    color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                    color::colorText(std::to_string(callArgsSize), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }

            visitFunctionCallArgs(ctx->functionCallArgs(), actualFunctionName, parentScope);
        }
        else
        {
            if (globalArgsSize > 0)
            {
                throw ArgumentCountMismatchException(util::format(
                    "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                    color::colorText(
                        util::format("fn {}", functionSymbolInfo.alias), color::BOLD_GREEN),
                    color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                    color::colorText(std::to_string(0), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }
        }
    }

    // Visita a lista de argumentos da função "actualFunctionName"
    void SemanticalAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx,
                                                   const std::string &actualFunctionName,
                                                   std::shared_ptr<SymbolTable> parentScope)
    {

        for (auto child : ctx->children)
        {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                visitFunctionCallArg(functionCallArg, actualFunctionName, parentScope);
            }
        }

        std::vector<std::string> sequenceOfArgs;
        for (auto child : ctx->children)
        {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                sequenceOfArgs.push_back(functionCallArg->varName->getText());
            }
        }

        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        auto globalFunction = globalScope->lookup(actualFunctionName).value();
        auto args = globalFunction.args;

        for (size_t i = 0; i < args.size(); ++i)
        {
            if (sequenceOfArgs[i] != args[i].first)
            { // args[i].first é o nome do argumento formal
                throw ArgumentOrderMismatchException(util::format(
                    "Argument order mismatch in function '{}'. Expected '{}', but got '{}'.",
                    color::colorText(util::format("fn {}", globalFunction.alias), color::BOLD_GREEN),
                    color::colorText(args[i].first, color::BOLD_GREEN),
                    color::colorText(sequenceOfArgs[i], color::BOLD_GREEN)));
            }
        }
    }

    // Visita um único argumento "argName" de "actualFunctionName"
    void SemanticalAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                                  const std::string &actualFunctionName,
                                                  std::shared_ptr<SymbolTable> parentScope)
    {
        int line = ctx->getStart()->getLine();

        // Nome do parâmetro formal, conforme declarado na função
        std::string formalArgName = ctx->varName->getText();

        // Localiza o escopo global
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        if (!globalScope)
        {
            throw std::runtime_error("Global scope not found.");
        }

        // Busca a função (actualFunctionName) no escopo global
        auto globalFunctionOpt = globalScope->lookup(actualFunctionName);
        if (!globalFunctionOpt.has_value())
        {
            throw FunctionNotFoundException(util::format(
                "Function 'fn {}' not found. Line: {}",
                color::colorText(actualFunctionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }

        // Verifica se 'formalArgName' é um parâmetro formal da função
        auto argOpt = iron::getArgumentByName(globalFunctionOpt.value(), formalArgName);
        if (!argOpt.has_value())
        {
            throw FunctionArgNotFoundException(util::format(
                "Argument '{}' not found in function 'fn {}'. Line: {}",
                color::colorText(formalArgName, color::BOLD_GREEN),
                color::colorText(actualFunctionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }

        // Recupera o nome e o tipo esperado do parâmetro
        auto [expectedArgName, expectedArgType] = *argOpt;

        // Se o parser identificou 'dataFormat', verifique se o literal é compatível
        if (ctx->dataFormat())
        {
            bool isIntLiteral = ctx->dataFormat()->INT_NUMBER();
            bool isRealLiteral = ctx->dataFormat()->REAL_NUMBER();

            // Caso o tipo do parâmetro seja int, mas o literal não é INT_NUMBER
            if (expectedArgType == tokenMap::TYPE_INT && !isIntLiteral)
            {
                throw TypeMismatchException(util::format(
                    "Argument '{}' is incompatible with type 'int'. Line: {}",
                    color::colorText(expectedArgName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }
            // Caso o tipo do parâmetro seja float/double, mas o literal não é REAL_NUMBER
            else if ((expectedArgType == tokenMap::TYPE_FLOAT || expectedArgType == tokenMap::TYPE_DOUBLE) && !isRealLiteral)
            {
                std::string floatTypeStr = (expectedArgType == tokenMap::TYPE_FLOAT) ? "float" : "double";
                throw TypeMismatchException(util::format(
                    "Argument '{}' is incompatible with type '{}'. Line: {}",
                    color::colorText(expectedArgName, color::BOLD_GREEN),
                    color::colorText(floatTypeStr, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }
            // Se o literal é REAL_NUMBER, mas precisamos checar se é float ou double
            else if (isRealLiteral)
            {
                auto realLiteralType = tokenMap::determineFloatType(ctx->dataFormat()->REAL_NUMBER()->getText());
                if (realLiteralType != expectedArgType)
                {
                    throw TypeMismatchException(util::format(
                        "Argument '{}' expects type '{}', but got '{}'. Line: {}",
                        color::colorText(expectedArgName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(expectedArgType), color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(realLiteralType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)));
                }
            }
        }

        // Se o valor do argumento for outra variável
        if (ctx->anotherVarName)
        {
            std::string anotherVarName = ctx->anotherVarName->getText();
            auto anotherVarLookup = parentScope->lookup(anotherVarName);

            if (!anotherVarLookup.has_value())
            {
                throw VariableNotFoundException(util::format(
                    "Variable '{}' not found in scope 'fn {}'. Line: {}",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(parentScope->getName(), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }

            SymbolInfo varSymbolInfo = anotherVarLookup.value();
            if (varSymbolInfo.type != tokenMap::VARIABLE && varSymbolInfo.type != tokenMap::ARGUMENT)
            {
                throw VariableNotFoundException(util::format(
                    "The '{}' is not a variable in scope 'fn {}'. Line: {}",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(parentScope->getName(), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }

            // Compara tipo do argumento esperado com o tipo da variável encontrada
            if (expectedArgType != varSymbolInfo.dataType)
            {
                throw TypeMismatchException(util::format(
                    "Argument '{}' is incompatible with variable '{}'. Line: {}",
                    color::colorText(expectedArgName, color::BOLD_GREEN),
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }
        }

        // Se o valor do argumento for outra função
        if (ctx->functionCall())
        {
            std::string innerFunctionName = ctx->functionCall()->functionName->getText();
            std::string resolvedFunctionName = innerFunctionName;

            // Verifica se a função está no escopo global; se não, tenta formá-la com o nome atual do escopo
            if (!globalScope->lookup(resolvedFunctionName).has_value())
            {
                resolvedFunctionName = iron::createFunctionName(parentScope->getName(), innerFunctionName);
                if (!globalScope->lookup(resolvedFunctionName).has_value())
                {
                    throw FunctionNotFoundException(util::format(
                        "Function '{}' not found. Line: {}",
                        color::colorText(innerFunctionName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)));
                }
            }

            auto innerFunctionSymbolOpt = globalScope->lookup(resolvedFunctionName);
            if (!innerFunctionSymbolOpt.has_value())
            {
                throw FunctionNotFoundException(util::format(
                    "Function '{}' not found. Line: {}",
                    color::colorText(resolvedFunctionName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }

            // Visita a chamada de função
            visitFunctionCall(ctx->functionCall(), resolvedFunctionName, parentScope);
        }
    }

    void SemanticalAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx)
    {
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            // Nome "original" da arrow function
            std::string arrowFuncName = varDeclaration->varName->getText();

            // Cria um nome único para a função no escopo global
            std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            if (ctx->functionSignature()->functionReturnType())
            {
                std::string returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                globalScope->addSymbol(
                    globalFunctionName,
                    {tokenMap::FUNCTION,
                     tokenMap::getTokenType(returnTypeStr),
                     nullptr,
                     {},
                     arrowFuncName});
            }
            else
            {
                // Caso não haja tipo de retorno, define como VOID
                globalScope->addSymbol(
                    globalFunctionName,
                    {tokenMap::FUNCTION,
                     tokenMap::VOID,
                     nullptr,
                     {},
                     arrowFuncName});
            }

            // Entra no escopo da função inline
            scopeManager->enterScope(globalFunctionName);

            // Se houver assinatura (parâmetros), visite-a
            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            // Se houver expressão (corpo inline), visite
            if (ctx->expr())
            {
                visitExpr(ctx->expr());
            }

            // Sai do escopo
            scopeManager->exitScope(globalFunctionName);
        }
    }

    void SemanticalAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx)
    {
        // Obtém o escopo global
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        // Guarda o nome do escopo atual (por exemplo, nome da função em que estamos)
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai da ArrowFunctionBlock é uma VarDeclaration
        if (auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            // Nome “original” da arrow function (o nome da variável que a recebeu)
            std::string arrowFunctionName = varDeclaration->varName->getText();

            // Cria um nome único para a função dentro do escopo global
            std::string fullyQualifiedName = iron::createFunctionName(currentScopeName, arrowFunctionName);

            // Se a assinatura da arrow function tiver tipo de retorno, definimos esse tipo;
            // caso contrário, assumimos VOID
            if (ctx->functionSignature()->functionReturnType())
            {
                std::string returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                globalScope->addSymbol(
                    fullyQualifiedName,
                    {tokenMap::FUNCTION,
                     tokenMap::getTokenType(returnTypeStr),
                     nullptr,
                     {},
                     arrowFunctionName});
            }
            else
            {
                globalScope->addSymbol(
                    fullyQualifiedName,
                    {tokenMap::FUNCTION,
                     tokenMap::VOID,
                     nullptr,
                     {},
                     arrowFunctionName});
            }

            // Entramos no escopo da nova função
            scopeManager->enterScope(fullyQualifiedName);

            // Se houver parâmetros na assinatura, visitamos para processar seus tipos
            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            // Se houver um bloco de statements, visitamos para processar cada instrução
            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList());
            }

            // Retornamos ao escopo anterior
            scopeManager->exitScope(fullyQualifiedName);
        }
    }

    void SemanticalAnalysis::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
        if (ctx->expr())
        {
            visitExpr(ctx->expr());
        }

        if (ctx->functionCall())
        {
            std::string functionName = ctx->functionCall()->functionName->getText();
            visitFunctionCall(ctx->functionCall(), functionName, scopeManager->currentScope());
        }
    }
}
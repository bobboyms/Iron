#include "headers/SemanticalAnalysis.h"
#include "headers/IronExceptions.h"
#include "headers/Colors.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"
#include <iostream>

// Construtor

namespace iron {


    SemanticalAnalysis::SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<iron::ScopeManager> scopeManager)
        : parser(parser), scopeManager(std::move(scopeManager)) {
    }

    // Destrutor
    SemanticalAnalysis::~SemanticalAnalysis() {
    }

    // Método principal para análise semântica
    void SemanticalAnalysis::analyze() {
        // Inicializa o escopo global

        scopeManager->enterScope(TokenMap::getTokenText(TokenMap::GLOBAL)); //start(TokenMap::getTokenText(TokenMap::GLOBAL));
        IronParser::ProgramContext* programContext = parser->program();

        // Processa todas as declarações no programa
        for (auto child : programContext->children) {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext*>(child)) {
                visitFunctionDeclaration(funcDecl);
            }
        }

        // Finaliza o escopo global após processar todas as declarações
        scopeManager->exitScope(TokenMap::getTokenText(TokenMap::GLOBAL));
    }

    void SemanticalAnalysis::visitStatementList(IronParser::StatementListContext* ctx) {
        for (auto child : ctx->children) {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(child)) {
                visitVarDeclaration(varDeclaration);
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
                visitVarAssignment(varAssignment);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext*>(child)) {
                visitExpr(expression);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnContext*>(child)) {
                visitReturn(returnctx);
            }
        }
    }

    void SemanticalAnalysis::visitExpr(IronParser::ExprContext* ctx) {
        // Estrutura que armazena informações sobre a última expressão/variável/função visitada
        struct LastExpressionInfo {
            std::string identifier; // Nome da variável, número ou função
            int dataType;           // Tipo de dado (ex.: TYPE_INT, NUMBER, FUNCTION, etc.)
            int symbolType;         // Tipo de símbolo (ex.: VARIABLE, FUNCTION, NUMBER, etc.)
        };

        // Mantido estático para preservar estado entre visitas dentro da mesma expressão
        static LastExpressionInfo lastExpr;

        int line = ctx->getStart()->getLine();

        // Função local para validar compatibilidade entre a "última expressão" e a expressão atual
        auto validateCompatibility = [&](const std::string& currentIdentifier,
                                        int currentDataType,
                                        int currentSymbolType,
                                        const std::string& scope)
        {
            // Verifica se a última expressão ainda existe no escopo
            auto optPreviousSymbol = scopeManager->currentScope()->lookup(lastExpr.identifier);
            if (!optPreviousSymbol.has_value()) {
                // Se não existe mais, limpamos a referência
                lastExpr.identifier.clear();
            } else {
                SymbolInfo previousSymbol = optPreviousSymbol.value();

                // Exemplo de regra: se um é numérico e o outro não é, gera incompatibilidade
                bool isCurrentNumber = TokenMap::isNumber(currentDataType);
                bool isPreviousNumber = TokenMap::isNumber(previousSymbol.dataType);

                if (isCurrentNumber != isPreviousNumber) {
                    std::string errorMessage;
                    if (currentSymbolType == TokenMap::FUNCTION) {
                        errorMessage = "Return type of function '{}' is incompatible with variable '{}'. Line: {}, Scope: {}";
                    } else if (currentSymbolType == TokenMap::VARIABLE) {
                        errorMessage = "Variable '{}' is incompatible with variable '{}'. Line: {}, Scope: {}";
                    } else if (currentSymbolType == TokenMap::NUMBER) {
                        errorMessage = "Number '{}' is incompatible with variable '{}'. Line: {}, Scope: {}";
                    }

                    throw TypeMismatchException(iron::format(
                        errorMessage,
                        color::colorText(currentIdentifier, color::BOLD_GREEN),
                        color::colorText(lastExpr.identifier, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("{} {}",
                                        TokenMap::getTokenText(TokenMap::FUNCTION),
                                        scope),
                            color::BOLD_YELLOW)
                    ));
                }
            }
        };

        // 1. Se o nó é apenas um nome de variável
        if (ctx->varName) {
            std::string varName = ctx->varName->getText();
            std::string currentScopeName = scopeManager->currentScopeName();
            auto optSymbolInfo = scopeManager->currentScope()->lookup(varName);

            if (!optSymbolInfo.has_value()) {
                throw VariableNotFoundException(iron::format(
                    "Variable '{}' not found. Line: {}",
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW))
                );
            }

            // Verifica compatibilidade com a última expressão visitada (se houver)
            if (!lastExpr.identifier.empty()) {
                SymbolInfo symbolInfo = optSymbolInfo.value();
                if (lastExpr.dataType == TokenMap::NUMBER) {
                    // Exemplo de validação: se a última expressão era "NUMBER" literal,
                    // e esta é uma variável não-numérica, dá erro.
                    if (!TokenMap::isNumber(symbolInfo.dataType)) {
                        throw TypeMismatchException(iron::format(
                            "Variable '{}' is incompatible with number '{}'. Line: {}, Scope: {}",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(lastExpr.identifier, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                iron::format("{} {}",
                                            TokenMap::getTokenText(TokenMap::FUNCTION),
                                            currentScopeName), 
                                color::BOLD_YELLOW)
                        ));
                    }
                } else {
                    validateCompatibility(varName, symbolInfo.dataType, symbolInfo.type, currentScopeName);
                }
            }

            // Atualiza o "último símbolo" com as infos desta variável
            SymbolInfo newSymbol = optSymbolInfo.value();
            lastExpr.identifier = varName;
            lastExpr.dataType   = newSymbol.dataType;
            lastExpr.symbolType = TokenMap::VARIABLE;
        }

        // 2. Se o nó é um número (literal)
        if (ctx->number()) {
            std::string numberLiteral = ctx->number()->getText();
            std::string currentScopeName = scopeManager->currentScopeName();

            // Se há uma última expressão, valida compatibilidade
            if (!lastExpr.identifier.empty()) {
                validateCompatibility(numberLiteral, TokenMap::NUMBER, TokenMap::NUMBER, currentScopeName);
            }

            // Atualiza o "último símbolo"
            lastExpr.identifier = numberLiteral;
            lastExpr.dataType   = TokenMap::NUMBER;
            lastExpr.symbolType = TokenMap::NUMBER;
        }

        // 3. Se o nó é uma chamada de função
        if (ctx->functionCall()) {
            std::string fnName = ctx->functionCall()->functionName->getText();
            std::string currentScopeName = scopeManager->currentScopeName();
            auto currentScope = scopeManager->currentScope();
            auto globalScope  = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

            std::string globalFunctionName;
            std::optional<SymbolInfo> optGlobalFunction;

            // Verifica se a função está declarada localmente com alias ou no global
            auto localLookup = currentScope->lookup(fnName);
            if (localLookup.has_value()) {
                if (localLookup.value().dataType == TokenMap::FUNCTION) {
                    globalFunctionName = localLookup->alias;
                    optGlobalFunction  = globalScope->lookup(globalFunctionName);
                } else {
                    // Se não é FUNCTION, tenta lookup no global direto
                    globalFunctionName = fnName;
                    optGlobalFunction = globalScope->lookup(globalFunctionName);
                }
            } else {
                throw FunctionNotFoundException(iron::format(
                    "Function '{}' not found. Line: {}, Scope: {}",
                    color::colorText(fnName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(
                        iron::format("{} {}",
                                    TokenMap::getTokenText(TokenMap::FUNCTION),
                                    currentScopeName),
                        color::BOLD_YELLOW)
                ));
            }

            if (!optGlobalFunction.has_value()) {
                throw FunctionNotFoundException(iron::format(
                    "Function '{}' not found. Line: {}, Scope: {}",
                    color::colorText(fnName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(
                        iron::format("{} {}",
                                    TokenMap::getTokenText(TokenMap::FUNCTION),
                                    currentScopeName),
                        color::BOLD_YELLOW)
                ));
            }

            // Verifica argumentos entrando no escopo da função
            const SymbolInfo& globalFunction = optGlobalFunction.value();
            scopeManager->enterScope(globalFunctionName);
            visitFunctionCall(ctx->functionCall(), globalFunctionName, currentScope);
            scopeManager->exitScope(globalFunctionName);

            // Verifica compatibilidade com a última expressão, se existir
            if (!lastExpr.identifier.empty()) {
                if (lastExpr.dataType == TokenMap::NUMBER) {
                    // Se a última expressão era um número literal,
                    // a função deve retornar tipo numérico
                    if (!TokenMap::isNumber(globalFunction.dataType)) {
                        throw TypeMismatchException(iron::format(
                            "Return type of function '{}' is incompatible with number '{}'. Line: {}, Scope: {}",
                            color::colorText(fnName, color::BOLD_GREEN),
                            color::colorText(lastExpr.identifier, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                iron::format("{} {}",
                                            TokenMap::getTokenText(TokenMap::FUNCTION),
                                            currentScope), 
                                color::BOLD_YELLOW)
                        ));
                    }
                } else {
                    // Caso contrário, usamos a função de validação
                    validateCompatibility(globalFunctionName, globalFunction.dataType, TokenMap::FUNCTION, currentScopeName);
                }
            }

            // Atualiza o "último símbolo"
            lastExpr.identifier = globalFunctionName;
            lastExpr.dataType   = globalFunction.dataType;
            lastExpr.symbolType = TokenMap::FUNCTION;
        }

        // 4. Visita subexpressões recursivamente
        for (auto child : ctx->children) {
            if (auto subExpr = dynamic_cast<IronParser::ExprContext*>(child)) {
                visitExpr(subExpr);
            }
        }

        // 5. Se este nó não tem pai (ou seja, é raiz na subárvore), limpamos o "último símbolo"
        if (ctx->parent == nullptr) {
            lastExpr.identifier.clear();
        }
    }



    void SemanticalAnalysis::visitVarAssignment(IronParser::VarAssignmentContext* ctx) {
        std::string varName = ctx->varName->getText();
        int line = ctx->getStart()->getLine();

        const std::string scope = scopeManager->currentScopeName();
        auto result = scopeManager->currentScope()->lookup(varName);

        if (result.has_value()) {
            SymbolInfo symbolInfo = result.value();
        } else {
            throw VariableNotFoundException(iron::format(
                "Variable '{}' not found. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    iron::format("{} {}", 
                        TokenMap::getTokenText(TokenMap::FUNCTION),
                        scope), 
                    color::BOLD_YELLOW)
            ));
        }
    }

    void SemanticalAnalysis::visitAssignment(IronParser::AssignmentContext* ctx) {
        int line = ctx->getStart()->getLine();

        // Visita todos os filhos que podem ser expressão ou arrow function
        for (auto child : ctx->children) {
            if (auto expr = dynamic_cast<IronParser::ExprContext*>(child)) {
                visitExpr(expr);
            } else if (auto arrowInline = dynamic_cast<IronParser::ArrowFunctionInlineContext*>(child)) {
                visitArrowFunctionInline(arrowInline);
            } else if (auto arrowBlock = dynamic_cast<IronParser::ArrowFunctionBlockContext*>(child)) {
                visitArrowFunctionBlock(arrowBlock);
            }
        }

        // Se houver um formato de dado literal (ex.: "3.14", "42", etc.)
        if (ctx->dataFormat()) {
            // Caso 1: a atribuição está sendo feita a um argumento de função
            if (auto* functionArg = dynamic_cast<IronParser::FunctionArgContext*>(ctx->parent)) {
                std::string argName      = functionArg->varName->getText();
                std::string argType      = functionArg->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType          = TokenMap::determineType(literalValue);

                // Se o argumento da função é um tipo real (float/double), mas o literal não é real
                if (TokenMap::isRealNumber(TokenMap::getTokenType(argType))) {
                    if (TokenMap::REAL_NUMBER != literalType) {
                        throw TypeMismatchException(iron::format(
                            "The argument '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                            color::colorText(argName, color::BOLD_GREEN),
                            color::colorText(argType, color::BOLD_GREEN),
                            color::colorText(literalValue, color::BOLD_GREEN),
                            color::colorText(TokenMap::getTokenText(literalType), color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                iron::format("fn {}", scopeManager->currentScopeName()), 
                                color::YELLOW
                            )
                        ));
                    }
                }
                // Se não for real, mas o tipo determinado do literal difere do tipo declarado
                else if (TokenMap::getTokenType(argType) != literalType) {
                    throw TypeMismatchException(iron::format(
                        "The argument '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(argType, color::BOLD_GREEN),
                        color::colorText(literalValue, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(literalType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("fn {}", scopeManager->currentScopeName()), 
                            color::YELLOW
                        )
                    ));
                }
            }

            // Caso 2: a atribuição está sendo feita a uma variável declarada
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent)) {
                std::string varName      = varDecl->varName->getText();
                std::string varType      = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType          = TokenMap::determineType(literalValue);

                // Se a variável é um tipo real, mas o literal não é real
                if (TokenMap::isRealNumber(TokenMap::getTokenType(varType))) {
                    if (TokenMap::REAL_NUMBER != literalType) {
                        throw TypeMismatchException(iron::format(
                            "The variable '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(literalValue, color::BOLD_GREEN),
                            color::colorText(TokenMap::getTokenText(literalType), color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                iron::format("fn {}", scopeManager->currentScopeName()), 
                                color::YELLOW
                            )
                        ));
                    }
                }
                // Se não for real, mas o tipo determinado do literal difere do tipo declarado
                else if (TokenMap::getTokenType(varType) != literalType) {
                    throw TypeMismatchException(iron::format(
                        "The variable '{}' is of type '{}', but the literal '{}' is '{}'. Line: {}, Scope: {}",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(varType, color::BOLD_GREEN),
                        color::colorText(literalValue, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(literalType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("fn {}", scopeManager->currentScopeName()), 
                            color::YELLOW
                        )
                    ));
                }
            }
        }
    }



    // Visita uma declaração de variável e verifica duplicatas
    void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext* ctx) {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        int line = ctx->getStart()->getLine();

        const std::string scopeName = scopeManager->currentScopeName();
        auto existingSymbol = scopeManager->currentScope()->lookupNoParent(varName);

        if (existingSymbol.has_value()) {
            throw VariableRedefinitionException(iron::format(
                    "Variable {} already declared. Line: {}, Scope: {}, Type: {}",
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeName, color::BOLD_YELLOW),
                    color::colorText(std::to_string(existingSymbol->type), color::CYAN)));
        }
        

        //auto arrowFunctionName = varDeclaration->varName->getText());
        if (TokenMap::getTokenType(varType) == TokenMap::FUNCTION) {
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            //iron::printf("VarName {} scopeName: {}", varName, scopeName);
            //auto localScope = scopeManager->getScopeByName(scopeName);
            scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr,{}, alias});
        } else {
            scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});
        }
        

        if (ctx->assignment()) {
            visitAssignment(ctx->assignment());
        } else {
            throw UninitializedVariableException(iron::format(
                "Variable {} has not been initialized. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
        }

        for (auto child : ctx->children) {
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
                visitVarAssignment(varAssignment);
            }
        }

        
    }


    void SemanticalAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx) {
        if (!ctx->functionName) {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();
        int line = ctx->functionName->getLine();

        // Verifica duplicata no escopo global antes de iniciar um novo escopo
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        auto result = globalScope->lookup(functionName);    


        if (result.has_value()) {
            throw FunctionRedefinitionException(iron::format(
                "Function {} already declared. Line: {}, Scope: {}",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
        }

        
        if (ctx->functionSignature()->functionReturnType()) {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::getTokenType(type), nullptr});
        } else {
            globalScope->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr});
        }
        

        scopeManager->enterScope(functionName);

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature());
        }

        for (auto child : ctx->children) {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
                visitStatementList(statementList);
            }
        }

        scopeManager->exitScope(functionName);
    }

    void SemanticalAnalysis::visitFunctionSignature(IronParser::FunctionSignatureContext* ctx) {
        for (auto child : ctx->children) {
            if (auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext*>(child)) {
                visitFunctionArgs(functionArgs);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionArgs(IronParser::FunctionArgsContext* ctx) {
        for (auto child : ctx->children) {
            if (auto functionArg = dynamic_cast<IronParser::FunctionArgContext*>(child)) {
                visitFunctionArg(functionArg);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionArg(IronParser::FunctionArgContext* ctx) {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();
        int line = ctx->getStart()->getLine();

        const std::string scope = scopeManager->currentScopeName();
        auto result = scopeManager->currentScope()->lookupNoParent(varName);



        if (result.has_value()) {
            SymbolInfo symbolInfo = result.value();

            if (symbolInfo.type == TokenMap::ARGUMENT) {
                throw VariableRedefinitionException(iron::format(
                    "Function arg {} already declared. Line: {}, Scope: fn {}",
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scope, color::BOLD_YELLOW),
                    color::colorText(TokenMap::getTokenText(symbolInfo.type), color::CYAN)));
                }
        }

        // adciona argumento da função ao escopo atual
        scopeManager->currentScope()->addSymbol(varName, {TokenMap::ARGUMENT, TokenMap::getTokenType(varType), nullptr});

        if (ctx->assignment()) {
            visitAssignment(ctx->assignment());
        }

        //adicionao argumento da função ao escopo global
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

        if (auto* globalFunctionPtr = globalScope->lookupPtr(scopeManager->currentScopeName())) {    
            globalFunctionPtr->args.emplace_back(varName, TokenMap::getTokenType(varType));
        }
    }

    void SemanticalAnalysis::visitFunctionCall(IronParser::FunctionCallContext* ctx,
                                            const std::string& actualFunctionName,
                                            std::shared_ptr<SymbolTable> parentScope)
    {

        auto line = ctx->getStart()->getLine();
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        auto globalFunctionSymbalInfo = globalScope->lookup(ctx->functionName->getText());

        SymbolInfo functionSymbolInfo = globalScope->lookup(actualFunctionName).value();
        auto globalArgsSize = functionSymbolInfo.args.size();
        // Se a call tem argumentos
        if (ctx->functionCallArgs()) {
            
            int callArgsSize = 0;
            for (auto child : ctx->functionCallArgs()->children) {
                if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
                    callArgsSize+=1;
                }
            }

            std::string aliasName = !functionSymbolInfo.alias.empty() ? functionSymbolInfo.alias : actualFunctionName;


            if (globalArgsSize != callArgsSize) {
                throw ArgumentCountMismatchException(iron::format(
                    "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                    color::colorText(
                        iron::format("fn {}", aliasName), color::BOLD_GREEN),
                    color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                    color::colorText(std::to_string(callArgsSize), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }
        
            visitFunctionCallArgs(ctx->functionCallArgs(), actualFunctionName, parentScope);
        } else {
            if (globalArgsSize > 0) {
                throw ArgumentCountMismatchException(iron::format(
                    "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                    color::colorText(
                        iron::format("fn {}", functionSymbolInfo.alias), color::BOLD_GREEN),
                    color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                    color::colorText(std::to_string(0), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }
        }
    }


    // Visita a lista de argumentos da função "actualFunctionName"
    void SemanticalAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx,
                                                const std::string& actualFunctionName,
                                                std::shared_ptr<SymbolTable> parentScope)
    {   
        
        for (auto child : ctx->children) {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
                visitFunctionCallArg(functionCallArg, actualFunctionName, parentScope);
            }
        }

        std::vector<std::string> sequenceOfArgs;
        for (auto child : ctx->children) {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
                sequenceOfArgs.push_back(functionCallArg->varName->getText());
            }
        }

        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        auto globalFunction = globalScope->lookup(actualFunctionName).value();
        auto args = globalFunction.args;

        for (size_t i = 0; i < args.size(); ++i) {
            if (sequenceOfArgs[i] != args[i].first) { // args[i].first é o nome do argumento formal
                throw ArgumentOrderMismatchException(iron::format(
                    "Argument order mismatch in function '{}'. Expected '{}', but got '{}'.",
                    color::colorText(iron::format("fn {}", globalFunction.alias),color::BOLD_GREEN),
                    color::colorText(args[i].first,color::BOLD_GREEN),
                    color::colorText(sequenceOfArgs[i], color::BOLD_GREEN)
                ));
            }
        }
    }

    // Visita um único argumento "argName" de "actualFunctionName"
    void SemanticalAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                                                const std::string& actualFunctionName,
                                                std::shared_ptr<SymbolTable> parentScope)
    {
        int line = ctx->getStart()->getLine();

        // Nome do parâmetro formal, conforme declarado na função
        std::string formalArgName = ctx->varName->getText();

        // Localiza o escopo global
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        if (!globalScope) {
            throw std::runtime_error("Global scope not found.");
        }

        // Busca a função (actualFunctionName) no escopo global
        auto globalFunctionOpt = globalScope->lookup(actualFunctionName);
        if (!globalFunctionOpt.has_value()) {
            throw FunctionNotFoundException(iron::format(
                "Function 'fn {}' not found. Line: {}",
                color::colorText(actualFunctionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)
            ));
        }

        // Verifica se 'formalArgName' é um parâmetro formal da função
        auto argOpt = iron::getArgumentByName(globalFunctionOpt.value(), formalArgName);
        if (!argOpt.has_value()) {
            throw FunctionArgNotFoundException(iron::format(
                "Argument '{}' not found in function 'fn {}'. Line: {}",
                color::colorText(formalArgName, color::BOLD_GREEN),
                color::colorText(actualFunctionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)
            ));
        }

        // Recupera o nome e o tipo esperado do parâmetro
        auto [expectedArgName, expectedArgType] = *argOpt;

        // Se o parser identificou 'dataFormat', verifique se o literal é compatível
        if (ctx->dataFormat()) {
            bool isIntLiteral  = ctx->dataFormat()->INT_NUMBER();
            bool isRealLiteral = ctx->dataFormat()->REAL_NUMBER();

            // Caso o tipo do parâmetro seja int, mas o literal não é INT_NUMBER
            if (expectedArgType == TokenMap::TYPE_INT && !isIntLiteral) {
                throw TypeMismatchException(iron::format(
                    "Argument '{}' is incompatible with type 'int'. Line: {}",
                    color::colorText(expectedArgName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }
            // Caso o tipo do parâmetro seja float/double, mas o literal não é REAL_NUMBER
            else if ((expectedArgType == TokenMap::TYPE_FLOAT || expectedArgType == TokenMap::TYPE_DOUBLE) && !isRealLiteral) {
                std::string floatTypeStr = (expectedArgType == TokenMap::TYPE_FLOAT) ? "float" : "double";
                throw TypeMismatchException(iron::format(
                    "Argument '{}' is incompatible with type '{}'. Line: {}",
                    color::colorText(expectedArgName, color::BOLD_GREEN),
                    color::colorText(floatTypeStr, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }
            // Se o literal é REAL_NUMBER, mas precisamos checar se é float ou double
            else if (isRealLiteral) {
                auto realLiteralType = TokenMap::determineFloatType(ctx->dataFormat()->REAL_NUMBER()->getText());
                if (realLiteralType != expectedArgType) {
                    throw TypeMismatchException(iron::format(
                        "Argument '{}' expects type '{}', but got '{}'. Line: {}",
                        color::colorText(expectedArgName, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(expectedArgType), color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(realLiteralType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }
            }
        }

        // Se o valor do argumento for outra variável
        if (ctx->anotherVarName) {
            std::string anotherVarName = ctx->anotherVarName->getText();
            auto anotherVarLookup = parentScope->lookup(anotherVarName);

            if (!anotherVarLookup.has_value()) {
                throw VariableNotFoundException(iron::format(
                    "Variable '{}' not found in scope 'fn {}'. Line: {}",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(parentScope->getName(), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }

            SymbolInfo varSymbolInfo = anotherVarLookup.value();
            if (varSymbolInfo.type != TokenMap::VARIABLE && varSymbolInfo.type != TokenMap::ARGUMENT) {
                throw VariableNotFoundException(iron::format(
                    "The '{}' is not a variable in scope 'fn {}'. Line: {}",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(parentScope->getName(), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }

            // Compara tipo do argumento esperado com o tipo da variável encontrada
            if (expectedArgType != varSymbolInfo.dataType) {
                throw TypeMismatchException(iron::format(
                    "Argument '{}' is incompatible with variable '{}'. Line: {}",
                    color::colorText(expectedArgName, color::BOLD_GREEN),
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }
        }

        // Se o valor do argumento for outra função
        if (ctx->functionCall()) {
            std::string innerFunctionName = ctx->functionCall()->functionName->getText();
            std::string resolvedFunctionName = innerFunctionName;

            // Verifica se a função está no escopo global; se não, tenta formá-la com o nome atual do escopo
            if (!globalScope->lookup(resolvedFunctionName).has_value()) {
                resolvedFunctionName = iron::createFunctionName(parentScope->getName(), innerFunctionName);
                if (!globalScope->lookup(resolvedFunctionName).has_value()) {
                    throw FunctionNotFoundException(iron::format(
                        "Function '{}' not found. Line: {}",
                        color::colorText(innerFunctionName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }
            }

            auto innerFunctionSymbolOpt = globalScope->lookup(resolvedFunctionName);
            if (!innerFunctionSymbolOpt.has_value()) {
                throw FunctionNotFoundException(iron::format(
                    "Function '{}' not found. Line: {}",
                    color::colorText(resolvedFunctionName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }

            // Visita a chamada de função
            visitFunctionCall(ctx->functionCall(), resolvedFunctionName, parentScope);
        }
    }

    void SemanticalAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx) {
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto* varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
            // Nome "original" da arrow function
            std::string arrowFuncName = varDeclaration->varName->getText();

            // Cria um nome único para a função no escopo global
            std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            if (ctx->functionSignature()->functionReturnType()) {
                std::string returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                globalScope->addSymbol(
                    globalFunctionName,
                    {
                        TokenMap::FUNCTION, 
                        TokenMap::getTokenType(returnTypeStr),
                        nullptr,
                        {},
                        arrowFuncName
                    }
                );
            } else {
                // Caso não haja tipo de retorno, define como VOID
                globalScope->addSymbol(
                    globalFunctionName,
                    {
                        TokenMap::FUNCTION, 
                        TokenMap::VOID, 
                        nullptr, 
                        {}, 
                        arrowFuncName
                    }
                );
            }

            // Entra no escopo da função inline
            scopeManager->enterScope(globalFunctionName);

            // Se houver assinatura (parâmetros), visite-a
            if (ctx->functionSignature()) {
                visitFunctionSignature(ctx->functionSignature());
            }

            // Se houver expressão (corpo inline), visite
            if (ctx->expr()) {
                visitExpr(ctx->expr());
            }

            // Sai do escopo
            scopeManager->exitScope(globalFunctionName);
        }
    }


    void SemanticalAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext* ctx) {
        // Obtém o escopo global
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        // Guarda o nome do escopo atual (por exemplo, nome da função em que estamos)
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai da ArrowFunctionBlock é uma VarDeclaration
        if (auto* varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
            // Nome “original” da arrow function (o nome da variável que a recebeu)
            std::string arrowFunctionName = varDeclaration->varName->getText();

            // Cria um nome único para a função dentro do escopo global
            std::string fullyQualifiedName = iron::createFunctionName(currentScopeName, arrowFunctionName);

            // Se a assinatura da arrow function tiver tipo de retorno, definimos esse tipo;
            // caso contrário, assumimos VOID
            if (ctx->functionSignature()->functionReturnType()) {
                std::string returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                globalScope->addSymbol(
                    fullyQualifiedName, 
                    {
                        TokenMap::FUNCTION,
                        TokenMap::getTokenType(returnTypeStr),
                        nullptr,
                        {},
                        arrowFunctionName
                    }
                );
            } else {
                globalScope->addSymbol(
                    fullyQualifiedName, 
                    {
                        TokenMap::FUNCTION,
                        TokenMap::VOID,
                        nullptr,
                        {},
                        arrowFunctionName
                    }
                );
            }

            // Entramos no escopo da nova função
            scopeManager->enterScope(fullyQualifiedName);

            // Se houver parâmetros na assinatura, visitamos para processar seus tipos
            if (ctx->functionSignature()) {
                visitFunctionSignature(ctx->functionSignature());
            }

            // Se houver um bloco de statements, visitamos para processar cada instrução
            if (ctx->statementList()) {
                visitStatementList(ctx->statementList());
            }

            // Retornamos ao escopo anterior
            scopeManager->exitScope(fullyQualifiedName);
        }
    }


    void SemanticalAnalysis::visitReturn(IronParser::ReturnContext* ctx) {
        if (ctx->expr()) {
            visitExpr(ctx->expr());
        }

        if (ctx->functionCall()) {
            std::string functionName = ctx->functionCall()->functionName->getText();
            visitFunctionCall(ctx->functionCall(), functionName, scopeManager->currentScope());
        }
    }
}
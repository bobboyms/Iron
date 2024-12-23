#include "headers/SemanticalAnalysis.h"
#include "headers/IronExceptions.h"
#include "headers/Colors.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"
#include <iostream>

// Construtor
SemanticalAnalysis::SemanticalAnalysis(std::unique_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager)
    : parser(std::move(parser)), scopeManager(std::move(scopeManager)) {
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
    }
}

void SemanticalAnalysis::visitExpr(IronParser::ExprContext* ctx) {
    struct PreviousVarStruct {
        std::string name;
        int localDatatype;
        int type;
    };

    static PreviousVarStruct reviousVarStruct;
    int line = ctx->getStart()->getLine();

    auto validatePreviousVariable = [&](const std::string& varName, int currentDatatype, int type, const std::string& scope) {
        auto optPreviousSymbolInfo = scopeManager->currentScope()->lookup(reviousVarStruct.name);

        if (!optPreviousSymbolInfo.has_value()) {
            reviousVarStruct.name.clear();
        } else {

            
            SymbolInfo previousSymbolInfo = optPreviousSymbolInfo.value();
            if (TokenMap::isNumber(currentDatatype) != TokenMap::isNumber(previousSymbolInfo.dataType)) {
                std::string errMessage;
                if (type == TokenMap::FUNCTION) {
                    errMessage =  "The return of fn {}:{}  is incompatible with Variable {}. Line: {}, Scope: {}";
                } else {
                    errMessage = "Variable {}:{} is incompatible with Variable {}. Line: {}, Scope: {}";
                }

                throw TypeMismatchException(iron::format(
                    errMessage,
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(TokenMap::getTokenText(currentDatatype), color::BOLD_GREEN),
                    color::colorText(reviousVarStruct.name, color::BOLD_GREEN),
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

    if (ctx->varName) {
        std::string varName = ctx->varName->getText();
        const std::string scope = scopeManager->currentScopeName();
        auto optSymbolInfo = scopeManager->currentScope()->lookup(varName);

        if (!optSymbolInfo.has_value()) {
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

        if (!reviousVarStruct.name.empty()) {
            SymbolInfo symbolInfo = optSymbolInfo.value();
            if (reviousVarStruct.localDatatype == TokenMap::NUMBER) {
                if (!TokenMap::isNumber(symbolInfo.dataType)) {
                    throw TypeMismatchException(iron::format(
                        "Variable {} is incompatible with Number {}. Line: {}, Scope: {}",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(reviousVarStruct.name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("{} {}", 
                                TokenMap::getTokenText(TokenMap::FUNCTION),
                                scope), 
                            color::BOLD_YELLOW)
                    ));
                }
            } else {
                validatePreviousVariable(varName, symbolInfo.dataType, symbolInfo.type, scope);
            }
        }

        reviousVarStruct.name = varName;
        reviousVarStruct.localDatatype = optSymbolInfo.value().dataType;
        reviousVarStruct.type = TokenMap::VARIABLE;
    }

    if (ctx->number()) {
        const std::string number = ctx->number()->getText();
        const std::string scope = scopeManager->currentScopeName();

        if (!reviousVarStruct.name.empty()) {
            validatePreviousVariable(number, TokenMap::NUMBER, TokenMap::NUMBER, scope);
        }

        reviousVarStruct.name = number;
        reviousVarStruct.localDatatype = TokenMap::NUMBER;
        reviousVarStruct.type = TokenMap::NUMBER;
    }

    if (ctx->functionCall()) {
        std::string functionName = ctx->functionCall()->functionName->getText();
        std::string currentScope = scopeManager->currentScopeName();
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

        if (!globalScope) {
            throw std::runtime_error("Global scope not found.");
        }

        auto result = globalScope->lookup(functionName);
        if (!result.has_value()) {
            throw VariableNotFoundException(iron::format(
                "Function '{}' not found. Line: {}, Scope: {}",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    iron::format("{} {}", 
                        TokenMap::getTokenText(TokenMap::FUNCTION),
                        currentScope), 
                    color::BOLD_YELLOW)
            ));
        }

        SymbolInfo globalFunction = result.value();
       // auto localFunction = scopeManager->currentScope()->lookup(functionName);

        //globalFunction.args.size();
        if (ctx->functionCall()->functionCallArgs()) {
            auto functionCallName = ctx->functionCall()->functionName->getText();
            scopeManager->enterScope(functionCallName);
            visitFunctionCallArgs(ctx->functionCall()->functionCallArgs());
            scopeManager->exitScope(functionCallName);
        }

        // Verifica compatibilidade com a variável anterior, se existir
        if (!reviousVarStruct.name.empty()) {
            if (reviousVarStruct.localDatatype == TokenMap::NUMBER) {
                // Se a variável anterior é um número, a função deve retornar um tipo numérico
                if (!TokenMap::isNumber(globalFunction.dataType)) {
                    throw TypeMismatchException(iron::format(
                        "Function return value {} is incompatible with Number {}. Line: {}, Scope: {}",
                        color::colorText(functionName, color::BOLD_GREEN),
                        color::colorText(reviousVarStruct.name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("{} {}",
                                TokenMap::getTokenText(TokenMap::FUNCTION),
                                currentScope),
                            color::BOLD_YELLOW)
                    ));
                }
            } else {
                // Caso contrário, valida com a função validatePreviousVariable
                validatePreviousVariable(functionName, globalFunction.dataType, TokenMap::FUNCTION, currentScope);
            }
        }

        reviousVarStruct.name = functionName;
        reviousVarStruct.localDatatype = globalFunction.dataType;
        reviousVarStruct.type = TokenMap::FUNCTION;
    }

    // Visita filhos recursivamente
    for (auto child : ctx->children) {
        if (auto expression = dynamic_cast<IronParser::ExprContext*>(child)) {
            visitExpr(expression);
        }
    }

    // Limpa a variável anterior ao sair do nó raiz
    if (ctx->parent == nullptr) {
        reviousVarStruct.name.clear();
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
    for (auto child : ctx->children) {
        if (auto expr = dynamic_cast<IronParser::ExprContext*>(child)) {
            visitExpr(expr);
        }
    }
}


// Visita uma declaração de variável e verifica duplicatas
void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext* ctx) {
    std::string varName = ctx->varName->getText();
    std::string varType = ctx->varTypes()->getText();

    int line = ctx->getStart()->getLine();

    

    const std::string scope = scopeManager->currentScopeName();
    auto result = scopeManager->currentScope()->lookup(varName);

    if (result.has_value()) {
        SymbolInfo symbolInfo = result.value();

        throw VariableRedefinitionException(iron::format(
            "Variable {} already declared. Line: {}, Scope: {}, Type: {}",
            color::colorText(varName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scope, color::BOLD_YELLOW),
            color::colorText(std::to_string(symbolInfo.type), color::CYAN)));
    }

    scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});

    for (auto child : ctx->children) {
        if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
            visitVarAssignment(varAssignment);
        }

        if (auto assignment = dynamic_cast<IronParser::AssignmentContext*>(child)) {
            visitAssignment(assignment);
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
        //iron::printf("1 Function: {}", functionName);
        visitFunctionSignature(ctx->functionSignature());
        //iron::printf("2 Function: {}", functionName);

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
    auto result = scopeManager->currentScope()->lookup(varName);

    //iron::printf("Function: {} VarName: {} VarType: {} Scope: {}", scope, varName, varType);

    if (result.has_value()) {
        SymbolInfo symbolInfo = result.value();

        throw VariableRedefinitionException(iron::format(
            "Function arg {} already declared. Line: {}, Scope: fn {}",
            color::colorText(varName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scope, color::BOLD_YELLOW),
            color::colorText(TokenMap::getTokenText(symbolInfo.type), color::CYAN)));
    }

    // adciona argumento da função ao escopo atual
    scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});


    //adicionao argumento da função ao escopo global
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

    if (auto* globalFunctionPtr = globalScope->lookupPtr(scopeManager->currentScopeName())) {    
        globalFunctionPtr->args.emplace_back(varName, TokenMap::getTokenType(varType));
    }
}

void SemanticalAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx) {
    for (auto child : ctx->children) {
        if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
            visitFunctionCallArg(functionCallArg);
        }
    }
}
void SemanticalAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx) {
    
    auto line = ctx->getStart()->getLine();
    auto functionCallName = scopeManager->currentScopeName();
    auto argName = ctx->varName->getText();
    //auto anotherVarName = ctx->anotherVarName->getText();
    
    
    auto globalFunction = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL))->lookup(functionCallName);

    if (!globalFunction.has_value()) {

        throw FunctionNotFoundException(iron::format(
            "Function fn {} not found. Line: {}",
            color::colorText(functionCallName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW)));
    }

    //valida se o argumento existe na função que está sendo chamada
    if (auto argOpt = iron::getArgumentByName(globalFunction.value(), argName)) {
        auto [foundArgName, foundArgType] = *argOpt;

        if (ctx->dataFormat()) {
            bool isIntLiteral = ctx->dataFormat()->INT_NUMBER();
            bool isRealLiteral = ctx->dataFormat()->REAL_NUMBER();

            if (foundArgType == TokenMap::TYPE_INT) {
                if (!isIntLiteral) {
                    iron::printf(
                        "Argument {} is incompatible with type int. Line: {}",
                        foundArgName,
                        line
                    );
                }
            }

            else if (foundArgType == TokenMap::TYPE_FLOAT || foundArgType == TokenMap::TYPE_DOUBLE) {
                if (!isRealLiteral) {
                    iron::printf(
                        "Argument {} is incompatible with type {}. Line: {}",
                        foundArgName,
                        (foundArgType == TokenMap::TYPE_FLOAT ? "float" : "double"),
                        line
                    );
                }
            }
        }
        
    } else {
        throw FunctionArgNotFoundException(iron::format(
            "Argument {} not found in function fn {}. Line: {}",
            color::colorText(argName, color::BOLD_GREEN),
            color::colorText(functionCallName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW)));
    }
}

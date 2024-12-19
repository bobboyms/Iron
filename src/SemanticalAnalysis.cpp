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
    static std::string previousVarName;

    if (ctx->varName) {
        std::string varName = ctx->varName->getText();
        int line = ctx->getStart()->getLine();

        if (auto variable = ctx->varName) {
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

            // Verificação segura da variável anterior
            if (!previousVarName.empty()) {
                auto optPreviousSymbolInfo = scopeManager->currentScope()->lookup(previousVarName);

                if (!optPreviousSymbolInfo.has_value()) {
                    previousVarName.clear();
                } else {
                    
                    SymbolInfo symbolInfo = optSymbolInfo.value();
                    SymbolInfo previousSymbolInfo = optPreviousSymbolInfo.value();

                    iron::printf("Previous variable: {}, Atual var name {}", previousVarName, varName);
                    iron::printf("Previous Type: {}, Atual Type {}", std::to_string(previousSymbolInfo.dataType), std::to_string(symbolInfo.dataType));
                    if (TokenMap::isNumber(symbolInfo.dataType) != TokenMap::isNumber(previousSymbolInfo.dataType)) {
                        throw TypeMismatchException(iron::format(
                            "Variable {} is incompatible with variable {}. Line: {}, Scope: {}",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(previousVarName, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(
                                iron::format("{} {}", 
                                    TokenMap::getTokenText(TokenMap::FUNCTION),
                                    scope), 
                                    color::BOLD_YELLOW)
                        ));
                    }
                }
            }

            previousVarName = varName;
        }
    }

    if (ctx->number()) {
        iron::printf("numero: {}", ctx->number()->getText());
    }

    for (auto child : ctx->children) {
        if (auto expression = dynamic_cast<IronParser::ExprContext*>(child)) {
            visitExpr(expression);
        }
    }

    // Limpa a variável anterior ao sair do nó raiz
    if (ctx->parent == nullptr) {
        previousVarName.clear();
    }
}

void SemanticalAnalysis::visitVarAssignment(IronParser::VarAssignmentContext* ctx) {
    std::string varName = ctx->varName->getText();
    int line = ctx->getStart()->getLine();

    const std::string scope = scopeManager->currentScopeName();
    auto result = scopeManager->currentScope()->lookup(varName);

    if (result.has_value()) {
        SymbolInfo symbolInfo = result.value();

        // Aqui você pode adicionar lógica para verificar tipos ou realizar outras validações
        iron::printf("Variable '{}' found in scope '{}', type: '{}'.\n",
                     color::colorText(varName, color::BOLD_GREEN),
                     color::colorText(scope, color::BOLD_YELLOW),
                     color::colorText(std::to_string(symbolInfo.type), color::CYAN));
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
    
    iron::printf("Declaration varName: {}, varType: {}", varName, TokenMap::getTokenType(varType));

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
        if (auto assignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
            visitVarAssignment(assignment);
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
    auto result = scopeManager->currentScope()->lookup(functionName);

    if (result.has_value()) {
        throw FunctionRedefinitionException(iron::format(
            "Function {} already declared. Line: {}, Scope: {}",
            color::colorText(functionName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
    }

    // Adiciona a função ao escopo global
    scopeManager->currentScope()->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr});

    // Inicia um novo escopo para o corpo da função
    scopeManager->enterScope(functionName);

    // Processa o corpo da função
    for (auto child : ctx->children) {
        if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
            visitStatementList(statementList);
        }
    }

    // Finaliza o escopo ao sair da função
    scopeManager->exitScope(functionName);
}


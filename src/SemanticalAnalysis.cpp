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

    scopeManager->start(TokenMap::getTokenText(TokenMap::GLOBAL));
    IronParser::ProgramContext* programContext = parser->program();

    // Processa todas as declarações no programa
    for (auto child : programContext->children) {
        if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext*>(child)) {
            visitFunctionDeclaration(funcDecl);
        }
    }

    // Finaliza o escopo global após processar todas as declarações
    scopeManager->end();
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
            SymbolInfo* symbolInfo = scopeManager->lookupSymbol(varName);

            if (!symbolInfo) {
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
                SymbolInfo* previousSymbolInfo = scopeManager->lookupSymbol(previousVarName);

                if (!previousSymbolInfo) {
                    previousVarName.clear();
                } else {
                    if (TokenMap::isNumber(symbolInfo->type) != TokenMap::isNumber(previousSymbolInfo->type)) {
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
    SymbolInfo* symbolInfo = scopeManager->lookupSymbol(varName);
    if (!symbolInfo) {
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

    if (scopeManager->lookupSymbol(varName)) {
        
        const std::string scope = scopeManager->currentScopeName();
        SymbolInfo* SymbolInfo = scopeManager->lookupSymbol(scope);

        throw VariableRedefinitionException(iron::format("Variable {} already declared. Line: {}, {}", 
            color::colorText(varName,color::BOLD_GREEN), std::to_string(line) ,
            color::colorText(iron::format("{} {}", SymbolInfo->type ,scope),color::BOLD_YELLOW)));
    }

    scopeManager->addSymbol(varName, TokenMap::getTokenType(varType), scopeManager->currentScopeName(), line);

    for (auto child : ctx->children) {
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
    if (scopeManager->lookupSymbol(functionName)) {
        throw FunctionRedefinitionException(iron::format("Function {} already declared. Line: {}, {}", 
            functionName, std::to_string(line),scopeManager->currentScopeName()));
    }

    // Adiciona a função ao escopo global
    scopeManager->addSymbol(functionName, TokenMap::FUNCTION, TokenMap::getTokenText(TokenMap::GLOBAL), line);

    // Inicia um novo escopo para o corpo da função
    scopeManager->start(functionName);

    // Processa o corpo da função
    for (auto child : ctx->children) {
        if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
            visitStatementList(statementList);
        }
    }

    // Finaliza o escopo ao sair da função
    scopeManager->end();
}

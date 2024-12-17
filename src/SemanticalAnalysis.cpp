#include "headers/SemanticalAnalysis.h"
#include "headers/SemanticException.h"
#include "Utils.cpp"
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
    scopeManager->start("global");

    IronParser::ProgramContext* programContext = parser->program();

    // Processa todas as declarações no programa
    for (auto child : programContext->children) {
        if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext*>(child)) {
            visitFunctionDeclaration(funcDecl);
        }
    }

    // Finaliza o escopo global após processar todas as declarações
    //scopeManager->printTable();
    scopeManager->end();
}

// Visita uma lista de declarações dentro de uma função
void SemanticalAnalysis::visitStatementList(IronParser::StatementListContext* ctx) {
    for (auto child : ctx->children) {
        if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(child)) {
            visitVarDeclaration(varDeclaration);
        }
    }
}

// Visita uma declaração de variável e verifica duplicatas
void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext* ctx) {
    std::string varName = ctx->varName->getText();
    std::string varType = ctx->varTypes()->getText();

    int line = ctx->getStart()->getLine();

    if (scopeManager->lookupSymbol(varName)) {
        throw VariableRedefinitionException(iron::format("Variable {} already declared. Line: {}, {}", 
            varName, std::to_string(line),scopeManager->currentScopeName()));
    }

    scopeManager->addSymbol(varName, varType, scopeManager->currentScopeName(), line);
}

void SemanticalAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx) {
    std::string functionName = ctx->functionName->getText();
    int line = ctx->functionName->getLine();

    // Verifica duplicata no escopo global antes de iniciar um novo escopo
    if (scopeManager->lookupSymbol(functionName)) {
        throw FunctionRedefinitionException(iron::format("Function {} already declared. Line: {}, {}", 
            functionName, std::to_string(line),scopeManager->currentScopeName()));
    }

    // Adiciona a função ao escopo global
    scopeManager->addSymbol(functionName, "function", "global", line);

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



#include "headers/ScopeManager.h"

// Inicia um novo escopo
void ScopeManager::start(const std::string& scopeName) {
    scopeStack.emplace_back();       // Adiciona um novo mapa vazio para o novo escopo
    scopeNameStack.push(scopeName);  // Adiciona o nome do escopo à pilha
}

// Finaliza o escopo atual
void ScopeManager::end() {
    if (!scopeStack.empty()) {
        scopeStack.pop_back();       // Remove o escopo atual
        scopeNameStack.pop();        // Remove o nome do escopo atual
    } 
}

// Retorna o nome do escopo atual
std::string ScopeManager::currentScopeName() const {
    if (!scopeNameStack.empty()) {
        return scopeNameStack.top();
    }
    throw ScopeNotFoundException(color::colorText("Semantic error: scope not found", color::RED));
}

// Adiciona um símbolo ao escopo atual
bool ScopeManager::addSymbol(const std::string& name, const int type, const std::string& scope, int line) {
    if (scopeStack.empty()) {
        return false;
    }

    auto& currentScope = scopeStack.back();

    currentScope[name] = {type, scope, line};
    return true;
}

// Busca um símbolo nos escopos aninhados
SymbolInfo* ScopeManager::lookupSymbol(const std::string& name) {
    for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}

// Imprime a tabela de símbolos
void ScopeManager::printTable() const {
    std::cout << "\n--- Tabela de Símbolos ---" << std::endl;

    int scopeLevel = scopeStack.size();
    for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it, --scopeLevel) {
        std::cout << "Escopo #" << scopeLevel << " (" << scopeNameStack.top() << "):\n";
        for (const auto& [name, info] : *it) {
            std::cout << "  Nome: " << name
                      << ", Tipo: " << info.type
                      << ", Escopo: " << info.scope
                      << ", Linha: " << info.line << std::endl;
        }
    }

    std::cout << "--- Fim da Tabela ---\n" << std::endl;
}

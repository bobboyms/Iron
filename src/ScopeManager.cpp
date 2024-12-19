#include "headers/ScopeManager.h"

// Implementação da classe SymbolTable
SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> parentScope)
    : parent(parentScope) {}

void SymbolTable::addSymbol(const std::string& name, const SymbolInfo& info) {
    if (symbols.find(name) != symbols.end()) {
        throw std::runtime_error("Symbol '" + name + "' already defined in the current scope.");
    }
    symbols[name] = info;
}

std::optional<SymbolInfo> SymbolTable::lookup(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    if (parent) {
        return parent->lookup(name);
    }
    return std::nullopt;
}

void SymbolTable::printSymbols(const std::string& scopeName) const {
    std::cout << "Scope: " << scopeName << "\n";
    for (const auto& [name, info] : symbols) {
        std::cout << "  Name: " << name << ", Type: " << info.type
                  << ", Data Type: " << info.dataType << "\n";
    }
    std::cout << "---\n";
}

// Implementação da classe ScopeManager
void ScopeManager::enterScope(const std::string& scopeName) {
    auto newScope = std::make_shared<SymbolTable>(currentScope());
    scopeStack.push(newScope);
    std::cout << "Entered scope: " << scopeName << "\n";
}

void ScopeManager::exitScope(const std::string& scopeName) {
    if (!scopeStack.empty()) {
        scopeStack.pop();
        std::cout << "Exited scope: " << scopeName << "\n";
    } else {
        throw std::runtime_error("Attempted to exit a non-existent scope.");
    }
}

std::shared_ptr<SymbolTable> ScopeManager::currentScope() const {
    if (!scopeStack.empty()) {
        return scopeStack.top();
    }
    return nullptr;
}

std::string ScopeManager::currentScopeName() const {
    if (!scopeStack.empty()) {
        return "Current Scope";
    }
    return "Global";
}

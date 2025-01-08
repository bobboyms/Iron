#include "../headers/ScopeManager.h"
#include <stdexcept>

// -----------------------------------------------------
// Implementação da classe SymbolTable
// -----------------------------------------------------

namespace iron {
    // Construtor sem nome (compatível com seu código original)
    SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> parentScope)
        : name(""), parent(parentScope)
    {
    }

    // Construtor adicional que recebe nome do escopo
    SymbolTable::SymbolTable(const std::string& scopeName, std::shared_ptr<SymbolTable> parentScope)
        : name(scopeName), parent(parentScope)
    {
    }

    void SymbolTable::addSymbol(const std::string& name, const SymbolInfo& info) {
        if (symbols.find(name) != symbols.end()) {
            throw std::runtime_error("Symbol '" + name + "' already defined in the current scope.");
        }
        symbols[name] = info;
    }

    SymbolInfo* SymbolTable::lookupPtr(const std::string& name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return &it->second;  // Ponteiro para o objeto dentro do map
        }
        if (parent) {
            return parent->lookupPtr(name);
        }
        return nullptr;
    }

    std::optional<SymbolInfo> SymbolTable::lookup(const std::string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return it->second; // Retorna cópia do SymbolInfo
        }
        if (parent) {
            return parent->lookup(name);
        }
        return std::nullopt;
    }

    std::optional<SymbolInfo> SymbolTable::lookupNoParent(const std::string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return it->second; // Retorna cópia do SymbolInfo
        }
        return std::nullopt;
    }

    void SymbolTable::printSymbols(const std::string& scopeName) const {
        std::cout << "Scope: " << scopeName << "\n";
        for (const auto& [symName, info] : symbols) {
            std::cout << "  Name: " << symName
                    << ", Type: " << info.type
                    << ", Data Type: " << info.dataType << "\n";
        }
        std::cout << "---\n";
    }

    // -----------------------------------------------------
    // Implementação da classe ScopeManager
    // -----------------------------------------------------

    void ScopeManager::enterScope(const std::string& scopeName) {
        // Se quiser criar sem nome, use a versão sem scopeName:
        // auto newScope = std::make_shared<SymbolTable>(currentScope());

        // Mas se quer aproveitar a "nome do escopo", use o construtor com scopeName:
        auto newScope = std::make_shared<SymbolTable>(scopeName, currentScope());
        scopeStack.push({scopeName, newScope});
        scopeMap[scopeName] = newScope; 
        // std::cout << "Entered scope: " << scopeName << "\n";
    }

    void ScopeManager::exitScope(const std::string& scopeName) {
        if (!scopeStack.empty()) {
            auto topScope = scopeStack.top();
            scopeStack.pop();

            // Se o topo da pilha corresponde ao escopo que desejamos sair
            if (topScope.first == scopeName) {
                scopeMap.erase(scopeName);
                // std::cout << "Exited scope: " << scopeName << "\n";
            } else {
                // Exceção se tentou sair de outro escopo
                throw std::runtime_error("Attempted to exit a scope that is not on top of the stack.");
            }
        } else {
            throw std::runtime_error("Attempted to exit a non-existent scope.");
        }
    }

    std::shared_ptr<SymbolTable> ScopeManager::currentScope() const {
        if (!scopeStack.empty()) {
            return scopeStack.top().second;
        }
        return nullptr;
    }

    std::string ScopeManager::currentScopeName() const {
        if (!scopeStack.empty()) {
            return scopeStack.top().first;
        }
        return "Global";
    }

    std::shared_ptr<SymbolTable> ScopeManager::getScopeByName(const std::string& scopeName) const {
        auto it = scopeMap.find(scopeName);
        if (it != scopeMap.end()) {
            return it->second;
        }
        return nullptr;
    }

}

#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include <stack>
#include "IronExceptions.h"
#include "Colors.h"

// Estrutura para armazenar informações de símbolos
struct SymbolInfo {
    int type;
    int dataType;
    std::shared_ptr<class SymbolTable> scope;
};

// Classe para representar a Tabela de Símbolos
class SymbolTable {
private:
    std::unordered_map<std::string, SymbolInfo> symbols;
    std::shared_ptr<SymbolTable> parent;

public:
    SymbolTable(std::shared_ptr<SymbolTable> parentScope = nullptr);
    void addSymbol(const std::string& name, const SymbolInfo& info);
    std::optional<SymbolInfo> lookup(const std::string& name) const;
    void printSymbols(const std::string& scopeName) const;
};

// Gerenciador de escopos usando uma pilha
class ScopeManager {
private:
    std::stack<std::shared_ptr<SymbolTable>> scopeStack;

public:
    void enterScope(const std::string& scopeName);
    void exitScope(const std::string& scopeName);
    std::shared_ptr<SymbolTable> currentScope() const;
    std::string currentScopeName() const;
};

#endif // SCOPE_MANAGER_H

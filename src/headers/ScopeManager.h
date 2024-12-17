#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <iostream>

// Estrutura para armazenar informações sobre um símbolo
struct SymbolInfo {
    std::string type;
    std::string scope;
    int line;
};

class ScopeManager {
private:
    std::vector<std::unordered_map<std::string, SymbolInfo>> scopeStack;
    std::stack<std::string> scopeNameStack; // Pilha de nomes dos escopos

public:
    void start(const std::string& scopeName);
    void end();
    std::string currentScopeName() const;

    bool addSymbol(const std::string& name, const std::string& type, const std::string& scope, int line);
    bool removeSymbol(const std::string& name);
    SymbolInfo* lookupSymbol(const std::string& name);
    void printTable() const;
};

#endif // SCOPE_MANAGER_H

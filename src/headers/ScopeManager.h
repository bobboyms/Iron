#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include "SymbolTable.h"

namespace iron
{
    // ---------------------------------------------------------------------
    // Gerenciador de escopos usando uma pilha
    // ---------------------------------------------------------------------
    class ScopeManager
    {
    private:
        // Pilha de pares <nome_do_escopo, SymbolTable>
        std::stack<std::pair<std::string, std::shared_ptr<SymbolTable>>> scopeStack;

        // Mapa para acessar escopos pelo nome
        std::unordered_map<std::string, std::shared_ptr<SymbolTable>> scopeMap;

    public:
        // Entra em um novo escopo
        void enterScope(const std::string &scopeName);

        // Sai do escopo especificado (deve ser o topo)
        void exitScope(const std::string &scopeName);

        // Retorna o escopo atual (topo da pilha)
        std::shared_ptr<SymbolTable> currentScope() const;

        // Retorna o nome do escopo atual
        std::string currentScopeName() const;

        // Recupera escopo pelo nome (se ainda existir)
        std::shared_ptr<SymbolTable> getScopeByName(const std::string &scopeName) const;
    };

}

#endif // SCOPE_MANAGER_H

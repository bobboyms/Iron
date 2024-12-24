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

// ---------------------------------------------------------------------
// Estrutura para armazenar informações de símbolos
// ---------------------------------------------------------------------
struct SymbolInfo {
    int type;
    int dataType;
    std::shared_ptr<class SymbolTable> scope;
    std::vector<std::pair<std::string, int>> args;
};

// ---------------------------------------------------------------------
// Classe para representar a Tabela de Símbolos
// ---------------------------------------------------------------------
class SymbolTable {
private:
    // (Opcional) nome do escopo, se você quiser armazenar
    std::string name;
    std::unordered_map<std::string, SymbolInfo> symbols;
    std::shared_ptr<SymbolTable> parent;

public:
    // Construtor padrão (sem nome), mantendo compatibilidade com o código original
    SymbolTable(std::shared_ptr<SymbolTable> parentScope = nullptr);

    // Construtor adicional que recebe um nome de escopo
    SymbolTable(const std::string& scopeName, std::shared_ptr<SymbolTable> parentScope);

    // Adiciona símbolo ao escopo
    void addSymbol(const std::string& name, const SymbolInfo& info);

    // Exibe todos os símbolos
    void printSymbols(const std::string& scopeName) const;

    // Busca (por cópia) com std::optional
    std::optional<SymbolInfo> lookup(const std::string& name) const;

    // Busca retornando ponteiro (útil para modificações diretas)
    SymbolInfo* lookupPtr(const std::string& name);

    // Getter para o pai (caso você queira acessar)
    std::shared_ptr<SymbolTable> getParent() const { return parent; }

    // Getter para o nome do escopo (caso queira usar)
    const std::string& getName() const { return name; }
};

// ---------------------------------------------------------------------
// Gerenciador de escopos usando uma pilha
// ---------------------------------------------------------------------
class ScopeManager {
private:
    // Pilha de pares <nome_do_escopo, SymbolTable>
    std::stack<std::pair<std::string, std::shared_ptr<SymbolTable>>> scopeStack;

    // Mapa para acessar escopos pelo nome
    std::unordered_map<std::string, std::shared_ptr<SymbolTable>> scopeMap;

public:
    // Entra em um novo escopo
    void enterScope(const std::string& scopeName);

    // Sai do escopo especificado (deve ser o topo)
    void exitScope(const std::string& scopeName);

    // Retorna o escopo atual (topo da pilha)
    std::shared_ptr<SymbolTable> currentScope() const;

    // Retorna o nome do escopo atual
    std::string currentScopeName() const;

    // Recupera escopo pelo nome (se ainda existir)
    std::shared_ptr<SymbolTable> getScopeByName(const std::string& scopeName) const;
};

class Store
{
private:
    std::shared_ptr<SymbolTable> _symbolTable;

public:

    std::shared_ptr<SymbolTable> symbolTable() const {
        return _symbolTable;
    }


    void storeSymbolTable(const std::shared_ptr<SymbolTable>& symbolTable) {
        if (_symbolTable) {
            throw std::runtime_error("Store already holds a SymbolTable!");
        }
        _symbolTable = symbolTable;
    }

    void releaseSymbolTable() {
        _symbolTable.reset();
    }
};




#endif // SCOPE_MANAGER_H

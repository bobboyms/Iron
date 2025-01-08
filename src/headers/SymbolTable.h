#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include <stack>
#include <llvm/IR/Instructions.h>
#include "IronExceptions.h"
#include "Colors.h"

namespace iron
{
    // ---------------------------------------------------------------------
    // Estrutura para armazenar informações de símbolos
    // ---------------------------------------------------------------------
    struct SymbolInfo
    {
        int type;
        int dataType;
        std::shared_ptr<class SymbolTable> scope;
        std::vector<std::pair<std::string, int>> args;
        std::string alias;
        llvm::AllocaInst *alloca;
    };
    class SymbolTable
    {
    private:
        // (Opcional) nome do escopo, se você quiser armazenar
        std::string name;
        std::unordered_map<std::string, SymbolInfo> symbols;
        std::shared_ptr<SymbolTable> parent;

    public:
        // Construtor padrão (sem nome), mantendo compatibilidade com o código original
        SymbolTable(std::shared_ptr<SymbolTable> parentScope = nullptr);

        // Construtor adicional que recebe um nome de escopo
        SymbolTable(const std::string &scopeName, std::shared_ptr<SymbolTable> parentScope);

        // Adiciona símbolo ao escopo
        void addSymbol(const std::string &name, const SymbolInfo &info);

        // Exibe todos os símbolos
        void printSymbols(const std::string &scopeName) const;

        // Busca (por cópia) com std::optional
        std::optional<SymbolInfo> lookup(const std::string &name) const;

        std::optional<SymbolInfo> lookupNoParent(const std::string &name) const;

        // Busca retornando ponteiro (útil para modificações diretas)
        SymbolInfo *lookupPtr(const std::string &name);

        // Getter para o pai (caso você queira acessar)
        std::shared_ptr<SymbolTable> getParent() const { return parent; }

        // Getter para o nome do escopo (caso queira usar)
        const std::string &getName() const { return name; }
    };

}

#endif
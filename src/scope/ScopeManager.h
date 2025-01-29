#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include "../headers/TokenMap.h"
#include <iostream>

namespace scope
{

    class Function;

    class Parent : public std::enable_shared_from_this<Parent>
    {
    protected:
        std::weak_ptr<Parent> parent;

    public:
        virtual ~Parent() = default; // Destruidor virtual padrão

        // Método para definir o pai
        virtual void setParent(std::shared_ptr<Parent> newParent) = 0;

        // Método para obter o pai
        std::shared_ptr<Parent> getParent() const
        {
            return parent.lock();
        }
    };

    class GlobalScope : public Parent
    {
    protected:
        std::string name;
        int type;

    public:
        std::string getName();
        int getType();

        GlobalScope() = default;
        ~GlobalScope() = default;

        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    struct Variable
    {
        std::string name;
        int type;
        std::shared_ptr<Function> function;

        Variable(const std::string &name, int type) : name(name), type(type) {}
    };

    class LocalScope : public Parent
    {
    protected:
        int type;

    public:
        int getType();

        LocalScope() = default;
        ~LocalScope() = default;

        std::shared_ptr<LocalScope> upperScope;

        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    class Statements : public LocalScope
    {
    protected:
        std::vector<std::shared_ptr<Variable>> variables;

    public:
        void addVariable(const std::string &name, int type);
        void addFunctionAlias(const std::string varName, std::shared_ptr<Function> function);
        std::shared_ptr<Variable> getVariable(const std::string &name);

        Statements();
        ~Statements();

        std::shared_ptr<Statements> upperScope;

        int getScopeType();
    };

    struct CallArg
    {
        std::string name;
        int type;

        CallArg(const std::string name, int type) : name(name), type(type) {}
    };

    class FunctionCall : public LocalScope
    {
    protected:
        std::string name;
        std::shared_ptr<Function> function;
        // std::vector<std::shared_ptr<CallArg>> callArgs;

    public:
        std::shared_ptr<Function> getFunction();

        FunctionCall(std::string name, std::shared_ptr<Function> function);
        ~FunctionCall();

        std::string getName();
    };

    struct FunctionArg
    {
        std::string name;
        int type;

        FunctionArg(const std::string &name, int type) : name(name), type(type) {}
    };

    class Function : public GlobalScope
    {
    private:
        std::stack<std::shared_ptr<LocalScope>> scopeStack;
        // Mapa para acessar escopos pelo nome
        std::unordered_map<std::string, std::shared_ptr<LocalScope>> scopeMap;

    protected:
        std::shared_ptr<Function> upperFunction;
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> args;
        int returnType;

    public:
        Function(std::string name, std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> args, int returnType);
        ~Function();
        std::string getFunctionName();
        int getReturnType();
        void setUpperFunction(std::shared_ptr<Function> function);
        void enterLocalScope(std::shared_ptr<LocalScope> scope);
        std::shared_ptr<LocalScope> getCurrentLocalScope();
        void exitLocalScope();

        std::shared_ptr<FunctionArg> getArgByName(const std::string argName);
        std::shared_ptr<Variable> findVarCurrentScopeAndArg(const std::string varName);
        std::shared_ptr<Variable> findVarAllScopesAndArg(const std::string varName);
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> getArgs();

        std::string getScopeName();
        int getScopeType();
    };

    class ScopeManager
    {
    private:
        std::vector<std::shared_ptr<Function>> functionDeclarations;
        std::stack<std::shared_ptr<GlobalScope>> scopeStack;
        // Mapa para acessar escopos pelo nome
        std::unordered_map<std::string, std::shared_ptr<GlobalScope>> scopeMap;

    public:
        void addFunctionDeclaration(std::shared_ptr<Function> function);
        std::shared_ptr<Function> getFunctionDeclarationByName(std::string functionName);
        std::shared_ptr<Function> currentFunctionDeclarationBy();
        void enterScope(std::shared_ptr<GlobalScope> scope);
        void exitScope();
        std::string currentScopeName() const;
        std::shared_ptr<GlobalScope> currentScope() const;
        std::shared_ptr<GlobalScope> getScopeByName(const std::string &scopeName) const;
    };

}

#endif // SCOPE_MANAGER_H

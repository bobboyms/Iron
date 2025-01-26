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
            return parent.lock(); // Retorna um shared_ptr se o pai ainda existir
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

        Variable(const std::string &name, int type) : name(name), type(type) {}
    };

    class LocalScope : public Parent
    {
    protected:
        std::string name;
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

    class Variables : public LocalScope
    {
    protected:
        std::vector<std::shared_ptr<Variable>> variables;

    public:
        void addVariable(const std::string &name, int type);
        std::shared_ptr<Variable> getVariable(const std::string &name);

        Variables();
        ~Variables();

        std::shared_ptr<Variables> upperScope;

        std::string getScopeName();
        int getScopeType();
    };

    class FunctionCall : public LocalScope
    {
    protected:
        std::shared_ptr<Function> function;

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
        // Armazena ponteiros inteligentes para preservar polimorfismo
        std::vector<std::shared_ptr<LocalScope>> localScope;

    protected:
        std::vector<std::shared_ptr<FunctionArg>> args;
        int returnType;

    public:
        Function(std::string name, std::vector<std::shared_ptr<FunctionArg>> callArgs, int returnType);
        ~Function();
        std::string getFunctionName();
        int getReturnType();

        void enterLocalScope(std::shared_ptr<LocalScope> scope);
        std::shared_ptr<LocalScope> getCurrentLocalScope();
        void exitLocalScope();

        std::shared_ptr<FunctionArg> getArgByName(const std::string argName);

        std::shared_ptr<Variable> findVarAllScopesAndArg(const std::string varName);
        std::shared_ptr<FunctionCall> findFuncCallAllScopes(const std::string callName);
        std::vector<std::shared_ptr<FunctionArg>> getArgs();

        std::string getScopeName();
        int getScopeType();
    };

    class ScopeManager
    {
    private:
        std::stack<std::shared_ptr<GlobalScope>> scopeStack;
        // Mapa para acessar escopos pelo nome
        std::unordered_map<std::string, std::shared_ptr<GlobalScope>> scopeMap;

    public:
        void enterScope(std::shared_ptr<GlobalScope> scope);
        void exitScope();
        std::string currentScopeName() const;
        std::shared_ptr<GlobalScope> currentScope() const;
        std::shared_ptr<GlobalScope> getScopeByName(const std::string &scopeName) const;
    };

}

#endif // SCOPE_MANAGER_H

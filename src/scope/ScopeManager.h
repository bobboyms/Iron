#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include <iostream>
#include "../headers/TokenMap.h"

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
        int getType() const;

        GlobalScope() = default;
        ~GlobalScope() override = default;

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

        Variable(const std::string &name, const int type) : name(name), type(type)
        {
        }
    };

    class LocalScope : public Parent
    {
    protected:
        int type{};

    public:
        int getType() const;

        LocalScope() = default;
        ~LocalScope() override = default;

        std::shared_ptr<LocalScope> upperScope;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    class Statements final : public LocalScope
    {
    protected:
        std::vector<std::shared_ptr<Variable>> variables;

    public:
        void addVariable(const std::string &name, int type);
        void addFunctionAlias(const std::string& varName, const std::shared_ptr<Function>& function);
        std::shared_ptr<Variable> getVariable(const std::string &name);

        Statements();
        ~Statements() override;

        std::shared_ptr<Statements> upperScope;

        int getScopeType() const;
    };

    struct CallArg
    {
        std::string name;
        int type;

        CallArg(std::string  name, const int type) : name(std::move(name)), type(type)
        {
        }
    };

    class FunctionCall final : public LocalScope
    {
    protected:
        std::string name;
        std::shared_ptr<Function> function;
        // std::vector<std::shared_ptr<CallArg>> callArgs;

    public:
        std::shared_ptr<Function> getFunction();

        FunctionCall(const std::string &name, const std::shared_ptr<Function> &function);
        ~FunctionCall() override;

        std::string getName();
    };

    struct FunctionArg
    {
        std::string name;
        int type;

        FunctionArg(std::string name, const int type) : name(std::move(name)), type(type)
        {
        }
    };

    class Function final : public GlobalScope
    {
    private:
        bool returnTokenFound = false;
        std::stack<std::shared_ptr<LocalScope>> scopeStack;
        std::unordered_map<std::string, std::shared_ptr<LocalScope>> scopeMap;
        bool external;
        bool variedArguments;

    protected:
        std::shared_ptr<Variable> alias;
        std::shared_ptr<Function> upperFunction;
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> args;
        int returnType;

    public:
        Function(const std::string &name, const std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> &args, int returnType);
        ~Function() override;
        std::string getFunctionName();
        int getReturnType() const;
        void setUpperFunction(const std::shared_ptr<Function>& function);
        void enterLocalScope(const std::shared_ptr<LocalScope>& scope);
        std::shared_ptr<LocalScope> getCurrentLocalScope();
        bool isReturnTokenFound() const;
        void updateReturnTokenStatusToFound();
        void exitLocalScope();
        void setAlias(const std::shared_ptr<Variable>& alias);
        std::shared_ptr<Variable> getAlias();

        std::shared_ptr<FunctionArg> getArgByName(const std::string &argName) const;
        std::shared_ptr<Variable> findVarCurrentScopeAndArg(const std::string &varName);
        std::shared_ptr<Variable> findVarAllScopesAndArg(const std::string &varName);
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> getArgs();
        std::shared_ptr<Function> getUpperFunction();

        bool isExternal() const;
        void changeToExternal();
        bool isVariedArguments() const;
        void changeToVariedArguments();

        std::string getScopeName();
        int getScopeType() const;
    };

    class ScopeManager
    {
    private:
        std::vector<std::shared_ptr<Function>> functionDeclarations;
        std::unordered_map<std::string, std::shared_ptr<Function>> externDeclarations;
        std::stack<std::shared_ptr<GlobalScope>> scopeStack;
        // Mapa para acessar escopos pelo nome
        std::unordered_map<std::string, std::shared_ptr<GlobalScope>> scopeMap;

    public:
        void addFunctionDeclaration(const std::shared_ptr<Function>& function);
        std::shared_ptr<Function> getFunctionDeclarationByName(const std::string& functionName);
        std::shared_ptr<Function> currentFunctionDeclaration();
        void enterScope(const std::shared_ptr<GlobalScope>& scope);
        void exitScope();
        std::string currentScopeName() const;
        std::shared_ptr<GlobalScope> currentScope() const;
        std::shared_ptr<GlobalScope> getScopeByName(const std::string &scopeName) const;
        std::vector<std::shared_ptr<Function>> getFunctionDeclarations();

        void setExternDeclaration(const std::shared_ptr<Function> &declarations);

    };

} // namespace scope

#endif // SCOPE_MANAGER_H

#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include <iostream>
#include "../headers/TokenMap.h"

namespace scope
{

    class Function;

    class FunctionArg;

    class StructStemt;

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
        bool mut{false};
        std::shared_ptr<Function> function;
        std::shared_ptr<StructStemt> structStemt;

        Variable(const std::string &name, const int type) : name(name), type(type)
        {
        }

        Variable(const std::string &name, const int type, const bool mut) : name(name), type(type), mut(mut)
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
        void addVariable(const std::string &name, int type, bool mut);
        void addFunctionAlias(const std::string &varName, const std::shared_ptr<Function> &function);
        std::shared_ptr<Variable> getVariable(const std::string &name);

        Statements();
        ~Statements() override;
        void addVariable(const std::shared_ptr<scope::Variable> &variable);

        std::shared_ptr<Statements> upperScope;

        int getScopeType() const;
    };

    struct CallArg
    {
        std::string name;
        int type;

        CallArg(std::string name, const int type) : name(std::move(name)), type(type)
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


    // struct SignatureArg
    // {
    //     int returnType;
    //     std::vector<int> argTypes;
    //
    //
    // };


    class Signature
    {
    protected:
        int returnType;
        std::vector<std::shared_ptr<FunctionArg>> arguments;

    public:
        Signature(int returnType, const std::vector<std::shared_ptr<FunctionArg>> &arguments);
        int getReturnType() const;
        int getArgumentCount() const;
        std::vector<std::shared_ptr<FunctionArg>> getArguments();
        std::shared_ptr<FunctionArg> getArgumentByName(const std::string &name);
    };

    struct FunctionArg
    {
        int type;
        std::string name;
        std::shared_ptr<Signature> signature;

        FunctionArg(std::string name, const int type) : type(type), name(std::move(name))
        {
        }

        FunctionArg(std::string name, const int type, const std::shared_ptr<Signature> &signature) :
            type(type), name(std::move(name)), signature(signature)
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
        std::vector<std::shared_ptr<StructStemt>> structs;
        int returnType;
        bool returnFound{false};

    public:
        Function(const std::string &name, const std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> &args,
                 int returnType);
        ~Function() override;
        std::string getFunctionName();
        int getReturnType() const;
        void setUpperFunction(const std::shared_ptr<Function> &function);
        void enterLocalScope(const std::shared_ptr<LocalScope> &scope);
        std::shared_ptr<LocalScope> getCurrentLocalScope();
        bool isReturnTokenFound() const;
        void updateReturnTokenStatusToFound();
        void exitLocalScope();
        void setAlias(const std::shared_ptr<Variable> &alias);
        std::shared_ptr<Variable> getAlias();

        std::shared_ptr<FunctionArg> getArgByName(const std::string &argName) const;
        std::shared_ptr<Variable> findVarCurrentScopeAndArg(const std::string &varName);
        std::shared_ptr<Variable> findVarAllScopesAndArg(const std::string &varName);
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> getArgs();
        std::shared_ptr<Function> getUpperFunction();

        bool isReturnFound();
        void changeToReturnFound();
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
        std::vector<std::shared_ptr<StructStemt>> structDeclarations;
        std::vector<std::shared_ptr<Function>> functionDeclarations;
        std::unordered_map<std::string, std::shared_ptr<Function>> externDeclarations;
        std::stack<std::shared_ptr<GlobalScope>> scopeStack;
        // Mapa para acessar escopos pelo nome
        std::unordered_map<std::string, std::shared_ptr<GlobalScope>> scopeMap;

    public:
        void addFunctionDeclaration(const std::shared_ptr<Function> &function);
        void addStructDeclaration(const std::shared_ptr<StructStemt> &struct_);

        std::shared_ptr<Function> getFunctionDeclarationByName(const std::string &functionName);
        std::shared_ptr<StructStemt> getStructDeclarationByName(const std::string &name) const;
        std::shared_ptr<Function> currentFunctionDeclaration();
        void enterScope(const std::shared_ptr<GlobalScope> &scope);
        void exitScope();
        std::string currentScopeName() const;
        std::shared_ptr<GlobalScope> currentScope() const;
        std::shared_ptr<GlobalScope> getScopeByName(const std::string &scopeName) const;
        std::vector<std::shared_ptr<Function>> getFunctionDeclarations();

        void setExternDeclaration(const std::shared_ptr<Function> &declarations);
    };

    class StructStemt
    {
    private:
        std::vector<std::shared_ptr<Variable>> variables;
    public:
        std::string name;
        explicit StructStemt(const std::string &name);
        void setVariables(const std::vector<std::shared_ptr<Variable>> &variables);

        std::shared_ptr<Variable> getVarByName(const std::string &varName) const;
        std::vector<std::shared_ptr<Variable>> getVariables();
    };

} // namespace scope

#endif // SCOPE_MANAGER_H

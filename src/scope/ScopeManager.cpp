#include "ScopeManager.h"

#include <stack>
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

namespace scope
{
    //
    // GlobalScope
    //
    std::string GlobalScope::getName()
    {
        return name;
    }

    int GlobalScope::getType()
    {
        return type;
    }

    //
    // LocalScope
    //
    int LocalScope::getType()
    {
        return type;
    }

    //
    // Variables
    //
    Variables::Variables()
    {
        // Construtor
    }

    Variables::~Variables()
    {
        // Destrutor
    }

    void Variables::addVariable(const std::string &varName, int varType)
    {
        variables.push_back(std::make_shared<Variable>(varName, varType));
        this->name = varName;
        this->type = tokenMap::VARIABLE;
    }

    std::shared_ptr<Variable> Variables::getVariable(const std::string &varName)
    {
        for (auto &var : variables)
        {
            if (var->name == varName)
            {
                return var;
            }
        }
        return nullptr; // Não encontrado
    }

    std::string Variables::getScopeName()
    {
        return this->name;
    }

    int Variables::getScopeType()
    {
        return this->type;
    }

    FunctionCall::FunctionCall(const std::string name, std::shared_ptr<Function> function)
    {
        // Define o nome do escopo usando o método da classe base
        this->name = name;
        this->type = tokenMap::FUNCTION_CALL;

        // Armazena a referência à função chamada
        this->function = function;
    }

    FunctionCall::~FunctionCall()
    {
        // Destrutor
    }

    std::shared_ptr<Function> FunctionCall::getFunction()
    {
        return function;
    }

    std::string FunctionCall::getName()
    {
        return this->name;
    }

    //
    // Function
    //

    std::vector<std::shared_ptr<FunctionArg>> Function::getArgs()
    {
        return args;
    }

    Function::Function(std::string funcName,
                       std::vector<std::shared_ptr<FunctionArg>> callArgs,
                       int returnType)
    {
        // Ajusta o nome e o tipo do escopo (herdado de GlobalScope)
        this->name = funcName;
        // Você pode definir 'type' para algum valor que identifique a função
        // Exemplo: this->type = 2; (caso queira indicar que 2 = "Function")
        this->type = 2;

        // Armazena os argumentos e o tipo de retorno
        this->args = callArgs;
        this->returnType = returnType;
    }

    Function::~Function()
    {
        // Destrutor
    }

    std::string Function::getFunctionName()
    {
        return this->name;
    }

    int Function::getReturnType()
    {
        return this->returnType;
    }

    std::shared_ptr<Variable> Function::findVarAllScopesAndArg(const std::string varName)
    {
        auto localScope = getCurrentLocalScope();
        while (localScope)
        {
            auto variable = std::dynamic_pointer_cast<Variables>(localScope);
            if (variable)
            {
                auto var = variable->getVariable(varName);
                if (var)
                {
                    return var;
                }
            }
            localScope = localScope->upperScope;
        }

        auto arg = getArgByName(varName);
        if (arg)
        {
            return std::make_shared<Variable>(arg->name, arg->type);
        }

        return nullptr;
    }

    std::shared_ptr<FunctionCall> Function::findFuncCallAllScopes(const std::string callName)
    {
        auto localScope = getCurrentLocalScope();
        while (localScope)
        {
            auto funcCall = std::dynamic_pointer_cast<FunctionCall>(localScope);
            if (funcCall)
            {
                if (funcCall->getName() == callName)
                {
                    return funcCall;
                }
            }
            localScope = localScope->upperScope;
        }

        return nullptr;
    }

    void Function::enterLocalScope(std::shared_ptr<LocalScope> scope)
    {
        if (!localScope.empty())
        {
            // Define o upperScope do novo escopo para o escopo atual
            scope->upperScope = localScope.back();
        }
        // Armazena o ponteiro diretamente para evitar cópia
        localScope.push_back(scope);
    }

    std::shared_ptr<LocalScope> Function::getCurrentLocalScope()
    {
        if (localScope.empty())
        {
            return nullptr;
        }
        // Retorna o ponteiro do último escopo inserido
        return localScope.back();
    }

    void Function::exitLocalScope()
    {
        if (!localScope.empty())
        {
            localScope.pop_back();
        }
    }

    std::shared_ptr<FunctionArg> Function::getArgByName(const std::string argName)
    {
        for (auto &arg : args)
        {
            if (arg->name == argName)
            {
                return arg;
            }
        }
        return nullptr; // Não encontrado
    }

    std::string Function::getScopeName()
    {
        return this->name;
    }

    int Function::getScopeType()
    {
        return this->type;
    }

    //
    // ScopeManager
    //
    void ScopeManager::enterScope(std::shared_ptr<GlobalScope> scope)
    {
        // Empilha o novo escopo
        scopeStack.push(scope);
        // Armazena no mapa para acesso direto pelo nome
        scopeMap[scope->getName()] = scope;
    }

    void ScopeManager::exitScope()
    {
        if (!scopeStack.empty())
        {
            scopeStack.pop();
        }
    }

    std::string ScopeManager::currentScopeName() const
    {
        if (!scopeStack.empty())
        {
            return scopeStack.top()->getName();
        }
        return ""; // Nenhum escopo atual
    }

    std::shared_ptr<GlobalScope> ScopeManager::currentScope() const
    {
        if (!scopeStack.empty())
        {
            return scopeStack.top();
        }
        return nullptr; // Nenhum escopo atual
    }

    std::shared_ptr<GlobalScope> ScopeManager::getScopeByName(const std::string &scopeName) const
    {
        auto it = scopeMap.find(scopeName);
        if (it != scopeMap.end())
        {
            return it->second;
        }
        return nullptr; // Não encontrado
    }

} // namespace scope

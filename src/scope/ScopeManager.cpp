#include "ScopeManager.h"
#include "../headers/Utils.h"

#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>

namespace scope
{

    /* ----------------------------- PARENT ----------------------------- */
    // No extra implementation here beyond the pure virtual setParent (implemented by derived classes)
    // and the getParent() function that is already defined inline in the header.

    /* --------------------------- GLOBALSCOPE --------------------------- */
    std::string GlobalScope::getName()
    {
        return name;
    }

    int GlobalScope::getType() const
    {
        return type;
    }

    // The constructor and destructor are defaulted in the header, so no extra code is needed here.
    // setParent is also defined inline in the header.

    /* --------------------------- LOCAL SCOPE --------------------------- */
    int LocalScope::getType() const
    {
        return type;
    }

    // The constructor and destructor are defaulted in the header, so no extra code is needed.
    // setParent is also defined inline in the header.

    /* --------------------------- STATEMENTS ---------------------------- */

    Statements::Statements() = default;

    Statements::~Statements() = default;

    void Statements::addVariable(const std::string &name, int type)
    {

        if (name.empty())
        {
            throw std::runtime_error(util::format("Statements::addVariable. Variable name is empty", ""));
        }
        variables.push_back(std::make_shared<Variable>(name, type));
    }

    void Statements::addFunctionAlias(const std::string& varName, const std::shared_ptr<Function>& function)
    {

        if (!function)
        {
            throw std::runtime_error(util::format("Statements::addFunctionAlias. Function is empty", ""));
        }

        const auto variable = getVariable(varName);
        if (!variable)
        {
            throw std::runtime_error(util::format("Statements::addFunctionAlias. Variable {} not found", varName));
        }

        variable->function = function;
    }

    std::shared_ptr<Variable> Statements::getVariable(const std::string &name)
    {
        for (auto &var: variables)
        {
            if (var->name == name)
            {
                return var;
            }
        }
        return nullptr;
    }

    int Statements::getScopeType() const
    {
        return this->getType();
    }

    /* --------------------------- FUNCTION CALL -------------------------- */

    // but does not store 'name' anywhere in the class. We need a member to hold it:
    //   private: std::string callName;
    // Make sure you add that to the class definition if it isn't there yet.

    FunctionCall::FunctionCall(const std::string &name, const std::shared_ptr<Function> &function) :
        name(name), function(function)
    {
    }

    FunctionCall::~FunctionCall() = default;

    std::string FunctionCall::getName()
    {
        return name;
    }
    Signature::Signature(const int returnType, const std::vector<std::shared_ptr<FunctionArg>> &arguments):
        returnType(returnType),arguments(arguments)
    {

    }
    int Signature::getReturnType() const
    {
        return returnType;
    }
    int Signature::getArgumentCount() const
    {
        return arguments.size();
    }

    std::vector<std::shared_ptr<FunctionArg>> Signature::getArguments()
    {
        return arguments;
    }

    std::shared_ptr<FunctionArg> Signature::getArgumentByName(const std::string &name)
    {
        for (auto &arg: arguments)
        {
            if (arg->name == name)
            {
                return arg;
            }
        }

        return nullptr;
    }

    std::shared_ptr<Function> FunctionCall::getFunction()
    {
        return function;
    }

    /* ------------------------------ FUNCTION ---------------------------- */

    Function::Function(const std::string &name, const std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> &args,
                       const int returnType) : args(args), returnType(returnType)
    {
        this->name = name;
        this->variedArguments = false;
        this->external = false;
    }

    Function::~Function() = default;

    bool Function::isReturnTokenFound() const
    {
        return returnTokenFound;
    }

    void Function::updateReturnTokenStatusToFound()
    {
        returnTokenFound = true;
    }

    std::string Function::getFunctionName()
    {
        return name; // 'name' is inherited from GlobalScope
    }

    int Function::getReturnType() const
    {
        return returnType;
    }

    void Function::setUpperFunction(const std::shared_ptr<Function>& function)
    {
        if (!function)
        {
            throw std::runtime_error(util::format("Function::setUpperFunction. Function is null", ""));
        }

        upperFunction = function;
    }

    void Function::enterLocalScope(const std::shared_ptr<LocalScope>& scope)
    {
        if (!scope)
        {
            throw std::runtime_error(util::format("Function::enterLocalScope. Scope is null", ""));
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        scope->setParent(parentPtr);

        if (const auto functionPtr = std::dynamic_pointer_cast<Function>(parentPtr); !functionPtr)
        {
            throw std::runtime_error("Function::enterLocalScope. Failed to cast Parent to Function.");
        }

        scopeStack.push(scope);
    }

    std::shared_ptr<LocalScope> Function::getCurrentLocalScope()
    {
        if (!scopeStack.empty())
        {
            return scopeStack.top();
        }
        return nullptr;
    }

    void Function::exitLocalScope()
    {
        if (!scopeStack.empty())
        {
            scopeStack.pop();
        }
    }
    void Function::setAlias(const std::shared_ptr<Variable> &alias)
    {
        if (!alias)
            throw std::runtime_error(util::format("Function::setAlias. Alias is null", ""));
        this->alias = alias;
    }

    std::shared_ptr<Variable> Function::getAlias()
    {
        return alias;
    }

    std::shared_ptr<FunctionArg> Function::getArgByName(const std::string &argName) const
    {

        for (auto arg: *args)
        {
            if (arg->name == argName)
            {
                return arg;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Variable> Function::findVarCurrentScopeAndArg(const std::string &varName)
    {
        if (const auto statement = std::dynamic_pointer_cast<Statements>(getCurrentLocalScope()))
        {
            if (auto var = statement->getVariable(varName))
            {
                return var;
            }
        }

        if (const auto arg = getArgByName(varName))
        {
            if (arg->signature)
            {
                const auto args = std::make_shared<std::vector<std::shared_ptr<FunctionArg>>>();
                for (auto arg: arg->signature->getArguments())
                {
                    args->push_back(arg);
                }

                const auto function = std::make_shared<Function>(arg->name,args, arg->signature->getReturnType());
                const auto variable = std::make_shared<Variable>(arg->name, arg->type);
                variable->function = function;
                return variable;
            }

            return std::make_shared<Variable>(arg->name, arg->type);
        }

        return nullptr;
    }

    std::shared_ptr<Variable> Function::findVarAllScopesAndArg(const std::string &varName)
    {

        // verifica no escopo local e superiores
        std::stack<std::shared_ptr<LocalScope>> tempStack(scopeStack);
        while (!tempStack.empty())
        {
            auto currentScope = tempStack.top();
            tempStack.pop();

            if (const auto statementsScope = std::dynamic_pointer_cast<Statements>(currentScope))
            {
                if (auto var = statementsScope->getVariable(varName))
                {
                    return var;
                }
            }
        }

        // verifica nos argumentos da função
        if (const auto arg = getArgByName(varName))
        {
            if (arg->signature)
            {
                const auto args = std::make_shared<std::vector<std::shared_ptr<FunctionArg>>>();
                for (auto arg: arg->signature->getArguments())
                {
                    args->push_back(arg);
                }

                const auto function = std::make_shared<Function>(arg->name,args, arg->signature->getReturnType());
                const auto variable = std::make_shared<Variable>(arg->name, arg->type);
                variable->function = function;
                return variable;
            }

            return std::make_shared<Variable>(arg->name, arg->type);
        }

        if (upperFunction)
        {
            return upperFunction->findVarAllScopesAndArg(varName);
        }

        return nullptr;
    }

    std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> Function::getArgs()
    {
        return args;
    }

    std::shared_ptr<Function> Function::getUpperFunction()
    {
        return upperFunction;
    }

    bool Function::isExternal() const
    {
        return external;
    }

    void Function::changeToExternal()
    {
        external = true;
    }
    bool Function::isVariedArguments() const
    {
        return variedArguments;
    }
    void Function::changeToVariedArguments()
    {
        variedArguments = true;
    }

    std::string Function::getScopeName()
    {
        return name;
    }

    int Function::getScopeType() const
    {
        return type;
    }

    /* --------------------------- SCOPE MANAGER -------------------------- */

    void ScopeManager::enterScope(const std::shared_ptr<GlobalScope>& scope)
    {
        if (!scope)
        {
            throw std::runtime_error(util::format("ScopeManager::enterScope. Scope is empty", ""));
        }


        scopeStack.push(scope);
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
        return ""; // No scope in stack
    }

    std::shared_ptr<GlobalScope> ScopeManager::currentScope() const
    {
        if (!scopeStack.empty())
        {
            return scopeStack.top();
        }
        return nullptr;
    }

    std::shared_ptr<GlobalScope> ScopeManager::getScopeByName(const std::string &scopeName) const
    {
        if (const auto it = scopeMap.find(scopeName); it != scopeMap.end())
        {
            return it->second;
        }

        return nullptr;
    }
    std::vector<std::shared_ptr<Function>> ScopeManager::getFunctionDeclarations()
    {
        return functionDeclarations;
    }
    void ScopeManager::setExternDeclaration(const std::shared_ptr<Function> &declarations)
    {
        externDeclarations.insert({declarations->getFunctionName(), declarations});
    }

    void ScopeManager::addFunctionDeclaration(const std::shared_ptr<Function> &function)
    {
        functionDeclarations.push_back(function);
    }

    // std::shared_ptr<Function> ScopeManager::getFunctionDeclarationByName(const std::string &functionName)
    // {
    //     for (auto function: functionDeclarations)
    //     {
    //         if (function->getFunctionName() == functionName)
    //         {
    //             return function;
    //         }
    //     }
    //
    //     if (const auto it = externDeclarations.find(functionName); it != externDeclarations.end())
    //     {
    //         return it->second;
    //     }
    //
    //     // auto variable = currentFunctionDeclarationBy(); //->findVarCurrentScopeAndArg(functionName);
    //     if (!currentScope())
    //     {
    //         return nullptr;
    //     }
    //
    //     const auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope());
    //     if (!currentFunction)
    //     {
    //         return nullptr;
    //     }
    //
    //     const auto variable = currentFunction->findVarAllScopesAndArg(functionName);
    //     if (!variable)
    //     {
    //         return nullptr;
    //     }
    //
    //     if (variable->type == tokenMap::FUNCTION)
    //     {
    //         return variable->function;
    //     }
    //
    //
    //     return nullptr;
    // }

    std::shared_ptr<Function> ScopeManager::getFunctionDeclarationByName(const std::string &functionName)
    {
        // 1. Primeiro, busca nas variáveis e nos escopos locais/anteriores.
        if (currentScope())
        {
            // Presume-se que o escopo atual seja uma função (ou pertença a ela)
            if (const auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope()))
            {
                // findVarAllScopesAndArg já faz a busca no escopo atual e nos escopos acima.
                if (const auto variable = currentFunction->findVarAllScopesAndArg(functionName);
                    variable && variable->type == tokenMap::FUNCTION)
                {
                    return variable->function;
                }
            }
        }

        // 2. Se não foi encontrada entre as variáveis locais ou dos escopos acima,
        //    busca nas declarações globais de função.
        for (auto function : functionDeclarations)
        {
            if (function->getFunctionName() == functionName)
            {
                return function;
            }
        }

        // 3. Por fim, verifica se há uma declaração externa com esse nome.
        if (const auto it = externDeclarations.find(functionName); it != externDeclarations.end())
        {
            return it->second;
        }

        // Se não encontrou em nenhum dos casos, retorna nullptr.
        return nullptr;
    }


    std::shared_ptr<Function> ScopeManager::currentFunctionDeclaration()
    {
        if (functionDeclarations.empty())
        {
            return nullptr;
        }

        return functionDeclarations.back();
    }

} // namespace scope

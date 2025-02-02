#include "ScopeManager.h"
#include "../headers/Utils.h"

#include <stack>
#include <unordered_map>
#include <memory>
#include <iostream>

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

    int GlobalScope::getType()
    {
        return type;
    }

    // The constructor and destructor are defaulted in the header, so no extra code is needed here.
    // setParent is also defined inline in the header.

    /* --------------------------- LOCAL SCOPE --------------------------- */
    int LocalScope::getType()
    {
        return type;
    }

    // The constructor and destructor are defaulted in the header, so no extra code is needed.
    // setParent is also defined inline in the header.

    /* --------------------------- STATEMENTS ---------------------------- */

    Statements::Statements()
    {
        // Constructor body, if needed
    }

    Statements::~Statements()
    {
        // Destructor body, if needed
    }

    void Statements::addVariable(const std::string &name, int type)
    {

        if (name.empty())
        {
            throw std::runtime_error(util::format("Statements::addVariable. Variable name is empty", ""));
        }
        variables.push_back(std::make_shared<Variable>(name, type));
    }

    void Statements::addFunctionAlias(const std::string varName, std::shared_ptr<Function> function)
    {

        if (!function)
        {
            throw std::runtime_error(util::format("Statements::addFunctionAlias. Function is empty", ""));
        }

        auto variable = getVariable(varName);
        if (!variable)
        {
            throw std::runtime_error(util::format("Variable {} not found", varName));
        }

        variable->function = function;
    }

    std::shared_ptr<Variable> Statements::getVariable(const std::string &name)
    {
        for (auto &var : variables)
        {
            if (var->name == name)
            {
                return var;
            }
        }
        return nullptr; // Not found
    }

    int Statements::getScopeType()
    {
        return this->getType();
    }

    /* --------------------------- FUNCTION CALL -------------------------- */

    // Note: The header mentions a constructor FunctionCall(std::string name, std::shared_ptr<Function> function),
    // but does not store 'name' anywhere in the class. We need a member to hold it:
    //   private: std::string callName;
    // Make sure you add that to the class definition if it isn't there yet.

    FunctionCall::FunctionCall(std::string name, std::shared_ptr<Function> function)
        : name(name), function(function)
    {
        // If you need to store the name in a member variable, do so here.
        // E.g.: this->callName = name;
    }

    FunctionCall::~FunctionCall()
    {
    }

    std::string FunctionCall::getName()
    {
        return name;
    }

    std::shared_ptr<Function> FunctionCall::getFunction()
    {
        return function;
    }

    /* ------------------------------ FUNCTION ---------------------------- */

    Function::Function(std::string name,
                       std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> args,
                       int returnType)
        : args(args),
          returnType(returnType)
    {
        this->name = name;
    }

    Function::~Function()
    {
        // Destructor body if needed
    }

    std::string Function::getFunctionName()
    {
        return name; // 'name' is inherited from GlobalScope
    }

    int Function::getReturnType()
    {
        return returnType;
    }

    void Function::setUpperFunction(std::shared_ptr<Function> function)
    {
        if (!function)
        {
            throw std::runtime_error(util::format("Function::setUpperFunction. Function is null", ""));
        }

        upperFunction = function;
    }

    void Function::enterLocalScope(std::shared_ptr<LocalScope> scope)
    {
        if (!scope)
        {
            throw std::runtime_error(util::format("Function::enterLocalScope. Scope is null", ""));
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        scope->setParent(parentPtr);

        auto functionPtr = std::dynamic_pointer_cast<Function>(parentPtr);
        if (!functionPtr)
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

    std::shared_ptr<FunctionArg> Function::getArgByName(const std::string argName)
    {

        for (auto arg : *args)
        {
            if (arg->name == argName)
            {
                return arg;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Variable> Function::findVarCurrentScopeAndArg(const std::string varName)
    {
        auto statement = std::dynamic_pointer_cast<Statements>(getCurrentLocalScope());
        if (statement)
        {
            auto var = statement->getVariable(varName);
            if (var)
            {
                return var;
            }
        }

        auto arg = getArgByName(varName);
        if (arg)
        {
            return std::make_shared<Variable>(arg->name, arg->type);
        }

        return nullptr;
    }

    std::shared_ptr<Variable> Function::findVarAllScopesAndArg(const std::string varName)
    {

        // verifica no escopo local e superiores
        std::stack<std::shared_ptr<LocalScope>> tempStack(scopeStack);
        while (!tempStack.empty())
        {
            auto currentScope = tempStack.top();
            tempStack.pop();

            auto statementsScope = std::dynamic_pointer_cast<Statements>(currentScope);
            if (statementsScope)
            {
                auto var = statementsScope->getVariable(varName);
                if (var)
                {
                    return var;
                }
            }
        }

        // verifica nos argumentos da função
        auto arg = getArgByName(varName);
        if (arg)
        {
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

    std::string Function::getScopeName()
    {
        // For a function, let's just return its name
        return name;
    }

    int Function::getScopeType()
    {
        // 'type' is inherited from GlobalScope. It might need to be set somewhere else.
        return type;
    }

    /* --------------------------- SCOPE MANAGER -------------------------- */

    void ScopeManager::enterScope(std::shared_ptr<GlobalScope> scope)
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
        auto it = scopeMap.find(scopeName);
        if (it != scopeMap.end())
        {
            return it->second;
        }

        return nullptr;
    }

    void ScopeManager::addFunctionDeclaration(std::shared_ptr<Function> function)
    {
        functionDeclarations.push_back(function);
    }

    std::shared_ptr<Function> ScopeManager::getFunctionDeclarationByName(std::string functionName)
    {
        for (auto function : functionDeclarations)
        {
            if (function->getFunctionName() == functionName)
            {
                return function;
            }
        }

        return nullptr;
    }

    std::shared_ptr<Function> ScopeManager::currentFunctionDeclarationBy()
    {
        if (functionDeclarations.empty())
        {
            return nullptr;
        }

        return functionDeclarations.back();
    }

} // namespace scope

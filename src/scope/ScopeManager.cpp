#include "ScopeManager.h"
#include "../headers/Utils.h"

#include <stack>
#include <unordered_map>
#include <optional>
#include <algorithm>

namespace scope
{

    /* ----------------------------- PARENT ----------------------------- */
    // Implementation for parent is in the header via inline methods

    /* --------------------------- GLOBALSCOPE --------------------------- */
    std::string GlobalScope::getName()
    {
        return scopeName;
    }

    int GlobalScope::getType() const
    {
        return scopeType;
    }

    /* --------------------------- LOCAL SCOPE --------------------------- */
    int LocalScope::getType() const
    {
        return scopeType;
    }

    /* --------------------------- STATEMENTS ---------------------------- */

    Statements::Statements() = default;

    Statements::~Statements() = default;

    void Statements::addVariable(const std::shared_ptr<Variable> &variable)
    {
        if (!variable)
        {
            throw std::runtime_error(util::format("Statements::addVariable: Variable is null", ""));
        }

        // Check for duplicate variable names
        for (const auto &var : variables)
        {
            if (var->name == variable->name)
            {
                throw std::runtime_error(util::format("Statements::addVariable: Variable {} already exists", variable->name));
            }
        }

        variables.push_back(variable);
    }

    void Statements::addVariable(const std::string &name, int type)
    {
        if (name.empty())
        {
            throw std::runtime_error(util::format("Statements::addVariable: Variable name is empty", ""));
        }

        // Check for duplicate variable names
        for (const auto &var : variables)
        {
            if (var->name == name)
            {
                throw std::runtime_error(util::format("Statements::addVariable: Variable {} already exists", name));
            }
        }

        variables.push_back(std::make_shared<Variable>(name, type));
    }

    void Statements::addVariable(const std::string &name, int type, bool mut)
    {
        if (name.empty())
        {
            throw std::runtime_error(util::format("Statements::addVariable: Variable name is empty", ""));
        }

        // Check for duplicate variable names
        for (const auto &var : variables)
        {
            if (var->name == name)
            {
                throw std::runtime_error(util::format("Statements::addVariable: Variable {} already exists", name));
            }
        }

        variables.push_back(std::make_shared<Variable>(name, type, mut));
    }

    void Statements::addFunctionAlias(const std::string &varName, const std::shared_ptr<Function> &function)
    {
        if (!function)
        {
            throw std::runtime_error(util::format("Statements::addFunctionAlias: Function is null", ""));
        }

        const auto variable = getVariable(varName);
        if (!variable)
        {
            throw std::runtime_error(util::format("Statements::addFunctionAlias: Variable {} not found", varName));
        }

        variable->function = function;
    }

    std::shared_ptr<Variable> Statements::getVariable(const std::string &name)
    {
        // Use find_if for better readability
        const auto it = std::find_if(variables.begin(), variables.end(),
                              [&name](const auto &var) { return var->name == name; });
        
        return (it != variables.end()) ? *it : nullptr;
    }

    int Statements::getScopeType() const
    {
        return this->getType();
    }

    /* --------------------------- FUNCTION CALL -------------------------- */

    FunctionCall::FunctionCall(const std::string &name, const std::shared_ptr<Function> &function) :
        callName(name), function(function)
    {
        if (!function) {
            throw std::runtime_error(util::format("FunctionCall::constructor: Function is null", ""));
        }
    }

    FunctionCall::~FunctionCall() = default;

    std::string FunctionCall::getName()
    {
        return callName;
    }

    std::shared_ptr<Function> FunctionCall::getFunction()
    {
        return function;
    }

    /* --------------------------- SIGNATURE -------------------------- */

    Signature::Signature(const int returnType, const std::vector<std::shared_ptr<FunctionArg>> &arguments) :
        returnType(returnType), arguments(arguments)
    {
    }
    
    int Signature::getReturnType() const
    {
        return returnType;
    }
    
    int Signature::getArgumentCount() const
    {
        return static_cast<int>(arguments.size());
    }

    std::vector<std::shared_ptr<FunctionArg>> Signature::getArguments()
    {
        return arguments;
    }

    std::shared_ptr<FunctionArg> Signature::getArgumentByName(const std::string &name)
    {
        auto it = std::find_if(arguments.begin(), arguments.end(),
                              [&name](const auto &arg) { return arg->name == name; });
        
        return (it != arguments.end()) ? *it : nullptr;
    }

    /* ------------------------------ FUNCTION ---------------------------- */

    Function::Function(const std::string &name, const std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> &args,
                       const int returnType) : args(args), returnType(returnType)
    {
        if (!args) {
            throw std::runtime_error(util::format("Function::constructor: Args is null", ""));
        }
        
        this->scopeName = name;
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
        return scopeName;
    }

    int Function::getReturnType() const
    {
        return returnType;
    }

    void Function::setUpperFunction(const std::shared_ptr<Function> &function)
    {
        if (!function)
        {
            throw std::runtime_error(util::format("Function::setUpperFunction: Function is null", ""));
        }

        upperFunction = function;
    }

    void Function::enterLocalScope(const std::shared_ptr<LocalScope> &scope)
    {
        if (!scope)
        {
            throw std::runtime_error(util::format("Function::enterLocalScope: Scope is null", ""));
        }

        try {
            // Get a shared_ptr to this instance
            const std::shared_ptr<Parent> parentPtr = shared_from_this();
            scope->setParent(parentPtr);

            // Verify the cast works (should always succeed but check for safety)
            if (const auto functionPtr = std::dynamic_pointer_cast<Function>(parentPtr); !functionPtr)
            {
                throw std::runtime_error("Function::enterLocalScope: Failed to cast Parent to Function");
            }

            scopeStack.push(scope);
        }
        catch (const std::bad_weak_ptr& e) {
            throw std::runtime_error("Function::enterLocalScope: Object not managed by shared_ptr");
        }
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
            throw std::runtime_error(util::format("Function::setAlias: Alias is null", ""));
        this->alias = alias;
    }

    std::shared_ptr<Variable> Function::getAlias()
    {
        return alias;
    }

    std::shared_ptr<FunctionArg> Function::getArgByName(const std::string &argName) const
    {
        if (!args) {
            return nullptr;
        }
        
        auto it = std::find_if(args->begin(), args->end(),
                              [&argName](const auto &arg) { return arg->name == argName; });
        
        return (it != args->end()) ? *it : nullptr;
    }

    std::shared_ptr<Variable> Function::findVarCurrentScopeAndArg(const std::string &varName)
    {
        // Check current scope first
        if (const auto statement = std::dynamic_pointer_cast<Statements>(getCurrentLocalScope()))
        {
            if (auto var = statement->getVariable(varName))
            {
                return var;
            }
        }

        // Then check function arguments
        if (const auto arg = getArgByName(varName))
        {
            if (arg->signature)
            {
                // This is a function pointer argument - create a variable that points to a function
                const auto newArgs = std::make_shared<std::vector<std::shared_ptr<FunctionArg>>>();
                for (auto &functionArg : arg->signature->getArguments())
                {
                    newArgs->push_back(functionArg);
                }

                const auto function = std::make_shared<Function>(arg->name, newArgs, arg->signature->getReturnType());
                const auto variable = std::make_shared<Variable>(arg->name, arg->type);
                variable->function = function;
                return variable;
            }

            // Regular argument - create a variable with the same type
            return std::make_shared<Variable>(arg->name, arg->type);
        }

        return nullptr;
    }

    std::shared_ptr<Variable> Function::findVarAllScopesAndArg(const std::string &varName)
    {
        // 1. Search all local scopes within this function (without copying the stack)
        if (!scopeStack.empty()) {
            // Create a non-modifying copy of the stack for iteration
            std::stack tempStack(scopeStack);
            
            while (!tempStack.empty()) {
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
        }

        // 2. Check function arguments
        if (const auto arg = getArgByName(varName))
        {
            if (arg->signature)
            {
                // This is a function pointer argument - create a variable that points to a function
                const auto newArgs = std::make_shared<std::vector<std::shared_ptr<FunctionArg>>>();
                for (auto &functionArg : arg->signature->getArguments())
                {
                    newArgs->push_back(functionArg);
                }

                const auto function = std::make_shared<Function>(arg->name, newArgs, arg->signature->getReturnType());
                const auto variable = std::make_shared<Variable>(arg->name, arg->type);
                variable->function = function;
                return variable;
            }

            // Regular argument - create a variable with the same type
            return std::make_shared<Variable>(arg->name, arg->type);
        }

        // 3. If we have a parent function, search there too
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
    
    bool Function::isReturnFound()
    {
        return returnFound;
    }

    void Function::changeToReturnFound()
    {
        returnFound = true;
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
        return scopeName;
    }

    int Function::getScopeType() const
    {
        return scopeType;
    }

    /* --------------------------- SCOPE GUARD -------------------------- */
    
    ScopeGuard::ScopeGuard(std::shared_ptr<Function> function, const std::shared_ptr<LocalScope> &scope)
        : function(std::move(function))
    {
        if (this->function) {
            this->function->enterLocalScope(scope);
        }
    }
    
    ScopeGuard::~ScopeGuard()
    {
        if (function) {
            function->exitLocalScope();
        }
    }

    /* Create ScopeGuard from Function */
    ScopeGuard Function::createScopeGuard(const std::shared_ptr<LocalScope> &scope)
    {
        try {
            // Get a shared_ptr to this function
            const auto self = std::dynamic_pointer_cast<Function>(shared_from_this());
            if (!self) {
                throw std::runtime_error("Function::createScopeGuard: Failed to cast to Function");
            }
            return ScopeGuard(self, scope);
        }
        catch (const std::bad_weak_ptr& e) {
            throw std::runtime_error("Function::createScopeGuard: Object not managed by shared_ptr");
        }
    }

    /* --------------------------- SCOPE MANAGER -------------------------- */

    void ScopeManager::enterScope(const std::shared_ptr<GlobalScope> &scope)
    {
        if (!scope)
        {
            throw std::runtime_error(util::format("ScopeManager::enterScope: Scope is null", ""));
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
        const auto it = scopeMap.find(scopeName);
        return (it != scopeMap.end()) ? it->second : nullptr;
    }
    
    std::vector<std::shared_ptr<Function>> ScopeManager::getFunctionDeclarations()
    {
        return functionDeclarations;
    }
    
    void ScopeManager::setExternDeclaration(const std::shared_ptr<Function> &declaration)
    {
        if (!declaration) {
            throw std::runtime_error(util::format("ScopeManager::setExternDeclaration: Declaration is null", ""));
        }
        
        externDeclarations[declaration->getFunctionName()] = declaration;
    }

    void ScopeManager::addFunctionDeclaration(const std::shared_ptr<Function> &function)
    {
        if (!function) {
            throw std::runtime_error(util::format("ScopeManager::addFunctionDeclaration: Function is null", ""));
        }
        
        functionDeclarations.push_back(function);
    }

    void ScopeManager::addStructDeclaration(const std::shared_ptr<StructStemt> &struct_)
    {
        if (!struct_) {
            throw std::runtime_error(util::format("ScopeManager::addStructDeclaration: Struct is null", ""));
        }
        
        structDeclarations.push_back(struct_);
    }

    std::shared_ptr<Function> ScopeManager::getFunctionDeclarationByName(const std::string &functionName)
    {
        // 1. First, look in variables and local/parent scopes
        if (currentScope())
        {
            // Assume current scope is a function (or belongs to one)
            if (const auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope()))
            {
                // findVarAllScopesAndArg searches current scope and parent scopes
                if (const auto variable = currentFunction->findVarAllScopesAndArg(functionName);
                    variable && variable->type == tokenMap::FUNCTION)
                {
                    return variable->function;
                }
            }
        }

        // 2. If not found in local variables or scopes,
        //    search in global function declarations
        auto it = std::find_if(functionDeclarations.begin(), functionDeclarations.end(),
                             [&functionName](const auto &func) { return func->getFunctionName() == functionName; });
        
        if (it != functionDeclarations.end()) {
            return *it;
        }

        // 3. Finally, check for an external declaration with that name
        if (const auto externIt = externDeclarations.find(functionName); externIt != externDeclarations.end()) {
            return externIt->second;
        }

        // Not found in any case
        return nullptr;
    }

    std::shared_ptr<StructStemt> ScopeManager::getStructDeclarationByName(const std::string &name) const
    {
        const auto it = std::find_if(structDeclarations.begin(), structDeclarations.end(),
                             [&name](const auto &stru) { return stru->name == name; });
        
        return (it != structDeclarations.end()) ? *it : nullptr;
    }

    std::shared_ptr<Function> ScopeManager::currentFunctionDeclaration()
    {
        if (functionDeclarations.empty())
        {
            return nullptr;
        }

        return functionDeclarations.back();
    }

    /* --------------------------- STRUCT STATEMENT -------------------------- */

    StructStemt::StructStemt(const std::string &name) : name(name)
    {
        if (name.empty()) {
            throw std::runtime_error("StructStemt::constructor: Name cannot be empty");
        }
    }

    void StructStemt::setVariables(const std::vector<std::shared_ptr<Variable>> &variables)
    {
        // Check for duplicate variable names
        std::unordered_map<std::string, bool> nameMap;
        for (const auto &var : variables) {
            if (!var) {
                throw std::runtime_error("StructStemt::setVariables: Variable cannot be null");
            }
            
            if (nameMap.find(var->name) != nameMap.end()) {
                throw std::runtime_error(util::format("StructStemt::setVariables: Duplicate variable name: {}", var->name));
            }
            
            nameMap[var->name] = true;
        }
        
        this->variables = variables;
    }

    std::shared_ptr<Variable> StructStemt::getVarByName(const std::string &varName) const
    {
        const auto it = std::find_if(variables.begin(), variables.end(),
                             [&varName](const auto &var) { return var->name == varName; });
        
        return (it != variables.end()) ? *it : nullptr;
    }
    
    std::vector<std::shared_ptr<Variable>> StructStemt::getVariables()
    {
        return variables;
    }

} // namespace scope

#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <stack>
#include <unordered_map>
#include <vector>
#include <optional>
#include "../headers/TokenMap.h"

/**
 * @namespace scope
 * @brief Contains classes for managing scope and symbol resolution in the Iron language.
 */
namespace scope
{
    // Forward declarations
    class Function;
    class FunctionArg;
    class StructStemt;
    class ScopeGuard;

    /**
     * @class Parent
     * @brief Base class for all scope-related classes that can participate in hierarchical relationships.
     *
     * Provides capabilities for managing parent-child relationships in the scope hierarchy.
     * Uses std::enable_shared_from_this to safely create shared_ptr instances from 'this'.
     */
    class Parent : public std::enable_shared_from_this<Parent>
    {
    protected:
        /** @brief Weak reference to parent to avoid circular dependencies */
        std::weak_ptr<Parent> parent;

    public:
        /** @brief Virtual destructor to ensure proper cleanup in derived classes */
        virtual ~Parent() = default;

        /**
         * @brief Sets the parent of this scope element
         * @param newParent The new parent to set
         */
        virtual void setParent(std::shared_ptr<Parent> newParent) = 0;

        /**
         * @brief Gets the parent of this scope element
         * @return shared_ptr to the parent, or nullptr if no parent exists
         */
        std::shared_ptr<Parent> getParent() const
        {
            return parent.lock();
        }
    };

    /**
     * @class GlobalScope
     * @brief Represents a global scope in the program (e.g., module level)
     *
     * Global scopes are the top-level containers for declarations like functions and structs.
     */
    class GlobalScope : public Parent
    {
    protected:
        /** @brief Name of this scope */
        std::string scopeName;
        
        /** @brief Type identifier for this scope */
        int scopeType;

    public:
        /**
         * @brief Gets the name of this scope
         * @return The scope name
         */
        std::string getName();
        
        /**
         * @brief Gets the type of this scope
         * @return The scope type as an integer code
         */
        int getType() const;

        /** @brief Default constructor */
        GlobalScope() = default;
        
        /** @brief Virtual destructor */
        ~GlobalScope() override = default;

        /**
         * @brief Sets the parent of this global scope
         * @param newParent The new parent to set
         */
        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @struct Variable
     * @brief Represents a variable declaration with type and mutability information
     */
    struct Variable
    {
        /** @brief Name of the variable */
        std::string name;
        
        /** @brief Type of the variable (as a token code) */
        int type;
        
        /** @brief Whether the variable is mutable */
        bool mut{false};
        
        /** @brief Function reference (for function variables) */
        std::shared_ptr<Function> function;
        
        /** @brief Struct reference (for struct variables) */
        std::shared_ptr<StructStemt> structStemt;

        /**
         * @brief Constructs a variable with name and type
         * @param name The variable name
         * @param type The variable type code
         */
        Variable(const std::string &name, const int type) 
            : name(name), type(type)
        {
        }

        /**
         * @brief Constructs a variable with name, type and mutability
         * @param name The variable name
         * @param type The variable type code
         * @param mut Whether the variable is mutable
         */
        Variable(const std::string &name, const int type, const bool mut) 
            : name(name), type(type), mut(mut)
        {
        }
    };

    /**
     * @class LocalScope
     * @brief Represents a local scope (e.g., block scope within functions)
     */
    class LocalScope : public Parent
    {
    protected:
        /** @brief Type identifier for this scope */
        int scopeType{};

    public:
        /**
         * @brief Gets the type of this scope
         * @return The scope type as an integer code
         */
        int getType() const;

        /** @brief Default constructor */
        LocalScope() = default;
        
        /** @brief Virtual destructor */
        ~LocalScope() override = default;

        /** @brief Reference to the containing scope */
        std::shared_ptr<LocalScope> upperScope;

        /**
         * @brief Sets the parent of this local scope
         * @param newParent The new parent to set
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class Statements
     * @brief Represents a scope that contains variable declarations
     */
    class Statements final : public LocalScope
    {
    protected:
        /** @brief Collection of variables declared in this scope */
        std::vector<std::shared_ptr<Variable>> variables;

    public:
        /**
         * @brief Adds a new variable to this scope
         * @param name The variable name
         * @param type The variable type code
         * @throws std::runtime_error if variable name is empty or already exists
         */
        void addVariable(const std::string &name, int type);
        
        /**
         * @brief Adds a new variable to this scope with mutability
         * @param name The variable name
         * @param type The variable type code
         * @param mut Whether the variable is mutable
         * @throws std::runtime_error if variable name is empty or already exists
         */
        void addVariable(const std::string &name, int type, bool mut);
        
        /**
         * @brief Associates a function with a variable (creates function alias)
         * @param varName The variable name
         * @param function The function to associate
         * @throws std::runtime_error if variable not found or function is null
         */
        void addFunctionAlias(const std::string &varName, const std::shared_ptr<Function> &function);
        
        /**
         * @brief Finds a variable by name in this scope
         * @param name The variable name to find
         * @return shared_ptr to the variable, or nullptr if not found
         */
        std::shared_ptr<Variable> getVariable(const std::string &name);

        /** @brief Default constructor */
        Statements();
        
        /** @brief Destructor */
        ~Statements() override;
        
        /**
         * @brief Adds an existing variable to this scope
         * @param variable The variable to add
         * @throws std::runtime_error if variable is null
         */
        void addVariable(const std::shared_ptr<scope::Variable> &variable);

        /** @brief Reference to the containing scope of statements type */
        std::shared_ptr<Statements> upperScope;

        /**
         * @brief Gets the type of this scope
         * @return The scope type as an integer code
         */
        int getScopeType() const;
    };

    /**
     * @struct CallArg
     * @brief Represents an argument in a function call
     */
    struct CallArg
    {
        /** @brief Name of the argument */
        std::string name;
        
        /** @brief Type of the argument */
        int type;

        /**
         * @brief Constructs a call argument
         * @param name The argument name
         * @param type The argument type code
         */
        CallArg(std::string name, const int type) 
            : name(std::move(name)), type(type)
        {
        }
    };

    /**
     * @class FunctionCall
     * @brief Represents a function call scope
     */
    class FunctionCall final : public LocalScope
    {
    protected:
        /** @brief Name of the function being called */
        std::string callName;
        
        /** @brief Reference to the function being called */
        std::shared_ptr<Function> function;

    public:
        /**
         * @brief Gets the function being called
         * @return shared_ptr to the function
         */
        std::shared_ptr<Function> getFunction();

        /**
         * @brief Constructs a function call scope
         * @param name Name of the function being called
         * @param function Reference to the function
         */
        FunctionCall(const std::string &name, const std::shared_ptr<Function> &function);
        
        /** @brief Destructor */
        ~FunctionCall() override;

        /**
         * @brief Gets the name of the function being called
         * @return The function name
         */
        std::string getName();
    };

    /**
     * @class Signature
     * @brief Represents a function signature (return type and arguments)
     */
    class Signature
    {
    protected:
        /** @brief Return type of the function */
        int returnType;
        
        /** @brief Arguments of the function */
        std::vector<std::shared_ptr<FunctionArg>> arguments;

    public:
        /**
         * @brief Constructs a function signature
         * @param returnType The return type code
         * @param arguments The function arguments
         */
        Signature(int returnType, const std::vector<std::shared_ptr<FunctionArg>> &arguments);
        
        /**
         * @brief Gets the return type
         * @return The return type code
         */
        int getReturnType() const;
        
        /**
         * @brief Gets the number of arguments
         * @return The argument count
         */
        int getArgumentCount() const;
        
        /**
         * @brief Gets all arguments
         * @return Vector of argument references
         */
        std::vector<std::shared_ptr<FunctionArg>> getArguments();
        
        /**
         * @brief Finds an argument by name
         * @param name The argument name to find
         * @return shared_ptr to the argument, or nullptr if not found
         */
        std::shared_ptr<FunctionArg> getArgumentByName(const std::string &name);
    };

    /**
     * @struct FunctionArg
     * @brief Represents a function argument/parameter
     */
    struct FunctionArg
    {
        /** @brief Type of the argument */
        int type;
        
        /** @brief Name of the argument */
        std::string name;
        
        /** @brief Function signature (for function pointer arguments) */
        std::shared_ptr<Signature> signature;

        /**
         * @brief Constructs a function argument
         * @param name The argument name
         * @param type The argument type code
         */
        FunctionArg(std::string name, const int type) 
            : type(type), name(std::move(name))
        {
        }

        /**
         * @brief Constructs a function pointer argument
         * @param name The argument name
         * @param type The argument type code
         * @param signature The function signature
         */
        FunctionArg(std::string name, const int type, const std::shared_ptr<Signature> &signature)
            : type(type), name(std::move(name)), signature(signature)
        {
        }
    };


    /**
     * @class Function
     * @brief Represents a function declaration with scope management
     */
    class Function final : public GlobalScope
    {
    private:
        /** @brief Whether a return token has been found in the function */
        bool returnTokenFound = false;
        
        /** @brief Stack of local scopes in this function */
        std::stack<std::shared_ptr<LocalScope>> scopeStack;
        
        /** @brief Map of scopes by name for quick lookup */
        std::unordered_map<std::string, std::shared_ptr<LocalScope>> scopeMap;
        
        /** @brief Whether this is an external function */
        bool external;
        
        /** @brief Whether this function takes variable arguments */
        bool variedArguments;

    protected:
        /** @brief Variable alias for this function (when stored in a variable) */
        std::shared_ptr<Variable> alias;
        
        /** @brief Parent function (for nested functions) */
        std::shared_ptr<Function> upperFunction;
        
        /** @brief Arguments of this function */
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> args;
        
        /** @brief Structs defined in this function */
        std::vector<std::shared_ptr<StructStemt>> structs;
        
        /** @brief Return type of this function */
        int returnType;
        
        /** @brief Whether a return statement has been found */
        bool returnFound{false};

    public:
        /**
         * @brief Constructs a function
         * @param name The function name
         * @param args The function arguments
         * @param returnType The return type code
         */
        Function(const std::string &name, const std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> &args,
                 int returnType);
        
        /** @brief Destructor */
        ~Function() override;
        
        /**
         * @brief Gets the function name
         * @return The function name
         */
        std::string getFunctionName();
        
        /**
         * @brief Gets the return type
         * @return The return type code
         */
        int getReturnType() const;
        
        /**
         * @brief Sets the parent function
         * @param function The parent function
         * @throws std::runtime_error if function is null
         */
        void setUpperFunction(const std::shared_ptr<Function> &function);
        
        /**
         * @brief Enters a new local scope
         * @param scope The scope to enter
         * @throws std::runtime_error if scope is null or if casting fails
         */
        void enterLocalScope(const std::shared_ptr<LocalScope> &scope);
        
        /**
         * @brief Gets the current local scope
         * @return shared_ptr to the current scope, or nullptr if no scope
         */
        std::shared_ptr<LocalScope> getCurrentLocalScope();
        
        /**
         * @brief Checks if a return token has been found
         * @return true if a return token has been found
         */
        bool isReturnTokenFound() const;
        
        /**
         * @brief Marks that a return token has been found
         */
        void updateReturnTokenStatusToFound();
        
        /**
         * @brief Exits the current local scope
         */
        void exitLocalScope();
        
        /**
         * @brief Sets the variable alias for this function
         * @param alias The variable to use as alias
         * @throws std::runtime_error if alias is null
         */
        void setAlias(const std::shared_ptr<Variable> &alias);
        
        /**
         * @brief Gets the variable alias for this function
         * @return shared_ptr to the alias variable
         */
        std::shared_ptr<Variable> getAlias();

        /**
         * @brief Finds an argument by name
         * @param argName The argument name to find
         * @return shared_ptr to the argument, or nullptr if not found
         */
        std::shared_ptr<FunctionArg> getArgByName(const std::string &argName) const;
        
        /**
         * @brief Finds a variable in the current scope or arguments
         * @param varName The variable name to find
         * @return shared_ptr to the variable, or nullptr if not found
         */
        std::shared_ptr<Variable> findVarCurrentScopeAndArg(const std::string &varName);
        
        /**
         * @brief Finds a variable in all scopes including parent functions
         * @param varName The variable name to find
         * @return shared_ptr to the variable, or nullptr if not found
         */
        std::shared_ptr<Variable> findVarAllScopesAndArg(const std::string &varName);
        
        /**
         * @brief Gets all arguments of this function
         * @return shared_ptr to the vector of arguments
         */
        std::shared_ptr<std::vector<std::shared_ptr<FunctionArg>>> getArgs();
        
        /**
         * @brief Gets the parent function
         * @return shared_ptr to the parent function
         */
        std::shared_ptr<Function> getUpperFunction();

        /**
         * @brief Checks if a return statement has been found
         * @return true if a return has been found
         */
        bool isReturnFound();
        
        /**
         * @brief Marks that a return statement has been found
         */
        void changeToReturnFound();
        
        /**
         * @brief Checks if this is an external function
         * @return true if this is an external function
         */
        bool isExternal() const;
        
        /**
         * @brief Marks this as an external function
         */
        void changeToExternal();
        
        /**
         * @brief Checks if this function takes variable arguments
         * @return true if this function takes variable arguments
         */
        bool isVariedArguments() const;
        
        /**
         * @brief Marks this function as taking variable arguments
         */
        void changeToVariedArguments();

        /**
         * @brief Gets the scope name (same as function name)
         * @return The scope name
         */
        std::string getScopeName();
        
        /**
         * @brief Gets the scope type
         * @return The scope type code
         */
        int getScopeType() const;
        
        /**
         * @brief Creates a RAII scope guard for safe scope management
         * @param scope The scope to enter
         * @return A ScopeGuard object that will exit the scope when destroyed
         */
        [[nodiscard]] ScopeGuard createScopeGuard(const std::shared_ptr<LocalScope> &scope);
    };

    /**
     * @class ScopeGuard
     * @brief RAII helper for safe scope management
     *
     * When constructed, enters a scope; when destroyed, exits the scope.
     * This ensures proper scope cleanup even when exceptions occur.
     */
    class ScopeGuard
    {
    private:
        /** @brief The function whose scope is being managed */
        std::shared_ptr<Function> function;

    public:
        /**
         * @brief Constructs a ScopeGuard and enters the scope
         * @param function The function to manage scope for
         * @param scope The scope to enter
         */
        ScopeGuard(std::shared_ptr<Function> function, const std::shared_ptr<LocalScope> &scope);
        
        /**
         * @brief Destructor - automatically exits the scope
         */
        ~ScopeGuard();
        
        // Prevent copying
        ScopeGuard(const ScopeGuard&) = delete;
        ScopeGuard& operator=(const ScopeGuard&) = delete;
    };

    /**
     * @class ScopeManager
     * @brief Manages global scopes, functions, and structs
     *
     * Central manager for all scope-related information in a program.
     */
    class ScopeManager
    {
    private:
        /** @brief All struct declarations in the program */
        std::vector<std::shared_ptr<StructStemt>> structDeclarations;
        
        /** @brief All function declarations in the program */
        std::vector<std::shared_ptr<Function>> functionDeclarations;
        
        /** @brief External function declarations mapped by name */
        std::unordered_map<std::string, std::shared_ptr<Function>> externDeclarations;
        
        /** @brief Stack of global scopes for tracking current scope */
        std::stack<std::shared_ptr<GlobalScope>> scopeStack;
        
        /** @brief Map of global scopes by name for quick lookup */
        std::unordered_map<std::string, std::shared_ptr<GlobalScope>> scopeMap;

    public:
        /**
         * @brief Adds a function declaration
         * @param function The function to add
         */
        void addFunctionDeclaration(const std::shared_ptr<Function> &function);
        
        /**
         * @brief Adds a struct declaration
         * @param struct_ The struct to add
         */
        void addStructDeclaration(const std::shared_ptr<StructStemt> &struct_);

        /**
         * @brief Finds a function by name, checking local scopes first
         * @param functionName The function name to find
         * @return shared_ptr to the function, or nullptr if not found
         */
        std::shared_ptr<Function> getFunctionDeclarationByName(const std::string &functionName);
        
        /**
         * @brief Finds a struct by name
         * @param name The struct name to find
         * @return shared_ptr to the struct, or nullptr if not found
         */
        std::shared_ptr<StructStemt> getStructDeclarationByName(const std::string &name) const;
        
        /**
         * @brief Gets the current function declaration
         * @return shared_ptr to the current function, or nullptr if none
         */
        std::shared_ptr<Function> currentFunctionDeclaration();
        
        /**
         * @brief Enters a new global scope
         * @param scope The scope to enter
         * @throws std::runtime_error if scope is null
         */
        void enterScope(const std::shared_ptr<GlobalScope> &scope);
        
        /**
         * @brief Exits the current global scope
         */
        void exitScope();
        
        /**
         * @brief Gets the name of the current scope
         * @return The current scope name, or empty string if no scope
         */
        std::string currentScopeName() const;
        
        /**
         * @brief Gets the current global scope
         * @return shared_ptr to the current scope, or nullptr if no scope
         */
        std::shared_ptr<GlobalScope> currentScope() const;
        
        /**
         * @brief Finds a global scope by name
         * @param scopeName The scope name to find
         * @return shared_ptr to the scope, or nullptr if not found
         */
        std::shared_ptr<GlobalScope> getScopeByName(const std::string &scopeName) const;
        
        /**
         * @brief Gets all function declarations
         * @return Vector of function declarations
         */
        std::vector<std::shared_ptr<Function>> getFunctionDeclarations();

        /**
         * @brief Adds an external function declaration
         * @param declaration The function to add
         */
        void setExternDeclaration(const std::shared_ptr<Function> &declaration);
    };

    /**
     * @class StructStemt
     * @brief Represents a struct declaration with variables
     */
    class StructStemt
    {
    private:
        /** @brief Variables defined in this struct */
        std::vector<std::shared_ptr<Variable>> variables;
        
    public:
        /** @brief Name of the struct */
        std::string name;
        
        /**
         * @brief Constructs a struct with a name
         * @param name The struct name
         */
        explicit StructStemt(const std::string &name);
        
        /**
         * @brief Sets the variables for this struct
         * @param variables The variables to set
         */
        void setVariables(const std::vector<std::shared_ptr<Variable>> &variables);

        /**
         * @brief Finds a variable by name in this struct
         * @param varName The variable name to find
         * @return shared_ptr to the variable, or nullptr if not found
         */
        std::shared_ptr<Variable> getVarByName(const std::string &varName) const;
        
        /**
         * @brief Gets all variables in this struct
         * @return Vector of variables
         */
        std::vector<std::shared_ptr<Variable>> getVariables();
    };

} // namespace scope

#endif // SCOPE_MANAGER_H

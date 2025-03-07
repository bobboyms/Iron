/**
 * @file Hlir.h
 * @brief High-Level Intermediate Representation (HLIR) for the Iron language compiler.
 * @author Thiago Rodrigues
 * @date 2025
 *
 * This file contains the comprehensive class hierarchy that forms the High-Level
 * Intermediate Representation (HLIR) used by the Iron language compiler. The HLIR
 * serves as a bridge between the AST (produced by parsing) and LLVM IR generation.
 */

#ifndef HLIR_H
#define HLIR_H

#include <memory>
#include "Exceptions.h"
#include "TokenMap.h"
#include "Utils.h"

#include <map>

/**
 * @namespace hlir
 * @brief Contains classes and structures representing the High-Level Intermediate Representation (HLIR).
 *
 * The HLIR namespace provides a comprehensive set of classes that represent various components
 * of the Iron programming language in an intermediate form between the AST and LLVM IR.
 * This includes representations for functions, variables, types, expressions, operations,
 * control flow structures, and other language constructs.
 *
 * The HLIR serves as a bridge between semantic analysis and code generation,
 * providing a structured and type-safe representation of program elements
 * that can be more easily translated to LLVM IR.
 */
namespace hlir
{
    /**
     * @class Function
     * @brief ‘Forward’ declaration da classe Function para evitar erros de compilação.
     */

    class Basic;

    class Parent;

    class Function;

    class Statement;

    class Block;

    class Conditional;

    class Jump;

    struct Arg;

    class Struct;

    class StructInit;


    /**
     * @class Basic
     * @brief Abstract base class enforcing a getText() method for all HLIR elements.
     *
     * Basic serves as the fundamental base class for all HLIR elements that need
     * a textual representation. It enforces a common interface through the pure virtual
     * getText() method, which all derived classes must implement. It also provides a
     * shared stringstream object for efficient string building.
     */
    class Basic
    {

    public:
        /** @brief String stream buffer used for text representation construction */
        std::stringstream sb;

        /**
         * @brief Virtual destructor for proper cleanup of derived classes.
         *
         * Since Basic is an abstract base class with derived classes,
         * a virtual destructor ensures proper cleanup when a derived object
         * is deleted through a pointer to the base class.
         */
        virtual ~Basic() = default;

        /**
         * @brief Produces a text representation of the derived object.
         *
         * This pure virtual method must be implemented by all derived classes.
         * It's used to generate a standardized textual representation of any
         * HLIR element, which is useful for debugging and serialization.
         *
         * @return A string containing the text representation of the object.
         */
        virtual std::string getText() = 0;

    protected:
        /**
         * @brief Protected constructor initializes the string stream.
         *
         * The constructor is protected to prevent direct instantiation of Basic,
         * and ensures the stringstream is properly initialized for all derived classes.
         */
        Basic() : sb(std::stringstream())
        {
        }
    };

    /**
     * @class Parent
     * @brief Base class for HLIR elements that can have a parent-child relationship.
     *
     * Parent provides the foundation for establishing hierarchical relationships between HLIR elements.
     * It inherits from std::enable_shared_from_this to allow objects to obtain a shared_ptr to themselves,
     * which is crucial for safe self-referencing in hierarchical structures.
     *
     * The class uses weak_ptr to store the parent reference to avoid circular reference issues
     * which could lead to memory leaks.
     */
    class Parent : public std::enable_shared_from_this<Parent>
    {
    protected:
        /** @brief Weak reference to the parent element to avoid circular references */
        std::weak_ptr<Parent> parent;

    public:
        /**
         * @brief Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~Parent() = default;

        /**
         * @brief Sets the parent of this HLIR element.
         *
         * This pure virtual method must be implemented by all derived classes
         * to establish the parent-child relationship.
         *
         * @param newParent A shared pointer to the parent element
         */
        virtual void setParent(std::shared_ptr<Parent> newParent) = 0;

        /**
         * @brief Gets the parent of this HLIR element.
         *
         * This method safely converts the internal weak_ptr to a shared_ptr,
         * returning nullptr if the parent no longer exists.
         *
         * @return A shared pointer to the parent element, or nullptr if the parent no longer exists
         */
        std::shared_ptr<Parent> getParent() const
        {
            return parent.lock(); // Returns a shared_ptr if the parent still exists
        }
    };

    /**
     * @class Expression
     * @brief ‘Interface’ (classe base) para todas as expressões.
     */
    class Expression : public Basic, public Parent
    {
    public:
        ~Expression() override = default;
    };

    /**
     * @class Type
     * @brief Represents a specific data type (int, float, etc.) in the HLIR.
     *
     * The Type class encapsulates information about data types in the Iron language.
     * Each type is represented by an integer code (corresponding to constants in tokenMap),
     * such as TYPE_INT, TYPE_FLOAT, TYPE_STRING, etc. This class provides methods for
     * accessing and converting types to their textual representation.
     *
     * This class is marked as 'final' to prevent further inheritance, as it represents
     * concrete types that should not be extended.
     */
    class Type final : public Basic, public Parent
    {
    private:
        /**
         * @brief Integer-based type identifier from tokenMap (e.g., TYPE_INT, TYPE_FLOAT)
         */
        int type{};
        std::string typeName;

    protected:
    public:
        /**
         * @brief Retrieves the integer-based type identifier.
         *
         * This method returns the numeric code that identifies this type,
         * corresponding to constants defined in the tokenMap namespace.
         *
         * @return An integer representing this type code
         */
        int getType() const;

        /**
         * @brief Returns the textual form of this type.
         *
         * Converts the numeric type identifier to its string representation,
         * such as "int", "float", "string", etc. This method is mainly used
         * for debugging and code generation purposes.
         *
         * @return A string containing the text representation of the type
         */
        std::string getText() override;

        /**
         * @brief Constructs a Type using an integer type code.
         *
         * @param type The integer code from tokenMap (e.g., TYPE_INT, TYPE_FLOAT)
         */
        explicit Type(int type);

        /**
         * @brief Constructs a Type object with an integer code and its textual name.
         *
         * This constructor initializes a Type instance by setting both its integer type code and its textual
         * representation. It is useful when you want to immediately assign a name to the type, aiding in debugging and
         * code generation.
         *
         * @param type The integer code representing the type (e.g., TYPE_INT, TYPE_FLOAT) as defined in tokenMap.
         * @param typeName The textual representation of the type (e.g., "int", "float", "string", etc.).
         */
        explicit Type(int type, const std::string &typeName);

        /**
         * @brief Default constructor creates an uninitialized type.
         *
         * The type must be explicitly set before use.
         */
        Type();

        /**
         * @brief Sets or changes the type identifier.
         *
         * @param type The new integer type code from tokenMap
         */
        void set(int type);

        /**
         * @brief Retrieves the textual name of the type.
         *
         * This method returns the string that represents the textual name of the type stored in the instance.
         * If the type name has not been explicitly set, it may return an empty string or a default value.
         *
         * @return A string containing the textual name of the type.
         */
        std::string getTypeName();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        ~Type() override;

        /**
         * @brief Sets the parent of this Type.
         *
         * Implementation of the pure virtual method from the Parent class.
         * Establishes the parent-child relationship for this Type instance.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class Signature
     * @brief Represents the signature of a function.
     *
     * The Signature class encapsulates information about a function's interface,
     * including its return type and argument types. This is used for function
     * declarations, function pointers, and function type checking.
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class Signature final : public Basic, public Parent
    {
    private:
        /** @brief The return type of the function */
        std::shared_ptr<Type> returnType;

        /** @brief List of arguments (parameters) for the function */
        std::vector<std::shared_ptr<Arg>> args;

    public:
        /**
         * @brief Adds a new argument to the function signature.
         *
         * This method appends a new argument to the list of arguments
         * in this function signature.
         *
         * @param arg A shared pointer to an Arg instance representing the argument
         */
        void addArg(const std::shared_ptr<Arg> &arg);

        /**
         * @brief Generates a textual representation of the signature.
         *
         * Creates a string that represents this function signature,
         * including return type and argument types.
         *
         * @return A string containing the text representation
         */
        std::string getText() override;

        /**
         * @brief Finds an argument by name.
         *
         * Static method to search for an argument with the specified name.
         *
         * @param argName The name of the argument to find
         * @return A shared pointer to the found Arg, or nullptr if not found
         */
        static std::shared_ptr<Arg> findArgByName(const std::string &argName);

        /**
         * @brief Gets all arguments of this signature.
         *
         * @return A vector of shared pointers to all arguments
         */
        std::vector<std::shared_ptr<Arg>> getArgs();

        /**
         * @brief Gets the return type of this signature.
         *
         * @return A shared pointer to the Type representing the return type
         */
        std::shared_ptr<Type> getReturnType();

        /**
         * @brief Constructs a Signature with a specified return type.
         *
         * @param returnType A shared pointer to the Type representing the return type
         */
        explicit Signature(const std::shared_ptr<Type> &returnType);

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        ~Signature() override;

        /**
         * @brief Sets the parent of this Signature.
         *
         * Implementation of the pure virtual method from the Parent class.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @struct Arg
     * @brief Represents a single function argument with a name, type, and optional signature.
     *
     * The Arg structure encapsulates information about a single function parameter,
     * including its name, data type, and optional function signature (for function pointer arguments).
     *
     * This structure is marked 'final' to prevent further inheritance.
     */
    struct Arg final : Parent
    {
        /**
         * @brief The argument's name as it appears in the function declaration.
         */
        std::string name;

        /**
         * @brief Shared pointer to the Type of this argument.
         *
         * Represents the data type of this argument, such as int, float, etc.
         */
        std::shared_ptr<Type> type;

        /**
         * @brief Optional function signature for function pointer arguments.
         *
         * When this argument represents a function pointer, this field
         * contains the signature of the target function.
         */
        std::shared_ptr<Signature> signature;

        /**
         * @brief Sets the parent of this Arg.
         *
         * Implementation of the pure virtual method from the Parent class.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

        /**
         * @brief Configures the Arg with a name and type.
         *
         * This method sets up the argument with the given name and type,
         * and establishes the parent-child relationship.
         *
         * @param newName The name of the argument
         * @param newType A shared pointer to the Type of the argument
         * @return A shared pointer to this Arg for method chaining
         * @throws HLIRException If the cast to Arg fails
         */
        std::shared_ptr<Arg> set(const std::string &newName, const std::shared_ptr<Type> &newType)
        {
            name = newName;
            type = newType;
            const std::shared_ptr<Parent> parentPtr = shared_from_this();
            newType->setParent(parentPtr);

            auto assignPtr = std::dynamic_pointer_cast<Arg>(parentPtr);
            if (!assignPtr)
            {
                throw HLIRException("Failed to cast Parent");
            }

            return assignPtr;
        }

        /**
         * @brief Configures the Arg with a name, type, and function signature.
         *
         * This expanded version of set() is used for function pointer arguments,
         * where a signature is required in addition to the name and type.
         *
         * @param name The name of the argument
         * @param type A shared pointer to the Type of the argument
         * @param signature A shared pointer to the Signature of the function pointer
         * @return A shared pointer to this Arg for method chaining
         * @throws HLIRException If the cast to Arg fails
         */
        std::shared_ptr<Arg> set(const std::string &name, const std::shared_ptr<Type> &type,
                                 const std::shared_ptr<Signature> &signature)
        {
            this->name = name;
            this->type = type;
            this->signature = signature;

            const std::shared_ptr<Parent> parentPtr = shared_from_this();
            this->type->setParent(parentPtr);

            auto assignPtr = std::dynamic_pointer_cast<Arg>(parentPtr);
            if (!assignPtr)
            {
                throw HLIRException("Failed to cast Parent");
            }

            return assignPtr;
        }
    };

    /**
     * @class FunctionArgs
     * @brief Represents a complete list of function parameters.
     *
     * The FunctionArgs class encapsulates a list of function parameters (Arg objects),
     * providing methods to add, find, and access these parameters. It represents
     * the complete parameter list of a function and is used in function declarations,
     * definitions, and calls.
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class FunctionArgs final : public Basic, public Parent
    {
    private:
        /**
         * @brief A vector of shared pointers to Arg objects representing the function parameters.
         *
         * This collection maintains the ordered list of all parameters for a function.
         */
        std::vector<std::shared_ptr<Arg>> args;

    public:
        /**
         * @brief Adds a new argument to the function parameter list.
         *
         * This method appends a new parameter to the list of function arguments.
         *
         * @param arg A shared pointer to an Arg object representing the parameter
         */
        void addArg(const std::shared_ptr<Arg> &arg);

        /**
         * @brief Produces a textual representation of all arguments.
         *
         * Generates a comma-separated list of all function parameters in the format
         * "arg1:type1,arg2:type2,...". This representation is used for debugging
         * and code generation.
         *
         * @return A string containing the comma-separated list of arguments
         */
        std::string getText() override;

        /**
         * @brief Finds an argument by name in this function's parameter list.
         *
         * Searches through the list of parameters to find one with the specified name.
         *
         * @param argName The name of the argument to find
         * @return A shared pointer to the Arg if found, nullptr otherwise
         */
        std::shared_ptr<Arg> findArgByName(const std::string &argName) const;

        /**
         * @brief Gets all arguments in this function parameter list.
         *
         * @return A vector of shared pointers to all Arg objects
         */
        std::vector<std::shared_ptr<Arg>> getArgs();

        /**
         * @brief Default constructor creates an empty parameter list.
         */
        FunctionArgs();

        /**
         * @brief Constructor that initializes the parameter list from a function signature.
         *
         * @param signature A shared pointer to a Signature to copy arguments from
         */
        explicit FunctionArgs(const std::shared_ptr<Signature> &signature);

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        ~FunctionArgs() override;

        /**
         * @brief Sets the parent of this FunctionArgs.
         *
         * Implementation of the pure virtual method from the Parent class.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class Variable
     * @brief Represents a variable with name, type, and additional attributes.
     *
     * The Variable class represents variables in the Iron language, including
     * their name, type, and various properties. Variables can be simple data variables,
     * function arguments, or function pointers (with signatures).
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class Variable final : public Expression
    {
        /**
         * @brief The variable's source name as written in the code.
         */
        std::string varName;

        /**
         * @brief The variable's real (potentially transformed) name used in code generation.
         *
         * This might differ from varName due to mangling, scope changes, or other transformations.
         */
        std::string realName;

        /**
         * @brief A shared pointer to the variable's data type.
         */
        std::shared_ptr<Type> varType;

        /**
         * @brief Optional function signature for function pointer variables.
         *
         * When this variable represents a function pointer, this field
         * contains the signature of the target function.
         */
        std::shared_ptr<Signature> signature;

        /**
         * @brief Flag indicating if this variable belongs to another scope.
         *
         * When true, this variable is referring to a variable defined in a parent scope.
         */
        bool anotherScope = false;

        /**
         * @brief Flag indicating if this variable was created from a function argument.
         *
         * When true, this variable represents a function parameter.
         */
        bool fromFunctionArg{false};

    public:
        /**
         * @brief Sets the function signature for this variable.
         *
         * Used when this variable represents a function pointer to specify
         * the signature of the target function.
         *
         * @param signature A shared pointer to the Signature
         */
        void setSignature(const std::shared_ptr<Signature> &signature);

        /**
         * @brief Gets the function signature for this variable.
         *
         * @return A shared pointer to the Signature, or nullptr if not a function pointer
         */
        std::shared_ptr<Signature> getSignature();

        /**
         * @brief Retrieves the variable's source name.
         *
         * @return A string containing the source name of the variable
         */
        std::string getVarName();

        /**
         * @brief Produces a textual representation of the variable.
         *
         * Generates a string representation in the format "let varName:typeName".
         * This representation is used for debugging and code generation.
         *
         * @return A string containing the text representation
         */
        std::string getText() override;

        /**
         * @brief Gets the real (potentially transformed) name of the variable.
         *
         * This name might differ from the source name due to mangling,
         * scope changes, or other transformations during compilation.
         *
         * @return A string containing the real name
         */
        std::string getRealName();

        /**
         * @brief Changes the real name of the variable.
         *
         * @param realName The new real name
         */
        void changeRealName(const std::string &realName);

        /**
         * @brief Gets the variable's data type.
         *
         * @return A shared pointer to the Type
         */
        std::shared_ptr<Type> getVarType();

        /**
         * @brief Configures the variable with a name and type.
         *
         * This method initializes or updates the variable with the given name and type.
         *
         * @param varName The name of the variable
         * @param varType A shared pointer to the Type
         * @return A shared pointer to this Variable for method chaining
         */
        std::shared_ptr<Variable> set(const std::string &varName, const std::shared_ptr<Type> &varType);

        /**
         * @brief Marks this variable as belonging to another scope.
         *
         * When this method is called, the variable is flagged as referencing
         * a variable defined in a parent scope.
         */
        void changeToAnotherScope();

        /**
         * @brief Checks if this variable belongs to another scope.
         *
         * @return true if this variable refers to one in a parent scope, false otherwise
         */
        bool isAnotherScope() const;

        /**
         * @brief Checks if this variable was created from a function argument.
         *
         * @return true if this variable represents a function parameter, false otherwise
         */
        bool isFromFunctionArg() const;

        /**
         * @brief Marks this variable as having been created from a function argument.
         */
        void changeToFromFunctionArg();

        /**
         * @brief Default constructor creates an uninitialized variable.
         */
        Variable();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        ~Variable() override;

        /**
         * @brief Sets the parent of this Variable.
         *
         * Implementation of the pure virtual method from the Parent class.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @typedef Data
     * @brief A variant type that can hold different kinds of values used in the HLIR.
     *
     * This variant can store any of the following types:
     * - std::shared_ptr<Function>: A reference to a function
     * - std::shared_ptr<Variable>: A reference to a variable
     * - std::string: A string literal
     *
     * This allows for flexible representation of different value types within
     * the HLIR without using inheritance or type erasure.
     */
    using Data = std::variant<std::shared_ptr<Function>, std::shared_ptr<Struct>, std::shared_ptr<StructInit>,
                              std::shared_ptr<Variable>,
                              std::string>; //, int, float, double, bool

    /**
     * @class Value
     * @brief Wraps a typed value of any supported data type.
     *
     * The Value class encapsulates a value of any supported type (represented by the Data variant)
     * along with its corresponding Type. This allows for type-safe value representation throughout
     * the HLIR, regardless of the actual data type (function pointer, variable reference, string, etc.).
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class Value final : public Basic, public Parent
    {
    public:
        /**
         * @brief Configures a Value object with a data value and its type.
         *
         * This method initializes or updates the Value with the given data and type information.
         *
         * @param value The Data variant to store (function pointer, variable reference, etc.)
         * @param valueType A shared pointer to a Type describing the data
         * @return A shared pointer to this Value for method chaining
         */
        std::shared_ptr<Value> set(const Data &value, const std::shared_ptr<Type> &valueType);

        /**
         * @brief Default constructor creates an uninitialized Value.
         */
        Value();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        ~Value() override;

        /**
         * @brief Retrieves the underlying data value.
         *
         * @return The stored Data variant
         */
        Data getValue();

        /**
         * @brief Produces a textual representation of the stored value.
         *
         * Generates a string representation of the underlying data,
         * appropriate to its type. For example, string values might be
         * quoted, while numbers are represented as digits.
         *
         * @return A string containing the text representation
         */
        std::string getText() override;

        /**
         * @brief Gets the type information for this value.
         *
         * @return A shared pointer to the Type of this value
         */
        std::shared_ptr<Type> getValueType();

        /**
         * @brief Sets the parent of this Value.
         *
         * Implementation of the pure virtual method from the Parent class.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

    private:
        /**
         * @brief The Data variant holding the actual value.
         *
         * This field stores the actual data value, which can be a Function pointer,
         * Variable reference, or string literal, depending on the context.
         */
        Data value;

        /**
         * @brief The type information for the stored data.
         *
         * This field holds the type descriptor for the value, defining what
         * data type the value represents (int, string, function pointer, etc.).
         */
        std::shared_ptr<Type> valueType;
    };

    /**
     * @class Assign
     * @brief Represents a variable assignment operation.
     *
     * The Assign class represents an assignment operation in the Iron language,
     * where a value is assigned to a variable. This is one of the fundamental
     * operations in the language, used for variable initialization and updates.
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class Assign final : public Basic, public Parent
    {
    protected:
        /**
         * @brief The target variable that is being assigned to.
         *
         * This is the left-hand side of the assignment operation.
         */
        std::shared_ptr<Variable> variable;

        /**
         * @brief The value that is being assigned.
         *
         * This is the right-hand side of the assignment operation,
         * containing the actual data being assigned to the variable.
         */
        std::shared_ptr<Value> value;

    public:
        /**
         * @brief Configures an assignment operation between a variable and a value.
         *
         * This method sets up or updates the assignment with the target variable and value.
         *
         * @param variable A shared pointer to the Variable being assigned to
         * @param value A shared pointer to the Value being assigned
         * @return A shared pointer to this Assign for method chaining
         */
        std::shared_ptr<Assign> set(const std::shared_ptr<Variable> &variable, const std::shared_ptr<Value> &value);

        /**
         * @brief Default constructor creates an uninitialized assignment.
         */
        Assign();

        /**
         * @brief Virtual destructor for proper cleanup.
         */
        ~Assign() override;

        /**
         * @brief Produces a textual representation of the assignment.
         *
         * Generates a string representation in the format "let varName:varType = value".
         * This representation is used for debugging and code generation.
         *
         * @return A string containing the text representation
         */
        std::string getText() override;

        /**
         * @brief Gets the variable being assigned to.
         *
         * @return A shared pointer to the target Variable
         */
        std::shared_ptr<Variable> getVariable();

        /**
         * @brief Gets the value being assigned.
         *
         * @return A shared pointer to the Value
         */
        std::shared_ptr<Value> getValue();

        /**
         * @brief Sets the parent of this Assign.
         *
         * Implementation of the pure virtual method from the Parent class.
         *
         * @param newParent A shared pointer to the new parent
         */
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @struct FunctionCallArg
     * @brief Represents a single argument in a function call.
     *
     * This structure encapsulates a single argument passed to a function during a call,
     * including the argument name, its type, and the specific value being passed.
     * It is used in function calls to track exactly what values are being passed.
     */
    struct FunctionCallArg final : Parent
    {
        /**
         * @brief The argument's name, e.g., "radius".
         */
        std::string argument;

        /**
         * @brief The Type of this argument.
         */
        std::shared_ptr<Type> argumentType;

        /**
         * @brief The Value for this argument.
         */
        std::shared_ptr<Value> value;

        /**
         * @brief Constructs a FunctionCallArg with an argument name, a Type, and a Value.
         * @param newArgument
         * @param type A shared pointer to a Type.
         * @param newValue A shared pointer to a Value.
         */
        std::shared_ptr<FunctionCallArg> set(const std::string &newArgument, const std::shared_ptr<Type> &type,
                                             const std::shared_ptr<Value> &newValue)
        {
            argument = newArgument;
            value = newValue;

            std::shared_ptr<Parent> parentPtr = shared_from_this();
            value->setParent(parentPtr);

            // Realiza o cast para std::shared_ptr<Assign>
            auto assignPtr = std::dynamic_pointer_cast<FunctionCallArg>(parentPtr);
            if (!assignPtr)
            {
                throw HLIRException("Failed to cast Parent.");
            }

            return assignPtr;
        }
        FunctionCallArg(std::string argument, std::shared_ptr<Type> type, std::shared_ptr<Value> value) :
            argument(std::move(argument)), argumentType(std::move(type)), value(std::move(value))
        {
        }

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class FunctionCallArgs
     * @brief Represents a list of FunctionCallArg items for a function call.
     *
     * Inherits from Basic to provide a textual representation of the call arguments.
     */
    class FunctionCallArgs final : public Basic, public Parent
    {
    private:
        /**
         * @brief A vector of shared pointers to FunctionCallArg.
         */
        std::vector<std::shared_ptr<FunctionCallArg>> callArgs;

    public:
        /**
         * @brief Generates a string listing each argument in the form "argName:value".
         * @return A comma-separated list of arguments, e.g. "x:42,flag:true".
         */
        std::string getText() override;

        /**
         * @brief Constructs a FunctionCallArgs with an existing list of arguments.
         * @param callArgs The vector of pointers to FunctionCallArg.
         */
        explicit FunctionCallArgs(const std::vector<std::shared_ptr<FunctionCallArg>> &callArgs);

        /**
         * @brief Default constructor (empty list).
         */
        FunctionCallArgs();

        /**
         * @brief Adds a FunctionCallArg to the internal list.
         * @param callArg The FunctionCallArg to add.
         */
        void addCallArg(const std::shared_ptr<FunctionCallArg> &callArg);

        std::vector<std::shared_ptr<FunctionCallArg>> getCallArgs();

        /**
         * @brief Destructor for FunctionCallArgs.
         */
        ~FunctionCallArgs() override;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class FunctionCall
     * @brief Represents a function call in the HLIR.
     *
     * The FunctionCall class inherits from Basic and implements the getText() method to provide
     * a textual representation of the function call.
     */
    class FunctionCall final : public Expression
    {
    private:
        std::shared_ptr<Function> function; ///< Shared pointer to the function being called.
        std::shared_ptr<FunctionCallArgs> callArgs; ///< Shared pointer to the arguments of the function call.
        std::string functionCallName;

    public:
        /**
         * @brief Constructs a FunctionCall with the specified function and arguments.
         * @param function Shared pointer to the function to be called.
         * @param callArgs Shared pointer to the arguments of the function call.
         *
         * @throws HLIRException If `function` or `callArgs` is nullptr.
         */
        std::shared_ptr<FunctionCall> set(const std::string &functionCallName,
                                          const std::shared_ptr<Function> &function,
                                          const std::shared_ptr<FunctionCallArgs> &callArgs);

        std::shared_ptr<Function> getFunction();

        FunctionCall();

        /**
         * @brief Destructor for FunctionCall.
         */
        ~FunctionCall() override;

        std::string getFunctionCallName() const;

        /**
         * @brief Generates a textual representation of the function call.
         * @return A string representing the function call, e.g., "call foo(arg1, arg2)".
         *
         * @throws HLIRException If `function` is nullptr.
         */
        std::string getText() override;

        std::shared_ptr<FunctionCallArgs> getCallArgs();

        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    class BinaryOperation : public Expression
    {
    protected:
        std::shared_ptr<Variable> varLeft;
        std::shared_ptr<Variable> varRight;

    public:
        BinaryOperation();
        ~BinaryOperation() override;
        std::shared_ptr<BinaryOperation> set(const std::shared_ptr<Variable> &varLeft,
                                             const std::shared_ptr<Variable> &varRight);

        std::string getText() override = 0;

        std::shared_ptr<Variable> getVarLeft();
        std::shared_ptr<Variable> getVarRight();

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    class CMP final : public BinaryOperation
    {
    protected:
        std::shared_ptr<Type> opType;

    public:
        explicit CMP(int op);

        /**
         * @brief Destructor for Plus.
         */
        ~CMP() override;

        std::shared_ptr<Type> getOpType();

        /**
         * @brief Generates a textual representation of the addition operation.
         * @return A string representing the addition, e.g., "PLUS a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    class AND final : public BinaryOperation
    {

    public:
        AND();

        /**
         * @brief Destructor for Plus.
         */
        ~AND() override;

        /**
         * @brief Generates a textual representation of the addition operation.
         * @return A string representing the addition, e.g., "PLUS a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    class OR final : public BinaryOperation
    {

    public:
        OR();

        /**
         * @brief Destructor for Plus.
         */
        ~OR() override;

        /**
         * @brief Generates a textual representation of the addition operation.
         * @return A string representing the addition, e.g., "PLUS a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    class _NOT final : public BinaryOperation
    {

    public:
        _NOT();

        /**
         * @brief Destructor for Plus.
         */
        ~_NOT() override;

        /**
         * @brief Generates a textual representation of the addition operation.
         * @return A string representing the addition, e.g., "PLUS a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    /**
     * @class Plus
     * @brief Represents an addition operation between two variables in the HLIR.
     *
     * The Plus class inherits from Basic and implements the getText() method to provide
     * a textual representation of the addition operation.
     */
    class Plus final : public BinaryOperation
    {

    public:
        Plus();

        /**
         * @brief Destructor for Plus.
         */
        ~Plus() override;

        /**
         * @brief Generates a textual representation of the addition operation.
         * @return A string representing the addition, e.g., "PLUS a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    /**
     * @class Minus
     * @brief Represents a subtraction operation between two variables in the HLIR.
     *
     * The Minus class inherits from Basic and implements the getText() method to provide
     * a textual representation of the subtraction operation.
     */
    class Minus final : public BinaryOperation
    {
    public:
        Minus();

        /**
         * @brief Destructor for Minus.
         */
        ~Minus() override;

        /**
         * @brief Generates a textual representation of the subtraction operation.
         * @return A string representing the subtraction, e.g., "MINUS a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    /**
     * @class Mult
     * @brief Represents a multiplication operation between two variables in the HLIR.
     *
     * The Mult class inherits from Basic and implements the getText() method to provide
     * a textual representation of the multiplication operation.
     */
    class Mult final : public BinaryOperation
    {

    public:
        Mult();

        /**
         * @brief Destructor for Mult.
         */
        ~Mult() override;

        /**
         * @brief Generates a textual representation of the multiplication operation.
         * @return A string representing the multiplication, e.g., "MULT a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    /**
     * @class Div
     * @brief Represents a division operation between two variables in the HLIR.
     *
     * The Div class inherits from Basic and implements the getText() method to provide
     * a textual representation of the division operation.
     */
    class Div final : public BinaryOperation
    {

    public:
        Div();

        /**
         * @brief Destructor for Div.
         */
        ~Div() override;

        /**
         * @brief Generates a textual representation of the division operation.
         * @return A string representing the division, e.g., "DIV a, b".
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        std::string getText() override;
    };

    /**
     * @class Cast
     * @brief Represents a type casting operation for a variable in the HLIR.
     *
     * The Cast class inherits from Basic and implements the getText() method to provide
     * a textual representation of the casting operation.
     */
    class Cast final : public Expression
    {
    private:
        std::shared_ptr<Variable> variable;
        std::shared_ptr<Type> type;

    public:
        /**
         * @brief Constructs a Cast operation for a specific variable and target type.
         * @param variable Shared pointer to the variable to be cast.
         * @param type Shared pointer to the target type for casting.
         *
         * @throws HLIRException If `variable` or `type` is nullptr.
         */
        std::shared_ptr<Cast> apply(const std::shared_ptr<Variable> &variable, const std::shared_ptr<Type> &type);

        Cast();

        /**
         * @brief Destructor for Cast.
         */
        ~Cast() override;

        /**
         * @brief Generates a textual representation of the casting operation.
         * @return A string representing the casting, e.g., "cast a:int to float".
         *
         * @throws HLIRException If `variable` or `type` is nullptr.
         */
        std::string getText() override;

        std::shared_ptr<Variable> getVariable();
        std::shared_ptr<Type> getType();

        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class FunctionPtr
     * @brief Represents a pointer to a function within the HLIR.
     *
     * The FunctionPtr class inherits from Basic and implements the getText() method to provide
     * a textual representation of the function pointer.
     */
    class FunctionPtr final : public Basic, public Parent
    {
    private:
        std::shared_ptr<Function> function; ///< Shared pointer to the referenced function.

    public:
        /**
         * @brief Constructs a FunctionPtr pointing to a specific function.
         * @param function Shared pointer to the function.
         *
         * @throws HLIRException If `function` is nullptr.
         */
        std::shared_ptr<FunctionPtr> set(const std::shared_ptr<Function> &function);
        FunctionPtr();

        /**
         * @brief Destructor for FunctionPtr.
         */
        ~FunctionPtr() override;

        /**
         * @brief Generates a textual representation of the function pointer.
         * @return A string representing the function pointer, e.g., "fptr foo".
         *
         * @throws HLIRException If `function` is nullptr.
         */
        std::string getText() override;

        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @typedef ValidExpr
     * @brief Alias for a variant type that can hold any valid expression.
     *
     * The ValidExpr type can hold any of the following shared pointers to classes derived from Basic:
     * - Div
     * - Mult
     * - Minus
     * - Plus
     * - FunctionCall
     * - Variable
     * - Cast
     * - FunctionPtr
     */

    /**
     * @class Expr
     * @brief Represents a generic expression in the HLIR.
     *
     * The Expr class inherits from Basic and encapsulates a valid expression (ValidExpr) associated with a variable.
     */
    class Expr final : public Basic, public Parent
    {
    private:
        std::shared_ptr<Expression> validExpr; ///< The encapsulated valid expression.
        std::shared_ptr<Variable> variable; ///< Shared pointer to the variable associated with the expression.

    public:
        /**
         * @brief Constructs a generic expression with a variable and a valid expression.
         * @param variable Shared pointer to the associated variable.
         * @param validExpr The valid expression encapsulated.
         *
         * @throws HLIRException If `variable` is nullptr or if `validExpr` is invalid.
         */
        std::shared_ptr<Expr> set(const std::shared_ptr<Variable> &variable,
                                  const std::shared_ptr<Expression> &validExpr);

        Expr();

        /**
         * @brief Destructor for Expr.
         */
        ~Expr() override;

        /**
         * @brief Generates a textual representation of the generic expression.
         * @return A string representing the expression, e.g., "let a:int = PLUS a, b".
         *
         * @throws HLIRException If `variable` is nullptr or if `validExpr` is invalid.
         */
        std::string getText() override;

        std::shared_ptr<Variable> getVariable();

        std::shared_ptr<Expression> getExpr();

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class FuncReturn
     * @brief Represents a function return statement in the HLIR.
     *
     * The FuncReturn class encapsulates a return statement within a function,
     * associating a function with the variable being returned. This class
     * is used to represent return statements and verify type compatibility
     * between the function's declared return type and the actual returned value.
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class FuncReturn final : public Basic
    {
    private:
        std::shared_ptr<Function> function;
        std::shared_ptr<Variable> variable;

    public:
        FuncReturn(const std::shared_ptr<Function> &function, const std::shared_ptr<Variable> &variable);
        ~FuncReturn() override;
        std::shared_ptr<Variable> getVariable();
        std::string getText() override;
    };

    /**
     * @typedef ValidStatement
     * @brief A variant that can hold any type of valid statement in a code block.
     *
     * This variant type can hold any kind of statement that can appear in a block of code,
     * allowing for flexible representation of different statement types without complex
     * inheritance hierarchies. It includes assignments, expressions, function calls,
     * returns, blocks, jumps, and conditionals.
     *
     * Used primarily by the Statement class to store collections of heterogeneous statements.
     */
    using ValidStatement = std::variant<std::shared_ptr<Assign>, std::shared_ptr<Expr>, std::shared_ptr<FunctionCall>,
                                        std::shared_ptr<FuncReturn>, std::shared_ptr<Block>, std::shared_ptr<Jump>,
                                        std::shared_ptr<Conditional>>;

    /**
     * @brief Helper function to check if a ValidStatement contains a null pointer.
     *
     * This utility function uses std::visit to check if the shared_ptr contained
     * in any ValidStatement variant alternative is null. This is useful for
     * validating statements before use and preventing null pointer dereferences.
     *
     * @param statement The ValidStatement to check
     * @return true if the contained shared_ptr is null, false otherwise
     */
    inline bool isValidStatementNull(const ValidStatement &statement)
    {
        return std::visit([](const auto &ptr) { return ptr == nullptr; }, statement);
    }


    /**
     * @class Statement
     * @brief Represents a block of code statements in the HLIR.
     *
     * The Statement class represents a code block containing multiple statements.
     * It manages a list of statements and provides methods to add, access, and manipulate them.
     * Statements can also track variables declared within their scope.
     *
     * This class serves as a container for executable statements in a function body
     * or block, and is a fundamental component for representing code structure in the HLIR.
     */
    class Statement final : public Basic, public Parent
    {
    private:
        int varId = 0;
        std::vector<ValidStatement> statementList;
        std::map<std::string, std::shared_ptr<Variable>> variableMap;

    protected:
    public:
        std::shared_ptr<Statement> rootStatement;
        bool logged = false;
        std::shared_ptr<Statement> set(ValidStatement statementList);
        Statement();
        ~Statement() override;
        void addStatement(ValidStatement statement);
        std::vector<ValidStatement> getStatements();
        std::string getText() override;
        std::string getNewVarName();
        void addDeclaredVariable(const std::shared_ptr<Variable> &variable);
        std::shared_ptr<Variable> findVarByName(const std::string &varName);
        std::shared_ptr<Value> getValueFromVariable(std::string varName);
        void insertStatementsAt(const std::vector<ValidStatement> &stmts, size_t pos);
        bool haveReturn() const;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };


    /**
     * @class Jump
     * @brief Represents an unconditional jump to a labeled block.
     *
     * The Jump class represents a control flow operation that unconditionally
     * transfers execution to a target block. This is used for implementing
     * control structures like loops, breaks, continues, and gotos in the HLIR.
     *
     * Jumps can be enabled or disabled, allowing for conditional compilation or optimization.
     */
    class Jump final : public Basic
    {
    public:
        explicit Jump(const std::shared_ptr<Block> &block);
        ~Jump() override;
        std::shared_ptr<Block> getBlock();
        std::string getText() override;
        void disable();

    private:
        bool disabled{false};
        std::shared_ptr<Block> block;
    };

    /**
     * @class Block
     * @brief Represents a labeled block of code in the HLIR.
     *
     * The Block class represents a labeled section of code that can be the target of jumps
     * and branches. Blocks are fundamental components in the control flow graph of a function,
     * providing targets for conditional and unconditional jumps.
     *
     * Blocks can be marked as "end blocks" to indicate they represent the end of a control flow construct.
     * This is used in optimization and code generation to identify termination points.
     */
    class Block final : public Basic, public Parent
    {
    public:
        Block();
        ~Block() override;

        // Configura o bloco com um label e uma instrução. Lança exceção se o label for vazio ou se a instrução for
        // nula.
        std::shared_ptr<Block> set(const std::string &label);
        std::string getLabel();
        // Retorna a representação textual do bloco.
        std::string getText() override;
        void changeToEndBlock();
        bool isEndBlock() const;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

    private:
        bool endBlock = false;
        std::string label;
        std::shared_ptr<Statement> statement;
        std::stringstream sb; // Buffer para montagem da string de saída.
    };


    /**
     * @class Conditional
     * @brief Represents a conditional branch in the control flow.
     *
     * The Conditional class represents a decision point in the code where execution
     * branches based on a boolean condition. It is used to implement if-else statements
     * and is a fundamental component of control flow structures in the HLIR.
     *
     * Each conditional has a condition variable, a true branch target label, and
     * a false branch target label, defining where execution should continue based
     * on the evaluation of the condition.
     */
    class Conditional final : public Basic, public Parent
    {
    public:
        Conditional();
        ~Conditional() override;

        // Configura a variável de condição. Lança exceção se for nula ou não for booleana.
        std::shared_ptr<Conditional> set(const std::shared_ptr<Variable> &variable);

        std::string getTrueLabel();
        std::string getFalseLabel();

        // Define os labels dos ramos verdadeiro e falso. Lança exceção se o label estiver vazio.
        void setTrueLabel(const std::string &label);
        void setFalseLabel(const std::string &label);

        // Retorna a representação textual da condição.
        std::string getText() override;
        std::shared_ptr<Variable> getVariable();

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

    private:
        std::shared_ptr<Variable> variable;
        std::string trueLabel;
        std::string falseLabel;
        std::stringstream sb; // Buffer para montagem da string de saída.
    };

    class Function;

    /**
     * @class ScopeGuard
     * @brief RAII helper for safe scope management in functions.
     *
     * The ScopeGuard class implements the Resource Acquisition Is Initialization (RAII)
     * pattern for scope management in functions. When created, it automatically enters a scope,
     * and when destroyed (e.g., when going out of scope), it automatically exits the scope.
     *
     * This ensures proper scope cleanup even in the presence of exceptions, providing
     * exception-safe scope management that's more robust than manual enterLocalScope/exitLocalScope calls.
     *
     * Copy and assignment are disabled to prevent scope mismanagement.
     */
    class ScopeGuard
    {
    private:
        /** @brief The function whose scope is being managed */
        std::shared_ptr<Function> function;

    public:
        /**
         * @brief Constructs a ScopeGuard and enters the specified scope.
         *
         * @param func The function whose scope is being managed
         * @param statement The statement (scope) to enter
         */
        explicit ScopeGuard(std::shared_ptr<Function> func, const std::shared_ptr<Statement> &statement);

        /**
         * @brief Destructor that automatically exits the scope.
         */
        ~ScopeGuard();

        // Prevent copying and assignment
        ScopeGuard(const ScopeGuard &) = delete;
        ScopeGuard &operator=(const ScopeGuard &) = delete;
    };

    /**
     * @class Function
     * @brief Represents a complete function definition in the HLIR.
     *
     * The Function class is one of the most complex and important classes in the HLIR,
     * representing a complete function with its name, arguments, return type, and body.
     * It manages function scope, variables, statements, and control flow within the function.
     *
     * Functions can be regular functions, external functions (declarations only),
     * inline functions, or functions with varied arguments. They can also contain
     * nested functions with proper scope management.
     *
     * This class forms the foundation of the executable code structure in the HLIR,
     * serving as the primary unit of compilation and execution.
     */
    class Function final : public Basic, public Parent
    {
    public:
        // Construtor e destrutor
        Function();
        ~Function() override;

        // Getters
        std::string getFunctionName();
        std::shared_ptr<Type> getFunctionReturnType();
        std::shared_ptr<FunctionArgs> getFunctionArgs();
        std::shared_ptr<Function> getParentFunction();

        // Setter para o parentFunction
        void setParentFunction(const std::shared_ptr<Function> &function);

        // Escopo local
        // std::shared_ptr<Statement> getCurrentStatement();
        std::shared_ptr<Statement> getCurrentLocalScope();
        std::shared_ptr<Statement> getRootScope();
        void enterLocalScope(const std::shared_ptr<Statement> &statement);
        void exitLocalScope();

        // Método seguro para gerenciamento de escopo via RAII
        [[nodiscard]] ScopeGuard createScopeGuard(const std::shared_ptr<Statement> &statement);

        // Busca de variável
        std::shared_ptr<Variable> findVarAllScopesAndArg(const std::string &varName, uint scopeNumbers = 0);
        std::shared_ptr<Variable> findVarCurrentScopeAndArg(const std::string &varName);
        std::shared_ptr<Variable> getArgByName(const std::string &argName) const;
        std::vector<std::shared_ptr<Block>> getAllBlocks();

        // Definição da função (nome, argumentos e retorno)
        std::shared_ptr<Function> set(const std::string &functionName,
                                      const std::shared_ptr<FunctionArgs> &functionArgs,
                                      const std::shared_ptr<Type> &functionReturnType);

        // Configura a função com um statement (corpo)
        // void setStatement(std::shared_ptr<Statement> statement);

        // std::vector<std::shared_ptr<Statement>> getStatementList();

        // Métodos de configuração e consulta de flags
        void enableInline();
        bool isExternal() const;
        int getLanguageType() const;
        void setLanguageType(int type);
        void changeToExternal();
        void changeToVariedArguments();
        bool isVariedArguments() const;
        bool getInline() const;

        // Produz uma representação textual da função
        std::string getText() override;

        // Cria um clone da função
        std::shared_ptr<Function> clone() const;

        // Implementação de setParent herdado de Parent
        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

        std::string generateLabel(const std::string &label);
        std::string generateVarName();

        bool isArgFunction();
        void changeToArgFunction();

    private:
        // Dados da função
        uint labelId{0};
        uint varId{0};
        std::string functionName;
        std::shared_ptr<Type> functionReturnType;
        bool external;
        bool variedArguments;
        bool argFunction{false};

    protected:
        // Corpo e escopo da função
        std::stack<size_t> localScopePositions;
        std::shared_ptr<Statement> rootStatement;
        std::stack<std::shared_ptr<Statement>> statementStack;
        std::unordered_map<std::string, std::shared_ptr<Statement>> statementMap;
        std::shared_ptr<Function> parentFunction;
        int languageType;
        std::shared_ptr<FunctionArgs> functionArgs;
        bool inlineFunction = false;

        // Buffer para montagem de strings
        mutable std::stringstream sb;
    };

    /**
     * @class Context
     * @brief Main container for all functions in an HLIR program.
     *
     * The Context class serves as the top-level container for an entire Iron program
     * in the HLIR. It maintains a collection of all functions (both regular and external)
     * defined in the program and provides methods to add, find, and access these functions.
     *
     * This class represents the global scope and overall structure of the program,
     * functioning as the root node of the HLIR representation.
     *
     * This class is marked 'final' to prevent further inheritance.
     */
    class Context final : public Basic
    {
    private:
    protected:
        std::vector<std::shared_ptr<Struct>> structs_;
        std::vector<std::shared_ptr<Function>> functions;

    public:
        Context();
        /**
         * @brief Destroys the Context instance.
         */
        ~Context() override;
        void addFunction(const std::shared_ptr<Function> &function);
        void addStruct(const std::shared_ptr<Struct> &struct_);

        std::shared_ptr<Function> getFunctionByName(const std::string &funcName) const;
        std::shared_ptr<Struct> getStructByName(const std::string &structName) const;

        /**
         * @brief Produces a textual representation: "fn functionName(args):returnType".
         * @return A string with the function definition.
         */
        std::string getText() override;

        std::vector<std::shared_ptr<Function>> getFunctions();
        std::vector<std::shared_ptr<Struct>> getStructs();
        void addExternalFunction(const std::shared_ptr<Function> &function);
    };

    /**
     * @class Utilities
     * @brief Utility class for helper functions.
     *
     * The Utilities class provides static methods for common tasks, such as generating
     * textual representations from a signature. These helper functions facilitate data
     * conversion and standardization in the HLIR.
     */
    class Utilities
    {
    public:
        /**
         * @brief Generates text from a signature.
         *
         * This static method converts a Signature instance into a formatted textual
         * representation, making it easier to display and debug.
         *
         * @param signature Shared pointer to the signature to be converted.
         * @return A string containing the textual representation of the signature.
         */
        static std::string generateTextFromSignature(const std::shared_ptr<Signature> &signature);
    };

    /**
     * @class Struct
     * @brief Represents a data structure in the HLIR.
     *
     * The Struct class encapsulates the concept of a structure, containing its name
     * and associated variables. It provides methods to obtain the textual representation,
     * search for variables by name, and access its components.
     */
    class Struct final : public Basic
    {
    private:
        std::string name; ///< The name of the structure.
        std::vector<std::shared_ptr<Variable>> variables; ///< List of variables contained in the structure.
    public:
        /**
         * @brief Constructs a new Struct instance.
         *
         * @param name The name of the structure.
         * @param variables A vector of variables that belong to the structure.
         */
        Struct(const std::string &name, const std::vector<std::shared_ptr<Variable>> &variables);

        /**
         * @brief Produces a textual representation of the structure.
         *
         * Returns a string that describes the structure, typically including the name
         * and the list of declared variables.
         *
         * @return A string containing the description of the structure.
         */
        std::string getText() override;

        /**
         * @brief Retrieves the name of the structure.
         *
         * @return A string with the name of the structure.
         */
        std::string getName();

        /**
         * @brief Gets all variables of the structure.
         *
         * @return A vector containing shared pointers to the structure's variables.
         */
        std::vector<std::shared_ptr<Variable>> getVariables();

        /**
         * @brief Searches for a variable by name in the structure.
         *
         * Searches and returns a variable with the specified name, if it exists.
         *
         * @param varName The name of the variable to search for.
         * @return Shared pointer to the found variable or nullptr if not found.
         */
        std::pair<int, std::shared_ptr<Variable>> findVarByName(const std::string &varName);
    };

    /**
     * @class StructInit
     * @brief Represents the initialization of a structure in the HLIR.
     *
     * The StructInit class encapsulates the initialization process for a structure.
     * It holds a reference to the structure being initialized and a collection of
     * assignment operations that set up the structure's variables.
     *
     * This class is used during the HLIR generation phase to represent the initialization
     * of structure instances with specific values.
     */
    class StructInit final : public Basic
    {
    private:
        /// Shared pointer to the structure being initialized.
        std::shared_ptr<Struct> struct_;

        /// List of assignment operations used to initialize the structure's fields.
        std::vector<std::shared_ptr<Assign>> assigns;

    public:
        /**
         * @brief Constructs a new StructInit instance.
         *
         * Initializes the StructInit with the provided structure.
         *
         * @param struct_ Shared pointer to the structure to be initialized.
         */
        explicit StructInit(const std::shared_ptr<Struct> &struct_);

        /**
         * @brief Adds an assignment operation to the initialization.
         *
         * Appends an assignment (Assign) to the list of assignments that configure
         * the structure's fields.
         *
         * @param assign Shared pointer to the assignment to add.
         */
        void addAssign(const std::shared_ptr<Assign> &assign);

        /**
         * @brief Retrieves the structure being initialized.
         *
         * @return Shared pointer to the structure associated with this initialization.
         */
        std::shared_ptr<Struct> getStruct();

        /**
         * @brief Gets the list of assignment operations.
         *
         * @return A vector containing shared pointers to all assignments used in this initialization.
         */
        std::vector<std::shared_ptr<Assign>> getAssigns();

        /**
         * @brief Produces a textual representation of the structure.
         *
         * Returns a string that describes the structure, typically including the name
         * and the list of declared variables.
         *
         * @return A string containing the description of the structure.
         */
        std::string getText() override;
    };


} // namespace hlir
#endif

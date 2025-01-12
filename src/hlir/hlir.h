#ifndef HLIR_H
#define HLIR_H

#include "WriterCodeHLIR.h"
#include "Exceptions.h"
#include "TokenMap.h"
#include "Utils.h"
#include "WriterCodeHLIR.h"
#include <memory>
#include <stack>

/**
 * @namespace hlir
 * @brief Contains classes and structures representing a High-Level IR.
 */
namespace hlir
{

    /**
     * @class Context
     * @brief Holds contextual resources like a shared stringstream.
     */
    class Context
    {
    private:
        /**
         * @brief A shared pointer to a stringstream for context usage.
         */
        std::shared_ptr<std::stringstream> localSb;

    public:
        /**
         * @brief Constructs a Context instance.
         */
        Context(/* args */);

        /**
         * @brief Destroys the Context instance.
         */
        ~Context();
    };

    /**
     * @class Basic
     * @brief Abstract base class enforcing a getText() method.
     */
    class Basic
    {

    public:
        std::stringstream sb;
        /**
         * @brief Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~Basic() = default;

        /**
         * @brief Produces a text representation of the derived object.
         * @return A string with the representation.
         */
        virtual std::string getText() = 0;

    protected:
        // Construct it in the base constructor to ensure it's never null
        Basic() : sb(std::stringstream())
        {
        }
    };

    /**
     * @class Type
     * @brief Represents a specific data type (int, float, etc.) in the IR.
     *
     * Inherits from Basic to provide a textual form of the type.
     */
    class Type : public Basic
    {
    private:
        /**
         * @brief Integer-based type identifier, e.g., TYPE_INT, TYPE_FLOAT.
         */
        int type;

    public:
        /**
         * @brief Retrieves the integer-based type identifier.
         * @return An int representing this type code.
         */
        int getType();

        /**
         * @brief Returns the textual form of this type, e.g., "int".
         * @return The text representing the type.
         */
        std::string getText() override;

        /**
         * @brief Constructs a Type using an integer type code.
         * @param type The integer code (e.g., TYPE_INT).
         */
        Type(int type);

        /**
         * @brief Destructor for Type.
         */
        ~Type();
    };

    /**
     * @struct Arg
     * @brief Represents a single argument with a name and an associated Type.
     */
    struct Arg
    {
        /**
         * @brief The argument's name.
         */
        std::string name;

        /**
         * @brief Shared pointer to a Type for this argument.
         */
        std::shared_ptr<Type> type;

        /**
         * @brief Constructs an Arg with a given name and Type pointer.
         * @param name The argument's name.
         * @param t A shared pointer to the argument's Type.
         */
        Arg(const std::string &name, std::shared_ptr<Type> t)
            : name(name), type(std::move(t)) {}
    };

    /**
     * @class FunctionArgs
     * @brief Represents a list of Arg objects (function parameters).
     *
     * Inherits from Basic to provide a combined textual representation.
     */
    class FunctionArgs : public Basic
    {
    private:
        /**
         * @brief A vector of shared pointers to Arg objects.
         */
        std::vector<std::shared_ptr<Arg>> args;

    public:
        /**
         * @brief Adds a new Arg to the internal list.
         * @param arg A shared pointer to an Arg.
         */
        void
        addArg(std::shared_ptr<Arg> arg);

        /**
         * @brief Produces a textual representation of all arguments, e.g., "x:int,y:int".
         * @return The comma-separated list of arguments.
         */
        std::string getText() override;

        /**
         * @brief Default constructor creating an empty FunctionArgs.
         */
        FunctionArgs();

        /**
         * @brief Constructs FunctionArgs from a provided list of Args.
         * @param args The vector of shared pointers to Arg.
         */
        FunctionArgs(std::vector<std::shared_ptr<Arg>> args);

        /**
         * @brief Destructor for FunctionArgs.
         */
        ~FunctionArgs();
    };

    /**
     * @class Function
     * @brief Represents a function, including its name, parameters, and return type.
     *
     * Inherits from Basic to provide a text output like "fn name(args):returnType".
     */
    class Function : public Basic
    {
    private:
        /**
         * @brief Name of the function.
         */
        std::string functionName;

        /**
         * @brief Pointer to the function's argument list.
         */
        std::shared_ptr<FunctionArgs> functionArgs;

        /**
         * @brief Pointer to the function's return Type.
         */
        std::shared_ptr<Type> functionReturnType;

    public:
        /**
         * @brief Retrieves the function's name.
         * @return A string containing the function name.
         */
        std::string getFunctionName();

        std::shared_ptr<Type> getFunctionReturnType();

        /**
         * @brief Produces a textual representation: "fn functionName(args):returnType".
         * @return A string with the function definition.
         */
        std::string getText() override;

        /**
         * @brief Constructs a Function object.
         * @param functionName The function's name.
         * @param functionArgs Shared pointer to FunctionArgs.
         * @param functionReturnType Shared pointer to the return Type.
         */
        Function(std::string functionName, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType);

        /**
         * @brief Destructor for Function.
         */
        ~Function();
    };

    /**
     * @class Variable
     * @brief Represents a variable with a name and a Type.
     *
     * Inherits from Basic to provide text in the form "let varName: varType".
     */
    class Variable : public Basic
    {
    private:
        /**
         * @brief The variable's name.
         */
        std::string varName;

        /**
         * @brief A shared pointer to the variable's Type.
         */
        std::shared_ptr<Type> varType;

    public:
        /**
         * @brief Retrieves the variable's name.
         * @return A string with the name.
         */
        std::string getVarName();

        /**
         * @brief Produces text like "let varName:typeName".
         * @return The textual representation of the variable.
         */
        std::string getText() override;

        /**
         * @brief Gets the variable's Type.
         * @return A shared pointer to a Type.
         */
        std::shared_ptr<Type> getVarType();

        /**
         * @brief Constructs a Variable with a given name and type.
         * @param varName The name of the variable.
         * @param varType A shared pointer to a Type.
         */
        Variable(const std::string &varName, std::shared_ptr<Type> varType);

        /**
         * @brief Destructor for Variable.
         */
        ~Variable();
    };

    /**
     * @typedef Data
     * @brief A variant capable of holding several possible data types (Function, std::string, int, float, double, bool).
     */
    using Data = std::variant<
        std::shared_ptr<Function>,
        std::string,
        int,
        float,
        double,
        bool>;

    /**
     * @class Value
     * @brief Wraps a Data variant and a corresponding Type.
     *
     * Inherits from Basic to produce a textual representation of the stored Data.
     */
    class Value : public Basic
    {
    public:
        /**
         * @brief Constructs a Value object with a Data variant and a Type.
         * @param value The Data to store (could be a string, int, function pointer, etc.).
         * @param valueType A shared pointer to a Type describing the data.
         */
        Value(Data value, std::shared_ptr<Type> valueType);

        /**
         * @brief Destructor for Value.
         */
        ~Value();

        /**
         * @brief Retrieves the underlying Data variant.
         * @return The stored Data.
         */
        Data getValue();

        /**
         * @brief Produces a textual representation of the stored data (e.g. "42", "true").
         * @return A string representation.
         */
        std::string getText() override;

        /**
         * @brief Gets the associated Type of this Value.
         * @return A shared pointer to the Type.
         */
        std::shared_ptr<Type> getValueType();

    private:
        /**
         * @brief The Data variant holding the actual value (e.g., int, string, etc.).
         */
        Data value;

        /**
         * @brief The semantic Type for the stored data.
         */
        std::shared_ptr<Type> valueType;
    };

    /**
     * @class Assign
     * @brief Represents an assignment operation, e.g., "let varName:varType = value".
     *
     * Inherits from Basic to produce the textual form of the assignment.
     */
    class Assign : public Basic
    {
    public:
        /**
         * @brief Constructs an Assign between a Variable and a Value.
         * @param variable A shared pointer to the Variable.
         * @param value A shared pointer to the Value.
         */
        Assign(std::shared_ptr<Variable> variable, std::shared_ptr<Value> value);

        /**
         * @brief Destructor for Assign.
         */
        ~Assign();

        /**
         * @brief Produces text in the form "let varName:varType = value".
         * @return The string representation of the assignment.
         */
        std::string getText() override;

    private:
        /**
         * @brief The Variable being assigned to.
         */
        std::shared_ptr<Variable> variable;

        /**
         * @brief The Value being assigned.
         */
        std::shared_ptr<Value> value;
    };

    /**
     * @struct FunctionCallArg
     * @brief Represents an argument in a function call, with a name, a Type, and a Value.
     */
    struct FunctionCallArg
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
         * @param argument The argument's name.
         * @param type A shared pointer to a Type.
         * @param value A shared pointer to a Value.
         */
        FunctionCallArg(const std::string &argument, std::shared_ptr<Type> type, std::shared_ptr<Value> value)
            : argument(argument), argumentType(std::move(type)), value(std::move(value)) {}
    };

    /**
     * @class FunctionCallArgs
     * @brief Represents a list of FunctionCallArg items for a function call.
     *
     * Inherits from Basic to provide a textual representation of the call arguments.
     */
    class FunctionCallArgs : public Basic
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
        FunctionCallArgs(std::vector<std::shared_ptr<FunctionCallArg>> callArgs);

        /**
         * @brief Default constructor (empty list).
         */
        FunctionCallArgs();

        /**
         * @brief Adds a FunctionCallArg to the internal list.
         * @param callArg The FunctionCallArg to add.
         */
        void addCallArg(std::shared_ptr<FunctionCallArg> callArg);

        /**
         * @brief Destructor for FunctionCallArgs.
         */
        ~FunctionCallArgs();
    };

    class FunctionCall : public Basic
    {
    private:
        std::shared_ptr<Function> function;
        std::shared_ptr<FunctionCallArgs> callArgs;

    public:
        std::string getText() override;
        FunctionCall(std::shared_ptr<Function> function, std::shared_ptr<FunctionCallArgs> callArgs);
        ~FunctionCall();
    };

}

#endif

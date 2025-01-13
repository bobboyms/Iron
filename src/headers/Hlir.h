#ifndef HLIR_H
#define HLIR_H

#include "WriterCodeHLIR.h"
#include "Exceptions.h"
#include "TokenMap.h"
#include "Utils.h"
#include <memory>
#include <stack>

/**
 * @namespace hlir
 * @brief Contains classes and structures representing a High-Level IR.
 */
namespace hlir
{
    /**
     * @class Function
     * @brief Forward declaration da classe Function para evitar erros de compilação.
     */
    class Function;

    class Statement;

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

    /**
     * @class FunctionCall
     * @brief Represents a function call in the HLIR.
     *
     * The FunctionCall class inherits from Basic and implements the getText() method to provide
     * a textual representation of the function call.
     */
    class FunctionCall : public Basic
    {
    private:
        std::shared_ptr<Function> function;         ///< Shared pointer to the function being called.
        std::shared_ptr<FunctionCallArgs> callArgs; ///< Shared pointer to the arguments of the function call.

    public:
        /**
         * @brief Constructs a FunctionCall with the specified function and arguments.
         * @param function Shared pointer to the function to be called.
         * @param callArgs Shared pointer to the arguments of the function call.
         *
         * @throws HLIRException If `function` or `callArgs` is nullptr.
         */
        FunctionCall(std::shared_ptr<Function> function, std::shared_ptr<FunctionCallArgs> callArgs);

        /**
         * @brief Destructor for FunctionCall.
         */
        ~FunctionCall();

        /**
         * @brief Generates a textual representation of the function call.
         * @return A string representing the function call, e.g., "call foo(arg1, arg2)".
         *
         * @throws HLIRException If `function` is nullptr.
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
    class Plus : public Basic
    {
    private:
        std::shared_ptr<Variable> varLeft;  ///< Shared pointer to the left-hand side variable.
        std::shared_ptr<Variable> varRight; ///< Shared pointer to the right-hand side variable.

    public:
        /**
         * @brief Constructs a Plus operation with two variables.
         * @param varLeft Shared pointer to the left-hand side variable.
         * @param varRight Shared pointer to the right-hand side variable.
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        Plus(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight);

        /**
         * @brief Destructor for Plus.
         */
        ~Plus();

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
    class Minus : public Basic
    {
    private:
        std::shared_ptr<Variable> varLeft;  ///< Shared pointer to the left-hand side variable.
        std::shared_ptr<Variable> varRight; ///< Shared pointer to the right-hand side variable.

    public:
        /**
         * @brief Constructs a Minus operation with two variables.
         * @param varLeft Shared pointer to the left-hand side variable.
         * @param varRight Shared pointer to the right-hand side variable.
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        Minus(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight);

        /**
         * @brief Destructor for Minus.
         */
        ~Minus();

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
    class Mult : public Basic
    {
    private:
        std::shared_ptr<Variable> varLeft;  ///< Shared pointer to the left-hand side variable.
        std::shared_ptr<Variable> varRight; ///< Shared pointer to the right-hand side variable.

    public:
        /**
         * @brief Constructs a Mult operation with two variables.
         * @param varLeft Shared pointer to the left-hand side variable.
         * @param varRight Shared pointer to the right-hand side variable.
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        Mult(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight);

        /**
         * @brief Destructor for Mult.
         */
        ~Mult();

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
    class Div : public Basic
    {
    private:
        std::shared_ptr<Variable> varLeft;  ///< Shared pointer to the left-hand side variable.
        std::shared_ptr<Variable> varRight; ///< Shared pointer to the right-hand side variable.

    public:
        /**
         * @brief Constructs a Div operation with two variables.
         * @param varLeft Shared pointer to the left-hand side variable.
         * @param varRight Shared pointer to the right-hand side variable.
         *
         * @throws HLIRException If `varLeft` or `varRight` is nullptr.
         */
        Div(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight);

        /**
         * @brief Destructor for Div.
         */
        ~Div();

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
    class Cast : public Basic
    {
    private:
        std::shared_ptr<Variable> variable; ///< Shared pointer to the variable to be casted.
        std::shared_ptr<Type> type;         ///< Shared pointer to the target type of the casting.

    public:
        /**
         * @brief Constructs a Cast operation for a specific variable and target type.
         * @param variable Shared pointer to the variable to be casted.
         * @param type Shared pointer to the target type for casting.
         *
         * @throws HLIRException If `variable` or `type` is nullptr.
         */
        Cast(std::shared_ptr<Variable> variable, std::shared_ptr<Type> type);

        /**
         * @brief Destructor for Cast.
         */
        ~Cast();

        /**
         * @brief Generates a textual representation of the casting operation.
         * @return A string representing the casting, e.g., "cast a:int to float".
         *
         * @throws HLIRException If `variable` or `type` is nullptr.
         */
        std::string getText() override;
    };

    /**
     * @class FunctionPtr
     * @brief Represents a pointer to a function within the HLIR.
     *
     * The FunctionPtr class inherits from Basic and implements the getText() method to provide
     * a textual representation of the function pointer.
     */
    class FunctionPtr : public Basic
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
        FunctionPtr(std::shared_ptr<Function> function);

        /**
         * @brief Destructor for FunctionPtr.
         */
        ~FunctionPtr();

        /**
         * @brief Generates a textual representation of the function pointer.
         * @return A string representing the function pointer, e.g., "fptr foo".
         *
         * @throws HLIRException If `function` is nullptr.
         */
        std::string getText() override;
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
    using ValidExpr = std::variant<
        std::shared_ptr<Div>,
        std::shared_ptr<Mult>,
        std::shared_ptr<Minus>,
        std::shared_ptr<Plus>,
        std::shared_ptr<FunctionCall>,
        std::shared_ptr<Variable>,
        std::shared_ptr<Cast>,
        std::shared_ptr<FunctionPtr>>;

    /**
     * @class Expr
     * @brief Represents a generic expression in the HLIR.
     *
     * The Expr class inherits from Basic and encapsulates a valid expression (ValidExpr) associated with a variable.
     */
    class Expr : public Basic
    {
    private:
        ValidExpr validExpr;                ///< The encapsulated valid expression.
        std::shared_ptr<Variable> variable; ///< Shared pointer to the variable associated with the expression.

    public:
        /**
         * @brief Constructs a generic expression with a variable and a valid expression.
         * @param variable Shared pointer to the associated variable.
         * @param validExpr The valid expression encapsulated.
         *
         * @throws HLIRException If `variable` is nullptr or if `validExpr` is invalid.
         */
        Expr(std::shared_ptr<Variable> variable, ValidExpr validExpr);

        /**
         * @brief Destructor for Expr.
         */
        ~Expr();

        /**
         * @brief Generates a textual representation of the generic expression.
         * @return A string representing the expression, e.g., "let a:int = PLUS a, b".
         *
         * @throws HLIRException If `variable` is nullptr or if `validExpr` is invalid.
         */
        std::string getText() override;
    };

    // statementList: (expr | functionCall)*;

    using ValidStatement = std::variant<
        std::shared_ptr<Expr>,
        std::shared_ptr<FunctionCall>>;

    class Statement : public Basic
    {
    private:
        std::vector<ValidStatement> statementList;

    public:
        Statement();
        Statement(std::vector<ValidStatement> statementList);
        ~Statement();
        void addStatement(ValidStatement statement);
        std::vector<ValidStatement> getStatements();
        std::string getText() override;
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

    protected:
        /**
         * @brief Pointer to the function's body (optional).
         */
        std::shared_ptr<Statement> statement;

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
         * @brief Constructs a Function object with a statement (function body).
         * @param functionName The function's name.
         * @param functionArgs Shared pointer to FunctionArgs.
         * @param functionReturnType Shared pointer to the return Type.
         * @param statement Shared pointer to the Statement (function body).
         */
        Function(std::string functionName, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType, std::shared_ptr<Statement> statement);

        /**
         * @brief Destructor for Function.
         */
        ~Function();
    };

}

#endif

#ifndef HLIR_H
#define HLIR_H

#include <memory>
#include "Exceptions.h"
#include "TokenMap.h"
#include "Utils.h"
#include "WriterCodeHLIR.h"

/**
 * @namespace hlir
 * @brief Contains classes and structures representing a High-Level IR.
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
            return parent.lock(); // Retorna um shared_ptr se o pai ainda existir
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
     * @brief Represents a specific data type (int, float, etc.) in the IR.
     *
     * Inherits from Basic to provide a textual form of the type.
     */
    class Type final : public Basic, public Parent
    {
    private:
        /**
         * @brief Integer-based type identifier, e.g., TYPE_INT, TYPE_FLOAT.
         */
        int type{};

    protected:
    public:
        /**
         * @brief Retrieves the integer-based type identifier.
         * @return An int representing this type code.
         */
        int getType() const;

        /**
         * @brief Returns the textual form of this type, e.g., "int".
         * @return The text representing the type.
         */
        std::string getText() override;

        /**
         * @brief Constructs a Type using an integer type code.
         * @param type The integer code (e.g., TYPE_INT).
         */
        explicit Type(int type);
        Type();

        void set(int type);
        /**
         * @brief Destructor for Type.
         */
        ~Type() override;

        void setParent(std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @struct Arg
     * @brief Represents a single argument with a name and an associated Type.
     */
    struct Arg final : Parent
    {
        /**
         * @brief The argument's name.
         */
        std::string name;

        /**
         * @brief Shared pointer to a Type for this argument.
         */
        std::shared_ptr<Type> type;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

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
    };

    /**
     * @class FunctionArgs
     * @brief Represents a list of Arg objects (function parameters).
     *
     * Inherits from Basic to provide a combined textual representation.
     */
    class FunctionArgs final : public Basic, public Parent
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
        void addArg(const std::shared_ptr<Arg> &arg);

        /**
         * @brief Produces a textual representation of all arguments, e.g., "x:int,y:int".
         * @return The comma-separated list of arguments.
         */
        std::string getText() override;

        std::shared_ptr<Arg> findArgByName(const std::string &argName) const;

        std::vector<std::shared_ptr<Arg>> getArgs();

        /**
         * @brief Default constructor creating an empty FunctionArgs.
         */
        FunctionArgs();

        /**
         * @brief Destructor for FunctionArgs.
         */
        ~FunctionArgs() override;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class Variable
     * @brief Represents a variable with a name and a Type.
     *
     * Inherits from Basic to provide text in the form "let varName: varType".
     */
    class Variable final : public Expression
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

        bool anotherScope = false;

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
        std::shared_ptr<Variable> set(const std::string &varName, const std::shared_ptr<Type> &varType);

        void changeToAnotherScope();
        bool isAnotherScope() const;

        Variable();

        /**
         * @brief Destructor for Variable.
         */
        ~Variable() override;

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @typedef Data
     * @brief A variant capable of holding several possible data types (Function, std::string, int, float, double,
     * bool).
     */
    using Data =
            std::variant<std::shared_ptr<Function>, std::shared_ptr<Variable>, std::string, int, float, double, bool>;

    /**
     * @class Value
     * @brief Wraps a Data variant and a corresponding Type.
     *
     * Inherits from Basic to produce a textual representation of the stored Data.
     */
    class Value final : public Basic, public Parent
    {
    public:
        /**
         * @brief setValue a Value object with a Data variant and a Type.
         * @param value The Data to store (could be a string, int, function pointer, etc.).
         * @param valueType A shared pointer to a Type describing the data.
         */
        std::shared_ptr<Value> set(const Data &value, const std::shared_ptr<Type> &valueType);

        Value();

        /**
         * @brief Destructor for Value.
         */
        ~Value() override;

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

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

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
    class Assign final : public Basic, public Parent
    {
    protected:
        /**
         * @brief The Variable being assigned to.
         */
        std::shared_ptr<Variable> variable;

        /**
         * @brief The Value being assigned.
         */
        std::shared_ptr<Value> value;

    public:
        /**
         * @brief setAssign an Assign between a Variable and a Value.
         * @param variable A shared pointer to the Variable.
         * @param value A shared pointer to the Value.
         */
        std::shared_ptr<Assign> set(const std::shared_ptr<Variable> &variable, const std::shared_ptr<Value> &value);

        Assign();

        /**
         * @brief Destructor for Assign.
         */
        ~Assign() override;

        /**
         * @brief Produces text in the form "let varName:varType = value".
         * @return The string representation of the assignment.
         */
        std::string getText() override;

        std::shared_ptr<Variable> getVariable();
        std::shared_ptr<Value> getValue();

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @struct FunctionCallArg
     * @brief Represents an argument in a function call, with a name, a Type, and a Value.
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

    public:
        /**
         * @brief Constructs a FunctionCall with the specified function and arguments.
         * @param function Shared pointer to the function to be called.
         * @param callArgs Shared pointer to the arguments of the function call.
         *
         * @throws HLIRException If `function` or `callArgs` is nullptr.
         */
        std::shared_ptr<FunctionCall> set(const std::shared_ptr<Function> &function,
                                          const std::shared_ptr<FunctionCallArgs> &callArgs);

        std::shared_ptr<Function> getFunction();

        FunctionCall();

        /**
         * @brief Destructor for FunctionCall.
         */
        ~FunctionCall() override;

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
    // using ValidExpr = std::variant<
    //     std::shared_ptr<Div>,
    //     std::shared_ptr<Mult>,
    //     std::shared_ptr<Minus>,
    //     std::shared_ptr<Plus>,
    //     std::shared_ptr<FunctionCall>,
    //     std::shared_ptr<Variable>,
    //     std::shared_ptr<Cast>,
    //     std::shared_ptr<FunctionPtr>>;

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

    using ValidStatement = std::variant<std::shared_ptr<Assign>, std::shared_ptr<Expr>, std::shared_ptr<FunctionCall>,
                                        std::shared_ptr<FuncReturn>>;

    inline bool isValidStatementNull(const ValidStatement &statement)
    {
        return std::visit([](const auto &ptr) { return ptr == nullptr; }, statement);
    }


    class Statement final : public Basic, public Parent
    {
    private:
        int varId = 0;
        std::vector<ValidStatement> statementList;

    public:
        bool logged = false;
        std::shared_ptr<Statement> set(ValidStatement statementList);
        Statement();
        ~Statement() override;
        void addStatement(ValidStatement statement);
        std::vector<ValidStatement> getStatements();
        std::string getText() override;
        std::string getNewVarName();
        std::shared_ptr<Variable> findVarByName(std::string varName);

        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }
    };

    /**
     * @class Function
     * @brief Represents a function, including its name, parameters, and return type.
     *
     * Inherits from Basic to provide a text output like "fn name(args):returnType".
     */
    class Function final : public Basic, public Parent
    {
    private:
        /**
         * @brief Name of the function.
         */
        std::string functionName;

        /**
         * @brief Pointer to the function's return Type.
         */
        std::shared_ptr<Type> functionReturnType;

        bool external;
        bool variedArguments;

    protected:
        /**
         * @brief Pointer to the function's body (optional).
         */
        std::shared_ptr<Statement> statement;
        std::shared_ptr<Function> parentFunction;
        int languageType;

        /**
         * @brief Pointer to the function's argument list.
         */
        std::shared_ptr<FunctionArgs> functionArgs;

        bool inlineFunction = false;

    public:
        /**
         * @brief Retrieves the function's name.
         * @return A string containing the function name.
         */
        std::string getFunctionName();

        std::shared_ptr<Type> getFunctionReturnType();

        std::shared_ptr<FunctionArgs> getFunctionArgs();

        std::shared_ptr<Function> getParentFunction();

        void setParentFunction(const std::shared_ptr<Function> &function);

        std::shared_ptr<Statement> getStatement();
        void setStatement(std::shared_ptr<Statement> statement);


        void setParent(const std::shared_ptr<Parent> newParent) override
        {
            parent = newParent;
        }

        /**
         * @brief Produces a textual representation: "fn functionName(args):returnType".
         * @return A string with the function definition.
         */
        std::string getText() override;

        /**
         * @brief set a Function object.
         * @param functionName The function's name.
         * @param functionArgs Shared pointer to FunctionArgs.
         * @param functionReturnType Shared pointer to the return Type.
         */
        std::shared_ptr<Function> set(const std::string &functionName,
                                      const std::shared_ptr<FunctionArgs> &functionArgs,
                                      const std::shared_ptr<Type> &functionReturnType);

        void enableInline();
        bool isExternal();
        int getLanguageType();
        void setLanguageType(int type);
        void changeToExternal();
        void changeToVariedArguments();
        bool isVariedArguments();
        bool getInline();
        // bool getInline() const;

        /**
         * @brief set a Function object with a statement (function body).
         * @param functionName The function's name.
         * @param functionArgs Shared pointer to FunctionArgs.
         * @param functionReturnType Shared pointer to the return Type.
         * @param statement Shared pointer to the Statement (function body).
         */
        std::shared_ptr<Function> set(const std::string &functionName,
                                      const std::shared_ptr<FunctionArgs> &functionArgs,
                                      const std::shared_ptr<Type> &functionReturnType,
                                      const std::shared_ptr<Statement> &statement);

        std::shared_ptr<Function> clone() const;

        Function();
        /**
         * @brief Destructor for Function.
         */
        ~Function() override;
    };

    /**
     * @class Context
     * @brief Holds contextual resources like a shared string stream.
     */
    class Context final : public Basic
    {
    private:
    protected:
        std::vector<std::shared_ptr<Function>> functions;

    public:
        Context();
        /**
         * @brief Destroys the Context instance.
         */
        ~Context() override;
        void addFunction(const std::shared_ptr<Function> &function);

        std::shared_ptr<Function> getFunctionByName(const std::string &funcName) const;

        /**
         * @brief Produces a textual representation: "fn functionName(args):returnType".
         * @return A string with the function definition.
         */
        std::string getText() override;

        std::vector<std::shared_ptr<Function>> getFunctions();
        void addExternalFunction(const std::shared_ptr<Function> &function);
    };

} // namespace hlir
#endif

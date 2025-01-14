#include "../headers/Hlir.h"

namespace hlir
{

    /**
     * Assign
     */

    std::shared_ptr<Assign> Assign::set(std::shared_ptr<Variable> newVariable, std::shared_ptr<Value> newValue)
    {
        if (!newVariable)
        {
            throw HLIRException("Assign::set failed: newVariable is null.");
        }

        if (!newValue)
        {
            throw HLIRException("Assign::set failed: newValue is null.");
        }

        if (newVariable->getVarType()->getType() != newValue->getValueType()->getType())
        {
            throw HLIRException("Assign::set failed: Variable type is incompatible with the value type.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("Assign::set failed: shared_from_this() returned null.");
        }
        variable = newVariable;
        value = newValue;

        variable->setParent(parentPtr);
        value->setParent(parentPtr);

        // Realiza o cast para std::shared_ptr<Assign>
        auto assignPtr = std::dynamic_pointer_cast<Assign>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Assign::set failed: Unable to cast Parent to Assign.");
        }

        return assignPtr;
    }

    Assign::Assign()
    {
    }

    Assign::~Assign() {}

    std::string Assign::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("let {}:{} = {}", variable->getVarName(), variable->getVarType()->getText(), value->getText());

        return sb.str();
    }

    /*********
     *
     */

    Plus::Plus()
    {
    }

    Plus::~Plus() {}

    std::string Plus::getText()
    {
        sb.str("");
        sb.clear();
        // mathOp: ( MULT | DIV | PLUS | MINUS) opLeft COMMA opRight;
        sb << util::format("PLUS {}, {}", varLeft->getVarName(), varRight->getVarName());

        return sb.str();
    }
    /*** Binary
     *  ***/

    BinaryOperation::BinaryOperation() {}
    BinaryOperation::~BinaryOperation() {}

    /**
     * @brief Constructs a Minus operation with two variables.
     * @param varLeft Shared pointer to the left-hand side variable.
     * @param varRight Shared pointer to the right-hand side variable.
     *
     * @throws HLIRException If `varLeft` or `varRight` is nullptr.
     */
    std::shared_ptr<BinaryOperation> BinaryOperation::set(std::shared_ptr<Variable> newVarLeft, std::shared_ptr<Variable> newVarRight)
    {
        if (!newVarLeft)
        {
            throw HLIRException("Minus::set failed: newVarLeft is null.");
        }

        if (!newVarRight)
        {
            throw HLIRException("Minus::set failed: newVarRight is null.");
        }

        if (newVarLeft->getVarType()->getType() != newVarRight->getVarType()->getType())
        {
            throw HLIRException("Minus::set failed: The variables must be of the same type.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("Minus::set failed: shared_from_this() returned null.");
        }

        newVarLeft->setParent(parentPtr);
        newVarRight->setParent(parentPtr);

        varLeft = newVarLeft;
        varRight = newVarRight;

        // Realiza o cast para std::shared_ptr<Minus>
        auto assignPtr = std::dynamic_pointer_cast<BinaryOperation>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Minus::set failed: Unable to cast Parent to Minus.");
        }

        return assignPtr;
    }

    /**
     *
     */

    // std::shared_ptr<Minus> Minus::set(std::shared_ptr<Variable> newVarLeft, std::shared_ptr<Variable> newVarRight)
    // {
    // }

    Minus::Minus()
    {
    }

    Minus::~Minus() {}

    std::string Minus::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("MINUS {}, {}", varLeft->getVarName(), varRight->getVarName());

        return sb.str();
    }

    Mult::Mult()
    {
    }

    Mult::~Mult() {}

    std::string Mult::getText()
    {
        sb.str("");
        sb.clear();
        // mathOp: ( MULT | DIV | PLUS | MINUS) opLeft COMMA opRight;
        sb << util::format("MULT {}, {}", varLeft->getVarName(), varRight->getVarName());

        return sb.str();
    }

    Div::Div()
    {
    }

    Div::~Div() {}

    std::string Div::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("DIV {}, {}", varLeft->getVarName(), varRight->getVarName());

        return sb.str();
    }

    std::shared_ptr<Expr> Expr::set(std::shared_ptr<Variable> newVariable, ValidExpr newValidExpr)
    {
        if (!newVariable)
        {
            throw HLIRException("Expr::set failed: newVariable is null.");
        }

        variable = newVariable;
        validExpr = newValidExpr;

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("Expr::set failed: shared_from_this() returned null.");
        }

        variable->setParent(parentPtr);
        std::visit([parentPtr](auto &&arg)
                   {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, std::shared_ptr<Div>> ||
                          std::is_same_v<T, std::shared_ptr<Mult>> ||
                          std::is_same_v<T, std::shared_ptr<Minus>> ||
                          std::is_same_v<T, std::shared_ptr<Plus>> ||
                          std::is_same_v<T, std::shared_ptr<FunctionCall>> ||
                          std::is_same_v<T, std::shared_ptr<Variable>> ||
                          std::is_same_v<T, std::shared_ptr<Cast>> ||
                          std::is_same_v<T, std::shared_ptr<FunctionPtr>>)
            {
                if (arg)
                {
                    arg->setParent(parentPtr);
                }
                else
                {
                    throw HLIRException("Expr::set failed: Expression argument is null.");
                }
            }
            else
            {
                throw HLIRException("Expr::set failed: Unsupported expression type.");
            } }, validExpr);

        auto exprPtr = std::dynamic_pointer_cast<Expr>(parentPtr);
        if (!exprPtr)
        {
            throw HLIRException("Expr::set failed: Unable to cast Parent to Expr.");
        }

        return exprPtr;
    }

    Expr::Expr()
    {
    }

    Expr::~Expr()
    {
    }

    std::string Expr::getText()
    {
        // Reseta o stringstream da classe base
        sb.str("");
        sb.clear();

        // Usa std::visit para lidar com cada tipo de expressão armazenada em validExpr
        std::visit([this](auto &&exprPtr)
                   {
            using T = std::decay_t<decltype(exprPtr)>;
            if constexpr (std::is_same_v<T, std::shared_ptr<Div>> ||
                          std::is_same_v<T, std::shared_ptr<Mult>> ||
                          std::is_same_v<T, std::shared_ptr<Minus>> ||
                          std::is_same_v<T, std::shared_ptr<Plus>> ||
                          std::is_same_v<T, std::shared_ptr<FunctionCall>> ||
                          std::is_same_v<T, std::shared_ptr<Cast>>)
            {
                if (exprPtr)
                {
                    sb << util::format("let {}:{} = {}", variable->getVarName(), variable->getVarType()->getText(), exprPtr->getText());
                }
                else
                {
                    throw HLIRException("Expr::getText failed: Expression pointer is null.");
                }
            }
            else
            if constexpr (std::is_same_v<T, std::shared_ptr<Variable>>)
            {
                if (!exprPtr)
                {
                    throw HLIRException("Expr::getText failed: Variable expression pointer is null.");
                }

                if (variable->getVarName() == exprPtr->getVarName()) {
                    throw HLIRException("Expr::getText failed: The variables cannot have the same name.");
                }

                sb << util::format("let {}:{} = {}", variable->getVarName(), variable->getVarType()->getText(), exprPtr->getVarName());
            }
            else {
                throw HLIRException("Expr::getText failed: Unsupported expression type.");
            } }, validExpr);

        return sb.str();
    }

    std::shared_ptr<Cast> Cast::apply(std::shared_ptr<Variable> newVariable, std::shared_ptr<Type> newType)
    {
        if (!newVariable)
        {
            throw HLIRException("Cast::apply failed: newVariable is null.");
        }

        if (!newType)
        {
            throw HLIRException("Cast::apply failed: newType is null.");
        }

        if (!newVariable->getVarType())
        {
            throw HLIRException("Cast::apply failed: newVariable's type is null.");
        }

        if (!newType->getType())
        {
            throw HLIRException("Cast::apply failed: newType's type is null.");
        }

        variable = newVariable;
        type = newType;

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("Cast::apply failed: shared_from_this() returned null.");
        }

        variable->setParent(parentPtr);
        type->setParent(parentPtr);

        // Realiza o cast para std::shared_ptr<Cast>
        auto assignPtr = std::dynamic_pointer_cast<Cast>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Cast::apply failed: Unable to cast Parent to Cast.");
        }

        return assignPtr;
    }

    Cast::Cast()
    {
    }

    Cast::~Cast()
    {
        // Como usamos shared_ptr, não há necessidade de liberar manualmente os recursos.
    }

    std::string Cast::getText()
    {
        // Reseta o stringstream da classe base
        sb.str("");
        sb.clear();

        // cast: anotherVarName = IDENTIFIER typeLeft TO typeRight;
        sb << util::format("{} {} to {}", variable->getVarName(), variable->getVarType()->getText(), type->getText());

        return sb.str();
    }

    std::shared_ptr<FunctionPtr> FunctionPtr::set(std::shared_ptr<Function> newFunction)
    {
        if (!newFunction)
        {
            throw HLIRException("FunctionPtr::set failed: newFunction is null.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("FunctionPtr::set failed: shared_from_this() returned null.");
        }

        function = newFunction;
        function->setParent(parentPtr);

        auto assignPtr = std::dynamic_pointer_cast<FunctionPtr>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("FunctionPtr::set failed: Unable to cast Parent to FunctionPtr.");
        }

        return assignPtr;
    }

    FunctionPtr::FunctionPtr()
    {
    }

    FunctionPtr::~FunctionPtr()
    {
    }

    std::string FunctionPtr::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("fptr {}", function->getFunctionName());

        return sb.str();
    }

}

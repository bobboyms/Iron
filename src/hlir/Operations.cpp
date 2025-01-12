#include "../headers/Hlir.h"

namespace hlir
{
    Assign::Assign(std::shared_ptr<Variable> variable, std::shared_ptr<Value> value)
        : variable(variable), value(value)
    {

        if (variable->getVarType()->getType() != value->getValueType()->getType())
        {
            throw HLIRException("The variable type is incompatible with the value.");
        }
    }

    Assign::~Assign() {}

    std::string Assign::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("let {}:{} = {}\n", variable->getVarName(), variable->getVarType()->getText(), value->getText());

        return sb.str();
    }

    /*********
     *
     */

    Plus::Plus(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight)
        : varLeft(varLeft), varRight(varRight)
    {

        if (varLeft->getVarType()->getType() != varRight->getVarType()->getType())
        {
            throw HLIRException("The variables need be the same type.");
        }
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

    /**
     *
     */

    Minus::Minus(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight)
        : varLeft(varLeft), varRight(varRight)
    {

        if (varLeft->getVarType()->getType() != varRight->getVarType()->getType())
        {
            throw HLIRException("The variables need be the same type.");
        }
    }

    Minus::~Minus() {}

    std::string Minus::getText()
    {
        sb.str("");
        sb.clear();
        // mathOp: ( MULT | DIV | PLUS | MINUS) opLeft COMMA opRight;
        sb << util::format("MINUS {}, {}", varLeft->getVarName(), varRight->getVarName());

        return sb.str();
    }

    /**
     *
     */

    Mult::Mult(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight)
        : varLeft(varLeft), varRight(varRight)
    {

        if (varLeft->getVarType()->getType() != varRight->getVarType()->getType())
        {
            throw HLIRException("The variables need be the same type.");
        }
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

    /***
     *
     */
    Div::Div(std::shared_ptr<Variable> varLeft, std::shared_ptr<Variable> varRight)
        : varLeft(varLeft), varRight(varRight)
    {

        if (varLeft->getVarType()->getType() != varRight->getVarType()->getType())
        {
            throw HLIRException("The variables need be the same type.");
        }
    }

    Div::~Div() {}

    std::string Div::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("DIV {}, {}", varLeft->getVarName(), varRight->getVarName());

        return sb.str();
    }

    Expr::Expr(std::shared_ptr<Variable> variable, ValidExpr validExpr)
        : validExpr(validExpr), variable(variable)
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
                    sb << util::format("let {}:{} = {}\n", variable->getVarName(), variable->getVarType()->getText(), exprPtr->getText());
                }
                else
                {
                    throw HLIRException("Expression pointer is null.");
                }
            }
            else
            if constexpr (std::is_same_v<T, std::shared_ptr<Variable>>)
            {
                sb << util::format("let {}:{} = {}\n", variable->getVarName(), variable->getVarType()->getText(), exprPtr->getVarName());
            } else {
                throw HLIRException("Unsupported expression type.");
            } }, validExpr);

        return sb.str();
    }

    Cast::Cast(std::shared_ptr<Variable> variable, std::shared_ptr<Type> type)
        : variable(variable), type(type)
    {
        if (!this->variable)
        {
            throw HLIRException("Variable pointer is null in Cast constructor.");
        }

        if (!this->type)
        {
            throw HLIRException("Type pointer is null in Cast constructor.");
        }
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

    FunctionPtr::FunctionPtr(std::shared_ptr<Function> function)
        : function(function)
    {
        if (!this->function)
        {
            throw HLIRException("Function pointer is null in FunctionPtr constructor.");
        }
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
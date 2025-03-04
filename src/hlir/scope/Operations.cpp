#include "../../headers/Hlir.h"

namespace hlir
{

    /**
     * Assign
     */

    std::shared_ptr<Value> Assign::getValue()
    {
        return value;
    }

    std::shared_ptr<Assign> Assign::set(const std::shared_ptr<Variable> &newVariable,
                                        const std::shared_ptr<Value> &newValue)
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

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
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

    Assign::Assign() = default;

    Assign::~Assign() = default;

    std::shared_ptr<Variable> Assign::getVariable()
    {
        return variable;
    }

    std::string Assign::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("{}:{} = {}", variable->getRealName(), variable->getVarType()->getText(),
                           value->getText());

        return sb.str();
    }

    /**
     * @brief Default constructor for the Plus class.
     *
     * @return Constructs a Plus operation object.
     */

    Plus::Plus() = default;

    Plus::~Plus() = default;

    std::string Plus::getText()
    {
        sb.str("");
        sb.clear();
        // mathOp: ( MULT | DIV | PLUS | MINUS) opLeft COMMA opRight;
        sb << util::format("PLUS {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }
    /*** Binary
     *  ***/

    BinaryOperation::BinaryOperation() = default;
    BinaryOperation::~BinaryOperation() = default;

    std::shared_ptr<Variable> BinaryOperation::getVarLeft()
    {
        return varLeft;
    }
    std::shared_ptr<Variable> BinaryOperation::getVarRight()
    {
        return varRight;
    }

    /**
     * @brief Constructs a Minus operation with two variables.
     * @param newVarLeft
     * @param newVarRight
     * @param varLeft Shared pointer to the left-hand side variable.
     * @param varRight Shared pointer to the right-hand side variable.
     *
     * @throws HLIRException If `varLeft` or `varRight` is nullptr.
     */
    /**
     * @brief Configure a binary operation with left and right operands
     * 
     * @param varLeft The left operand variable
     * @param varRight The right operand variable
     * @return std::shared_ptr<BinaryOperation> Pointer to this object for method chaining
     * @throws HLIRException If parameters are invalid or operation fails
     */
    std::shared_ptr<BinaryOperation> BinaryOperation::set(const std::shared_ptr<Variable> &varLeft,
                                                         const std::shared_ptr<Variable> &varRight)
    {
        // Validate parameters
        if (!varLeft) {
            throw HLIRException("BinaryOperation::set failed: Left operand is null.");
        }

        if (!varRight) {
            throw HLIRException("BinaryOperation::set failed: Right operand is null.");
        }

        if (varLeft->getVarType()->getType() != varRight->getVarType()->getType()) {
            throw HLIRException("BinaryOperation::set failed: Operands must be of the same type.");
        }

        try {
            std::shared_ptr<Parent> parentPtr = shared_from_this();
            
            // Set the operands
            this->varLeft = varLeft;
            this->varRight = varRight;
            
            // Set parent relationships
            varLeft->setParent(parentPtr);
            varRight->setParent(parentPtr);

            // Return self for chaining
            auto selfPtr = std::dynamic_pointer_cast<BinaryOperation>(parentPtr);
            if (!selfPtr) {
                throw HLIRException("BinaryOperation::set failed: Unable to cast to BinaryOperation.");
            }
            return selfPtr;
        }
        catch (const std::bad_weak_ptr& e) {
            throw HLIRException("BinaryOperation::set failed: Object not managed by shared_ptr.");
        }
    }

    /**
     *
     */

    // std::shared_ptr<Minus> Minus::set(std::shared_ptr<Variable> newVarLeft, std::shared_ptr<Variable> newVarRight)
    // {
    // }

    Minus::Minus() = default;

    Minus::~Minus() = default;

    std::string Minus::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("MINUS {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    Mult::Mult() = default;

    Mult::~Mult() = default;

    std::string Mult::getText()
    {
        sb.str("");
        sb.clear();
        // mathOp: ( MULT | DIV | PLUS | MINUS) opLeft COMMA opRight;
        sb << util::format("MULT {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    Div::Div() = default;

    Div::~Div() = default;

    std::string Div::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("DIV {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    AND::AND() = default;

    AND::~AND() = default;

    std::string AND::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("AND {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    OR::OR() = default;

    OR::~OR() = default;

    std::string OR::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("OR {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    /**
     * @brief Represents a logical NOT operation
     */
    _NOT::_NOT() = default;

    _NOT::~_NOT() = default;

    std::string _NOT::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("NOT {}, {}", varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    CMP::CMP(int op)
    {
        opType = std::make_shared<Type>(op);
    }

    CMP::~CMP() = default;

    std::shared_ptr<Type> CMP::getOpType()
    {
        return opType;
    }

    std::string CMP::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("cmp {} {}, {}", opType->getText(), varLeft->getRealName(), varRight->getRealName());

        return sb.str();
    }

    std::shared_ptr<Expression> Expr::getExpr()
    {
        return validExpr;
    }


    std::shared_ptr<Variable> Expr::getVariable()
    {
        return variable;
    }

    std::shared_ptr<Expr> Expr::set(const std::shared_ptr<Variable> &newVariable,
                                    const std::shared_ptr<Expression> &newValidExpr)
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
        validExpr->setParent(parentPtr);

        auto exprPtr = std::dynamic_pointer_cast<Expr>(parentPtr);
        if (!exprPtr)
        {

            throw HLIRException("Expr::set failed: Unable to cast Parent to Expr.");
        }

        return exprPtr;
    }

    Expr::Expr() = default;

    Expr::~Expr() = default;

    std::string Expr::getText()
    {
        // Reseta o stringstream da classe base
        sb.str("");
        sb.clear();

        sb << util::format("{}:{} = {}", variable->getRealName(), variable->getVarType()->getText(),
                           validExpr->getText());

        return sb.str();
    }

    std::shared_ptr<Cast> Cast::apply(const std::shared_ptr<Variable> &newVariable,
                                      const std::shared_ptr<Type> &newType)
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

    Cast::Cast() = default;

    Cast::~Cast() = default;

    std::shared_ptr<Variable> Cast::getVariable()
    {
        return variable;
    }

    std::shared_ptr<Type> Cast::getType()
    {
        return type;
    }

    std::string Cast::getText()
    {
        // Reseta o stringstream da classe base
        sb.str("");
        sb.clear();

        // cast: anotherVarName = IDENTIFIER typeLeft TO typeRight;
        sb << util::format("{} {} to {}", variable->getRealName(), variable->getVarType()->getText(), type->getText());

        return sb.str();
    }

    std::shared_ptr<FunctionPtr> FunctionPtr::set(const std::shared_ptr<Function> &function)
    {
        if (!function)
        {
            throw HLIRException("FunctionPtr::set failed: newFunction is null.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("FunctionPtr::set failed: shared_from_this() returned null.");
        }

        this->function = function;
        this->function->setParent(parentPtr);

        auto assignPtr = std::dynamic_pointer_cast<FunctionPtr>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("FunctionPtr::set failed: Unable to cast Parent to FunctionPtr.");
        }

        return assignPtr;
    }

    FunctionPtr::FunctionPtr() = default;

    FunctionPtr::~FunctionPtr() = default;

    std::string FunctionPtr::getText()
    {
        sb.str("");
        sb.clear();

        sb << util::format("fptr {}", function->getFunctionName());

        return sb.str();
    }

    Context::Context() = default;

    Context::~Context() = default;

    std::vector<std::shared_ptr<Function>> Context::getFunctions()
    {
        return functions;
    }

    std::vector<std::shared_ptr<Struct>> Context::getStructs()
    {
        return structs_;
    }

    void Context::addExternalFunction(const std::shared_ptr<Function> &function)
    {
        if (!function)
        {
            throw HLIRException("Context::addExternalFunction failed: function is null.");
        }

        if (!function->isExternal())
        {
            throw HLIRException("Context::addExternalFunction failed: function is not external.");
        }

        if (!getFunctionByName(function->getFunctionName()))
        {
            functions.push_back(function);
        }
    }

    void Context::addFunction(const std::shared_ptr<Function> &function)
    {
        if (!function)
        {
            throw HLIRException("Context::addFunction failed: function is null.");
        }

        if (!functions.empty() && function->getInline())
        {
            const std::shared_ptr<Function> lastFunction = functions.back();
            function->setParentFunction(lastFunction);
        }

        functions.push_back(function);
    }

    void Context::addStruct(const std::shared_ptr<Struct> &struct_)
    {
        if (!struct_)
        {
            throw HLIRException("Context::addStruct failed: struct is null.");
        }

        structs_.push_back(struct_);
    }

    std::shared_ptr<Function> Context::getFunctionByName(const std::string &funcName) const
    {
        for (auto function: functions)
        {
            if (function->getFunctionName() == funcName)
            {
                return function;
            }
        }

        return nullptr;
    }

    std::shared_ptr<Struct> Context::getStructByName(const std::string &structName) const
    {
        for (auto struct_: structs_)
        {
            if (struct_->getName() == structName)
            {
                return struct_;
            }
        }

        return nullptr;
    }

    std::string Context::getText()
    {
        sb.str("");
        sb.clear();

        for (const auto &function: functions)
        {

            sb << util::format("{}\n", function->getText());
        }

        return sb.str();
    }

} // namespace hlir

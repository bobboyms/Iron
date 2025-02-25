#include "../../headers/Hlir.h"

namespace hlir
{

    std::shared_ptr<Value> Value::set(const Data &newValue, const std::shared_ptr<Type> &newValueType)
    {
        if (!newValueType)
        {
            throw HLIRException("Value::set failed: newValueType is null.");
        }

        if (newValueType->getType() == tokenMap::VOID)
        {
            throw HLIRException("Value::set failed: The value type cannot be void.");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("Value::set failed: shared_from_this() returned null.");
        }

        newValueType->setParent(parentPtr);

        if (!newValueType->getType())
        {
            throw HLIRException("Value::set failed: newValueType's type is null.");
        }

        valueType = newValueType;
        value = newValue;

        // Verifica se value contém uma Function e estabelece seu pai
        if (std::holds_alternative<std::shared_ptr<Function>>(newValue))
        {
            auto funcPtr = std::get<std::shared_ptr<Function>>(newValue);
            if (!funcPtr)
            {
                throw HLIRException("Value::set failed: Function pointer in value is null.");
            }
            funcPtr->setParent(parentPtr);
        }

        // Realiza o cast para std::shared_ptr<Value>
        auto assignPtr = std::dynamic_pointer_cast<Value>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Value::set failed: Unable to cast Parent to Value.");
        }

        return assignPtr;
    }

    Value::Value() = default;

    Value::~Value() = default;

    Data Value::getValue()
    {
        return value;
    }

    std::shared_ptr<Type> Value::getValueType()
    {
        return valueType;
    }

    std::string Value::getText()
    {
        sb.str("");
        sb.clear();

        // Usa std::visit p/ converter "value" num std::string
        std::visit(
                [this](auto &&arg)
                {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<Function>>)
                    {
                        // Se Function tiver um método getText():
                        if (valueType->getType() == tokenMap::FUNCTION_PTR)
                        {
                            sb << util::format("{} {}", tokenMap::getTokenText(tokenMap::FUNCTION_PTR),
                                               arg->getFunctionName());
                        }
                        else
                        {
                            sb << arg->getFunctionName();
                        }
                    }
                    else if constexpr (std::is_same_v<T, std::shared_ptr<Variable>>)
                    {
                        sb << util::format("{}", arg->getVarName());
                    }
                    else if constexpr (std::is_same_v<T, std::string>)
                    {
                        sb << arg;
                    }
                    else if constexpr (std::is_same_v<T, int>)
                    {
                        sb << arg; // int -> "123"
                    }
                    else if constexpr (std::is_same_v<T, float>)
                    {
                        sb << arg; // float -> "1.230000"
                    }
                    else if constexpr (std::is_same_v<T, double>)
                    {
                        sb << arg; // double -> "3.140000"
                    }
                    else if constexpr (std::is_same_v<T, bool>)
                    {
                        sb << (arg ? "true" : "false");
                    }
                    else
                    {
                        throw HLIRException("Value::getText failed: Unsupported type in value.");
                    }
                },
                value);

        return sb.str();
    }

    // Variable

    void Variable::changeToAnotherScope()
    {
        anotherScope = true;
    }

    bool Variable::isAnotherScope() const
    {
        return anotherScope;
    }

    std::shared_ptr<Variable> Variable::set(const std::string &newVarName, const std::shared_ptr<Type> &newVarType)
    {
        if (!newVarType)
        {
            throw HLIRException("Variable::set failed: newVarType is null.");
        }

        if (newVarType->getType() == tokenMap::VOID)
        {
            throw HLIRException("Variable::set failed: The variable type cannot be void.");
        }

        if (newVarName.empty())
        {
            throw HLIRException("Variable::set failed: The variable name cannot be empty.");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        if (!parentPtr)
        {
            throw HLIRException("Variable::set failed: shared_from_this() returned null.");
        }

        varName = newVarName;
        varType = newVarType;
        varType->setParent(parentPtr);

        // Realiza o cast para std::shared_ptr<Variable>
        auto variablePtr = std::dynamic_pointer_cast<Variable>(parentPtr);
        if (!variablePtr)
        {
            throw HLIRException("Variable::set failed: Unable to cast Parent to Variable.");
        }

        return variablePtr;
    }

    Variable::Variable() = default;
    Variable::~Variable() = default;

    void Variable::setSignature(const std::shared_ptr<Signature> &signature)
    {
        if (!signature)
        {
            throw HLIRException("Variable::setSignature failed: Signature is null.");
        }

        this->signature = signature;
    }

    std::shared_ptr<Signature> Variable::getSignature()
    {
        return signature;
    }

    std::string Variable::getVarName()
    {
        return varName;
    }

    std::shared_ptr<Type> Variable::getVarType()
    {
        return varType;
    }

    std::string Variable::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("let {}:{}", varName, varType->getText());
        return sb.str();
    }

} // namespace hlir

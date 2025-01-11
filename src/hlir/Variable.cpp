#include "Hlir.h"

namespace hlir
{

    // ----------------------------------------------------------------
    // Value (permanece igual, se ainda for útil em outro contexto)
    // ----------------------------------------------------------------
    Value::Value(Data value, std::shared_ptr<Type> valueType)
        : value(std::move(value)), valueType(std::move(valueType))
    {
    }

    Value::~Value() {}

    Data Value::getValue()
    {
        return value;
    }

    // Exemplo simples: getText() retorna a string correspondente
    // do valor guardado. Você pode usar std::visit:
    std::string Value::getText()
    {
        // reseta o stringstream
        sb.str("");
        sb.clear();

        // Usa std::visit p/ converter "value" num std::string
        std::visit([this](auto &&arg)
                   {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::shared_ptr<Function>>) {
            // Se Function tiver um método getText():
            sb << arg->getFunctionName();
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            sb << arg;
        }
        else if constexpr (std::is_same_v<T, int>) {
            sb << arg; // int -> "123"
        }
        else if constexpr (std::is_same_v<T, float>) {
            sb << arg; // float -> "1.230000"
        }
        else if constexpr (std::is_same_v<T, double>) {
            sb << arg; // double -> "3.140000"
        }
        else if constexpr (std::is_same_v<T, bool>) {
            sb << (arg ? "true" : "false");
        }
        else {
            throw HLIRException("Type undefined");
        } }, value);

        return sb.str();
    }

    std::shared_ptr<Type> Value::getValueType()
    {
        return valueType;
    }

    Variable::Variable(const std::string &varName, std::shared_ptr<Type> varType)
        : varName(varName), varType(std::move(varType))
    {
    }

    Variable::~Variable() {}

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
        // Exemplo de formatação: "let idade: int"
        // Ajuste conforme sua necessidade
        sb << util::format("let {}:{}", varName, varType->getText());
        return sb.str();
    }

}
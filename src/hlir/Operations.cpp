#include "Hlir.h"

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
        sb << util::format("let {}:{} = {}\n", variable->getVarName(), variable->getVarType()->getText(), value->getText());

        return sb.str();
    }

}
//
// Created by Thiago Rodrigues on 04/03/25.
//
#include "../../headers/Hlir.h"
#include "../../headers/Utils.h"

namespace hlir
{
    Struct::Struct(const std::string &name, const std::vector<std::shared_ptr<Variable>> &variables) :
        name(name), variables(variables)
    {
    }

    std::string Struct::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("struct {} {\n", name);
        for (const auto &variable : variables)
        {
            sb << variable->getText() << "\n";
        }
        sb << "}\n";
        return sb.str();
    }

    std::string Struct::getName()
    {
        return name;
    }

    std::vector<std::shared_ptr<Variable>> Struct::getVariables()
    {
        return variables;
    }

    std::shared_ptr<Variable> Struct::findVarByName(const std::string &varName)
    {
        for (auto &variable : variables)
        {
            if (variable->getVarName() == varName) {
                return variable;
            }
        }

        return nullptr;
    }
} // namespace hlir

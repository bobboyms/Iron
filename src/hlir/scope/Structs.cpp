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
        sb << util::format("struct {} {", name);

        const uint commaCount = variables.size();
        int argIndex = 1;
        for (const auto &variable: variables)
        {
            const bool hasComma = (argIndex < commaCount);

            sb << variable->getText() << "";
            if (hasComma)
            {
                sb << ",";
            }
            argIndex++;
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

    std::pair<int, std::shared_ptr<Variable>> Struct::findVarByName(const std::string &varName)
    {
        int index = 0;
        for (auto &variable: variables)
        {
            if (variable->getVarName() == varName)
            {
                return std::make_pair(index, variable);
            }
            index++;
        }

        return std::make_pair(index, nullptr);
    }

    StructInit::StructInit(const std::shared_ptr<Struct> &struct_) : struct_(struct_)
    {
    }
    
    void StructInit::addAssign(const std::shared_ptr<Assign> &assign)
    {
        this->assigns.push_back(assign);
    }
    
    std::shared_ptr<Struct> StructInit::getStruct()
    {
        return struct_;
    }
    
    std::vector<std::shared_ptr<Assign>> StructInit::getAssigns()
    {
        return assigns;
    }

    std::string StructInit::getText()
    {
        sb.str("");
        sb.clear();
        sb << struct_->getName()  << " {";
        
        bool first = true;
        for (const auto &assign : assigns)
        {
            if (!first)
            {
                sb << ", ";
            }
            else
            {
                first = false;
            }
            sb << assign->getText();
        }
        
        sb << "}";
        return sb.str();
    }
} // namespace hlir

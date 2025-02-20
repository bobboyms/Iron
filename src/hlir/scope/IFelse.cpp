//
// Created by Thiago Rodrigues on 18/02/25.
//
#include "../../headers/Hlir.h"


namespace hlir
{
    Conditional::Conditional()
    {
    }
    Conditional::~Conditional()
    {
    }

    std::shared_ptr<Conditional> Conditional::set(const std::shared_ptr<Variable> &variable)

    {
        if (!variable)
        {
            throw iron::LLVMException("Conditional::set. Null variable pointer");
        }


        if (variable->getVarType()->getType() != tokenMap::TYPE_BOOLEAN)
        {
            throw iron::LLVMException("Conditional::set. Variable is not a boolean");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        this->variable = variable;
        this->variable->setParent(parentPtr);

        auto ptr = std::dynamic_pointer_cast<Conditional>(parentPtr);
        if (!ptr)
        {
            throw HLIRException("Failed to cast Parent to Function.");
        }

        return ptr;

    }

    std::string Conditional::getTrueLabel()
    {
        return trueLabel;
    }
    std::string Conditional::getFalseLabel()
    {
        return falseLabel;
    }
    void Conditional::setTrueLabel(const std::string &label)
    {
        if (label.empty())
        {
            throw iron::LLVMException("Conditional::setTrueLabel. label can't be empty");
        }
        trueLabel = label;
    }
    void Conditional::setFalseLabel(const std::string &label)
    {
        if (label.empty())
        {
            throw iron::LLVMException("Conditional::setTrueLabel. label can't be empty");
        }
        falseLabel = label;
    }

    std::string Conditional::getText()
    {
        //conditional var_3 %then, %ifcont
        sb.str("");
        sb.clear();
        sb << util::format("cond {} {}, {}", variable->getVarName(), trueLabel, falseLabel);
        return sb.str();
    }

    Block::Block()
    {
    }
    Block::~Block()
    {
    }
    std::shared_ptr<Block> Block::set(const std::string& label)
    {
        if (label.empty())
        {
            throw iron::LLVMException("Block::set. label can't be empty");
        }

        this->label = label;


        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        // this->variable = variable;
        // this->variable->setParent(parentPtr);

        auto ptr = std::dynamic_pointer_cast<Block>(parentPtr);
        if (!ptr)
        {
            throw HLIRException("Failed to cast Parent to Function.");
        }

        return ptr;
    }
    std::string Block::getLabel()
    {
        return label;
    }

    std::string Block::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("block {}:", label);
        return sb.str();
    }
} // namespace hlir

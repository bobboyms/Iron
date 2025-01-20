#include "../headers/Hlir.h"

namespace hlir
{
    bool verifyType(int type)
    {
        switch (type)
        {

        case tokenMap::TYPE_INT:
        case tokenMap::TYPE_FLOAT:
        case tokenMap::TYPE_CHAR:
        case tokenMap::TYPE_STRING:
        case tokenMap::TYPE_BOOLEAN:
        case tokenMap::TYPE_DOUBLE:
        case tokenMap::FUNCTION:
        case tokenMap::FUNCTION_PTR:
        case tokenMap::VOID:
            return true;
            break;

        default:
            throw HLIRException(util::format("Type::verifyType: DataType error: type not allowed -> {}", tokenMap::getTokenText(type)));
        }
    }

    Type::Type() {}

    Type::Type(int type) : type(type)
    {
        if (verifyType(type))
        {
            this->type = type;
        }
    }

    void Type::set(int type)
    {
        if (verifyType(type))
        {
            this->type = type;
        }
    }

    Type::~Type()
    {
    }

    int Type::getType()
    {
        return type;
    }

    std::string Type::getText()
    {
        sb.str("");
        sb.clear();

        sb << tokenMap::getTokenText(type);
        return sb.str();
    }

}
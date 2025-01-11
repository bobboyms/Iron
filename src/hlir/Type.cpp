#include "Hlir.h"

namespace hlir
{
    Type::Type(int type) : type(type)
    {

        switch (type)
        {

        case TYPE_INT:
        case TYPE_FLOAT:
        case TYPE_CHAR:
        case TYPE_STRING:
        case TYPE_BOOLEAN:
        case TYPE_DOUBLE:
        case FUNCTION:
        case FUNCTION_PTR:
            this->type = type; // se for um dos permitidos, atribui
            break;

        default:
            throw HLIRException(util::format("DataType error: type not allowed -> {}", getTokenText(type)));
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
        sb << getTokenText(type);
        return sb.str();
    }

}
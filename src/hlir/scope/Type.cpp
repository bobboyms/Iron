#include "../../headers/Hlir.h"
#include "../../headers/Utils.h"

namespace hlir
{
    bool verifyType(const int type)
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
            case tokenMap::PTR_TYPE_INT:
            case tokenMap::PTR_TYPE_FLOAT:
            case tokenMap::PTR_TYPE_CHAR:
            case tokenMap::PTR_TYPE_BOOLEAN:
            case tokenMap::PTR_TYPE_DOUBLE:
            case tokenMap::OR:
            case tokenMap::AND:
            case tokenMap::EQEQ:
            case tokenMap::NEQ:
            case tokenMap::LT:
            case tokenMap::LTE:
            case tokenMap::GT:
            case tokenMap::GTE:
            case tokenMap::VOID:
                return true;

            default:
                throw HLIRException(util::format("Type::verifyType: DataType error: type not allowed -> {}",
                                                 tokenMap::getTokenText(type)));
        }
    }

    Type::Type() = default;

    Type::Type(const int type) : type(type)
    {
        verifyType(type);
        this->type = type;
    }

    void Type::set(const int type)
    {
        verifyType(type);
        this->type = type;
    }

    Type::~Type() = default;

    void Signature::addArg(const std::shared_ptr<Arg> &arg)
    {
        if (!arg)
        {
            throw HLIRException("Signature::addArg. Arg is nullptr");
        }
        args.push_back(arg);
    }

    std::string Signature::getText()
    {
        throw std::runtime_error("Signature::getText() not implemented");
    }

    std::shared_ptr<Arg> Signature::findArgByName(const std::string &argName)
    {
        throw std::runtime_error("Signature::findArgByName not implemented");
    }

    std::vector<std::shared_ptr<Arg>> Signature::getArgs()
    {
        return args;
    }

    Signature::Signature(const std::shared_ptr<Type> &returnType) : returnType(returnType)
    {
        if (!returnType)
        {
            throw HLIRException("Signature::Signature. returnType is null");
        }
    }
    Signature::~Signature()
    {
    }

    std::shared_ptr<Type> Signature::getReturnType()
    {
        return returnType;
    }

    int Type::getType() const
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

} // namespace hlir

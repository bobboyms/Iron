#include "../../headers/Hlir.h"
#include "../../headers/Utils.h"
#include <unordered_set>

namespace hlir
{
    /**
     * @brief Validates if a type value is allowed in the system
     * 
     * @param type Integer representation of the type to validate
     * @return true If the type is valid
     * @throws HLIRException If the type is not among the allowed types
     */
    bool verifyType(const int type)
    {
        static const std::unordered_set<int> validTypes = {
            tokenMap::TYPE_INT,
            tokenMap::TYPE_FLOAT,
            tokenMap::TYPE_CHAR,
            tokenMap::TYPE_STRING,
            tokenMap::TYPE_BOOLEAN,
            tokenMap::TYPE_DOUBLE,
            tokenMap::FUNCTION,
            tokenMap::FUNCTION_PTR,
            tokenMap::PTR_TYPE_INT,
            tokenMap::PTR_TYPE_FLOAT,
            tokenMap::PTR_TYPE_CHAR,
            tokenMap::PTR_TYPE_BOOLEAN,
            tokenMap::PTR_TYPE_DOUBLE,
            tokenMap::STRUCT,
            tokenMap::OR,
            tokenMap::AND,
            tokenMap::EQEQ,
            tokenMap::NEQ,
            tokenMap::LT,
            tokenMap::LTE,
            tokenMap::GT,
            tokenMap::GTE,
            tokenMap::VOID,

        };
        
        if (validTypes.find(type) != validTypes.end()) {
            return true;
        }
        
        throw HLIRException(util::format("Type::verifyType: DataType error: type not allowed -> {}",
                                        tokenMap::getTokenText(type)));
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

    /**
     * @brief Finds an argument by name
     * 
     * @param argName Name of the argument to find
     * @return std::shared_ptr<Arg> The found argument or nullptr if not found
     * @throws std::runtime_error This method is not implemented in the base class
     */
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

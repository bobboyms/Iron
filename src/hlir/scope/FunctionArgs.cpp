#include "../../headers/Hlir.h"

namespace hlir
{

    FunctionArgs::FunctionArgs() = default;

    FunctionArgs::FunctionArgs(const std::shared_ptr<Signature> &signature)
    {
        for (const auto arg: signature->getArgs())
        {
            addArg(arg);
        }
    }

    FunctionArgs::~FunctionArgs() = default;

    void FunctionArgs::addArg(const std::shared_ptr<Arg> &arg)
    {
        if (!arg)
        {
            throw HLIRException("Attempted to add a null argument to FunctionArgs.");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        arg->setParent(parentPtr);
        args.push_back(arg);
    }

    std::shared_ptr<Arg> FunctionArgs::findArgByName(const std::string &argName) const
    {
        for (auto arg: args)
        {
            if (arg->name == argName)
            {
                return arg;
            }
        }

        return nullptr;
    }
    std::vector<std::shared_ptr<Arg>> FunctionArgs::getArgs()
    {
        return args;
    }

    std::string FunctionArgs::getText()
    {
        sb.str("");
        sb.clear();

        const uint commaCount = args.size();
        int argIndex = 1;
        for (const auto &arg: args)
        {
            if (!arg || !arg->type)
            {
                throw HLIRException("Null argument or type encountered in FunctionArgs.");
            }

            const bool hasComma = (argIndex < commaCount);
            if (arg->signature)
            {
                sb << util::format("{}:fn{}", arg->name, Utilities::generateTextFromSignature(arg->signature));
            }
            else
            {
                sb << util::format("{}:{}", arg->name, arg->type->getText());
            }

            if (hasComma)
            {
                sb << ",";
            }

            argIndex++;
        }

        if (const auto function = std::dynamic_pointer_cast<Function>(getParent()))
        {
            if (function->isExternal() and function->isVariedArguments())
            {
                sb << ", ...";
            }
        }
        else
        {
            throw std::runtime_error("FunctionArgs::getArgs is not a function.");
        }

        return sb.str();
    }
} // namespace hlir

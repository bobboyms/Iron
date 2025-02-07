#include "../headers/Hlir.h"

namespace hlir
{
    FunctionArgs::FunctionArgs() = default;

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
            sb << util::format("{}:{}", arg->name, arg->type->getText());
            if (hasComma)
            {
                sb << ",";
            }

            argIndex++;
        }

        return sb.str();
    }
} // namespace hlir

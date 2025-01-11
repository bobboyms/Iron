#include "Hlir.h"

namespace hlir
{
    FunctionArgs::FunctionArgs()
    {
    }

    FunctionArgs::FunctionArgs(std::vector<std::shared_ptr<Arg>> args) : args(args)
    {
    }

    FunctionArgs::~FunctionArgs() {}

    void FunctionArgs::addArg(std::shared_ptr<Arg> arg)
    {
        args.push_back(arg);
    }

    std::string FunctionArgs::getText()
    {
        int commaCount = args.size();
        int argIndex = 1;
        for (auto arg : args)
        {
            bool hasComma = (argIndex < commaCount);
            sb << util::format("{}:{}", arg->name, arg->type->getText());
            if (hasComma)
            {
                sb << ",";
            }

            argIndex++;
        }

        return sb.str();
    }

}
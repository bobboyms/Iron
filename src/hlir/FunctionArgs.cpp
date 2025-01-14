#include "../headers/Hlir.h"

namespace hlir
{
    FunctionArgs::FunctionArgs()
    {
    }

    FunctionArgs::~FunctionArgs() {}

    void FunctionArgs::addArg(std::shared_ptr<Arg> arg)
    {
        if (!arg)
        {
            throw HLIRException("Attempted to add a null argument to FunctionArgs.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        arg->setParent(parentPtr);
        args.push_back(arg);
    }

    std::string FunctionArgs::getText()
    {
        sb.str("");
        sb.clear();

        int commaCount = args.size();
        int argIndex = 1;
        for (const auto &arg : args)
        {
            if (!arg || !arg->type)
            {
                throw HLIRException("Null argument or type encountered in FunctionArgs.");
            }

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

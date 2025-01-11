#include "Hlir.h"

namespace hlir
{
    Function::Function(std::string functionName, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType)
        : functionName(functionName), functionArgs(functionArgs), functionReturnType(functionReturnType)
    {
    }

    Function::~Function() {}

    std::string Function::getFunctionName()
    {
        return functionName;
    }

    std::string Function::getText()
    {
        sb << util::format("fn {}({}):{}", functionName, functionArgs->getText(), functionReturnType->getText());
        return sb.str();
    }

    // Function Call

    FunctionCallArgs::FunctionCallArgs(std::vector<std::shared_ptr<FunctionCallArg>> callArgs)
        : callArgs(std::move(callArgs))
    {
    }

    FunctionCallArgs::FunctionCallArgs()
    {
        // pode estar vazio, mas precisa existir
    }

    FunctionCallArgs::~FunctionCallArgs()
    {
        // se não precisa fazer nada, pode deixar vazio
    }

    std::string FunctionCallArgs::getText()
    {

        int commaCount = callArgs.size();
        int argIndex = 1;
        for (auto arg : callArgs)
        {
            bool hasComma = (argIndex < commaCount);
            sb << util::format("{}:{}", arg->argument, arg->value->getText());
            if (hasComma)
            {
                sb << ",";
            }

            argIndex++;
        }

        return sb.str();
    }

    void FunctionCallArgs::addCallArg(std::shared_ptr<FunctionCallArg> callArg)
    {
        callArgs.push_back(callArg);
    }

}
//
// Created by Thiago Rodrigues on 02/03/25.
//
#include "../../headers/Hlir.h"

namespace hlir
{
    std::string Utilities::generateTextFromSignature(const std::shared_ptr<Signature> &signature)
    {
        std::stringstream sb;

        const uint commaCount = signature->getArgs().size();
        int argIndex = 1;
        sb << "(";
        for (const auto &arg: signature->getArgs())
        {
            const bool hasComma = (argIndex < commaCount);
            if (arg->type->getType() == tokenMap::FUNCTION)
            {
                sb << generateTextFromSignature(arg->signature);
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

        sb << "):";
        sb << signature->getReturnType()->getText();


        return sb.str();
    }


} // namespace hlir

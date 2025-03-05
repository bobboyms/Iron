//
// Created by Thiago Rodrigues on 04/03/25.
//
#include <tuple>
#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"

namespace hlir
{

    void HLIRGenerator::ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var)
    {

        if (F->findVarCurrentScopeAndArg(var->getVarName()))
        {
            return;
        }

        if (!F->findVarCurrentScopeAndArg(var->getVarName()))
        {
            const auto functionArgs = F->getFunctionArgs();
            const auto newArg = std::make_shared<Arg>()->set(var->getVarName(), var->getVarType(), var->getSignature());
            functionArgs->addArg(newArg);
        }

        if (const auto parentF = F->getParentFunction())
        {
            ensureVariableCaptured(parentF, var);
        }
    }

    int HLIRGenerator::defineRealType(const std::string &strValue)
    {
        int realType;
        if (const auto definedType = tokenMap::determineType(strValue); definedType == tokenMap::REAL_NUMBER)
        {
            realType = tokenMap::determineFloatType(strValue);
        }
        else
        {
            realType = definedType;
        }

        return realType;
    }

    std::shared_ptr<Assign> HLIRGenerator::generateAssignFromDataFormat(const std::shared_ptr<Variable> &variable,
                                                                        const std::string &literalValue)
    {
        const auto value =
                std::make_shared<Value>()->set(literalValue, std::make_shared<Type>(variable->getVarType()->getType()));
        return std::make_shared<Assign>()->set(variable, value);
    }

    std::shared_ptr<Function> HLIRGenerator::getFunctionValue(const std::shared_ptr<Function> &currentFunction,
                                                              const std::string &varName)
    {

        auto statement = currentFunction->getCurrentLocalScope();

        while (statement)
        {

            // 1. Tenta achar como variável local
            if (const auto value = statement->getValueFromVariable(varName))
            {
                // Se subimos algum nível, marque a variável como estando em outro escopo
                const auto data = value->getValue();
                if (const auto funcPtr = std::get_if<std::shared_ptr<Function>>(&data))
                {
                    if (funcPtr)
                    {
                        return *funcPtr;
                    }
                }
            }

            // 3. Se não achou nem variável local, nem argumento,
            //    subimos para o próximo escopo (função pai)
            const auto parentFunction = currentFunction->getParentFunction();
            if (!parentFunction)
            {
                break;
            }

            statement = parentFunction->getCurrentLocalScope();
        }

        const auto variable = currentFunction->findVarAllScopesAndArg(varName);
        if (!variable)
        {
            throw HLIRException(
                    util::format("HLIRGenerator::getFunctionValue. Undefined Function: '{}' in expression", varName));
        }

        if (variable->getVarType()->getType() != tokenMap::FUNCTION)
        {
            throw HLIRException(
                    util::format("HLIRGenerator::getFunctionValue. Undefined Function: '{}' in expression", varName));
        }

        if (!variable->getSignature())
        {
            throw HLIRException(
                    util::format("HLIRGenerator::getFunctionValue. Undefined Function: '{}' in expression", varName));
        }

        const auto functionArgs = std::make_shared<FunctionArgs>();

        for (const auto arg: variable->getSignature()->getArgs())
        {
            functionArgs->addArg(arg);
        }

        const auto function = std::make_shared<Function>()->set(variable->getVarName(), functionArgs,
                                                                variable->getSignature()->getReturnType());
        function->changeToArgFunction();
        return function;
    }

    std::shared_ptr<Struct> HLIRGenerator::getStruct(const std::shared_ptr<Function> &currentFunction,
                                                              const std::string &varName)
    {

        auto statement = currentFunction->getCurrentLocalScope();

        while (statement)
        {

            // 1. Tenta achar como variável local
            if (const auto value = statement->getValueFromVariable(varName))
            {
                // Se subimos algum nível, marque a variável como estando em outro escopo
                const auto data = value->getValue();
                if (const auto structPtr = std::get_if<std::shared_ptr<Struct>>(&data))
                {
                    if (structPtr)
                    {
                        return *structPtr;
                    }
                }
            }

            // 3. Se não achou nem variável local, nem argumento,
            //    subimos para o próximo escopo (função pai)
            const auto parentFunction = currentFunction->getParentFunction();
            if (!parentFunction)
            {
                break;
            }

            statement = parentFunction->getCurrentLocalScope();
        }

        return nullptr;
    }

} // namespace hlir

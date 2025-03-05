//
// Created by Thiago Rodrigues on 04/03/25.
//
// This file's contents have been moved to HLIRGenerator.cpp to fix linker issues
// The file is kept to maintain the project structure
#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"

namespace hlir
{
    void HLIRGenerator::visitStructStatement(IronParser::StructStatementContext *ctx) const
    {
        const auto strutName = ctx->structName->getText();
        std::vector<std::shared_ptr<Variable>> structVariables{};

        for (const auto &body: ctx->structBody())
        {
            const auto varName = body->varName->getText();
            const auto varTypeStr = body->varTypes()->getText();

            const auto type = std::make_shared<Type>(tokenMap::getTokenType(varTypeStr));
            const auto variable = std::make_shared<Variable>()->set(varName, type);
            structVariables.push_back(variable);
        }

        const auto newStruct = std::make_shared<Struct>(strutName, structVariables);
        context->addStruct(newStruct);
    }

    void HLIRGenerator::visitStructInit(IronParser::StructInitContext *ctx,
                                        const std::shared_ptr<Function> &currentFunction)
    {
        const auto statement = currentFunction->getCurrentLocalScope();
        if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            const auto varName = varDeclaration->varName->getText();
            const auto variable = currentFunction->findVarAllScopesAndArg(varName);
            if (!variable)
            {
                throw HLIRException(util::format(
                        "HLIRGenerator::visitStructInit. Undefined Variable: '{}' in expression", varName));
            }

            std::vector<std::shared_ptr<Assign>> assigns{};
            const auto struct_ = getStruct(currentFunction, varName);
            const auto structInit = std::make_shared<StructInit>(struct_);
            for (const auto &body: ctx->structInitBody())
            {
                if (!struct_)
                {
                    throw HLIRException(util::format(
                            "HLIRGenerator::visitStructInit. Undefined Struct: '{}' in expression", varName));
                }

                const auto fieldName = body->varName->getText();
                if (const auto field = struct_->findVarByName(fieldName); !field)
                {
                    throw HLIRException(util::format(
                            "HLIRGenerator::visitStructInit. Undefined Field: '{}' in expression", fieldName));
                }

                if (body->dataFormat())
                {
                    const auto value = body->dataFormat()->getText();

                    if (const auto realType = defineRealType(value); realType == tokenMap::TYPE_STRING)
                    {
                        const auto type = std::make_shared<Type>(tokenMap::TYPE_STRING);
                        const auto anotherVarName = currentFunction->generateVarName();
                        const auto anotherVariable = std::make_shared<Variable>()->set(anotherVarName, type);
                        const auto anotherAssign = generateAssignFromDataFormat(anotherVariable, value);
                        statement->addStatement(anotherAssign);

                        const auto variable = std::make_shared<Variable>()->set(fieldName, type);
                        const auto anotherValue = std::make_shared<Value>()->set(anotherVariable, type);
                        const auto assign = std::make_shared<Assign>()->set(variable, anotherValue);
                        structInit->addAssign(assign);

                    }
                    else
                    {
                        const auto type = std::make_shared<Type>(realType);
                        const auto anotherVarName = currentFunction->generateVarName();
                        const auto anotherVariable = std::make_shared<Variable>()->set(anotherVarName, type);
                        const auto anotherAssign = generateAssignFromDataFormat(anotherVariable, value);
                        statement->addStatement(anotherAssign);

                        const auto variable = std::make_shared<Variable>()->set(fieldName, type);
                        const auto anotherValue = std::make_shared<Value>()->set(anotherVariable, type);
                        const auto assign = std::make_shared<Assign>()->set(variable, anotherValue);
                        structInit->addAssign(assign);
                    }
                }
            }

            const auto value = std::make_shared<Value>()->set(structInit, std::make_shared<Type>(tokenMap::STRUCT));
            statement->addStatement(std::make_shared<Assign>()->set(variable, value));
        }
    }
} // namespace hlir

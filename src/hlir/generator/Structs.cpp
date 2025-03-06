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

            if (body->anotherType)
            {
                const auto anotherTypeName = body->anotherType->getText();
                const auto anotherStruct = context->getStructByName(anotherTypeName);

                const auto type = std::make_shared<Type>(tokenMap::STRUCT, anotherTypeName);
                const auto variable = std::make_shared<Variable>()->set(varName, type);
                structVariables.push_back(variable);
            }
            else
            {
                const auto varTypeStr = body->varTypes()->getText();
                const auto type = std::make_shared<Type>(tokenMap::getTokenType(varTypeStr));
                const auto variable = std::make_shared<Variable>()->set(varName, type);
                structVariables.push_back(variable);
            }
        }

        const auto newStruct = std::make_shared<Struct>(strutName, structVariables);
        context->addStruct(newStruct);
    }

    void HLIRGenerator::visitStructInit(IronParser::StructInitContext *ctx,
                                        const std::shared_ptr<Function> &currentFunction,
                                        const std::shared_ptr<Variable> &variable)
    {

        if (!variable)
        {
            throw HLIRException(util::format("HLIRGenerator::visitStructInit. Undefined Variable: '{}' in expression",
                                             ctx->structName->getText()));
        }

        const auto statement = currentFunction->getCurrentLocalScope();

        std::vector<std::shared_ptr<Assign>> assigns{};
        const auto struct_ = getStruct(currentFunction, variable->getVarName());
        const auto structInit = std::make_shared<StructInit>(struct_);
        for (const auto &body: ctx->structInitBody())
        {
            if (!struct_)
            {
                throw HLIRException(util::format("HLIRGenerator::visitStructInit. Undefined Struct: '{}' in expression",
                                                 variable->getVarName()));
            }

            const auto fieldName = body->varName->getText();
            const auto field = struct_->findVarByName(fieldName);
            if (!field)
            {
                throw HLIRException(
                        util::format("HLIRGenerator::visitStructInit. Undefined Field: '{}' in expression", fieldName));
            }

            if (body->structInit())
            {
                const auto anotherVarName = currentFunction->generateVarName();
                const auto anotherVariable = std::make_shared<Variable>()->set(anotherVarName, field->getVarType());
                const auto assignAnother = std::make_shared<Assign>()->set(
                        anotherVariable,
                        std::make_shared<Value>()->set(context->getStructByName(field->getVarType()->getTypeName()),
                                                       std::make_shared<Type>(tokenMap::STRUCT)));
                statement->addStatement(assignAnother);

                visitStructInit(body->structInit(), currentFunction, anotherVariable);

                const auto variable = std::make_shared<Variable>()->set(fieldName, field->getVarType());
                const auto anotherValue = std::make_shared<Value>()->set(anotherVariable, field->getVarType());
                const auto assign = std::make_shared<Assign>()->set(variable, anotherValue);
                structInit->addAssign(assign);
            }
            else if (body->dataFormat())
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


    void HLIRGenerator::createStructAndField(std::vector<antlr4::tree::TerminalNode *> identifiers,
                                        const std::shared_ptr<Function> &currentFunction, const std::string &value)
    {
        const auto statement = currentFunction->getCurrentLocalScope();
        // We must have at least two identifiers: [struct, field] or [struct, field, nested_field, ...]
        if (identifiers.size() < 2)
        {
            throw std::invalid_argument(
                    util::format("Invalid struct field access: expected at least a struct name and field name.",
                                 color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW)));
        }

        // Get the base struct name and prepare to traverse the hierarchy
        std::string baseName = identifiers[0]->getText();
        std::string baseField = identifiers[1]->getText();
        auto baseVariable = currentFunction->findVarAllScopesAndArg(baseName);

        // Look up the initial struct in the scope
        if (!baseVariable)
        {
            throw HLIRException(util::format("Invalid struct field access: '{}' is not a struct.", baseName));
        }

        const auto baseStruct = getStruct(currentFunction, baseName);

        // For each field in the access chain, traversing the struct hierarchy
        std::shared_ptr<Variable> lastVariable;
        std::shared_ptr<Struct> lastStruct = baseStruct;
        std::string accessPath = baseName;

        // Start from index 1 (first field after struct name)
        for (size_t i = 1; i < identifiers.size(); i++)
        {
            const std::string fieldName = identifiers[i]->getText();
            accessPath += "." + fieldName;

            // Get the field from the current struct
            printf("fieldName %s\n", fieldName.c_str());
            const auto field = lastStruct->findVarByName(fieldName);
            if (!field)
            {
                throw HLIRException(util::format("Invalid struct field access: '{}' is not a field.", accessPath));
            }

            if (field->getVarType()->getType() == tokenMap::STRUCT)
            {

                const auto varName = currentFunction->generateVarName();
                const auto variable =
                        std::make_shared<Variable>()->set(varName, std::make_shared<Type>(tokenMap::STRUCT));
                statement->addDeclaredVariable(variable);
                const auto assign = std::make_shared<Assign>()->set(
                        variable, std::make_shared<Value>()->set(context->getStructByName(field->getVarType()->getTypeName()),
                                                                 std::make_shared<Type>(tokenMap::STRUCT)));
                statement->addStatement(assign);

                lastVariable = variable;
                lastStruct = getStruct(currentFunction, varName);
            } else
            {
                const auto structInit = std::make_shared<StructInit>(lastStruct);
                const auto varName = currentFunction->generateVarName();
                const auto variable = std::make_shared<Variable>()->set(varName, field->getVarType());
                const auto assignVariable = std::make_shared<Assign>()->set(variable, std::make_shared<Value>()->set(value, field->getVarType()));

                const auto assignField = std::make_shared<Assign>()->set(field, std::make_shared<Value>()->set(variable, field->getVarType()));
                structInit->addAssign(assignField);
                const auto assignLastVariable = std::make_shared<Assign>()->set(lastVariable, std::make_shared<Value>()->set(structInit, lastVariable->getVarType()));
                statement->addStatement(assignVariable);
                statement->addStatement(assignLastVariable);
                // lastStruct = getStruct(currentFunction, field->getVarName());
                // structInit->addAssign(std::make_shared<Assign>()->set(field, std::make_shared<Value>()->set(lastStruct, field->getVarType())));
            }

        }

        const auto structInit = std::make_shared<StructInit>(baseStruct);
        const auto varName = currentFunction->generateVarName();
        //const auto variable = std::make_shared<Variable>()->set(varName, lastVariable->getVarType());

        const auto lastBaseField = baseStruct->findVarByName(baseField);

        structInit->addAssign(std::make_shared<Assign>()->set(lastBaseField,
            std::make_shared<Value>()->set(lastVariable,lastVariable->getVarType())));


        const auto assignVariable = std::make_shared<Assign>()->set(
            baseVariable, std::make_shared<Value>()->set(
                structInit, lastBaseField->getVarType()));

        statement->addStatement(assignVariable);


        // return std::make_pair(lastStruct, field);
    }
} // namespace hlir

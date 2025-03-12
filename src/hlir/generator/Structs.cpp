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
            const auto [_, field] = struct_->findVarByName(fieldName);
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


    void HLIRGenerator::createStructAndField(IronParser::VariableQualifiedNameContext* identifiers,
                                        const std::shared_ptr<Function> &currentFunction, const std::string &value)
    {
        const auto statement = currentFunction->getCurrentLocalScope();

        // We must have at least two identifiers: [struct, field] or [struct, field, nested_field, ...]
        const auto restSize = identifiers->rest.size();
        if (restSize < 1)
        {
            throw std::invalid_argument(
                    util::format("Invalid struct field access: expected at least a struct name and field name.",
                                 color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW)));
        }

        // Get the base struct name and prepare to traverse the hierarchy
        const auto baseName = identifiers->base->getText();
        const auto rest = identifiers->rest;
        auto baseVariable = currentFunction->findVarAllScopesAndArg(baseName);

        // Look up the initial struct in the scope
        if (!baseVariable)
        {
            printf("baseName: %s\n", baseName.c_str());
            throw HLIRException(util::format("Invalid struct field access: '{}' is not defined.", baseName));
        }

        if (baseVariable->getVarType()->getType() != tokenMap::STRUCT)
        {
            throw HLIRException(util::format("Invalid struct field access: '{}' is not a struct.", baseName));
        }

        const auto baseStruct = getStruct(currentFunction, baseVariable->getVarName());
        if (!baseStruct)
        {
            throw HLIRException(util::format("Invalid struct field access: struct type '{}' not found.", 
                                            baseVariable->getVarType()->getTypeName()));
        }
        
        // First create the value variable (for the string or whatever is assigned)
        const auto valueVarName = currentFunction->generateVarName();
        std::shared_ptr<Type> valueType;
        
        // For the case like "Rua 25 de março" - determine the type from the value
        if (value.front() == '"' && value.back() == '"') {
            valueType = std::make_shared<Type>(tokenMap::TYPE_STRING);
        } else {
            valueType = std::make_shared<Type>(defineRealType(value));
        }
        
        // Create the value variable and its assignment
        const auto valueVar = std::make_shared<Variable>()->set(valueVarName, valueType);
        statement->addDeclaredVariable(valueVar);

        const auto valueAssign = std::make_shared<Assign>()->set(
            valueVar, 
            std::make_shared<Value>()->set(value, valueType)
        );
        statement->addStatement(valueAssign);
        
        // Maps to store struct info for each level in the chain
        std::vector<std::string> fieldNames;
        std::vector<std::shared_ptr<Struct>> structTypes;
        std::vector<std::shared_ptr<Variable>> structVars;
        
        // Build the access path
        structTypes.push_back(baseStruct);
        
        // First, verify the access path and build the field name hierarchy
        std::shared_ptr<Struct> currentStruct = baseStruct;
        for (size_t i = 0; i < restSize; i++) {
            std::string fieldName = rest[i]->getText();
            fieldNames.push_back(fieldName);
            
            // Find the field in the current struct
            auto [_, field] = currentStruct->findVarByName(fieldName);
            if (!field) {
                throw HLIRException(util::format("Invalid struct field access: '{}' is not a field of '{}'.", 
                                                fieldName, currentStruct->getName()));
            }
            
            // If not at the last field, prepare for the next nested struct
            if (i < rest.size()) {
                if (field->getVarType()->getType() != tokenMap::STRUCT) {
                    throw HLIRException(util::format("Invalid struct field access: '{}' is not a struct field.", fieldName));
                }
                
                // Get the next struct type
                std::string structTypeName = field->getVarType()->getTypeName();
                auto nextStruct = context->getStructByName(structTypeName);
                if (!nextStruct) {
                    throw HLIRException(util::format("Invalid struct field access: struct type '{}' not found.", structTypeName));
                }
                
                currentStruct = nextStruct;
                structTypes.push_back(nextStruct);
            }
        }
        
        // Now create struct variables for each level (except the base which already exists)
        // Start with the deepest struct and work back to the base
        std::shared_ptr<Variable> lastVar = valueVar;
        std::shared_ptr<Type> lastType = valueType;
        
        for (int i = fieldNames.size() - 1; i >= 0; i--) {
            // Create a variable to hold the struct at this level
            std::string structVarName = currentFunction->generateVarName();
            auto structType = std::make_shared<Type>(tokenMap::STRUCT, structTypes[i]->getName());
            auto structVar = std::make_shared<Variable>()->set(structVarName, structType);
            const auto structDeclarationAssign = std::make_shared<Assign>()->set(structVar,
                std::make_shared<Value>()->set(context->getStructByName(structType->getTypeName()), structType));
            statement->addStatement(structDeclarationAssign);

            // Create a struct initialization 
            auto structInit = std::make_shared<StructInit>(structTypes[i]);
            
            // Find the field we're setting at this level
            auto [_, field] = structTypes[i]->findVarByName(fieldNames[i]);
            
            // Create the assignment for this field
            auto fieldAssign = std::make_shared<Assign>()->set(
                field,
                std::make_shared<Value>()->set(lastVar, lastType)
            );
            structInit->addAssign(fieldAssign);
            
            // Assign the struct init to our struct var
            auto structAssign = std::make_shared<Assign>()->set(
                structVar,
                std::make_shared<Value>()->set(structInit, structType)
            );
            statement->addStatement(structAssign);
            
            // Save this var for the next level up
            lastVar = structVar;
            lastType = structType;
        }
        
        // Finally, assign the top-level struct to the base variable
        auto baseAssign = std::make_shared<Assign>()->set(
            baseVariable,
            std::make_shared<Value>()->set(lastVar, lastType)
        );
        statement->addStatement(baseAssign);
    }
} // namespace hlir

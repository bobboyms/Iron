//
// Created by Thiago Rodrigues on 03/03/25.
//

#include "../headers/Analyser.h"
#include "../headers/Files.h"
#include "../headers/SemanticAnalysis.h"

namespace iron
{
    void SemanticAnalysis::visitStructDeclaration(IronParser::StructStatementContext *ctx) const
    {
        const auto structName = ctx->IDENTIFIER()->getText();
        const auto structStmt = std::make_shared<scope::StructStemt>(structName);
        scopeManager->addStructDeclaration(structStmt);
    }

    void SemanticAnalysis::visitStructStatement(IronParser::StructStatementContext *ctx) const
    {
        std::vector<std::shared_ptr<scope::Variable>> variables{};
        const auto structName = ctx->IDENTIFIER()->getText();
        const auto structref = scopeManager->getStructDeclarationByName(structName);
        if (!structref)
        {
            throw std::runtime_error("Struct not found");
        }

        structref->setVariables(variables);
        for (const auto &structBody: ctx->structBody())
        {
            visitStructBody(structBody, variables);
        }
    }

    void SemanticAnalysis::visitStructBody(IronParser::StructBodyContext *ctx,
                                           std::vector<std::shared_ptr<scope::Variable>> &variables)
    {
        const auto varName =  ctx->varName->getText();
        const auto varTypeStr = ctx->varTypes()->getText();
        const auto variable = std::make_shared<scope::Variable>(varName,
            tokenMap::getTokenType(varTypeStr), ctx->MUT() != nullptr);
        variables.push_back(variable);
    }

    void SemanticAnalysis::visitStructInit(IronParser::StructInitContext *ctx)
    {
        printf("Struct init\n");
    }
    void SemanticAnalysis::visitStructInitBody(IronParser::StructInitBodyContext *ctx)
    {
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);
        
        // Get field name
        const std::string fieldName = ctx->varName->getText();
        const auto currentFunction = getCurrentFunction();
        
        // Check the struct definition to validate the field type
        if (ctx->dataFormat())
        {
            // Handle literal values (numbers, strings, booleans)
            const std::string value = ctx->dataFormat()->getText();
            int valueType = determineValueType(value);
            
            // We would check if the field exists in the struct and if the type matches
            // This would require access to the struct definition
            // For now, just display an informational message
            printf("Assigning %s (type: %s) to struct field %s\n", 
                value.c_str(), 
                tokenMap::getTokenText(valueType).c_str(), 
                fieldName.c_str());
        }
        else if (ctx->anotherVarName)
        {
            // Handle variable assignment
            const std::string varName = ctx->anotherVarName->getText();
            auto variable = verifyVariableExists(varName, line, col, 
                "Hint: The variable must be declared before using it in a struct initialization.");
            
            // Check if the variable type matches the struct field type
            // This would require access to the struct definition
            printf("Assigning variable %s (type: %s) to struct field %s\n", 
                varName.c_str(), 
                tokenMap::getTokenText(variable->type).c_str(), 
                fieldName.c_str());
        }
        else if (ctx->functionCall())
        {
            // Handle function call
            const std::string functionName = ctx->functionCall()->functionName->getText();
            auto function = verifyFunctionExists(functionName, line, col);
            
            // Check if the function return type matches the struct field type
            visitFunctionCall(ctx->functionCall());
            
            printf("Assigning result of function %s (return type: %s) to struct field %s\n", 
                functionName.c_str(), 
                tokenMap::getTokenText(function->getReturnType()).c_str(), 
                fieldName.c_str());
        }
        else if (ctx->arrowFunctionInline())
        {
            // Handle arrow function
            auto arrowFunction = visitArrowFunctionInline(ctx->arrowFunctionInline());
            
            // Check if the arrow function type matches the struct field type
            printf("Assigning arrow function (return type: %s) to struct field %s\n", 
                tokenMap::getTokenText(arrowFunction->getReturnType()).c_str(), 
                fieldName.c_str());
        }
    }
} // namespace iron

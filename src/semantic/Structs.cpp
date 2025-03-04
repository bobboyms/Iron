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
        std::vector<std::shared_ptr<scope::Variable>> variables;
        const auto structName = ctx->IDENTIFIER()->getText();
        const auto structref = scopeManager->getStructDeclarationByName(structName);
        if (!structref)
        {
            throw std::runtime_error("Struct not found");
        }

        for (const auto &structBody: ctx->structBody())
        {
            const auto varName = structBody->varName->getText();
            const auto varTypeStr = structBody->varTypes()->getText();
            auto variable = std::make_shared<scope::Variable>(varName, tokenMap::getTokenType(varTypeStr),
                                                              structBody->MUT() != nullptr);
            variables.push_back(variable);
        }

        structref->setVariables(variables);
    }

    void SemanticAnalysis::visitStructInit(IronParser::StructInitContext *ctx)
    {
        for (const auto &bodyCtx: ctx->structInitBody())
        {
            visitStructInitBody(bodyCtx);
        }
    }

    void SemanticAnalysis::visitStructInitBody(IronParser::StructInitBodyContext *ctx)
    {
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        // Get field name
        const auto fieldName = ctx->varName->getText();
        const auto currentFunction = getCurrentFunction();

        // Get the variable and struct type from the parent context
        // IronParser::VarDeclarationContext *varDeclaration = nullptr;
        // std::string varName;
        // std::shared_ptr<scope::Variable> variable;


        if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent->parent))
        {
            const auto varName = varDeclaration->varName->getText();
            const auto variable = getCurrentFunction()->findVarAllScopesAndArg(varName);

            if (!variable)
            {
                throw VariableNotFoundException(
                        util::format("Variable '{}' not found.\n"
                                     "Line: {}, Scope: {}\n\n"
                                     "{}\n"
                                     "{}\n",
                                     color::colorText(varName, color::BOLD_GREEN),
                                     color::colorText(std::to_string(line), color::YELLOW),
                                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                     codeLine, caretLine));
            }


            if (!variable->structStemt)
            {
                throw TypeNotFoundException(util::format(
                        "The variable {} is not of type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(varName, color::BOLD_GREEN), color::colorText("struct", color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                        caretLine));
            }


            if (ctx->dataFormat())
            {
                const auto value = ctx->dataFormat()->getText();
                auto valueType = determineValueType(value);

                // Debug output
                // printf("Struct init for %s, field: %s, value: %s\n", variable->structStemt->name.c_str(),
                //        fieldName.c_str(), value.c_str());

                // Print all variables in the struct for debugging
                // for (const auto &var: variable->structStemt->getVariables())
                // {
                //     printf("Found struct field: %s of type %s\n", var->name.c_str(),
                //            tokenMap::getTokenText(var->type).c_str());
                // }

                const auto field = variable->structStemt->getVarByName(fieldName);
                if (!field)
                {
                    throw VariableNotFoundException(
                            util::format("The field '{}' not found in struct '{}'.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(fieldName, color::BOLD_GREEN),
                                         color::colorText(variable->structStemt->name, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                if (valueType != field->type)
                {
                    throw TypeMismatchException(
                            util::format("The struct field {} type is {} and the value {} type is {}.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n" // Exibe a linha de código
                                         "{}\n", // Exibe a setinha '^'
                                         color::colorText(fieldName, color::BOLD_GREEN),
                                         color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                                         color::colorText(value, color::BOLD_BLUE),
                                         color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }
        }
        else if (ctx->anotherVarName)
        {
            // Handle variable assignment
            const std::string varName = ctx->anotherVarName->getText();
            auto variable = verifyVariableExists(
                    varName, line, col,
                    "Hint: The variable must be declared before using it in a struct initialization.");
        }
        else if (ctx->functionCall())
        {
            // Handle function call
            const std::string functionName = ctx->functionCall()->functionName->getText();
            auto function = verifyFunctionExists(functionName, line, col);

            // Check if the function return type matches the struct field type
            visitFunctionCall(ctx->functionCall());
        }
        else if (ctx->arrowFunctionInline())
        {
            // Handle arrow function
            auto arrowFunction = visitArrowFunctionInline(ctx->arrowFunctionInline());

            // Check if the arrow function type matches the struct field type
        }
    }
} // namespace iron

/**
 * @file HLIRGenerator.cpp
 * @brief Implementation of the High-Level IR Generator for the Iron language
 *
 * This file contains the implementation of the HLIRGenerator class, which is responsible
 * for transforming the parse tree into a high-level intermediate representation.
 */
#include "../../headers/HLIRGenerator.h"
#include <optional>
#include <string_view>
#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/Hlir.h"

namespace hlir
{
    /**
     * @brief Creates a math expression assignment with type checking and casting if needed
     *
     * @param leftVarName The name of the left variable
     * @param leftVarTypeName The type name of the left variable
     * @param rightVar The right variable
     * @param currentFunction The current function context
     * @throws HLIRException If the left variable cannot be found
     */
    void createMathExprAssign(std::string_view leftVarName, std::string_view leftVarTypeName,
                              const std::shared_ptr<Variable> &rightVar,
                              const std::shared_ptr<Function> &currentFunction)
    {
        const auto statement = currentFunction->getCurrentLocalScope();
        if (!statement)
        {
            throw HLIRException("createMathExprAssign: Current scope is null");
        }

        int leftDataTypeType = tokenMap::getTokenType(std::string(leftVarTypeName));
        const auto leftVar = currentFunction->findVarAllScopesAndArg(std::string(leftVarName));
        if (!leftVar)
        {
            throw HLIRException("createMathExprAssign: Left variable not found");
        }

        // Different types require casting
        if (leftDataTypeType != rightVar->getVarType()->getType())
        {
            // Create a temporary variable for the cast result
            const std::string tempVarName = currentFunction->generateVarName();
            auto tempType = std::make_shared<Type>(leftDataTypeType);
            auto tempVariable = std::make_shared<Variable>()->set(tempVarName, tempType);
            statement->addDeclaredVariable(tempVariable);

            // Cast and assign
            const auto cast = std::make_shared<Cast>()->apply(rightVar, tempType);
            auto expr = std::make_shared<Expr>()->set(tempVariable, cast);
            statement->addStatement(expr);

            // Assign the casted value to the left variable
            const auto value = std::make_shared<Value>()->set(tempVariable, tempVariable->getVarType());
            auto assign = std::make_shared<Assign>()->set(leftVar, value);
            statement->addStatement(assign);
        }
        else // Same types, direct assignment
        {
            const auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
            auto assign = std::make_shared<Assign>()->set(leftVar, value);
            statement->addStatement(assign);
        }
    }

    /**
     * @brief Constructs a new HLIRGenerator
     *
     * @param parser The Iron parser containing the parse tree
     * @param context The context for storing generated code
     * @param config The configuration settings
     * @param exportContexts Map of contexts for imported modules
     */
    HLIRGenerator::HLIRGenerator(
            const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context,
            const std::shared_ptr<config::Configuration> &config,
            const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts) :
        parser(parser), context(context), config(config), exportContexts(exportContexts)
    {
    }

    /**
     * @brief Virtual destructor
     */
    HLIRGenerator::~HLIRGenerator() = default;

    /**
     * @brief Process the parse tree and build the HLIR context
     *
     * This method processes imports, external function declarations,
     * and function declarations to build the HLIR context.
     *
     * @return The processed HLIR context
     */
    std::shared_ptr<Context> HLIRGenerator::getContext()
    {
        IronParser::ProgramContext *programContext = parser->program();
        if (!programContext)
        {
            throw HLIRException("Failed to get program context from parser");
        }

        try
        {
            // Process import statements
            for (const auto importStmt: programContext->importStatement())
            {
                visitImportStatement(importStmt);
            }

            // Process external function declarations
            if (programContext->externBlock())
            {
                visitExternBlock(programContext->externBlock());
            }

            // Process function declarations
            for (const auto child: programContext->children)
            {
                if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
                {
                    visitFunctionDeclaration(funcDecl);
                }
                if (const auto structStatement = dynamic_cast<IronParser::StructStatementContext *>(child))
                {
                    visitStructStatement(structStatement);
                }
            }
        }
        catch (const std::exception &e)
        {
            throw HLIRException(util::format("Error processing program: {}", e.what()));
        }

        return context;
    }

    std::pair<bool, bool> HLIRGenerator::visitStatementList(const IronParser::StatementListContext *ctx,
                                                            const std::shared_ptr<Function> &currentFunction,
                                                            const std::shared_ptr<Jump> &endJump)
    {
        bool hasBreak{false};
        bool hasReturn{false};
        const auto statement = currentFunction->getCurrentLocalScope();
        for (const auto child: ctx->children)
        {

            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration, currentFunction);
            }

            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression, currentFunction);
            }

            if (const auto expression = dynamic_cast<IronParser::BoolExprContext *>(child))
            {
                visitBoolExpr(expression, currentFunction);
            }

            if (const auto IfStatement = dynamic_cast<IronParser::IfStatementContext *>(child))
            {
                const auto endLabel = currentFunction->generateLabel("end");
                visitIfStatement(IfStatement, currentFunction, endLabel, endJump);
            }

            if (const auto whileLoop = dynamic_cast<IronParser::WhileStatementContext *>(child))
            {
                visitWhileStatement(whileLoop, currentFunction);
            }
            if (const auto forLoop = dynamic_cast<IronParser::ForStatementContext *>(child))
            {
                visitForStatement(forLoop, currentFunction);
            }
            if (const auto repeatLoop = dynamic_cast<IronParser::RepeatStatementContext *>(child))
            {
                visitRepeatStatement(repeatLoop, currentFunction);
            }

            if (const auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment, currentFunction);
            }

            if (dynamic_cast<IronParser::BreakStatementContext *>(child))
            {
                if (endJump)
                {
                    statement->addStatement(endJump);
                }

                hasBreak = true;
            }

            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                auto call = visitFunctionCall(funcCall, currentFunction);
                statement->addStatement(call);
            }

            if (const auto re_turn = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(re_turn, currentFunction);
                hasReturn = true;
            }
        }

        return std::make_pair(hasBreak, hasReturn);
    }

    void HLIRGenerator::visitVarAssignment(IronParser::VarAssignmentContext *ctx,
                                           const std::shared_ptr<Function> &currentFunction)
    {

        const auto leftVarName = ctx->varName->getText();
        const auto leftVariable = currentFunction->findVarAllScopesAndArg(leftVarName);
        if (!leftVariable)
        {
            throw std::runtime_error("leftVariable name not found");
        }

        if (ctx->expr())
        {
            const auto rightVarName = visitExpr(ctx->expr(), currentFunction);
            const auto rightVar = currentFunction->findVarAllScopesAndArg(rightVarName);
            if (!rightVar)
            {
                throw std::runtime_error("Right var not found");
            }

            createMathExprAssign(leftVarName, tokenMap::getTokenText(leftVariable->getVarType()->getType()), rightVar,
                                 currentFunction);
        }

        if (ctx->dataFormat())
        {
            if (ctx->IDENTIFIER().size() >= 1)
            {
                createStructAndField(ctx->IDENTIFIER(), currentFunction, ctx->dataFormat()->getText());
            }
        }

    }

    void HLIRGenerator::visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                            const std::shared_ptr<Function> &currentFunction)
    {
        const std::string varName = ctx->varName->getText();
        const auto statement = currentFunction->getCurrentLocalScope();

        if (ctx->varTypes())
        {
            const auto variable = std::make_shared<Variable>()->set(
                    varName, std::make_shared<Type>(tokenMap::getTokenType(ctx->varTypes()->getText())));
            statement->addDeclaredVariable(variable);
            variable->changeRealName(currentFunction->generateVarName());
        }
        else
        {
            if (!ctx->anotherType)
            {
                throw std::runtime_error("SemanticAnalysis::visitVarDeclaration. Invalid variable declaration");
            }

            if (const auto anotherType = ctx->anotherType->getText(); context->getStructByName(anotherType))
            {
                const auto anotherStruct = context->getStructByName(anotherType);
                const auto variable =
                        std::make_shared<Variable>()->set(varName, std::make_shared<Type>(tokenMap::STRUCT, anotherType));
                statement->addDeclaredVariable(variable);
                variable->changeRealName(currentFunction->generateVarName());
                const auto assign = std::make_shared<Assign>()->set(
                        variable, std::make_shared<Value>()->set(anotherStruct,
                                                                 std::make_shared<Type>(tokenMap::STRUCT)));
                statement->addStatement(assign);
            }
        }

        // statement->addStatement(std::make_shared<DeclareVariable>(variable));

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment(), currentFunction);
        }

    }

    void HLIRGenerator::visitAssignment(IronParser::AssignmentContext *ctx,
                                        const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        if (ctx->dataFormat())
        {
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                const auto variable = statement->findVarByName(varName);
                const auto assign = generateAssignFromDataFormat(variable, literalValue);
                statement->addStatement(assign);
            }
        }

        if (ctx->varName)
        {

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const auto anotherVarName = ctx->varName->getText();
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();

                const auto variable = statement->findVarByName(varName);
                if (!variable)
                {
                    throw HLIRException("HLIRGenerator::visitAssignment. Variable not found");
                }

                const auto isVariableFunction = variable->getVarType()->getType() == tokenMap::FUNCTION;
                const auto anotherVariable = currentFunction->findVarAllScopesAndArg(anotherVarName);
                if (!anotherVariable && !isVariableFunction)
                {
                    throw HLIRException("HLIRGenerator::visitAssignment. Variable not found");
                }

                if (anotherVariable)
                {
                    if (anotherVariable->isAnotherScope())
                    {
                        ensureVariableCaptured(currentFunction, anotherVariable);
                    }
                }

                if (isVariableFunction)
                {
                    std::shared_ptr<Function> localFunction;
                    if (!anotherVariable)
                    {
                        localFunction = context->getFunctionByName(anotherVarName);
                    }
                    else
                    {
                        localFunction = getFunctionValue(currentFunction, anotherVariable->getVarName());
                    }

                    if (!localFunction)
                    {
                        throw HLIRException("HLIRGenerator::visitAssignment. Function not found");
                    }

                    const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
                    auto value = std::make_shared<Value>()->set(localFunction, type);
                    auto assign = std::make_shared<Assign>()->set(variable, value);
                    statement->addStatement(assign);
                }
                else
                {
                    auto value = std::make_shared<Value>()->set(anotherVariable, anotherVariable->getVarType());
                    auto assign = std::make_shared<Assign>()->set(variable, value);
                    statement->addStatement(assign);
                }
            }
        }

        if (ctx->boolExpr())
        {

            const auto rightVarStr = visitBoolExpr(ctx->boolExpr(), currentFunction);
            const auto rightVar = currentFunction->findVarAllScopesAndArg(rightVarStr);

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const auto strLeftVarName = varDecl->varName->getText();
                const auto strLeftVarTypeName = varDecl->varTypes()->getText();

                auto leftVar = currentFunction->findVarAllScopesAndArg(strLeftVarName);

                auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                auto assign = std::make_shared<Assign>()->set(leftVar, value);
                statement->addStatement(assign);
            }
        }

        if (ctx->expr())
        {

            const auto strRightVarName = visitExpr(ctx->expr(), currentFunction);
            const auto rightVar = currentFunction->findVarAllScopesAndArg(strRightVarName);

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string leftVarName = varDecl->varName->getText();
                std::string leftVarTypeName = varDecl->varTypes()->getText();

                createMathExprAssign(leftVarName, leftVarTypeName, rightVar, currentFunction);
            }
        }

        if (ctx->functionCall())
        {
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varTypeStr = varDecl->varTypes()->getText();
                const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);

                const auto calledFunction = visitFunctionCall(ctx->functionCall(), currentFunction);
                const auto expr = std::make_shared<Expr>()->set(variable, calledFunction);
                statement->addStatement(expr);
            }
        }

        else if (ctx->arrowFunctionInline())
        {
            visitArrowFunctionInline(ctx->arrowFunctionInline(), currentFunction);
        }

        else if (ctx->structInit())
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const auto varName = varDeclaration->varName->getText();
                const auto variable = currentFunction->findVarAllScopesAndArg(varName);
                if (!variable)
                {
                    throw HLIRException(util::format(
                            "HLIRGenerator::visitStructInit. Undefined Variable: '{}' in expression", varName));
                }

                visitStructInit(ctx->structInit(), currentFunction, variable);
            }

        }
    }


} // namespace hlir

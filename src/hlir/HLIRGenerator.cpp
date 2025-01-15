#include "../headers/Hlir.h"
#include "../headers/HLIRGenerator.h"

namespace hlir
{
    HLIRGenerator::HLIRGenerator(std::shared_ptr<IronParser> parser, std::shared_ptr<Context> context)
        : parser(parser), context(context)
    {

        if (!parser)
        {
            throw HLIRException("The parser can't be nullptr");
        }

        if (!context)
        {
            throw HLIRException("The context can't be nullptr");
        }
    }

    HLIRGenerator::~HLIRGenerator() {}

    void HLIRGenerator::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        auto functionName = ctx->functionName->getText();
        // PUBLIC? FUNCTION functionName = IDENTIFIER functionSignature L_CURLY statementList R_CURLY;
        // std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType

        auto functionArgs = std::make_shared<FunctionArgs>();
        auto functionReturnType = std::make_shared<Type>();
        auto statement = std::make_shared<Statement>();

        auto function = std::make_shared<Function>()->set(functionName, functionArgs, functionReturnType, statement);
        context->addFunction(function);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
        }

        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList(), statement);
        }
    }
    void HLIRGenerator::visitStatementList(IronParser::StatementListContext *ctx, std::shared_ptr<Statement> statement)
    {
        for (auto child : ctx->children)
        {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration, statement);
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment, statement);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression, statement);
            }
            if (auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall, statement);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
            }
        }
    }
    void HLIRGenerator::visitVarDeclaration(IronParser::VarDeclarationContext *ctx, std::shared_ptr<Statement> statement)
    {

        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        {
            auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("Error: std::dynamic_pointer_cast<Function>(statement->getParent())");
            }
            auto alias = iron::createFunctionName(currentFunction->getFunctionName(), varName);
            auto aliasFunction = context->getFunctionByName(alias);

            if (!aliasFunction)
            {
                if (ctx->assignment())
                {
                    // visitAssignment(ctx->assignment(), sb);
                }
            }
            else
            {
                auto funcPtr = std::make_shared<FunctionPtr>()->set(aliasFunction);
                auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                auto value = std::make_shared<Value>()->set(aliasFunction, std::make_shared<Type>(tokenMap::FUNCTION_PTR));
                auto assign = std::make_shared<Assign>()->set(variable, value);

                statement->addStatement(assign);
            }
        }
        else
        {
            if (ctx->assignment())
            {
                visitAssignment(ctx->assignment(), statement);
            }
        }
    }
    void HLIRGenerator::visitVarAssignment(IronParser::VarAssignmentContext *ctx, std::shared_ptr<Statement> statement)
    {
    }

    std::string HLIRGenerator::visitExpr(IronParser::ExprContext *ctx, std::shared_ptr<Statement> statement)
    {
        int line = ctx->getStart()->getLine();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (auto child : ctx->children)
            {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
                {
                    return visitExpr(subExpr, statement);
                }
            }
        }

        if (ctx->left != nullptr && ctx->right != nullptr)
        {

            // Visita os lados esquerdo e direito da expressão
            std::string strLeftVar = visitExpr(ctx->left, statement);
            std::string strRightVar = visitExpr(ctx->right, statement);

            auto leftVar = statement->findVarByName(strLeftVar);
            auto rightVar = statement->findVarByName(strRightVar);

            if (!leftVar)
            {
                throw hlir::HLIRException(util::format("Undefined left variable: {} in expression", strLeftVar));
            }

            if (!rightVar)
            {
                throw hlir::HLIRException(util::format("Undefined right variable: {} in expression", strRightVar));
            }

            int higherType = tokenMap::getHigherPrecedenceType(leftVar->getVarType()->getType(), rightVar->getVarType()->getType());

            if (leftVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = statement->getNewVarName();

                auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(higherType));
                auto cast = std::make_shared<Cast>()->apply(leftVar, std::make_shared<Type>(higherType));

                auto expr = std::make_shared<Expr>()->set(tempVar, cast);

                statement->addStatement(expr);
                strLeftVar = tempVarStr;
            }

            if (rightVar->getVarType()->getType() != higherType)
            {

                std::string tempVarStr = statement->getNewVarName();
                auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(higherType));
                auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(higherType));

                strRightVar = tempVarStr;
            }

            std::string tempVarStr = statement->getNewVarName();

            auto newLeftVar = std::make_shared<Variable>()->set(strLeftVar, std::make_shared<Type>(higherType));
            auto newRightVar = std::make_shared<Variable>()->set(strRightVar, std::make_shared<Type>(higherType));
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(higherType));

            if (ctx->mult)
            {

                auto operation = std::make_shared<Mult>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->div)
            {
                auto operation = std::make_shared<Div>()->set(leftVar, rightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->plus)
            {
                auto operation = std::make_shared<Plus>()->set(leftVar, rightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->minus)
            {
                auto operation = std::make_shared<Minus>()->set(leftVar, rightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            return tempVarStr;
        }
        else if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            return varName;
        }
        else if (ctx->number())
        {

            std::string tempVarStr = statement->getNewVarName();
            std::string numberLiteral = ctx->number()->getText();
            int dataType = tokenMap::determineType(numberLiteral);

            if (dataType == tokenMap::REAL_NUMBER)
            {
                dataType = tokenMap::determineFloatType(numberLiteral);
            }

            auto type = std::make_shared<Type>(dataType);
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, type);
            auto value = std::make_shared<Value>()->set(numberLiteral, type);

            return tempVarStr;
        }

        throw hlir::HLIRException(util::format("Invalid expression. Line: {}", line));
    }

    void HLIRGenerator::visitAssignment(IronParser::AssignmentContext *ctx, std::shared_ptr<Statement> statement)
    {
        int line = ctx->getStart()->getLine();

        // Se houver um util::formato de dado literal (ex.: "3.14", "42", etc.)
        if (ctx->dataFormat())
        {
            // Caso 1: a atribuição está sendo feita a um argumento de função
            if (auto *functionArg = dynamic_cast<IronParser::FunctionArgContext *>(ctx->parent))
            {
                std::string argName = functionArg->varName->getText();
                std::string argType = functionArg->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType = tokenMap::determineType(literalValue);

                //*sb << util::format("{}:{} = {}", argName, argType, literalValue);
            }

            // Caso 2: a atribuição está sendo feita a uma variável declarada
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {

                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType = tokenMap::determineType(literalValue);

                auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(literalType));
                auto value = std::make_shared<Value>()->set(literalValue, std::make_shared<Type>(literalType));
                auto assign = std::make_shared<Assign>()->set(variable, value);

                statement->addStatement(assign);
            }
        }

        if (ctx->expr())
        {

            const auto strRightVarName = visitExpr(ctx->expr(), statement);
            auto rightVar = statement->findVarByName(strRightVarName);

            if (!rightVar)
            {
                throw HLIRException("The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string strLeftVarName = varDecl->varName->getText();
                std::string strLeftvarTypeName = varDecl->varTypes()->getText();

                int leftDataTypeType = tokenMap::getTokenType(strLeftvarTypeName);
                auto leftVar = std::make_shared<Variable>()->set(strLeftVarName, std::make_shared<Type>(leftDataTypeType));

                if (leftDataTypeType != rightVar->getVarType()->getType())
                {

                    std::string strTempVar = statement->getNewVarName();

                    auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(leftDataTypeType));
                    auto tempVariable = std::make_shared<Variable>()->set(strTempVar, std::make_shared<Type>(leftDataTypeType));

                    auto expr = std::shared_ptr<Expr>()->set(tempVariable, cast);

                    statement->addStatement(expr);

                    auto value = std::make_shared<Value>()->set(tempVariable, tempVariable->getVarType());
                    auto assign = std::make_shared<Assign>()->set(leftVar, value);
                    statement->addStatement(assign);
                }
                else
                {

                    auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                    auto assign = std::make_shared<Assign>()->set(leftVar, value);
                    statement->addStatement(assign);
                }
            }
        }
    }

    void HLIRGenerator::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType)
    {
        if (ctx->functionArgs())
        {
            visitFunctionArgs(ctx->functionArgs(), functionArgs);
        }

        if (ctx->functionReturnType())
        {
            ctx->functionReturnType()->varTypes()->getText();
            functionReturnType->set(tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText()));
        }
        else
        {
            functionReturnType->set(tokenMap::VOID);
        }
    }
    void HLIRGenerator::visitFunctionArgs(IronParser::FunctionArgsContext *ctx, std::shared_ptr<FunctionArgs> functionArgs)
    {

        for (auto child : ctx->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(funcDecl, functionArgs);
            }
        }
    }
    void HLIRGenerator::visitFunctionArg(IronParser::FunctionArgContext *ctx, std::shared_ptr<FunctionArgs> functionArgs)
    {
        auto argName = ctx->varName->getText();
        auto type = std::make_shared<Type>();
        type->set(tokenMap::getTokenType(ctx->varTypes()->getText()));
        functionArgs->addArg(std::make_shared<Arg>()->set(argName, type));
    }

    void HLIRGenerator::visitFunctionCall(IronParser::FunctionCallContext *ctx, std::shared_ptr<Statement> statement) {}
    void HLIRGenerator::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx) {}
    void HLIRGenerator::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx, bool hasComma) {}

    void HLIRGenerator::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) {}
    void HLIRGenerator::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx) {}
    void HLIRGenerator::visitReturn(IronParser::ReturnStatementContext *ctx) {}

    std::string HLIRGenerator::generateCode()
    {

        IronParser::ProgramContext *programContext = parser->program();

        // Processa todas as declarações no programa

        for (auto child : programContext->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        return context->getText();
    }
}
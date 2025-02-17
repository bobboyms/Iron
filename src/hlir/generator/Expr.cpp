#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"


namespace hlir
{

    std::string HLIRGenerator::visitBoolExpr(IronParser::BoolExprContext *ctx,
                                             const std::shared_ptr<Statement> &statement)
    {
        const uint line = ctx->getStart()->getLine();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (const auto child: ctx->children)
            {
                if (const auto subExpr = dynamic_cast<IronParser::BoolExprContext *>(child))
                {
                    return visitBoolExpr(subExpr, statement);
                }
            }
        }


        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            std::string strLeftVar = visitBoolExpr(ctx->left, statement);
            std::string strRightVar = visitBoolExpr(ctx->right, statement);

            const auto [higherType, leftVar, rightVar] =  initializerExprVariables(strLeftVar, strRightVar, statement);

            if (leftVar->getVarType()->getType() != higherType)
            {
                const std::string tempVarStr = statement->getNewVarName();
                const auto expr = castVariable(higherType, tempVarStr, leftVar);
                statement->addStatement(expr);
                strLeftVar = tempVarStr;
            }

            if (rightVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = statement->getNewVarName();
                const auto expr = castVariable(higherType, tempVarStr, rightVar);
                statement->addStatement(expr);
                strRightVar = tempVarStr;
            }

            std::string tempVarStr = statement->getNewVarName();

            auto newLeftVar = std::make_shared<Variable>()->set(strLeftVar, std::make_shared<Type>(higherType));
            auto newRightVar = std::make_shared<Variable>()->set(strRightVar, std::make_shared<Type>(higherType));
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));

            if (ctx->EQEQ())
            {
                auto operation = std::make_shared<CMP>(tokenMap::EQEQ)->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->NEQ())
            {
                auto operation = std::make_shared<CMP>(tokenMap::NEQ)->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->LT())
            {
                auto operation = std::make_shared<CMP>(tokenMap::LT)->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->LTE())
            {
                auto operation = std::make_shared<CMP>(tokenMap::LTE)->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->GT())
            {
                auto operation = std::make_shared<CMP>(tokenMap::GT)->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->GTE())
            {
                auto operation = std::make_shared<CMP>(tokenMap::GTE)->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->OR())
            {
                auto operation = std::make_shared<OR>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            if (ctx->AND())
            {
                auto operation = std::make_shared<AND>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            return tempVarStr;
        }

        if (ctx->BOOLEAN_VALUE())
        {
            std::string tempVarStr = statement->getNewVarName();
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));

            const auto value = std::make_shared<Value>()->set(ctx->BOOLEAN_VALUE()->getText(), std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            const auto assign = std::make_shared<Assign>()->set(tempVar, value);
            statement->addStatement(assign);
            return tempVarStr;
        }

        if (ctx->NOT())
        {
            std::string tempRightVarStr = statement->getNewVarName();
            auto newRightVar = std::make_shared<Variable>()->set(tempRightVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));

            const auto value = std::make_shared<Value>()->set("true", std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            const auto assign = std::make_shared<Assign>()->set(newRightVar, value);
            statement->addStatement(assign);

            const auto varName = visitBoolExpr(ctx->boolExpr().front(), statement);
            const auto [_, newLeftVar] = findVarByScope(statement, varName);

            std::string tempVarStr = statement->getNewVarName();
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));

            auto operation = std::make_shared<_NOT>()->set(newLeftVar, newRightVar);
            auto expr = std::make_shared<Expr>()->set(tempVar, operation);
            statement->addStatement(expr);

            return tempVarStr;
        }

        if (ctx->expr())
        {
            return visitExpr(ctx->expr(), statement);
        }

        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            return varName;
        }

        if (ctx->number())
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
            auto assign = std::make_shared<Assign>()->set(tempVar, value);

            statement->addStatement(assign);

            return tempVarStr;
        }

        throw HLIRException(util::format("Invalid boolean expression. Line: {}", line));
    }

    std::tuple<int, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
    HLIRGenerator::initializerExprVariables(const std::string &strLeftVar, const std::string &strRightVar,
                                  const std::shared_ptr<Statement> &statement)
    {
        const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
        if (!currentFunction)
        {
            throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
        }

        auto [_, rightVar] = findVarByScope(statement, strRightVar);
        auto [__, leftVar] = findVarByScope(statement, strLeftVar);

        // auto rightVar = right;
        // auto leftVar = left;

        if (!rightVar)
        {
            throw HLIRException(util::format("Undefined right variable: {} in expression", strRightVar));
        }

        if (!leftVar)
        {
            throw HLIRException(util::format("Undefined left variable: {} in expression", strLeftVar));
        }

        if (rightVar->isAnotherScope())
        {

            ensureVariableCaptured(currentFunction, rightVar);
        }

        if (leftVar->isAnotherScope())
        {
            ensureVariableCaptured(currentFunction, leftVar);
        }

        int higherType;
        if (rightVar->getVarType()->getType() == tokenMap::TYPE_BOOLEAN || leftVar->getVarType()->getType() == tokenMap::TYPE_BOOLEAN)
        {
            higherType = tokenMap::TYPE_BOOLEAN;
        } else
        {
            higherType = tokenMap::getHigherPrecedenceType(leftVar->getVarType()->getType(), rightVar->getVarType()->getType());
        }

        return std::make_tuple(higherType, leftVar, rightVar);

    }

    std::shared_ptr<Expr> HLIRGenerator::castVariable(int higherType, const std::string &varName, const std::shared_ptr<Variable> &variable)
    {
        const auto tempVar = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(higherType));
        const auto cast = std::make_shared<Cast>()->apply(variable, std::make_shared<Type>(higherType));
        return std::make_shared<Expr>()->set(tempVar, cast);
    }

    std::string HLIRGenerator::visitExpr(IronParser::ExprContext *ctx, const std::shared_ptr<Statement> &statement)
    {
        const uint line = ctx->getStart()->getLine();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (auto child: ctx->children)
            {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
                {
                    return visitExpr(subExpr, statement);
                }
            }
        }

        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            std::string strLeftVar = visitExpr(ctx->left, statement);
            std::string strRightVar = visitExpr(ctx->right, statement);

            const auto [higherType, leftVar, rightVar] =  initializerExprVariables(strLeftVar, strRightVar, statement);

            if (leftVar->getVarType()->getType() != higherType)
            {
                const std::string tempVarStr = statement->getNewVarName();
                const auto expr = castVariable(higherType, tempVarStr, leftVar);
                statement->addStatement(expr);
                strLeftVar = tempVarStr;
            }

            if (rightVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = statement->getNewVarName();
                const auto expr = castVariable(higherType, tempVarStr, rightVar);
                statement->addStatement(expr);
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
                auto operation = std::make_shared<Div>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->plus)
            {
                auto operation = std::make_shared<Plus>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }
            else if (ctx->minus)
            {
                auto operation = std::make_shared<Minus>()->set(newLeftVar, newRightVar);
                auto expr = std::make_shared<Expr>()->set(tempVar, operation);
                statement->addStatement(expr);
            }

            return tempVarStr;
        }

        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            return varName;
        }

        if (ctx->number())
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
            auto assign = std::make_shared<Assign>()->set(tempVar, value);

            statement->addStatement(assign);

            return tempVarStr;
        }

        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();

            auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            if (auto globalFunction = context->getFunctionByName(functionName))
            {
                std::string strTempVar = statement->getNewVarName();

                auto tempVar = std::make_shared<Variable>()->set(
                        strTempVar, std::make_shared<Type>(globalFunction->getFunctionReturnType()->getType()));

                auto functionCall = visitFunctionCall(ctx->functionCall(), statement);
                auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
                statement->addStatement(expr);

                return strTempVar;
            }
            const std::string localFunctionName =
                    iron::createFunctionName(currentFunction->getFunctionName(), functionName);

            auto localFunction = context->getFunctionByName(localFunctionName);

            if (!localFunction)
            {
                throw HLIRException("hlir::visitExpr. function not found");
            }

            std::string strTempVar = statement->getNewVarName();

            auto tempVar = std::make_shared<Variable>()->set(
                    strTempVar, std::make_shared<Type>(localFunction->getFunctionReturnType()->getType()));

            auto functionCall = visitFunctionCall(ctx->functionCall(), statement);
            auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
            statement->addStatement(expr);

            return strTempVar;
        }

        throw HLIRException(util::format("Invalid expression. Line: {}", line));
    }
} // namespace hlir

/**
 * @file Expr.cpp
 * @brief Implementation of expression handling in the HLIR generator
 */
#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"
#include <string_view>

namespace hlir
{
    /**
     * @brief Gets or creates variables needed for binary operations
     * 
     * This utility method finds or creates the variables needed for a binary operation,
     * including optionally creating a temporary variable for the result.
     * 
     * @param currentFunction The current function context
     * @param leftVarName Name of the left variable
     * @param rightVarName Name of the right variable
     * @param tempVarName Name for the temporary result variable
     * @param targetType Type to use for the variables
     * @param createTempVar Whether to create a temporary variable for the result
     * @return Tuple of (leftVar, rightVar, tempVar) with tempVar possibly nullptr
     * @throws HLIRException If variables cannot be found or created
     */
    std::tuple<std::shared_ptr<Variable>, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
    HLIRGenerator::getVariableOrCreate(
        const std::shared_ptr<Function> &currentFunction, 
        const std::string &strLeftVar,
        const std::string &strRightVar, 
        const std::string &tempVarStr,
        uint higherType, 
        bool createTempVar)
    {
        if (!currentFunction) {
            throw HLIRException("getVariableOrCreate: Current function is null");
        }
        
        // Find or create left variable
        auto leftVar = currentFunction->findVarAllScopesAndArg(strLeftVar);
        if (!leftVar) {
            leftVar = std::make_shared<Variable>()->set(
                strLeftVar, 
                std::make_shared<Type>(higherType));
        }
        
        // Find or create right variable
        auto rightVar = currentFunction->findVarAllScopesAndArg(strRightVar);
        if (!rightVar) {
            rightVar = std::make_shared<Variable>()->set(
                strRightVar, 
                std::make_shared<Type>(higherType));
        }
        
        // Verify variables were created successfully
        if (!rightVar) {
            throw HLIRException(util::format(
                "Undefined right variable: {} in expression", 
                strRightVar));
        }
        
        if (!leftVar) {
            throw HLIRException(util::format(
                "Undefined left variable: {} in expression", 
                strLeftVar));
        }
        
        // Create temp variable if requested
        if (createTempVar) {
            auto statement = currentFunction->getCurrentLocalScope();
            if (!statement) {
                throw HLIRException("Current scope is null");
            }
            
            const auto tempVar = std::make_shared<Variable>()->set(
                tempVarStr, 
                std::make_shared<Type>(higherType));
                
            statement->addDeclaredVariable(tempVar);
            return std::make_tuple(leftVar, rightVar, tempVar);
        }
        
        return std::make_tuple(leftVar, rightVar, nullptr);
    }

    std::string HLIRGenerator::visitBoolExpr(IronParser::BoolExprContext *ctx,
                                             const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        const uint line = ctx->getStart()->getLine();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (const auto child: ctx->children)
            {
                if (const auto subExpr = dynamic_cast<IronParser::BoolExprContext *>(child))
                {
                    return visitBoolExpr(subExpr, currentFunction);
                }
            }
        }


        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            std::string strLeftVar = visitBoolExpr(ctx->left, currentFunction);
            std::string strRightVar = visitBoolExpr(ctx->right, currentFunction);


            const auto [higherType, leftVar, rightVar] =
                    initializerExprVariables(strLeftVar, strRightVar, currentFunction);

            if (leftVar->getVarType()->getType() != higherType)
            {
                const std::string tempVarStr = currentFunction->generateVarName();
                const auto expr = castVariable(higherType, tempVarStr, leftVar, currentFunction);
                statement->addStatement(expr);
                strLeftVar = tempVarStr;
            }

            if (rightVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = currentFunction->generateVarName();
                const auto expr = castVariable(higherType, tempVarStr, rightVar, currentFunction);
                statement->addStatement(expr);
                strRightVar = tempVarStr;
            }

            std::string tempVarStr = currentFunction->generateVarName();

            const auto [newLeftVar, newRightVar, _] =
                    getVariableOrCreate(currentFunction, strLeftVar, strRightVar, tempVarStr, higherType, false);
            auto tempVar =
                    std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            statement->addDeclaredVariable(tempVar);

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
            std::string tempVarStr = currentFunction->generateVarName();
            auto tempVar =
                    std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            statement->addDeclaredVariable(tempVar);
            const auto value = std::make_shared<Value>()->set(ctx->BOOLEAN_VALUE()->getText(),
                                                              std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            const auto assign = std::make_shared<Assign>()->set(tempVar, value);
            statement->addStatement(assign);
            return tempVarStr;
        }

        if (ctx->NOT())
        {
            std::string tempRightVarStr = currentFunction->generateVarName();
            auto newRightVar =
                    std::make_shared<Variable>()->set(tempRightVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            statement->addDeclaredVariable(newRightVar);
            const auto value = std::make_shared<Value>()->set("true", std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            const auto assign = std::make_shared<Assign>()->set(newRightVar, value);
            statement->addStatement(assign);

            const auto varName = visitBoolExpr(ctx->boolExpr().front(), currentFunction);
            const auto newLeftVar =
                    currentFunction->findVarAllScopesAndArg(varName); // findVarByScope(currentFunction, varName);

            std::string tempVarStr = currentFunction->generateVarName();
            auto tempVar =
                    std::make_shared<Variable>()->set(tempVarStr, std::make_shared<Type>(tokenMap::TYPE_BOOLEAN));
            statement->addDeclaredVariable(tempVar);
            auto operation = std::make_shared<_NOT>()->set(newLeftVar, newRightVar);
            auto expr = std::make_shared<Expr>()->set(tempVar, operation);
            statement->addStatement(expr);

            return tempVarStr;
        }

        if (ctx->expr())
        {
            return visitExpr(ctx->expr(), currentFunction);
        }

        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            return varName;
        }

        if (ctx->number())
        {
            std::string tempVarStr = currentFunction->generateVarName();
            std::string numberLiteral = ctx->number()->getText();
            int dataType = tokenMap::determineType(numberLiteral);

            if (dataType == tokenMap::REAL_NUMBER)
            {
                dataType = tokenMap::determineFloatType(numberLiteral);
            }

            auto type = std::make_shared<Type>(dataType);
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, type);
            statement->addDeclaredVariable(tempVar);
            auto value = std::make_shared<Value>()->set(numberLiteral, type);
            auto assign = std::make_shared<Assign>()->set(tempVar, value);

            statement->addStatement(assign);

            return tempVarStr;
        }

        throw HLIRException(util::format("Invalid boolean expression. Line: {}", line));
    }

    std::tuple<int, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
    HLIRGenerator::initializerExprVariables(const std::string &strLeftVar, const std::string &strRightVar,
                                            const std::shared_ptr<Function> &currentFunction)
    {

        auto rightVar = currentFunction->findVarAllScopesAndArg(strRightVar);
        auto leftVar = currentFunction->findVarAllScopesAndArg(strLeftVar);

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
        if (rightVar->getVarType()->getType() == tokenMap::TYPE_BOOLEAN ||
            leftVar->getVarType()->getType() == tokenMap::TYPE_BOOLEAN)
        {
            higherType = tokenMap::TYPE_BOOLEAN;
        }
        else
        {
            higherType = tokenMap::getHigherPrecedenceType(leftVar->getVarType()->getType(),
                                                           rightVar->getVarType()->getType());
        }

        return std::make_tuple(higherType, leftVar, rightVar);
    }

    std::shared_ptr<Expr> HLIRGenerator::castVariable(int higherType, const std::string &varName,
                                                      const std::shared_ptr<Variable> &variable,
                                                      const std::shared_ptr<Function> &currentFunction
                                                      )
    {

        if (!variable)
        {
            throw HLIRException(util::format("HLIRGenerator::castVariable. Undefined variable: {} in expression", varName));
        }

        const auto tempVar = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(higherType));
        const auto cast = std::make_shared<Cast>()->apply(variable, std::make_shared<Type>(higherType));

        currentFunction->getCurrentLocalScope()->addDeclaredVariable(tempVar);

        return std::make_shared<Expr>()->set(tempVar, cast);

    }


    std::string HLIRGenerator::visitExpr(IronParser::ExprContext *ctx, const std::shared_ptr<Function> &currentFunction)
    {

        const uint line = ctx->getStart()->getLine();
        const auto statement = currentFunction->getCurrentLocalScope();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (auto child: ctx->children)
            {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
                {
                    return visitExpr(subExpr, currentFunction);
                }
            }
        }

        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            std::string strLeftVar = visitExpr(ctx->left, currentFunction);
            std::string strRightVar = visitExpr(ctx->right, currentFunction);

            const auto [higherType, leftVar, rightVar] =
                    initializerExprVariables(strLeftVar, strRightVar, currentFunction);

            if (leftVar->getVarType()->getType() != higherType)
            {
                const std::string tempVarStr = currentFunction->generateVarName();
                const auto expr = castVariable(higherType, tempVarStr, leftVar, currentFunction);
                statement->addStatement(expr);
                strLeftVar = tempVarStr;
            }

            if (rightVar->getVarType()->getType() != higherType)
            {
                std::string tempVarStr = currentFunction->generateVarName();
                const auto expr = castVariable(higherType, tempVarStr, rightVar, currentFunction);
                statement->addStatement(expr);
                strRightVar = tempVarStr;
            }

            std::string tempVarStr = currentFunction->generateVarName();

            const auto [newLeftVar, newRightVar, tempVar] =
                    getVariableOrCreate(currentFunction, strLeftVar, strRightVar, tempVarStr, higherType, true);

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
            const auto tempVarStr = currentFunction->generateVarName();
            const auto numberLiteral = ctx->number()->getText();
            int dataType = tokenMap::determineType(numberLiteral);

            if (dataType == tokenMap::REAL_NUMBER)
            {
                dataType = tokenMap::determineFloatType(numberLiteral);
            }

            auto type = std::make_shared<Type>(dataType);
            auto tempVar = std::make_shared<Variable>()->set(tempVarStr, type);
            statement->addDeclaredVariable(tempVar);
            auto value = std::make_shared<Value>()->set(numberLiteral, type);
            auto assign = std::make_shared<Assign>()->set(tempVar, value);

            statement->addStatement(assign);

            return tempVarStr;
        }

        if (ctx->functionCall())
        {

            std::string strTempVar = currentFunction->generateVarName();
            auto const functionName = ctx->functionCall()->functionName->getText();

            if (const auto variable = currentFunction->findVarAllScopesAndArg(functionName);
                variable && variable->getSignature())
            {

                if (variable->isAnotherScope())
                {
                    ensureVariableCaptured(currentFunction, variable);
                }

                if (variable->isFromFunctionArg())
                {
                    const auto tempVar = std::make_shared<Variable>()->set(
                            strTempVar, std::make_shared<Type>(variable->getSignature()->getReturnType()->getType()));
                    statement->addDeclaredVariable(tempVar);

                    const auto functionCall = visitFunctionCall(ctx->functionCall(), currentFunction);
                    const auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
                    statement->addStatement(expr);

                    return strTempVar;
                }

                const auto localFunction = getFunctionValue(currentFunction, functionName);
                const auto tempVar = std::make_shared<Variable>()->set(
                        strTempVar, std::make_shared<Type>(localFunction->getFunctionReturnType()->getType()));
                statement->addDeclaredVariable(tempVar);

                const auto functionCall = visitFunctionCall(ctx->functionCall(), currentFunction);

                const auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
                statement->addStatement(expr);

                return strTempVar;
            }

            if (auto globalFunction = context->getFunctionByName(functionName))
            {

                const auto tempVar = std::make_shared<Variable>()->set(
                        strTempVar, std::make_shared<Type>(globalFunction->getFunctionReturnType()->getType()));
                statement->addDeclaredVariable(tempVar);

                const auto functionCall = visitFunctionCall(ctx->functionCall(), currentFunction);
                const auto expr = std::make_shared<Expr>()->set(tempVar, functionCall);
                statement->addStatement(expr);

                return strTempVar;
            }

            throw HLIRException(util::format("Invalid expression. Line: {}", line));
        }
    }
} // namespace hlir

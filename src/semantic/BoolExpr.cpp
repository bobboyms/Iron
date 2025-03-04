#include "../headers/SemanticAnalysis.h"

namespace iron
{
    /**
     * @brief Processes a boolean expression and determines its type
     * 
     * Evaluates a boolean expression in the AST, handling different kinds of expressions
     * like comparisons, boolean literals, variables, and function calls. Ensures type
     * compatibility for boolean operations.
     * 
     * @param ctx The boolean expression context from the parser
     * @return std::pair<std::string, int> The expression name and its type
     * @throws TypeMismatchException if expression types are incompatible
     * @throws std::runtime_error if the expression is invalid
     */
    std::pair<std::string, int> SemanticAnalysis::visitBoolExpr(IronParser::BoolExprContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        auto currentFunction = getCurrentFunction();

        // Handle parenthesized expressions
        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            return visitBoolExpr(ctx->boolExpr(0));
        }

        // Handle binary operations between two boolean expressions
        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            auto [leftName, leftType] = visitBoolExpr(ctx->left);
            auto [rightName, rightType] = visitBoolExpr(ctx->right);

            // Check if types are compatible for boolean operations
            bool leftIsValidType = tokenMap::isNumber(leftType) || leftType == tokenMap::TYPE_BOOLEAN;
            bool rightIsValidType = tokenMap::isNumber(rightType) || rightType == tokenMap::TYPE_BOOLEAN;
            
            if (leftIsValidType && rightIsValidType)
            {
                // If either operand is boolean, the result is boolean
                if (leftType == tokenMap::TYPE_BOOLEAN || rightType == tokenMap::TYPE_BOOLEAN)
                {
                    return {rightName, tokenMap::TYPE_BOOLEAN};
                }
                
                // Otherwise, determine the appropriate numeric type
                auto resultType = tokenMap::getHigherPrecedenceType(leftType, rightType);
                return {rightName, resultType};
            }

            // Types are incompatible, throw a detailed error
            verifyTypesMatch(
                leftType, 
                rightType, 
                leftName, 
                rightName, 
                lineNumber, 
                columnPosition, 
                "The left operator of type is incompatible with the right operator"
            );
        }

        // Handle regular expression within a boolean context
        if (ctx->expr())
        {
            return visitExpr(ctx->expr());
        }

        // Handle boolean literals
        if (ctx->booleanValue)
        {
            return {ctx->booleanValue->getText(), tokenMap::TYPE_BOOLEAN};
        }

        // Handle boolean NOT operation
        if (ctx->not_)
        {
            return {ctx->not_->getText(), tokenMap::TYPE_BOOLEAN};
        }

        // Handle numeric literals in boolean context
        if (ctx->number())
        {
            std::string numberText = ctx->number()->getText();
            int numberType = determineValueType(numberText);
            return {numberText, numberType};
        }

        // Handle variables in boolean context
        if (ctx->varName)
        {
            const std::string variableName = ctx->varName->getText();
            const auto variable = verifyVariableExists(variableName, lineNumber, columnPosition);
            return {variable->name, variable->type};
        }

        // Handle function calls in boolean context
        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();
            auto function = verifyFunctionExists(functionName, lineNumber, columnPosition);
            visitFunctionCall(ctx->functionCall());
            return {functionName, function->getReturnType()};
        }

        // If none of the expected patterns matched, the expression is invalid
        throw std::runtime_error("Invalid boolean expression");
    }

} // namespace iron

#include "../headers/SemanticAnalysis.h"

namespace iron
{
    /**
     * @brief Evaluates an expression and determines its type
     * 
     * Processes an expression node in the AST, handling different kinds of expressions
     * like arithmetic operations, variables, literals, and function calls. Ensures
     * type compatibility for operations and provides detailed error messages.
     * 
     * @param ctx The expression context from the parser
     * @return std::pair<std::string, int> The expression name and its type
     * @throws TypeMismatchException if expression types are incompatible
     * @throws std::runtime_error if the expression is invalid
     */
    std::pair<std::string, int> SemanticAnalysis::visitExpr(IronParser::ExprContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        auto currentFunction = getCurrentFunction();

        // Handle parenthesized expressions
        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            return visitExpr(ctx->expr(0));
        }

        // Handle binary operations
        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            auto [leftName, leftType] = visitExpr(ctx->left);
            auto [rightName, rightType] = visitExpr(ctx->right);

            // Handle numeric operations
            if (tokenMap::isNumber(leftType) && tokenMap::isNumber(rightType))
            {
                // Determine the result type based on operand types
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

        // Handle variable references
        if (ctx->varName)
        {
            const std::string variableName = ctx->varName->getText();
            auto variable = verifyVariableExists(variableName, lineNumber, columnPosition);
            return {variable->name, variable->type};
        }

        // Handle numeric literals
        if (ctx->number())
        {
            std::string numberText = ctx->number()->getText();
            int numberType = determineValueType(numberText);
            return {numberText, numberType};
        }

        // Handle function calls
        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();
            auto function = verifyFunctionExists(functionName, lineNumber, columnPosition);
            visitFunctionCall(ctx->functionCall());
            return {functionName, function->getReturnType()};
        }

        // If none of the expected patterns matched, the expression is invalid
        throw std::runtime_error("Invalid expression");
    }

} // namespace iron

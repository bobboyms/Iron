#include "../headers/SemanticAnalysis.h"

namespace iron
{
    /**
     * @brief Processes the block of statements within an if statement
     * 
     * Validates and processes all statements within an if or else block.
     * Handles scoping for the statements inside the block.
     * 
     * @param ctx The if block context from the parser
     */
    void SemanticAnalysis::visitIfBlock(IronParser::IfBlockContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        
        // Process all statements in the block
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList());
        }
    }

    /**
     * @brief Processes an if statement with its condition and branches
     * 
     * Validates the boolean condition and processes both the if and optional else branches.
     * Ensures the condition is of boolean type and throws appropriate errors for invalid conditions.
     * 
     * @param ctx The if statement context from the parser
     * @throws std::runtime_error if the if statement doesn't have a boolean expression
     */
    void SemanticAnalysis::visitIfStatement(IronParser::IfStatementContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        
        // Verify that the if statement has a boolean expression
        if (!ctx->boolExpr())
        {
            throw std::runtime_error(util::format(
                "If statement must have a boolean expression.\n"
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(std::to_string(lineNumber), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine, caretLine));
        }

        // Process and validate the boolean expression
        auto [exprName, exprType] = visitBoolExpr(ctx->boolExpr());
        
        // Verify condition is boolean compatible
        if (exprType != tokenMap::TYPE_BOOLEAN && !tokenMap::isNumber(exprType)) {
            throw TypeMismatchException(util::format(
                "If condition must be a boolean expression or numeric value, got {} of type {}.\n"
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(exprName, color::BOLD_GREEN),
                color::colorText(tokenMap::getTokenText(exprType), color::BOLD_GREEN),
                color::colorText(std::to_string(lineNumber), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine, caretLine));
        }

        // Process the if block
        if (ctx->ifBlock())
        {
            visitIfBlock(ctx->ifBlock());
        }

        // Process the optional else statement
        if (ctx->elseStatement())
        {
            visitElseStatement(ctx->elseStatement());
        }
    }

    /**
     * @brief Processes an else statement or else-if chain
     * 
     * Handles the else branch of an if statement, which can be either
     * a simple block of statements or another if statement (else-if).
     * 
     * @param ctx The else statement context from the parser
     */
    void SemanticAnalysis::visitElseStatement(IronParser::ElseStatementContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        
        // Handle else-if case
        if (ctx->ifStatement())
        {
            visitIfStatement(ctx->ifStatement());
        }
        // Handle simple else block
        else if (ctx->ifBlock())
        {
            visitIfBlock(ctx->ifBlock());
        }
    }

} // namespace iron

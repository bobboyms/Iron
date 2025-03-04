#include "../headers/SemanticAnalysis.h"
#include <iostream>
#include <utility>
#include "../headers/Analyser.h"
#include "../headers/Files.h"

namespace iron
{
    /**
     * @brief Processes a while loop statement
     * 
     * Validates the boolean condition and processes the statement list in the loop body.
     * Ensures the condition is of boolean type and handles the scope for the loop body.
     * 
     * @param ctx The while statement context from the parser
     */
    void SemanticAnalysis::visitWhileStatement(IronParser::WhileStatementContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        
        // Validate the boolean expression
        auto [exprName, exprType] = visitBoolExpr(ctx->boolExpr());
        
        // Verify condition is boolean compatible
        if (exprType != tokenMap::TYPE_BOOLEAN && !tokenMap::isNumber(exprType)) {
            throw TypeMismatchException(util::format(
                "While loop condition must be a boolean expression or numeric value, got {} of type {}.\n"
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(exprName, color::BOLD_GREEN),
                color::colorText(tokenMap::getTokenText(exprType), color::BOLD_GREEN),
                color::colorText(std::to_string(lineNumber), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine, caretLine));
        }
        
        // Process the loop body
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList());
        }
    }
    
    /**
     * @brief Processes a repeat statement (do-while equivalent)
     * 
     * Validates the loop body and the condition. Ensures proper scope handling
     * and type checking for the loop condition.
     * 
     * @param ctx The repeat statement context from the parser
     */
    void SemanticAnalysis::visitRepeatStatement(IronParser::RepeatStatementContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        // Process the loop body first (executed at least once)
        // if (ctx->loopStatementList())
        // {
        //     visitStatementList(ctx->loopStatementList());
        // }

        // Then validate the condition
        if (ctx->boolExpr())
        {
            auto [exprName, exprType] = visitBoolExpr(ctx->boolExpr());

            // Verify condition is boolean compatible
            if (exprType != tokenMap::TYPE_BOOLEAN && !tokenMap::isNumber(exprType)) {
                throw TypeMismatchException(util::format(
                    "Repeat loop condition must be a boolean expression or numeric value, got {} of type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(exprName, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(exprType), color::BOLD_GREEN),
                    color::colorText(std::to_string(lineNumber), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine, caretLine));
            }
        }
        else {
            throw std::runtime_error("Repeat statement is missing a condition");
        }
    }
    
    /**
     * @brief Processes a for loop statement
     * 
     * Handles initialization, condition, and increment expressions in a for loop.
     * Manages scope and variable declarations for the loop.
     * 
     * @param ctx The for statement context from the parser
     */
    void SemanticAnalysis::visitForStatement(IronParser::ForStatementContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
        
        auto currentFunction = getCurrentFunction();
        
        // Create a new scope for the for loop variables
        currentFunction->enterLocalScope(std::make_shared<scope::Statements>());
        
        // Process the initialization expression
        // if (ctx->varDeclaration())
        // {
        //     visitVarDeclaration(ctx->varDeclaration());
        // }
        
        // Process the condition expression
        // if (ctx->boolExpr())
        // {
        //     auto [exprName, exprType] = visitBoolExpr(ctx->boolExpr());
        //
        //     // Verify condition is boolean compatible
        //     if (exprType != tokenMap::TYPE_BOOLEAN && !tokenMap::isNumber(exprType)) {
        //         throw TypeMismatchException(util::format(
        //             "For loop condition must be a boolean expression or numeric value, got {} of type {}.\n"
        //             "Line: {}, Scope: {}\n\n"
        //             "{}\n"
        //             "{}\n",
        //             color::colorText(exprName, color::BOLD_GREEN),
        //             color::colorText(tokenMap::getTokenText(exprType), color::BOLD_GREEN),
        //             color::colorText(std::to_string(lineNumber), color::YELLOW),
        //             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
        //             codeLine, caretLine));
        //     }
        // }
        
        // Process the increment/update expression
        // if (ctx->varAssignment())
        // {
        //     visitVarAssignment(ctx->varAssignment());
        // }
        
        // Process the loop body
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList());
        }
        
        // Exit the for loop scope
        currentFunction->exitLocalScope();
    }
}
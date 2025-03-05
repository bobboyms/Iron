/**
 * @file IFelse.cpp
 * @brief Implementation of if-else statement processing for the HLIR generator
 * @author Thiago Rodrigues
 * @date 2025-02-18
 */

#include <tuple>
#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"

namespace hlir
{
    /**
     * @brief Executes a conditional block and checks if it contains return or break statements
     * 
     * This method creates a new scope, visits the block, and checks if it contains
     * return or break statements before exiting the scope.
     * 
     * @param blockCtx The if block context to visit
     * @param currentFunction The current function context
     * @param endJump The jump to the end of the block
     * @return A pair indicating if the block has break and return statements
     */
    std::pair<bool, bool> HLIRGenerator::visitBlockAndCheckReturn(
        IronParser::IfBlockContext* blockCtx,
        const std::shared_ptr<Function>& currentFunction,
        const std::shared_ptr<Jump> &endJump)
    {
        // Use RAII ScopeGuard to manage scope entry/exit
        auto scopeStatement = std::make_shared<Statement>();
        ScopeGuard guard(currentFunction, scopeStatement);
        
        const auto [hasBreak, hasReturn] = visitIfBlock(blockCtx, currentFunction, endJump);
        return std::make_pair(hasBreak, hasReturn);
    }

    /**
     * @brief Adds an end block to the statement, with a jump if needed
     * 
     * @param currentFunction The current function context
     * @param statement The statement to add the end block to
     * @param endLabel The label for the end block
     * @param haveReturn Whether the code path already has a return statement
     */
    void HLIRGenerator::handleEndBlock(
        const std::shared_ptr<Function>& currentFunction,
        const std::shared_ptr<Statement>& statement,
        const std::string &endLabel,
        const bool haveReturn)
    {
        if (!statement) {
            throw HLIRException("handleEndBlock: Statement is null");
        }
        
        auto endBlock = std::make_shared<Block>()->set(endLabel);
        if (!endBlock) {
            throw HLIRException("handleEndBlock: Failed to create end block");
        }
        
        // Only add jump if there's no return statement
        if (!haveReturn) {
            auto endJump = std::make_shared<Jump>(endBlock);
            statement->addStatement(endJump);
        }
        
        endBlock->changeToEndBlock();
        statement->addStatement(endBlock);
    }

/**
 * @brief Processes an if block by visiting its statements
 * 
 * @param ctx The if block context
 * @param currentFunction The current function context
 * @param endJump The jump to the end of the block
 * @return A pair indicating if the block has break and return statements
 */
std::pair<bool, bool> HLIRGenerator::visitIfBlock(
    IronParser::IfBlockContext *ctx,
    const std::shared_ptr<Function> &currentFunction,
    const std::shared_ptr<Jump> &endJump)
{
    if (!ctx) {
        return std::make_pair(false, false);
    }

    if (ctx->statementList()) {
        return visitStatementList(ctx->statementList(), currentFunction, endJump);
    }

    return std::make_pair(false, false);
}

/**
 * @brief Processes an if statement with possible else blocks
 * 
 * @param ctx The if statement context
 * @param currentFunction The current function context
 * @param endLabel The label for the end of the if statement
 * @param endJump The jump to the end of the enclosing block
 * @return A pair indicating if the if statement has break and return statements
 */
std::pair<bool, bool> HLIRGenerator::visitIfStatement(
    IronParser::IfStatementContext *ctx,
    const std::shared_ptr<Function> &currentFunction,
    const std::string &endLabel,
    const std::shared_ptr<Jump> &endJump)
{
    if (!ctx) {
        throw HLIRException("visitIfStatement: Context is null");
    }
    
    const auto statement = currentFunction->getCurrentLocalScope();
    if (!statement) {
        throw HLIRException("visitIfStatement: Current scope is null");
    }

    // Process the condition expression
    const std::string varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
    const auto variable = currentFunction->findVarCurrentScopeAndArg(varName);
    if (!variable) {
        throw HLIRException(util::format("Variable '{}' not found in scope", varName));
    }

    // Generate unique labels for then and else blocks
    const std::string thenLabel = currentFunction->generateLabel("then");
    const std::string elseLabel = currentFunction->generateLabel("else");

    // Create conditional branching
    auto conditional = std::make_shared<Conditional>()->set(variable);
    conditional->setTrueLabel(thenLabel);
    conditional->setFalseLabel(elseLabel);
    statement->addStatement(conditional);

    // Create the 'then' block
    auto thenBlock = std::make_shared<Block>()->set(thenLabel);
    statement->addStatement(thenBlock);

    // Process the 'then' block
    bool hasBreak = false;
    bool hasReturn = false;
    if (ctx->ifBlock()) {
        std::tie(hasBreak, hasReturn) = visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction, endJump);
    }

    // Handle else statement if present
    if (ctx->elseStatement()) {
        // Add jump to end block if needed
        if (!hasReturn && !hasBreak) {
            auto endBlock = std::make_shared<Block>()->set(endLabel);
            auto endJump = std::make_shared<Jump>(endBlock);
            statement->addStatement(endJump);
        }
        
        // Process the 'else' block
        bool elseHasBreak, elseHasReturn;
        std::tie(elseHasBreak, elseHasReturn) = visitElseStatement(
            ctx->elseStatement(), currentFunction, elseLabel, endLabel, endJump);
        
        // Combine results from both branches
        hasBreak = hasBreak || elseHasBreak;
        hasReturn = hasReturn || elseHasReturn;
    }
    else {
        // No else block: adjust the false label to point to the end
        conditional->setFalseLabel(endLabel);
        handleEndBlock(currentFunction, statement, endLabel, hasBreak || hasReturn);
    }

    return std::make_pair(hasBreak, hasReturn);
}

/**
 * @brief Processes an else statement
 * 
 * @param ctx The else statement context
 * @param currentFunction The current function context
 * @param label The label for this else block
 * @param endLabel The label for the end of the if statement
 * @param endJump The jump to the end of the enclosing block
 * @return A pair indicating if the else statement has break and return statements
 */
std::pair<bool, bool> HLIRGenerator::visitElseStatement(
    IronParser::ElseStatementContext *ctx,
    const std::shared_ptr<Function> &currentFunction,
    const std::string &label, 
    const std::string &endLabel,
    const std::shared_ptr<Jump> &endJump)
{
    if (!ctx) {
        throw HLIRException("visitElseStatement: Context is null");
    }
    
    const auto statement = currentFunction->getCurrentLocalScope();
    if (!statement) {
        throw HLIRException("visitElseStatement: Current scope is null");
    }
    
    // Create the else block
    auto block = std::make_shared<Block>()->set(label);
    statement->addStatement(block);

    // Handle nested if statement
    if (ctx->ifStatement()) {
        return visitIfStatement(ctx->ifStatement(), currentFunction, endLabel, endJump);
    }

    // Handle else block
    if (ctx->ifBlock()) {
        auto [hasBreak, hasReturn] = visitBlockAndCheckReturn(ctx->ifBlock(), currentFunction, endJump);
        
        // Add end block with conditional jump
        handleEndBlock(currentFunction, statement, endLabel, hasBreak || hasReturn);
        return std::make_pair(hasBreak, hasReturn);
    }
    
    // If neither if statement nor block is present, this is an empty else
    handleEndBlock(currentFunction, statement, endLabel, false);
    return std::make_pair(false, false);
}

} // namespace hlir



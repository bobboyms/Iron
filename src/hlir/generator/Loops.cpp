/**
 * @file Loops.cpp
 * @brief Implementation of loop statement processing for the HLIR generator
 * @author Thiago Rodrigues
 * @date 2025-03-01
 */
#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"
#include <string_view>

namespace hlir
{

    /**
     * @brief Processes a while loop statement
     *
     * This method generates the HLIR representation of a while loop,
     * including condition checking, body execution, and proper flow control.
     *
     * @param ctx The while statement context
     * @param currentFunction The current function context
     * @throws HLIRException If the condition variable is not found or statement is null
     */
    void HLIRGenerator::visitWhileStatement(
        IronParser::WhileStatementContext *ctx,
        const std::shared_ptr<Function> &currentFunction)
    {
        if (!ctx) {
            throw HLIRException("visitWhileStatement: Context is null");
        }
        
        const auto statement = currentFunction->getCurrentLocalScope();
        if (!statement) {
            throw HLIRException("visitWhileStatement: Current scope is null");
        }

        // Generate unique labels for loop parts
        const std::string whileCond = currentFunction->generateLabel("while_cond");
        const std::string whileBody = currentFunction->generateLabel("while_body");
        const std::string whileEnd = currentFunction->generateLabel("while_end");

        // Create condition block and jump to it
        auto condBlock = std::make_shared<Block>()->set(whileCond);
        auto condJump = std::make_shared<Jump>(condBlock);
        statement->addStatement(condJump);
        statement->addStatement(condBlock);

        // Process loop condition
        const auto varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
        const auto variable = currentFunction->findVarAllScopesAndArg(varName);
        if (!variable) {
            throw HLIRException(util::format("Variable '{}' not found in scope", varName));
        }

        // Create conditional branching
        auto conditional = std::make_shared<Conditional>()->set(variable);
        conditional->setTrueLabel(whileBody);
        conditional->setFalseLabel(whileEnd);
        statement->addStatement(conditional);
        
        // Create loop body block
        auto whileBodyBlock = std::make_shared<Block>()->set(whileBody);
        statement->addStatement(whileBodyBlock);
        
        // Create end block for break statements
        auto whileEndBlock = std::make_shared<Block>()->set(whileEnd);
        auto endJump = std::make_shared<Jump>(whileEndBlock);

        // Process loop body
        bool hasBreak = false;
        bool hasReturn = false;
        if (ctx->statementList()) {
            std::tie(hasBreak, hasReturn) = visitStatementList(
                ctx->statementList(), currentFunction, endJump);
        }

        // Add jump back to condition if no break or return
        if (!hasBreak && !hasReturn) {
            statement->addStatement(condJump);
        }

        // Add the end block
        statement->addStatement(whileEndBlock);
    }

    /**
     * @brief Processes a repeat statement
     * 
     * @param ctx The repeat statement context
     * @param currentFunction The current function context
     * @throws HLIRException If the context or statement is null
     */
    void HLIRGenerator::visitRepeatStatement(
        IronParser::RepeatStatementContext *ctx,
        const std::shared_ptr<Function> &currentFunction)
    {
        if (!ctx) {
            throw HLIRException("visitRepeatStatement: Context is null");
        }
        
        const auto statement = currentFunction->getCurrentLocalScope();
        if (!statement) {
            throw HLIRException("visitRepeatStatement: Current scope is null");
        }
        
        // Generate unique labels for loop parts
        const std::string repeatBody = currentFunction->generateLabel("repeat_body");
        const std::string repeatCond = currentFunction->generateLabel("repeat_cond");
        const std::string repeatEnd = currentFunction->generateLabel("repeat_end");
        
        // Create and add body block
        auto bodyBlock = std::make_shared<Block>()->set(repeatBody);
        statement->addStatement(bodyBlock);
        
        // Create end block for break statements
        auto endBlock = std::make_shared<Block>()->set(repeatEnd);
        auto endJump = std::make_shared<Jump>(endBlock);
        
        // Process loop body
        bool hasBreak = false;
        bool hasReturn = false;
        if (ctx->statementList()) {
            std::tie(hasBreak, hasReturn) = visitStatementList(
                ctx->statementList(), currentFunction, endJump);
        }
        
        // Only add condition check if no break or return in body
        if (!hasBreak && !hasReturn) {
            // Create condition block
            auto condBlock = std::make_shared<Block>()->set(repeatCond);
            statement->addStatement(condBlock);
            
            // Process condition
            const auto varName = visitBoolExpr(ctx->boolExpr(), currentFunction);
            const auto variable = currentFunction->findVarAllScopesAndArg(varName);
            if (!variable) {
                throw HLIRException(util::format("Variable '{}' not found in scope", varName));
            }
            
            // Create conditional branching (continue while condition is true)
            auto conditional = std::make_shared<Conditional>()->set(variable);
            conditional->setTrueLabel(repeatBody);  // Loop back if true
            conditional->setFalseLabel(repeatEnd);  // Exit if false
            statement->addStatement(conditional);
        }
        
        // Add the end block
        statement->addStatement(endBlock);
    }

    /**
     * @brief Processes a for loop statement
     * 
     * @param ctx The for statement context
     * @param currentFunction The current function context
     * @throws HLIRException If the context or statement is null
     */
    void HLIRGenerator::visitForStatement(
        IronParser::ForStatementContext *ctx,
        const std::shared_ptr<Function> &currentFunction)
    {
        if (!ctx) {
            throw HLIRException("visitForStatement: Context is null");
        }
        
        const auto statement = currentFunction->getCurrentLocalScope();
        if (!statement) {
            throw HLIRException("visitForStatement: Current scope is null");
        }
        
        // TODO: Implement a proper for loop with initialization, condition, and increment
        throw HLIRException("For loops are not fully implemented yet");
    }
}
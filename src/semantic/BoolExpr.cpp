#include "../headers/SemanticAnalysis.h"

namespace iron
{

    std::pair<std::string, int> SemanticAnalysis::visitBoolExpr(IronParser::BoolExprContext *ctx)
    {
        const auto line = ctx->getStart()->getLine();
        const auto col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentFunction = getCurrentFunction();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            return visitBoolExpr(ctx->boolExpr(0));
        }

        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            auto [leftName, leftType] = visitBoolExpr(ctx->left);
            auto [rightName, rightType] = visitBoolExpr(ctx->right);


            if ((tokenMap::isNumber(leftType) or leftType == tokenMap::TYPE_BOOLEAN) and tokenMap::isNumber(rightType) or
                rightType == tokenMap::TYPE_BOOLEAN)
            {
                if (leftType == tokenMap::TYPE_BOOLEAN or rightType == tokenMap::TYPE_BOOLEAN)
                {
                    return std::pair(rightName, tokenMap::TYPE_BOOLEAN);
                }
                auto procedenceType = tokenMap::getHigherPrecedenceType(leftType, rightType);
                return std::pair(rightName, procedenceType);
            }

            verifyTypesMatch(leftType, rightType, leftName, rightName, line, col, 
                           "The left operator of type is incompatible with the right operator");
        }

        if (ctx->expr())
        {
            return visitExpr(ctx->expr());
        }

        if (ctx->booleanValue)
        {
            return std::pair(ctx->booleanValue->getText(), tokenMap::TYPE_BOOLEAN);
        }

        if (ctx->not_)
        {
            return std::pair(ctx->not_->getText(), tokenMap::TYPE_BOOLEAN);
        }

        if (ctx->number())
        {
            std::string number = ctx->number()->getText();
            int type = determineValueType(number);
            return std::pair(number, type);
        }

        if (ctx->varName)
        {
            const std::string varName = ctx->varName->getText();
            const auto variable = verifyVariableExists(varName, line, col);
            return std::pair(variable->name, variable->type);
        }

        if (ctx->functionCall())
        {
            auto calledFunctionName = ctx->functionCall()->functionName->getText();
            auto calledFunction = verifyFunctionExists(calledFunctionName, line, col);
            visitFunctionCall(ctx->functionCall());
            return std::pair(calledFunctionName, calledFunction->getReturnType());
        }

        throw std::runtime_error("Invalid boolean expression");
    }

} // namespace iron

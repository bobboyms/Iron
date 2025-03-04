#include "../headers/SemanticAnalysis.h"

namespace iron
{
std::pair<std::string, int> SemanticAnalysis::visitExpr(IronParser::ExprContext *ctx)
    {


        auto line = ctx->getStart()->getLine();
        auto col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentFunction = getCurrentFunction();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            return visitExpr(ctx->expr(0));
        }
        if (ctx->left != nullptr && ctx->right != nullptr)
        {
            auto [leftName, leftType] = visitExpr(ctx->left);
            auto [rightName, rightType] = visitExpr(ctx->right);

            if (tokenMap::isNumber(leftType) && tokenMap::isNumber(rightType))
            {
                auto procedenceType = tokenMap::getHigherPrecedenceType(leftType, rightType);
                return std::pair(rightName, procedenceType);
            }
            verifyTypesMatch(leftType, rightType, leftName, rightName, line, col, 
                           "The left operator of type is incompatible with the right operator");
        }
        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            auto variable = verifyVariableExists(varName, line, col);
            return std::pair(variable->name, variable->type);
        }
        if (ctx->number())
        {
            std::string number = ctx->number()->getText();
            int type = determineValueType(number);
            return std::pair(number, type);
        }
        if (ctx->functionCall())
        {
            auto calledFunctionName = ctx->functionCall()->functionName->getText();
            auto calledFunction = verifyFunctionExists(calledFunctionName, line, col);
            visitFunctionCall(ctx->functionCall());
            return std::pair(calledFunctionName, calledFunction->getReturnType());
        }

        throw std::runtime_error("Invalid expression");
    }

} // namespace iron

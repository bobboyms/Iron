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
        else if (ctx->left != nullptr && ctx->right != nullptr)
        {
            auto [leftName, leftType] = visitExpr(ctx->left);
            auto [rightName, rightType] = visitExpr(ctx->right);

            if (tokenMap::isNumber(leftType) && tokenMap::isNumber(rightType))
            {
                auto procedenceType = tokenMap::getHigherPrecedenceType(leftType, rightType);
                return std::pair(rightName, procedenceType);
            }
            else
            {
                throw TypeMismatchException(util::format(
                        "The left operator {} of type {} is incompatible with the right operator {} of type {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(leftName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(leftType), color::BOLD_GREEN),
                        color::colorText(rightName, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(rightType), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }
        else if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
            if (!function)
            {
                throw FunctionNotFoundException("SemanticAnalysis::visitExpr. No current function scope found");
            }
            auto variable = function->findVarAllScopesAndArg(varName);
            if (!variable)
            {
                throw VariableNotFoundException(util::format(
                        "Variable '{}' not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            return std::pair(variable->name, variable->type);
        }
        else if (ctx->number())
        {
            std::string number = ctx->number()->getText();
            int type = tokenMap::determineType(number);
            if (type == tokenMap::REAL_NUMBER)
            {
                type = tokenMap::determineFloatType(number);
            }

            return std::pair(number, type);
        }
        else if (ctx->functionCall())
        {
            auto calledFunctionName = ctx->functionCall()->functionName->getText();
            std::shared_ptr<scope::Function> calledFunction;
            auto functionPtr = currentFunction->findVarAllScopesAndArg(calledFunctionName);
            if (!functionPtr)
            {
                calledFunction = scopeManager->getFunctionDeclarationByName(calledFunctionName);
                if (!calledFunction)
                {
                    // throw ScopeNotFoundException("SemanticAnalysis::visitExpr. No current function scope found");
                    throw FunctionNotFoundException(
                            util::format("Function {} not found.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(calledFunctionName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }
            }
            else
            {
                calledFunction = functionPtr->function;
            }

            visitFunctionCall(ctx->functionCall());
            return std::pair(calledFunctionName, calledFunction->getReturnType());
        }

        throw std::runtime_error("Invalid expression");
    }

} // namespace iron

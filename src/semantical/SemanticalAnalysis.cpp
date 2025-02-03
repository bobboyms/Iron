#include "../headers/SemanticalAnalysis.h"

#include <iostream>

namespace iron
{
    // Construtor
    SemanticalAnalysis::SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<scope::ScopeManager> scopeManager, std::vector<std::string> sourceLines)
        : parser(parser), scopeManager(std::move(scopeManager)), sourceLines(sourceLines)
    {
    }

    // Destrutor
    SemanticalAnalysis::~SemanticalAnalysis()
    {
    }

    // Método principal para análise semântica
    void SemanticalAnalysis::analyze()
    {
        IronParser::ProgramContext *programContext = parser->program();

        for (auto child : programContext->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        parser->reset();
        for (auto child : parser->program()->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionBody(funcDecl);
            }
        }
    }

    void SemanticalAnalysis::visitStatementList(IronParser::StatementListContext *ctx)
    {
        auto function = getCurrentFunction();

        function->enterLocalScope(std::make_shared<scope::Statements>());
        for (auto child : ctx->children)
        {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration);
            }
            if (auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall);
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
            }
        }
        function->exitLocalScope();
    }

    void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext *ctx)
    {

        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        int col = ctx->getStart()->getCharPositionInLine();
        int line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        const std::string scopeName = scopeManager->currentScopeName();

        auto currentFunction = getCurrentFunction();

        auto existingSymbol = currentFunction->findVarCurrentScopeAndArg(varName);

        if (existingSymbol)
        {
            throw VariableRedefinitionException(util::format(
                "Variable {} already declared. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeName, color::BOLD_YELLOW)));
        }

        auto localScope = currentFunction->getCurrentLocalScope();
        if (!localScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitVarDeclaration. Local scope not found");
        }

        auto statement = std::dynamic_pointer_cast<scope::Statements>(localScope);
        if (!statement)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitVarDeclaration. Local scope is not a statement");
        }

        statement->addVariable(varName, tokenMap::getTokenType(varType));

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
        else
        {

            throw UninitializedVariableException(util::format(
                "Variable {} has not been initialized.\n"
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }
    }

    void SemanticalAnalysis::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {

        int col = ctx->getStart()->getCharPositionInLine();
        int line = ctx->getStart()->getLine();

        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        std::string varName = ctx->varName->getText();

        auto function = getCurrentFunction();

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
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        // Implementação adicional conforme necessário
    }

    std::pair<std::string, int> SemanticalAnalysis::visitExpr(IronParser::ExprContext *ctx)
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
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }
        }
        else if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
            if (!function)
            {
                throw FunctionNotFoundException("SemanticalAnalysis::visitExpr. No current function scope found");
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
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
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
                    // throw ScopeNotFoundException("SemanticalAnalysis::visitExpr. No current function scope found");
                    throw FunctionNotFoundException(util::format(
                        "Function {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(calledFunctionName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
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

    std::pair<std::string, std::string> SemanticalAnalysis::getCodeLineAndCaretLine(int line, int col, int steps)
    {
        std::string codeLine;
        if (line > 0 && line <= (int)sourceLines.size())
        {
            codeLine = sourceLines[line - 1];
        }
        else
        {
            throw std::runtime_error("Unknown line (out of range)");
        }

        // Cria a linha de marcação
        std::string caretLine(col + steps, ' ');
        caretLine += '^';

        return std::make_pair(caretLine, codeLine);
    }

    void SemanticalAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 2);

        if (ctx->dataFormat())
        {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDeclaration->varName->getText();
                std::string value = ctx->dataFormat()->getText();
                std::string varType = varDeclaration->varTypes()->getText();

                if (tokenMap::determineType(value) == tokenMap::REAL_NUMBER)
                {
                    if (!(tokenMap::getTokenType(varType) == tokenMap::determineFloatType(value)))
                    {
                        auto valueType = tokenMap::getTokenText(tokenMap::determineFloatType(value));

                        // Lançando exceção com a linha do código em destaque
                        throw TypeMismatchException(util::format(
                            "The variable {} type is {} and the value {} type is {}.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"  // Exibe a linha de código
                            "{}\n", // Exibe a setinha '^'
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(value, color::BOLD_BLUE),
                            color::colorText(valueType, color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                            codeLine,
                            caretLine));
                    }
                }
                else
                {
                    if (tokenMap::getTokenType(varType) != tokenMap::determineType(value))
                    {
                        auto valueType = tokenMap::getTokenText(tokenMap::determineType(value));

                        throw TypeMismatchException(util::format(
                            "The variable {} type is {} and the value {} type is {}.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(value, color::BOLD_BLUE),
                            color::colorText(valueType, color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                            codeLine,
                            caretLine));
                    }
                }
            }
        }

        if (ctx->arrowFunctionInline())
        {
            visitArrowFunctionInline(ctx->arrowFunctionInline());
        }

        if (ctx->arrowFunctionBlock())
        {
            visitArrowFunctionBlock(ctx->arrowFunctionBlock());
        }

        if (ctx->expr())
        {
            visitExpr(ctx->expr());
        }
    }

    void SemanticalAnalysis::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
        const int line = ctx->getStart()->getLine();
        const int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentFunction = getCurrentFunction();

        if (ctx->dataFormat())
        {
            auto value = ctx->dataFormat()->getText();
            auto valueType = tokenMap::determineType(value);
            if (valueType == tokenMap::REAL_NUMBER)
            {
                valueType = tokenMap::determineFloatType(value);
            }

            if (valueType != currentFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                    "The Function {} return type {} is incompatible with the value {} of type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(value, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }
        }

        if (ctx->varName)
        {
            auto variable = currentFunction->findVarAllScopesAndArg(ctx->varName->getText());
            if (!variable)
            {
                throw VariableNotFoundException(util::format(
                    "Variable '{}' not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(ctx->varName->getText(), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            if (variable->type == tokenMap::FUNCTION)
            {
                if (variable->type != currentFunction->getReturnType())
                {
                    throw TypeMismatchException(util::format(
                        "The Function {} return type {} is incompatible with the operator {} of type {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                        color::colorText(variable->name, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }
            }
            else if (variable->type != currentFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                    "The Function {} return type {} is incompatible with the operator {} of type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(variable->name, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            currentFunction->updateReturnTokenStatusToFound();
        }
        else if (ctx->expr())
        {
            auto [_, typeExpr] = visitExpr(ctx->expr());

            if (typeExpr != currentFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                    "The Function {} return type {} is incompatible with result of the expression type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(typeExpr), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            currentFunction->updateReturnTokenStatusToFound();
        }
        else if (ctx->functionCall())
        {
            auto functionCallName = ctx->functionCall()->functionName->getText();
            auto calledFunction = scopeManager->getFunctionDeclarationByName(functionCallName);
            if (!calledFunction)
            {
                throw FunctionNotFoundException(util::format(
                    "Function {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(functionCallName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            if (calledFunction->getReturnType() != currentFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                    "The Function {} return type {} is incompatible with the Function {} return type {}.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(functionCallName, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            visitFunctionCall(ctx->functionCall());
            currentFunction->updateReturnTokenStatusToFound();
        }
    }

}
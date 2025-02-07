#include "../headers/SemanticAnalysis.h"

#include <iostream>
#include <utility>

namespace fs = std::filesystem;

namespace iron
{
    // Construtor
    SemanticAnalysis::SemanticAnalysis(std::shared_ptr<IronParser> parser,
                                       std::unique_ptr<scope::ScopeManager> scopeManager,
                                       const std::vector<std::string> &sourceLines) :
        parser(std::move(parser)), scopeManager(std::move(scopeManager)), sourceLines(sourceLines)
    {
    }

    // Destrutor
    SemanticAnalysis::~SemanticAnalysis() = default;

    // Método principal para análise semântica
    void SemanticAnalysis::analyze()
    {
        IronParser::ProgramContext *programContext = parser->program();

        std::vector<IronParser::ImportStatementContext*> imports = programContext->importStatement();
        for (auto importStmt : programContext->importStatement()) {
            visitImportStatement(importStmt);
        }


        for (const auto child: programContext->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        parser->reset();
        for (const auto child: parser->program()->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionBody(funcDecl);
            }
        }
    }

    void SemanticAnalysis::visitStatementList(const IronParser::StatementListContext *ctx)
    {
        const int col = ctx->getStart()->getCharPositionInLine();
        const int line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, -7);

        const auto currentFunction = getCurrentFunction();

        bool hasReturn = false;
        currentFunction->enterLocalScope(std::make_shared<scope::Statements>());
        for (const auto child: ctx->children)
        {

            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration);
            }
            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall);
            }
            if (const auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
            }
            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression);
            }
            if (const auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
                hasReturn = true;
            }
        }

        if (currentFunction->getReturnType() != tokenMap::VOID && !hasReturn)
        {

            auto funcName = currentFunction->getName();
            auto scopeName = currentFunction->getName();
            if (currentFunction->getAlias())
            {
                funcName = currentFunction->getAlias()->name;
                auto upperFunction = currentFunction->getUpperFunction();
                while (upperFunction)
                {
                    scopeName = upperFunction->getName();
                    upperFunction = upperFunction->getUpperFunction();
                }
            }
            throw ReturnNotFoundException(util::format(
                    "The Function {} returns an {} type. But you are not returning any value in the function body.\n"
                    "To do this, use the keyword '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n",
                    color::colorText(funcName, color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText("return", color::BOLD_BLUE), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeName, color::BOLD_YELLOW), codeLine));
        }
    }

    void SemanticAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext *ctx)
    {
        const std::string varName = ctx->varName->getText();
        const std::string varType = ctx->varTypes()->getText();

        const int col = ctx->getStart()->getCharPositionInLine();
        const int line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        const std::string scopeName = scopeManager->currentScopeName();

        const auto currentFunction = getCurrentFunction();

        if (auto existingSymbol = currentFunction->findVarCurrentScopeAndArg(varName))
        {
            throw VariableRedefinitionException(util::format("Variable {} already declared. Line: {}, Scope: {}",
                                                             color::colorText(varName, color::BOLD_GREEN),
                                                             color::colorText(std::to_string(line), color::YELLOW),
                                                             color::colorText(scopeName, color::BOLD_YELLOW)));
        }

        const auto localScope = currentFunction->getCurrentLocalScope();
        if (!localScope)
        {
            throw ScopeNotFoundException("SemanticAnalysis::visitVarDeclaration. Local scope not found");
        }

        const auto statement = std::dynamic_pointer_cast<scope::Statements>(localScope);
        if (!statement)
        {
            throw ScopeNotFoundException("SemanticAnalysis::visitVarDeclaration. Local scope is not a statement");
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
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    void SemanticAnalysis::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {
        const int col = ctx->getStart()->getCharPositionInLine();
        const int line = ctx->getStart()->getLine();

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
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }

        // Implementação adicional conforme necessário
    }
    void SemanticAnalysis::visitImportStatement(IronParser::ImportStatementContext *ctx)
    {
        fs::path currentPath = fs::current_path();
        std::cout << "Diretório de trabalho: " << currentPath << "\n";
        if (ctx->qualifiedName())
        {
            util::printf("{}\n",ctx->qualifiedName()->getText());
        }
    }


    std::pair<std::string, std::string> SemanticAnalysis::getCodeLineAndCaretLine(const int line, const int col,
                                                                                  const int steps)
    {
        std::string codeLine;
        if (line > 0 && line <= static_cast<int>(sourceLines.size()))
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

    void SemanticAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    {
        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 2);

        if (ctx->dataFormat())
        {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const std::string varName = varDeclaration->varName->getText();
                const std::string value = ctx->dataFormat()->getText();
                const std::string varType = varDeclaration->varTypes()->getText();

                if (tokenMap::determineType(value) == tokenMap::REAL_NUMBER)
                {
                    if (tokenMap::getTokenType(varType) != tokenMap::determineFloatType(value))
                    {
                        const auto valueType = tokenMap::getTokenText(tokenMap::determineFloatType(value));

                        // Lançando exceção com a linha do código em destaque
                        throw TypeMismatchException(util::format(
                                "The variable {} type is {} and the value {} type is {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n" // Exibe a linha de código
                                "{}\n", // Exibe a setinha '^'
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(varType, color::BOLD_GREEN), color::colorText(value, color::BOLD_BLUE),
                                color::colorText(valueType, color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                caretLine));
                    }
                }
                else
                {
                    if (tokenMap::getTokenType(varType) != tokenMap::determineType(value))
                    {
                        const auto valueType = tokenMap::getTokenText(tokenMap::determineType(value));

                        throw TypeMismatchException(util::format(
                                "The variable {} type is {} and the value {} type is {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n"
                                "{}\n",
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(varType, color::BOLD_GREEN), color::colorText(value, color::BOLD_BLUE),
                                color::colorText(valueType, color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
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

    void SemanticAnalysis::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
        const int line = ctx->getStart()->getLine();
        const int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        const auto currentFunction = getCurrentFunction();

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
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }

        if (ctx->varName)
        {
            const auto variable = currentFunction->findVarAllScopesAndArg(ctx->varName->getText());
            if (!variable)
            {
                throw VariableNotFoundException(util::format(
                        "Variable '{}' not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(ctx->varName->getText(), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
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
                            color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()),
                                             color::BOLD_GREEN),
                            color::colorText(variable->name, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
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
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
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
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            currentFunction->updateReturnTokenStatusToFound();
        }
        else if (ctx->functionCall())
        {
            const auto functionCallName = ctx->functionCall()->functionName->getText();
            const auto calledFunction = scopeManager->getFunctionDeclarationByName(functionCallName);
            if (!calledFunction)
            {
                throw FunctionNotFoundException(util::format(
                        "Function {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(functionCallName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
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
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            visitFunctionCall(ctx->functionCall());
            currentFunction->updateReturnTokenStatusToFound();
        }
    }
} // namespace iron

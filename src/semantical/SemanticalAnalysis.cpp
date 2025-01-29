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
        auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
        if (!function)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitStatementList. Current scope not found");
        }

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

        auto currentFunction = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
        if (!currentFunction)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitStatementList. Current scope not found");
        }

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

        // if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        // {
        //     auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
        // }
        // else
        // {
        //     statement->addVariable(varName, tokenMap::getTokenType(varType));
        // }

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

        auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
        if (!function)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitVarAssignment. Current scope not found");
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

        // Implementação adicional conforme necessário
    }

    std::pair<std::string, int> SemanticalAnalysis::visitExpr(IronParser::ExprContext *ctx)
    {

        auto line = ctx->getStart()->getLine();
        auto col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitExpr. No current scope found");
        }

        auto currentFunction = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitExpr. No current function found");
        }

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
                throw ScopeNotFoundException("SemanticalAnalysis::visitExpr. No current function scope found");
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
                    throw ScopeNotFoundException("SemanticalAnalysis::visitExpr. No current function scope found");
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
        // Exemplo para ilustrar como obter linha e coluna
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

    void SemanticalAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();

        auto globalScope = scopeManager->getFunctionDeclarationByName(functionName);
        if (globalScope)
        {

            throw FunctionRedefinitionException(util::format(
                "Function {} already declared."
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText("Global", color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();

        int returnType = tokenMap::VOID;
        if (ctx->functionSignature()->functionReturnType())
        {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            returnType = tokenMap::getTokenType(type);
        }

        auto function = std::make_shared<scope::Function>(functionName, funcArgs, returnType);
        scopeManager->addFunctionDeclaration(function);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature());
        }
    }

    void SemanticalAnalysis::visitFunctionBody(IronParser::FunctionDeclarationContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();
        auto function = scopeManager->getFunctionDeclarationByName(functionName);
        if (!function)
        {
            throw FunctionRedefinitionException(util::format(
                "Function {} not found."
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText("Global", color::BOLD_YELLOW),
                codeLine,
                caretLine));
        }

        scopeManager->enterScope(function);

        for (auto child : ctx->children)
        {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext *>(child))
            {

                visitStatementList(statementList);
            }
        }

        scopeManager->exitScope();
    }

    void SemanticalAnalysis::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext *>(child))
            {
                visitFunctionArgs(functionArgs);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionArgs(IronParser::FunctionArgsContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(functionArg);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionArg(IronParser::FunctionArgContext *ctx)
    {
        std::string argName = ctx->varName->getText();
        std::string argType = ctx->varTypes()->getText();
        int line = ctx->getStart()->getLine();

        const auto function = scopeManager->currentFunctionDeclarationBy();
        if (!function)
        {
            throw ScopeNotFoundException(util::format(
                "visitFunctionArg. Scope current not found. Line: {}",
                color::colorText(std::to_string(line), color::BOLD_GREEN)));
        }

        auto arg = function->getArgByName(argName);
        if (arg)
        {
            throw VariableRedefinitionException(util::format(
                "Function arg {} already declared. Line: {}, Scope: fn {}",
                color::colorText(argName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(function->getFunctionName(), color::BOLD_YELLOW)));
        }

        auto argsList = function->getArgs();
        argsList->push_back(std::make_shared<scope::FunctionArg>(argName, tokenMap::getTokenType(argType)));

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
    }

    void SemanticalAnalysis::visitFunctionCall(IronParser::FunctionCallContext *ctx)
    {

        std::string functionName = ctx->functionName->getText();
        int line = ctx->getStart()->getLine();

        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCall. Current scope not found");
        }

        auto function = std::dynamic_pointer_cast<scope::Function>(currentScope);
        if (!function)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCall. Current scope is not a function");
        }

        // Verificar argumentos e outras validações conforme necessário
        // Exemplo:
        if (ctx->functionCallArgs())
        {
            visitFunctionCallArgs(ctx->functionCallArgs());
        }

        // Implementação adicional conforme necessário
    }

    void SemanticalAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                visitFunctionCallArg(functionCallArg);
            }
        }
    }

    void SemanticalAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx)
    {
        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCallArg. Current scope not found");
        }

        auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope);
        if (!currentFunction)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCallArg. Current function not found");
        }

        auto argName = ctx->varName->getText();

        if (auto functionCall = dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent->parent))
        {
            auto functionName = functionCall->functionName->getText();

            std::shared_ptr<scope::Function> calledFunction;
            auto functionPtr = currentFunction->findVarCurrentScopeAndArg(functionName);
            if (!functionPtr)
            {

                functionPtr = currentFunction->findVarAllScopesAndArg(functionName);
                if (!functionPtr)
                {
                    auto scope = scopeManager->getScopeByName(functionName);
                    if (!scope)
                    {

                        util::printf("fff", "");
                        throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCallArg. Current scope not found");
                    }

                    auto function = std::dynamic_pointer_cast<scope::Function>(scope);
                    if (!function)
                    {
                        throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCallArg. Current function not found");
                    }

                    calledFunction = function;
                }
                else
                {
                    calledFunction = functionPtr->function;
                    if (!calledFunction)
                    {
                        throw SemanticException("SemanticalAnalysis::visitFunctionCallArg. Invalid function ptr");
                    }
                    functionName = functionPtr->name;
                }
            }
            else
            {
                calledFunction = functionPtr->function;
                if (!calledFunction)
                {
                    throw SemanticException("SemanticalAnalysis::visitFunctionCallArg. Invalid function ptr");
                }
                functionName = functionPtr->name;
            }

            auto funcArg = calledFunction->getArgByName(argName);
            if (!funcArg)
            {
                throw FunctionArgNotFoundException(util::format(
                    "The argument {} not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(argName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                    codeLine,
                    caretLine));
            }

            if (ctx->dataFormat())
            {

                auto value = ctx->dataFormat()->getText();
                auto valueType = tokenMap::determineType(value);
                if (valueType == tokenMap::REAL_NUMBER)
                {
                    valueType = tokenMap::determineFloatType(value);
                }

                if (valueType != funcArg->type)
                {

                    throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the value {} type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"  // Exibe a linha de código
                        "{}\n", // Exibe a setinha '^'
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(value, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }
            }

            if (ctx->anotherVarName)
            {
                auto varName = ctx->anotherVarName->getText();
                auto variable = currentFunction->findVarAllScopesAndArg(varName);
                if (!variable)
                {
                    throw VariableNotFoundException(util::format(
                        "The variable {} not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }

                if (variable->type != funcArg->type)
                {
                    throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the variable {} type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"  // Exibe a linha de código
                        "{}\n", // Exibe a setinha '^'
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(variable->name, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }
            }

            if (ctx->functionCall())
            {
                auto calledFunctionName = ctx->functionCall()->functionName->getText();
                auto calledFunction = scopeManager->getFunctionDeclarationByName(calledFunctionName);
                if (!calledFunction)
                {
                    auto functionPtr = currentFunction->findVarAllScopesAndArg(calledFunctionName);
                    if (!functionPtr)
                    {
                        util::printf("xxx", "");
                        throw ScopeNotFoundException("SemanticalAnalysis::visitFunctionCallArg. No current function scope found");
                    }

                    calledFunction = functionPtr->function;
                }

                if (funcArg->type != calledFunction->getReturnType())
                {
                    throw TypeMismatchException(util::format(
                        "The function argument {} type is {} and the function {} return type is {}.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"  // Exibe a linha de código
                        "{}\n", // Exibe a setinha '^'
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(funcArg->type), color::BOLD_GREEN),
                        color::colorText(calledFunction->getName(), color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(functionName, color::BOLD_YELLOW),
                        codeLine,
                        caretLine));
                }

                visitFunctionCall(ctx->functionCall());
            }
        }

        // if (ctx->varName)
        // {
        // }

        // if (ctx->functionCall())
        // {
        //     visitFunctionCall(ctx->functionCall());
        // }

        // Implementação adicional conforme necessário
    }

    std::shared_ptr<scope::Function> SemanticalAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx)
    {

        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitArrowFunctionInline. Current scope not found");
        }

        auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope);
        if (!currentFunction)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitArrowFunctionInline. Current function not found");
        }

        if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            auto varName = varDeclaration->varName->getText();
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();
            int returnType = tokenMap::VOID;
            if (ctx->functionSignature()->functionReturnType())
            {
                std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                returnType = tokenMap::getTokenType(type);
            }

            auto arrowFunction = std::make_shared<scope::Function>(alias, funcArgs, returnType);
            scopeManager->addFunctionDeclaration(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            auto currentStatement = std::dynamic_pointer_cast<scope::Statements>(currentFunction->getCurrentLocalScope());
            if (!currentStatement)
            {
                throw ScopeNotFoundException("SemanticalAnalysis::visitArrowFunctionInline. Current statement not found");
            }

            currentStatement->addFunctionAlias(varName, arrowFunction);
            arrowFunction->setUpperFunction(currentFunction);

            scopeManager->enterScope(arrowFunction);
            if (ctx->expr())
            {
                visitExpr(ctx->expr());
            }
            scopeManager->exitScope();
            // currentFunction->exitLocalScope();

            return arrowFunction;
        }

        throw SemanticException("SemanticalAnalysis::visitArrowFunctionInline error.");
    }

    std::shared_ptr<scope::Function> SemanticalAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx)
    {
        int line = ctx->getStart()->getLine();
        int col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        auto currentScope = scopeManager->currentScope();
        if (!currentScope)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitArrowFunctionInline. Current scope not found");
        }

        auto currentFunction = std::dynamic_pointer_cast<scope::Function>(currentScope);
        if (!currentFunction)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitArrowFunctionInline. Current function not found");
        }

        if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            auto varName = varDeclaration->varName->getText();
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();
            int returnType = tokenMap::VOID;
            if (ctx->functionSignature()->functionReturnType())
            {
                std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
                returnType = tokenMap::getTokenType(type);
            }

            auto arrowFunction = std::make_shared<scope::Function>(alias, funcArgs, returnType);
            scopeManager->addFunctionDeclaration(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature());
            }

            auto currentStatement = std::dynamic_pointer_cast<scope::Statements>(currentFunction->getCurrentLocalScope());
            if (!currentStatement)
            {
                throw ScopeNotFoundException("SemanticalAnalysis::visitArrowFunctionInline. Current statement not found");
            }

            currentStatement->addFunctionAlias(varName, arrowFunction);
            arrowFunction->setUpperFunction(currentFunction);

            scopeManager->enterScope(arrowFunction);
            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList());
            }
            scopeManager->exitScope();

            return arrowFunction;
        }

        throw SemanticException("SemanticalAnalysis::visitArrowFunctionInline error.");
    }

    void SemanticalAnalysis::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
        // Implementação da declaração de return
        // Exemplo:
        if (ctx->expr())
        {
            visitExpr(ctx->expr());
        }
        else if (ctx->functionCall())
        {
            visitFunctionCall(ctx->functionCall());
        }

        // Implementação adicional conforme necessário
    }
}
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

        // Processa todas as declarações no programa
        for (auto child : programContext->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
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
        // Implementação da declaração de variável
        // Exemplo:
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();
        int line = ctx->getStart()->getLine();

        const std::string scopeName = scopeManager->currentScopeName();

        auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
        if (!function)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitStatementList. Current scope not found");
        }

        auto existingSymbol = function->findVarAllScopesAndArg(varName);

        if (existingSymbol)
        {
            throw VariableRedefinitionException(util::format(
                "Variable {} already declared. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeName, color::BOLD_YELLOW)));
        }

        auto localScope = function->getCurrentLocalScope();
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
        //     scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr, {}, alias});
        // }
        // else
        // {
        //     scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr});
        // }

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
        else
        {
            throw UninitializedVariableException(util::format(
                "Variable {} has not been initialized. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
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
        // Implementação da expressão
        // Esta é uma implementação simplificada e deve ser adaptada conforme a lógica da sua análise semântica
        auto line = ctx->getStart()->getLine();
        auto col = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (auto child : ctx->children)
            {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
                {
                    return visitExpr(subExpr);
                }
            }
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
                throw ScopeNotFoundException("No current function scope found");
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
            return std::pair(number, type);
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

        auto globalScope = scopeManager->getScopeByName(functionName);
        if (globalScope)
        {
            // throw FunctionRedefinitionException(util::format(
            //     "Function {} already declared. Line: {}, Scope: {}",
            //     color::colorText(functionName, color::BOLD_GREEN),
            //     color::colorText(std::to_string(line), color::YELLOW),
            //     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));

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

        std::vector<std::shared_ptr<scope::FunctionArg>> funcArgs = {};

        int returnType = 0;
        if (ctx->functionSignature()->functionReturnType())
        {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            returnType = tokenMap::getTokenType(type);
        }
        else
        {
            returnType = tokenMap::VOID;
        }

        auto function = std::make_shared<scope::Function>(functionName, funcArgs, returnType);

        scopeManager->enterScope(function);
        // printf("Function name: %s\n", functionName.c_str());

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature());
        }

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

        const auto scope = scopeManager->currentScope();
        if (!scope)
        {
            throw ScopeNotFoundException(util::format(
                "visitFunctionArg. Scope scope not found. Line: {}",
                color::colorText(std::to_string(line), color::BOLD_GREEN)));
        }

        auto function = std::dynamic_pointer_cast<scope::Function>(scope);
        if (!function)
        {
            throw ScopeNotFoundException(util::format(
                "visitFunctionArg. Scope is not a function. Line: {}",
                color::colorText(std::to_string(line), color::BOLD_GREEN)));
        }

        auto arg = function->getArgByName(argName);
        if (arg)
        {
            throw VariableRedefinitionException(util::format(
                "Function arg {} already declared. Line: {}, Scope: fn {}",
                color::colorText(argName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scope->getName(), color::BOLD_YELLOW)));
        }

        function->getArgs().push_back(std::make_shared<scope::FunctionArg>(argName, tokenMap::getTokenType(argType)));

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
    }

    void SemanticalAnalysis::visitFunctionCall(IronParser::FunctionCallContext *ctx)
    {
        // Implementação da chamada de função
        // Exemplo simplificado:

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

        // auto calledFunction = function->findFuncCallAllScopes(functionName);
        // if (!calledFunction)
        // {
        //     calledFunction = std::dynamic_pointer_cast<scope::Function>(scopeManager->getScopeByName(functionName));
        //     if (!calledFunction)
        //     {
        //         throw FunctionNotFoundException(util::format(
        //             "Function '{}' not found. Line: {}, Scope: {}",
        //             color::colorText(functionName, color::BOLD_GREEN),
        //             color::colorText(std::to_string(line), color::YELLOW),
        //             color::colorText(
        //                 util::format("{} {}",
        //                              tokenMap::getTokenText(tokenMap::FUNCTION),
        //                              currentScope->getName()),
        //                 color::BOLD_YELLOW)));
        //     }
        // }

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

        if (ctx->varName)
        {
        }

        if (ctx->functionCall())
        {
            visitFunctionCall(ctx->functionCall());
        }

        // Implementação adicional conforme necessário
    }

    void SemanticalAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx)
    {
        // Implementação da arrow function inline
        // Exemplo simplificado:
        // Processar conforme a lógica da sua análise semântica

        // Placeholder:
        // Você pode implementar a lógica específica aqui
    }

    void SemanticalAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx)
    {
        // Implementação da arrow function com bloco
        // Exemplo simplificado:
        // Processar conforme a lógica da sua análise semântica

        // Placeholder:
        // Você pode implementar a lógica específica aqui
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
#include "../headers/SemanticalAnalysis.h"

#include <iostream>

namespace iron
{
    // Construtor
    SemanticalAnalysis::SemanticalAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<scope::ScopeManager> scopeManager)
        : parser(parser), scopeManager(std::move(scopeManager))
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
    }

    void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext *ctx)
    {
        // Implementação da declaração de variável
        // Exemplo:
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();
        int line = ctx->getStart()->getLine();

        const std::string scopeName = scopeManager->currentScopeName();

        // if (existingSymbol.has_value())
        // {
        //     throw VariableRedefinitionException(util::format(
        //         "Variable {} already declared. Line: {}, Scope: {}, Type: {}",
        //         color::colorText(varName, color::BOLD_GREEN),
        //         color::colorText(std::to_string(line), color::YELLOW),
        //         color::colorText(scopeName, color::BOLD_YELLOW),
        //         color::colorText(std::to_string(existingSymbol->type), color::CYAN)));
        // }

        // if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        // {
        //     auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
        //     scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr, {}, alias});
        // }
        // else
        // {
        //     scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr});
        // }

        // if (ctx->assignment())
        // {
        //     visitAssignment(ctx->assignment());
        // }
        // else
        // {
        //     throw UninitializedVariableException(util::format(
        //         "Variable {} has not been initialized. Line: {}, Scope: {}",
        //         color::colorText(varName, color::BOLD_GREEN),
        //         color::colorText(std::to_string(line), color::YELLOW),
        //         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
        // }
    }

    void SemanticalAnalysis::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {
        std::string varName = ctx->varName->getText();
        int line = ctx->getStart()->getLine();

        auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
        if (!function)
        {
            throw ScopeNotFoundException("SemanticalAnalysis::visitVarAssignment. Current scope not found");
        }

        auto variable = function->findVarAllScopesAndArg(varName);

        if (!variable)
        {
            throw VariableNotFoundException(util::format(
                "Variable '{}' not found. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    util::format("{} {}",
                                 tokenMap::getTokenText(tokenMap::FUNCTION),
                                 scopeManager->currentScope()->getName()),
                    color::BOLD_YELLOW)));
        }

        // Implementação adicional conforme necessário
    }

    void SemanticalAnalysis::visitExpr(IronParser::ExprContext *ctx)
    {
        // Implementação da expressão
        // Esta é uma implementação simplificada e deve ser adaptada conforme a lógica da sua análise semântica

        // Exemplo:
        if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            auto function = std::dynamic_pointer_cast<scope::Function>(scopeManager->currentScope());
            if (!function)
            {
                throw ScopeNotFoundException("SemanticalAnalysis::visitExpr. Current scope not found");
            }

            auto variable = function->findVarAllScopesAndArg(varName);
            if (!variable)
            {
                throw VariableNotFoundException(util::format(
                    "Variable '{}' not found. Line: {}",
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(std::to_string(ctx->getStart()->getLine()), color::YELLOW)));
            }

            // Processamento adicional conforme necessário
        }

        if (ctx->number())
        {
            // Processamento de números literais
            // Exemplo:
            std::string numberLiteral = ctx->number()->getText();
            // Validar ou armazenar conforme necessário
        }

        if (ctx->functionCall())
        {
            // Processamento de chamadas de função
            visitFunctionCall(ctx->functionCall());
        }

        // Implementar lógica adicional para expressões complexas
    }

    void SemanticalAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    {
        // Implementação da atribuição
        // Exemplo:
        // Processar a expressão à direita da atribuição
        if (ctx->expr())
        {
            visitExpr(ctx->expr());
        }
    }

    void SemanticalAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        if (!ctx->functionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->functionName->getText();
        int line = ctx->functionName->getLine();

        auto globalScope = scopeManager->getScopeByName(functionName);
        if (globalScope)
        {
            throw FunctionRedefinitionException(util::format(
                "Function {} already declared. Line: {}, Scope: {}",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
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

        auto myFunction = std::make_shared<scope::Function>(functionName, funcArgs, returnType);

        scopeManager->enterScope(myFunction);

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
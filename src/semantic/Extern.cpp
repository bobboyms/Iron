#include "../headers/SemanticAnalysis.h"

namespace iron
{

    void SemanticAnalysis::visitExternBlock(IronParser::ExternBlockContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::ExternFunctionDeclarationContext *>(child))
            {
                visitExternFunctionDeclaration(funcDecl);
            }
        }
    }

    void SemanticAnalysis::visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx)
    {

        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 1);

        if (!ctx->exterFunctionName)
        {
            throw std::runtime_error("Function name is missing.");
        }

        std::string functionName = ctx->exterFunctionName->getText();
        auto funcArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();


        int returnType = tokenMap::VOID;
        if (ctx->functionReturnType())
        {
            const std::string type = ctx->functionReturnType()->varTypes()->getText();
            returnType = tokenMap::getTokenType(type);
        }

        const auto function = std::make_shared<scope::Function>(functionName, funcArgs, returnType);
        function->changeToExternal();
        if (ctx->varied)
        {
            function->changeToVariedArguments();
        }
        scopeManager->addFunctionDeclaration(function);
        function->changeToExternal();
        if (ctx->varied)
        {
            function->changeToVariedArguments();
        }

        if (ctx->externFunctionArgs())
        {
            visitExternFunctionArgs(ctx->externFunctionArgs(), funcArgs);
        }




    }

    void SemanticAnalysis::visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx, std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList)
    {
        for (const auto arg: ctx->externFunctionArg())
        {
            visitExternFunctionArg(arg, argsList);
        }
    }

    void SemanticAnalysis::visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx, std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList)
    {
        std::string argName = ctx->varName->getText();
        const std::string argType = ctx->cTypes()->getText();
        const uint line = ctx->getStart()->getLine();

        const auto currentFunction = scopeManager->currentFunctionDeclaration();
        if (!currentFunction)
        {
            throw ScopeNotFoundException(util::format("visitFunctionArg. Scope current not found. Line: {}",
                                                      color::colorText(std::to_string(line), color::BOLD_GREEN)));
        }

        if (auto arg = currentFunction->getArgByName(argName))
        {
            throw VariableRedefinitionException(util::format(
                    "Function arg {} already declared. Line: {}, Scope: fn {}",
                    color::colorText(argName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW)));
        }

        argsList->push_back(std::make_shared<scope::FunctionArg>(argName, tokenMap::getTokenType(argType)));


    }

} // namespace iron

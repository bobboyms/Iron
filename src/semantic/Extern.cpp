#include "../headers/SemanticAnalysis.h"

namespace iron
{
    /**
     * @brief Processes an extern block containing external function declarations
     * 
     * Iterates through all children of the extern block and processes each
     * external function declaration.
     * 
     * @param ctx The extern block context from the parser
     */
    void SemanticAnalysis::visitExternBlock(IronParser::ExternBlockContext *ctx)
    {
        for (const auto& child : ctx->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::ExternFunctionDeclarationContext*>(child))
            {
                visitExternFunctionDeclaration(funcDecl);
            }
        }
    }

    /**
     * @brief Processes an external function declaration
     * 
     * Creates a function declaration for an external function, setting its return type
     * and marking it as external. Also processes any function arguments.
     * 
     * @param ctx The extern function declaration context from the parser
     * @throws std::runtime_error if the function name is missing
     */
    void SemanticAnalysis::visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx)
    {
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 1);

        // Verify function name exists
        if (!ctx->exterFunctionName)
        {
            throw std::runtime_error(util::format(
                "External function declaration is missing a name.\n"
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(std::to_string(lineNumber), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                codeLine, caretLine));
        }

        // Extract function name and create argument list
        const std::string functionName = ctx->exterFunctionName->getText();
        auto functionArgs = std::make_shared<std::vector<std::shared_ptr<scope::FunctionArg>>>();

        // Determine return type (default to void)
        int returnType = tokenMap::VOID;
        if (ctx->functionReturnType())
        {
            const std::string typeName = ctx->functionReturnType()->varTypes()->getText();
            returnType = tokenMap::getTokenType(typeName);
        }

        // Create the function object
        auto function = std::make_shared<scope::Function>(functionName, functionArgs, returnType);
        
        // Mark as external
        function->changeToExternal();
        
        // Check if it supports varied arguments
        if (ctx->varied)
        {
            function->changeToVariedArguments();
        }
        
        // Add to scope manager
        scopeManager->addFunctionDeclaration(function);

        // Process function arguments if present
        if (ctx->externFunctionArgs())
        {
            visitExternFunctionArgs(ctx->externFunctionArgs(), functionArgs);
        }
    }

    /**
     * @brief Processes the arguments of an external function
     * 
     * Iterates through and processes each argument of an external function.
     * 
     * @param ctx The extern function arguments context from the parser
     * @param argsList Shared pointer to the vector of function arguments to populate
     */
    void SemanticAnalysis::visitExternFunctionArgs(
        IronParser::ExternFunctionArgsContext *ctx, 
        std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList)
    {
        for (const auto& arg : ctx->externFunctionArg())
        {
            visitExternFunctionArg(arg, argsList);
        }
    }

    /**
     * @brief Processes a single argument of an external function
     * 
     * Extracts the name and type of the argument and adds it to the argument list.
     * Checks for duplicate argument names within the same function.
     * 
     * @param ctx The extern function argument context from the parser
     * @param argsList Shared pointer to the vector of function arguments to update
     * @throws ScopeNotFoundException if the current function scope is not found
     * @throws VariableRedefinitionException if the argument name is already used
     */
    void SemanticAnalysis::visitExternFunctionArg(
        IronParser::ExternFunctionArgContext *ctx,
        std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList)
    {
        const std::string argName = ctx->varName->getText();
        const std::string argTypeName = ctx->cTypes()->getText();
        const auto lineNumber = ctx->getStart()->getLine();
        const auto columnPosition = ctx->getStart()->getCharPositionInLine();
        auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);

        // Get current function context
        const auto currentFunction = scopeManager->currentFunctionDeclaration();
        if (!currentFunction)
        {
            throw ScopeNotFoundException(util::format(
                "Internal error: Function scope not found when processing extern argument '{}'.\n"
                "Line: {}",
                color::colorText(argName, color::BOLD_GREEN),
                color::colorText(std::to_string(lineNumber), color::BOLD_YELLOW)));
        }

        // Check for duplicate argument names
        if (auto existingArg = currentFunction->getArgByName(argName))
        {
            throw VariableRedefinitionException(util::format(
                "Duplicate argument error: Function argument '{}' is already declared.\n"
                "Line: {}, Scope: fn {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(argName, color::BOLD_GREEN), 
                color::colorText(std::to_string(lineNumber), color::YELLOW),
                color::colorText(currentFunction->getFunctionName(), color::BOLD_YELLOW),
                codeLine, caretLine));
        }

        // Create and add the argument
        int argType = tokenMap::getTokenType(argTypeName);
        argsList->push_back(std::make_shared<scope::FunctionArg>(argName, argType));
    }

} // namespace iron

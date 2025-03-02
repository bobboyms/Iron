#include "../headers/SemanticAnalysis.h"
#include <iostream>
#include <utility>
#include "../headers/Analyser.h"
#include "../headers/Files.h"


namespace iron
{
    // Construtor
    SemanticAnalysis::SemanticAnalysis(std::shared_ptr<IronParser> parser,
                                       std::unique_ptr<scope::ScopeManager> scopeManager,
                                       const std::vector<std::string> &sourceLines,
                                       const std::shared_ptr<config::Configuration> &config) :
        parser(std::move(parser)), scopeManager(std::move(scopeManager)), sourceLines(sourceLines), config(config)
    {
    }

    // Destrutor
    SemanticAnalysis::~SemanticAnalysis() = default;

    // Método principal para análise semântica
    std::vector<std::shared_ptr<scope::Function>> SemanticAnalysis::analyze()
    {

        IronParser::ProgramContext *programContext = parser->program();

        // std::vector<IronParser::ImportStatementContext *> imports = programContext->importStatement();
        for (const auto importStmt: programContext->importStatement())
        {
            visitImportStatement(importStmt);
        }

        if (programContext->externBlock())
        {
            visitExternBlock(programContext->externBlock());
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

        return scopeManager->getFunctionDeclarations();
    }

    void SemanticAnalysis::visitStatementList(const IronParser::StatementListContext *ctx)
    {
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, -7);

        const auto currentFunction = getCurrentFunction();

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
            if (const auto whileLoop = dynamic_cast<IronParser::WhileStatementContext *>(child))
            {
                visitWhileStatement(whileLoop);
            }
            if (const auto forLoop = dynamic_cast<IronParser::ForStatementContext *>(child))
            {
                visitForStatement(forLoop);
            }
            if (const auto repeatLoop = dynamic_cast<IronParser::RepeatStatementContext *>(child))
            {
                visitRepeatStatement(repeatLoop);
            }
            if (const auto IfStatement = dynamic_cast<IronParser::IfStatementContext *>(child))
            {
                visitIfStatement(IfStatement);
            }
            if (const auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
            }
        }
        currentFunction->exitLocalScope();
    }

    void SemanticAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext *ctx)
    {
        const std::string varName = ctx->varName->getText();
        const std::string varType = ctx->varTypes()->getText();

        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        const std::string scopeName = scopeManager->currentScopeName();

        const auto currentFunction = getCurrentFunction();

        bool mut = ctx->MUT() != nullptr;

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

        statement->addVariable(varName, tokenMap::getTokenType(varType), mut);

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

    void SemanticAnalysis::visitVarAssignment(const IronParser::VarAssignmentContext *ctx)
    {
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();

        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        const std::string varName = ctx->varName->getText();
        const auto function = getCurrentFunction();

        const auto variable = function->findVarAllScopesAndArg(varName);
        if (!variable)
        {
            throw VariableNotFoundException(util::format(
                    "Variable '{}' not found.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), caretLine, codeLine));
        }

        if (!variable->mut)
        {
            throw VariableCannotBeChangedException(util::format(
                "The value of the variable '{}' cannot be changed because it is immutable. If you want to make the variable mutable, use '{}' before let..\n"
                "Line: {}, Scope: {}\n\n"
                "{}\n"
                "{}\n",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText("mut", color::BOLD_BLUE),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(scopeManager->currentScopeName(),
                    color::BOLD_YELLOW), caretLine, codeLine));
        }

        if (ctx->anotherVarName)
        {
            const auto anotherVarName = ctx->anotherVarName->getText();
            const auto anotherVariable = function->findVarAllScopesAndArg(anotherVarName);
            if (!anotherVariable)
            {
                throw VariableNotFoundException(util::format(
                        "Variable '{}' not found.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n",
                        color::colorText(anotherVarName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), caretLine, codeLine));
            }

            if (!variable->type != anotherVariable->type)
            {
                throw TypeMismatchException(util::format(
                                "The variable {} type is {} and the variable {} type is {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n" // Exibe a linha de código
                                "{}\n", // Exibe a setinha '^'
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(tokenMap::getTokenText(variable->type),
                                color::BOLD_GREEN), color::colorText(anotherVarName, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(anotherVariable->type), color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                caretLine, codeLine));
            }

        }
    }

    void SemanticAnalysis::visitImportStatement(IronParser::ImportStatementContext *ctx) const
    {
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();

        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        if (ctx->qualifiedName())
        {
            const std::string import = ctx->qualifiedName()->getText();
            const auto [path, element] = convertImportPath(import);
            const std::string fullPath = util::format("{}{}", config->stdFolder(), path);

            if (auto globalScope = scopeManager->getFunctionDeclarationByName(element))
            {

                throw ModuleRedefinitionException(util::format("Module {} already declared."
                                                               "Line: {}, Scope: {}\n\n"
                                                               "{}\n"
                                                               "{}\n",
                                                               color::colorText(element, color::BOLD_GREEN),
                                                               color::colorText(std::to_string(line), color::YELLOW),
                                                               color::colorText("Global", color::BOLD_YELLOW), codeLine,
                                                               caretLine));
            }

            bool foundExternal = false;
            Analyser analyser(config);
            auto const externalDeclarations = analyser.semantic(fullPath);
            for (const auto &externalDeclaration: externalDeclarations)
            {
                if (externalDeclaration->getFunctionName() != element)
                {
                    continue;
                }

                scopeManager->setExternDeclaration(externalDeclaration);
                foundExternal = true;
            }

            if (!foundExternal)
            {
                throw ModuleNotFoundException(util::format("Module {} not found."
                                                           "Line: {}, Scope: {}\n\n"
                                                           "{}\n"
                                                           "{}\n",
                                                           color::colorText(element, color::BOLD_GREEN),
                                                           color::colorText(std::to_string(line), color::YELLOW),
                                                           color::colorText("Global", color::BOLD_YELLOW), codeLine,
                                                           caretLine));
            }
        }
    }



    std::pair<std::string, std::string> SemanticAnalysis::getCodeLineAndCaretLine(const uint line, const uint col,
                                                                                  const int steps) const
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

        // Calcula o número de espaços; se for negativo, define como zero
        int numSpaces = col + steps;
        if (numSpaces < 0)
            numSpaces = 0;

        std::string caretLine(numSpaces, ' ');
        caretLine += '^';

        return std::make_pair(caretLine, codeLine);
    }


    void SemanticAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    {
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 2);

        const auto currentFunction = getCurrentFunction();

        if (ctx->dataFormat())
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
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

        if (ctx->functionCall())
        {

            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const std::string varName = varDeclaration->varName->getText();
                const std::string varType = varDeclaration->varTypes()->getText();
                const auto functionName = ctx->functionCall()->functionName->getText();

                if (const auto variable = getCurrentFunction()->findVarAllScopesAndArg(functionName))
                {

                    if (variable->type == tokenMap::FUNCTION && !variable->function)
                    {
                        const auto arg = currentFunction->getArgByName(functionName);
                        if (!arg || !arg->signature)
                        {
                            throw FunctionNotFoundException(
                                util::format("Function {} not found.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(functionName, color::BOLD_GREEN),
                                             color::colorText(std::to_string(line), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                        }

                        if (arg->signature->getReturnType() != tokenMap::getTokenType(varType))
                        {
                            throw TypeMismatchException(util::format(
                                    "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
                                    "Line: {}, Scope: {}\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(varName, color::BOLD_GREEN),
                                    color::colorText(varType, color::BOLD_GREEN),
                                    color::colorText(functionName, color::BOLD_BLUE),
                                    color::colorText(tokenMap::getTokenText(variable->function->getReturnType()),
                                                     color::BOLD_BLUE),
                                    color::colorText(std::to_string(line), color::YELLOW),
                                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                    caretLine));
                        }

                        visitFunctionCall(ctx->functionCall());

                        return;
                    }

                    if (!variable->function)
                    {

                        throw FunctionNotFoundException(
                                util::format("Function {} not found.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(functionName, color::BOLD_GREEN),
                                             color::colorText(std::to_string(line), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                    }

                    if (variable->function->getReturnType() != tokenMap::getTokenType(varType))
                    {
                        throw TypeMismatchException(util::format(
                                "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n"
                                "{}\n",
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(varType, color::BOLD_GREEN),
                                color::colorText(functionName, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(variable->function->getReturnType()),
                                                 color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                caretLine));
                    }
                }
                else
                {
                    const auto function = scopeManager->getFunctionDeclarationByName(functionName);
                    if (!function)
                    {
                        throw FunctionNotFoundException(
                                util::format("Function {} not found.\n"
                                             "Line: {}, Scope: {}\n\n"
                                             "{}\n"
                                             "{}\n",
                                             color::colorText(functionName, color::BOLD_GREEN),
                                             color::colorText(std::to_string(line), color::YELLOW),
                                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                             codeLine, caretLine));
                    }

                    if (function->getReturnType() != tokenMap::getTokenType(varType))
                    {
                        throw TypeMismatchException(util::format(
                                "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
                                "Line: {}, Scope: {}\n\n"
                                "{}\n"
                                "{}\n",
                                color::colorText(varName, color::BOLD_GREEN),
                                color::colorText(varType, color::BOLD_GREEN),
                                color::colorText(functionName, color::BOLD_BLUE),
                                color::colorText(tokenMap::getTokenText(function->getReturnType()), color::BOLD_BLUE),
                                color::colorText(std::to_string(line), color::YELLOW),
                                color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                caretLine));
                    }
                }
            }

            visitFunctionCall(ctx->functionCall());
        }

        if (ctx->varName)
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const std::string anotherVarName = ctx->varName->getText();
                const std::string varName = varDeclaration->varName->getText();
                const std::string varType = varDeclaration->varTypes()->getText();

                if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
                {
                    std::shared_ptr<scope::Function> functionPtr;
                    if (const auto anotherVariable = getCurrentFunction()->findVarAllScopesAndArg(anotherVarName);
                        !anotherVariable)
                    {
                        const auto function = scopeManager->getFunctionDeclarationByName(anotherVarName);
                        if (!function)
                        {
                            throw FunctionNotFoundException(
                                    util::format("Function {} not found.\n"
                                                 "Line: {}, Scope: {}\n\n"
                                                 "{}\n"
                                                 "{}\n",
                                                 color::colorText(anotherVarName, color::BOLD_GREEN),
                                                 color::colorText(std::to_string(line), color::YELLOW),
                                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                                 codeLine, caretLine));
                        }
                        functionPtr = function;
                    }
                    else
                    {
                        if (!anotherVariable->function)
                        {
                            throw TypeMismatchException(util::format(
                                    "The variable {} of type {} is incompatible with the variable {} of type {}.\n"
                                    "Line: {}, Scope: {}\n\n"
                                    "{}\n"
                                    "{}\n",
                                    color::colorText(varName, color::BOLD_GREEN),
                                    color::colorText(varType, color::BOLD_GREEN),
                                    color::colorText(anotherVariable->name, color::BOLD_BLUE),
                                    color::colorText(tokenMap::getTokenText(anotherVariable->type), color::BOLD_BLUE),
                                    color::colorText(std::to_string(line), color::YELLOW),
                                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                                    caretLine));
                        }

                        functionPtr = anotherVariable->function;

                    }
                    const auto variable = currentFunction->findVarAllScopesAndArg(varName);
                    variable->function = functionPtr;
                    return;
                }

                const auto variable = getCurrentFunction()->findVarAllScopesAndArg(anotherVarName);
                if (!variable)
                {
                    throw VariableNotFoundException(
                            util::format("Variable '{}' not found.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n",
                                         color::colorText(anotherVarName, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                if (variable->type != tokenMap::getTokenType(varType))
                {

                    throw TypeMismatchException(util::format(
                            "The variable {} of type {} is incompatible with the variable {} of type {}.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(variable->name, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
        }

        if (ctx->expr())
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const std::string varName = varDeclaration->varName->getText();
                const std::string varType = varDeclaration->varTypes()->getText();

                if (const auto [_, exprType] = visitExpr(ctx->expr()); exprType != tokenMap::getTokenType(varType))
                {
                    throw TypeMismatchException(util::format(
                            "The variable {} of type {} is incompatible with the return of expression of type {}.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(exprType), color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }
            }
        }

        if (ctx->boolExpr())
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const std::string varName = varDeclaration->varName->getText();

                if (const std::string varType = varDeclaration->varTypes()->getText();
                    tokenMap::getTokenType(varType) != tokenMap::TYPE_BOOLEAN)
                {
                    throw TypeMismatchException(util::format(
                            "The variable {} type need be {} to receive the value of a boolean expression\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText("boolean", color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }

                visitBoolExpr(ctx->boolExpr());
            }
        }
    }

    void SemanticAnalysis::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();

        auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);

        const auto currentFunction = getCurrentFunction();
        currentFunction->changeToReturnFound();

        printf(">> return func: %s\n", currentFunction->getFunctionName().c_str());
        printf(">> is return: %u\n", currentFunction->isReturnFound());

        if (ctx->dataFormat())
        {
            const auto value = ctx->dataFormat()->getText();
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

            const auto arg = currentFunction->getArgByName(functionCallName);
            if (arg && arg->signature)
            {

                if (arg->signature->getReturnType() != currentFunction->getReturnType())
                {
                    throw TypeMismatchException(util::format(
                            "The Function {} return type {} is incompatible with the Function {} return type {}.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n",
                            color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                            color::colorText(functionCallName, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(arg->signature->getReturnType()), color::BOLD_BLUE),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
                }

                visitFunctionCall(ctx->functionCall());
                currentFunction->updateReturnTokenStatusToFound();
                return;

            }

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

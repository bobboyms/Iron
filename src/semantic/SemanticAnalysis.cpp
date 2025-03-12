#include "../headers/SemanticAnalysis.h"
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
        // Fase 1: Coletar declarações de importações, estruturas e funções
        analyzeDeclarations();

        // Fase 2: Analisar definições e implementações
        analyzeDefinitions();

        return scopeManager->getFunctionDeclarations();
    }

    void SemanticAnalysis::analyzeDeclarations()
    {
        IronParser::ProgramContext *programContext = parser->program();

        // Processar todas as importações primeiro
        for (const auto importStmt: programContext->importStatement())
        {
            visitImportStatement(importStmt);
        }

        // Processar blocos externos
        if (programContext->externBlock())
        {
            visitExternBlock(programContext->externBlock());
        }

        // Coletar declarações de funções e estruturas
        for (const auto child: programContext->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }

            if (const auto struct_ = dynamic_cast<IronParser::StructStatementContext *>(child))
            {
                visitStructDeclaration(struct_);
            }
        }
    }

    void SemanticAnalysis::analyzeDefinitions()
    {
        parser->reset();
        const auto programContext = parser->program();

        // Analisar implementações de estruturas
        for (const auto child: programContext->children)
        {
            if (const auto struct_ = dynamic_cast<IronParser::StructStatementContext *>(child))
            {
                visitStructStatement(struct_);
            }
        }

        // Analisar corpos de funções após todas as declarações
        for (const auto child: programContext->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionBody(funcDecl);
            }
        }
    }

    void SemanticAnalysis::visitStatementList(const IronParser::StatementListContext *ctx)
    {
        // Capturar contexto de erro
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();

        // Obter função atual e configurar escopo local
        const auto currentFunction = getCurrentFunction();
        currentFunction->enterLocalScope(std::make_shared<scope::Statements>());

        // Processar cada tipo de declaração por tipo
        for (const auto child: ctx->children)
        {
            // Declarações de variável
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration);
                continue;
            }

            // Chamadas de função
            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall);
                continue;
            }

            // Atribuições de variável
            if (const auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
                continue;
            }

            // Expressões
            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression);
                continue;
            }

            // Estruturas de controle de fluxo
            if (const auto whileLoop = dynamic_cast<IronParser::WhileStatementContext *>(child))
            {
                visitWhileStatement(whileLoop);
                continue;
            }

            if (const auto forLoop = dynamic_cast<IronParser::ForStatementContext *>(child))
            {
                visitForStatement(forLoop);
                continue;
            }

            if (const auto repeatLoop = dynamic_cast<IronParser::RepeatStatementContext *>(child))
            {
                visitRepeatStatement(repeatLoop);
                continue;
            }

            if (const auto ifStatement = dynamic_cast<IronParser::IfStatementContext *>(child))
            {
                visitIfStatement(ifStatement);
                continue;
            }

            // Comando de retorno
            if (const auto returnCtx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnCtx);
            }
        }

        // Saindo do escopo local
        currentFunction->exitLocalScope();
    }

    void SemanticAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext *ctx)
    {
        const std::string varName = ctx->varName->getText();
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);

        const std::string scopeName = scopeManager->currentScopeName();

        const auto currentFunction = getCurrentFunction();

        const bool mut = ctx->MUT() != nullptr;

        if (auto existingSymbol = currentFunction->findVarCurrentScopeAndArg(varName))
        {
            throw VariableRedefinitionException(util::format(
                    "Variable redefinition error: '{}' is already declared in the current scope.\n"
                    "Line: {}, Scope: {}\n\n"
                    "Hint: Use a different variable name or remove the duplicate declaration.",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeName, color::BOLD_YELLOW)));
        }

        const auto localScope = currentFunction->getCurrentLocalScope();
        if (!localScope)
        {
            throw ScopeNotFoundException(util::format(
                    "Internal error: Local scope not found when declaring variable '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "This is a compiler internal error. Verify that your variable declaration is within a valid block.",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeName, color::BOLD_YELLOW)));
        }

        const auto statement = std::dynamic_pointer_cast<scope::Statements>(localScope);
        if (!statement)
        {
            throw ScopeNotFoundException(util::format(
                    "Internal error: The local scope for variable '{}' is not a valid statement block.\n"
                    "Line: {}, Scope: {}\n\n"
                    "This is a compiler internal error. Verify your code structure.",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeName, color::BOLD_YELLOW)));
        }

        if (ctx->varTypes())
        {
            const std::string varType = ctx->varTypes()->getText();
            statement->addVariable(varName, tokenMap::getTokenType(varType), mut);
        }
        else
        {
            if (!ctx->anotherType)
            {
                throw std::runtime_error("SemanticAnalysis::visitVarDeclaration. Invalid variable declaration");
            }

            const std::string anotherType = ctx->anotherType->getText();
            statement->addVariable(checkAnotherTypes(varName, anotherType, mut, line, codeLine, caretLine));
        }

        if (ctx->assignment())
        {
            visitAssignment(ctx->assignment());
        }
        else
        {
            throw UninitializedVariableException(util::format(
                    "Uninitialized variable error: Variable '{}' must be initialized at declaration.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: All variables must be initialized when declared. Add an assignment using '=' followed by a "
                    "value.",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
        }
    }

    std::shared_ptr<scope::Variable> SemanticAnalysis::verifyVariableExists(const std::string &varName, uint line,
                                                                            uint col, const std::string &contextInfo)
    {
        const auto function = getCurrentFunction();
        const auto variable = function->findVarAllScopesAndArg(varName);

        if (!variable)
        {
            const auto context = getErrorContext(line, col, 0);
            throw VariableNotFoundException(util::format(
                    "Variable not found error: '{}' is not defined in the current scope.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "{}",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine,
                    contextInfo));
        }

        return variable;
    }

    std::shared_ptr<scope::Function> SemanticAnalysis::verifyFunctionExists(const std::string &functionName,
                                                                            const uint line, const uint col) const
    {
        auto function = scopeManager->getFunctionDeclarationByName(functionName);

        if (!function)
        {
            const auto context = getErrorContext(line, col, 0);
            throw FunctionNotFoundException(util::format(
                    "Function not found error: '{}' is not defined in the current scope or standard library.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: Check for typos in the function name or import the module that contains this function.",
                    color::colorText(functionName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine));
        }

        return function;
    }

    void SemanticAnalysis::verifyTypesMatch(const int typeA, const int typeB, const std::string &nameA,
                                            const std::string &nameB, const uint line, const uint col,
                                            const std::string &errorContextMsg) const
    {
        if (typeA != typeB)
        {
            const auto context = getErrorContext(line, col, 0);
            throw TypeMismatchException(
                    util::format("{}: Cannot assign a value of type '{}' to '{}' of type '{}'.\n"
                                 "Line: {}, Scope: {}\n\n"
                                 "{}\n"
                                 "{}\n\n"
                                 "Hint: The types must match for assignment. Use the correct type or cast the value.",
                                 errorContextMsg, color::colorText(tokenMap::getTokenText(typeB), color::BOLD_BLUE),
                                 color::colorText(nameA, color::BOLD_GREEN),
                                 color::colorText(tokenMap::getTokenText(typeA), color::BOLD_GREEN),
                                 color::colorText(std::to_string(line), color::YELLOW),
                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                 context.codeLine, context.caretLine));
        }
    }

    int SemanticAnalysis::determineValueType(const std::string &value)
    {
        if (value.front() == '"' && value.back() == '"')
        {
            return tokenMap::TYPE_STRING;
        }
        if (value == "true" || value == "false")
        {
            return tokenMap::TYPE_BOOLEAN;
        }
        if (value.find('.') != std::string::npos)
        {
            return tokenMap::determineFloatType(value);
        }
        if (std::all_of(value.begin(), value.end(), [](const char c) { return std::isdigit(c); }))
        {
            return tokenMap::TYPE_INT;
        }

        return tokenMap::UNKNOWN;
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

                throw ModuleRedefinitionException(
                        util::format("Module redefinition error: Module '{}' is already imported or declared.\n"
                                     "Line: {}, Scope: {}\n\n"
                                     "{}\n"
                                     "{}\n\n"
                                     "Hint: Remove duplicate imports or rename one of the modules to avoid conflicts.",
                                     color::colorText(element, color::BOLD_GREEN),
                                     color::colorText(std::to_string(line), color::YELLOW),
                                     color::colorText("Global", color::BOLD_YELLOW), codeLine, caretLine));
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
                throw ModuleNotFoundException(util::format(
                        "Module not found error: Module '{}' could not be found in the standard library.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: Check for typos in the module name or verify that the module exists in path: '{}'",
                        color::colorText(element, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText("Global", color::BOLD_YELLOW), codeLine, caretLine,
                        color::colorText(fullPath, color::BOLD_BLUE)));
            }
        }
    }


    ErrorContext SemanticAnalysis::getErrorContext(const uint line, const uint col, const int caretOffset) const
    {
        ErrorContext context;
        context.line = line;
        context.col = col;
        context.scopeName = scopeManager->currentScopeName();

        if (line > 0 && line <= static_cast<int>(sourceLines.size()))
        {
            context.codeLine = sourceLines[line - 1];
        }
        else
        {
            throw std::runtime_error("Unknown line (out of range)");
        }

        // Calcula o número de espaços; se for negativo, define como zero
        int numSpaces = col + caretOffset;
        if (numSpaces < 0)
            numSpaces = 0;

        context.caretLine = std::string(numSpaces, ' ') + '^';

        return context;
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

        return std::make_pair(codeLine, caretLine);
    }


    void SemanticAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    {
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();
        auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 0);
        const auto currentFunction = getCurrentFunction();

        // Processa atribuição por literal ou formato de dado.
        if (ctx->dataFormat())
        {
            handleDataFormatAssignment(ctx, line, codeLine, caretLine);
            return;
        }

        // Processa funções inline (arrow functions).
        if (ctx->arrowFunctionInline())
        {
            visitArrowFunctionInline(ctx->arrowFunctionInline());
            return;
        }

        // Processa atribuição envolvendo chamada função.
        if (ctx->functionCall())
        {
            handleFunctionCallAssignment(ctx, line, codeLine, caretLine, currentFunction);
            return;
        }

        // Processa atribuição usando outro identificador (ex.: atribuição entre variáveis).
        if (ctx->anotherVarName)
        {
            handleAnotherVarNameAssignment(ctx, line, codeLine, caretLine, currentFunction);
            return;
        }

        // Processa atribuição por meio de expressão.
        if (ctx->expr())
        {
            handleExprAssignment(ctx, line, codeLine, caretLine);
            return;
        }

        // Processa atribuição via expressão booleana.
        if (ctx->boolExpr())
        {
            handleBoolExprAssignment(ctx, line, codeLine, caretLine);
            return;
        }

        // Processa inicialização de struct.
        if (ctx->structInit())
        {
            visitStructInit(ctx->structInit(), nullptr);
        }
    }

    void SemanticAnalysis::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
        const uint line = ctx->getStart()->getLine();
        const uint col = ctx->getStart()->getCharPositionInLine();
        auto context = getErrorContext(line, col, 0);

        const auto currentFunction = getCurrentFunction();
        currentFunction->changeToReturnFound();

        // Validar retorno de valor literal
        if (ctx->dataFormat())
        {
            validateReturnLiteral(ctx, currentFunction, line, col);
        }
        // Validar retorno de variável
        else if (ctx->varName)
        {
            validateReturnVariable(ctx, currentFunction, line, col);
        }
        // Validar retorno de expressão
        else if (ctx->expr())
        {
            validateReturnExpression(ctx, currentFunction, line, col);
        }
        // Validar retorno de chamada de função
        else if (ctx->functionCall())
        {
            validateReturnFunctionCall(ctx, currentFunction, line, col);
        }
    }

    // Funções auxiliares para validação de retorno

    void SemanticAnalysis::validateReturnLiteral(IronParser::ReturnStatementContext *ctx,
                                                 const std::shared_ptr<scope::Function> &currentFunction, uint line,
                                                 uint col)
    {
        // Get error context with code line and caret line for error messages
        auto context = getErrorContext(line, col, 0);
        // Create local variables for backwards compatibility with existing code
        const std::string &codeLine = context.codeLine;
        const std::string &caretLine = context.caretLine;

        const auto value = ctx->dataFormat()->getText();
        auto valueType = tokenMap::determineType(value);
        if (valueType == tokenMap::REAL_NUMBER)
        {
            valueType = tokenMap::determineFloatType(value);
        }

        // Verificação de tipo
        if (valueType != currentFunction->getReturnType())
        {
            auto context = getErrorContext(line, col, 0);
            throw TypeMismatchException(util::format(
                    "Return type mismatch error: Function '{}' returns type '{}' but attempting to return a value of "
                    "type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: The literal '{}' (type: {}) cannot be returned from a function that returns type {}.",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine,
                    color::colorText(value, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN)));
        }
    }

    void SemanticAnalysis::validateReturnVariable(IronParser::ReturnStatementContext *ctx,
                                                  const std::shared_ptr<scope::Function> &currentFunction, uint line,
                                                  uint col)
    {
        // Get error context with code line and caret line for error messages
        auto context = getErrorContext(line, col, 0);
        // Create local variables for backwards compatibility with existing code
        const std::string &codeLine = context.codeLine;
        const std::string &caretLine = context.caretLine;

        const std::string varName = ctx->varName->getText();
        const auto variable = verifyVariableExists(
                varName, line, col,
                "Hint: Check for typos in the variable name or declare the variable before using it.");

        // Verificação especial para funções
        if (variable->type == tokenMap::FUNCTION)
        {
            if (variable->type != currentFunction->getReturnType())
            {
                auto context = getErrorContext(line, col, 0);
                throw TypeMismatchException(util::format(
                        "Return type mismatch error: Function '{}' returns type '{}' but attempting to return a "
                        "function variable '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The return type of the function must match the function variable type.",
                        color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                        color::colorText(variable->name, color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine));
            }
        }
        // Verificação para variáveis normais
        else if (variable->type != currentFunction->getReturnType())
        {
            auto context = getErrorContext(line, col, 0);
            throw TypeMismatchException(util::format(
                    "Return type mismatch error: Function '{}' returns type '{}' but attempting to return variable "
                    "'{}' of type '{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: The variable type must match the function return type.",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(variable->name, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine));
        }

        currentFunction->updateReturnTokenStatusToFound();
    }

    void SemanticAnalysis::validateReturnExpression(IronParser::ReturnStatementContext *ctx,
                                                    const std::shared_ptr<scope::Function> &currentFunction, uint line,
                                                    uint col)
    {
        // Get error context with code line and caret line for error messages
        auto context = getErrorContext(line, col, 0);
        // Create local variables for backwards compatibility with existing code
        const std::string &codeLine = context.codeLine;
        const std::string &caretLine = context.caretLine;

        if (auto [_, typeExpr] = visitExpr(ctx->expr()); typeExpr != currentFunction->getReturnType())
        {
            auto context = getErrorContext(line, col, 0);
            throw TypeMismatchException(util::format(
                    "Return type mismatch error: Function '{}' returns type '{}' but the expression returns type "
                    "'{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: The expression result type must match the function return type.",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(typeExpr), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine));
        }

        currentFunction->updateReturnTokenStatusToFound();
    }

    void SemanticAnalysis::validateReturnFunctionCall(IronParser::ReturnStatementContext *ctx,
                                                      const std::shared_ptr<scope::Function> &currentFunction,
                                                      uint line, uint col)
    {
        // Get error context with code line and caret line for error messages
        auto context = getErrorContext(line, col, 0);
        // Create local variables for backwards compatibility with existing code
        const std::string &codeLine = context.codeLine;
        const std::string &caretLine = context.caretLine;

        const auto functionCallName = ctx->functionCall()->functionName->getText();

        // Verificar argumento de função como função
        if (const auto arg = currentFunction->getArgByName(functionCallName); arg && arg->signature)
        {
            if (arg->signature->getReturnType() != currentFunction->getReturnType())
            {
                auto context = getErrorContext(line, col, 0);
                throw TypeMismatchException(util::format(
                        "Return type mismatch error: Function '{}' returns type '{}' but function argument '{}' "
                        "returns type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The function argument's return type must match the current function's return type.",
                        color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                        color::colorText(functionCallName, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(arg->signature->getReturnType()), color::BOLD_BLUE),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine));
            }

            visitFunctionCall(ctx->functionCall());
            currentFunction->updateReturnTokenStatusToFound();
            return;
        }

        // Verificar função global

        if (const auto calledFunction = verifyFunctionExists(functionCallName, line, col);
            calledFunction->getReturnType() != currentFunction->getReturnType())
        {
            auto context = getErrorContext(line, col, 0);
            throw TypeMismatchException(util::format(
                    "Return type mismatch error: Function '{}' returns type '{}' but called function '{}' returns type "
                    "'{}'.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: The called function's return type must match the current function's return type.",
                    color::colorText(currentFunction->getFunctionName(), color::BOLD_GREEN),
                    color::colorText(tokenMap::getTokenText(currentFunction->getReturnType()), color::BOLD_GREEN),
                    color::colorText(functionCallName, color::BOLD_BLUE),
                    color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.codeLine, context.caretLine));
        }

        visitFunctionCall(ctx->functionCall());
        currentFunction->updateReturnTokenStatusToFound();
    }
} // namespace iron

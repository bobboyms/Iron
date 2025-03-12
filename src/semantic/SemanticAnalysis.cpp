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

    void SemanticAnalysis::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {
        const uint col = ctx->getStart()->getCharPositionInLine();
        const uint line = ctx->getStart()->getLine();

        // Get error context with code line and caret line for error messages
        auto context = getErrorContext(line, col, 0);
        // Create local variables for backwards compatibility with existing code
        const std::string &codeLine = context.codeLine;
        const std::string &caretLine = context.caretLine;

        const std::string varName = ctx->variableQualifiedName()->base->getText();
        const auto function = getCurrentFunction();

        // Use the helper function to verify if the variable exists
        const auto variable = verifyVariableExists(
                varName, line, col,
                "Hint: Check for typos in the variable name or declare the variable before using it.");

        if (!variable->mut)
        {
            throw VariableCannotBeChangedException(util::format(
                    "Immutable variable error: Cannot assign a new value to '{}' because it is immutable.\n"
                    "Line: {}, Scope: {}\n\n"
                    "{}\n"
                    "{}\n\n"
                    "Hint: Add the '{}' keyword before 'let' in the variable's declaration to make it mutable: '{}let "
                    "{} = ...'",
                    color::colorText(varName, color::BOLD_GREEN), color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(context.scopeName, color::BOLD_YELLOW), context.caretLine, context.codeLine,
                    color::colorText("mut", color::BOLD_BLUE), color::colorText("mut ", color::BOLD_BLUE),
                    color::colorText(varName, color::BOLD_GREEN)));
        }

        // Handle assignment based on the type of value
        if (ctx->structInit())
        {

            if (const auto restSize = ctx->variableQualifiedName()->rest.size(); restSize >= 1)
            {
                // Handle nested struct field assignment
                const auto [parentStructDef, field] = getStructAndField(ctx->variableQualifiedName());

                // Verify the field is mutable
                if (!field->mut)
                {
                    throw VariableCannotBeChangedException(util::format(
                            "Immutable field error: Cannot assign a new value to field '{}' because it is immutable.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n\n"
                            "Hint: Add the '{}' keyword before the field name in the struct definition to make it "
                            "mutable",
                            color::colorText(field->name, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                            color::colorText("mut", color::BOLD_BLUE)));
                }

                // Verify the field is a struct type
                if (!field->structStemt)
                {
                    throw TypeMismatchException(
                            util::format("Type mismatch error: Cannot assign a struct value to field '{}' which is not "
                                         "a struct type.\n"
                                         "Line: {}, Scope: {}\n\n"
                                         "{}\n"
                                         "{}\n\n"
                                         "Hint: The field must be of a struct type to receive a struct initialization.",
                                         color::colorText(field->name, color::BOLD_GREEN),
                                         color::colorText(std::to_string(line), color::YELLOW),
                                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
                                         codeLine, caretLine));
                }

                // Process the struct initialization
                visitStructInit(ctx->structInit(), field->structStemt);
            }
            else
            {
                // Handle struct initialization for a variable
                if (!variable->structStemt)
                {
                    throw TypeMismatchException(util::format(
                            "Type mismatch error: Cannot assign a struct value to variable '{}' which is not a struct "
                            "type.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n\n"
                            "Hint: The variable must be declared as a struct type to receive a struct initialization.",
                            color::colorText(varName, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
                            caretLine));
                }

                // Process the struct initialization
                visitStructInit(ctx->structInit(), variable->structStemt);
            }
        }
        else if (ctx->anotherVarName)
        {
            const auto anotherVarName = ctx->anotherVarName->getText();
            const auto anotherVariable = verifyVariableExists(
                    anotherVarName, line, col,
                    "Hint: Check for typos in the variable name or declare the variable before using it.");

            // Use the helper function to verify if types match
            verifyTypesMatch(variable->type, anotherVariable->type, varName, anotherVarName, line, col,
                             "Type mismatch error: Cannot assign a value of type to a variable of type");
        }
        else if (ctx->dataFormat())
        {

            // Handle literal values (numbers, strings, booleans)
            const std::string value = ctx->dataFormat()->getText();

            if (const auto restSize = ctx->variableQualifiedName()->rest.size(); restSize >= 1)
            {
                // Handle struct field assignment
                const auto [structDef, field] = getStructAndField(ctx->variableQualifiedName());

                if (!field->mut)
                {
                    throw VariableCannotBeChangedException(util::format(
                            "Immutable field error: Cannot assign a new value to field '{}' because it is immutable.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n\n"
                            "Hint: Add the '{}' keyword before the field name in the struct definition to make it "
                            "mutable",
                            color::colorText(field->name, color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                            color::colorText("mut", color::BOLD_BLUE)));
                }

                // Check if the value type matches the field type
                if (int valueType = determineValueType(value); field->type != valueType)
                {
                    throw TypeMismatchException(util::format(
                            "Type mismatch error: Cannot assign a value of type '{}' to a field of type '{}'.\n"
                            "Line: {}, Scope: {}\n\n"
                            "{}\n"
                            "{}\n\n"
                            "Hint: The literal '{}' (type: {}) cannot be assigned to field '{}' (type: {}). Use "
                            "the correct type or cast the value.",
                            color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW),
                            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                            color::colorText(value, color::BOLD_BLUE),
                            color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                            color::colorText(field->name, color::BOLD_GREEN),
                            color::colorText(tokenMap::getTokenText(field->type), color::BOLD_GREEN)));
                }
                return;
            }

            // Check if the value type matches the variable type
            if (int valueType = determineValueType(value); variable->type != valueType)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign a value of type '{}' to a variable of type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: The literal '{}' (type: {}) cannot be assigned to variable '{}' (type: {}). Use "
                        "the correct type or cast the value.",
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine,
                        color::colorText(value, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(valueType), color::BOLD_BLUE),
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN)));
            }
        }
        else if (ctx->functionCall())
        {
            // Handle function call
            const std::string functionName = ctx->functionCall()->functionName->getText();

            // Check if the function return type matches the variable type
            if (auto calledFunction = verifyFunctionExists(functionName, line, col);
                variable->type != calledFunction->getReturnType())
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign result of function '{}' returning type '{}' to variable "
                        "'{}' of type '{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: Function return type and variable type must match for assignment.",
                        color::colorText(functionName, color::BOLD_BLUE),
                        color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }

            visitFunctionCall(ctx->functionCall());
        }
        else if (ctx->arrowFunctionInline())
        {
            // Handle arrow function

            // Check if the arrow function return type matches the variable type
            if (auto arrowFunction = visitArrowFunctionInline(ctx->arrowFunctionInline());
                variable->type != arrowFunction->getReturnType() && variable->type != tokenMap::FUNCTION)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign a function returning type '{}' to variable '{}' of type "
                        "'{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: Variable type must be 'function' or match the function's return type.",
                        color::colorText(tokenMap::getTokenText(arrowFunction->getReturnType()), color::BOLD_BLUE),
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
            }
        }
        else if (ctx->expr())
        {
            // Handle expression

            // Check if the expression type matches the variable type
            if (auto [exprResult, exprType] = visitExpr(ctx->expr()); variable->type != exprType)
            {
                throw TypeMismatchException(util::format(
                        "Type mismatch error: Cannot assign expression result of type '{}' to variable '{}' of type "
                        "'{}'.\n"
                        "Line: {}, Scope: {}\n\n"
                        "{}\n"
                        "{}\n\n"
                        "Hint: Expression result type must match variable type for assignment.",
                        color::colorText(tokenMap::getTokenText(exprType), color::BOLD_BLUE),
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
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


    // void SemanticAnalysis::visitAssignment(IronParser::AssignmentContext *ctx)
    // {
    //     const uint line = ctx->getStart()->getLine();
    //     const uint col = ctx->getStart()->getCharPositionInLine();
    //
    //     auto [codeLine, caretLine] = getCodeLineAndCaretLine(line, col, 2);
    //
    //     const auto currentFunction = getCurrentFunction();
    //
    //     if (ctx->dataFormat())
    //     {
    //         if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
    //         {
    //             const std::string varName = varDeclaration->varName->getText();
    //             const std::string value = ctx->dataFormat()->getText();
    //             const std::string varType = varDeclaration->varTypes()->getText();
    //
    //             if (tokenMap::determineType(value) == tokenMap::REAL_NUMBER)
    //             {
    //                 if (tokenMap::getTokenType(varType) != tokenMap::determineFloatType(value))
    //                 {
    //                     const auto valueType = tokenMap::getTokenText(tokenMap::determineFloatType(value));
    //
    //                     // Lançando exceção com a linha do código em destaque
    //                     throw TypeMismatchException(util::format(
    //                             "Type mismatch error: Cannot assign a float value '{}' to a variable of type '{}'.\n"
    //                             "Line: {}, Scope: {}\n\n"
    //                             "{}\n"
    //                             "{}\n\n"
    //                             "Hint: The float value's precision ({}) doesn't match the variable's type ({}). Use "
    //                             "the correct type or cast the value.",
    //                             color::colorText(value, color::BOLD_BLUE), color::colorText(varType, color::BOLD_GREEN),
    //                             color::colorText(std::to_string(line), color::YELLOW),
    //                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                             caretLine, color::colorText(valueType, color::BOLD_BLUE),
    //                             color::colorText(varType, color::BOLD_GREEN)));
    //                 }
    //             }
    //             else
    //             {
    //                 if (tokenMap::getTokenType(varType) != tokenMap::determineType(value))
    //                 {
    //                     const auto valueType = tokenMap::getTokenText(tokenMap::determineType(value));
    //
    //                     throw TypeMismatchException(util::format(
    //                             "Type mismatch error: Cannot assign a value of type '{}' to a variable of type '{}'.\n"
    //                             "Line: {}, Scope: {}\n\n"
    //                             "{}\n"
    //                             "{}\n\n"
    //                             "Hint: The literal '{}' (type: {}) cannot be assigned to variable '{}' (type: {}). Use "
    //                             "the correct type or cast the value.",
    //                             color::colorText(valueType, color::BOLD_BLUE),
    //                             color::colorText(varType, color::BOLD_GREEN),
    //                             color::colorText(std::to_string(line), color::YELLOW),
    //                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                             caretLine, color::colorText(value, color::BOLD_BLUE),
    //                             color::colorText(valueType, color::BOLD_BLUE),
    //                             color::colorText(varName, color::BOLD_GREEN),
    //                             color::colorText(varType, color::BOLD_GREEN)));
    //                 }
    //             }
    //         }
    //     }
    //
    //     if (ctx->arrowFunctionInline())
    //     {
    //         visitArrowFunctionInline(ctx->arrowFunctionInline());
    //     }
    //
    //     if (ctx->functionCall())
    //     {
    //
    //         if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
    //         {
    //             const std::string varName = varDeclaration->varName->getText();
    //             const std::string varType = varDeclaration->varTypes()->getText();
    //             const auto functionName = ctx->functionCall()->functionName->getText();
    //
    //             if (const auto variable = getCurrentFunction()->findVarAllScopesAndArg(functionName))
    //             {
    //
    //                 if (variable->type == tokenMap::FUNCTION && !variable->function)
    //                 {
    //                     const auto arg = currentFunction->getArgByName(functionName);
    //                     if (!arg || !arg->signature)
    //                     {
    //                         throw FunctionNotFoundException(
    //                                 util::format("Function not found error: Function '{}' is not defined in current "
    //                                              "scope or standard library.\n"
    //                                              "Line: {}, Scope: {}\n\n"
    //                                              "{}\n"
    //                                              "{}\n\n"
    //                                              "Hint: Check for typos in the function name or import the module that "
    //                                              "contains this function.",
    //                                              color::colorText(functionName, color::BOLD_GREEN),
    //                                              color::colorText(std::to_string(line), color::YELLOW),
    //                                              color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                              codeLine, caretLine));
    //                     }
    //
    //                     if (arg->signature->getReturnType() != tokenMap::getTokenType(varType))
    //                     {
    //                         throw TypeMismatchException(util::format(
    //                                 "Return type mismatch error: Cannot assign result of function '{}' to variable "
    //                                 "'{}'.\n"
    //                                 "Line: {}, Scope: {}\n\n"
    //                                 "{}\n"
    //                                 "{}\n\n"
    //                                 "Hint: Function '{}' returns type '{}' but variable '{}' is of type '{}'. These "
    //                                 "types are incompatible.",
    //                                 color::colorText(functionName, color::BOLD_BLUE),
    //                                 color::colorText(varName, color::BOLD_GREEN),
    //                                 color::colorText(std::to_string(line), color::YELLOW),
    //                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                                 caretLine, color::colorText(functionName, color::BOLD_BLUE),
    //                                 color::colorText(tokenMap::getTokenText(variable->function->getReturnType()),
    //                                                  color::BOLD_BLUE),
    //                                 color::colorText(varName, color::BOLD_GREEN),
    //                                 color::colorText(varType, color::BOLD_GREEN)));
    //                     }
    //
    //                     visitFunctionCall(ctx->functionCall());
    //
    //                     return;
    //                 }
    //
    //                 if (!variable->function)
    //                 {
    //
    //                     throw FunctionNotFoundException(
    //                             util::format("Function {} not found.\n"
    //                                          "Line: {}, Scope: {}\n\n"
    //                                          "{}\n"
    //                                          "{}\n",
    //                                          color::colorText(functionName, color::BOLD_GREEN),
    //                                          color::colorText(std::to_string(line), color::YELLOW),
    //                                          color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                          codeLine, caretLine));
    //                 }
    //
    //                 if (variable->function->getReturnType() != tokenMap::getTokenType(varType))
    //                 {
    //                     throw TypeMismatchException(util::format(
    //                             "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
    //                             "Line: {}, Scope: {}\n\n"
    //                             "{}\n"
    //                             "{}\n",
    //                             color::colorText(varName, color::BOLD_GREEN),
    //                             color::colorText(varType, color::BOLD_GREEN),
    //                             color::colorText(functionName, color::BOLD_BLUE),
    //                             color::colorText(tokenMap::getTokenText(variable->function->getReturnType()),
    //                                              color::BOLD_BLUE),
    //                             color::colorText(std::to_string(line), color::YELLOW),
    //                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                             caretLine));
    //                 }
    //             }
    //             else
    //             {
    //                 const auto function = scopeManager->getFunctionDeclarationByName(functionName);
    //                 if (!function)
    //                 {
    //                     throw FunctionNotFoundException(
    //                             util::format("Function {} not found.\n"
    //                                          "Line: {}, Scope: {}\n\n"
    //                                          "{}\n"
    //                                          "{}\n",
    //                                          color::colorText(functionName, color::BOLD_GREEN),
    //                                          color::colorText(std::to_string(line), color::YELLOW),
    //                                          color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                          codeLine, caretLine));
    //                 }
    //
    //                 if (function->getReturnType() != tokenMap::getTokenType(varType))
    //                 {
    //                     throw TypeMismatchException(util::format(
    //                             "The variable {} of type {} is incompatible with the function {} return of type {}.\n"
    //                             "Line: {}, Scope: {}\n\n"
    //                             "{}\n"
    //                             "{}\n",
    //                             color::colorText(varName, color::BOLD_GREEN),
    //                             color::colorText(varType, color::BOLD_GREEN),
    //                             color::colorText(functionName, color::BOLD_BLUE),
    //                             color::colorText(tokenMap::getTokenText(function->getReturnType()), color::BOLD_BLUE),
    //                             color::colorText(std::to_string(line), color::YELLOW),
    //                             color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                             caretLine));
    //                 }
    //             }
    //         }
    //
    //         visitFunctionCall(ctx->functionCall());
    //     }
    //
    //     if (ctx->anotherVarName)
    //     {
    //         if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
    //         {
    //             const std::string anotherVarName =
    //                     ctx->variableQualifiedName()->base->getText(); // anotherVarName->getText();
    //             const std::string varName = varDeclaration->varName->getText();
    //             // printf("varName %s\n", varName.c_str());
    //             // printf("anotherVarName %s\n", anotherVarName.c_str());
    //             const auto anotherVariable = getCurrentFunction()->findVarAllScopesAndArg(anotherVarName);
    //             const auto variable = currentFunction->findVarAllScopesAndArg(varName);
    //             const auto restSize = ctx->variableQualifiedName()->rest.size();
    //
    //             if (restSize > 0)
    //             {
    //                 if (!anotherVariable)
    //                 {
    //                     throw VariableNotFoundException(
    //                             util::format("Variable {} not found.\n"
    //                                          "Line: {}, Scope: {}\n\n"
    //                                          "{}\n"
    //                                          "{}\n",
    //                                          color::colorText(anotherVarName, color::BOLD_GREEN),
    //                                          color::colorText(std::to_string(line), color::YELLOW),
    //                                          color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                          codeLine, caretLine));
    //                 }
    //
    //                 if (anotherVariable->type == tokenMap::STRUCT)
    //                 {
    //
    //                     if (const auto restSize = ctx->variableQualifiedName()->rest.size(); restSize >= 1)
    //                     {
    //                         const auto [structStmt, field] = getStructAndField(ctx->variableQualifiedName());
    //                         if (field->type != variable->type)
    //                         {
    //                             throw TypeMismatchException(util::format(
    //                                     "The variable {} of type {} is incompatible with the field {} of type {}.\n"
    //                                     "Line: {}, Scope: {}\n\n"
    //                                     "{}\n"
    //                                     "{}\n",
    //                                     color::colorText(varName, color::BOLD_GREEN),
    //                                     color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_GREEN),
    //                                     color::colorText(field->name, color::BOLD_BLUE),
    //                                     color::colorText(tokenMap::getTokenText(field->type), color::BOLD_BLUE),
    //                                     color::colorText(std::to_string(line), color::YELLOW),
    //                                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                     codeLine, caretLine));
    //                         }
    //
    //                         if (field->structStemt->name != variable->structStemt->name)
    //                         {
    //                             throw TypeMismatchException(util::format(
    //                                     "The variable {} of type {} is incompatible with the field {} of type {}.\n"
    //                                     "Line: {}, Scope: {}\n\n"
    //                                     "{}\n"
    //                                     "{}\n",
    //                                     color::colorText(varName, color::BOLD_GREEN),
    //                                     color::colorText(variable->structStemt->name, color::BOLD_GREEN),
    //                                     color::colorText(field->name, color::BOLD_BLUE),
    //                                     color::colorText(field->structStemt->name, color::BOLD_BLUE),
    //                                     color::colorText(std::to_string(line), color::YELLOW),
    //                                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                     codeLine, caretLine));
    //                         }
    //                     }
    //
    //                     return;
    //                 }
    //             }
    //
    //             const std::string varType = varDeclaration->varTypes()->getText();
    //             if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
    //             {
    //                 std::shared_ptr<scope::Function> functionPtr;
    //                 if (!anotherVariable)
    //                 {
    //                     const auto function = scopeManager->getFunctionDeclarationByName(anotherVarName);
    //                     if (!function)
    //                     {
    //                         throw FunctionNotFoundException(
    //                                 util::format("Function {} not found.\n"
    //                                              "Line: {}, Scope: {}\n\n"
    //                                              "{}\n"
    //                                              "{}\n",
    //                                              color::colorText(anotherVarName, color::BOLD_GREEN),
    //                                              color::colorText(std::to_string(line), color::YELLOW),
    //                                              color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                              codeLine, caretLine));
    //                     }
    //                     functionPtr = function;
    //                 }
    //                 else
    //                 {
    //                     if (!anotherVariable->function)
    //                     {
    //                         throw TypeMismatchException(util::format(
    //                                 "The variable {} of type {} is incompatible with the variable {} of type {}.\n"
    //                                 "Line: {}, Scope: {}\n\n"
    //                                 "{}\n"
    //                                 "{}\n",
    //                                 color::colorText(varName, color::BOLD_GREEN),
    //                                 color::colorText(varType, color::BOLD_GREEN),
    //                                 color::colorText(anotherVariable->name, color::BOLD_BLUE),
    //                                 color::colorText(tokenMap::getTokenText(anotherVariable->type), color::BOLD_BLUE),
    //                                 color::colorText(std::to_string(line), color::YELLOW),
    //                                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                                 caretLine));
    //                     }
    //
    //                     functionPtr = anotherVariable->function;
    //                 }
    //                 const auto variable = currentFunction->findVarAllScopesAndArg(varName);
    //                 variable->function = functionPtr;
    //                 return;
    //             }
    //
    //             if (!anotherVariable)
    //             {
    //                 throw VariableNotFoundException(
    //                         util::format("Variable {} not found.\n"
    //                                      "Line: {}, Scope: {}\n\n"
    //                                      "{}\n"
    //                                      "{}\n",
    //                                      color::colorText(anotherVarName, color::BOLD_GREEN),
    //                                      color::colorText(std::to_string(line), color::YELLOW),
    //                                      color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                      codeLine, caretLine));
    //             }
    //
    //             // const auto variable = getCurrentFunction()->findVarAllScopesAndArg(anotherVarName);
    //             if (!variable)
    //             {
    //                 throw VariableNotFoundException(
    //                         util::format("Variable '{}' not found.\n"
    //                                      "Line: {}, Scope: {}\n\n"
    //                                      "{}\n"
    //                                      "{}\n",
    //                                      color::colorText(anotherVarName, color::BOLD_GREEN),
    //                                      color::colorText(std::to_string(line), color::YELLOW),
    //                                      color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
    //                                      codeLine, caretLine));
    //             }
    //
    //             if (variable->type != tokenMap::getTokenType(varType))
    //             {
    //
    //                 throw TypeMismatchException(util::format(
    //                         "The variable {} of type {} is incompatible with the variable {} of type {}.\n"
    //                         "Line: {}, Scope: {}\n\n"
    //                         "{}\n"
    //                         "{}\n",
    //                         color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
    //                         color::colorText(variable->name, color::BOLD_BLUE),
    //                         color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
    //                         color::colorText(std::to_string(line), color::YELLOW),
    //                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                         caretLine));
    //             }
    //         }
    //     }
    //
    //     if (ctx->expr())
    //     {
    //         if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
    //         {
    //             const std::string varName = varDeclaration->varName->getText();
    //             const std::string varType = varDeclaration->varTypes()->getText();
    //
    //             if (const auto [_, exprType] = visitExpr(ctx->expr()); exprType != tokenMap::getTokenType(varType))
    //             {
    //                 throw TypeMismatchException(util::format(
    //                         "The variable {} of type {} is incompatible with the return of expression of type {}.\n"
    //                         "Line: {}, Scope: {}\n\n"
    //                         "{}\n"
    //                         "{}\n",
    //                         color::colorText(varName, color::BOLD_GREEN), color::colorText(varType, color::BOLD_GREEN),
    //                         color::colorText(tokenMap::getTokenText(exprType), color::BOLD_BLUE),
    //                         color::colorText(std::to_string(line), color::YELLOW),
    //                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                         caretLine));
    //             }
    //         }
    //     }
    //
    //     if (ctx->boolExpr())
    //     {
    //         if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
    //         {
    //             const std::string varName = varDeclaration->varName->getText();
    //
    //             if (const std::string varType = varDeclaration->varTypes()->getText();
    //                 tokenMap::getTokenType(varType) != tokenMap::TYPE_BOOLEAN)
    //             {
    //                 throw TypeMismatchException(util::format(
    //                         "The variable {} type need be {} to receive the value of a boolean expression\n"
    //                         "Line: {}, Scope: {}\n\n"
    //                         "{}\n"
    //                         "{}\n",
    //                         color::colorText(varName, color::BOLD_GREEN),
    //                         color::colorText("boolean", color::BOLD_GREEN),
    //                         color::colorText(std::to_string(line), color::YELLOW),
    //                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine,
    //                         caretLine));
    //             }
    //
    //             visitBoolExpr(ctx->boolExpr());
    //         }
    //     }
    //
    //     if (ctx->structInit())
    //     {
    //         visitStructInit(ctx->structInit(), nullptr);
    //     }
    // }

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
        const auto arg = currentFunction->getArgByName(functionCallName);
        if (arg && arg->signature)
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
        const auto calledFunction = verifyFunctionExists(functionCallName, line, col);

        if (calledFunction->getReturnType() != currentFunction->getReturnType())
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

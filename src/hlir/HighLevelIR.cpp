#include "../headers/HighLevelIR.h"
#include "../headers/Exceptions.h"
#include "../headers/Colors.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

#include <iostream>

namespace iron
{

    HighLevelIR::HighLevelIR(std::shared_ptr<IronParser> parser,
                             std::unique_ptr<ScopeManager> scopeManager)
        : parser(parser), scopeManager(std::move(scopeManager)), writerCodeHLIR(new WriterCodeHLIR())
    {
    }

    HighLevelIR::~HighLevelIR()
    {
    }

    std::string HighLevelIR::generateTempVar()
    {
        return "var_" + std::to_string(++tempVarCounter);
    }

    std::shared_ptr<HightLavelIRParser> HighLevelIR::generateParser()
    {
        const auto code = generateCode();

        std::cout << code << std::endl;

        antlr4::ANTLRInputStream inputStream(code);
        HightLavelIRLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<HightLavelIRParser>(&tokens);
        return parser;
    }

    std::string HighLevelIR::generateCode()
    {
        scopeManager->enterScope(tokenMap::getTokenText(tokenMap::GLOBAL));
        IronParser::ProgramContext *programContext = parser->program();

        // Processa todas as declarações no programa
        auto writer = writerCodeHLIR->getWriter(tokenMap::getTokenText(tokenMap::GLOBAL));
        for (auto child : programContext->children)
        {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        // Finaliza o escopo global após processar todas as declarações

        scopeManager->exitScope(tokenMap::getTokenText(tokenMap::GLOBAL));
        return writerCodeHLIR->getCode();
    }

    void HighLevelIR::visitStatementList(IronParser::StatementListContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        for (auto child : ctx->children)
        {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration, sb);
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext *>(child))
            {
                visitVarAssignment(varAssignment);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression, sb);
            }
            if (auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall, sb);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(returnctx);
            }
        }
    }

    std::string HighLevelIR::visitExpr(IronParser::ExprContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        auto currentScope = scopeManager->currentScope();

        if (ctx->L_PAREN() && ctx->R_PAREN())
        {
            for (auto child : ctx->children)
            {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext *>(child))
                {
                    return visitExpr(subExpr, sb);
                }
            }
        }

        int line = ctx->start->getLine();

        // Determina a operação
        std::string operation;
        if (ctx->mult)
        {
            operation = "MULT";
        }
        else if (ctx->div)
        {
            operation = "DIV";
        }
        else if (ctx->plus)
        {
            operation = "PLUS";
        }
        else if (ctx->minus)
        {
            operation = "MINUS";
        }

        // Verifica se é uma expressão binária
        if (!operation.empty() && ctx->left != nullptr && ctx->right != nullptr)
        {

            // Visita os lados esquerdo e direito da expressão
            std::string leftVar = visitExpr(ctx->left, sb);
            std::string rightVar = visitExpr(ctx->right, sb);

            auto rightSymbolOpt = currentScope->lookup(rightVar);
            auto leftSymbolOpt = currentScope->lookup(leftVar);

            if (!leftSymbolOpt.has_value())
            {
                throw hlir::HLIRException(util::format("Undefined left variable: {} in expression", leftVar));
            }

            if (!rightSymbolOpt.has_value())
            {
                throw hlir::HLIRException(util::format("Undefined right variable: {} in expression", rightVar));
            }

            auto leftSymbol = leftSymbolOpt.value();
            auto rightSymbol = rightSymbolOpt.value();
            // util::printf("leftVar: {}, rightSymbol: {}", leftVar, rightVar);
            // util::printf("leftSymbol: {}, rightSymbol: {}", tokenMap::getTokenText(leftSymbol.dataType), tokenMap::getTokenText(rightSymbol.dataType));

            int higherType = tokenMap::getHigherPrecedenceType(leftSymbol.dataType, rightSymbol.dataType);

            if (leftSymbol.dataType != higherType)
            {
                std::string tempVar = generateTempVar();
                currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, higherType, nullptr});
                *sb << util::format("let {}:{} = {} {} to {}\n",
                                    tempVar,
                                    tokenMap::getTokenText(higherType),
                                    leftVar,
                                    tokenMap::getTokenText(leftSymbol.dataType),
                                    tokenMap::getTokenText(higherType));
                leftVar = tempVar;
            }

            if (rightSymbol.dataType != higherType)
            {

                std::string tempVar = generateTempVar();
                currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, higherType, nullptr});
                *sb << util::format("let {}:{} = {} {} to {}\n",
                                    tempVar,
                                    tokenMap::getTokenText(higherType),
                                    rightVar, tokenMap::getTokenText(rightSymbol.dataType),
                                    tokenMap::getTokenText(higherType));
                rightVar = tempVar;
            }

            std::string tempVar = generateTempVar();
            currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, higherType, nullptr});
            // Gere a atribuição temporária
            *sb << util::format("let {}:{} = {} {}, {}\n",
                                tempVar,
                                tokenMap::getTokenText(higherType),
                                operation,
                                leftVar,
                                rightVar);

            return tempVar;
        }
        // Verifica se é uma variável
        else if (ctx->varName)
        {
            std::string varName = ctx->varName->getText();
            return varName;
        }
        // Verifica se é uma chamada de função
        else if (ctx->functionCall())
        {
            // auto mainTypeSymbolInfo = currentScope->lookup(tokenMap::MAIN_TYPE);
            auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
            auto functionName = ctx->functionCall()->functionName->getText();

            auto functionSymbolInfo = globalScope->lookup(functionName);
            if (functionSymbolInfo.has_value())
            {
                std::string tempVar = generateTempVar();
                int dataType = functionSymbolInfo.value().dataType;
                *sb << util::format("let {}:{} = ", tempVar, tokenMap::getTokenText(dataType));
                currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, dataType, nullptr});
                visitFunctionCall(ctx->functionCall(), sb);
                return tempVar;
            }
            else
            {
                const std::string globalFunctionName = createFunctionName(currentScope->getName(), functionName);
                // util::printf("Expr globalFunctionName: {}", globalFunctionName);
                auto globalFunctionOpt = globalScope->lookup(globalFunctionName);
                if (globalFunctionOpt.has_value())
                {
                    std::string tempVar = generateTempVar();
                    int dataType = globalFunctionOpt.value().dataType;
                    *sb << util::format("let {}:{} = ", tempVar, tokenMap::getTokenText(dataType));
                    currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, dataType, nullptr});
                    visitFunctionCall(ctx->functionCall(), sb);
                    return tempVar;
                }
                else
                {

                    throw hlir::HLIRException(util::format("HLIR Error: Function fn {} not found", functionName));
                }
            }
        }
        else if (ctx->number())
        {
            int line = ctx->getStart()->getLine();
            std::string numberLiteral = ctx->number()->getText();
            std::string currentScopeName = scopeManager->currentScopeName();

            int dataType = tokenMap::determineType(numberLiteral);

            if (dataType == tokenMap::REAL_NUMBER)
            {
                dataType = tokenMap::determineFloatType(numberLiteral);
            }

            const std::string tempVar = generateTempVar();
            currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, dataType, nullptr});
            *sb << util::format("let {}:{} = {}\n", tempVar, tokenMap::getTokenText(dataType), numberLiteral);
            return tempVar;
        }

        throw hlir::HLIRException(util::format("Invalid expression. Line: {}", line));
    }

    void HighLevelIR::visitAssignment(IronParser::AssignmentContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        int line = ctx->getStart()->getLine();
        auto currentScope = scopeManager->currentScope();

        // Se houver um util::formato de dado literal (ex.: "3.14", "42", etc.)
        if (ctx->dataFormat())
        {
            // Caso 1: a atribuição está sendo feita a um argumento de função
            if (auto *functionArg = dynamic_cast<IronParser::FunctionArgContext *>(ctx->parent))
            {
                std::string argName = functionArg->varName->getText();
                std::string argType = functionArg->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType = tokenMap::determineType(literalValue);

                *sb << util::format("{}:{} = {}", argName, argType, literalValue);
            }

            // Caso 2: a atribuição está sendo feita a uma variável declarada
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
                int literalType = tokenMap::determineType(literalValue);

                *sb << util::format("let {}:{} = {}\n", varName, varType, literalValue);
            }
        }

        if (ctx->expr())
        {
            const auto rightVarName = visitExpr(ctx->expr(), sb);
            const auto rightSymbolOpt = currentScope->lookup(rightVarName);
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string leftVarName = varDecl->varName->getText();
                std::string leftvarTypeName = varDecl->varTypes()->getText();
                // const auto leftSymbolOpt = currentScope->lookup(leftVarName);

                int leftDataTypeType = tokenMap::getTokenType(leftvarTypeName);

                if (leftDataTypeType != rightSymbolOpt->dataType)
                {

                    std::string tempVar = generateTempVar();
                    currentScope->addSymbol(tempVar, {tokenMap::VARIABLE, leftDataTypeType, nullptr});
                    *sb << util::format("let {}:{} = {} {} to {}\n",
                                        tempVar,
                                        leftvarTypeName,
                                        rightVarName,
                                        tokenMap::getTokenText(rightSymbolOpt->dataType),
                                        leftvarTypeName);

                    *sb << util::format("let {}:{} = {}\n", leftVarName, leftvarTypeName, tempVar);
                }
                else
                {
                    *sb << util::format("let {}:{} = {}\n", leftVarName, leftvarTypeName, rightVarName);
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
    }

    void HighLevelIR::visitVarAssignment(IronParser::VarAssignmentContext *ctx)
    {
        util::printf("visitVarAssignment", "");
    }

    void HighLevelIR::visitVarDeclaration(IronParser::VarDeclarationContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        int line = ctx->getStart()->getLine();
        const std::string scopeName = scopeManager->currentScopeName();

        if (tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        {
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            // util::printf("varName: {}, alias: {}", alias, varName);

            scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr, {}, alias});
            if (ctx->assignment())
            {
                visitAssignment(ctx->assignment(), sb);
            }

            *sb << util::format("let {}:{} = fptr {}\n", varName, varType, alias);
        }
        else
        {
            scopeManager->currentScope()->addSymbol(varName, {tokenMap::VARIABLE, tokenMap::getTokenType(varType), nullptr});
            if (ctx->assignment())
            {
                visitAssignment(ctx->assignment(), sb);
            }
        }
    }

    void HighLevelIR::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        std::string visibility;
        if (ctx->PUBLIC())
        {
            visibility = tokenMap::getTokenText(tokenMap::PUBLIC);
        }
        else
        {
            visibility = tokenMap::getTokenText(tokenMap::PRIVATE);
        }
        const auto fn = ctx->FUNCTION()->getText();
        const auto functionName = ctx->functionName->getText();

        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));

        std::string returnType;
        if (ctx->functionSignature()->functionReturnType())
        {
            returnType = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(functionName, {tokenMap::FUNCTION, tokenMap::getTokenType(returnType), nullptr});
        }
        else
        {
            returnType = tokenMap::getTokenText(tokenMap::VOID);
            globalScope->addSymbol(functionName, {tokenMap::FUNCTION, tokenMap::VOID, nullptr});
        }

        scopeManager->enterScope(functionName);
        auto writer = writerCodeHLIR->getWriter(functionName);

        *writer->localSb << util::format("{} {} {} (", visibility, fn, functionName);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature(), writer->localSb);
        }

        *writer->localSb << util::format("): {} { \n", returnType); //"" << returnType << "{"
        for (auto child : ctx->children)
        {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext *>(child))
            {
                visitStatementList(statementList, writer->localSb);
            }
        }

        *writer->localSb << util::format("} \n", returnType);
        scopeManager->exitScope(functionName);
    }

    void HighLevelIR::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        if (ctx->functionArgs())
        {
            visitFunctionArgs(ctx->functionArgs(), sb);
        }
    }

    void HighLevelIR::visitFunctionArgs(IronParser::FunctionArgsContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        int commaCount = ctx->COMMA().size();
        int argIndex = 0;

        // Para cada filho que seja FunctionArgContext
        for (auto *child : ctx->children)
        {
            if (auto *arg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                bool hasComma = (argIndex < commaCount);
                visitFunctionArg(arg, hasComma, sb);
                // util::printf("arg: {}", arg->getText());
                argIndex++;
            }
        }
    }

    void HighLevelIR::visitFunctionArg(IronParser::FunctionArgContext *ctx, bool comma, std::shared_ptr<std::stringstream> sb)
    {
        const auto argName = ctx->varName->getText();
        const auto dataType = ctx->varTypes()->getText();

        if (comma)
        {
            *sb << util::format("{}:{}, ", argName, dataType);
        }
        else
        {
            *sb << util::format("{}:{}", argName, dataType);
        }

        scopeManager->currentScope()->addSymbol(argName, {tokenMap::ARGUMENT, tokenMap::getTokenType(dataType), nullptr});

        // adicionao argumento da função ao escopo global
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));

        if (auto *globalFunctionPtr = globalScope->lookupPtr(scopeManager->currentScopeName()))
        {
            globalFunctionPtr->args.emplace_back(argName, tokenMap::getTokenType(dataType));
        }
    }

    void HighLevelIR::visitFunctionCall(IronParser::FunctionCallContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        // auto mainTypeSymbolInfo = currentScope->lookup(tokenMap::MAIN_TYPE);
        auto parentScope = scopeManager->currentScope(); //->getParent();
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        auto functionName = ctx->functionName->getText();
        // util::printf("functionName: {}", functionName);
        // util::printf("functionName {}", functionName);
        auto functionSymbolInfo = globalScope->lookup(functionName);
        if (functionSymbolInfo.has_value())
        {

            int dataType = functionSymbolInfo.value().dataType;
            *sb << util::format("call {} {}(", tokenMap::getTokenText(dataType), functionName);

            if (ctx->functionCallArgs())
            {
                visitFunctionCallArgs(ctx->functionCallArgs(), sb);
            }

            *sb << util::format("{}\n", ")");
        }
        else
        {
            const std::string globalFunctionName = createFunctionName(parentScope->getName(), functionName);
            // util::printf("Expr globalFunctionName: {}", globalFunctionName);
            auto globalFunctionOpt = globalScope->lookup(globalFunctionName);
            if (globalFunctionOpt.has_value())
            {
                int dataType = globalFunctionOpt.value().dataType;
                *sb << util::format("call {} {}()\n", tokenMap::getTokenText(dataType), functionName);
            }
            else
            {

                throw hlir::HLIRException(util::format("HLIR Error: Function fn {} not found", functionName));
            }
        }
    }

    void HighLevelIR::visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx, std::shared_ptr<std::stringstream> sb)
    {
        int commaCount = ctx->COMMA().size();
        int argIndex = 0;
        for (auto *child : ctx->children)
        {
            if (auto *arg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                bool hasComma = (argIndex < commaCount);
                visitFunctionCallArg(arg, hasComma, sb);
                argIndex++;
            }
        }
    }

    void HighLevelIR::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx, bool hasComma, std::shared_ptr<std::stringstream> sb)
    {

        auto currentScope = scopeManager->currentScope();
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));

        auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent->parent);
        std::string functionName = funcCall->functionName->getText();

        util::printf("functionName: {}", functionName);

        *sb << util::format("{}:", ctx->varName->getText());

        auto functionOpt = currentScope->lookup(functionName);
        if (functionOpt.has_value())
        {
            util::printf("Ponteiro para função", "");
        }

        auto gBfunctionOpt = globalScope->lookup(functionName);
        if (gBfunctionOpt.has_value())
        {
            util::printf("Função Global", "");
        }

        if (ctx->anotherVarName)
        {
            if (hasComma)
            {
                *sb << util::format("{}, ", ctx->anotherVarName->getText());
            }
            else
            {
                *sb << util::format("{} ", ctx->anotherVarName->getText());
            }
        }

        if (ctx->dataFormat())
        {
            std::string value = ctx->dataFormat()->getText();

            if (hasComma)
            {
                *sb << util::format("{}, ", value);
            }
            else
            {
                *sb << util::format("{} ", value);
            }
        }

        if (ctx->functionCall())
        {
            std::string functionName = ctx->functionCall()->functionName->getText();
            *sb << util::format("{}(", functionName);
            if (ctx->functionCall()->functionCallArgs())
            {
                visitFunctionCallArgs(ctx->functionCall()->functionCallArgs(), sb);
            }

            if (hasComma)
            {
                *sb << util::format("),", functionName);
            }
            else
            {
                *sb << util::format(")", functionName);
            }
        }
    }

    void HighLevelIR::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx)
    {
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            // Nome "original" da arrow function
            std::string arrowFuncName = varDeclaration->varName->getText();

            // Cria um nome único para a função no escopo global
            std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType())
            {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            }
            else
            {
                returnTypeStr = tokenMap::getTokenText(tokenMap::VOID);
            }

            // Adiciona a função ao escopo global
            globalScope->addSymbol(
                globalFunctionName,
                {tokenMap::FUNCTION,
                 tokenMap::getTokenType(returnTypeStr),
                 nullptr,
                 {},
                 arrowFuncName});

            // Entra no escopo da função inline
            scopeManager->enterScope(globalFunctionName);
            auto writer = writerCodeHLIR->getWriter(globalFunctionName);
            // Escreve a declaração da função no globalSb
            *writer->localSb << util::format("private fn {}(",
                                             globalFunctionName);

            if (ctx->functionSignature()->functionArgs())
            {
                visitFunctionArgs(ctx->functionSignature()->functionArgs(), writer->localSb);
            }

            *writer->localSb << util::format("):{} {\n",
                                             returnTypeStr);

            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList(), writer->localSb);
            }

            *writer->localSb << util::format("}\n", "");
            // Sai do escopo
            scopeManager->exitScope(globalFunctionName);
        }
    }

    void HighLevelIR::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx)
    {
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            // Nome "original" da arrow function
            std::string arrowFuncName = varDeclaration->varName->getText();

            // Cria um nome único para a função no escopo global
            std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType())
            {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            }
            else
            {
                returnTypeStr = tokenMap::getTokenText(tokenMap::VOID);
            }

            // Adiciona a função ao escopo global
            globalScope->addSymbol(
                globalFunctionName,
                {tokenMap::FUNCTION,
                 tokenMap::getTokenType(returnTypeStr),
                 nullptr,
                 {},
                 arrowFuncName});

            // Entra no escopo da função inline
            scopeManager->enterScope(globalFunctionName);

            auto writer = writerCodeHLIR->getWriter(globalFunctionName);

            // Escreve a declaração da função no globalSb
            *writer->localSb << util::format("private fn {}(",
                                             globalFunctionName);

            if (ctx->functionSignature()->functionArgs())
            {
                visitFunctionArgs(ctx->functionSignature()->functionArgs(), writer->localSb);
            }

            *writer->localSb << util::format("):{} {\n",
                                             returnTypeStr);

            if (ctx->expr())
            {
                visitExpr(ctx->expr(), writer->localSb);
            }

            *writer->localSb << util::format("}\n", "");
            // Sai do escopo
            scopeManager->exitScope(globalFunctionName);
        }
    }

    void HighLevelIR::visitReturn(IronParser::ReturnStatementContext *ctx)
    {
    }

} // namespace iron

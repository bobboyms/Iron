#include "headers/HighLevelIR.h"
#include "headers/IronExceptions.h"
#include "headers/Colors.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"
#include <iostream>

namespace iron {

    HighLevelIR::HighLevelIR(std::shared_ptr<IronParser> parser, 
                                           std::unique_ptr<ScopeManager> scopeManager)
        : parser(parser), scopeManager(std::move(scopeManager)) 
    {
    }

    HighLevelIR::~HighLevelIR() 
    {
    }

    std::string HighLevelIR::generateTempVar() {
        return "tmp_" + std::to_string(++tempVarCounter);
    }

    std::string HighLevelIR::generateCode() 
    {
        scopeManager->enterScope(TokenMap::getTokenText(TokenMap::GLOBAL));
        IronParser::ProgramContext* programContext = parser->program();

        // Processa todas as declarações no programa
        for (auto child : programContext->children) {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext*>(child)) {
                visitFunctionDeclaration(funcDecl);
            }
        }

        // Finaliza o escopo global após processar todas as declarações
        scopeManager->exitScope(TokenMap::getTokenText(TokenMap::GLOBAL));
        
        return sb.str();
    }

    void HighLevelIR::visitStatementList(IronParser::StatementListContext* ctx) 
    {
        for (auto child : ctx->children) {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(child)) {
                visitVarDeclaration(varDeclaration);
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
                visitVarAssignment(varAssignment);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext*>(child)) {
                visitExpr(expression);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnContext*>(child)) {
                visitReturn(returnctx);
            }
        }
    }

    std::string HighLevelIR::visitExpr(IronParser::ExprContext* ctx) 
    {
        auto currentScope = scopeManager->currentScope();
        
        // Verifica se a expressão é parte de uma declaração de variável
        if (auto declaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
            currentScope->addSymbol(TokenMap::MAIN_TYPE, {TokenMap::VARIABLE, TokenMap::getTokenType(declaration->varTypes()->getText()), nullptr});
        }        

        if (ctx->L_PAREN() && ctx->R_PAREN()) {
            for (auto child : ctx->children) {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext*>(child)) {
                    return visitExpr(subExpr);
                }
            }
        }

        int line = ctx->start->getLine();

        // Determina a operação
        std::string operation;
        if (ctx->mult) {
            operation = "MULT";
        } else if (ctx->div) {
            operation = "DIV";
        } else if (ctx->plus) {
            operation = "PLUS";
        } else if (ctx->minus) {
            operation = "MINUS";
        }

        // Verifica se é uma expressão binária
        if (!operation.empty() && ctx->left != nullptr && ctx->right != nullptr) {

            auto symbolInfo = currentScope->lookup(TokenMap::MAIN_TYPE);

            // Visita os lados esquerdo e direito da expressão
            std::string leftVar = visitExpr(ctx->left);
            std::string rightVar = visitExpr(ctx->right);            

            // Gere uma variável temporária para o resultado
            if (!leftVar.empty()) {
                
                auto rightSymbolOpt = currentScope->lookup(rightVar);
                // Verifica se é necessário fazer um cast
                if (rightSymbolOpt.has_value()) {
                    auto rightSymbol = rightSymbolOpt.value();

                    if (rightSymbol.dataType != symbolInfo->dataType) {
                        iron::printf("Right: {}, Left: {}", rightVar, leftVar);
                        std::string tempVar = generateTempVar();
                        currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, symbolInfo->dataType, nullptr});
                        sb << iron::format("let {}:{} = {} {} to {}\n", tempVar, TokenMap::getTokenText(symbolInfo->dataType), rightVar, TokenMap::getTokenText(rightSymbol.dataType), TokenMap::getTokenText(symbolInfo->dataType));    
                        rightVar = tempVar;
                    }
                }
                
            }

            std::string tempVar = generateTempVar();
            currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, symbolInfo->dataType, nullptr});
            // Gere a atribuição temporária
            sb << iron::format("let {}:{} = {} {}, {}\n", tempVar, TokenMap::getTokenText(symbolInfo->dataType), operation, leftVar, rightVar);

            return tempVar;
        } 
        // Verifica se é uma variável
        else if (ctx->varName) {
            std::string varName = ctx->varName->getText();
            auto mainTypesymbolInfo = currentScope->lookup(TokenMap::MAIN_TYPE);
            auto variable = currentScope->lookup(varName);
            
            if (variable->dataType != mainTypesymbolInfo->dataType) {
                // Faz o cast
                // let tmp1:float = idade int to float
                std::string tempVar = generateTempVar();
                currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, mainTypesymbolInfo->dataType, nullptr});
                sb << iron::format("let {}:{} = {} {} to {}\n", tempVar, TokenMap::getTokenText(mainTypesymbolInfo->dataType), varName, TokenMap::getTokenText(variable->dataType), TokenMap::getTokenText(mainTypesymbolInfo->dataType));    
                return tempVar;
            }

            return varName;
        } 
        // Verifica se é uma chamada de função
        else if (ctx->functionCall()) {
            //auto mainTypeSymbolInfo = currentScope->lookup(TokenMap::MAIN_TYPE);
            auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
            auto functionName = ctx->functionCall()->functionName->getText();
            //iron::printf("functionName: {}", functionName);
            auto functionSymbolInfo = globalScope->lookup(functionName);
            if (functionSymbolInfo.has_value()) {
                std::string tempVar = generateTempVar(); 
                int dataType = functionSymbolInfo.value().dataType;
                sb << iron::format("let {}:{} = {}()\n", tempVar, TokenMap::getTokenText(dataType), functionName);
                currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, dataType, nullptr});
                return tempVar;
            } else {
                throw SemanticException("Function fn " + functionName + " not found");
            }
        } else if (ctx->number())
        {
            std::string numberLiteral = ctx->number()->getText();
            std::string currentScopeName = scopeManager->currentScopeName();

            int dataType = TokenMap::determineType(numberLiteral);
            //if (dataType == TokenMap::REAL_NUMBER) {
            //    dataType = TokenMap::determineFloatType(numberLiteral);
            //}
            const std::string tempVar = generateTempVar();
            currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, dataType, nullptr});
            sb << iron::format("let {}:{} = {}\n", tempVar, TokenMap::getTokenText(dataType), numberLiteral);
            return tempVar;
        }
        

        throw std::runtime_error("Invalid expression");
    }


    void HighLevelIR::visitAssignment(IronParser::AssignmentContext* ctx) {
            int line = ctx->getStart()->getLine();

            // Se houver um formato de dado literal (ex.: "3.14", "42", etc.)
            if (ctx->dataFormat()) {
                // Caso 1: a atribuição está sendo feita a um argumento de função
                if (auto* functionArg = dynamic_cast<IronParser::FunctionArgContext*>(ctx->parent)) {
                    std::string argName      = functionArg->varName->getText();
                    std::string argType      = functionArg->varTypes()->getText();
                    std::string literalValue = ctx->dataFormat()->getText();
                    int literalType          = TokenMap::determineType(literalValue);

                    sb << iron::format("{}:{} = {}", argName, argType, literalValue);

                }

                // Caso 2: a atribuição está sendo feita a uma variável declarada
                if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent)) {
                    std::string varName      = varDecl->varName->getText();
                    std::string varType      = varDecl->varTypes()->getText();
                    std::string literalValue = ctx->dataFormat()->getText();
                    int literalType          = TokenMap::determineType(literalValue);

                    sb << iron::format("let {}:{} = {}\n", varName, varType, literalValue);                    
                }
            }

            if (ctx->expr()) {
                const auto rightVarName = visitExpr(ctx->expr());
                // Caso 2: a atribuição está sendo feita a uma variável declarada
                if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent)) {
                    std::string varName      = varDecl->varName->getText();
                    std::string varType      = varDecl->varTypes()->getText();

                    sb << iron::format("let {}:{} = {}\n", varName, varType, rightVarName);                    
                }

                
            }

            // Visita todos os filhos que podem ser expressão ou arrow function
            for (auto child : ctx->children) {
                if (auto arrowInline = dynamic_cast<IronParser::ArrowFunctionInlineContext*>(child)) {
                    visitArrowFunctionInline(arrowInline);
                } else if (auto arrowBlock = dynamic_cast<IronParser::ArrowFunctionBlockContext*>(child)) {
                    visitArrowFunctionBlock(arrowBlock);
                }
            }
    }

    void HighLevelIR::visitVarAssignment(IronParser::VarAssignmentContext* ctx) 
    {
    }

    void HighLevelIR::visitVarDeclaration(IronParser::VarDeclarationContext* ctx) {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        int line = ctx->getStart()->getLine();

        const std::string scope = scopeManager->currentScopeName();
        const auto result = scopeManager->currentScope()->lookup(varName);

        if (TokenMap::getTokenType(varType) == TokenMap::FUNCTION) {
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr,{}, alias});
        } else {
            scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});
        }

        if (ctx->assignment()) {
            visitAssignment(ctx->assignment());
        }

    }

    void HighLevelIR::visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx) 
    {   
        std::string visibility;
        if (ctx->PUBLIC()) {
            visibility = TokenMap::getTokenText(TokenMap::PUBLIC);
        } else {
            visibility = TokenMap::getTokenText(TokenMap::PRIVATE);
        }
        const auto fn = ctx->FUNCTION()->getText();
        const auto functionName = ctx->functionName->getText();

        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        
        std::string returnType;
        if (ctx->functionSignature()->functionReturnType()) {
            returnType = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::getTokenType(returnType), nullptr});
        } else {
            returnType = TokenMap::getTokenText(TokenMap::VOID);
            globalScope->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr});
        }

        scopeManager->enterScope(functionName);
        sb << iron::format("{} {} {} (",visibility, fn, functionName);

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature());
        }
        
        sb << iron::format("): {} { \n", returnType); //"" << returnType << "{"
        for (auto child : ctx->children) {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
                visitStatementList(statementList);
            }
        }

        sb << iron::format("} \n", returnType);
        scopeManager->exitScope(functionName);
    
    }

    void HighLevelIR::visitFunctionSignature(IronParser::FunctionSignatureContext* ctx) 
    {
        if (ctx->functionArgs()) {
            visitFunctionArgs(ctx->functionArgs());
        }
    }

    void HighLevelIR::visitFunctionArgs(IronParser::FunctionArgsContext* ctx)
    {
        int commaCount = ctx->COMMA().size(); // quantidade de vírgulas
        int argIndex = 0;

        // Para cada filho que seja FunctionArgContext
        for (auto* child : ctx->children) {
            if (auto* arg = dynamic_cast<IronParser::FunctionArgContext*>(child)) {
                bool hasComma = (argIndex < commaCount); 
                visitFunctionArg(arg, hasComma);
                argIndex++;
            }
        }
    }


    void HighLevelIR::visitFunctionArg(IronParser::FunctionArgContext* ctx, bool comma) 
    {
        const auto argName = ctx->varName->getText();
        const auto dataType = ctx->varTypes()->getText();

        if (comma) {
            sb << iron::format("{}:{}, ", argName, dataType);
        } else {
            sb << iron::format("{}:{}", argName, dataType);
        }

        
    }

    void HighLevelIR::visitFunctionCall(IronParser::FunctionCallContext* ctx,
                                               const std::string& actualFunctionName,
                                               std::shared_ptr<SymbolTable> parentScope) 
    {
    }

    void HighLevelIR::visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx,
                                                   const std::string& actualFunctionName,
                                                   std::shared_ptr<SymbolTable> parentScope) 
    {
    }

    void HighLevelIR::visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                                                  const std::string& actualFunctionName,
                                                  std::shared_ptr<SymbolTable> parentScope) 
    {
    }

    void HighLevelIR::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx) 
    {
    }

    void HighLevelIR::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext* ctx) 
    {
    }

    void HighLevelIR::visitReturn(IronParser::ReturnContext* ctx) 
    {
    }

} // namespace iron

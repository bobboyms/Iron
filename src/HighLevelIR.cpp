#include "headers/HighLevelIR.h"
#include "headers/IronExceptions.h"
#include "headers/Colors.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"


#include <iostream>

namespace iron {

    HighLevelIR::HighLevelIR(std::shared_ptr<IronParser> parser, 
                                           std::unique_ptr<ScopeManager> scopeManager)
        : parser(parser), scopeManager(std::move(scopeManager)), writerCodeHLIR(new WriterCodeHLIR())
    {
    }

    HighLevelIR::~HighLevelIR() 
    {
    }

    std::string HighLevelIR::generateTempVar() {
        return "var_" + std::to_string(++tempVarCounter);
    }
    
    std::shared_ptr<HightLavelIRParser> HighLevelIR::generateParser() {
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
        scopeManager->enterScope(TokenMap::getTokenText(TokenMap::GLOBAL));
        IronParser::ProgramContext* programContext = parser->program();
        

        // Processa todas as declarações no programa
        auto writer = writerCodeHLIR->getWriter(TokenMap::getTokenText(TokenMap::GLOBAL));
        for (auto child : programContext->children) {
            if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext*>(child)) {
                visitFunctionDeclaration(funcDecl);
            }
        }

        

        // Finaliza o escopo global após processar todas as declarações

        scopeManager->exitScope(TokenMap::getTokenText(TokenMap::GLOBAL));
        return writerCodeHLIR->getCode();
    }

    void HighLevelIR::visitStatementList(IronParser::StatementListContext* ctx, std::shared_ptr<std::stringstream> sb) 
    {
        for (auto child : ctx->children) {
            if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(child)) {
                visitVarDeclaration(varDeclaration, sb);
            }
            if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
                visitVarAssignment(varAssignment);
            }
            if (auto expression = dynamic_cast<IronParser::ExprContext*>(child)) {
                visitExpr(expression, sb);
            }
            if (auto returnctx = dynamic_cast<IronParser::ReturnContext*>(child)) {
                visitReturn(returnctx);
            }
        }
    }

    std::string HighLevelIR::visitExpr(IronParser::ExprContext* ctx, std::shared_ptr<std::stringstream> sb) 
    {
        auto currentScope = scopeManager->currentScope();
        
        // Verifica se a expressão é parte de uma declaração de variável
        //if (auto declaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
            //currentScope->addSymbol(TokenMap::MAIN_TYPE, {TokenMap::VARIABLE, TokenMap::getTokenType(declaration->varTypes()->getText()), nullptr});
        //}        

        if (ctx->L_PAREN() && ctx->R_PAREN()) {
            for (auto child : ctx->children) {
                if (auto subExpr = dynamic_cast<IronParser::ExprContext*>(child)) {
                    return visitExpr(subExpr, sb);
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


            // Visita os lados esquerdo e direito da expressão
            std::string leftVar = visitExpr(ctx->left, sb);
            std::string rightVar = visitExpr(ctx->right, sb);     

            auto rightSymbolOpt = currentScope->lookup(rightVar);
            auto leftSymbolOpt = currentScope->lookup(leftVar);       

            if (!leftSymbolOpt.has_value()) {
                throw std::runtime_error(format("HLIR Error: Undefined left variable: {} in expression", leftVar));
            } 

            if (!rightSymbolOpt.has_value()) {
                throw std::runtime_error(format("HLIR Error: Undefined right variable: {} in expression", rightVar));
            }

            auto leftSymbol = leftSymbolOpt.value();
            auto rightSymbol = rightSymbolOpt.value();
            //iron::printf("leftVar: {}, rightSymbol: {}", leftVar, rightVar);
            //iron::printf("leftSymbol: {}, rightSymbol: {}", TokenMap::getTokenText(leftSymbol.dataType), TokenMap::getTokenText(rightSymbol.dataType));

            

            int higherType = TokenMap::getHigherPrecedenceType(leftSymbol.dataType, rightSymbol.dataType);

            if (leftSymbol.dataType != higherType) {
                std::string tempVar = generateTempVar();
                currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, higherType, nullptr});
                *sb << iron::format("let {}:{} = {} {} to {}\n", 
                                    tempVar, 
                                    TokenMap::getTokenText(higherType), 
                                    leftVar, 
                                    TokenMap::getTokenText(leftSymbol.dataType), 
                                    TokenMap::getTokenText(higherType));    
                leftVar = tempVar;
            }

            if (rightSymbol.dataType != higherType) {
                        
                std::string tempVar = generateTempVar();
                currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, higherType, nullptr});
                *sb << iron::format("let {}:{} = {} {} to {}\n", 
                    tempVar, 
                    TokenMap::getTokenText(higherType), 
                    rightVar, TokenMap::getTokenText(rightSymbol.dataType), 
                    TokenMap::getTokenText(higherType));    
                rightVar = tempVar;
            }

            std::string tempVar = generateTempVar();
            currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, higherType, nullptr});
            // Gere a atribuição temporária
            *sb << iron::format("let {}:{} = {} {}, {}\n", 
                tempVar, 
                TokenMap::getTokenText(higherType), 
                operation, 
                leftVar, 
                rightVar);

            return tempVar;
        } 
        // Verifica se é uma variável
        else if (ctx->varName) {
            std::string varName = ctx->varName->getText();
            return varName;

        } 
        // Verifica se é uma chamada de função
        else if (ctx->functionCall()) {
            //auto mainTypeSymbolInfo = currentScope->lookup(TokenMap::MAIN_TYPE);
            auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
            auto functionName = ctx->functionCall()->functionName->getText();
            //iron::printf("functionName: {}", functionName);
            iron::printf("functionName {}", functionName);
            auto functionSymbolInfo = globalScope->lookup(functionName);
            if (functionSymbolInfo.has_value()) {
                std::string tempVar = generateTempVar(); 
                int dataType = functionSymbolInfo.value().dataType;
                *sb << iron::format("let {}:{} = {}()\n", tempVar, TokenMap::getTokenText(dataType), functionName);
                currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, dataType, nullptr});
                return tempVar;
            } else {
                const std::string globalFunctionName = createFunctionName(currentScope->getName(), functionName);
                //iron::printf("Expr globalFunctionName: {}", globalFunctionName);
                auto globalFunctionOpt = globalScope->lookup(globalFunctionName);
                if (globalFunctionOpt.has_value()) {
                    std::string tempVar = generateTempVar(); 
                    int dataType = globalFunctionOpt.value().dataType;
                    *sb << iron::format("let {}:{} = {}()\n", tempVar, TokenMap::getTokenText(dataType), functionName);
                    currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, dataType, nullptr});
                    return tempVar;

                } else {
                    throw std::runtime_error("HLIR Error: Function fn " + functionName + " not found");
                }
                 
            }
        } else if (ctx->number())
        {
            std::string numberLiteral = ctx->number()->getText();
            std::string currentScopeName = scopeManager->currentScopeName();

            int dataType = TokenMap::determineType(numberLiteral);

            if (dataType == TokenMap::REAL_NUMBER) {
                dataType = TokenMap::determineFloatType(numberLiteral);
            }
            
            const std::string tempVar = generateTempVar();
            currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, dataType, nullptr});
            *sb << iron::format("let {}:{} = {}\n", tempVar, TokenMap::getTokenText(dataType), numberLiteral);
            return tempVar;
        }
    
        throw std::runtime_error("Invalid expression");
    }


    void HighLevelIR::visitAssignment(IronParser::AssignmentContext* ctx, std::shared_ptr<std::stringstream> sb) {
            int line = ctx->getStart()->getLine();
            auto currentScope = scopeManager->currentScope();

            // Se houver um formato de dado literal (ex.: "3.14", "42", etc.)
            if (ctx->dataFormat()) {
                // Caso 1: a atribuição está sendo feita a um argumento de função
                if (auto* functionArg = dynamic_cast<IronParser::FunctionArgContext*>(ctx->parent)) {
                    std::string argName      = functionArg->varName->getText();
                    std::string argType      = functionArg->varTypes()->getText();
                    std::string literalValue = ctx->dataFormat()->getText();
                    int literalType          = TokenMap::determineType(literalValue);

                    *sb << iron::format("{}:{} = {}", argName, argType, literalValue);

                }

                // Caso 2: a atribuição está sendo feita a uma variável declarada
                if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent)) {
                    std::string varName      = varDecl->varName->getText();
                    std::string varType      = varDecl->varTypes()->getText();
                    std::string literalValue = ctx->dataFormat()->getText();
                    int literalType          = TokenMap::determineType(literalValue);

                    *sb << iron::format("let {}:{} = {}\n", varName, varType, literalValue);                    
                }
            }

            if (ctx->expr()) {
                const auto rightVarName = visitExpr(ctx->expr(), sb);
                const auto rightSymbolOpt = currentScope->lookup(rightVarName);
                if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent)) {
                    std::string leftVarName      = varDecl->varName->getText();
                    std::string leftvarTypeName = varDecl->varTypes()->getText();
                    //const auto leftSymbolOpt = currentScope->lookup(leftVarName);

                    int leftDataTypeType      = TokenMap::getTokenType(leftvarTypeName);


                    if (leftDataTypeType != rightSymbolOpt->dataType) {
                        std::string tempVar = generateTempVar();
                        currentScope->addSymbol(tempVar, {TokenMap::VARIABLE, leftDataTypeType, nullptr});
                        *sb << iron::format("let {}:{} = {} {} to {}\n", 
                                            tempVar, 
                                            leftvarTypeName, 
                                            rightVarName, 
                                            TokenMap::getTokenText(rightSymbolOpt->dataType), 
                                            leftvarTypeName);    

                        *sb << iron::format("let {}:{} = {}\n", leftVarName, leftvarTypeName, tempVar);
                    } else {
                        *sb << iron::format("let {}:{} = {}\n", leftVarName, leftvarTypeName, rightVarName);
                    }

                }
                
            }

            if (ctx->arrowFunctionInline()) {
                visitArrowFunctionInline(ctx->arrowFunctionInline());
            } 
            

             if (ctx->arrowFunctionBlock()) {
                visitArrowFunctionBlock(ctx->arrowFunctionBlock());
            }
            

            
    }

    void HighLevelIR::visitVarAssignment(IronParser::VarAssignmentContext* ctx) 
    {
        iron::printf("visitVarAssignment","");
    }

    void HighLevelIR::visitVarDeclaration(IronParser::VarDeclarationContext* ctx, std::shared_ptr<std::stringstream> sb) {
        std::string varName = ctx->varName->getText();
        std::string varType = ctx->varTypes()->getText();

        int line = ctx->getStart()->getLine();
        const std::string scopeName = scopeManager->currentScopeName();

        if (TokenMap::getTokenType(varType) == TokenMap::FUNCTION) {
            auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
            //iron::printf("varName: {}, alias: {}", alias, varName);

            scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr,{}, alias});
            if (ctx->assignment()) {
                visitAssignment(ctx->assignment(), sb);
            }

            *sb << iron::format("let {}:{} = {}\n", varName, varType, alias);

        } else {
            scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});
            if (ctx->assignment()) {
                visitAssignment(ctx->assignment(), sb);
            }
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
        auto writer = writerCodeHLIR->getWriter(functionName);

        *writer->localSb << iron::format("{} {} {} (",visibility, fn, functionName);

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature(), writer->localSb);
        }
        
        *writer->localSb << iron::format("): {} { \n", returnType); //"" << returnType << "{"
        for (auto child : ctx->children) {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
                visitStatementList(statementList, writer->localSb);
            }
        }

        *writer->localSb << iron::format("} \n", returnType);
        scopeManager->exitScope(functionName);
    
    }

    void HighLevelIR::visitFunctionSignature(IronParser::FunctionSignatureContext* ctx, std::shared_ptr<std::stringstream> sb) 
    {
        if (ctx->functionArgs()) {
            visitFunctionArgs(ctx->functionArgs(), sb);
        }
    }

    void HighLevelIR::visitFunctionArgs(IronParser::FunctionArgsContext* ctx, std::shared_ptr<std::stringstream> sb)
    {
        int commaCount = ctx->COMMA().size();
        int argIndex = 0;

        // Para cada filho que seja FunctionArgContext
        for (auto* child : ctx->children) {
            if (auto* arg = dynamic_cast<IronParser::FunctionArgContext*>(child)) {
                bool hasComma = (argIndex < commaCount); 
                visitFunctionArg(arg, hasComma, sb);
                //iron::printf("arg: {}", arg->getText());
                argIndex++;
            }
        }
    }


    void HighLevelIR::visitFunctionArg(IronParser::FunctionArgContext* ctx, bool comma, std::shared_ptr<std::stringstream> sb) 
    {
        const auto argName = ctx->varName->getText();
        const auto dataType = ctx->varTypes()->getText();

        if (comma) {
            *sb << iron::format("{}:{}, ", argName, dataType);
        } else {
            *sb << iron::format("{}:{}", argName, dataType);
        }

        scopeManager->currentScope()->addSymbol(argName, {TokenMap::ARGUMENT, TokenMap::getTokenType(dataType), nullptr});

        //adicionao argumento da função ao escopo global
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

        if (auto* globalFunctionPtr = globalScope->lookupPtr(scopeManager->currentScopeName())) {    
            globalFunctionPtr->args.emplace_back(argName, TokenMap::getTokenType(dataType));
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

    void HighLevelIR::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext* ctx) {
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto* varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
            // Nome "original" da arrow function
            std::string arrowFuncName = varDeclaration->varName->getText();

            // Cria um nome único para a função no escopo global
            std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType()) {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            } else {
                returnTypeStr = TokenMap::getTokenText(TokenMap::VOID);
            }

            // Adiciona a função ao escopo global
            globalScope->addSymbol(
                globalFunctionName,
                {
                    TokenMap::FUNCTION, 
                    TokenMap::getTokenType(returnTypeStr),
                    nullptr,
                    {},
                    arrowFuncName
                }
            );

            

            // Entra no escopo da função inline
            scopeManager->enterScope(globalFunctionName);
            auto writer = writerCodeHLIR->getWriter(globalFunctionName);
            // Escreve a declaração da função no globalSb
            *writer->localSb << iron::format("private fn {}(", 
                                    globalFunctionName);

            
            if (ctx->functionSignature()->functionArgs()) {
                visitFunctionArgs(ctx->functionSignature()->functionArgs(), writer->localSb);
            }

            *writer->localSb << iron::format("):{} {\n", 
                                    returnTypeStr);
            
            if (ctx->statementList()) {
                visitStatementList(ctx->statementList(), writer->localSb);
            }

            

            *writer->localSb << iron::format("}\n", "");
            // Sai do escopo
            scopeManager->exitScope(globalFunctionName);
            
            
        }
    }

    void HighLevelIR::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx) {
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
        std::string currentScopeName = scopeManager->currentScopeName();

        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (auto* varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
            // Nome "original" da arrow function
            std::string arrowFuncName = varDeclaration->varName->getText();

            // Cria um nome único para a função no escopo global
            std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType()) {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            } else {
                returnTypeStr = TokenMap::getTokenText(TokenMap::VOID);
            }

            // Adiciona a função ao escopo global
            globalScope->addSymbol(
                globalFunctionName,
                {
                    TokenMap::FUNCTION, 
                    TokenMap::getTokenType(returnTypeStr),
                    nullptr,
                    {},
                    arrowFuncName
                }
            );

            // Entra no escopo da função inline
            scopeManager->enterScope(globalFunctionName);

            auto writer = writerCodeHLIR->getWriter(globalFunctionName);

            // Escreve a declaração da função no globalSb
            *writer->localSb << iron::format("private fn {}(", 
                                    globalFunctionName);

            if (ctx->functionSignature()->functionArgs()) {
                visitFunctionArgs(ctx->functionSignature()->functionArgs(), writer->localSb);
            }

            *writer->localSb << iron::format("):{} {\n", 
                                    returnTypeStr);
            
            if (ctx->expr()) {
                visitExpr(ctx->expr(), writer->localSb);
            }

            *writer->localSb << iron::format("}\n", "");
            // Sai do escopo
            scopeManager->exitScope(globalFunctionName);

            
        }
    }

    void HighLevelIR::visitReturn(IronParser::ReturnContext* ctx) 
    {
    }

} // namespace iron

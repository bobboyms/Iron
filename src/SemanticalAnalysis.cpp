#include "headers/SemanticalAnalysis.h"
#include "headers/IronExceptions.h"
#include "headers/Colors.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"
#include <iostream>

// Construtor
SemanticalAnalysis::SemanticalAnalysis(std::unique_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager)
    : parser(std::move(parser)), scopeManager(std::move(scopeManager)) {
}

// Destrutor
SemanticalAnalysis::~SemanticalAnalysis() {
}

// Método principal para análise semântica
void SemanticalAnalysis::analyze() {
    // Inicializa o escopo global

    scopeManager->enterScope(TokenMap::getTokenText(TokenMap::GLOBAL)); //start(TokenMap::getTokenText(TokenMap::GLOBAL));
    IronParser::ProgramContext* programContext = parser->program();

    // Processa todas as declarações no programa
    for (auto child : programContext->children) {
        if (auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext*>(child)) {
            visitFunctionDeclaration(funcDecl);
        }
    }

    // Finaliza o escopo global após processar todas as declarações
    scopeManager->exitScope(TokenMap::getTokenText(TokenMap::GLOBAL));
}

void SemanticalAnalysis::visitStatementList(IronParser::StatementListContext* ctx) {
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

void SemanticalAnalysis::visitExpr(IronParser::ExprContext* ctx) {
    struct PreviousVarStruct {
        std::string name;
        int localDatatype;
        int type;
    };

    static PreviousVarStruct reviousVarStruct;
    int line = ctx->getStart()->getLine();

    auto validatePreviousVariable = [&](const std::string& varName, int currentDatatype, int type, const std::string& scope) {
        auto optPreviousSymbolInfo = scopeManager->currentScope()->lookup(reviousVarStruct.name);

        if (!optPreviousSymbolInfo.has_value()) {
            reviousVarStruct.name.clear();
        } else {

            SymbolInfo previousSymbolInfo = optPreviousSymbolInfo.value();

            if (TokenMap::isNumber(currentDatatype) != TokenMap::isNumber(previousSymbolInfo.dataType)) {
                std::string errMessage;
                if (type == TokenMap::FUNCTION) {
                    errMessage =  "The return of fn {} is incompatible with Variable {}. Line: {}, Scope: {}";
                } else if (type == TokenMap::VARIABLE) {
                     errMessage = "Variable {} is incompatible with Variable {}. Line: {}, Scope: {}";
                } else if (type == TokenMap::NUMBER) {
                    errMessage = "The number {} is incompatible with Variable {}. Line: {}, Scope: {}";
                }

                throw TypeMismatchException(iron::format(
                    errMessage,
                    color::colorText(varName, color::BOLD_GREEN),
                    color::colorText(reviousVarStruct.name, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW),
                    color::colorText(
                        iron::format("{} {}", 
                            TokenMap::getTokenText(TokenMap::FUNCTION),
                            scope), 
                        color::BOLD_YELLOW)
                ));
            }
        }
    };

    if (ctx->varName) {
        std::string varName = ctx->varName->getText();
        const std::string scope = scopeManager->currentScopeName();
        auto optSymbolInfo = scopeManager->currentScope()->lookup(varName);

        if (!optSymbolInfo.has_value()) {
            throw VariableNotFoundException(iron::format(
                "Variable '{}' not found. Line: {}, Scope: {}",
                color::colorText(varName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    iron::format("{} {}", 
                        TokenMap::getTokenText(TokenMap::FUNCTION),
                        scope), 
                    color::BOLD_YELLOW)
            ));
        }

        if (!reviousVarStruct.name.empty()) {
            SymbolInfo symbolInfo = optSymbolInfo.value();
            if (reviousVarStruct.localDatatype == TokenMap::NUMBER) {
                if (!TokenMap::isNumber(symbolInfo.dataType)) {
                    throw TypeMismatchException(iron::format(
                        "Variable {} is incompatible with Number {}. Line: {}, Scope: {}",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(reviousVarStruct.name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("{} {}", 
                                TokenMap::getTokenText(TokenMap::FUNCTION),
                                scope), 
                            color::BOLD_YELLOW)
                    ));
                }
            } else {
                validatePreviousVariable(varName, symbolInfo.dataType, symbolInfo.type, scope);
            }
        }

        reviousVarStruct.name = varName;
        reviousVarStruct.localDatatype = optSymbolInfo.value().dataType;
        reviousVarStruct.type = TokenMap::VARIABLE;
    }

    if (ctx->number()) {
        const std::string number = ctx->number()->getText();
        const std::string scope = scopeManager->currentScopeName();

        if (!reviousVarStruct.name.empty()) {
            validatePreviousVariable(number, TokenMap::NUMBER, TokenMap::NUMBER, scope);
        }

        reviousVarStruct.name = number;
        reviousVarStruct.localDatatype = TokenMap::NUMBER;
        reviousVarStruct.type = TokenMap::NUMBER;
    }

    if (ctx->functionCall()) {

        std::string functionName = ctx->functionCall()->functionName->getText();
        std::string currentScopeName = scopeManager->currentScopeName();
        auto currentScope = scopeManager->currentScope();
        auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

        std::string globalFunctionName;
        std::optional<SymbolInfo> result;

        auto functionNameResult = currentScope->lookup(functionName);
        if (functionNameResult.has_value()) {
            if (functionNameResult.value().dataType == TokenMap::FUNCTION) {
                globalFunctionName = functionNameResult->alias;
                result = globalScope->lookup(globalFunctionName);
            } else {
                globalFunctionName = functionName;
                result = globalScope->lookup(functionName);
            }
        } else {
            throw FunctionNotFoundException(iron::format(
                "Function '{}' not found. Line: {}, Scope: {}",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    iron::format("{} {}", 
                        TokenMap::getTokenText(TokenMap::FUNCTION),
                        currentScopeName), 
                    color::BOLD_YELLOW)
            ));
        }

        if (!result.has_value()) {
            throw FunctionNotFoundException(iron::format(
                "Function '{}' not found. Line: {}, Scope: {}",
                color::colorText(functionName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW),
                color::colorText(
                    iron::format("{} {}", 
                        TokenMap::getTokenText(TokenMap::FUNCTION),
                        currentScopeName), 
                    color::BOLD_YELLOW)
            ));
        }

        const SymbolInfo& globalFunction = result.value();
        //std::string functionCallName = isLocal ? globalFunctionName : functionName;
        
        
        scopeManager->enterScope(globalFunctionName);
        visitFunctionCall(ctx->functionCall(), globalFunctionName, currentScope);
        scopeManager->exitScope(globalFunctionName);

        // Verifica compatibilidade com a variável anterior, se existir
        if (!reviousVarStruct.name.empty()) {
            if (reviousVarStruct.localDatatype == TokenMap::NUMBER) {
                // Se a variável anterior é um número, a função deve retornar um tipo numérico
                if (!TokenMap::isNumber(globalFunction.dataType)) {
                    throw TypeMismatchException(iron::format(
                        "Function return value {} is incompatible with Number {}. Line: {}, Scope: {}",
                        color::colorText(functionName, color::BOLD_GREEN),
                        color::colorText(reviousVarStruct.name, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(
                            iron::format("{} {}",
                                TokenMap::getTokenText(TokenMap::FUNCTION),
                                currentScope),
                            color::BOLD_YELLOW)
                    ));
                }
            } else {
                // Caso contrário, valida com a função validatePreviousVariable
                //std::string validatedFunctionName = globalFunctionName;
                validatePreviousVariable(globalFunctionName, globalFunction.dataType, TokenMap::FUNCTION, currentScopeName);
            }
        }

        reviousVarStruct.name = globalFunctionName;
        reviousVarStruct.localDatatype = globalFunction.dataType;
        reviousVarStruct.type = TokenMap::FUNCTION;
        
       
    }

    // Visita filhos recursivamente
    for (auto child : ctx->children) {
        if (auto expression = dynamic_cast<IronParser::ExprContext*>(child)) {
            visitExpr(expression);
        }
    }

    // Limpa a variável anterior ao sair do nó raiz
    if (ctx->parent == nullptr) {
        reviousVarStruct.name.clear();
    }
}


void SemanticalAnalysis::visitVarAssignment(IronParser::VarAssignmentContext* ctx) {
    std::string varName = ctx->varName->getText();
    int line = ctx->getStart()->getLine();

    const std::string scope = scopeManager->currentScopeName();
    auto result = scopeManager->currentScope()->lookup(varName);

    if (result.has_value()) {
        SymbolInfo symbolInfo = result.value();
    } else {
        throw VariableNotFoundException(iron::format(
            "Variable '{}' not found. Line: {}, Scope: {}",
            color::colorText(varName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(
                iron::format("{} {}", 
                    TokenMap::getTokenText(TokenMap::FUNCTION),
                    scope), 
                color::BOLD_YELLOW)
        ));
    }
}

void SemanticalAnalysis::visitAssignment(IronParser::AssignmentContext* ctx) {
    
    const int line = ctx->getStart()->getLine();
    
    for (auto child : ctx->children) {
        if (auto expr = dynamic_cast<IronParser::ExprContext*>(child)) {
            visitExpr(expr);
        }
        if (auto function = dynamic_cast<IronParser::ArrowFunctionInlineContext*>(child)) {
            visitArrowFunctionInline(function);
        }
        if (auto function = dynamic_cast<IronParser::ArrowFunctionBlockContext*>(child)) {
            visitArrowFunctionBlock(function);
        }

    }

    if (ctx->dataFormat()) {
        if (auto arg = dynamic_cast<IronParser::FunctionArgContext*>(ctx->parent)) {
            auto argName = arg->varName->getText();
            auto argType = arg->varTypes()->getText();
            auto dataFormat = ctx->dataFormat()->getText();
            auto dataFormatType = TokenMap::determineType(dataFormat);

            if (TokenMap::isRealNumber(TokenMap::getTokenType(argType))) {
                if (TokenMap::REAL_NUMBER != dataFormatType) {
                    throw TypeMismatchException(iron::format(
                        "The type of argument {} is an {}, and the data format {} is {}. Line: {}, Scope: {}",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(argType, color::BOLD_GREEN),
                        color::colorText(dataFormat, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(dataFormatType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(iron::format("fn {}", scopeManager->currentScopeName()), color::YELLOW)
                    ));
                }
                
            } else
            if (TokenMap::getTokenType(argType) != dataFormatType) {
                
                throw TypeMismatchException(iron::format(
                        "The type of argument {} is an {}, and the data format {} is {}. Line: {}, Scope: {}",
                        color::colorText(argName, color::BOLD_GREEN),
                        color::colorText(argType, color::BOLD_GREEN),
                        color::colorText(dataFormat, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(dataFormatType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(iron::format("fn {}", scopeManager->currentScopeName()), color::YELLOW)
                ));

            }

        }
        if (auto var = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent)) {
            auto varName = var->varName->getText();
            auto varType = var->varTypes()->getText();
            auto dataFormat = ctx->dataFormat()->getText();
            auto dataFormatType = TokenMap::determineType(dataFormat);

            if (TokenMap::isRealNumber(TokenMap::getTokenType(varType))) {
                if (TokenMap::REAL_NUMBER != dataFormatType) {
                    throw TypeMismatchException(iron::format(
                        "The type of argument {} is an {}, and the data format {} is {}. Line: {}, Scope: {}",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(varType, color::BOLD_GREEN),
                        color::colorText(dataFormat, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(dataFormatType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(iron::format("fn {}", scopeManager->currentScopeName()), color::YELLOW)
                    ));
                }
                
            } else
            if (TokenMap::getTokenType(varType) != dataFormatType) {
                
                throw TypeMismatchException(iron::format(
                        "The type of variable {} is an {}, and the data format {} is {}. Line: {}, Scope: {}",
                        color::colorText(varName, color::BOLD_GREEN),
                        color::colorText(varType, color::BOLD_GREEN),
                        color::colorText(dataFormat, color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(dataFormatType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW),
                        color::colorText(iron::format("fn {}", scopeManager->currentScopeName()), color::YELLOW)
                ));

            }

        }
    }

}


// Visita uma declaração de variável e verifica duplicatas
void SemanticalAnalysis::visitVarDeclaration(IronParser::VarDeclarationContext* ctx) {
    std::string varName = ctx->varName->getText();
    std::string varType = ctx->varTypes()->getText();

    int line = ctx->getStart()->getLine();

    const std::string scope = scopeManager->currentScopeName();
    auto result = scopeManager->currentScope()->lookup(varName);

    if (result.has_value()) {
        SymbolInfo symbolInfo = result.value();

        throw VariableRedefinitionException(iron::format(
            "Variable {} already declared. Line: {}, Scope: {}, Type: {}",
            color::colorText(varName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scope, color::BOLD_YELLOW),
            color::colorText(std::to_string(symbolInfo.type), color::CYAN)));
    }

    //auto arrowFunctionName = varDeclaration->varName->getText());
    if (TokenMap::getTokenType(varType) == TokenMap::FUNCTION) {
        auto alias = iron::createFunctionName(scopeManager->currentScope()->getName(), varName);
        scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr,{}, alias});
    } else {
        scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});
    }
    

    if (ctx->assignment()) {
        visitAssignment(ctx->assignment());
    } else {
        throw UninitializedVariableException(iron::format(
            "Variable {} has not been initialized. Line: {}, Scope: {}",
            color::colorText(varName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
    }

    for (auto child : ctx->children) {
        if (auto varAssignment = dynamic_cast<IronParser::VarAssignmentContext*>(child)) {
            visitVarAssignment(varAssignment);
        }
    }

    
}


void SemanticalAnalysis::visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx) {
    if (!ctx->functionName) {
        throw std::runtime_error("Function name is missing.");
    }

    std::string functionName = ctx->functionName->getText();
    int line = ctx->functionName->getLine();

    // Verifica duplicata no escopo global antes de iniciar um novo escopo
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    auto result = globalScope->lookup(functionName);    


    if (result.has_value()) {
        throw FunctionRedefinitionException(iron::format(
            "Function {} already declared. Line: {}, Scope: {}",
            color::colorText(functionName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW)));
    }

    
    if (ctx->functionSignature()->functionReturnType()) {
         std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
         globalScope->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::getTokenType(type), nullptr});
    } else {
         globalScope->addSymbol(functionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr});
    }
    

    scopeManager->enterScope(functionName);

    if (ctx->functionSignature()) {
        visitFunctionSignature(ctx->functionSignature());
    }

    for (auto child : ctx->children) {
        if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
            visitStatementList(statementList);
        }
    }

    scopeManager->exitScope(functionName);
}

void SemanticalAnalysis::visitFunctionSignature(IronParser::FunctionSignatureContext* ctx) {
    for (auto child : ctx->children) {
        if (auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext*>(child)) {
            visitFunctionArgs(functionArgs);
        }
    }
}

void SemanticalAnalysis::visitFunctionArgs(IronParser::FunctionArgsContext* ctx) {
    for (auto child : ctx->children) {
        if (auto functionArg = dynamic_cast<IronParser::FunctionArgContext*>(child)) {
            visitFunctionArg(functionArg);
        }
    }
}

void SemanticalAnalysis::visitFunctionArg(IronParser::FunctionArgContext* ctx) {
    std::string varName = ctx->varName->getText();
    std::string varType = ctx->varTypes()->getText();
    int line = ctx->getStart()->getLine();

    const std::string scope = scopeManager->currentScopeName();
    auto result = scopeManager->currentScope()->lookup(varName);


    if (result.has_value()) {
        SymbolInfo symbolInfo = result.value();

        throw VariableRedefinitionException(iron::format(
            "Function arg {} already declared. Line: {}, Scope: fn {}",
            color::colorText(varName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW),
            color::colorText(scope, color::BOLD_YELLOW),
            color::colorText(TokenMap::getTokenText(symbolInfo.type), color::CYAN)));
    }

    // adciona argumento da função ao escopo atual
    scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});

    if (ctx->assignment()) {
        visitAssignment(ctx->assignment());
    }

    //adicionao argumento da função ao escopo global
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

    if (auto* globalFunctionPtr = globalScope->lookupPtr(scopeManager->currentScopeName())) {    
        globalFunctionPtr->args.emplace_back(varName, TokenMap::getTokenType(varType));
    }
}

void SemanticalAnalysis::visitFunctionCall(IronParser::FunctionCallContext* ctx,
                                           const std::string& actualFunctionName,
                                           std::shared_ptr<SymbolTable> parentScope)
{

    auto line = ctx->getStart()->getLine();
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    auto globalFunctionSymbalInfo = globalScope->lookup(ctx->functionName->getText());

    SymbolInfo functionSymbolInfo = globalScope->lookup(actualFunctionName).value();
    auto globalArgsSize = functionSymbolInfo.args.size();
    // Se a call tem argumentos
    if (ctx->functionCallArgs()) {
        
        int callArgsSize = 0;
        for (auto child : ctx->functionCallArgs()->children) {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
                callArgsSize+=1;
            }
        }

        std::string aliasName = !functionSymbolInfo.alias.empty() ? functionSymbolInfo.alias : actualFunctionName;


        if (globalArgsSize != callArgsSize) {
            throw ArgumentCountMismatchException(iron::format(
                "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                color::colorText(
                    iron::format("fn {}", aliasName), color::BOLD_GREEN),
                color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                color::colorText(std::to_string(callArgsSize), color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)
            ));
        }
    
        visitFunctionCallArgs(ctx->functionCallArgs(), actualFunctionName, parentScope);
    } else {
        if (globalArgsSize > 0) {
            throw ArgumentCountMismatchException(iron::format(
                "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                color::colorText(
                    iron::format("fn {}", functionSymbolInfo.alias), color::BOLD_GREEN),
                color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                color::colorText(std::to_string(0), color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)
            ));
        }
    }
}


// Visita a lista de argumentos da função "actualFunctionName"
void SemanticalAnalysis::visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx,
                                               const std::string& actualFunctionName,
                                               std::shared_ptr<SymbolTable> parentScope)
{   
    
    for (auto child : ctx->children) {
        if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
            visitFunctionCallArg(functionCallArg, actualFunctionName, parentScope);
        }
    }


    
    std::vector<std::string> sequenceOfArgs;
    for (auto child : ctx->children) {
        if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
            sequenceOfArgs.push_back(functionCallArg->varName->getText());
        }
    }

    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    auto globalFunction = globalScope->lookup(actualFunctionName).value();
    auto args = globalFunction.args;

    for (size_t i = 0; i < args.size(); ++i) {
        if (sequenceOfArgs[i] != args[i].first) { // args[i].first é o nome do argumento formal
            throw ArgumentOrderMismatchException(iron::format(
                "Argument order mismatch in function '{}'. Expected '{}', but got '{}'.",
                color::colorText(iron::format("fn {}", globalFunction.alias),color::BOLD_GREEN),
                color::colorText(args[i].first,color::BOLD_GREEN),
                color::colorText(sequenceOfArgs[i], color::BOLD_GREEN)
            ));
        }
    }
}

// Visita um único argumento "argName" de "actualFunctionName"
void SemanticalAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                                              const std::string& actualFunctionName,
                                              std::shared_ptr<SymbolTable> parentScope) {
    auto line = ctx->getStart()->getLine();

    // O nome do parâmetro formal
    auto argName = ctx->varName->getText();

    // Procura a função (actualFunctionName) no escopo global
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    if (!globalScope) {
        throw std::runtime_error("Global scope not found.");
    }

    auto globalFunctionOpt = globalScope->lookup(actualFunctionName);
    if (!globalFunctionOpt.has_value()) {
        throw FunctionNotFoundException(iron::format(
            "Function fn {} not found. Line: {}",
            color::colorText(actualFunctionName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW)));
    }

    // Verifica se "argName" existe na lista de parâmetros formais dessa função
    auto argOpt = iron::getArgumentByName(globalFunctionOpt.value(), argName);
    if (!argOpt.has_value()) {
        throw FunctionArgNotFoundException(iron::format(
            "Argument {} not found in function fn {}. Line: {}",
            color::colorText(argName, color::BOLD_GREEN),
            color::colorText(actualFunctionName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW)));
    }

    auto [foundArgName, foundArgType] = *argOpt;

    // Se o parser identificou algo como 'dataFormat', checa o tipo do valor literal
    if (ctx->dataFormat()) {
        bool isIntLiteral = ctx->dataFormat()->INT_NUMBER();
        bool isRealLiteral = ctx->dataFormat()->REAL_NUMBER();

        if (foundArgType == TokenMap::TYPE_INT && !isIntLiteral) {
            throw TypeMismatchException(iron::format(
                "Argument {} is incompatible with type int. Line: {}",
                color::colorText(foundArgName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        } else if ((foundArgType == TokenMap::TYPE_FLOAT || foundArgType == TokenMap::TYPE_DOUBLE) && !isRealLiteral) {
            throw TypeMismatchException(iron::format(
                "Argument {} is incompatible with type {}. Line: {}",
                color::colorText(foundArgName, color::BOLD_GREEN),
                color::colorText(foundArgType == TokenMap::TYPE_FLOAT ? "float" : "double", color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        } else if (isRealLiteral) {
            auto literalType = iron::typeOfRealNumber(ctx->dataFormat()->REAL_NUMBER()->getText());
            if (literalType != foundArgType) {
                throw TypeMismatchException(iron::format(
                    "Argument {} expects type {}, but got {}. Line: {}",
                    color::colorText(foundArgName, color::BOLD_GREEN),
                    color::colorText(TokenMap::getTokenText(foundArgType), color::BOLD_GREEN),
                    color::colorText(TokenMap::getTokenText(literalType), color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }
        }
    }

    // Se o valor do argumento for outra variável
    if (ctx->anotherVarName) {
        auto anotherVarName = ctx->anotherVarName->getText();
        auto anotherVarLookup = parentScope->lookup(anotherVarName);

        if (!anotherVarLookup.has_value()) {
            throw VariableNotFoundException(iron::format(
                "Variable {} not found in that scope (fn {}). Line: {}",
                color::colorText(anotherVarName, color::BOLD_GREEN),
                color::colorText(parentScope->getName(), color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }

        auto symbolInfo = anotherVarLookup.value();
        if (symbolInfo.type != TokenMap::VARIABLE) {
            throw VariableNotFoundException(iron::format(
                "{} is not a variable in that scope (fn {}). Line: {}",
                color::colorText(anotherVarName, color::BOLD_GREEN),
                color::colorText(parentScope->getName(), color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }

        if (foundArgType != symbolInfo.dataType) {
            throw TypeMismatchException(iron::format(
                "Argument {} is incompatible with Variable {}. Line: {}",
                color::colorText(foundArgName, color::BOLD_GREEN),
                color::colorText(anotherVarName, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }
    }

    // Se o valor do argumento for outra função
    if (ctx->functionCall()) {
        auto innerFunctionName = ctx->functionCall()->functionName->getText();
        auto functionNameCalled = innerFunctionName;

        if (!globalScope->lookup(functionNameCalled).has_value()) {
            functionNameCalled = iron::createFunctionName(parentScope->getName(), innerFunctionName);
            if (!globalScope->lookup(functionNameCalled).has_value()) {
                throw FunctionNotFoundException(iron::format(
                    "Function {} not found. Line: {}",
                    color::colorText(innerFunctionName, color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)));
            }
        }

        auto globalInnerFunctionOpt = globalScope->lookup(functionNameCalled);
        if (!globalInnerFunctionOpt.has_value()) {
            throw FunctionNotFoundException(iron::format(
                "Function {} not found. Line: {}",
                color::colorText(functionNameCalled, color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)));
        }

        visitFunctionCall(ctx->functionCall(), functionNameCalled, parentScope);
    }
}


void SemanticalAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx) {
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    auto currentScopeName = scopeManager->currentScopeName();

    if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
        auto arrowFunctionName = varDeclaration->varName->getText();
        std::string globalFunctionName = iron::createFunctionName(currentScopeName, arrowFunctionName);

        if (ctx->functionSignature()->functionReturnType()) {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(globalFunctionName, {TokenMap::FUNCTION, TokenMap::getTokenType(type), nullptr, {}, arrowFunctionName});
        } else {
            globalScope->addSymbol(globalFunctionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr, {}, arrowFunctionName});
        }

        scopeManager->enterScope(globalFunctionName);

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature());
        }

        if (ctx->expr()) {
            visitExpr(ctx->expr());
        }

        scopeManager->exitScope(globalFunctionName);

    }
    
}

void SemanticalAnalysis::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext* ctx) {
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    auto currentScopeName = scopeManager->currentScopeName();

    if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
        auto blockFunctionName = varDeclaration->varName->getText();
        std::string globalFunctionName = iron::createFunctionName(currentScopeName, blockFunctionName);

        if (ctx->functionSignature()->functionReturnType()) {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(globalFunctionName, {TokenMap::FUNCTION, TokenMap::getTokenType(type), nullptr, {}, blockFunctionName});
        } else {
            globalScope->addSymbol(globalFunctionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr, {}, blockFunctionName});
        }

        scopeManager->enterScope(globalFunctionName);

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature());
        }

        if (ctx->statementList()) {
            visitStatementList(ctx->statementList());
        }

        scopeManager->exitScope(globalFunctionName);

    }
}

void SemanticalAnalysis::visitReturn(IronParser::ReturnContext* ctx) {
    if (ctx->expr()) {
        visitExpr(ctx->expr());
    }

    if (ctx->functionCall()) {
        std::string functionName = ctx->functionCall()->functionName->getText();
        visitFunctionCall(ctx->functionCall(), functionName, scopeManager->currentScope());
    }
}
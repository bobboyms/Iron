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
                    color::colorText(iron::getTextAfterUnderscore(reviousVarStruct.name), color::BOLD_GREEN),
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

        bool isLocal = false;
        std::string globalFunctionName;
        std::optional<SymbolInfo> result;

        auto functionNameResult = currentScope->lookup(functionName);
        if (functionNameResult.has_value()) {
            if (functionNameResult.value().dataType == TokenMap::FUNCTION) {
                globalFunctionName = iron::format("{}_{}", currentScopeName, functionName);
                isLocal = true;
                result = globalScope->lookup(globalFunctionName);
            } else {
                auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
                if (!globalScope) {
                    throw std::runtime_error("Global scope not found.");
                }
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

        if (result.has_value()) {
            SymbolInfo arrowFunction = result.value();

            //iron::printf("função encontrada {}, retorno type {}", globalFunctionName, TokenMap::getTokenText(arrowFunction.dataType));
            //scopeManager->currentScope()->printSymbols("GLOBAL");
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

        const SymbolInfo& globalFunction = result.value();
        std::string functionCallName = isLocal ? globalFunctionName : functionName;
        
        
        scopeManager->enterScope(functionCallName);
        visitFunctionCall(ctx->functionCall(), functionCallName, currentScope);
        scopeManager->exitScope(functionCallName);

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
                std::string validatedFunctionName = isLocal ? globalFunctionName : functionName;
                validatePreviousVariable(validatedFunctionName, globalFunction.dataType, TokenMap::FUNCTION, currentScopeName);
            }
        }

        reviousVarStruct.name = isLocal ? globalFunctionName : functionName;
        reviousVarStruct.localDatatype = isLocal 
            ? scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL))->lookup(globalFunctionName).value().dataType 
            : globalFunction.dataType;
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

    }

    if (ctx->dataFormat()) {
        if (auto arg = dynamic_cast<IronParser::FunctionArgContext*>(ctx->parent)) {
            auto argName = arg->varName->getText();
            auto argType = arg->varTypes()->getText();
            auto dataFormat = ctx->dataFormat()->getText();
            auto dataFormatType = TokenMap::determineType(dataFormat);

            if (TokenMap::isRealNumber(TokenMap::getTokenType(argType))) {
                //iron::printf("É numero real {}, tipo {}", TokenMap::isRealNumber(TokenMap::getTokenType(argType)), TokenMap::getTokenText(dataFormatType));
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
                //iron::printf("É numero real {}, tipo {}", TokenMap::isRealNumber(TokenMap::getTokenType(argType)), TokenMap::getTokenText(dataFormatType));
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

    scopeManager->currentScope()->addSymbol(varName, {TokenMap::VARIABLE, TokenMap::getTokenType(varType), nullptr});

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

    //iron::printf("Function: {} VarName: {} VarType: {} Scope: {}", scope, varName, varType);

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

    iron::printf("Chegou {}, Atual {}", actualFunctionName, ctx->functionName->getText());
    iron::printf("O que foi encontrado: {}", ctx->functionName->getText());

    auto line = ctx->getStart()->getLine();
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));
    auto globalFunctionSymbalInfo = globalScope->lookup(ctx->functionName->getText());
    //auto globalArgsSize = globalFunctionSymbalInfo->args.size();

    //iron::printf("actualFunctionName {}, functionName: {}", actualFunctionName, ctx->functionName->getText());

    //primeiro vamos verificar se a função existe no escopo local
    SymbolInfo functionSymbolInfo;
    std::string localFunction = iron::format("{}_{}", parentScope->getName(), actualFunctionName);
    std::string realFunctionName;
    if (globalScope->lookup(localFunction).has_value()) {
        functionSymbolInfo = globalScope->lookup(localFunction).value();
        realFunctionName = localFunction;
    } else 
    //procura no escopo global
    if (globalScope->lookup(actualFunctionName).has_value()) {
        functionSymbolInfo = globalScope->lookup(actualFunctionName).value();
        realFunctionName = actualFunctionName;
    } else {
        throw FunctionNotFoundException(iron::format("Function {} not found",actualFunctionName));
    }
    auto globalArgsSize = functionSymbolInfo.args.size();
    // Se a call tem argumentos
    if (ctx->functionCallArgs()) {
        
        int callArgsSize = 0;
        for (auto child : ctx->functionCallArgs()->children) {
            if (auto functionCallArg = dynamic_cast<IronParser::FunctionCallArgContext*>(child)) {
                callArgsSize+=1;
            }
        }

        iron::printf("size {}, Size global: {}", std::to_string(callArgsSize), globalArgsSize);

        if (globalArgsSize != callArgsSize) {
            throw ArgumentCountMismatchException(iron::format(
                "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                color::colorText(
                    iron::format("fn {}", iron::getTextAfterUnderscore(actualFunctionName)), color::BOLD_GREEN),
                color::colorText(std::to_string(globalArgsSize), color::BOLD_GREEN),
                color::colorText(std::to_string(callArgsSize), color::BOLD_GREEN),
                color::colorText(std::to_string(line), color::YELLOW)
            ));
        }
    
        visitFunctionCallArgs(ctx->functionCallArgs(), realFunctionName, parentScope);
    } else {
        if (globalArgsSize > 0) {
            throw ArgumentCountMismatchException(iron::format(
                "Function '{}' expects {} arguments, but {} were provided. Line: {}",
                color::colorText(
                    iron::format("fn {}", iron::getTextAfterUnderscore(actualFunctionName)), color::BOLD_GREEN),
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
}

// Visita um único argumento "argName" de "actualFunctionName"
void SemanticalAnalysis::visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                                              const std::string& actualFunctionName,
                                              std::shared_ptr<SymbolTable> parentScope)
{
    // Exemplo de debug
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
    if (auto argOpt = iron::getArgumentByName(globalFunctionOpt.value(), argName)) {
        auto [foundArgName, foundArgType] = *argOpt;

        // Se o parser identificou algo como 'dataFormat', checa se é int, float, etc.
        if (ctx->dataFormat()) {
            bool isIntLiteral  = ctx->dataFormat()->INT_NUMBER();
            bool isRealLiteral = ctx->dataFormat()->REAL_NUMBER();

            if (foundArgType == TokenMap::TYPE_INT) {
                if (!isIntLiteral) {
                    throw TypeMismatchException(iron::format(
                        "Argument {} is incompatible with type int. Line: {}",
                        color::colorText(foundArgName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }
            }
            else if (foundArgType == TokenMap::TYPE_FLOAT
                  || foundArgType == TokenMap::TYPE_DOUBLE)
            {
                if (!isRealLiteral) {
                    throw TypeMismatchException(iron::format(
                        "Argument {} is incompatible with type {}. Line: {}",
                        color::colorText(foundArgName, color::BOLD_GREEN),
                        color::colorText(
                            foundArgType == TokenMap::TYPE_FLOAT ? "float" : "double",
                            color::BOLD_GREEN
                        ),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                } else {
                    auto literalType = iron::typeOfRealNumber(
                        ctx->dataFormat()->REAL_NUMBER()->getText()
                    );

                    if (literalType == TokenMap::NO_REAL_NUMBER) {
                        auto dataType = ctx->dataFormat()->getText();
                        throw TypeMismatchException(iron::format(
                            "Invalid real number type for argument {}. Expected {} or {}. Line: {}",
                            color::colorText(foundArgName, color::BOLD_GREEN),
                            color::colorText(iron::format("{}{}", dataType, "D"), color::BOLD_GREEN),
                            color::colorText(iron::format("{}{}", dataType, "F"), color::BOLD_GREEN),
                            color::colorText(std::to_string(line), color::YELLOW)
                        ));
                    }

                    if (foundArgType == TokenMap::TYPE_FLOAT  && literalType == TokenMap::TYPE_FLOAT) {
                        // OK
                    }
                    else if (foundArgType == TokenMap::TYPE_DOUBLE && literalType == TokenMap::TYPE_DOUBLE) {
                        // OK
                    }
                    else {
                        throw TypeMismatchException(iron::format(
                            "Invalid real number type for argument {}. Expected {}, found {}. Line: {}",
                            color::colorText(foundArgName, color::BOLD_GREEN),
                            color::colorText(
                                foundArgType == TokenMap::TYPE_FLOAT ? "float" : "double",
                                color::BOLD_GREEN
                            ),
                            color::colorText(
                                literalType == TokenMap::TYPE_DOUBLE ? "double" : "float",
                                color::BOLD_GREEN
                            ),
                            color::colorText(std::to_string(line), color::YELLOW)
                        ));
                    }
                }
            }
        }

        // Se for algo como "varName: anotherVarName"
        if (ctx->anotherVarName) {
            auto anotherVarName = ctx->anotherVarName->getText();
            auto anotherVarLookup = parentScope->lookup(anotherVarName);

            if (anotherVarLookup.has_value()) {
                auto symbolInfo = anotherVarLookup.value();

                if (symbolInfo.type != TokenMap::VARIABLE) {
                    throw VariableNotFoundException(iron::format(
                        "{} is not a variable in that scope (fn {}). Line: {}",
                        color::colorText(anotherVarName, color::BOLD_GREEN),
                        color::colorText(parentScope ? parentScope->getName() : "Global", color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }

                if (foundArgType != symbolInfo.dataType) {
                    throw TypeMismatchException(iron::format(
                        "Argument {} is incompatible with Variable {}. Line: {}",
                        color::colorText(foundArgName, color::BOLD_GREEN),
                        color::colorText(anotherVarName, color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }
            } else {
                throw VariableNotFoundException(iron::format(
                    "Variable {} not found in that scope (fn {}). Line: {}",
                    color::colorText(anotherVarName, color::BOLD_GREEN),
                    color::colorText(parentScope ? parentScope->getName() : "Global", color::BOLD_GREEN),
                    color::colorText(std::to_string(line), color::YELLOW)
                ));
            }
        }

        // Se o valor do argumento for outra functionCall, 
        // precisamos descobrir o nome REAL dessa functionCall
        if (ctx->functionCall()) {
            
            auto innerFunctionName = ctx->functionCall()->functionName->getText();
            
            std::string functionNameCalled;
            //primeiro procura no escopo global para verificar se a função existe
            if (globalScope->lookup(innerFunctionName).has_value()) {
                functionNameCalled = innerFunctionName;
            } else {
                //verifica no escopo local se a função existe
                std::string localName = iron::format("{}_{}", parentScope->getName(), innerFunctionName);
                if (globalScope->lookup(localName).has_value()) {
                    functionNameCalled = localName;
                } else {
                    throw TypeMismatchException(iron::format(
                        "Function {} not found. Line: {}",
                        color::colorText(iron::format("fn {}", innerFunctionName), color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(foundArgType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }
            }

            auto globalFunctionOpt = globalScope->lookup(functionNameCalled).value();

            if (auto argOpt = iron::getArgumentByName(globalFunctionOpt, argName)) {
                auto innerFunction = scopeManager->currentScope()->lookup(innerFunctionName);
                auto [foundArgName, foundArgType] = *argOpt;
                if (foundArgType != innerFunction->dataType) {
                    throw TypeMismatchException(iron::format(
                        "The return of function {} must be {}. Line: {}",
                        color::colorText(iron::format("fn {}", innerFunctionName), color::BOLD_GREEN),
                        color::colorText(TokenMap::getTokenText(foundArgType), color::BOLD_GREEN),
                        color::colorText(std::to_string(line), color::YELLOW)
                    ));
                }
            }

            // Agora chamamos recursivamente o visitFunctionCall, 
            // passamos "innerFunctionName" e o MESMO parentScope:
            visitFunctionCall(ctx->functionCall(), innerFunctionName, parentScope);
        }
    }
    else {
        // Se não encontrou esse argName na função actualFunctionName
        throw FunctionArgNotFoundException(iron::format(
            "Argument {} not found in function fn {}. Line: {}",
            color::colorText(argName, color::BOLD_GREEN),
            color::colorText(actualFunctionName, color::BOLD_GREEN),
            color::colorText(std::to_string(line), color::YELLOW)
        ));
    }
}

void SemanticalAnalysis::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext* ctx) {
    auto globalScope = scopeManager->getScopeByName(TokenMap::getTokenText(TokenMap::GLOBAL));

    auto currentScopeName = scopeManager->currentScopeName();

    if (auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext*>(ctx->parent->parent)) {
        std::string globalFunctionName = iron::format("{}_{}",currentScopeName, varDeclaration->varName->getText());

        if (ctx->functionSignature()->functionReturnType()) {
            std::string type = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            globalScope->addSymbol(globalFunctionName, {TokenMap::FUNCTION, TokenMap::getTokenType(type), nullptr});
        } else {
            globalScope->addSymbol(globalFunctionName, {TokenMap::FUNCTION, TokenMap::VOID, nullptr});
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
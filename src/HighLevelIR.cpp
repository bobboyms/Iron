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
    }

    void HighLevelIR::visitExpr(IronParser::ExprContext* ctx) 
    {
    }

    void HighLevelIR::visitVarAssignment(IronParser::VarAssignmentContext* ctx) 
    {
    }

    void HighLevelIR::visitAssignment(IronParser::AssignmentContext* ctx) 
    {
    }

    void HighLevelIR::visitVarDeclaration(IronParser::VarDeclarationContext* ctx) 
    {
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
        
        std::string returnType;
        if (ctx->functionSignature()->functionReturnType()) {
            returnType = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
        } else {
            returnType = TokenMap::getTokenText(TokenMap::VOID);
        }


        sb << iron::format("{} {} {} (",visibility, fn, functionName);
        scopeManager->enterScope(functionName);

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature());
        }
        scopeManager->exitScope(functionName);
        sb << iron::format("): {} { \n", returnType); //"" << returnType << "{"
        
        for (auto child : ctx->children) {
            if (auto statementList = dynamic_cast<IronParser::StatementListContext*>(child)) {
                visitStatementList(statementList);
            }
        }

        sb << iron::format("} \n", returnType); 

    
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

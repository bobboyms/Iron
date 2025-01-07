#include "headers/LLVMIR.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"

namespace iron {

    LLVMIR::LLVMIR(std::string code, std::unique_ptr<ScopeManager> scopeManager)
        : hlirCode(code), scopeManager(std::move(scopeManager)), builder(context) {
            module = std::make_unique<llvm::Module>("file_1", context);
        }

    LLVMIR::~LLVMIR() {}

    std::string LLVMIR::generateCode() 
    {
        if (hlirCode.empty()) {
            throw std::runtime_error("Code is not properly initialized.");
        }

        std::cout << hlirCode << std::endl;

        antlr4::ANTLRInputStream inputStream(hlirCode);
        HightLavelIRLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<HightLavelIRParser>(&tokens);
        scopeManager->enterScope(TokenMap::getTokenText(TokenMap::GLOBAL));

        HightLavelIRParser::ProgramContext* programContext = parser->program();
        
        for (auto child : programContext->children) {
            if (auto funcDecl = dynamic_cast<HightLavelIRParser::FunctionDeclarationContext*>(child)) {
                visitFunctionDeclaration(funcDecl);
            }
        }

        scopeManager->exitScope(TokenMap::getTokenText(TokenMap::GLOBAL));
        // Verifica a validade do módulo
        if (llvm::verifyModule(*module, &llvm::errs())) {
            throw std::runtime_error("Erro: Módulo LLVM inválido.");
        }

        // Captura o LLVM IR em uma string
        std::string irStr;
        llvm::raw_string_ostream irStream(irStr);
        module->print(irStream, nullptr);
        return irStr;
    }

    void LLVMIR::visitStatementList(HightLavelIRParser::StatementListContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitExpr(HightLavelIRParser::ExprContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitCast(HightLavelIRParser::CastContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitOp(HightLavelIRParser::OpContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitMathOp(HightLavelIRParser::Math_opContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext* ctx) {
        iron::printf("olá","");
    }

    void LLVMIR::visitFunctionSignature(HightLavelIRParser::FunctionSignatureContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionArgs(HightLavelIRParser::FunctionArgsContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionArg(HightLavelIRParser::FunctionArgContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionCall(HightLavelIRParser::FunctionCallContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext* ctx) {
        // Implementação do método
    }
}

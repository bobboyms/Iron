#ifndef SEMANTICAL_ANALYSIS_H
#define SEMANTICAL_ANALYSIS_H

#include "../parsers/IronParser.h"
#include "ScopeManager.h" // Inclui a tabela de símbolos
#include <memory>
#include <stack>

class SemanticalAnalysis {
private:
    std::unique_ptr<IronParser> parser;
    std::unique_ptr<ScopeManager> scopeManager;

    

    void visitFunctionDeclaration(IronParser::FunctionDeclarationContext* ctx);
    void visitStatementList(IronParser::StatementListContext* ctx);
    void visitVarDeclaration(IronParser::VarDeclarationContext* ctx);
    void visitVarAssignment(IronParser::VarAssignmentContext* ctx);

    void visitExpr(IronParser::ExprContext* ctx);
    void visitAssignment(IronParser::AssignmentContext* ctx);

    void visitFunctionSignature(IronParser::FunctionSignatureContext* ctx);
    void visitFunctionArgs(IronParser::FunctionArgsContext* ctx);
    void visitFunctionArg(IronParser::FunctionArgContext* ctx);

    // Novos ou ajustados
    void visitFunctionCall(IronParser::FunctionCallContext* ctx,
                           const std::string& actualFunctionName,
                           std::shared_ptr<SymbolTable> parentScope);

    void visitFunctionCallArgs(IronParser::FunctionCallArgsContext* ctx,
                               const std::string& actualFunctionName,
                               std::shared_ptr<SymbolTable> parentScope);

    void visitFunctionCallArg(IronParser::FunctionCallArgContext* ctx,
                              const std::string& actualFunctionName,
                              std::shared_ptr<SymbolTable> parentScope);


public:
    SemanticalAnalysis(std::unique_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager);
    ~SemanticalAnalysis();
    void analyze();
};

#endif // SEMANTICAL_ANALYSIS_H

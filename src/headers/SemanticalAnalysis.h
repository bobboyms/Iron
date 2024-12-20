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

    //std::unordered_map<antlr4::ParserRuleContext*, std::string> typeMap;
    std::string left;
    std::string op;
    std::string right;


public:
    SemanticalAnalysis(std::unique_ptr<IronParser> parser, std::unique_ptr<ScopeManager> scopeManager);
    ~SemanticalAnalysis();
    void analyze();
};

#endif // SEMANTICAL_ANALYSIS_H

#ifndef SEMANTICAL_ANALYSIS_H
#define SEMANTICAL_ANALYSIS_H

#include "../parsers/IronParser.h"
#include "../scope/ScopeManager.h"
#include "Configuration.h"
#include "Hlir.h"
#include "TokenMap.h"
#include "Utils.h"

namespace iron
{
    struct ErrorContext
    {
        uint line;
        uint col;
        std::string codeLine;
        std::string caretLine;
        std::string scopeName;
    };

    class SemanticAnalysis
    {
    private:
        std::shared_ptr<IronParser> parser;
        std::unique_ptr<scope::ScopeManager> scopeManager;
        std::vector<std::string> sourceLines;
        std::shared_ptr<config::Configuration> config;

        // Métodos de análise por fases
        void analyzeDeclarations();
        void analyzeDefinitions();

        // Visitantes para declarações de loop
        void visitWhileStatement(IronParser::WhileStatementContext *ctx);
        void visitRepeatStatement(IronParser::RepeatStatementContext *ctx);
        void visitForStatement(IronParser::ForStatementContext *ctx);
        // void visitLoopStatementList(IronParser::LoopStatementListContext *ctx);
        // void visitBreakStatement(IronParser::BreakStatementContext *ctx);
        // void visitContinueStatement(IronParser::ContinueStatementContext *ctx);
        // void visitVoidReturnStatement(IronParser::VoidReturnStatementContext *ctx);

        // Funções auxiliares para erro e contexto
        std::pair<std::string, std::string> getCodeLineAndCaretLine(uint line, uint col, int steps) const;
        ErrorContext getErrorContext(uint line, uint col, int caretOffset = 0) const;
        
        // Funções auxiliares para validação
        std::shared_ptr<scope::Variable> verifyVariableExists(const std::string &varName, uint line, uint col,
                                                              const std::string &contextInfo = "");
        std::shared_ptr<scope::Function> verifyFunctionExists(const std::string &functionName, uint line, uint col) const;
        void verifyTypesMatch(int typeA, int typeB, const std::string &nameA, const std::string &nameB, uint line,
                              uint col, const std::string &errorContextMsg = "Type mismatch error") const;
        static int determineValueType(const std::string &value);

        void visitStructDeclaration(IronParser::StructStatementContext *ctx) const;
        void visitStructStatement(IronParser::StructStatementContext *ctx) const;
        void visitStructInit(IronParser::StructInitContext *ctx,
                             const std::shared_ptr<scope::StructStemt> &parentStructDef = nullptr);
        void visitStructInitBody(IronParser::StructInitBodyContext *ctx, std::shared_ptr<scope::StructStemt> parentStructDef = nullptr);
        
        // Métodos auxiliares para validação de struct removidos (já redefinidos abaixo)

        void visitExternBlock(IronParser::ExternBlockContext *ctx);

        void visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx);

        void visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                     std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList);

        void visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                    std::shared_ptr<std::vector<std::shared_ptr<scope::FunctionArg>>> argsList);

        std::pair<std::string, int> visitBoolExpr(IronParser::BoolExprContext *ctx);

        void visitIfBlock(IronParser::IfBlockContext *ctx);
        void visitIfStatement(IronParser::IfStatementContext *ctx);
        void visitElseStatement(IronParser::ElseStatementContext *ctx);

        // void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);
        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) const;
        static void validateFunctionReturn(const std::string &codeLine, int line,
                                           const std::shared_ptr<scope::Function> &function);

        void visitFunctionBody(IronParser::FunctionDeclarationContext *ctx);
        std::shared_ptr<scope::Signature> getSignature(IronParser::FunctionSignatureContext *ctx) const;

        void visitStatementList(const IronParser::StatementListContext *ctx);
        std::shared_ptr<scope::Variable> checkAnotherTypes(const std::string &varName,
                                                           const std::string &anotherTypeName, bool mut, int line,
                                                           const std::string &codeLine,
                                                           const std::string &caretLine) const;

        std::pair<std::shared_ptr<scope::StructStemt>, std::shared_ptr<scope::Variable>>
        getStructAndField(IronParser::VariableQualifiedNameContext *identifiers);

        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx);

        void visitVarAssignment(IronParser::VarAssignmentContext *ctx);

        void visitImportStatement(IronParser::ImportStatementContext *ctx) const;

        std::pair<std::string, int> visitExpr(IronParser::ExprContext *ctx);

        void visitAssignment(IronParser::AssignmentContext *ctx);
        void handleDataFormatAssignment(IronParser::AssignmentContext *ctx, uint line, const std::string &codeLine,
                                        const std::string &caretLine) const;
        void handleFunctionCallAssignment(IronParser::AssignmentContext *ctx, uint line, const std::string &codeLine,
                                          const std::string &caretLine,
                                          const std::shared_ptr<scope::Function> &currentFunction);
        void handleAnotherVarNameAssignment(IronParser::AssignmentContext *ctx, uint line, const std::string &codeLine,
                                            const std::string &caretLine,
                                            const std::shared_ptr<scope::Function> &currentFunction);
        void handleQualifiedNameAssignment(IronParser::AssignmentContext *ctx, uint line, const std::string &codeLine,
                                           const std::string &caretLine, const std::string &varName,
                                           const std::string &anotherVarName,
                                           const std::shared_ptr<scope::Variable> &variable,
                                           const std::shared_ptr<scope::Variable> &anotherVariable);
        void handleFunctionAssignment(uint line, const std::string &codeLine, const std::string &caretLine,
                                      const std::string &varName, const std::string &anotherVarName,
                                      const std::shared_ptr<scope::Variable> &anotherVariable,
                                      const std::shared_ptr<scope::Function> &currentFunction,
                                      const std::shared_ptr<scope::Variable> &variable) const;
        void handleVariableAssignment(uint line, const std::string &codeLine, const std::string &caretLine,
                                      const std::string &varName, const std::string &varType,
                                      const std::shared_ptr<scope::Variable> &variable,
                                      const std::shared_ptr<scope::Variable> &anotherVariable) const;
        void handleExprAssignment(IronParser::AssignmentContext *ctx, uint line, const std::string &codeLine,
                                  const std::string &caretLine);
        void handleBoolExprAssignment(IronParser::AssignmentContext *ctx, uint line, const std::string &codeLine,
                                      const std::string &caretLine);

        void visitFunctionSignature(const IronParser::FunctionSignatureContext *ctx) const;

        void visitFunctionArgs(const IronParser::FunctionArgsContext *ctx) const;

        void visitFunctionArg(IronParser::FunctionArgContext *ctx) const;

        void visitFunctionCall(IronParser::FunctionCallContext *ctx);
        void validateFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                     const std::shared_ptr<scope::FunctionArg> &arg);

        void visitFunctionCallArgs(const IronParser::FunctionCallArgsContext *ctx);

        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx);

        static bool validateSignature(const std::shared_ptr<scope::Signature> &signature,
                                      const std::shared_ptr<scope::Function> &function);

        std::shared_ptr<scope::Function> getCurrentFunction();

        std::shared_ptr<scope::Function> visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx);

        // std::shared_ptr<scope::Function> visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx);

        // Métodos para validação de retorno
        void visitReturn(IronParser::ReturnStatementContext *ctx);
        void validateReturnLiteral(IronParser::ReturnStatementContext *ctx, 
                                 const std::shared_ptr<scope::Function> &currentFunction,
                                 uint line, uint col);
        void validateReturnVariable(IronParser::ReturnStatementContext *ctx, 
                                  const std::shared_ptr<scope::Function> &currentFunction,
                                  uint line, uint col);
        void validateReturnExpression(IronParser::ReturnStatementContext *ctx, 
                                    const std::shared_ptr<scope::Function> &currentFunction,
                                    uint line, uint col);
        void validateReturnFunctionCall(IronParser::ReturnStatementContext *ctx, 
                                      const std::shared_ptr<scope::Function> &currentFunction,
                                      uint line, uint col);

        // Métodos auxiliares para validação de campos de struct
        void validateStructField(const std::string &fieldName,
                              const std::shared_ptr<scope::StructStemt> &parentStructDef, uint lineNumber,
                              uint columnPosition) const;
        void validateStructFieldValue(IronParser::StructInitBodyContext *ctx,
                                   const std::shared_ptr<scope::Variable> &field);
        void validateStructFieldAssignment(const std::string &fieldName, const std::shared_ptr<scope::Variable> &field,
                                        int valueType, const std::string &valueDesc, const std::string &valueTypeDesc,
                                        uint lineNumber, uint columnPosition);

        // Métodos para validação de struct
        void validateNestedStructValues(IronParser::StructInitContext *ctx,
                                      const std::shared_ptr<scope::Variable> &field);
        std::shared_ptr<scope::StructStemt> findParentStructDefForNestedInit(IronParser::StructInitBodyContext *ctx);
        void processDirectStructInitialization(IronParser::StructInitBodyContext *ctx, const std::string &variableName,
                                             const std::shared_ptr<scope::Variable> &structVariable);
        void processNestedStructFieldInit(IronParser::StructInitBodyContext *ctx);
                                      
        std::vector<std::pair<std::string, int>>
        parseFormatSpecifiers(const std::string &format, uint line, const std::string &caretLine,
                              const std::string &codeLine) const;


    public:
        explicit SemanticAnalysis(std::shared_ptr<IronParser> parser, std::unique_ptr<scope::ScopeManager> scopeManager,
                                  const std::vector<std::string> &sourceLines,
                                  const std::shared_ptr<config::Configuration> &config);

        ~SemanticAnalysis();

        std::vector<std::shared_ptr<scope::Function>> analyze();
    };
} // namespace iron

#endif // SEMANTICAL_ANALYSIS_H

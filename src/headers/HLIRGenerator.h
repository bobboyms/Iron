#include "../parsers/HighLevelIRLexer.h"
#include "../parsers/HighLevelIRParser.h"
#include "../parsers/IronParser.h"
#include "Configuration.h"
#include "Files.h"
#include "Hlir.h"

#include <tuple>

namespace hlir
{
    class HLIRGenerator
    {
    private:
        std::shared_ptr<IronParser> parser;
        std::shared_ptr<Context> context;
        std::shared_ptr<config::Configuration> config;
        std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> exportContexts;

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);
        void visitStatementList(const IronParser::StatementListContext *ctx,
                                const std::shared_ptr<Function> &currentFunction);
        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                 const std::shared_ptr<Function> &currentFunction);
        // static void visitVarAssignment(IronParser::VarAssignmentContext *ctx, std::shared_ptr<Statement> statement);

        std::string visitExpr(IronParser::ExprContext *ctx, const std::shared_ptr<Function> &currentFunction);
        std::string visitBoolExpr(IronParser::BoolExprContext *ctx, const std::shared_ptr<Function> &currentFunction);
        void visitIfBlock(IronParser::IfBlockContext *ctx, const std::shared_ptr<Function> &currentFunction);
        void visitIfStatement(IronParser::IfStatementContext *ctx, const std::shared_ptr<Function> &currentFunction);
        void visitElseStatement(IronParser::ElseStatementContext *ctx, const std::shared_ptr<Function> &currentFunction,
                                const std::string &label);

        std::tuple<int, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
        initializerExprVariables(const std::string &strLeftVar, const std::string &strRightVar,
                                 const std::shared_ptr<Function> &currentFunction);

        static std::shared_ptr<Expr> castVariable(int higherType, const std::string &varName,
                                                  const std::shared_ptr<Variable> &variable);

        void visitAssignment(IronParser::AssignmentContext *ctx, const std::shared_ptr<Function> &currentFunction);

        static void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx,
                                           const std::shared_ptr<FunctionArgs> &functionArgs,
                                           const std::shared_ptr<Type> &functionReturnType);
        static void visitFunctionArgs(const IronParser::FunctionArgsContext *ctx,
                                      const std::shared_ptr<FunctionArgs> &functionArgs);
        static void visitFunctionArg(IronParser::FunctionArgContext *ctx,
                                     const std::shared_ptr<FunctionArgs> &functionArgs);

        std::shared_ptr<FunctionCall> visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                                        const std::shared_ptr<Function> &currentFunction);

        void visitFunctionCallArgs(const IronParser::FunctionCallArgsContext *ctx,
                                   const std::shared_ptr<FunctionCallArgs> &callArgs,
                                   const std::shared_ptr<Function> &currentFunction);

        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                  const std::shared_ptr<FunctionCallArgs> &callArgs,
                                  const std::shared_ptr<Function> &currentFunction);

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx,
                                      const std::shared_ptr<Function> &currentFunction);

        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx,
                                     const std::shared_ptr<Function> &currentFunction);
        void visitReturn(IronParser::ReturnStatementContext *ctx, const std::shared_ptr<Function> &currentFunction);


        static std::pair<int, std::shared_ptr<Variable>> findVarByScope(const std::shared_ptr<Function> &currentFunction,
                                                                        const std::string &varName);

        std::shared_ptr<Function> getFunctionValue(const std::shared_ptr<Function> &currentFunction,
                                                   const std::string &varName);

        static void ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var);
        static bool hasVariableOrArg(const std::shared_ptr<Function> &F, const std::string &varName);

        void visitImportStatement(IronParser::ImportStatementContext *ctx) const;
        void registerExternalFunction(const std::shared_ptr<Function> &function) const;
        void visitExternBlock(const IronParser::ExternBlockContext *ctx) const;
        void visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx) const;
        static void visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                            const std::shared_ptr<FunctionArgs> &argsList);
        static void visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                           const std::shared_ptr<FunctionArgs> &argsList);

        std::shared_ptr<Function> gatArrowFunction(const std::shared_ptr<Statement> &statement,
                                                   const std::string &functionName);


    public:
        // std::string generateCode();
        std::shared_ptr<Context> getContext();

        // HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context);
        HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context,
                      const std::shared_ptr<config::Configuration> &config,
                      const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts);

        ~HLIRGenerator();
    };

} // namespace hlir

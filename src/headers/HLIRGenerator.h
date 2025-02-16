#include "../parsers/HighLevelIRLexer.h"
#include "../parsers/HighLevelIRParser.h"
#include "../parsers/IronParser.h"
#include "Configuration.h"
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
                                const std::shared_ptr<Statement> &statement);
        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx, const std::shared_ptr<Statement> &statement);
        void visitVarAssignment(IronParser::VarAssignmentContext *ctx, std::shared_ptr<Statement> statement);

        std::string visitExpr(IronParser::ExprContext *ctx, const std::shared_ptr<Statement> &statement);
        std::string visitBoolExpr(IronParser::BoolExprContext *ctx, const std::shared_ptr<Statement> &statement);
        std::tuple<int, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
        initializerExprVariables(const std::string &strLeftVar, const std::string &strRightVar,
                                 const std::shared_ptr<Statement> &statement);
        std::shared_ptr<Expr> castVariable(int higherType, const std::string &varName,
                                           const std::shared_ptr<Variable> &variable);

        void visitAssignment(IronParser::AssignmentContext *ctx, std::shared_ptr<Statement> statement);

        void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx,
                                    std::shared_ptr<FunctionArgs> functionArgs,
                                    std::shared_ptr<Type> functionReturnType);
        void visitFunctionArgs(IronParser::FunctionArgsContext *ctx, std::shared_ptr<FunctionArgs> functionArgs);
        void visitFunctionArg(IronParser::FunctionArgContext *ctx, std::shared_ptr<FunctionArgs> functionArgs);

        std::shared_ptr<FunctionCall> visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                                        const std::shared_ptr<Statement>& statement);
        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx,
                                   const std::shared_ptr<FunctionCallArgs> &callArgs,
                                   const std::shared_ptr<Statement> &statement);
        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                  const std::shared_ptr<FunctionCallArgs> &callArgs,
                                  const std::shared_ptr<Statement> &statement);

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx,
                                      const std::shared_ptr<Statement> &statement);
        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx,
                                     const std::shared_ptr<Statement> &statement);
        void visitReturn(IronParser::ReturnStatementContext *ctx, const std::shared_ptr<Statement> &statement);


        std::pair<int, std::shared_ptr<Variable>> findVarByScope(const std::shared_ptr<Statement> &Statement,
                                                                 const std::string &varName);

        static void ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var);
        static bool hasVariableOrArg(const std::shared_ptr<Function> &F, const std::string &varName);


    public:
        // std::string generateCode();
        std::shared_ptr<Context> getContext();
        void visitImportStatement(IronParser::ImportStatementContext *ctx);
        void registerExternalFunction(const std::shared_ptr<Function> &function) const;
        void visitExternBlock(IronParser::ExternBlockContext *ctx);
        void visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx);
        void visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                     const std::shared_ptr<FunctionArgs> &argsList);
        void visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                    const std::shared_ptr<FunctionArgs> &argsList);
        // HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context);
        HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::__1::shared_ptr<Context> &context,
                      const std::shared_ptr<config::Configuration> &config,
                      const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts);
        // HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context);
        ~HLIRGenerator();
    };

} // namespace hlir

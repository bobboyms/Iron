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

        // structs
        // void visitStructDeclaration(IronParser::StructStatementContext *ctx, const std::shared_ptr<Function> &currentFunction);
        void visitStructStatement(IronParser::StructStatementContext *ctx) const;
        void visitStructInit(IronParser::StructInitContext *ctx, const std::shared_ptr<Function> &currentFunction);
        // void visitStructInitBody(IronParser::StructInitBodyContext *ctx, const std::shared_ptr<Function> &currentFunction);

        // loops
        void visitWhileStatement(IronParser::WhileStatementContext *ctx,
                                 const std::shared_ptr<Function> &currentFunction);
        void visitRepeatStatement(IronParser::RepeatStatementContext *ctx,
                                  const std::shared_ptr<Function> &currentFunction);
        void visitForStatement(IronParser::ForStatementContext *ctx, const std::shared_ptr<Function> &currentFunction);


        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);

        std::pair<bool, bool> visitStatementList(const IronParser::StatementListContext *ctx,
                                                 const std::shared_ptr<Function> &currentFunction,
                                                 const std::shared_ptr<Jump> &endJump = nullptr);

        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                 const std::shared_ptr<Function> &currentFunction);

        std::string visitExpr(IronParser::ExprContext *ctx, const std::shared_ptr<Function> &currentFunction);
        static int defineRealType(const std::string &strValue);
        static std::shared_ptr<Assign> generateAssignFromDataFormat(const std::shared_ptr<Variable> &variable,
                                                             const std::string &literalValue);
        static std::tuple<std::shared_ptr<Variable>, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
        getVariableOrCreate(const std::shared_ptr<Function> &currentFunction, const std::string &strLeftVar,
                            const std::string &strRightVar, const std::string &tempVarStr, uint higherType,
                            bool createTempVar = false);

        std::string visitBoolExpr(IronParser::BoolExprContext *ctx, const std::shared_ptr<Function> &currentFunction);
        std::pair<bool, bool> visitBlockAndCheckReturn(IronParser::IfBlockContext *blockCtx,
                                                       const std::shared_ptr<Function> &currentFunction,
                                                       const std::shared_ptr<Jump> &endJump);

        static void handleEndBlock(const std::shared_ptr<Function> &currentFunction,
                                   const std::shared_ptr<Statement> &statement, const std::string &endLabel,
                                   bool haveReturn);

        std::pair<bool, bool> visitIfBlock(IronParser::IfBlockContext *ctx,
                                           const std::shared_ptr<Function> &currentFunction,
                                           const std::shared_ptr<Jump> &endJump);

        std::pair<bool, bool> visitIfStatement(IronParser::IfStatementContext *ctx,
                                               const std::shared_ptr<Function> &currentFunction,
                                               const std::string &endLabel, const std::shared_ptr<Jump> &endJump);

        std::pair<bool, bool> visitElseStatement(IronParser::ElseStatementContext *ctx,
                                                 const std::shared_ptr<Function> &currentFunction,
                                                 const std::string &label, const std::string &endLabel,
                                                 const std::shared_ptr<Jump> &endJump);

        std::tuple<int, std::shared_ptr<Variable>, std::shared_ptr<Variable>>
        initializerExprVariables(const std::string &strLeftVar, const std::string &strRightVar,
                                 const std::shared_ptr<Function> &currentFunction);

        static std::shared_ptr<Expr> castVariable(int higherType, const std::string &varName,
                                                  const std::shared_ptr<Variable> &variable,
                                                  const std::shared_ptr<Function> &currentFunction);


        static std::shared_ptr<Signature> getSignature(IronParser::FunctionSignatureContext *ctx);

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
        std::shared_ptr<Signature> createSignatureFromFunction(const std::shared_ptr<Function> &function);

        // void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx,
        //                              const std::shared_ptr<Function> &currentFunction);
        void visitReturn(IronParser::ReturnStatementContext *ctx, const std::shared_ptr<Function> &currentFunction);


        static std::shared_ptr<Function> getFunctionValue(const std::shared_ptr<Function> &currentFunction,
                                                          const std::string &varName);
        std::shared_ptr<Struct> getStruct(const std::shared_ptr<Function> &currentFunction, const std::string &varName);

        static void ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var);

        void visitImportStatement(IronParser::ImportStatementContext *ctx) const;
        void registerExternalFunction(const std::shared_ptr<Function> &function) const;
        void visitExternBlock(const IronParser::ExternBlockContext *ctx) const;
        void visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx) const;
        static void visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                            const std::shared_ptr<FunctionArgs> &argsList);
        static void visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                           const std::shared_ptr<FunctionArgs> &argsList);

        static std::shared_ptr<Function> gatArrowFunction(const std::shared_ptr<Function> &currentFunction,
                                                   const std::string &functionName);

        void visitVarAssignment(IronParser::VarAssignmentContext *ctx,
                                const std::shared_ptr<Function> &currentFunction);


    public:
        std::shared_ptr<Context> getContext();

        // HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context);
        HLIRGenerator(const std::shared_ptr<IronParser> &parser, const std::shared_ptr<Context> &context,
                      const std::shared_ptr<config::Configuration> &config,
                      const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts);

        ~HLIRGenerator();
    };

} // namespace hlir

#include "../parsers/IronParser.h"
#include "../parsers/HightLavelIRParser.h"
#include "../parsers/HightLavelIRLexer.h"
#include "Hlir.h"

namespace hlir
{
    class HLIRGenerator
    {
    private:
        std::shared_ptr<IronParser> parser;
        std::shared_ptr<Context> context;

        void visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx);
        void visitStatementList(IronParser::StatementListContext *ctx, std::shared_ptr<Statement> statement);
        void visitVarDeclaration(IronParser::VarDeclarationContext *ctx, std::shared_ptr<Statement> statement);
        void visitVarAssignment(IronParser::VarAssignmentContext *ctx, std::shared_ptr<Statement> statement);

        std::string visitExpr(IronParser::ExprContext *ctx, std::shared_ptr<Statement> statement);
        void visitAssignment(IronParser::AssignmentContext *ctx, std::shared_ptr<Statement> statement);

        void visitFunctionSignature(IronParser::FunctionSignatureContext *ctx, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType);
        void visitFunctionArgs(IronParser::FunctionArgsContext *ctx, std::shared_ptr<FunctionArgs> functionArgs);
        void visitFunctionArg(IronParser::FunctionArgContext *ctx, std::shared_ptr<FunctionArgs> functionArgs);

        std::shared_ptr<FunctionCall> visitFunctionCall(IronParser::FunctionCallContext *ctx, std::shared_ptr<Statement> statement);
        void visitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx, std::shared_ptr<FunctionCallArgs> callArgs, std::shared_ptr<Statement> statement);
        void visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx, std::shared_ptr<FunctionCallArgs> callArgs, std::shared_ptr<Statement> statement);

        void visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx, std::shared_ptr<Statement> statement);
        void visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx, std::shared_ptr<Statement> statement);
        void visitReturn(IronParser::ReturnStatementContext *ctx);

    public:
        std::string generateCode();
        HLIRGenerator(std::shared_ptr<IronParser> parser, std::shared_ptr<Context> context);
        ~HLIRGenerator();
    };

}
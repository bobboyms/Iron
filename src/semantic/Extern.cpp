#include "../headers/SemanticAnalysis.h"

namespace iron
{

    void SemanticAnalysis::visitExternBlock(IronParser::ExternBlockContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::ExternFunctionDeclarationContext *>(child))
            {
                visitExternFunctionDeclaration(funcDecl);
            }
        }
    }

    void SemanticAnalysis::visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto args = dynamic_cast<IronParser::ExternFunctionArgsContext *>(ctx))
            {
                visitExternFunctionArgs(args);
            }
        }


    }

    void SemanticAnalysis::visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx)
    {
        for (const auto child: ctx->children)
        {
            if (const auto arg = dynamic_cast<IronParser::ExternFunctionArgContext *>(ctx))
            {
                visitExternFunctionArg(arg);
            }
        }
    }

    void SemanticAnalysis::visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx)
    {
    }

} // namespace iron

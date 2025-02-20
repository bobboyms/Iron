#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"

namespace hlir
{
    void HLIRGenerator::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        const auto functionName = ctx->functionName->getText();

        const auto functionArgs = std::make_shared<FunctionArgs>();
        const auto functionReturnType = std::make_shared<Type>();

        const auto function = std::make_shared<Function>()->set(functionName, functionArgs, functionReturnType);
        context->addFunction(function);

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
        }

        function->enterLocalScope(std::make_shared<Statement>());
        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList(), function);
        }
        function->exitLocalScope();
    }



    void HLIRGenerator::visitFunctionSignature(IronParser::FunctionSignatureContext *ctx,
                                               const std::shared_ptr<FunctionArgs> &functionArgs,
                                               const std::shared_ptr<Type> &functionReturnType)
    {
        if (ctx->functionArgs())
        {
            visitFunctionArgs(ctx->functionArgs(), functionArgs);
        }

        if (ctx->functionReturnType())
        {
            // ctx->functionReturnType()->varTypes()->getText();
            functionReturnType->set(tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText()));
        }
        else
        {
            functionReturnType->set(tokenMap::VOID);
        }
    }

    void HLIRGenerator::visitFunctionArgs(const IronParser::FunctionArgsContext *ctx,
                                          const std::shared_ptr<FunctionArgs> &functionArgs)
    {
        for (const auto child: ctx->children)
        {
            if (const auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
            {
                visitFunctionArg(functionArg, functionArgs);
            }
        }
    }

    void HLIRGenerator::visitFunctionArg(IronParser::FunctionArgContext *ctx,
                                         const std::shared_ptr<FunctionArgs> &functionArgs)
    {
        const auto argName = ctx->varName->getText();
        const auto type = std::make_shared<Type>();
        type->set(tokenMap::getTokenType(ctx->varTypes()->getText()));
        functionArgs->addArg(std::make_shared<Arg>()->set(argName, type));
    }
    void HLIRGenerator::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx,
                                                 const std::shared_ptr<Function> &currentFunction)
    {
    }

    std::shared_ptr<FunctionCall> HLIRGenerator::visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                                                   const std::shared_ptr<Function> &currentFunction)
    {
        // Implementação removida
        return nullptr;
    }

    void HLIRGenerator::visitFunctionCallArgs(const IronParser::FunctionCallArgsContext *ctx,
                                              const std::shared_ptr<FunctionCallArgs> &callArgs,
                                              const std::shared_ptr<Function> &currentFunction)
    {
        // Implementação removida
    }

    void HLIRGenerator::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                             const std::shared_ptr<FunctionCallArgs> &callArgs,
                                             const std::shared_ptr<Function> &currentFunction)
    {
        // Implementação removida
    }



    void HLIRGenerator::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx,
                                                const std::shared_ptr<Function> &currentFunction)
    {
        // Implementação removida
    }

    void HLIRGenerator::visitReturn(IronParser::ReturnStatementContext *ctx,
                                    const std::shared_ptr<Function> &currentFunction)
    {
        // Implementação removida
    }
    std::pair<int, std::shared_ptr<Variable>>
    HLIRGenerator::findVarByScope(const std::shared_ptr<Function> &currentFunction, const std::string &varName)
    {
    }
    std::shared_ptr<Function> HLIRGenerator::getFunctionValue(const std::shared_ptr<Function> &currentFunction,
                                                              const std::string &varName)
    {
    }
    std::shared_ptr<Function> HLIRGenerator::gatArrowFunction(const std::shared_ptr<Statement> &statement,
                                                              const std::string &functionName)
    {
    }


    void HLIRGenerator::visitImportStatement(IronParser::ImportStatementContext *ctx) const
    {
        if (ctx->qualifiedName())
        {
            const std::string import = ctx->qualifiedName()->getText();
            const auto [path, element] = iron::convertImportPath(import);
            const std::string fullPath = util::format("{}{}", config->stdFolder(), path);

            if (const auto it = exportContexts->find(fullPath); it != exportContexts->end())
            {
                if (const auto foundContext = it->second)
                {
                    const auto externalFunction = foundContext->getFunctionByName(element);
                    registerExternalFunction(externalFunction);
                }
            }
            else
            {
                const iron::Analyser analyser(config);
                const auto parentContext = analyser.hlir(fullPath, exportContexts);
                exportContexts->emplace(fullPath, parentContext);

                const auto hlirPath = util::format("{}{}", config->outputHLIR(), path);
                // const auto pathAndFile = iron::saveToFile(parentContext->getText(), hlirPath, "hlir");

                // hilirFiles->push_back(pathAndFile);

                for (const auto &externalFunction: parentContext->getFunctions())
                {

                    if (externalFunction->getFunctionName() != element)
                    {
                        continue;
                    }
                    registerExternalFunction(externalFunction);
                }
            }
        }
    }
    void HLIRGenerator::registerExternalFunction(const std::shared_ptr<Function> &function) const
    {
    }
    void HLIRGenerator::visitExternBlock(const IronParser::ExternBlockContext *ctx) const
    {
        for (const auto child: ctx->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::ExternFunctionDeclarationContext *>(child))
            {
                visitExternFunctionDeclaration(funcDecl);
            }
        }
    }
    void HLIRGenerator::visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx) const
    {
    }
    void HLIRGenerator::visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                                const std::shared_ptr<FunctionArgs> &argsList)
    {
    }
    void HLIRGenerator::visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                               const std::shared_ptr<FunctionArgs> &argsList)
    {
    }
} // namespace hlir

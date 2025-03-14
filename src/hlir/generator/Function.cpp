/**
 * @file Function.cpp
 * @brief Implementation of function processing in the HLIR generator
 */
#include "../../headers/Analyser.h"
#include "../../headers/HLIRGenerator.h"
#include "../../headers/Hlir.h"
#include <string_view>

namespace hlir
{
    /**
     * @brief Processes a function declaration in the parser
     * 
     * This method converts a function declaration from the parse tree
     * into a Function object in the HLIR representation.
     * 
     * @param ctx Function declaration context from the parser
     * @throws HLIRException If required components are missing or invalid
     */
    void HLIRGenerator::visitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx)
    {
        if (!ctx) {
            throw HLIRException("visitFunctionDeclaration: Context is null");
        }
        
        if (!ctx->functionName) {
            throw HLIRException("Function name is missing");
        }
        
        // Create function components
        const auto functionName = ctx->functionName->getText();
        const auto functionArgs = std::make_shared<FunctionArgs>();
        const auto functionReturnType = std::make_shared<Type>();

        // Create the function and add it to the context
        const auto function = std::make_shared<Function>()->set(
            functionName, functionArgs, functionReturnType);
        context->addFunction(function);

        // Process function signature if present
        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
        }

        // Process function body if present
        const auto scopeStatement = std::make_shared<Statement>();
        ScopeGuard guard(function, scopeStatement);
        if (ctx->statementList()) {
            visitStatementList(ctx->statementList(), function);
        }
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

    std::shared_ptr<Signature> HLIRGenerator::getSignature(IronParser::FunctionSignatureContext *ctx)
    {
        int returnType = tokenMap::VOID;
        if (ctx->functionReturnType())
        {
            returnType = tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText());
        }

        const auto signature = std::make_shared<Signature>(std::make_shared<Type>(returnType));

        for (const auto child: ctx->children)
        {
            if (const auto functionArgs = dynamic_cast<IronParser::FunctionArgsContext *>(child))
            {
                for (const auto child: functionArgs->children)
                {
                    if (const auto functionArg = dynamic_cast<IronParser::FunctionArgContext *>(child))
                    {

                        const std::string argName = functionArg->varName->getText();
                        if (functionArg->fnsignature())
                        {
                            const auto anotherSignature = getSignature(functionArg->fnsignature()->functionSignature());
                            const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
                            const auto arg = std::make_shared<Arg>()->set(argName, type, anotherSignature);
                            signature->addArg(arg);
                        } else
                        {
                            const std::string argType = functionArg->varTypes()->getText();
                            const auto type = std::make_shared<Type>(tokenMap::getTokenType(argType));
                            const auto arg = std::make_shared<Arg>()->set(argName, type);
                            signature->addArg(arg);
                        }
                    }
                }
            }
        }

        return signature;
    }

    void HLIRGenerator::visitFunctionArg(IronParser::FunctionArgContext *ctx,
                                         const std::shared_ptr<FunctionArgs> &functionArgs)
    {
        const auto argName = ctx->varName->getText();
        const auto type = std::make_shared<Type>();

        if (ctx->fnsignature())
        {
            const auto signature = getSignature(ctx->fnsignature()->functionSignature());
            type->set(tokenMap::FUNCTION);
            functionArgs->addArg(std::make_shared<Arg>()->set(argName, type, signature));
        }
        else
        {
            type->set(tokenMap::getTokenType(ctx->varTypes()->getText()));
            functionArgs->addArg(std::make_shared<Arg>()->set(argName, type));
        }
    }

    std::shared_ptr<Function> createFunctionFromSignature(const std::shared_ptr<Variable> &variable)
    {
        const auto functionArgs = std::make_shared<FunctionArgs>();

        for (const auto arg: variable->getSignature()->getArgs())
        {
            functionArgs->addArg(arg);
        }

        return std::make_shared<Function>()->set(variable->getVarName(), functionArgs,
                                                 variable->getSignature()->getReturnType());
    }

    void createExternalCallArg(const std::shared_ptr<FunctionCallArgs> &callArgs,
                               const std::shared_ptr<Function> &calledFunction,
                               const std::shared_ptr<Function> &currentFunction)
    {
        const auto funcArgSize = calledFunction->getFunctionArgs()->getArgs().size();

        if (const auto callArgSize = callArgs->getCallArgs().size(); funcArgSize > callArgSize)
        {
            // auto diff = funcArgSize - callArgSize;
            for (size_t i = callArgSize; i < funcArgSize; i++)
            {
                const auto arg = calledFunction->getFunctionArgs()->getArgs()[i];
                auto variable = currentFunction->findVarAllScopesAndArg(arg->name);
                // auto variable = snd;

                if (!variable)
                {
                    throw HLIRException("HLIRGenerator::visitFunctionCall. Variable not found");
                }

                auto value = std::make_shared<Value>()->set(variable, variable->getVarType());
                auto callArg = std::make_shared<FunctionCallArg>(arg->name, variable->getVarType(), value);
                callArgs->addCallArg(callArg);
            }
        }
    }

    std::shared_ptr<FunctionCall> HLIRGenerator::visitFunctionCall(IronParser::FunctionCallContext *ctx,
                                                                   const std::shared_ptr<Function> &currentFunction)
    {

        const auto functionName = ctx->functionName->getText();

        if (const auto globalFunction = context->getFunctionByName(functionName))
        {
            const auto callArgs = std::make_shared<FunctionCallArgs>();
            const auto call =
                    std::make_shared<FunctionCall>()->set(globalFunction->getFunctionName(), globalFunction, callArgs);

            if (ctx->functionCallArgs())
            {
                visitFunctionCallArgs(ctx->functionCallArgs(), callArgs, currentFunction);
            }

            return call;
        }

        if (const auto variable = currentFunction->findVarCurrentScopeAndArg(functionName);
            variable && variable->getSignature())
        {

            const auto callArgs = std::make_shared<FunctionCallArgs>();
            std::shared_ptr<FunctionCall> call;

            std::shared_ptr<Function> function;
            if (variable->isFromFunctionArg())
            {
                function = createFunctionFromSignature(variable);
                call = std::make_shared<FunctionCall>()->set(functionName, function, callArgs);
            }
            else
            {
                function = getFunctionValue(currentFunction, functionName);
                call = std::make_shared<FunctionCall>()->set(functionName, function, callArgs);
            }

            if (ctx->functionCallArgs())
            {
                visitFunctionCallArgs(ctx->functionCallArgs(), callArgs, currentFunction);
            }

            createExternalCallArg(callArgs, function, currentFunction);

            return call;
        }

        throw HLIRException("HLIRGenerator::visitFunctionCall. Function not found");
    }

    void HLIRGenerator::visitFunctionCallArgs(const IronParser::FunctionCallArgsContext *ctx,
                                              const std::shared_ptr<FunctionCallArgs> &callArgs,
                                              const std::shared_ptr<Function> &currentFunction)
    {
        for (const auto child: ctx->children)
        {
            if (auto *arg = dynamic_cast<IronParser::FunctionCallArgContext *>(child))
            {
                visitFunctionCallArg(arg, callArgs, currentFunction);
            }
        }
    }

    void HLIRGenerator::visitFunctionCallArg(IronParser::FunctionCallArgContext *ctx,
                                             const std::shared_ptr<FunctionCallArgs> &callArgs,
                                             const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        auto argName = ctx->varName->getText();
        auto callFunction = std::dynamic_pointer_cast<FunctionCall>(callArgs->getParent());

        if (!callFunction)
        {
            throw HLIRException("HLIRGenerator::visitFunctionCallArg. The callFunction not found");
        }

        if (ctx->dataFormat())
        {
            const auto strValue = ctx->dataFormat()->getText();
            const auto realType = defineRealType(strValue);

            auto strAnotherVar = currentFunction->generateVarName();
            auto type = std::make_shared<Type>(realType);

            auto anotherVar = std::make_shared<Variable>()->set(strAnotherVar, type);
            // statement->setParent(anotherVar);
            statement->addDeclaredVariable(anotherVar);
            auto value = std::make_shared<Value>()->set(strValue, std::make_shared<Type>(realType));
            auto assign = std::make_shared<Assign>()->set(anotherVar, value);

            auto variableValue = std::make_shared<Value>()->set(anotherVar, std::make_shared<Type>(realType));
            // auto value = std::make_shared<Value>()->set(anotherVar, type);
            callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, type, variableValue));

            // auto expr = std::make_shared<Expr>()->set(anotherVar, assign);
            statement->addStatement(assign);

            // callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, std::make_shared<Type>(realType),
            // value));
        }

        if (ctx->anotherVarName)
        {

            if (dynamic_cast<IronParser::FunctionCallContext *>(ctx->parent->parent))
            {

                std::shared_ptr<Function> function;
                const auto inlineFunctionName = callFunction->getFunction()->getFunctionName();
                if (const auto variable = currentFunction->findVarCurrentScopeAndArg(inlineFunctionName);
                    variable && variable->getSignature())
                {
                    function = callFunction->getFunction();
                }
                else
                {
                    function = context->getFunctionByName(inlineFunctionName);
                    if (!function)
                    {
                        function = getFunctionValue(currentFunction, inlineFunctionName);
                        if (!function)
                        {
                            throw HLIRException("HLIRGenerator::visitFunctionCallArg. Function not found");
                        }
                    }
                }

                const auto arg = function->getFunctionArgs()->findArgByName(argName);
                if (!arg)
                {
                    if (!callFunction->getFunction()->isExternal() && !callFunction->getFunction()->isVariedArguments())
                    {
                        throw HLIRException("HLIRGenerator::visitFunctionCallArg. Arg not found");
                    }
                }

                const auto anotherVarName = ctx->anotherVarName->getText();
                auto anotherVar = currentFunction->findVarAllScopesAndArg(anotherVarName);
                if (!anotherVar)
                {
                    if (arg->type->getType() == tokenMap::FUNCTION)
                    {
                        const auto function = context->getFunctionByName(anotherVarName);
                        const auto value = std::make_shared<Value>()->set(function, arg->type);
                        callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, arg->type, value));
                        return;
                    }

                    auto variable = currentFunction->findVarAllScopesAndArg(anotherVarName);
                    if (!variable)
                    {
                        throw HLIRException("HLIRGenerator::visitFunctionCallArg. Variable not found");
                    }

                    if (variable->isAnotherScope())
                    {
                        ensureVariableCaptured(currentFunction, variable);
                    }

                    anotherVar = variable;
                }

                if (anotherVar->isAnotherScope())
                {
                    ensureVariableCaptured(currentFunction, anotherVar);
                }

                auto type = anotherVar->getVarType();
                auto value = std::make_shared<Value>()->set(anotherVar, type);
                callArgs->addCallArg(std::make_shared<FunctionCallArg>(argName, type, value));
            }
        }

        if (ctx->functionCall())
        {
            auto functionName = ctx->functionCall()->functionName->getText();
            auto calledFunction = context->getFunctionByName(functionName);

            if (!calledFunction)
            {
                auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
                auto inlineFunctionName = iron::createFunctionName(currentFunction->getFunctionName(), functionName);

                calledFunction = context->getFunctionByName(inlineFunctionName);

                if (!calledFunction)
                {
                    throw HLIRException("HLIRGenerator::visitFunctionCallArg. Function not found");
                }
            }

            auto localCallFunction = visitFunctionCall(ctx->functionCall(), currentFunction);

            auto strAnotherVar = currentFunction->generateVarName();
            auto anotherVar = std::make_shared<Variable>()->set(strAnotherVar, calledFunction->getFunctionReturnType());
            statement->addDeclaredVariable(anotherVar);
            auto expr = std::make_shared<Expr>()->set(anotherVar, localCallFunction);
            statement->addStatement(expr);

            auto arg = callFunction->getFunction()->getFunctionArgs()->findArgByName(argName);
            if (!arg)
            {
                if (!callFunction->getFunction()->isExternal() && !callFunction->getFunction()->isVariedArguments())
                {
                    throw HLIRException("HLIRGenerator::visitFunctionCallArg. Arg not found");
                }
            }


            if (callFunction->getFunction()->isExternal() && callFunction->getFunction()->isVariedArguments())
            {
                const auto type = anotherVar->getVarType();
                auto value = std::make_shared<Value>()->set(anotherVar, std::make_shared<Type>(type->getType()));
                callArgs->addCallArg(
                        std::make_shared<FunctionCallArg>(argName, std::make_shared<Type>(type->getType()), value));
            }
            else
            {
                auto value = std::make_shared<Value>()->set(anotherVar, std::make_shared<Type>(arg->type->getType()));
                callArgs->addCallArg(std::make_shared<FunctionCallArg>(
                        argName, std::make_shared<Type>(arg->type->getType()), value));
            }
        }
    }


    void HLIRGenerator::visitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx,
                                                 const std::shared_ptr<Function> &currentFunction)
    {
        const auto currentStatement = currentFunction->getCurrentLocalScope();
        // Verifica se o nó pai é uma declaração de variável (VarDeclarationContext)
        if (const auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
        {
            const auto arrowFuncName = varDeclaration->varName->getText();
            const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
            const auto variable = currentFunction->findVarAllScopesAndArg(arrowFuncName);
            if (!variable)
            {
                throw HLIRException("HLIRGenerator::visitArrowFunctionInline. Variable not found");
            }


            // Cria um nome único para a função no escopo global
            const auto inlineFunctionName = iron::createFunctionName(currentFunction->getFunctionName(), arrowFuncName);

            // Verifica se há tipo de retorno na assinatura da arrow function
            std::string returnTypeStr;
            if (ctx->functionSignature()->functionReturnType())
            {
                returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
            }
            else
            {
                returnTypeStr = getTokenText(tokenMap::VOID);
            }

            const auto functionArgs = std::make_shared<FunctionArgs>();
            const auto functionReturnType = std::make_shared<Type>(tokenMap::getTokenType(returnTypeStr));
            const auto inlineStatement = std::make_shared<Statement>();

            const auto arrowFunction =
                    std::make_shared<Function>()->set(inlineFunctionName, functionArgs, functionReturnType);

            const auto value = std::make_shared<Value>()->set(arrowFunction, type);
            const auto assign = std::make_shared<Assign>()->set(variable, value);
            currentStatement->addStatement(assign);

            arrowFunction->enableInline();
            context->addFunction(arrowFunction);

            if (ctx->functionSignature())
            {
                visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
            }


            if (ctx->expr())
            {
                // const auto varName = visitExpr(ctx->expr(), statement);
                // auto [_, variable] = findVarByScope(inlineFunction, varName);

                arrowFunction->enterLocalScope(std::make_shared<Statement>());
                const auto varName = visitExpr(ctx->expr(), arrowFunction);
                const auto variable = arrowFunction->findVarAllScopesAndArg(varName);

                if (functionReturnType->getType() != tokenMap::VOID)
                {
                    auto funcReturn = std::make_shared<FuncReturn>(arrowFunction, variable);
                    arrowFunction->getCurrentLocalScope()->addStatement(funcReturn);
                }

                arrowFunction->exitLocalScope();
            }

            arrowFunction->enterLocalScope(std::make_shared<Statement>());
            if (ctx->statementList())
            {
                visitStatementList(ctx->statementList(), arrowFunction);
            }
            arrowFunction->exitLocalScope();
            variable->setSignature(createSignatureFromFunction(arrowFunction));
        }
    }

    std::shared_ptr<Signature> HLIRGenerator::createSignatureFromFunction(const std::shared_ptr<Function> &function)
    {
        const auto signature = std::make_shared<Signature>(function->getFunctionReturnType());

        for (const auto &arg: function->getFunctionArgs()->getArgs())
        {
            signature->addArg(arg);
        }

        return signature;
    }

    // void HLIRGenerator::visitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx,
    //                                             const std::shared_ptr<Function> &currentFunction)
    // {
    //     const auto currentStatement = currentFunction->getCurrentLocalScope();
    //     if (const auto *varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent->parent))
    //     {
    //         const auto arrowFuncName = varDeclaration->varName->getText();
    //         const auto type = std::make_shared<Type>(tokenMap::FUNCTION);
    //         const auto variable = currentFunction->findVarAllScopesAndArg(arrowFuncName);
    //         if (!variable)
    //         {
    //             throw HLIRException("HLIRGenerator::visitArrowFunctionInline. Variable not found");
    //         }
    //
    //         // Cria um nome único para a função no escopo global
    //         const std::string inlineFunctionName =
    //                 iron::createFunctionName(currentFunction->getFunctionName(), arrowFuncName);
    //
    //         // Verifica se há tipo de retorno na assinatura da arrow function
    //         std::string returnTypeStr;
    //         if (ctx->functionSignature()->functionReturnType())
    //         {
    //             returnTypeStr = ctx->functionSignature()->functionReturnType()->varTypes()->getText();
    //         }
    //         else
    //         {
    //             returnTypeStr = getTokenText(tokenMap::VOID);
    //         }
    //
    //
    //         const auto functionArgs = std::make_shared<FunctionArgs>();
    //         const auto functionReturnType = std::make_shared<Type>(tokenMap::getTokenType(returnTypeStr));
    //         const auto inlineStatement = std::make_shared<Statement>();
    //
    //         auto arrowFunction =
    //                 std::make_shared<Function>()->set(inlineFunctionName, functionArgs, functionReturnType);
    //         const auto value = std::make_shared<Value>()->set(arrowFunction, type);
    //         const auto assign = std::make_shared<Assign>()->set(variable, value);
    //         currentStatement->addStatement(assign);
    //
    //         arrowFunction->enableInline();
    //         context->addFunction(arrowFunction);
    //
    //         arrowFunction->enterLocalScope(std::make_shared<Statement>());
    //         if (ctx->functionSignature())
    //         {
    //             visitFunctionSignature(ctx->functionSignature(), functionArgs, functionReturnType);
    //         }
    //
    //         if (ctx->statementList())
    //         {
    //             visitStatementList(ctx->statementList(), arrowFunction);
    //         }
    //         arrowFunction->exitLocalScope();
    //         variable->setSignature(createSignatureFromFunction(arrowFunction));
    //     }
    // }


    void HLIRGenerator::visitReturn(IronParser::ReturnStatementContext *ctx,
                                    const std::shared_ptr<Function> &currentFunction)
    {

        const auto statement = currentFunction->getCurrentLocalScope();

        if (ctx->dataFormat())
        {
            const auto strValue = ctx->dataFormat()->getText();
            auto valueType = tokenMap::determineType(strValue);
            if (valueType == tokenMap::REAL_NUMBER)
            {
                valueType = tokenMap::determineFloatType(strValue);
            }

            const auto varName = currentFunction->generateVarName();
            const auto variable = std::make_shared<Variable>()->set(varName, std::make_shared<Type>(valueType));
            statement->addDeclaredVariable(variable);

            const auto value = std::make_shared<Value>()->set(strValue, variable->getVarType());
            const auto assign = std::make_shared<Assign>()->set(variable, value);
            statement->addStatement(assign);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            statement->addStatement(funcReturn);
        }

        if (ctx->varName)
        {
            const auto variable = currentFunction->findVarAllScopesAndArg(ctx->varName->getText());
            if (!variable)
            {
                throw HLIRException("HLIRGenerator::visitReturn. Variable not found");
            }
            if (variable->isAnotherScope())
            {
                ensureVariableCaptured(currentFunction, variable);
            }

            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            statement->addStatement(funcReturn);
        }


        if (ctx->expr())
        {
            const auto varName = visitExpr(ctx->expr(), currentFunction);
            const auto variable = currentFunction->findVarAllScopesAndArg(varName);
            if (!variable)
            {
                throw HLIRException("HLIRGenerator::visitReturn. Variable not found");
            }

            const auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            statement->addStatement(funcReturn);
        }

        if (ctx->functionCall())
        {
            const auto varName = currentFunction->generateVarName();
            const auto funcCall = visitFunctionCall(ctx->functionCall(), currentFunction);

            const auto funcReturnType = funcCall->getFunction()->getFunctionReturnType();
            const auto variable = std::make_shared<Variable>()->set(varName, funcReturnType);
            statement->addDeclaredVariable(variable);
            const auto expr = std::make_shared<Expr>()->set(variable, funcCall);
            statement->addStatement(expr);
            auto funcReturn = std::make_shared<FuncReturn>(currentFunction, variable);
            statement->addStatement(funcReturn);
        }
    }



    std::shared_ptr<Function> HLIRGenerator::gatArrowFunction(const std::shared_ptr<Function> &currentFunction,
                                                              const std::string &functionName)
    {
        const auto variable = currentFunction->findVarAllScopesAndArg(functionName);
        if (!variable)
        {
            throw HLIRException(util::format(" HLIRGenerator::gatArrowFunction. Function {} not found", functionName));
        }

        if (variable->getVarType()->getType() != tokenMap::FUNCTION)
        {
            throw HLIRException(
                    util::format(" HLIRGenerator::gatArrowFunction. The variable {} is not a function", functionName));
        }

        const auto localFunction = getFunctionValue(currentFunction, variable->getVarName());
        if (!localFunction)
        {
            throw HLIRException(util::format(
                    " HLIRGenerator::gatArrowFunction. The variable {} not have a function value", functionName));
        }

        return localFunction;
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

    void HLIRGenerator::registerExternalFunction(const std::shared_ptr<Function> &function) const
    {
        const auto externalFunction = function->clone();
        externalFunction->changeToExternal();
        if (function->isVariedArguments())
        {
            externalFunction->changeToVariedArguments();
        }

        externalFunction->setLanguageType(function->getLanguageType());

        context->addExternalFunction(externalFunction);
    }

    void HLIRGenerator::visitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx) const
    {
        const std::string functionName = ctx->exterFunctionName->getText();

        const auto functionArgs = std::make_shared<FunctionArgs>();
        const auto functionReturnType = std::make_shared<Type>();

        const auto function = std::make_shared<Function>()->set(functionName, functionArgs, functionReturnType);
        function->setLanguageType(tokenMap::C_LANG);
        function->changeToExternal();
        if (ctx->varied)
        {
            function->changeToVariedArguments();
        }

        context->addFunction(function);

        functionReturnType->set(tokenMap::VOID);
        if (ctx->functionReturnType())
        {
            functionReturnType->set(tokenMap::getTokenType(ctx->functionReturnType()->varTypes()->getText()));
        }

        if (ctx->externFunctionArgs())
        {
            visitExternFunctionArgs(ctx->externFunctionArgs(), functionArgs);
        }
    }

    void HLIRGenerator::visitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx,
                                                const std::shared_ptr<FunctionArgs> &argsList)
    {
        for (const auto arg: ctx->externFunctionArg())
        {
            visitExternFunctionArg(arg, argsList);
        }
    }
    void HLIRGenerator::visitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx,
                                               const std::shared_ptr<FunctionArgs> &argsList)
    {
        const auto argName = ctx->varName->getText();
        const auto type = std::make_shared<Type>();

        if (ctx->ptr)
        {
            const auto ptrType = tokenMap::getTokenType(ctx->cTypes()->getText());
            type->set(tokenMap::getPtrFromType(ptrType));
        }
        else
        {
            type->set(tokenMap::getTokenType(ctx->cTypes()->getText()));
        }

        argsList->addArg(std::make_shared<Arg>()->set(argName, type));
    }
} // namespace hlir

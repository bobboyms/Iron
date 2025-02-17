#include "../../headers/HLIRGenerator.h"
#include "../../headers/Analyser.h"
#include "../../headers/Files.h"
#include "../../headers/Hlir.h"


namespace hlir
{
    bool HLIRGenerator::hasVariableOrArg(const std::shared_ptr<Function> &F, const std::string &varName)
    {
        if (auto v = F->getStatement()->findVarByName(varName))
            return true;
        if (auto a = F->getFunctionArgs()->findArgByName(varName))
            return true;
        return false;
    }

    void HLIRGenerator::ensureVariableCaptured(const std::shared_ptr<Function> &F, const std::shared_ptr<Variable> &var)
    {
        if (hasVariableOrArg(F, var->getVarName()))
        {
            return;
        }

        if (!hasVariableOrArg(F, var->getVarName()))
        {
            const auto functionArgs = F->getFunctionArgs();
            const auto newArg = std::make_shared<Arg>()->set(var->getVarName(), var->getVarType());
            functionArgs->addArg(newArg);
        }

        auto parentF = F->getParentFunction();
        if (!parentF)
        {
            throw HLIRException("Variável não encontrada em escopo global");
        }

        ensureVariableCaptured(parentF, var);
    }

    std::pair<int, std::shared_ptr<Variable>> HLIRGenerator::findVarByScope(const std::shared_ptr<Statement> &Statement,
                                                                            const std::string &varName)
    {

        auto currentFunction = std::dynamic_pointer_cast<Function>(Statement->getParent());

        int scopeNumber = 0;
        while (currentFunction)
        {
            // 1. Tenta achar como variável local
            if (auto variable = currentFunction->getStatement()->findVarByName(varName))
            {
                // Se subimos algum nível, marque a variável como estando em outro escopo
                if (scopeNumber > 0)
                {
                    variable->changeToAnotherScope();
                }
                return {scopeNumber, variable};
            }

            // 2. Tenta achar como argumento
            if (const auto arg = currentFunction->getFunctionArgs()->findArgByName(varName))
            {
                // Cria um objeto Variable baseado no Arg encontrado
                auto variable = std::make_shared<Variable>()->set(arg->name, arg->type);

                // Se subimos algum nível, marque a variável como estando em outro escopo
                if (scopeNumber > 0)
                {
                    variable->changeToAnotherScope();
                }
                return {scopeNumber, variable};
            }

            // 3. Se não achou nem variável local, nem argumento,
            //    subimos para o próximo escopo (função pai)
            const auto parentFunction = currentFunction->getParentFunction();
            if (!parentFunction)
            {
                // Não há mais escopos para subir: variável não existe
                break;
            }

            scopeNumber++;
            currentFunction = parentFunction;
        }

        // 4. Se chegar aqui, não encontrou a variável em nenhum escopo
        throw HLIRException(util::format("Undefined variable: {} in expression", varName));
    }

    HLIRGenerator::HLIRGenerator(
            const std::shared_ptr<IronParser> &parser, const std::__1::shared_ptr<Context> &context,
            const std::shared_ptr<config::Configuration> &config,
            const std::shared_ptr<std::map<std::string, std::shared_ptr<Context>>> &exportContexts) :
        parser(parser), context(context), config(config), exportContexts(exportContexts)
    {
        if (!parser)
        {
            throw HLIRException("The parser can't be nullptr");
        }

        if (!context)
        {
            throw HLIRException("The context can't be nullptr");
        }

        if (!config)
        {
            throw HLIRException("The config can't be nullptr");
        }

        if (!exportContexts)
        {
            throw HLIRException("The exportContexts can't be nullptr");
        }
    }

    HLIRGenerator::~HLIRGenerator() = default;


    void HLIRGenerator::visitStatementList(const IronParser::StatementListContext *ctx,
                                           const std::shared_ptr<Statement> &statement)
    {

        const auto function = std::dynamic_pointer_cast<Function>(statement->getParent());


        for (const auto child: ctx->children)
        {
            if (const auto varDeclaration = dynamic_cast<IronParser::VarDeclarationContext *>(child))
            {
                visitVarDeclaration(varDeclaration, statement);
            }

            if (const auto expression = dynamic_cast<IronParser::ExprContext *>(child))
            {
                visitExpr(expression, statement);
            }
            if (const auto funcCall = dynamic_cast<IronParser::FunctionCallContext *>(child))
            {
                auto call = visitFunctionCall(funcCall, statement);
                statement->addStatement(call);
            }
            if (const auto re_turn = dynamic_cast<IronParser::ReturnStatementContext *>(child))
            {
                visitReturn(re_turn, statement);
            }
        }
    }

    void HLIRGenerator::visitVarDeclaration(IronParser::VarDeclarationContext *ctx,
                                            const std::shared_ptr<Statement> &statement)
    {
        const std::string varName = ctx->varName->getText();

        if (const std::string varType = ctx->varTypes()->getText();
            tokenMap::getTokenType(varType) == tokenMap::FUNCTION)
        {
            const auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
            if (!currentFunction)
            {
                throw HLIRException("Error: std::dynamic_pointer_cast<Function>(statement->getParent())");
            }

            const auto alias = iron::createFunctionName(currentFunction->getFunctionName(), varName);

            if (auto aliasFunction = context->getFunctionByName(alias); !aliasFunction)
            {
                if (ctx->assignment())
                {
                    visitAssignment(ctx->assignment(), statement);
                }
            }
            else
            {
                auto funcPtr = std::make_shared<FunctionPtr>()->set(aliasFunction);
                const auto variable = std::make_shared<Variable>()->set(
                        varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                const auto value =
                        std::make_shared<Value>()->set(aliasFunction, std::make_shared<Type>(tokenMap::FUNCTION_PTR));
                auto assign = std::make_shared<Assign>()->set(variable, value);

                statement->addStatement(assign);
            }
        }
        else if (ctx->assignment())
        {

            visitAssignment(ctx->assignment(), statement);
        }
    }

    void HLIRGenerator::visitVarAssignment(IronParser::VarAssignmentContext *ctx, std::shared_ptr<Statement> statement)
    {
        throw std::runtime_error("Error: HLIRGenerator::visitVarAssignment. Não implementado.");
    }

    void HLIRGenerator::visitAssignment(IronParser::AssignmentContext *ctx, const std::shared_ptr<Statement> &statement)
    {

        if (auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent()); !currentFunction)
        {
            throw HLIRException("HLIRGenerator::visitAssignment. The current function not found.");
        }

        if (ctx->dataFormat())
        {
            // Caso 1: a atribuição está sendo feita a um argumento de função
            if (auto *functionArg = dynamic_cast<IronParser::FunctionArgContext *>(ctx->parent))
            {
                std::string argName = functionArg->varName->getText();
                std::string argType = functionArg->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();
            }

            // Caso 2: a atribuição está sendo feita a uma variável declarada
            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();
                std::string literalValue = ctx->dataFormat()->getText();

                auto variable = std::make_shared<Variable>()->set(
                        varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                auto value = std::make_shared<Value>()->set(literalValue,
                                                            std::make_shared<Type>(tokenMap::getTokenType(varType)));
                auto assign = std::make_shared<Assign>()->set(variable, value);

                statement->addStatement(assign);
            }
        }

        if (ctx->varName)
        {

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {

                const auto anotherVar = ctx->varName->getText();
                std::string varName = varDecl->varName->getText();
                std::string varType = varDecl->varTypes()->getText();

                if (auto currentFunction = std::dynamic_pointer_cast<Function>(statement->getParent());
                    !currentFunction)
                {
                    throw HLIRException("HLIRGenerator::visitAssignment. The current function not found.");
                }

                const auto variable = std::make_shared<Variable>()->set(
                        varName, std::make_shared<Type>(tokenMap::getTokenType(varType)));
                const auto [__, anotherVariable] = findVarByScope(statement, anotherVar);
                auto value = std::make_shared<Value>()->set(anotherVariable, anotherVariable->getVarType());
                auto assign = std::make_shared<Assign>()->set(variable, value);
                statement->addStatement(assign);
            }
        }

        if (ctx->boolExpr())
        {

            const auto rightVarStr = visitBoolExpr(ctx->boolExpr(), statement);
            const auto [_, rightVar] = findVarByScope(statement, rightVarStr);

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                const auto strLeftVarName = varDecl->varName->getText();
                const auto strLeftvarTypeName = varDecl->varTypes()->getText();

                int leftDataTypeType = tokenMap::getTokenType(strLeftvarTypeName);
                auto leftVar =
                        std::make_shared<Variable>()->set(strLeftVarName, std::make_shared<Type>(leftDataTypeType));

                auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                auto assign = std::make_shared<Assign>()->set(leftVar, value);
                statement->addStatement(assign);
            }
        }

        if (ctx->expr())
        {

            const auto strRightVarName = visitExpr(ctx->expr(), statement);
            const auto [_, rightVar] = findVarByScope(statement, strRightVarName);
            // auto rightVar = variable.second;

            if (!rightVar)
            {
                throw HLIRException("HLIRGenerator::visitAssignment. The rightVar not found");
            }

            if (auto varDecl = dynamic_cast<IronParser::VarDeclarationContext *>(ctx->parent))
            {
                std::string strLeftVarName = varDecl->varName->getText();
                std::string strLeftvarTypeName = varDecl->varTypes()->getText();

                int leftDataTypeType = tokenMap::getTokenType(strLeftvarTypeName);
                auto leftVar =
                        std::make_shared<Variable>()->set(strLeftVarName, std::make_shared<Type>(leftDataTypeType));

                // TODO: adicionar nova variaves externas aos argumentos locais das funções
                //  if (rightVar->isAnotherScope())
                //  {
                //      // auto functionArgs = currentFunction->getFunctionArgs();
                //      // auto arg = std::make_shared<Arg>()->set(rightVar->getVarName(), rightVar->getVarType());
                //      // functionArgs->addArg(arg);
                //      ensureVariableCaptured(currentFunction,leftVar);
                //  }
                //
                //  if (leftVar->isAnotherScope())
                //  {
                //      // auto functionArgs = currentFunction->getFunctionArgs();
                //      // auto arg = std::make_shared<Arg>()->set(leftVar->getVarName(), leftVar->getVarType());
                //      // functionArgs->addArg(arg);
                //
                //      ensureVariableCaptured(currentFunction,leftVar);
                //  }

                if (leftDataTypeType != rightVar->getVarType()->getType())
                {
                    std::string strTempVar = statement->getNewVarName();

                    auto cast = std::make_shared<Cast>()->apply(rightVar, std::make_shared<Type>(leftDataTypeType));
                    auto tempVariable =
                            std::make_shared<Variable>()->set(strTempVar, std::make_shared<Type>(leftDataTypeType));

                    auto expr = std::make_shared<Expr>()->set(tempVariable, cast);
                    statement->addStatement(expr);

                    auto value = std::make_shared<Value>()->set(tempVariable, tempVariable->getVarType());
                    auto assign = std::make_shared<Assign>()->set(leftVar, value);
                    statement->addStatement(assign);
                }
                else
                {
                    auto value = std::make_shared<Value>()->set(rightVar, rightVar->getVarType());
                    auto assign = std::make_shared<Assign>()->set(leftVar, value);
                    statement->addStatement(assign);
                }
            }
        }

        if (ctx->arrowFunctionBlock())
        {
            visitArrowFunctionBlock(ctx->arrowFunctionBlock(), statement);
        }
        else if (ctx->arrowFunctionInline())
        {
            visitArrowFunctionInline(ctx->arrowFunctionInline(), statement);
        }
    }

    std::shared_ptr<Context> HLIRGenerator::getContext()
    {
        IronParser::ProgramContext *programContext = parser->program();

        for (const auto importStmt: programContext->importStatement())
        {
            visitImportStatement(importStmt);
        }

        if (programContext->externBlock())
        {
            visitExternBlock(programContext->externBlock());
        }

        for (const auto child: programContext->children)
        {
            if (const auto funcDecl = dynamic_cast<IronParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        return context;
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
                if (auto foundContext = it->second)
                {
                    auto externalFunction = foundContext->getFunctionByName(element);
                    registerExternalFunction(externalFunction);
                }
            }
            else
            {
                const iron::Analyser analyser(config);
                const auto parentContext = analyser.hlir(fullPath, exportContexts);
                exportContexts->emplace(fullPath, parentContext);

                const auto hlirPath = util::format("{}{}", config->outputHLIR(), path);
                const auto pathAndFile = iron::saveToFile(parentContext->getText(), hlirPath, "hlir");

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
        if (function)
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
        const std::string functionName = ctx->exterFunctionName->getText();

        const auto functionArgs = std::make_shared<FunctionArgs>();
        const auto functionReturnType = std::make_shared<Type>();
        const auto statement = std::make_shared<Statement>();

        const auto function =
                std::make_shared<Function>()->set(functionName, functionArgs, functionReturnType, statement);
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

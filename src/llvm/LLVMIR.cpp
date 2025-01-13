#include "../headers/LLVMIR.h"
#include "../headers/Exceptions.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{

    LLVMIR::LLVMIR(std::string code, std::unique_ptr<ScopeManager> scopeManager)
        : hlirCode(code), scopeManager(std::move(scopeManager)), builder(context)
    {
        module = std::make_unique<llvm::Module>("file_1", context);
        module->setTargetTriple("arm64-apple-macosx15.0.0");
    }

    LLVMIR::~LLVMIR() {}

    std::string LLVMIR::generateCode()
    {
        if (hlirCode.empty())
        {
            throw std::runtime_error("Code is not properly initialized.");
        }

        std::cout << hlirCode << std::endl;

        antlr4::ANTLRInputStream inputStream(hlirCode);
        HightLavelIRLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<HightLavelIRParser>(&tokens);
        scopeManager->enterScope(tokenMap::getTokenText(tokenMap::GLOBAL));

        HightLavelIRParser::ProgramContext *programContext = parser->program();

        for (auto child : programContext->children)
        {
            if (auto funcDecl = dynamic_cast<HightLavelIRParser::FunctionDeclarationContext *>(child))
            {
                visitFunctionDeclaration(funcDecl);
            }
        }

        scopeManager->exitScope(tokenMap::getTokenText(tokenMap::GLOBAL));
        // Verifica a validade do módulo e captura mensagens de erro
        std::string errorStr;
        llvm::raw_string_ostream errorStream(errorStr);

        if (llvm::verifyModule(*module, &errorStream))
        {
            throw LLVMException(util::format("{} {}", color::colorText(util::format("Invalid LLVM module:", ""), color::BOLD_RED),
                                             errorStream.str()));
        }

        // Captura o LLVM IR em uma string
        std::string irStr;
        llvm::raw_string_ostream irStream(irStr);
        module->print(irStream, nullptr);
        return irStr;
    }

    void LLVMIR::visitStatementList(HightLavelIRParser::StatementListContext *ctx)
    {
        for (auto child : ctx->children)
        {
            if (auto exp = dynamic_cast<HightLavelIRParser::ExprContext *>(child))
            {
                visitExpr(exp);
            }

            if (auto funcCall = dynamic_cast<HightLavelIRParser::FunctionCallContext *>(child))
            {
                visitFunctionCall(funcCall);
            }
        }
    }

    void LLVMIR::visitExpr(HightLavelIRParser::ExprContext *ctx)
    {
        const std::string varName = ctx->varName->getText();
        const auto varType = tokenMap::getTokenType(ctx->varTypes()->getText());
        auto currentScope = scopeManager->currentScope();

        util::printf("varName {}, varType {}", varName, ctx->varTypes()->getText());

        if (varType == tokenMap::FUNCTION)
        {

            if (!ctx->functionPtr())
            {
                throw LLVMException(util::format("The variable: {} is not function ptr", varName));
            }

            std::string functionName = ctx->functionPtr()->functionName->getText();
            llvm::Function *func = module->getFunction(functionName);

            llvm::Type *funcPtrType = func->getType();
            llvm::FunctionType *functionType = func->getFunctionType();

            llvm::PointerType *gfnPtrPtrType = llvm::PointerType::getUnqual(funcPtrType);
            llvm::AllocaInst *functionPtrVar = builder.CreateAlloca(funcPtrType, nullptr, varName);

            llvm::Constant *gfnPtr = llvm::ConstantExpr::getBitCast(func, funcPtrType);

            // Armazena o ponteiro da função
            builder.CreateStore(gfnPtr, functionPtrVar);
            currentScope->addSymbol(varName, {tokenMap::FUNCTION, tokenMap::FUNCTION_PTR, nullptr, {}, "", functionPtrVar, funcPtrType, functionType});
        }
        else
        {
            llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
            llvm::BasicBlock &entryBlock = currentFunction->getEntryBlock();
            llvm::IRBuilder<> tmpBuilder(&entryBlock, entryBlock.begin());

            llvm::Type *llvmType = mapType(varType);
            llvm::AllocaInst *allocaVariable = tmpBuilder.CreateAlloca(llvmType, nullptr, varName);
            currentScope->addSymbol(varName, {tokenMap::VARIABLE, varType, nullptr, {}, "", allocaVariable});

            if (ctx->number())
            {
                // **Step 2: Create the constant value**
                const std::string literalValue = ctx->number()->getText();
                literalToRealNumber(varType, literalValue, allocaVariable);
            }

            else if (ctx->mathOp())
            {
                mathematicalOperations(ctx, allocaVariable, varType, varName, llvmType);
            }
            else if (ctx->functionCall())
            {
            }
            else if (ctx->cast())
            {
                numberCasting(ctx, allocaVariable);
            }
            else if (ctx->functionCall())
            {
                std::string functionName = ctx->functionCall()->functionName->getText();
            }
            else
            {
                throw LLVMException("Unsupported expression in visitExpr.");
            }
        }
    }

    void LLVMIR::visitCast(HightLavelIRParser::CastContext *ctx)
    {
        // Implementação do método
    }

    void LLVMIR::visitOp(HightLavelIRParser::OpContext *ctx)
    {
        // Implementação do método
    }

    void LLVMIR::visitMathOp(HightLavelIRParser::MathOpContext *ctx)
    {
        // Implementação do método
    }

    void LLVMIR::visitFunctionReturnType(HightLavelIRParser::FunctionReturnTypeContext *ctx, llvm::Type *&functionReturnType)
    {
        if (ctx->VOID())
        {
            functionReturnType = mapType(tokenMap::VOID);
        }
        else
        {
            functionReturnType = mapType(tokenMap::getTokenType(ctx->varTypes()->getText()));
        }
    }

    void LLVMIR::visitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext *ctx)
    {
        std::string functionName = ctx->functionName->getText();
        auto returnType = ctx->functionSignature()->functionReturnType();

        scopeManager->enterScope(functionName);
        // Mapear o tipo de retorno
        llvm::Type *functionReturnType = nullptr;
        std::vector<llvm::Type *> argTypes;
        std::vector<std::string> argNames;

        if (ctx->functionSignature())
        {
            visitFunctionSignature(ctx->functionSignature(), functionReturnType, argTypes, argNames);
        }

        if (!functionReturnType)
        {
            throw LLVMException("Function return type is not defined.");
        }

        llvm::FunctionType *funcType;
        if (argTypes.size() > 0)
        {
            // Definir o tipo da função
            funcType = llvm::FunctionType::get(
                functionReturnType,
                argTypes,
                false);
        }
        else
        {
            // Definir o tipo da função
            funcType = llvm::FunctionType::get(
                functionReturnType,
                llvm::ArrayRef<llvm::Type *>(),
                false);
        }

        // Definir a linkage baseada na visibilidade
        llvm::Function::LinkageTypes linkage = llvm::Function::ExternalLinkage; // Padrão

        // if (ctx->PRIVATE()) {
        //     linkage = llvm::Function::PrivateLinkage;
        // }

        // Criar a função no módulo
        llvm::Function *function = llvm::Function::Create(
            funcType,
            linkage,
            functionName,
            module.get());

        if (argTypes.size() > 0)
        {
            unsigned idx = 0;
            for (auto &arg : function->args())
            {
                if (idx < argNames.size())
                {
                    std::string argName = argNames[idx++];
                    arg.setName(argName);
                }
            }
        }

        // Criar o bloco básico "entry" e definir o ponto de inserção
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", function);
        builder.SetInsertPoint(entry);

        if (ctx->statementList())
        {
            visitStatementList(ctx->statementList());
        }

        // **Passo Adicional: Adicionar uma instrução terminadora**
        if (functionReturnType->isVoidTy())
        {
            builder.CreateRetVoid();
        }
        else
        {
            // Se a função deve retornar um valor, certifique-se de que todas as vias de execução retornem um valor
            // Caso contrário, lance uma exceção ou adicione um valor de retorno padrão
            throw LLVMException("Non-void function without a return statement.");
        }

        scopeManager->exitScope(functionName);
    }

    void LLVMIR::visitFunctionSignature(
        HightLavelIRParser::FunctionSignatureContext *ctx,
        llvm::Type *&functionReturnType,
        std::vector<llvm::Type *> &argTypes,
        std::vector<std::string> &argNames)
    {
        if (ctx->functionReturnType())
        {
            visitFunctionReturnType(ctx->functionReturnType(), functionReturnType);
        }

        if (ctx->functionArgs())
        {
            visitFunctionArgs(ctx->functionArgs(), argTypes, argNames);
        }
    }

    void LLVMIR::visitFunctionArgs(
        HightLavelIRParser::FunctionArgsContext *ctx,
        std::vector<llvm::Type *> &argTypes,
        std::vector<std::string> &argNames)
    {
        for (auto arg : ctx->functionArg())
        {
            visitFunctionArg(arg, argTypes, argNames);
        }
    }

    void LLVMIR::visitFunctionArg(
        HightLavelIRParser::FunctionArgContext *ctx,
        std::vector<llvm::Type *> &argTypes,
        std::vector<std::string> &argNames)
    {
        std::string argTypeStr = ctx->varTypes()->getText();
        std::string argName = ctx->varName->getText();
        // Mapear o tipo para LLVM
        argTypes.push_back(mapType(tokenMap::getTokenType(argTypeStr)));
        argNames.push_back(argName);
    }

    void LLVMIR::visitFunctionCall(HightLavelIRParser::FunctionCallContext *ctx)
    {
        auto globalScope = scopeManager->getScopeByName(tokenMap::getTokenText(tokenMap::GLOBAL));
        auto currentScope = scopeManager->currentScope();
        const std::string functionName = ctx->functionName->getText();

        auto functionOpt = currentScope->lookup(functionName);
        if (functionOpt.has_value())
        {
            auto function = functionOpt.value();

            if (function.type == tokenMap::FUNCTION)
            {

                llvm::Value *loadedFuncPtr = builder.CreateLoad(function.llvmType, function.alloca, util::format("loaded_{}", functionName));

                // llvm::Value *arg1 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 10);
                std::vector<llvm::Value *> args = {};

                if (ctx->functionCallArgs())
                {
                    visitFunctionCallArgs(ctx->functionCallArgs(), args);
                }

                llvm::FunctionCallee callee = llvm::FunctionCallee(function.llvmFuncType, loadedFuncPtr);

                if (function.llvmFuncType->getReturnType()->isVoidTy())
                {
                    // Se a função retorna void, não atribua um nome à chamada
                    builder.CreateCall(callee, args);
                }
                else
                {
                    // llvm::Value *callResult = builder.CreateCall(callee, args, util::format("call_inline_{}", functionName));

                    // builder.CreateCall(callee, args, util::format("call_inline_{}", functionName));

                    // Opcional: Armazena o resultado em uma variável (Alloca)
                    // llvm::AllocaInst *resultVar = builder.CreateAlloca(function.llvmFuncType->getReturnType(), nullptr, "result");
                    // builder.CreateStore(callResult, resultVar);
                }

                // quando tem retorno
            }
        }
        else
        {
            llvm::Function *function = module->getFunction(functionName);
            if (!function)
            {
                throw LLVMException(util::format("Function {} not found", functionName));
            }

            builder.CreateCall(function, llvm::ArrayRef<llvm::Value *>());
        }
    }

    void LLVMIR::visitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext *ctx, std::vector<llvm::Value *> args)
    {
        for (auto child : ctx->children)
        {
            if (auto arg = dynamic_cast<HightLavelIRParser::FunctionCallArgContext *>(child))
            {
                visitFunctionCallArg(arg, args);
            }
        }
    }

    void LLVMIR::visitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext *ctx, std::vector<llvm::Value *> args)
    {
        // llvm::Value *arg1 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 10);

        std::string argName = ctx->varName->getText();
        if (ctx->dataFormat())
        {
            std::string valueStr = ctx->dataFormat()->getText();
            int type = tokenMap::getTokenType(valueStr);

            if (type == tokenMap::REAL_NUMBER)
            {
                int dataType = tokenMap::determineFloatType(valueStr);

                llvm::Type *type = mapType(dataType);
                llvm::Value *arg = llvm::ConstantInt::get(type, 10);
            }
        }
    }
}

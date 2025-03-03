#include "../headers/Exceptions.h"
#include "../headers/LLVMIR.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron
{
    void LLVM::visitFunction(const std::shared_ptr<hlir::Function> &hlirFunction)
    {

        if (!hlirFunction)
        {
            throw LLVMException("LLVM::visitFunction. VisitFunction called with null hlirFunction");
        }

        if (hlirFunction->isExternal())
        {
            return;
        }

        llvm::Function *function = module->getFunction(hlirFunction->getFunctionName());

        if (!function)
        {
            throw LLVMException(
                    util::format("LLVM::visitFunction. Function {} not found", hlirFunction->getFunctionName()));
        }

        const llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvmContext, "entry", function);
        builder.SetInsertPoint(entry);

        // Cria todos os blocos basicos
        for (const auto block: hlirFunction->getAllBlocks())
        {
            llvm::BasicBlock::Create(llvmContext, block->getLabel(), function);
        }

        visitStatement(hlirFunction->getRootScope());
        if (functionReturnType->isVoidTy())
        {
            builder.CreateRetVoid();
        }
    }

    void LLVM::visitFuncReturn(const std::shared_ptr<hlir::FuncReturn> &funcReturn)
    {
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitAssignment: currentFunction is null");
        }

        const auto varName = funcReturn->getVariable()->getRealName();
        const auto allocaVariable = findAllocaByName(currentFunction, varName);

        const auto type = mapType(funcReturn->getVariable()->getVarType()->getType());

        llvm::Value *varValue = builder.CreateLoad(type, allocaVariable, util::format("load_{}", varName));
        // printf("Criou um retorno tipo: %s\n",
        // tokenMap::getTokenText(funcReturn->getVariable()->getVarType()->getType()).c_str());

        builder.CreateRet(varValue);
    }

    llvm::BasicBlock *LLVM::getBasicBlock(const std::string &blockName, llvm::Function *currentFunction)
    {
        for (auto &BB: *currentFunction)
        {
            if (BB.getName() == blockName)
            {
                return &BB;
            }
        }

        throw LLVMException(util::format("Block {} not found", blockName));
    }

    void LLVM::visitJump(const std::shared_ptr<hlir::Jump> &jump)
    {
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitExpr: currentFunction is null");
        }

        const auto basicBlock = getBasicBlock(jump->getBlock()->getLabel(), currentFunction);
        builder.CreateBr(basicBlock);
    }

    void LLVM::visitBlock(const std::shared_ptr<hlir::Block> &block)
    {
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitExpr: currentFunction is null");
        }


        const auto basicBlock = getBasicBlock(block->getLabel(), currentFunction);
        builder.SetInsertPoint(basicBlock);
    }

    // cria uma condicional if
    void LLVM::visitConditional(const std::shared_ptr<hlir::Conditional> &conditional)
    {

        if (!conditional)
        {
            throw LLVMException("visitConditional: conditional is null");
        }
        //
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitExpr: currentFunction is null");
        }

        const auto variable = getOrPromoteToAlloca(conditional->getVariable()->getRealName(), currentFunction);
        auto *cond = builder.CreateLoad(builder.getInt1Ty(), variable, "cond_");

        llvm::BasicBlock *thenBB = getBasicBlock(conditional->getTrueLabel(), currentFunction);
        llvm::BasicBlock *elseBB = getBasicBlock(conditional->getFalseLabel(), currentFunction);

        builder.CreateCondBr(cond, thenBB, elseBB);
    }

    llvm::Value *getArgumentByName(llvm::Function *F, const llvm::StringRef name)
    {
        for (auto &Arg: F->args())
        {
            if (Arg.getName() == name)
                return &Arg;
        }
        return nullptr; // Retorna nullptr se não encontrar o argumento
    }

    llvm::Value *LLVM::visitFunctionCallArg(const std::shared_ptr<hlir::FunctionCall> &functionCall,
                                            llvm::Value *funcArg)
    {

        const llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitAssignment: currentFunction is null");
        }

        const auto parentFunctionName = currentFunction->getName().str();
        const auto functionCallName = functionCall->getFunctionCallName();

        const auto parentFunction = hlirContext->getFunctionByName(parentFunctionName);
        if (!parentFunction)
        {
            throw LLVMException("LLVM::visitFunctionCallArg. parentFunction is null");
        }

        const auto variable = parentFunction->findVarAllScopesAndArg(functionCallName);
        if (!parentFunction)
        {
            throw LLVMException("LLVM::visitFunctionCallArg. variable is null");
        }

        if (!variable->getSignature())
        {
            throw LLVMException("LLVM::visitFunctionCallArg. Signature is null");
        }

        const auto targetFuncType = createFuncTypeFromSignature(variable->getSignature());

        std::vector<llvm::Value *> args;
        for (const auto &arg: functionCall->getCallArgs()->getCallArgs())
        {
            const auto value = createConstValue(arg->value->getValueType(), arg->value);
            args.push_back(value);
        }

        return builder.CreateCall(targetFuncType, funcArg, args, "call_func_arg");
    }

    llvm::Value *LLVM::visitFunctionCall(const std::shared_ptr<hlir::FunctionCall> &functionCall)
    {

        if (!functionCall)
        {
            throw LLVMException("visitFunctionCall called with null functionCall");
        }

        // Checar também functionCall->getFunction()
        if (!functionCall->getFunction())
        {
            throw LLVMException("visitFunctionCall: functionCall->getFunction() is null");
        }

        if (!functionCall->getCallArgs())
        {
            throw LLVMException("visitFunctionCall: functionCall->getCallArgs() is null");
        }

        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitAssignment: currentFunction is null");
        }

        // Obter o nome da função a ser chamada
        const auto functionName = functionCall->getFunction()->getFunctionName();

        // Buscar a função no módulo LLVM
        llvm::Function *function = module->getFunction(functionName);
        if (!function)
        {

            const auto funcArg = getArgumentByName(currentFunction, functionName);
            if (!funcArg)
            {
                throw LLVMException(util::format("LLVM::visitFunctionCall. Function {} not found", functionName));
            }

            return visitFunctionCallArg(functionCall, funcArg);
        }

        const auto arrowFunction = findAllocaByName(currentFunction, functionCall->getFunctionCallName());

        std::vector<llvm::Value *> args;
        for (const auto &arg: functionCall->getCallArgs()->getCallArgs())
        {
            const auto value = createConstValue(arg->value->getValueType(), arg->value);
            args.push_back(value);
        }

        // Verificar se o número de argumentos corresponde à assinatura da função
        if (!functionCall->getFunction()->isVariedArguments())
        {
            if (function->arg_size() != args.size())
            {
                throw LLVMException(util::format("LLVM::visitFunctionCall. Argument count mismatch for function {}.",
                                                 functionName));
            }
        }

        if (function->getReturnType()->isVoidTy())
        {
            if (arrowFunction)
            {
                llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(function->getFunctionType());
                llvm::Value *arrowLoaded =
                        builder.CreateLoad(funcPtrType, arrowFunction,
                                           util::format("arrow_{}_loaded", functionCall->getFunctionCallName()));
                return builder.CreateCall(function->getFunctionType(), arrowLoaded, args);
            }

            builder.CreateCall(function, args);
            return nullptr;
        }

        if (arrowFunction)
        {
            llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(function->getFunctionType());
            llvm::Value *arrowLoaded = builder.CreateLoad(
                    funcPtrType, arrowFunction, util::format("arrow_{}_loaded", functionCall->getFunctionCallName()));
            return builder.CreateCall(function->getFunctionType(), arrowLoaded, args,
                                      util::format("call_{}", functionCall->getFunctionCallName()));
        }

        return builder.CreateCall(function, args, "call_" + functionName);
    }

    llvm::FunctionType *LLVM::createFuncType(llvm::Type *functionReturnType, const std::vector<llvm::Type *> &argTypes,
                                             const bool isVariedArguments) const
    {
        llvm::FunctionType *funcType;
        if (!argTypes.empty())
        {
            funcType = llvm::FunctionType::get(functionReturnType, argTypes, isVariedArguments);
        }
        else
        {
            funcType = llvm::FunctionType::get(functionReturnType, llvm::ArrayRef<llvm::Type *>(), isVariedArguments);
        }

        return funcType;
    }

    llvm::FunctionType *LLVM::createFuncTypeFromSignature(const std::shared_ptr<hlir::Signature> &signature) const
    {
        llvm::Type *functionReturnType = mapType(signature->getReturnType()->getType());
        const auto [innerArgTypes, _] = createFunctionArgs(signature->getArgs());
        return createFuncType(functionReturnType, innerArgTypes, false);
    }

    std::pair<std::vector<llvm::Type *>, std::vector<std::string>>
    LLVM::createFunctionArgs(const std::vector<std::shared_ptr<hlir::Arg>> &args) const
    {
        std::vector<llvm::Type *> argTypes{};
        std::vector<std::string> argNames{};

        for (const auto &arg: args)
        {

            if (arg->type->getType() == tokenMap::FUNCTION)
            {
                if (!arg->signature)
                {
                    throw LLVMException("LLVM::createFunctionArgs. Arg don't have a signature. Arg name: " + arg->name);
                }

                const llvm::FunctionType *funcType = createFuncTypeFromSignature(arg->signature);
                argTypes.push_back(funcType->getPointerTo());
                argNames.push_back(arg->name);

            }
            else
            {
                argTypes.push_back(mapType(arg->type->getType()));
                argNames.push_back(arg->name);
            }
        }

        return std::make_pair(argTypes, argNames);
    }

    void LLVM::declareFunction(const std::shared_ptr<hlir::Function> &hlirFunction) const
    {

        if (module->getFunction(hlirFunction->getFunctionName()))
        {
            return;
        }

        llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        const auto [argTypes, argNames] = createFunctionArgs(hlirFunction->getFunctionArgs()->getArgs());

        llvm::FunctionType *funcType = createFuncType(functionReturnType, argTypes, hlirFunction->isVariedArguments());

        // Definir a linkage baseada na visibilidade
        constexpr llvm::Function::LinkageTypes linkage = llvm::Function::ExternalLinkage;

        const auto functionName = hlirFunction->getFunctionName();

        // Criar a função no módulo
        llvm::Function *function =
                llvm::Function::Create(funcType, linkage, functionName, module.get());

        if (!argTypes.empty())
        {
            unsigned idx = 0;
            for (auto &arg: function->args())
            {
                if (idx < argNames.size())
                {
                    const std::string &argName = argNames[idx++];
                    arg.setName(argName);
                }
            }
        }
    }
} // namespace iron

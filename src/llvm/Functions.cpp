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

        //Cria todos os blocos basicos
        for (const auto block : hlirFunction->getAllBlocks())
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

        const auto varName = funcReturn->getVariable()->getVarName();
        const auto allocaVariable = findAllocaByName(currentFunction, varName);

        const auto type = mapType(funcReturn->getVariable()->getVarType()->getType());

        llvm::Value *varValue = builder.CreateLoad(type, allocaVariable, util::format("load_{}", varName));
        // printf("Criou um retorno tipo: %s\n", tokenMap::getTokenText(funcReturn->getVariable()->getVarType()->getType()).c_str());

        builder.CreateRet(varValue);
    }

    llvm::BasicBlock *LLVM::getBasicBlock(const std::string &blockName, llvm::Function *currentFunction)
    {
        for (auto &BB : *currentFunction) {
            if (BB.getName() == blockName) {
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


        const auto basicBlock = getBasicBlock(block->getLabel(),currentFunction);
        builder.SetInsertPoint(basicBlock);

    }

    //cria uma condicional if
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

        //  = llvm::BasicBlock::Create(llvmContext, conditional->getTrueLabel(), currentFunction);
        //  = llvm::BasicBlock::Create(llvmContext, conditional->getFalseLabel(), currentFunction);

        // printf("Bloco quando true: %s\n", conditional->getTrueLabel().c_str());
        // printf("Bloco quando false: %s\n", conditional->getFalseLabel().c_str());

        const auto variable = getOrPromoteToAlloca(conditional->getVariable()->getVarName() ,currentFunction);
        auto *cond = builder.CreateLoad(builder.getInt1Ty(), variable, "cond_");

        llvm::BasicBlock *thenBB = getBasicBlock(conditional->getTrueLabel(), currentFunction);
        llvm::BasicBlock *elseBB = getBasicBlock(conditional->getFalseLabel(), currentFunction);

        builder.CreateCondBr(cond, thenBB, elseBB);
        // printf("builder.CreateBr: %s\n", conditional->getFalseLabel().c_str());
        // builder.CreateBr(thenBB);
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
            throw LLVMException(util::format("LLVM::visitFunctionCall. Function {} not found", functionName));
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
                throw LLVMException(
                        util::format("LLVM::visitFunctionCall. Argument count mismatch for function {}.", functionName));
            }
        }

        if (function->getReturnType()->isVoidTy())
        {
            if (arrowFunction)
            {
                llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(function->getFunctionType());
                llvm::Value *arrowLoaded = builder.CreateLoad(funcPtrType, arrowFunction, util::format("arrow_{}_loaded",functionCall->getFunctionCallName()));
                return builder.CreateCall(function->getFunctionType(), arrowLoaded,
                                                         args);
            }

            builder.CreateCall(function, args);
            return nullptr;
        }

        if (arrowFunction)
        {
            llvm::PointerType *funcPtrType = llvm::PointerType::getUnqual(function->getFunctionType());
            llvm::Value *arrowLoaded = builder.CreateLoad(funcPtrType, arrowFunction, util::format("arrow_{}_loaded",functionCall->getFunctionCallName()));
            return builder.CreateCall(function->getFunctionType(), arrowLoaded,
                                                     args,
                                                     util::format("call_{}",functionCall->getFunctionCallName()));
        }

        return builder.CreateCall(function, args, "call_" + functionName);
    }

    void LLVM::declareFunction(const std::shared_ptr<hlir::Function> &hlirFunction)
    {

        if (module->getFunction(hlirFunction->getFunctionName())) {
            return;
        }

        llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        std::vector<llvm::Type *> argTypes;
        std::vector<std::string> argNames;

        for (const auto &arg: hlirFunction->getFunctionArgs()->getArgs())
        {
            argTypes.push_back(mapType(arg->type->getType()));
            argNames.push_back(arg->name);
        }

        llvm::FunctionType *funcType;
        if (!argTypes.empty())
        {
            funcType = llvm::FunctionType::get(functionReturnType, argTypes, hlirFunction->isVariedArguments());
        }
        else
        {
            // Definir o tipo da função
            funcType = llvm::FunctionType::get(functionReturnType, llvm::ArrayRef<llvm::Type *>(), hlirFunction->isVariedArguments());
        }

        // Definir a linkage baseada na visibilidade
        constexpr llvm::Function::LinkageTypes linkage = llvm::Function::ExternalLinkage;

        // Criar a função no módulo
        llvm::Function *function =
                llvm::Function::Create(funcType, linkage, hlirFunction->getFunctionName(), module.get());

        // printf("Função declarada\n");
        // function->print(llvm::outs());
        //
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
}
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
                    util::format("LLVM::visitFunctionCall. Function {} not found", hlirFunction->getFunctionName()));
        }

        const llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvmContext, "entry", function);
        builder.SetInsertPoint(entry);

        visitStatement(hlirFunction->getStatement());
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

        builder.CreateRet(varValue);
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
            // Se for esperado que getCallArgs() nunca seja nulo, lance exceção
            throw LLVMException("visitFunctionCall: functionCall->getCallArgs() is null");
        }

        // Obter o nome da função a ser chamada
        const auto functionName = functionCall->getFunction()->getFunctionName();

        // Buscar a função no módulo LLVM
        llvm::Function *function = module->getFunction(functionName);
        if (!function)
        {
            throw LLVMException(util::format("LLVM::visitFunctionCall. Function {} not found", functionName));
        }

        // Vetor para armazenar os argumentos LLVM
        std::vector<llvm::Value *> args;
        // Iterar sobre os argumentos da chamada

        for (const auto &arg: functionCall->getCallArgs()->getCallArgs())
        {
            functionCall->getFunction()->getStatement()->findVarByName(arg->argument);

            if (auto var = functionCall->getFunction()->getStatement()->findVarByName(arg->argument))
            {
                throw LLVMException(util::format("LLVM::visitFunctionCall. Variable {} found", arg->argument));
            }

            auto value = createConstValue(arg->value->getValueType(), arg->value);

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
            builder.CreateCall(function, args);
            return nullptr;
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
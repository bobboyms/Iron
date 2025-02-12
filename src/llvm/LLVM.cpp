#include <utility>

#include "../headers/LLVMIR.h"

namespace iron
{
    LLVM::LLVM(const std::shared_ptr<hlir::Context> &hlirContext) :
        hlirContext(std::move(hlirContext)), builder(llvmContext)
    {
        module = std::make_unique<llvm::Module>("file_1", llvmContext);
        module->setTargetTriple("arm64-apple-macosx15.0.0");
    }

    LLVM::~LLVM() = default;

    void LLVM::visitFunction(const std::shared_ptr<hlir::Function> &hlirFunction)
    {

        if (hlirFunction->isExternal())
        {
            return;
        }

        if (!hlirFunction)
        {
            throw LLVMException("LLVM::visitFunction. VisitFunction called with null hlirFunction");
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

    void LLVM::visitStatement(const std::shared_ptr<hlir::Statement> &hlirStatement)
    {

        if (!hlirStatement)
        {
            throw LLVMException("LLVM::visitStatement. VisitStatement called with null hlirStatement");
        }

        for (auto statement: hlirStatement->getStatements())
        {
            std::visit(
                    [this](auto &&arg)
                    {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Assign>>)
                        {
                            this->visitAssignment(arg);
                        }
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Expr>>)
                        {
                            this->visitExpr(arg);
                        }
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::FunctionCall>>)
                        {
                            this->visitFunctionCall(arg);
                        }
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::FuncReturn>>)
                        {
                            this->visitFuncReturn(arg);
                        }
                    },
                    statement);
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

        // 9. Retorna o valor de "idade"
        builder.CreateRet(varValue);
    }

    void printFunctionInfo(const llvm::Function *function)
    {
        // 1) Obter o nome da função
        const std::string funcName = function->getName().str();

        // 2) Obter o tipo de retorno
        const llvm::Type *returnType = function->getReturnType();

        // 3) Converter o tipo de retorno em ‘string’ (opcional)
        // Uma maneira de imprimir o tipo é usando a própria API do LLVM:
        std::string typeStr;
        {
            llvm::raw_string_ostream rso(typeStr);
            returnType->print(rso); // imprime algo como "i32", "double", "void", etc.
        }

        // Exibir as informações
        llvm::outs() << "Function Name: " << funcName << "\n";
        llvm::outs() << "Return Type: " << typeStr << "\n";
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
            if (auto var = functionCall->getFunction()->getStatement()->findVarByName(arg->argument))
            {
                throw LLVMException(util::format("LLVM::visitFunctionCall. Variable {} found", arg->argument));
            }

            // auto val = tokenMap::getTokenText(arg->value->getValueType()->getType());

            // llvm::Constant *helloConst = ConstantDataArray::getString(Context, "Hello, world!\n", true);
            printf("Arg: %s\n", arg->argument.c_str());
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


        // Criar a chamada função diretamente
        if (function->getReturnType()->isVoidTy())
        {
            builder.CreateCall(function, args);
            return nullptr;
        }
        return builder.CreateCall(function, args, "call_" + functionName);
    }

    void LLVM::visitAssignment(const std::shared_ptr<hlir::Assign> &hlirAssignment)
    {
        if (!hlirAssignment)
        {
            throw LLVMException("visitAssignment called with null hlirAssignment");
        }
        if (!hlirAssignment->getValue())
        {
            throw LLVMException("visitAssignment: hlirAssignment->getValue() is null");
        }
        if (!hlirAssignment->getVariable())
        {
            throw LLVMException("visitAssignment: hlirAssignment->getVariable() is null");
        }

        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitAssignment: currentFunction is null");
        }

        const auto variable = hlirAssignment->getVariable();
        const auto value = hlirAssignment->getValue()->getValue();



        // auto value = hlirAssignment->getValue()->getValue();
        std::visit(
                [this, hlirAssignment, variable, currentFunction]([[maybe_unused]] auto &&arg)
                {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {
                    }
                    else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                    {
                        const auto alloca = allocaVariable(hlirAssignment->getVariable());
                        this->assignVariable(hlirAssignment->getValue(), alloca, currentFunction);
                    }
                    else if constexpr (std::is_same_v<T, std::string>)
                    {
                        llvm::AllocaInst * alloca;
                        if (variable->getVarType()->getType() == tokenMap::TYPE_STRING)
                        {
                            alloca = allocaVariableStr(hlirAssignment->getVariable(), arg);
                        } else
                        {
                            alloca = allocaVariable(hlirAssignment->getVariable());
                        }

                        this->assignValue(hlirAssignment->getVariable(), hlirAssignment->getValue(), alloca);
                        // this->assignValue(hlirAssignment->getVariable(), hlirAssignment->getValue(), alloca);
                    }
                },
                value);


    }

    void LLVM::visitExpr(const std::shared_ptr<hlir::Expr> &hlirExpr)
    {

        if (!hlirExpr)
        {
            throw LLVMException("visitExpr called with null hlirExpr");
        }

        if (!hlirExpr->getVariable())
        {
            throw LLVMException("visitExpr: hlirExpr->getVariable() is null");
        }

        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        if (!currentFunction)
        {
            throw LLVMException("visitExpr: currentFunction is null");
        }

        const auto div = std::dynamic_pointer_cast<hlir::Div>(hlirExpr->getExpr());
        const auto mult = std::dynamic_pointer_cast<hlir::Mult>(hlirExpr->getExpr());
        const auto minus = std::dynamic_pointer_cast<hlir::Minus>(hlirExpr->getExpr());
        const auto plus = std::dynamic_pointer_cast<hlir::Plus>(hlirExpr->getExpr());
        const auto cast = std::dynamic_pointer_cast<hlir::Cast>(hlirExpr->getExpr());
        const auto assign = std::dynamic_pointer_cast<hlir::Assign>(hlirExpr->getExpr());
        const auto funcCall = std::dynamic_pointer_cast<hlir::FunctionCall>(hlirExpr->getExpr());

        const auto variable = allocaVariable(hlirExpr->getVariable());
        if (!variable)
        {
            throw LLVMException("visitExpr: variable is null");
        }

        if (mult)
        {
            const auto result = executeMult(mult, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (div)
        {
            const auto result = executeDiv(div, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (plus)
        {
            const auto result = executePlus(plus, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (minus)
        {
            const auto result = executeMinus(minus, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (cast)
        {
            const auto result = numberCasting(cast->getVariable(), cast->getType(), currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (assign)
        {
            visitAssignment(assign);
        }
        else if (funcCall)
        {
            const auto value = visitFunctionCall(funcCall);
            builder.CreateStore(value, variable);
        }
    }

    void LLVM::declareFunction(const std::shared_ptr<hlir::Function> &hlirFunction)
    {
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
            funcType = llvm::FunctionType::get(functionReturnType, llvm::ArrayRef<llvm::Type *>(), false);
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

    std::string LLVM::generateCode()
    {
        for (const auto &function: hlirContext->getFunctions())
        {
            if (!function)
            {
                throw LLVMException("generateCode: function in hlirContext->getFunctions() is null");
            }

            declareFunction(function);
        }

        for (const auto &function: hlirContext->getFunctions())
        {
            visitFunction(function);
        }

        std::string errorStr;
        llvm::raw_string_ostream errorStream(errorStr);

        if (verifyModule(*module, &errorStream))
        {
            throw LLVMException(
                    util::format("{} {}", color::colorText(util::format("Invalid LLVM module:", ""), color::BOLD_RED),
                                 errorStream.str()));
        }

        std::string irStr;
        llvm::raw_string_ostream irStream(irStr);
        module->print(irStream, nullptr);
        return irStr;
    }
} // namespace iron

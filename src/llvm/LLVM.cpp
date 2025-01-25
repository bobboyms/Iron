#include "../headers/LLVMIR.h"

namespace iron
{

    LLVM::LLVM(std::shared_ptr<hlir::Context> hlirContext)
        : hlirContext(hlirContext), builder(llvmContext)
    {
        module = std::make_unique<llvm::Module>("file_1", llvmContext);
        module->setTargetTriple("arm64-apple-macosx15.0.0");
    }

    LLVM::~LLVM()
    {
    }

    void LLVM::visitFunction(std::shared_ptr<hlir::Function> hlirFunction)
    {

        if (!hlirFunction)
        {
            throw LLVMException("LLVM::visitFunction. VisitFunction called with null hlirFunction");
        }

        llvm::Function *function = module->getFunction(hlirFunction->getFunctionName());
        if (!function)
        {
            throw LLVMException(util::format("LLVM::visitFunctionCall. Function {} not found", hlirFunction->getFunctionName()));
        }

        llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvmContext, "entry", function);
        builder.SetInsertPoint(entry);

        visitStatement(hlirFunction->getStatement());

        generateTerminator(functionReturnType);
    }

    // assignment: anotherVarName = IDENTIFIER;

    void LLVM::visitStatement(std::shared_ptr<hlir::Statement> hlirStatement)
    {

        if (!hlirStatement)
        {
            throw LLVMException("LLVM::visitStatement. VisitStatement called with null hlirStatement");
        }

        for (auto statement : hlirStatement->getStatements())
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
                },
                statement);
        }
    }

    void printFunctionInfo(llvm::Function *function)
    {
        // 1) Obter o nome da função
        std::string funcName = function->getName().str();

        // 2) Obter o tipo de retorno
        llvm::Type *returnType = function->getReturnType();

        // 3) Converter o tipo de retorno em string (opcional)
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

    llvm::Value *LLVM::visitFunctionCall(std::shared_ptr<hlir::FunctionCall> functionCall)
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
        auto functionName = functionCall->getFunction()->getFunctionName();

        // Buscar a função no módulo LLVM
        llvm::Function *function = module->getFunction(functionName);
        if (!function)
        {
            throw LLVMException(util::format("LLVM::visitFunctionCall. Function {} not found", functionName));
        }

        // Vetor para armazenar os argumentos LLVM
        std::vector<llvm::Value *> args;

        // Iterar sobre os argumentos da chamada
        for (auto arg : functionCall->getCallArgs()->getCallArgs())
        {
            auto var = functionCall->getFunction()->getStatement()->findVarByName(arg->argument);
            if (var)
            {
                throw LLVMException(util::format("LLVM::visitFunctionCall. Variable {} found", arg->argument));
            }

            auto value = createConstValue(arg->value->getValueType(), arg->value);
            args.push_back(value);
        }

        // Verificar se o número de argumentos corresponde à assinatura da função
        if (function->arg_size() != args.size())
        {
            throw LLVMException(util::format("LLVM::visitFunctionCall. Argument count mismatch for function {}.", functionName));
        }

        // Criar a chamada de função diretamente
        if (function->getReturnType()->isVoidTy())
        {
            builder.CreateCall(function, args);
            return nullptr;
        }
        else
        {
            return builder.CreateCall(function, args, "call_" + functionName);
        }
    }

    void LLVM::visitAssignment(std::shared_ptr<hlir::Assign> hlirAssignment)
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

        auto alloca = allocaVariable(hlirAssignment->getVariable());
        auto value = hlirAssignment->getValue()->getValue();
        std::visit(
            [this, hlirAssignment, alloca, currentFunction](auto &&arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                {
                }
                else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                {
                    this->assignVariable(hlirAssignment->getValue(), alloca, currentFunction);
                }
                else if constexpr (std::is_same_v<T, std::string>)
                {
                    this->assignValue(hlirAssignment->getVariable(), hlirAssignment->getValue(), alloca);
                }
            },
            value);
    }

    void LLVM::visitExpr(std::shared_ptr<hlir::Expr> hlirExpr)
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

        auto div = std::dynamic_pointer_cast<hlir::Div>(hlirExpr->getExpr());
        auto mult = std::dynamic_pointer_cast<hlir::Mult>(hlirExpr->getExpr());
        auto minus = std::dynamic_pointer_cast<hlir::Minus>(hlirExpr->getExpr());
        auto plus = std::dynamic_pointer_cast<hlir::Plus>(hlirExpr->getExpr());
        auto cast = std::dynamic_pointer_cast<hlir::Cast>(hlirExpr->getExpr());
        auto assign = std::dynamic_pointer_cast<hlir::Assign>(hlirExpr->getExpr());
        auto funcCall = std::dynamic_pointer_cast<hlir::FunctionCall>(hlirExpr->getExpr());

        auto variable = allocaVariable(hlirExpr->getVariable());
        if (!variable)
        {
            throw LLVMException("visitExpr: variable is null");
        }

        if (mult)
        {
            auto result = executeMult(mult, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (div)
        {
            auto result = executeDiv(div, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (plus)
        {
            auto result = executePlus(plus, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (minus)
        {
            auto result = executeMinus(minus, currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (cast)
        {
            auto result = numberCasting(cast->getVariable(), cast->getType(), currentFunction);
            builder.CreateStore(result, variable);
        }
        else if (assign)
        {
            visitAssignment(assign);
        }
        else if (funcCall)
        {
            auto value = visitFunctionCall(funcCall);
            builder.CreateStore(value, variable);
        }
    }

    void LLVM::declareFunction(std::shared_ptr<hlir::Function> hlirFunction)
    {
        llvm::Type *functionReturnType = mapType(hlirFunction->getFunctionReturnType()->getType());
        std::vector<llvm::Type *> argTypes;
        std::vector<std::string> argNames;

        for (auto arg : hlirFunction->getFunctionArgs()->getArgs())
        {
            argTypes.push_back(mapType(arg->type->getType()));
            argNames.push_back(arg->name);
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

        // Criar a função no módulo
        llvm::Function *function = llvm::Function::Create(
            funcType,
            linkage,
            hlirFunction->getFunctionName(),
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
    }

    std::string LLVM::generateCode()
    {

        for (auto function : hlirContext->getFunctions())
        {
            if (!function)
            {

                throw LLVMException("generateCode: function in hlirContext->getFunctions() is null");
            }

            declareFunction(function);
        }

        for (auto function : hlirContext->getFunctions())
        {
            visitFunction(function);
        }

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
}

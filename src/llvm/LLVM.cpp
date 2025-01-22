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

        // Criar o bloco básico "entry" e definir o ponto de inserção
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvmContext, "entry", function);
        builder.SetInsertPoint(entry);

        visitStatement(hlirFunction->getStatement());

        generateTerminator(functionReturnType);
    }

    // assignment: anotherVarName = IDENTIFIER;

    void LLVM::visitStatement(std::shared_ptr<hlir::Statement> hlirStatement)
    {

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
                        // arg é um std::shared_ptr<FunctionCall>
                    }
                },
                statement);
        }
    }

    void LLVM::visitAssignment(std::shared_ptr<hlir::Assign> hlirAssignment)
    {
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();

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
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();

        auto div = std::dynamic_pointer_cast<hlir::Div>(hlirExpr->getExpr());
        auto mult = std::dynamic_pointer_cast<hlir::Mult>(hlirExpr->getExpr());
        auto minus = std::dynamic_pointer_cast<hlir::Minus>(hlirExpr->getExpr());
        auto plus = std::dynamic_pointer_cast<hlir::Plus>(hlirExpr->getExpr());
        auto cast = std::dynamic_pointer_cast<hlir::Cast>(hlirExpr->getExpr());
        auto assign = std::dynamic_pointer_cast<hlir::Assign>(hlirExpr->getExpr());

        auto variable = allocaVariable(hlirExpr->getVariable());

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
    }

    std::string LLVM::generateCode()
    {
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

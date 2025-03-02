#include <utility>

#include "../headers/LLVMIR.h"

namespace iron
{
    LLVM::LLVM(const std::shared_ptr<hlir::Context> &hlirContext, llvm::LLVMContext &context,
               const std::string &filename) :
        hlirContext(std::move(hlirContext)), llvmContext(context), builder(llvmContext), filename(filename)
    {
        module = std::make_unique<llvm::Module>(filename, llvmContext);
    }

    LLVM::~LLVM() = default;

    void LLVM::visitStatement(const std::shared_ptr<hlir::Statement> &statements)
    {

        if (!statements)
        {
            throw LLVMException("LLVM::visitStatement. VisitStatement called with null hlirStatement");
        }

        for (auto &statement: statements->getStatements())
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
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Conditional>>)
                        {
                            this->visitConditional(arg);
                        }
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Block>>)
                        {
                            this->visitBlock(arg);
                        }
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Jump>>)
                        {
                            this->visitJump(arg);
                        }
                        else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::FuncReturn>>)
                        {
                            this->visitFuncReturn(arg);
                        }
                    },
                    statement);
        }
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
                [this, &hlirAssignment, currentFunction]([[maybe_unused]] auto &&arg)
                {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {

                        llvm::AllocaInst *alloca =
                                findAllocaByName(currentFunction, hlirAssignment->getVariable()->getRealName());
                        if (!alloca)
                        {
                            alloca = allocaVariableFuncPtr(hlirAssignment->getVariable(), arg);
                        }

                        llvm::Function *calledFunction = module->getFunction(arg->getFunctionName());
                        builder.CreateStore(calledFunction, alloca);
                    }
                    else if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Variable>>)
                    {
                        llvm::AllocaInst *alloca =
                                findAllocaByName(currentFunction, hlirAssignment->getVariable()->getRealName());
                        if (!alloca)
                        {
                            alloca = allocaVariable(hlirAssignment->getVariable());
                        }

                        this->assignVariable(hlirAssignment->getValue(), alloca, currentFunction);
                    }
                    else if constexpr (std::is_same_v<T, std::string>)
                    {
                        llvm::AllocaInst *alloca =
                                findAllocaByName(currentFunction, hlirAssignment->getVariable()->getRealName());
                        if (hlirAssignment->getVariable()->getVarType()->getType() == tokenMap::TYPE_STRING)
                        {
                            if (!alloca)
                            {
                                alloca = allocaVariableStr(hlirAssignment->getVariable(), arg);
                            }
                        }
                        else
                        {
                            if (!alloca)
                            {
                                alloca = allocaVariable(hlirAssignment->getVariable());
                            }
                        }

                        this->assignValue(hlirAssignment->getVariable(), hlirAssignment->getValue(), alloca);
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
        const auto cmp = std::dynamic_pointer_cast<hlir::CMP>(hlirExpr->getExpr());
        const auto _and = std::dynamic_pointer_cast<hlir::AND>(hlirExpr->getExpr());
        const auto _or = std::dynamic_pointer_cast<hlir::OR>(hlirExpr->getExpr());
        const auto _not = std::dynamic_pointer_cast<hlir::_NOT>(hlirExpr->getExpr());

        const auto variable = allocaVariable(hlirExpr->getVariable());
        if (!variable)
        {
            throw LLVMException("visitExpr: variable is null");
        }

        if (cmp)
        {
            const auto result = executeCMP(cmp, currentFunction);
            builder.CreateStore(result, variable);
        }

        if (_and)
        {
            const auto result = executeAND(_and, currentFunction);
            builder.CreateStore(result, variable);
        }

        if (_or)
        {
            const auto result = executeOR(_or, currentFunction);
            builder.CreateStore(result, variable);
        }

        if (_not)
        {
            const auto result = executeNOT(_not, currentFunction);
            builder.CreateStore(result, variable);
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


    std::unique_ptr<llvm::Module> LLVM::generateCode()
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

        // std::string irStr;
        // llvm::raw_string_ostream irStream(irStr);
        // module->print(irStream, nullptr);

        return std::move(module);
    }
} // namespace iron

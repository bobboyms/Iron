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

    void LLVM::visitStruct(const std::shared_ptr<hlir::Struct> &struct_) const
    {
        if (!struct_)
        {
            throw LLVMException("LLVM::visitStruct. struct_ is null");
        }

        llvm::StructType *StructType =
                llvm::StructType::create(llvmContext, util::format("struct.{}", struct_->getName()));
        std::vector<llvm::Type *> structElements = {};
        for (const auto element: struct_->getVariables())
        {
            if (element->getVarType()->getType() == tokenMap::STRUCT)
            {
                const auto structName = element->getVarType()->getTypeName();
                const auto struct_ = getStructByName(structName);
                structElements.push_back(struct_);
            } else
            {
                llvm::Type *llvmType = mapType(element->getVarType()->getType());
                structElements.push_back(llvmType);
            }

        }

        StructType->setBody(structElements, /*isPacked=*/false);
    }

    /**
 * @brief Processes a list of statements and generates their LLVM IR
 *
 * This function traverses a list of statements and dispatches each to the 
 * appropriate handler based on its type.
 *
 * @param statements The statements to process
 * @throws LLVMException if statements is null
 */
void LLVM::visitStatement(const std::shared_ptr<hlir::Statement> &statements)
{
    llvm_utils::checkNotNull(statements, "statements", "visitStatement");

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
        std::visit(
                [this, &hlirAssignment, currentFunction]([[maybe_unused]] auto &&arg)
                {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Struct>>)
                    {
                        const auto structName = arg->getName();
                        const auto structType = getStructByName(structName);
                        const auto varName = hlirAssignment->getVariable()->getRealName();
                        builder.CreateAlloca(structType, nullptr, varName);
                    }
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::StructInit>>)
                    {
                        structInit(currentFunction, arg, hlirAssignment->getVariable());
                    }
                    if constexpr (std::is_same_v<T, std::shared_ptr<hlir::Function>>)
                    {
                        llvm::AllocaInst *alloca =
                                findAllocaByName(currentFunction, hlirAssignment->getVariable()->getRealName());
                        if (!alloca)
                        {
                            alloca = allocaVariableFuncPtr(hlirAssignment->getVariable(), arg);
                        }

                        if (!alloca)
                        {
                            throw LLVMException("visitAssignment: Failed to allocate variable for function pointer");
                        }

                        llvm::Function *calledFunction = module->getFunction(arg->getFunctionName());
                        if (!calledFunction)
                        {
                            throw LLVMException(util::format("visitAssignment: Function '{}' not found in module",
                                                             arg->getFunctionName()));
                        }

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
                                const auto varName = hlirAssignment->getVariable()->getRealName();
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
            if (!result)
            {
                throw LLVMException("visitExpr: executeCMP returned null");
            }
            builder.CreateStore(result, variable);
        }

        if (_and)
        {
            const auto result = executeAND(_and, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executeAND returned null");
            }
            builder.CreateStore(result, variable);
        }

        if (_or)
        {
            const auto result = executeOR(_or, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executeOR returned null");
            }
            builder.CreateStore(result, variable);
        }

        if (_not)
        {
            const auto result = executeNOT(_not, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executeNOT returned null");
            }
            builder.CreateStore(result, variable);
        }

        if (mult)
        {
            const auto result = executeMult(mult, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executeMult returned null");
            }
            builder.CreateStore(result, variable);
        }
        else if (div)
        {
            const auto result = executeDiv(div, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executeDiv returned null");
            }
            builder.CreateStore(result, variable);
        }
        else if (plus)
        {
            const auto result = executePlus(plus, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executePlus returned null");
            }
            builder.CreateStore(result, variable);
        }
        else if (minus)
        {
            const auto result = executeMinus(minus, currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: executeMinus returned null");
            }
            builder.CreateStore(result, variable);
        }
        else if (cast)
        {
            const auto result = numberCasting(cast->getVariable(), cast->getType(), currentFunction);
            if (!result)
            {
                throw LLVMException("visitExpr: numberCasting returned null");
            }
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

        for (const auto &struct_: hlirContext->getStructs())
        {
            visitStruct(struct_);
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


        // Para std::unique_ptr, o std::move é necessário para transferir propriedade
        return std::move(module);
    }
} // namespace iron

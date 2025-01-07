#include "headers/LLVMIR.h"
#include "headers/IronExceptions.h"
#include "headers/TokenMap.h"
#include "headers/Utils.h"

namespace iron {

    LLVMIR::LLVMIR(std::string code, std::unique_ptr<ScopeManager> scopeManager)
        : hlirCode(code), scopeManager(std::move(scopeManager)), builder(context) {
            module = std::make_unique<llvm::Module>("file_1", context);
            module->setTargetTriple("arm64-apple-macosx15.0.0");
        }

    LLVMIR::~LLVMIR() {}

    std::string LLVMIR::generateCode() 
    {
        if (hlirCode.empty()) {
            throw std::runtime_error("Code is not properly initialized.");
        }

        std::cout << hlirCode << std::endl;

        antlr4::ANTLRInputStream inputStream(hlirCode);
        HightLavelIRLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<HightLavelIRParser>(&tokens);
        scopeManager->enterScope(TokenMap::getTokenText(TokenMap::GLOBAL));

        HightLavelIRParser::ProgramContext* programContext = parser->program();
        
        for (auto child : programContext->children) {
            if (auto funcDecl = dynamic_cast<HightLavelIRParser::FunctionDeclarationContext*>(child)) {
                visitFunctionDeclaration(funcDecl);
            }
        }

        scopeManager->exitScope(TokenMap::getTokenText(TokenMap::GLOBAL));
        // Verifica a validade do módulo e captura mensagens de erro
        std::string errorStr;
        llvm::raw_string_ostream errorStream(errorStr);

        if (llvm::verifyModule(*module, &errorStream)) {
            throw LLVMException(iron::format("{} {}", color::colorText(
                iron::format("Invalid LLVM module:",""),color::BOLD_RED),
                errorStream.str()));
        }


        // Captura o LLVM IR em uma string
        std::string irStr;
        llvm::raw_string_ostream irStream(irStr);
        module->print(irStream, nullptr);
        return irStr;
    }

    llvm::Type* LLVMIR::mapType(const int type) {
            if (type == TokenMap::TYPE_INT) {
                return llvm::Type::getInt32Ty(context);
            } else if (type == TokenMap::TYPE_FLOAT) {
                return llvm::Type::getFloatTy(context);
            } else if (type == TokenMap::TYPE_DOUBLE) {
                return llvm::Type::getDoubleTy(context);
            } else if (type == TokenMap::TYPE_CHAR) {
                return llvm::Type::getInt8Ty(context);
            } else if (type == TokenMap::TYPE_BOOLEAN) {
                return llvm::Type::getInt1Ty(context);
            } else if (type == TokenMap::VOID) {
                return llvm::Type::getVoidTy(context);
            }
            // Adicione outros tipos conforme necessário
            throw LLVMException(format("Unknown data type: {}",type));

    }


    void LLVMIR::visitStatementList(HightLavelIRParser::StatementListContext* ctx) {
        int i = 0;
        for (auto exp : ctx->expr()) {
            visitExpr(exp);
            
        }
    }

    void LLVMIR::visitExpr(HightLavelIRParser::ExprContext* ctx) {
        const std::string varName = ctx->varName->getText();
        const auto varType = TokenMap::getTokenType(ctx->varTypes()->getText());
        auto currentScope = scopeManager->currentScope();

        llvm::Value* valueToStore = nullptr; // Value to be stored in the variable
        llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock &entryBlock = currentFunction->getEntryBlock();
        llvm::IRBuilder<> tmpBuilder(&entryBlock, entryBlock.begin());

        llvm::Type* type = mapType(varType);
        llvm::AllocaInst* allocaVariable = tmpBuilder.CreateAlloca(type, nullptr, varName);
        currentScope->addSymbol(varName, {TokenMap::VARIABLE, varType, nullptr, {}, "", allocaVariable});

        if (ctx->number()) {

            // **Step 2: Create the constant value**
            const std::string literalValue = ctx->number()->getText();
            switch (varType) {
                case TokenMap::TYPE_INT: {
                    // Convert string to int
                    int num = std::stoi(literalValue);

                    // Create a 32-bit integer constant
                    llvm::Constant* constInt = llvm::ConstantInt::get(
                        llvm::Type::getInt32Ty(context),
                        num,
                        true // Signed
                    );
                    valueToStore = constInt;
                    break;
                }

                case TokenMap::TYPE_FLOAT: {
                    // Convert string to float
                    float num = std::stof(literalValue);
                    llvm::APFloat apFloatValue(num);
                    llvm::Constant* constFP = llvm::ConstantFP::get(context, apFloatValue);
                    valueToStore = constFP;
                    break;
                }

                case TokenMap::TYPE_DOUBLE: {
                    // Convert string to double
                    double num = std::stod(literalValue);
                    llvm::APFloat apFloatValue(num);
                    llvm::Constant* constFP = llvm::ConstantFP::get(context, apFloatValue);
                    valueToStore = constFP;
                    break;
                }

                default: {
                    throw LLVMException("Unsupported type for number literal: " + literalValue);
                }
            }

            // **Step 3: Store the constant in the allocated variable**
            if (valueToStore) {
                builder.CreateStore(valueToStore, allocaVariable);
                
            }

        } else
        if (ctx->math_op()) {
                auto left = ctx->math_op()->opLeft();
                auto right = ctx->math_op()->opRight();

                std::string leftVarName = left->op()->varName->getText();
                std::string rightVarName = right->op()->varName->getText();


                auto leftSymbolInfo = scopeManager->currentScope()->lookup(leftVarName);
                if (!leftSymbolInfo.has_value()) {
                    throw LLVMException("Left variable not found");
                }

                auto rightSymbolInfo = scopeManager->currentScope()->lookup(rightVarName);
                if (!rightSymbolInfo.has_value()) {
                    throw LLVMException("Right variable not found");
                }

                llvm::Value *leftValue = builder.CreateLoad(type, leftSymbolInfo->alloca, iron::format("load_{}", leftVarName));
                llvm::Value *rigthValue = builder.CreateLoad(type, rightSymbolInfo->alloca, iron::format("load_{}", rightVarName));    

            if (ctx->math_op()->PLUS()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFAdd(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateAdd(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
                
                
            }

        } else
        if (ctx->assignment()) {
            
            std::string anotherVarName = ctx->assignment()->anotherVarName->getText();
            auto anotherVarNameOpt = scopeManager->currentScope()->lookup(anotherVarName);

            if (!anotherVarNameOpt.has_value()) {
                throw LLVMException(iron::format("Variable: {} not found", anotherVarName));
            }

            auto varNameOpt = scopeManager->currentScope()->lookup(varName);

            if (!varNameOpt.has_value()) {
                throw LLVMException(iron::format("Variable: {} not found", varName));
            }

            // Carregar o valor da variável fonte
            llvm::Value* loadedValue = builder.CreateLoad(type, anotherVarNameOpt->alloca, iron::format("load_{}", anotherVarName));
            
            // Armazenar o valor carregado na variável de destino
            builder.CreateStore(loadedValue, varNameOpt->alloca);
        } else
        if (ctx->cast()) {
            std::string anotherVarName = ctx->cast()->anotherVarName->getText();
            auto anotherVarNameOpt = scopeManager->currentScope()->lookup(anotherVarName);
            
            if (!anotherVarNameOpt.has_value()) {
                throw LLVMException(iron::format("Variable: {} not found", anotherVarName));
            }

            const auto typeLeft = TokenMap::getTokenType(ctx->cast()->typeLeft()->varTypes()->getText());
            const auto typeRight = TokenMap::getTokenType(ctx->cast()->typeRight()->varTypes()->getText());
            
            llvm::Type *desiredType = mapType(typeRight);
            llvm::Type *currentType = mapType(typeLeft);

            llvm::Value *loadedVar = builder.CreateLoad(currentType, anotherVarNameOpt->alloca, iron::format("load_",anotherVarName));
            // Definir o tipo inteiro desejado (e.g., i32)

            //converte float para int
            llvm::Value *value;
            if (typeLeft == TokenMap::TYPE_FLOAT && typeRight == TokenMap::TYPE_INT) {
                value = builder.CreateFPToSI(loadedVar, desiredType, iron::format("cast_",anotherVarName));
            } else
            if (typeLeft == TokenMap::TYPE_INT && typeRight == TokenMap::TYPE_FLOAT) {
                value = builder.CreateSIToFP(loadedVar, desiredType, iron::format("cast_",anotherVarName));
            } else {
                throw LLVMException("Type conversion not defined.");
            }

            builder.CreateStore(value, allocaVariable);

        }
        else {
            throw LLVMException("Unsupported expression in visitExpr.");
        }
    }



    void LLVMIR::visitCast(HightLavelIRParser::CastContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitOp(HightLavelIRParser::OpContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitMathOp(HightLavelIRParser::Math_opContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionReturnType(HightLavelIRParser::FunctionReturnTypeContext* ctx, llvm::Type*& functionReturnType) {
        if (ctx->VOID()) {
            functionReturnType = mapType(TokenMap::VOID);
        } else {
            functionReturnType = mapType(TokenMap::getTokenType(ctx->varTypes()->getText()));
        }
    }

    void LLVMIR::visitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext* ctx) {
        std::string functionName = ctx->functionName->getText();
        auto returnType = ctx->functionSignature()->functionReturnType();

        scopeManager->enterScope(functionName);
         // Mapear o tipo de retorno
        llvm::Type* functionReturnType = nullptr;
        std::vector<llvm::Type*> argTypes;
        std::vector<std::string> argNames;

        if (ctx->functionSignature()) {
            visitFunctionSignature(ctx->functionSignature(), functionReturnType, argTypes, argNames);
        }
        
        if (!functionReturnType) {
            throw LLVMException("Function return type is not defined.");
        }

        
        llvm::FunctionType *funcType;
        if (argTypes.size() > 0) {
            // Definir o tipo da função
            funcType = llvm::FunctionType::get(
            functionReturnType,
            argTypes,
            false);
        } else {
            // Definir o tipo da função
            funcType = llvm::FunctionType::get(
            functionReturnType,
            llvm::ArrayRef<llvm::Type*>(),
            false);
        }

        
   
        // Definir a linkage baseada na visibilidade
        llvm::Function::LinkageTypes linkage = llvm::Function::ExternalLinkage; // Padrão

        //if (ctx->PRIVATE()) {
        //    linkage = llvm::Function::PrivateLinkage;
        //}

        

        // Criar a função no módulo
        llvm::Function *function = llvm::Function::Create(
            funcType,
            linkage,
            functionName,
            module.get()
        );

        if (argTypes.size() > 0) {
            unsigned idx = 0;
            for (auto &arg : function->args()) {
                if (idx < argNames.size()) {
                    std::string argName = argNames[idx++];
                    arg.setName(argName);
                }
            }
        }

        // Criar o bloco básico "entry" e definir o ponto de inserção
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", function);
        builder.SetInsertPoint(entry);
        
        

        if (ctx->statementList()) {
            visitStatementList(ctx->statementList());
        }

        

        // **Passo Adicional: Adicionar uma instrução terminadora**
        if (functionReturnType->isVoidTy()) {
            builder.CreateRetVoid();
        } else {
            // Se a função deve retornar um valor, certifique-se de que todas as vias de execução retornem um valor
            // Caso contrário, lance uma exceção ou adicione um valor de retorno padrão
            throw LLVMException("Non-void function without a return statement.");
        }

        scopeManager->exitScope(functionName);

        
    }

    void LLVMIR::visitFunctionSignature(
    HightLavelIRParser::FunctionSignatureContext* ctx,
        llvm::Type*& functionReturnType,
        std::vector<llvm::Type*>& argTypes,
        std::vector<std::string>& argNames
    ) {
        if (ctx->functionReturnType()) {
            visitFunctionReturnType(ctx->functionReturnType(), functionReturnType);
        }

        if (ctx->functionArgs()) {
            visitFunctionArgs(ctx->functionArgs(), argTypes, argNames);
        }
    }

    void LLVMIR::visitFunctionArgs(
        HightLavelIRParser::FunctionArgsContext* ctx,
        std::vector<llvm::Type*>& argTypes,
        std::vector<std::string>& argNames
    ) {
        for (auto arg : ctx->functionArg()) {
            visitFunctionArg(arg, argTypes, argNames);
        }
    }

    void LLVMIR::visitFunctionArg(
        HightLavelIRParser::FunctionArgContext* ctx,
        std::vector<llvm::Type*>& argTypes,
        std::vector<std::string>& argNames
    ) {
        std::string argTypeStr = ctx->varTypes()->getText();
        std::string argName = ctx->varName->getText();
        // Mapear o tipo para LLVM
        argTypes.push_back(mapType(TokenMap::getTokenType(argTypeStr)));
        argNames.push_back(argName);
    }

    void LLVMIR::visitFunctionCall(HightLavelIRParser::FunctionCallContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext* ctx) {
        // Implementação do método
    }

    void LLVMIR::visitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext* ctx) {
        // Implementação do método
    }
}

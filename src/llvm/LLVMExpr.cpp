#include "../headers/LLVMIR.h"
#include "../headers/IronExceptions.h"
#include "../headers/TokenMap.h"
#include "../headers/Utils.h"

namespace iron {

    // faz conversão de valores de variaveis
    void LLVMIR::numberCasting(HightLavelIRParser::ExprContext* ctx, llvm::AllocaInst* allocaVariable) {
        std::string anotherVarName = ctx->cast()->anotherVarName->getText();
        auto anotherVarNameOpt = scopeManager->currentScope()->lookup(anotherVarName);

        if (!anotherVarNameOpt.has_value()) {
            throw LLVMException(iron::format("Variable: {} not found", anotherVarName));
        }

        const auto typeLeft = TokenMap::getTokenType(ctx->cast()->typeLeft()->varTypes()->getText());
        const auto typeRight = TokenMap::getTokenType(ctx->cast()->typeRight()->varTypes()->getText());

        llvm::Type *desiredType = mapType(typeRight);
        llvm::Type *currentType = mapType(typeLeft);

        llvm::Value *loadedVar = builder.CreateLoad(
            currentType, 
            anotherVarNameOpt->alloca, 
            iron::format("load_{}", anotherVarName)
        );

        llvm::Value *value;

        // Converter float
        if (typeLeft == TokenMap::TYPE_FLOAT && typeRight == TokenMap::TYPE_INT) {
            value = builder.CreateFPToSI(loadedVar, desiredType, iron::format("cast_{}", anotherVarName));
        } else if (typeLeft == TokenMap::TYPE_FLOAT && typeRight == TokenMap::TYPE_DOUBLE) {
            value = builder.CreateFPExt(loadedVar, desiredType, iron::format("cast_{}", anotherVarName));
        }
        // Converter int
        else if (typeLeft == TokenMap::TYPE_INT && typeRight == TokenMap::TYPE_FLOAT) {
            value = builder.CreateSIToFP(loadedVar, desiredType, iron::format("cast_{}", anotherVarName));
        } else if (typeLeft == TokenMap::TYPE_INT && typeRight == TokenMap::TYPE_DOUBLE) {
            value = builder.CreateSIToFP(loadedVar, desiredType, iron::format("cast_{}", anotherVarName));
        }
        // Converter double
        else if (typeLeft == TokenMap::TYPE_DOUBLE && typeRight == TokenMap::TYPE_FLOAT) {
            value = builder.CreateFPTrunc(loadedVar, desiredType, iron::format("cast_{}", anotherVarName));
        } else if (typeLeft == TokenMap::TYPE_DOUBLE && typeRight == TokenMap::TYPE_INT) {
            value = builder.CreateFPToSI(loadedVar, desiredType, iron::format("cast_{}", anotherVarName));
        }
        // Caso não definido
        else {
            throw LLVMException("Type conversion not defined.");
        }

        builder.CreateStore(value, allocaVariable);
    }

    // transformar uma literal Exemplo: "20" para um número 20
    void LLVMIR::literalToRealNumber(int varType, std::string literalValue, llvm::AllocaInst* allocaVariable) {
        llvm::Value* valueToStore = nullptr; 

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
                throw LLVMException(iron::format("Unsupported type for number literal: {}", literalValue));
            }
        }

        builder.CreateStore(valueToStore, allocaVariable);
    }

    
    // Cria operações matemáticas
    void LLVMIR::mathematicalOperations(HightLavelIRParser::ExprContext* ctx, llvm::AllocaInst* allocaVariable, int varType, std::string varName, llvm::Type* llvmType) {
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

                llvm::Value *leftValue = builder.CreateLoad(llvmType, leftSymbolInfo->alloca, iron::format("load_{}", leftVarName));
                llvm::Value *rigthValue = builder.CreateLoad(llvmType, rightSymbolInfo->alloca, iron::format("load_{}", rightVarName));    

            if (ctx->math_op()->PLUS()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFAdd(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateAdd(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
                
            }

            if (ctx->math_op()->MINUS()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFSub(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateSub(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
            }

            if (ctx->math_op()->MINUS()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFSub(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateSub(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
            }

            if (ctx->math_op()->MULT()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFMul(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateMul(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
            }

            if (ctx->math_op()->MULT()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFMul(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateMul(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
            }

            if (ctx->math_op()->DIV()) {
                if (varType == TokenMap::TYPE_FLOAT || varType == TokenMap::TYPE_DOUBLE) {
                    llvm::Value *result = builder.CreateFDiv(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                } else {
                    llvm::Value *result = builder.CreateSDiv(leftValue, rigthValue, iron::format("tmp_{}", varName));
                    builder.CreateStore(result, allocaVariable);
                }
            }
    }

    //Cria atribuições
    void LLVMIR::assignment(HightLavelIRParser::ExprContext* ctx, std::string varName, llvm::Type* llvmType) {
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
            llvm::Value* loadedValue = builder.CreateLoad(llvmType, anotherVarNameOpt->alloca, iron::format("load_{}", anotherVarName));
            
            // Armazenar o valor carregado na variável de destino
            builder.CreateStore(loadedValue, varNameOpt->alloca);

    }

}
 
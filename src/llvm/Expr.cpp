#include "../headers/LLVMIR.h"

namespace iron
{

    // faz conversão de valores de variaveis
    void LLVMIR::numberCasting(HightLavelIRParser::ExprContext *ctx, llvm::AllocaInst *allocaVariable)
    {
        std::string anotherVarName = ctx->cast()->anotherVarName->getText();
        auto anotherVarNameOpt = scopeManager->currentScope()->lookup(anotherVarName);

        if (!anotherVarNameOpt.has_value())
        {
            throw LLVMException(util::format("Variable: {} not found", anotherVarName));
        }

        const auto typeLeft = tokenMap::getTokenType(ctx->cast()->typeLeft()->varTypes()->getText());
        const auto typeRight = tokenMap::getTokenType(ctx->cast()->typeRight()->varTypes()->getText());

        llvm::Type *desiredType = mapType(typeRight);
        llvm::Type *currentType = mapType(typeLeft);

        llvm::Value *loadedVar = builder.CreateLoad(
            currentType,
            anotherVarNameOpt->alloca,
            util::format("load_{}", anotherVarName));

        llvm::Value *value;

        // Converter float
        if (typeLeft == tokenMap::TYPE_FLOAT && typeRight == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", anotherVarName));
        }
        else if (typeLeft == tokenMap::TYPE_FLOAT && typeRight == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateFPExt(loadedVar, desiredType, util::format("cast_{}", anotherVarName));
        }
        // Converter int
        else if (typeLeft == tokenMap::TYPE_INT && typeRight == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", anotherVarName));
        }
        else if (typeLeft == tokenMap::TYPE_INT && typeRight == tokenMap::TYPE_DOUBLE)
        {
            value = builder.CreateSIToFP(loadedVar, desiredType, util::format("cast_{}", anotherVarName));
        }
        // Converter double
        else if (typeLeft == tokenMap::TYPE_DOUBLE && typeRight == tokenMap::TYPE_FLOAT)
        {
            value = builder.CreateFPTrunc(loadedVar, desiredType, util::format("cast_{}", anotherVarName));
        }
        else if (typeLeft == tokenMap::TYPE_DOUBLE && typeRight == tokenMap::TYPE_INT)
        {
            value = builder.CreateFPToSI(loadedVar, desiredType, util::format("cast_{}", anotherVarName));
        }
        // Caso não definido
        else
        {
            throw LLVMException("Type conversion not defined.");
        }

        builder.CreateStore(value, allocaVariable);
    }

    // transformar uma literal Exemplo: "20" para um número 20
    void LLVMIR::literalToRealNumber(int varType, std::string literalValue, llvm::AllocaInst *allocaVariable)
    {
        llvm::Value *valueToStore = nullptr;

        switch (varType)
        {
        case tokenMap::TYPE_INT:
        {
            // Convert string to int
            int num = std::stoi(literalValue);

            // Create a 32-bit integer constant
            llvm::Constant *constInt = llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(context),
                num,
                true // Signed
            );
            valueToStore = constInt;
            break;
        }

        case tokenMap::TYPE_FLOAT:
        {
            // Convert string to float
            float num = std::stof(literalValue);
            llvm::APFloat apFloatValue(num);
            llvm::Constant *constFP = llvm::ConstantFP::get(context, apFloatValue);
            valueToStore = constFP;
            break;
        }

        case tokenMap::TYPE_DOUBLE:
        {
            // Convert string to double
            double num = std::stod(literalValue);
            llvm::APFloat apFloatValue(num);
            llvm::Constant *constFP = llvm::ConstantFP::get(context, apFloatValue);
            valueToStore = constFP;
            break;
        }

        default:
        {
            throw iron::LLVMException(util::format("Unsupported type for number literal: {}", literalValue));
        }
        }

        builder.CreateStore(valueToStore, allocaVariable);
    }

    // Cria operações matemáticas
    void LLVMIR::mathematicalOperations(HightLavelIRParser::ExprContext *ctx,
                                        llvm::AllocaInst *allocaVariable,
                                        int varType,
                                        std::string varName,
                                        llvm::Type *llvmType)
    {
        auto left = ctx->mathOp()->opLeft();
        auto right = ctx->mathOp()->opRight();

        std::string leftVarName = left->op()->varName->getText();
        std::string rightVarName = right->op()->varName->getText();
        std::string currentFunctionName = scopeManager->currentScopeName();

        // 1. Verifica se a variável 'leftVarName' está no escopo atual.
        //    Se não estiver, verifica se é um argumento da função atual.
        auto leftSymbolInfo = scopeManager->currentScope()->lookup(leftVarName);
        llvm::Value *leftValue = nullptr;

        if (!leftSymbolInfo.has_value())
        {
            // Tenta buscar a função pelo nome atual do escopo
            llvm::Function *currentFunction = module->getFunction(currentFunctionName);
            if (!currentFunction)
            {
                throw LLVMException(
                    util::format("Function {} not found", currentFunctionName));
            }

            // Verifica se existe um argumento da função com esse nome
            llvm::Argument *argLeft = getArgumentByName(currentFunction, leftVarName);
            if (!argLeft)
            {
                // Nem variável local nem argumento de função -> erro
                throw LLVMException(
                    util::format("Variable or argument '{}' not found in function '{}'",
                                 leftVarName, currentFunctionName));
            }
            // Se for argumento, usamos diretamente o argLeft como 'leftValue'
            leftValue = argLeft;
        }
        else
        {
            // Se encontrou a variável no escopo, carregamos a partir do alloca
            leftValue = builder.CreateLoad(
                llvmType,
                leftSymbolInfo->alloca,
                util::format("load_{}", leftVarName));
        }

        // 2. Verifica se a variável 'rightVarName' está no escopo atual.
        //    Se não estiver, verifica se é um argumento da função atual.
        auto rightSymbolInfo = scopeManager->currentScope()->lookup(rightVarName);
        llvm::Value *rightValue = nullptr;

        if (!rightSymbolInfo.has_value())
        {
            // Tenta buscar a função pelo nome atual do escopo
            llvm::Function *currentFunction = module->getFunction(currentFunctionName);
            if (!currentFunction)
            {
                throw LLVMException(
                    util::format("Function {} not found", currentFunctionName));
            }

            // Verifica se existe um argumento da função com esse nome
            llvm::Argument *argRight = getArgumentByName(currentFunction, rightVarName);
            if (!argRight)
            {
                // Nem variável local nem argumento de função -> erro
                throw LLVMException(
                    util::format("Variable or argument '{}' not found in function '{}'",
                                 rightVarName, currentFunctionName));
            }
            // Se for argumento, usamos diretamente o argRight como 'rightValue'
            rightValue = argRight;
        }
        else
        {
            // Se encontrou a variável no escopo, carregamos a partir do alloca
            rightValue = builder.CreateLoad(
                llvmType,
                rightSymbolInfo->alloca,
                util::format("load_{}", rightVarName));
        }

        // 3. A partir daqui, leftValue e rightValue estão resolvidos (variável local ou argumento).
        //    Realiza as operações matemáticas de acordo com o token de operação.

        // Soma (PLUS)
        if (ctx->mathOp()->PLUS())
        {
            if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
            {
                llvm::Value *result = builder.CreateFAdd(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
            else
            {
                llvm::Value *result = builder.CreateAdd(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
        }

        // Subtração (MINUS)
        if (ctx->mathOp()->MINUS())
        {
            if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
            {
                llvm::Value *result = builder.CreateFSub(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
            else
            {
                llvm::Value *result = builder.CreateSub(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
        }

        // Multiplicação (MULT)
        if (ctx->mathOp()->MULT())
        {
            if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
            {
                llvm::Value *result = builder.CreateFMul(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
            else
            {
                llvm::Value *result = builder.CreateMul(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
        }

        // Divisão (DIV)
        if (ctx->mathOp()->DIV())
        {
            if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
            {
                llvm::Value *result = builder.CreateFDiv(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
            else
            {
                llvm::Value *result = builder.CreateSDiv(
                    leftValue, rightValue, util::format("tmp_{}", varName));
                builder.CreateStore(result, allocaVariable);
            }
        }
    }

    // Cria atribuições
    void LLVMIR::assignment(HightLavelIRParser::ExprContext *ctx, std::string varName, llvm::Type *llvmType)
    {
        std::string anotherVarName = ctx->assignment()->anotherVarName->getText();
        auto anotherVarNameOpt = scopeManager->currentScope()->lookup(anotherVarName);

        if (!anotherVarNameOpt.has_value())
        {
            throw LLVMException(util::format("Variable: {} not found", anotherVarName));
        }

        auto varNameOpt = scopeManager->currentScope()->lookup(varName);

        if (!varNameOpt.has_value())
        {
            throw LLVMException(util::format("Variable: {} not found", varName));
        }

        // Carregar o valor da variável fonte
        llvm::Value *loadedValue = builder.CreateLoad(llvmType, anotherVarNameOpt->alloca, util::format("load_{}", anotherVarName));

        // Armazenar o valor carregado na variável de destino
        builder.CreateStore(loadedValue, varNameOpt->alloca);
    }

}

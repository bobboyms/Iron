#include <iostream>
#include <memory>
#include "headers/Hlir.h"

std::string removeWhitespace(const std::string &str)
{
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](unsigned char c)
                 { return !std::isspace(c); });
    return result;
}

int main()
{
    auto stmt = std::make_shared<hlir::Statement>();

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat, stmt);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>(varRes, functionCall);

    // Adicionar declarações ao Statement
    stmt->addStatement(expr1);

    stmt->addStatement(functionCall);

    stmt->addStatement(expr2);

    // Verificar a saída de getText()
    std::cout << func->getText() << std::endl;
}

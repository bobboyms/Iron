#include <iostream>
#include <memory>
#include "headers/Hlir.h"

int main()
{
    // Cria o tipo string
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Cria a variável 'name:string'
    auto varName = std::make_shared<hlir::Variable>("name", typeString);

    // Cria a expressão válida como Variable
    hlir::ValidExpr exprVariant = varName;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varName, exprVariant);

    std::cout << expr->getText() << std::endl;
    // Verifica o texto gerado
    // runAnalysis(, "let name:string = name");
}

#include <iostream>
#include <memory>
#include "hlir/Hlir.h"

int main()
{

    auto varTypeBool = std::make_shared<hlir::Type>(hlir::TYPE_BOOLEAN);
    auto variable = std::make_shared<hlir::Variable>("flag", varTypeBool);

    auto val = std::make_shared<hlir::Value>("false", varTypeBool);

    hlir::Assign assign(variable, val);

    // Checa se várias chamadas a getText retornam o mesmo valor
    std::string first = assign.getText();
    std::string second = assign.getText();

    // Esperado: "let flag:boolean = true"
    std::cout << first << "\n";

    return 0;
}

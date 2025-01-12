#include <iostream>
#include <memory>
#include "hlir/Hlir.h"

int main()
{
    // Return type double
    auto typeDouble = std::make_shared<hlir::Type>(hlir::TYPE_DOUBLE);
    // Args (n:int)
    auto argN = std::make_shared<hlir::Arg>("n", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argN});
    auto func = std::make_shared<hlir::Function>("sqrtCalc", funcArgs, typeDouble);

    // CallArg "n:25"
    auto val25 = std::make_shared<hlir::Value>("25", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto callArgN = std::make_shared<hlir::FunctionCallArg>("n", std::make_shared<hlir::Type>(hlir::TYPE_INT), val25);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgN});

    // "call double sqrtCalc(n:25)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Check repeated calls
    std::string first = functionCall->getText();
    std::string second = functionCall->getText();

    std::cout << first << std::endl;
    std::cout << second << std::endl;

    return 0;
}

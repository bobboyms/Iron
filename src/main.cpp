#include <iostream>
#include <memory>
#include "headers/Hlir.h"

int main()
{

    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    std::cout << "1" << std::endl;

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", funcArgs, typeInt);

    std::cout << "2" << std::endl;

    // Cria o FunctionPtr para a função 'foo'
    auto funcPtrert = std::make_shared<hlir::FunctionPtr>();
    funcPtrert->set(func);

    std::cout << "3" << std::endl;

    // Esperamos que getText() retorne "fptr foo"

    std::cout << funcPtrert->getText() << std::endl;
}

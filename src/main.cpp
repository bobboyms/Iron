#include <iostream>
#include <memory>
#include "headers/Hlir.h"

#include <iostream>
#include <string>
#include <cctype>

// Função que remove todos os caracteres de espaço em branco
std::string removeWhitespace(const std::string &str)
{
    std::string result;
    for (char c : str)
    {
        // Verifica se o caractere não é um espaço em branco (incluindo \n, \t, etc.)
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            result += c;
        }
    }
    return result;
}

int main()
{
    // Exemplos de strings grandes (corrigidas para que sejam iguais ao remover espaços)
    std::string largeString1 = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";
    std::string largeString2 = "\n let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    // Comparação ignorando todos os espaços e quebras de linha
    if (removeWhitespace(largeString1) == removeWhitespace(largeString2))
    {
        std::cout << "As strings são iguais." << std::endl;
    }
    else
    {
        std::cout << "As strings são diferentes." << std::endl;
    }

    return 0;
}

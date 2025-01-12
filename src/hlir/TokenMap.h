#ifndef TOKEN_MAP_HLIR_H
#define TOKEN_MAP_HLIR_H

#include "../headers/Colors.h"
#include "Exceptions.h"
#include <string>
#include <unordered_map>
#include <regex>

namespace hlir
{

    const auto MAIN_TYPE = "MAIN_TYPE_EXPR";

    enum Token
    {
        GLOBAL,
        COLON,
        EQ,
        SEMICOLON,
        DOT,
        STAR,
        L_CURLY,
        R_CURLY,
        L_PAREN,
        R_PAREN,
        PLUS,
        MINUS,
        DIV,
        L_BRACKET,
        R_BRACKET,
        ARROW, // Tokens especiais, como "->"

        // Palavras reservadas
        FUNCTION,

        LET,
        PUBLIC,
        IMPORT,
        RETURN,

        // Tipos de dados
        TYPE_INT,
        TYPE_CHAR,
        TYPE_FLOAT,
        TYPE_STRING,
        TYPE_BOOLEAN,
        TYPE_DOUBLE,

        // tipos de controle
        PTR,
        FUNCTION_PTR,
        VARIABLE,
        VOID,
        NUMBER,
        NO_REAL_NUMBER,
        REAL_NUMBER,
        PRIVATE,
        ARGUMENT,
    };

    inline const std::unordered_map<int, std::string> tokenText = {
        {COLON, ":"},
        {EQ, "="},
        {SEMICOLON, ";"},
        {DOT, "."},
        {STAR, "*"},
        {L_CURLY, "{"},
        {R_CURLY, "}"},
        {L_PAREN, "("},
        {R_PAREN, ")"},
        {PLUS, "+"},
        {MINUS, "-"},
        {DIV, "/"},
        {L_BRACKET, "["},
        {R_BRACKET, "]"},
        {ARROW, "->"},

        {FUNCTION, "fn"},
        {LET, "let"},
        {PUBLIC, "public"},
        {IMPORT, "import"},
        {RETURN, "return"},

        // Tipos de dados
        {TYPE_INT, "int"},
        {TYPE_CHAR, "char"},
        {TYPE_FLOAT, "float"},
        {TYPE_STRING, "string"},
        {TYPE_BOOLEAN, "boolean"},
        {TYPE_DOUBLE, "double"},

        // tipos de controle
        {GLOBAL, "global"},
        {VARIABLE, "variable"},
        {VOID, "void"},
        {NUMBER, "number"},
        {NO_REAL_NUMBER, "not_is_a_real_number"},
        {REAL_NUMBER, "real_number"},
        {PRIVATE, "private"},
        {ARGUMENT, "arg"},
        {FUNCTION_PTR, "fptr"},
        {PTR, "ptr"},

    };

    inline std::string getTokenText(int tokenType)
    {
        auto it = tokenText.find(tokenType);
        if (it != tokenText.end())
        {
            return it->second;
        }
        throw TokenNotFoundException(color::colorText("Compiler error, token not found.", color::BOLD_RED));
    }

    inline int getTokenType(const std::string &tokenString)
    {
        for (const auto &pair : tokenText)
        {
            if (pair.second == tokenString)
            {
                return pair.first;
            }
        }
        throw TokenNotFoundException(color::colorText("Compiler error, token not found.", color::BOLD_RED));
    }

    inline bool isNumber(int type)
    {
        switch (type)
        {
        case hlir::TYPE_DOUBLE:
        case hlir::TYPE_FLOAT:
        case hlir::TYPE_INT:
        case hlir::NUMBER:
            return true;
        default:
            return false;
        }
    }

    inline bool isRealNumber(int type)
    {
        switch (type)
        {
        case hlir::TYPE_DOUBLE:
        case hlir::TYPE_FLOAT:
            return true;
        default:
            return false;
        }
    }

    inline int determineType(const std::string &input)
    {
        // Definição das expressões regulares com base nas regras fornecidas
        static const std::regex realNumberRegex(R"(^-?\d+\.\d+([eE][+-]?\d+)?[FD]?$)");
        static const std::regex intNumberRegex(R"(^-?\d+$)");
        static const std::regex booleanValueRegex(R"(^true|false$)");
        static const std::regex stringLiteralRegex(R"(^"[^"\r\n]*"$)");

        if (std::regex_match(input, realNumberRegex))
        {
            return hlir::REAL_NUMBER;
        }
        if (std::regex_match(input, intNumberRegex))
        {
            return hlir::TYPE_INT;
        }
        if (std::regex_match(input, booleanValueRegex))
        {
            return hlir::TYPE_BOOLEAN;
        }
        if (std::regex_match(input, stringLiteralRegex))
        {
            return hlir::TYPE_STRING;
        }

        throw TokenException("Isn't impossivel determine the type of " + input);
    }

    inline bool isValidFloatChar(char c)
    {
        return std::isdigit(c) || c == '.' || c == 'e' || c == 'E' || c == '+' || c == '-';
    }

    // Função para determinar o tipo de um literal de ponto flutuante com validação
    inline int determineFloatType(const std::string &literal)
    {
        if (literal.empty())
        {
            throw std::invalid_argument("Literal vazio");
        }

        // Verifica se o último caractere é um sufixo
        char lastChar = literal.back();
        int type = hlir::TYPE_FLOAT; // Tipo padrão

        if (lastChar == 'd' || lastChar == 'D')
        {
            type = hlir::TYPE_DOUBLE;
        }

        // Se o último caractere é um sufixo, remova-o para validar o restante do literal
        std::string numericPart = (lastChar == 'f' || lastChar == 'F' || lastChar == 'd' || lastChar == 'D')
                                      ? literal.substr(0, literal.size() - 1)
                                      : literal;

        // Verifica se todos os caracteres na parte numérica são válidos
        for (char c : numericPart)
        {
            if (!isValidFloatChar(c))
            {
                throw std::invalid_argument("Literal contém caracteres inválidos: " + std::string(1, c));
            }
        }

        // (Opcional) Verifica se a parte numérica pode ser convertida para um tipo de ponto flutuante
        try
        {
            std::stod(numericPart); // Tenta converter para double
        }
        catch (const std::exception &)
        {
            throw std::invalid_argument("Literal numérico inválido: " + numericPart);
        }

        return type;
    }

    inline int getTypePrecedence(int dataType)
    {
        // Defina a precedência de tipos conforme sua implementação em TokenMap
        switch (dataType)
        {
        case hlir::TYPE_INT:
            return 1;
        case hlir::TYPE_FLOAT:
            return 2;
        case hlir::TYPE_DOUBLE:
            return 3;
        default:
            throw std::runtime_error("TokenMap Error: Invalid type");
        }
    }

    inline int getHigherPrecedenceType(int type1, int type2)
    {
        int precedence1 = getTypePrecedence(type1);
        int precedence2 = getTypePrecedence(type2);

        if (precedence1 >= precedence2)
        {
            return type1;
        }
        else
        {
            return type2;
        }
    }

}

#endif // TOKEN_MAP_H

#ifndef TOKEN_MAP_HLIR_H
#define TOKEN_MAP_HLIR_H

#include <regex>
#include <string>
#include <unordered_map>
#include "../headers/Colors.h"
#include "Exceptions.h"

namespace tokenMap
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
        ARROW,

        // Linguagens suportadas
        C_LANG,
        IRON_LANG,

        //
        TRUE,
        FALSE,

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

        // Ponteiros
        PTR_TYPE_INT,
        PTR_TYPE_CHAR,
        PTR_TYPE_FLOAT,
        PTR_TYPE_BOOLEAN,
        PTR_TYPE_DOUBLE,

        // tipos de controle
        FUNCTION_PTR,
        FUNCTION_CALL,
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

            {TRUE, "true"},
            {FALSE, "false"},

            // Tipos de dados
            {TYPE_INT, "int"},
            {TYPE_CHAR, "char"},
            {TYPE_FLOAT, "float"},
            {TYPE_STRING, "string"},
            {TYPE_BOOLEAN, "boolean"},
            {TYPE_DOUBLE, "double"},

            {PTR_TYPE_INT, "ptr int"},
            {PTR_TYPE_CHAR, "ptr char"},
            {PTR_TYPE_FLOAT, "ptr float"},
            {PTR_TYPE_BOOLEAN, "ptr boolean"},
            {PTR_TYPE_DOUBLE, "ptr double"},

            // Linguagens suportadas
            {C_LANG, "C"},
            {IRON_LANG, "IRON"},

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
            {FUNCTION_CALL, "fn_call"},

    };

    inline std::string getTokenText(const int tokenType)
    {
        if (const auto it = tokenText.find(tokenType); it != tokenText.end())
        {
            return it->second;
        }
        printf("Token: %i\n", tokenType);
        throw TokenNotFoundException(color::colorText("Compiler error, token not found.", color::BOLD_RED));
    }

    inline int getTokenType(const std::string &tokenString)
    {
        for (const auto &[fst, snd]: tokenText)
        {
            if (snd == tokenString)
            {
                return fst;
            }
        }
        throw TokenNotFoundException(color::colorText("Compiler error, token not found.", color::BOLD_RED));
    }

    inline bool isNumber(const int type)
    {
        switch (type)
        {
            case TYPE_DOUBLE:
            case TYPE_FLOAT:
            case TYPE_INT:
            case NUMBER:
                return true;
            default:
                return false;
        }
    }

    inline bool isBooleanValue(const int type)
    {
        switch (type)
        {
            case TRUE:
            case FALSE:
                return true;
            default:
                return false;
        }
    }

    inline bool isRealNumber(const int type)
    {
        switch (type)
        {
            case TYPE_DOUBLE:
            case TYPE_FLOAT:
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
            return REAL_NUMBER;
        }
        if (std::regex_match(input, intNumberRegex))
        {
            return TYPE_INT;
        }
        if (std::regex_match(input, booleanValueRegex))
        {
            return TYPE_BOOLEAN;
        }
        if (std::regex_match(input, stringLiteralRegex))
        {
            return TYPE_STRING;
        }

        throw TokenException("Isn't impossible determine the type of " + input);
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

        // Verifica se o último character é um sufixo
        const char lastChar = literal.back();
        int type = tokenMap::TYPE_FLOAT; // Tipo padrão

        if (lastChar == 'd' || lastChar == 'D')
        {
            type = tokenMap::TYPE_DOUBLE;
        }

        // Se o último character é um sufixo, remova-o para validar o restante do literal
        const std::string numericPart = (lastChar == 'f' || lastChar == 'F' || lastChar == 'd' || lastChar == 'D')
                                                ? literal.substr(0, literal.size() - 1)
                                                : literal;

        // Verifica se todos os caracteres na parte numérica são válidos
        for (char c: numericPart)
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
        // Defina a precedência de tipos conforme a sua implementação em TokenMap
        switch (dataType)
        {
            case tokenMap::TYPE_INT:
                return 1;
            case tokenMap::TYPE_FLOAT:
                return 2;
            case tokenMap::TYPE_DOUBLE:
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

} // namespace tokenMap

#endif // TOKEN_MAP_HLIR_H

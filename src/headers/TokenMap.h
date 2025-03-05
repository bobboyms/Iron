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
        STRUCT,

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

        // Tipos de controle
        FUNCTION_PTR,
        FUNCTION_CALL,
        VARIABLE,
        VOID,
        NUMBER,
        NO_REAL_NUMBER,
        REAL_NUMBER,
        PRIVATE,
        ARGUMENT,

        // Operadores Lógicos e Relacionais
        OR, // Representa "||"
        AND, // Representa "&&"
        EQEQ, // Representa "=="
        NEQ, // Representa "!="
        LT, // Representa "<"
        LTE, // Representa "<="
        GT, // Representa ">"
        GTE // Representa ">="
    };

    inline const std::unordered_map<int, std::string> tokenText = {{COLON, ":"},
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
                                                                   {STRUCT, "struct"},

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

                                                                   // Tipos de controle
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

                                                                   // Operadores Lógicos e Relacionais
                                                                   {OR, "OR"},
                                                                   {AND, "AND"},
                                                                   {EQEQ, "EQEQ"},
                                                                   {NEQ, "NEQ"},
                                                                   {LT, "LT"},
                                                                   {LTE, "LTE"},
                                                                   {GT, "GT"},
                                                                   {GTE, "GTE"}};

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

    inline int getPtrFromType(const int type)
    {
        switch (type)
        {
            case TYPE_INT:
                return PTR_TYPE_INT;
            case TYPE_CHAR:
                return PTR_TYPE_CHAR;
            case TYPE_FLOAT:
                return PTR_TYPE_FLOAT;
            case TYPE_STRING:
                return PTR_TYPE_CHAR;
            case TYPE_BOOLEAN:
                return PTR_TYPE_BOOLEAN;
            case TYPE_DOUBLE:
                return PTR_TYPE_DOUBLE;
            default:
                throw TokenException("Isn't impossible determine the ptr token type of " + type);
        }
    }

    inline std::string getBoolOpText(const int type)
    {
        switch (type)
        {

            case OR:
                return "OR";
            case AND:
                return "AND";
            case EQEQ:
                return "EQEQ";
            case NEQ:
                return "NEQ";
            case LT:
                return "LT";
            case LTE:
                return "LTE";
            case GT:
                return "GT";
            case GTE:
                return "GTE";
            default:
                throw TokenException("Isn't impossible determine the boolean token type of " + type);
        }
    }

    inline bool isBooleanOp(const int type)
    {
        switch (type)
        {
            case OR:
            case AND:
            case EQEQ:
            case NEQ:
            case LT:
            case LTE:
            case GT:
            case GTE:
                return true;
            default:
                throw TokenException("Isn't impossible determine the boolean token type of " + type);
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
        for (const char c: numericPart)
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

    inline int getTypePrecedence(const int dataType)
    {
        // Defina a precedência de tipos conforme a sua implementação em TokenMap
        switch (dataType)
        {
            case TYPE_INT:
                return 1;
            case TYPE_FLOAT:
                return 2;
            case TYPE_DOUBLE:
                return 3;
            default:
                throw std::runtime_error("TokenMap Error: Invalid type");
        }
    }

    inline int getHigherPrecedenceType(const int type1, const int type2)
    {
        const int precedence1 = getTypePrecedence(type1);

        if (const int precedence2 = getTypePrecedence(type2); precedence1 >= precedence2)
        {
            return type1;
        }

        return type2;
    }

} // namespace tokenMap

#endif // TOKEN_MAP_HLIR_H

#ifndef TOKEN_MAP_H
#define TOKEN_MAP_H

#include "Colors.h"
#include <string>
#include <unordered_map>

namespace TokenMap {

    enum Token {
        GLOBAL = 1,
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
        VARIABLE,
        VOID,
        NUMBER,
        NO_REAL_NUMBER,
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
    };


    inline std::string getTokenText(int tokenType) {
        auto it = tokenText.find(tokenType);
        if (it != tokenText.end()) {
            return it->second;
        }
        throw LexusNotFoundException(color::colorText("Compiler error, token not found.", color::BOLD_RED));
    }

    inline int getTokenType(const std::string& tokenString) {
        for (const auto& pair : tokenText) {
            if (pair.second == tokenString) {
                return pair.first;
            }
        }
        throw LexusNotFoundException(color::colorText("Compiler error, token not found.", color::BOLD_RED));
    }

    inline  bool isNumber(int type) {
        switch (type) {
            case TokenMap::TYPE_DOUBLE:
            case TokenMap::TYPE_FLOAT:
            case TokenMap::TYPE_INT:
            case TokenMap::NUMBER:
                return true;
            default:
                return false;
        }
}



} // namespace TokenMap

#endif // TOKEN_MAP_H

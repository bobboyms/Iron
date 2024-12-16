// tests/IronLexerTests.cpp

#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include "../parsers/IronLexer.h"

// Função auxiliar para testar tokens individuais
void testToken(const std::string& input, int expectedTokenType, const std::string& expectedText) {
    antlr4::ANTLRInputStream inputStream(input);
    IronLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill(); // Preenche o buffer de tokens

    // Obtém o primeiro token gerado pelo lexer
    auto token = tokens.getTokens()[0];

    // Verifica o texto e o tipo do token
    EXPECT_EQ(token->getText(), expectedText) << "Texto do token incorreto para '" << input << "'";
    EXPECT_EQ(token->getType(), expectedTokenType) << "Tipo do token incorreto para '" << input << "'";
}

// Testes para os tokens de símbolos
TEST(IronLexerTests, Symbols) {
    testToken(":", IronLexer::COLON, ":");
    testToken("=", IronLexer::EQ, "=");
    testToken(";", IronLexer::SEMICOLON, ";");
    testToken(".", IronLexer::DOT, ".");
    testToken("*", IronLexer::STAR, "*");
    testToken("{", IronLexer::L_CURLY, "{");
    testToken("}", IronLexer::R_CURLY, "}");
    testToken("[", IronLexer::L_BRACKET, "[");
    testToken("]", IronLexer::R_BRACKET, "]");
    testToken("(", IronLexer::L_PAREN, "(");
    testToken(")", IronLexer::R_PAREN, ")");
}

// Testes para as palavras reservadas
TEST(IronLexerTests, ReservedWords) {
    testToken("fn", IronLexer::FUNCTION, "fn");
    testToken("let", IronLexer::LET, "let");
    testToken("public", IronLexer::PUBLIC, "public");
    testToken("import", IronLexer::IMPORT, "import");
}

// Testes para os tipos de dados
TEST(IronLexerTests, DataTypes) {
    testToken("int", IronLexer::TYPE_INT, "int");
    testToken("char", IronLexer::TYPE_CHAR, "char");
    testToken("float", IronLexer::TYPE_FLOAT, "float");
    testToken("string", IronLexer::TYPE_STRING, "string");
    testToken("boolean", IronLexer::TYPE_BOOLEAN, "boolean");
    testToken("double", IronLexer::TYPE_DOUBLE, "double");
}

// Testes para literais
TEST(IronLexerTests, Literals) {
    testToken("3.14", IronLexer::REAL_NUMBER, "3.14");
    testToken("-42", IronLexer::INT_NUMBER, "-42");
    testToken("true", IronLexer::BOOLEAN_VALUE, "true");
    testToken("false", IronLexer::BOOLEAN_VALUE, "false");
    testToken("\"hello\"", IronLexer::STRING_LITERAL, "\"hello\"");
}

// Testes para identificadores
TEST(IronLexerTests, Identifiers) {
    testToken("myVariable", IronLexer::IDENTIFIER, "myVariable");
    testToken("_var123", IronLexer::IDENTIFIER, "_var123");
}

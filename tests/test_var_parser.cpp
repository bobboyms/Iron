#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include "../parsers/IronLexer.h"
#include "../parsers/IronParser.h"

// Fixture para os testes do IronParser
class IronParserTest : public ::testing::Test {
protected:
    void SetUpParser(const std::string& input) {
        inputStream = std::make_unique<antlr4::ANTLRInputStream>(input);
        lexer = std::make_unique<IronLexer>(inputStream.get());
        tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
        parser = std::make_unique<IronParser>(tokens.get());
        parser->program(); // Processa o programa
    }

    void CheckSyntaxErrors(int expectedErrors) const {
        int syntaxErrors = parser->getNumberOfSyntaxErrors();
        if (expectedErrors == 0) {
            ASSERT_EQ(syntaxErrors, 0) << "Erro: O número de erros de sintaxe deve ser zero.";
        } else {
            ASSERT_EQ(syntaxErrors, expectedErrors) << "Erro: O número de erros de sintaxe deve ser " << expectedErrors << ".";
        }
    }

    std::unique_ptr<antlr4::ANTLRInputStream> inputStream;
    std::unique_ptr<IronLexer> lexer;
    std::unique_ptr<antlr4::CommonTokenStream> tokens;
    std::unique_ptr<IronParser> parser;
};

// --- Testes Válidos ---

TEST_F(IronParserTest, VarDeclarationWithoutInitialization) {
    // Testa a declaração de variável sem inicialização
    std::string input = R"(let x: int
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, VarDeclarationWithIntInitialization) {
    // Testa a declaração de variável com inicialização inteira
    std::string input = R"(let x: int = 42
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, VarDeclarationWithStringInitialization) {
    // Testa a declaração de variável com inicialização string
    std::string input = R"(let name: string = "ChatGPT"
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, VarDeclarationWithBoolInitialization) {
    // Testa a declaração de variável com inicialização booleana
    std::string input = R"(let isActive: boolean = true
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, VarDeclarationWithFloatInitialization) {
    // Testa a declaração de variável com inicialização float
    std::string input = R"(let pi: float = 3.14
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, MultipleVarDeclarations) {
    // Testa múltiplas declarações de variáveis
    std::string input = R"(
let x: int = 10
let name: string = "ChatGPT"
let isActive: boolean = false
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, IdentifierWithNumbersAndLetters) {
    // Testa identificadores que começam com letra e contêm números
    std::string input = R"(let var1: int = 100
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, TypeCaseSensitivity) {
    // Testa tipos de dados com diferentes capitalizações
    std::string input = R"(let x: int = 10
let y: string = "Hello"
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}


TEST_F(IronParserTest, MultipleVarDeclarationsWithoutInitialization) {
    // Testa múltiplas declarações sem inicialização
    std::string input = R"(
let a: int
let b: string
let c: boolean
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, ExtraSpacesBetweenTokens) {
    // Testa espaços extras entre os tokens
    std::string input = R"(let    x    :    int    =    5
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes Inválidos ---

TEST_F(IronParserTest, MissingLetKeyword) {
    // Testa a declaração sem a palavra-chave 'let'
    std::string input = R"(x: int
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, MissingVariableName) {
    // Testa a declaração sem o nome da variável
    std::string input = R"(let : int
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, MissingColon) {
    // Testa a declaração sem os dois pontos
    std::string input = R"(let x int
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, MissingType) {
    // Testa a declaração sem o tipo da variável
    std::string input = R"(let x:
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, MissingNewline) {
    // Testa a declaração sem a nova linha no final
    std::string input = R"(let x: int = 10)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, MissingInitializationValue) {
    // Testa a declaração com '=' mas sem valor de inicialização
    std::string input = R"(let x: int = 
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, InvalidType) {
    // Testa a declaração com tipo de dado inválido
    std::string input = R"(let x: unknownType = 10
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

TEST_F(IronParserTest, InvalidIdentifier) {
    // Testa a declaração com identificador inválido (contém caracteres especiais)
    std::string input = R"(let x$: int = 10
)";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronParserTest, OnlyLetKeyword) {
    // Testa a entrada contendo apenas 'let'
    std::string input = R"(let
)";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

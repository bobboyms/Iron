#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include "../parsers/IronLexer.h"
#include "../parsers/IronParser.h"

// Fixture para os testes do IronParser
class IronFunctionParserTest : public ::testing::Test {
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
            ASSERT_GT(syntaxErrors, 0) << "Erro: O número de erros de sintaxe deve ser maior que zero.";
        }
    }

    std::unique_ptr<antlr4::ANTLRInputStream> inputStream;
    std::unique_ptr<IronLexer> lexer;
    std::unique_ptr<antlr4::CommonTokenStream> tokens;
    std::unique_ptr<IronParser> parser;
};

// --- Testes para Importações ---
TEST_F(IronFunctionParserTest, ValidImportStatements) {
    std::string input = R"(
        import sistema.io
        import sistema.rede.*
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes para Declarações de Funções ---
TEST_F(IronFunctionParserTest, FunctionWithoutParametersOrReturnType) {
    std::string input = R"(
        fn outro() {
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, FunctionWithParametersAndReturnType) {
    std::string input = R"(
        fn soma(numero: int, outro: int=20):int {
            return numero + outro
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, FunctionWithFunctionalParameterType) {
    std::string input = R"(
        fn outro(soma:(a:int, b:int):int):float {
            return soma(a:10, b:20)
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, FunctionWithEmptyBody) {
    std::string input = R"(
        fn vazio():int {
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes para Funções Anônimas (Lambdas) ---
TEST_F(IronFunctionParserTest, InlineLambdaFunction) {
    std::string input = R"(
        @main(args) {
            let funcaoInline: fn = (idade:int, peso:float):int -> 2 * 3 + soma()
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, BlockLambdaFunction) {
    std::string input = R"(
        @main(args) {
            let funcaoBlock: fn = (altura:float, calc:fn = (altura:float):float -> {
                return altura / 1.5
            }): float -> {
                return calc(altura:altura)
            }
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes para Variáveis e Atribuições ---
TEST_F(IronFunctionParserTest, VariableDeclarationWithInitialization) {
    std::string input = R"(
        @main(args) {
            let numero: int = 20
            let mensagem: string = "Olá"
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, VariableWithLambdaFunction) {
    std::string input = R"(
        @main(args) {
            let soma: fn = (a:int, b:int):int -> a + b
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes para Chamadas de Função ---
TEST_F(IronFunctionParserTest, SimpleFunctionCall) {
    std::string input = R"(
        @main(args) {
            soma(numero:10, outro:5)
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, FunctionCallWithLambdaAsArgument) {
    std::string input = R"(
        @main(args) {
            outro(soma:(a:int, b:int):int -> a + b)
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes para Expressões Matemáticas ---
TEST_F(IronFunctionParserTest, MathematicalExpressions) {
    std::string input = R"(
        @main(args) {
            let resultado: int = 2 * 3 + (5 - 1) / 2
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

// --- Testes Inválidos ---
TEST_F(IronFunctionParserTest, DuplicateFunctionName) {
    std::string input = R"(
        fn soma(numero: int):int {
            return numero
        }
        fn soma(numero: int):int {
            return numero
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0); // Erro semântico esperado, mas verifica sintaxe
}

TEST_F(IronFunctionParserTest, DuplicateParameterName) {
    std::string input = R"(
        fn soma(numero: int, numero: int):int {
            return numero
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, LambdaWithoutReturnType) {
    std::string input = R"(
        @main(args) {
            let funcao: fn = (a:int, b:int) -> a + b
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, FunctionCallWithMissingArgument) {
    std::string input = R"(
        @main(args) {
            soma(numero:10)
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(0);
}

TEST_F(IronFunctionParserTest, FunctionWithInvalidBody) {
    std::string input = R"(
        fn soma(numero: int):int {
            10 * 20 return
        }
    )";
    SetUpParser(input);
    CheckSyntaxErrors(1);
}

#include "test_semantic_common.cpp"

// Test fixture for variable declaration and type checking
class SemanticVariableTests : public SemanticAnalysisTestBase {};

// Testes básicos de declaração de variáveis
TEST_F(SemanticVariableTests, TestBasicVariableDeclarations)
{
    const std::string input = R"(
        fn main():int {
            let x:int = 25
            let b:float = 25.00
            return x
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticVariableTests, TestVariableRedefinition)
{
    const std::string input = R"(
        fn main():int {
            let x:int = 25
            let x:float = 25.00
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableRedefinitionException);
}

TEST_F(SemanticVariableTests, TestUninitializedVariable)
{
    std::string input = R"(
        fn main():int {
            let x:int
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::UninitializedVariableException);
}

TEST_F(SemanticVariableTests, TestMultipleDataTypes)
{
    std::string input = R"(
        fn main() {
            let x:int = 25
            let y:float = 25.00
            let z:double = 250.00D
            let d:string = "Olá mundo doido!"
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

// Testes de incompatibilidade de tipos
TEST_F(SemanticVariableTests, TestTypeMismatchFloatToInt)
{
    std::string input = R"(
        fn main() {
            let x:int = 25.00
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticVariableTests, TestTypeMismatchIntToFloat)
{
    std::string input = R"(
        fn main() {
            let y:float = 25
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticVariableTests, TestTypeMismatchDoubleToFloat)
{
    std::string input = R"(
        fn main() {
            let z:double = 250.00
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticVariableTests, TestTypeMismatchIntToString)
{
    std::string input = R"(
        fn main() {
            let d:string = 2
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

// Testes de referência e atribuição de variáveis não definidas
TEST_F(SemanticVariableTests, TestUndefinedVariableReference)
{
    std::string input = R"(
        fn teste() {
            x
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticVariableTests, TestUndefinedVariableAssignment)
{
    std::string input = R"(
        fn teste() {
            x = 10
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticVariableTests, TestUndefinedVariableInitialization)
{
    std::string input = R"(
        fn teste() {
            let x:int = b
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

// Testes de mutabilidade
TEST_F(SemanticVariableTests, TestMutableVariables)
{
    std::string input = R"(
        fn main() {
            mut let x:int = 3
            x = x + 1
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticVariableTests, TestImmutableAssignment)
{
    std::string input = R"(
        fn main() {
            let x:int = 3
            while (x < 5) {
                x = x + 1
            }
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableCannotBeChangedException);
}

TEST_F(SemanticVariableTests, TestMutableTypeMismatch)
{
    std::string input = R"(
        fn main() {
            mut let x:int = 3
            let z:float = 0.25
            while (x < 5) {
                x = z
            }
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

// Testes de inicialização de structs
TEST_F(SemanticVariableTests, TestStructInitTypeNotFound)
{
    std::string input = R"(
        struct Pessoa {
            mut name:string,
            idade:int
        }

        fn main() {
            let pessoa:PessoaX = {name:"Thiago", idade:2}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeNotFoundException);
}

TEST_F(SemanticVariableTests, TestStructInitTypeFound)
{
    std::string input = R"(
        struct Pessoa {
            mut name:string,
            idade:int
        }

        fn main() {
            let pessoa:Pessoa = {name:"Thiago", idade:2}
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticVariableTests, TestStructInitFieldNotFound)
{
    std::string input = R"(
        struct Pessoa {
            mut name:string,
            idade:int
        }

        fn main() {
            let pessoa:Pessoa = {nameXX:"Thiago", idade:2}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::FieldNotFoundException);
}

TEST_F(SemanticVariableTests, TestStructInitFieldTypeMismatch)
{
    std::string input = R"(
        struct Pessoa {
            mut name:string,
            idade:int
        }

        fn main() {
            let pessoa:Pessoa = {name:78468, idade:2}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticVariableTests, TestStructInitFieldTypeMismatch2)
{
    std::string input = R"(
        struct Pessoa {
            mut name:string
        }

        fn main() {
            mut let pessoa:Pessoa = { name:"" }
            pessoa.name = 2
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

// Testes com estruturas aninhadas (T1 a T6)
TEST_F(SemanticVariableTests, T1)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            mut endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {endereco:{rua:"32", cidade:{nome:"taliba"}}}
            pessoa.endereco = {rua:25, cidade:{nome:"taliba"}}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticVariableTests, T2)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            mut endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {endereco:{rua:"32", cidade:{nome:74}}}
            pessoa.endereco = {rua:"25 de março", cidade:{nome:"taliba"}}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticVariableTests, T3)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {endereco:{rua:"32", cidade:{nome:"José e Maria"}}}
            pessoa.endereco = {rua:"25 de março", cidade:{nome:"taliba"}}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableCannotBeChangedException);
}

TEST_F(SemanticVariableTests, T4)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            mut endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {endereco:{rua:"32", cidade:{nome:"taliba"}}}
            pessoa.endereco = {rua:"25", cidade:{nomex:"taliba"}}
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::FieldNotFoundException);
}

TEST_F(SemanticVariableTests, T5)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            mut endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {endereco:{}}
            let endereco:Endereco = pessoa.endereco
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticVariableTests, T6)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            mut endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {endereco:{}}
            let rua:int = pessoa.endereco.rua
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::UninitializedFieldException);
}

TEST_F(SemanticVariableTests, T7)
{
    std::string input = R"(
        struct Cidade {
            mut nome:string
        }
        struct Endereco {
            mut rua:string,
            cidade: Cidade
        }
        struct Pessoa {
            mut name:string,
            mut endereco: Endereco
        }
        fn main() {
            mut let pessoa:Pessoa = {}
            pessoa.endereco.rua = "rua 25 de março"
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::UninitializedFieldException);
}

#include "test_semantic_common.cpp"

// Test fixture for variable declaration and type checking
class SemanticVariableTests : public SemanticAnalysisTestBase {};

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
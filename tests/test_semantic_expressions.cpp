#include "test_semantic_common.cpp"

// Test fixture for expression handling
class SemanticExpressionTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticExpressionTests, TestBasicVariableExpressions)
{
    std::string input = R"(
        fn soma() {
            let b:int = 12
            let x:int = b
            b + x * 25
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticExpressionTests, TestMultipleVariableExpressions)
{
    std::string input = R"(
        fn teste() {
            let b:int = 12
            let x:int = b
            25 + x * b * x
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticExpressionTests, TestUndefinedVariableInExpression)
{
    std::string input = R"(
        fn teste() {
            let b:int = 12
            let x:int = b
            25 + x * x * c
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticExpressionTests, TestTypeMismatchInExpression)
{
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:int = 32
            let c:int = 28
            let d:int = 15
            let e:string = "olá mundo"
            (a + b * (c + d) - e)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticExpressionTests, TestStringTypeMismatchInExpression)
{
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:string = "32"
            let c:int = 28
            let d:int = 15
            let e:string = "olá mundo"
            (a + b * (c + d) - e)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticExpressionTests, TestMixedTypesExpression)
{
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:double = 32.26D
            a + 1.25 + b * 2.36 - a
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticExpressionTests, TestComplexExpression)
{
    std::string input = R"(
        fn teste() {
            (10 * 1.36 / (250.1254D - 25) + 28)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticExpressionTests, TestFunctionCallInExpression)
{
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma() {
            let x: int = 10
            x + sub()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticExpressionTests, TestTypeMismatchInFunctionCallExpression)
{
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma() {
            let y: string = "hello"
            y * sub()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}
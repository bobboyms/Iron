#include "test_semantic_common.cpp"

// Test fixture for boolean expression tests
class SemanticBooleanTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticBooleanTests, TestBooleanLiteral)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = true
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBooleanTests, TestNotOperator)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = not false
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBooleanTests, TestAndOrOperators)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = true and false or true
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBooleanTests, TestRelationalExpression)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = 5 < 10
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBooleanTests, TestParenthesizedBooleanExpression)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = (true or false) and (5 == 5)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBooleanTests, TestUndefinedVariableInBoolean)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = x and true
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticBooleanTests, TestIntToBooleanCoercion)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = 5 and false
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBooleanTests, TestFunctionReturnTypeBoolean)
{
    const std::string input = R"(
        fn getNumber():int {
            return 5
        }
        fn main() {
            let b:boolean = getNumber()
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticBooleanTests, TestComplexBooleanExpression)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = not (5 > 3 and (10 <= 10))
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}
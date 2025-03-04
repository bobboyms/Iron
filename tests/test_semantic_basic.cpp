#include "test_semantic_common.cpp"

// Test fixture for basic semantics of functions and return statements
class SemanticBasicTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticBasicTests, TestEmptyMain)
{
    const std::string input = R"(
        fn main() {
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBasicTests, TestMainWithReturn)
{
    const std::string input = R"(
        fn main():int {
            return 0
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBasicTests, TestFunctionRedefinition)
{
    const std::string input = R"(
        fn main():int {
        }

        fn main() {
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionRedefinitionException);
}

TEST_F(SemanticBasicTests, TestMissingFunctionReturn)
{
    const std::string input = R"(
        fn main():float {
            let block:fn = (a:int):float -> {
                2.5 / a
            }
            return block(a:25)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ReturnNotFoundException);
}

TEST_F(SemanticBasicTests, TestReturnTypeFloat)
{
    std::string input = R"(
        fn returnFloat():float {
            return 10.00
        }

        fn main():float {
            return returnFloat()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBasicTests, TestReturnTypeInt)
{
    std::string input = R"(
        fn returnInt():int {
            return 10
        }

        fn main() {
            returnInt() * 9
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBasicTests, TestReturnTypeMismatchIntFloat)
{
    std::string input = R"(
        fn returnInt():int {
            return 10.00
        }

        fn main() {
            returnFloat() * 9
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticBasicTests, TestReturnTypeMismatchFloatInt)
{
    std::string input = R"(
        fn returnFloat():float {
            return 10
        }

        fn main() {
            returnFloat() * 9
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticBasicTests, TestReturnFunctionType)
{
    std::string input = R"(
        fn returnFN():fn {
            let inline:fn = (a:int):int -> a * 2
            return inline
        }

        fn main() {
            returnFN()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticBasicTests, TestReturnTypeMismatchFunctionString)
{
    std::string input = R"(
        fn returnFN():string {
            let inline:fn = (a:int):int -> a * 2
            return inline
        }

        fn main() {
            returnFN()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticBasicTests, TestMissingFunctionDefinition)
{
    std::string input = R"(
        fn main():int {
            return returnFloat()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticBasicTests, TestMissingInlineFunction)
{
    std::string input = R"(
        fn main():int {
            // let inline:fn = (a:int):float -> a * 6
            return inline(a:10)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}
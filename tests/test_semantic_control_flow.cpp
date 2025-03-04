#include "test_semantic_common.cpp"

// Test fixture for control flow tests
class SemanticControlFlowTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticControlFlowTests, TestBasicIfElse)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 3

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else {
                printf(format:"X < Y\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticControlFlowTests, TestIfElseIf)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 30

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else if (x < y) {
                printf(format:"X < Y\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticControlFlowTests, TestIfElseIfElse)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 30

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else if (false) {
                printf(format:"X < Y\n")
            } else {
                printf(format:"Entrou no else\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}
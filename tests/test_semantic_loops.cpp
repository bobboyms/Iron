#include "test_semantic_common.cpp"

// Test fixture for loop tests
class SemanticLoopTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticLoopTests, TestUndefinedVariableInLoop)
{
    std::string input = R"(
        fn main() {
            mut let x:int = 3
            while (x < 5) {
                x = z
            }
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticLoopTests, TestCompoundLoopWithBreak)
{
    std::string input = R"(
    import std.output.printf

    fn main() {
        mut let x:int = 0
        while x < 100 {
            x = x + 1
            if (x == 5) {
                printf(format:"x = 5\n")
            } else {
                x = x + 1
                 printf(format:"else x = %u\n", x:x)
                 if (x == 59) {
                    break
                 }
            }
        }

        printf(format:"x1 = %u\n", r:x)
    }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}
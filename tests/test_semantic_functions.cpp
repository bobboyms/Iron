#include "test_semantic_common.cpp"

// Test fixture for function argument and call tests
class SemanticFunctionTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticFunctionTests, TestUndefinedVariableInFunctionBody)
{
    std::string input = R"(
        fn soma(x:int, b:int, n:string) {
            x + b * z
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticFunctionTests, TestMissingFunctionArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 5}

        fn main() {
            sub(a:10,p:5) * 36
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionArgNotFoundException);
}

TEST_F(SemanticFunctionTests, TestValidFunctionCall)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 22 }

        fn main() {
            sub(a:10,b:5) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionTests, TestArgumentTypeMismatch)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}

        fn main() {
            sub(a:10,b:5.00) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticFunctionTests, TestVariableAsArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0 }

        fn main(x:int) {
            sub(a:10,b:x) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionTests, TestFloatToFloatArgument)
{
    std::string input = R"(
        fn sub(a:float, b:int):int { return 0}

        fn main(x:int) {
            let a:float = 6.23
            sub(a:a,b:x) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionTests, TestUndefinedVariableAsArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0 }

        fn main() {
            sub(a:10,b:p) * 8958.12554D
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticFunctionTests, TestFunctionCallAsArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {  return 0 }
        fn div():int { return 0 }

        fn main() {
            sub(a:10,b:div()) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionTests, TestFunctionTypeMismatchAsArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div():float { return 0}

        fn main() {
            sub(a:10,b:div()) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticFunctionTests, TestNestedFunctionCallAsArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):int { return 0}

        fn main() {
            sub(a:10,b:div(d:254.022D)) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionTests, TestMultipleNestedFunctionCallAsArgument)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):int { return 0}
        fn mult(x:float):double { return 0.0D}

        fn main() {
            sub(a:10,b:div(d:mult(x:15.0))) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionTests, TestNestedFunctionCallTypeMismatch)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):float { return 0.0 }

        fn main() {
            sub(a:10,b:div(d:254.022D)) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticFunctionTests, TestArgumentCountMismatch)
{
    std::string input = R"(
        fn adicionar(a:int, b:int): int {
            return a + b
        }

        fn main() {
            let soma: int = adicionar(a: 5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
}

TEST_F(SemanticFunctionTests, TestArgumentOrderMismatch)
{
    std::string input = R"(
        fn sub(x:int, y:int):int {return 0}

        fn main() {
            let add:fn = (pp:int):int -> pp + 32
            let inline:fn = (a:int,b:float, c:boolean):int -> a + b
            sub(x:12, y:add(pp:25)) * inline(b:25.00F,a:32, c:false)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticFunctionTests, TestArgumentOrderMismatchInline)
{
    std::string input = R"(
        fn main() {
            let inline:fn = (a:int, b:float, c:boolean):int -> a + b
            inline(c:true, a:32, b:25.00F)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticFunctionTests, TestArgumentOrderMismatchSimple)
{
    std::string input = R"(
        fn multiply(x:int, y:float):float {return 0.0}

        fn main() {
            multiply(y:25.00F, x:10)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticFunctionTests, TestThreeArgsOrderMismatch)
{
    std::string input = R"(
        fn sub(a:int, b:int, c:boolean):int {return 0}

        fn main() {
            let x:int = 10
            let y:int = 20
            sub(b:y, c:false, a:x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticFunctionTests, TestNestedCallsWithOrderMismatch)
{
    std::string input = R"(
        fn addOne(n:int):int {
            return n + 1
        }

        fn doubleValue(x:int, y:int):int {return 0}

        fn main() {
            doubleValue(y:addOne(n:2), x:5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}
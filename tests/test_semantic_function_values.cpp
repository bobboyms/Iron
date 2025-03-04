#include "test_semantic_common.cpp"

// Test fixture for function as value tests
class SemanticFunctionValueTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticFunctionValueTests, TestBasicInlineFunction)
{
    const std::string input = R"(
        fn main():int {
           let inline:fn = ():int -> 12
           let r:int = inline()
           return r
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestSimpleArrowFunction)
{
    const std::string input = R"(
        fn main() {
            let inline: fn = (a: int, b: int) -> a + b
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestArrowFunctionCall)
{
    const std::string input = R"(
        fn main() {
            let inline: fn = (a: int, b: int) -> a + b
            inline(a:12, b:14)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestArrowFunctionWithContextVariable)
{
    std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline: fn = (a: int, b: int): int -> (xb + b) * a
            inline(a:12, b:14)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestArrowFunctionTypeMismatch)
{
    std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline: fn = (a: int, b: int) -> (xb + b) * a
            inline(a:12, b:14) + 5.22
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticFunctionValueTests, TestTypedArrowFunctionNoMismatch)
{
    std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline: fn = (a: int, b: int): int -> (xb + b) * a
            inline(a:12, b:14) + 5.22
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestMultipleFunctions)
{
    const std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x:int, y:float):float -> x + y

            inline(a:12, b:14) + 5.22 / sum(x:2, y:3.26F)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestBlockWithFunctionReturn)
{
    const std::string input = R"(
        fn value():int{
            return 25
        }
        fn main() {
            let blockFn : fn = (a:int, c:int):int ->{return 0}
            (blockFn(a:32, c:25) * (36 / value()))
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestAssignFunctionToVariable)
{
    const std::string input = R"(
        fn main() {
            let inline:fn = (a:int):int -> a * 8
            let x:fn = inline
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestAssignNamedFunctionToVariable)
{
    const std::string input = R"(
        fn sum(a:int, b:int) {
            let r:int = a + b
        }

        fn main() {
            let inline:fn = (a:int):int -> a * 8
            let x:fn = sum
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestTypeMismatchAssignFunction)
{
    const std::string input = R"(
        fn main() {
            let inline:int = 10
            let x:fn = inline
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticFunctionValueTests, TestSignatureMismatch)
{
    const std::string input = R"(
        fn sum(func:fn(a:float):int, c:int) {}

        fn main() {
            let inline:fn = (a:int):int -> a * 3
            sum(func:inline, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticFunctionValueTests, TestReturnTypeMismatch)
{
    const std::string input = R"(
        fn sum(func:fn(a:int):float, c:int) {}

        fn main() {
            let inline:fn = (a:int):int -> a * 3
            sum(func:inline, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticFunctionValueTests, TestCorrectSignatureMatch)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int,c:float):int, c:int) {}

        fn main() {
            let inline:fn = (a:int,b:int,c:float):int -> a * 3
            sum(func:inline, c:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestNamedFunctionSignatureMismatch)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int, b:float):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticFunctionValueTests, TestArgumentCountMismatch)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticFunctionValueTests, TestCorrectArgumentCountMatch)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int,b:int):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestNestedFunctionCall)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let inline:fn = (x:int):int -> x * 2 * p
            func(a:inline(x:p))
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticFunctionValueTests, TestNestedReturnTypeMismatch)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let inline:fn = (x:int):float -> x * 2.0 * p
            func(a:inline(x:p))
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}
#include "test_hlir_common.cpp"

// Test fixture for expression-related HLIR tests
class HlirExpressionTests : public HlirTestBase {};

TEST_F(HlirExpressionTests, TestBasicExpressions)
{
    const std::string output = R"(
        fn main():void {
            var_0:int = 12
            var_1:int = var_0
            var_2:int = 25
            var_3:int = MULT var_1, var_2
            var_4:int = PLUS var_0, var_3
        }
    )";

    const std::string input = R"(
        fn main() {
            let b:int = 12
            let x:int = b
            b + x * 25
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirExpressionTests, TestFloatExpressions)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn main():void {
            var_0:int = 25
            var_1:int = 32
            var_3:float = 1.25
            var_4:float = var_0 int to float
            var_5:float = PLUS var_4, var_3
            var_6:float = 2.36
            var_7:float = var_1 int to float
            var_8:float = MULT var_7, var_6
            var_9:float = PLUS var_5, var_8
            var_10:float = var_0 int to float
            var_11:float = MINUS var_9, var_10
            var_2:float = var_11
            var_12:string = "result %f\n"
            call int printf(result:var_12,r:var_2)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
           let a:int = 25
           let b:int = 32
           let r:float = a + 1.25 + b * 2.36 - a
           //result 76.77
           printf(result:"result %f\n",r:r)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirExpressionTests, TestDoubleExpressions)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn main():void {
            var_0:int = 10
            var_1:double = 20.00D
            var_2:int = 30
            var_4:double = var_0 int to double
            var_5:double = PLUS var_4, var_1
            var_6:double = var_2 int to double
            var_7:double = MULT var_5, var_6
            var_8:double = var_0 int to double
            var_9:double = MINUS var_7, var_8
            var_3:double = var_9
            var_10:string = "result %f\n"
            call int printf(result:var_10,r:var_3)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
            let a:int = 10
            let b:double = 20.00D
            let c:int = 30
            let r:double = (a + b) * c - a
            // result = 890.00
            printf(result:"result %f\n",r:r)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirExpressionTests, TestMixedTypeExpressions)
{
    const std::string output = R"(
        fn soma(x:int,b:int):void {
            var_0:float = 1.145
            var_1:float = b int to float
            var_2:float = MULT var_1, var_0
            var_3:float = x int to float
            var_4:float = PLUS var_3, var_2
        }
    )";

    std::string input = R"(
        fn soma(x:int, b:int) {
            x + b * 1.145
        }
    )";

    runAnalysis(input, output);
}
#include "test_hlir_common.cpp"

// Test fixture for function-as-argument HLIR tests
class HlirFunctionArgTests : public HlirTestBase {};

TEST_F(HlirFunctionArgTests, TestFunctionAsArgument)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn(a:int,b:int):int,a:int,b:int):int {
            var_0:int = call int func(a:a,b:b)
            return int var_0
        }

        fn main():void {
            var_0:fn = gfn_main_inline
            var_1:string = "result:%u\n"
            var_2:int = 2
            var_3:int = 3
            var_4:int = call int sum(func:var_0,a:var_2,b:var_3)
            call int printf(format:var_1,r:var_4)
        }

        fn gfn_main_inline(a:int,b:int):int {
            var_0:int = MULT a, b
            return int var_0
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sum(func:fn(a:int,b:int):int, a:int,b:int):int {
            return func(a:a,b:b)
        }

        fn main() {
            let inline:fn = (a:int,b:int):int -> a * b
            printf(format:"result:%u\n", r:sum(func:inline, a:2, b:3))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestNamedFunctionAsArgument)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn(a:int,b:int):int,c:int):void {
            var_1:int = 2
            var_0:int = call int func(a:c,b:var_1)
            var_2:string = "result: %u\n"
            call int printf(format:var_2,r:var_0)
        }

        fn sub(a:int,b:int):int {
            var_0:int = MINUS a, b
            return int var_0
        }

        fn main():void {
            var_0:int = 10
            call void sum(func:sub,c:var_0)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sum(func:fn(a:int,b:int):int, c:int) {
            let r:int = func(a:c, b:2)
            printf(format:"result: %u\n", r:r)
        }

        fn sub(a:int,b:int):int {
            return a - b
        }

        fn main() {
            sum(func:sub, c:10)
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestNestedFunctionArg)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn(a:int):int,p:int):int {
            var_0:fn = gfn_sum_inline
            var_2:int = call int inline(x:p,p:p)
            var_1:int = call int func(a:var_2)
            return int var_1
        }

        fn gfn_sum_inline(x:int,p:int):int {
            var_0:int = 2
            var_1:int = MULT x, var_0
            var_2:int = MULT var_1, p
            return int var_2
        }

        fn main():void {
            var_0:fn = gfn_main_inline
            var_1:string = "result %u\n"
            var_2:int = 3
            var_3:int = call int sum(func:var_0,p:var_2)
            call int printf(format:var_1,r:var_3)
        }

        fn gfn_main_inline(a:int):int {
            var_0:int = 8
            var_1:int = MULT a, var_0
            return int var_1
        }
    )";

    const std::string input = R"(
                import std.output.printf

                fn sum(func:fn (a:int):int, p:int):int {
                    let inline:fn = (x:int):int -> x * 2 * p
                    return func(a:inline(x:p))
                }

                fn main() {
                   let inline:fn = (a:int):int -> a * 8
                   printf(format:"result %u\n", r:sum(func:inline, p:3))
                }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestSimpleFunctionArg)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn(a:int):int,p:int):int {
            var_0:int = call int func(a:p)
            return int var_0
        }

        fn main():void {
            var_0:fn = gfn_main_inline
            var_1:string = "result %u\n"
            var_2:int = 3
            var_3:int = call int sum(func:var_0,p:var_2)
            call int printf(format:var_1,r:var_3)
        }

        fn gfn_main_inline(a:int):int {
            var_0:int = 8
            var_1:int = MULT a, var_0
            return int var_1
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sum(func:fn (a:int):int, p:int):int {
            return func(a:p)
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           printf(format:"result %u\n", r:sum(func:inline, p:3))
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestBlockWithFunctionCall)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sub(a:int):int {
            var_0:int = 2
            var_1:int = MINUS a, var_0
            return int var_1
        }

        fn sum(p:int):int {
            var_0:fn = gfn_sum_block
            var_2:int = 3
            var_1:int = call int block(x:var_2,p:p)
            return int var_1
        }

        fn gfn_sum_block(x:int,p:int):int {
            var_0:int = call int sub(a:p)
            var_1:int = MULT var_0, x
            return int var_1
        }

        fn main():void {
            var_0:string = "resutl: %u\n"
            var_1:int = 3
            var_2:int = call int sum(p:var_1)
            call int printf(format:var_0,r:var_2)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sub(a:int):int {
            return a - 2
        }

        fn sum(p:int):int {

            let block:fn = (x:int):int -> {
                return sub(a:p) * x
            }

            return block(x:3)
        }

        fn main() {
           printf(format: "resutl: %u\n", r:sum(p:3))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestBlockWithFunctionAsArgument)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(sub:fn(a:int):int,p:int):int {
            var_0:fn = gfn_sum_block
            var_2:int = 3
            var_1:int = call int block(x:var_2,sub:sub,p:p)
            return int var_1
        }

        fn gfn_sum_block(x:int,sub:fn(a:int):int,p:int):int {
            var_0:int = call int sub(a:p)
            var_1:int = MULT var_0, x
            return int var_1
        }

        fn main():void {
            var_0:fn = gfn_main_inline
            var_1:string = "resutl: %u\n"
            var_2:int = 3
            var_3:int = call int sum(sub:var_0,p:var_2)
            call int printf(format:var_1,r:var_3)
        }

        fn gfn_main_inline(a:int):int {
            var_0:int = 2
            var_1:int = MINUS a, var_0
            return int var_1
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sum(sub:fn (a:int):int, p:int):int {

            let block:fn = (x:int):int -> {
                return sub(a:p) * x
            }

            return block(x:3)
        }

        fn main() {
           let inline:fn = (a:int):int -> a - 2
           printf(format: "resutl: %u\n", r:sum(sub:inline,p:3))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestMultipleFunctionArgument)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn main():void {
            var_0:int = 36
            var_1:fn = gfn_main_inline
            var_2:fn = gfn_main_sum
            var_5:int = 12
            var_6:int = 14
            var_4:int = call int inline(a:var_5,b:var_6,xb:var_0)
            var_7:float = 5.22
            var_9:int = 2
            var_10:float = 3.26F
            var_8:float = call float sum(x:var_9,y:var_10)
            var_11:float = DIV var_7, var_8
            var_12:float = var_4 int to float
            var_13:float = PLUS var_12, var_11
            var_3:float = var_13
            var_14:string = "result %f\n"
            call int printf(format:var_14,r:var_3)
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int {
            var_0:int = PLUS xb, b
            var_1:int = MULT var_0, a
            return int var_1
        }

        fn gfn_main_sum(x:int,y:float):float {
            var_0:float = x int to float
            var_1:float = PLUS var_0, y
            return float var_1
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x:int, y:float):float -> x + y

            let r:float = inline(a:12, b:14) + 5.22 / sum(x:2, y:3.26F)
            // result 600.992
            printf(format:"result %f\n", r:r)
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionArgTests, TestComplexFunctionArgs)
{
    const std::string output = R"(
        fn mult(pp:float):float {
            var_0:float = 1.3
            return float var_0
        }

        fn xptc(z:float):int {
            var_0:int = 2
            return int var_0
        }

        fn main():void {
            var_0:int = 36
            var_1:fn = gfn_main_inline
            var_2:fn = gfn_main_sum
            var_3:float = 5.22
            var_5:int = 12
            var_6:int = 14
            var_4:int = call int inline(a:var_5,b:var_6,xb:var_0)
            var_8:int = 12
            var_9:int = 87
            var_7:float = call float sum(x:var_8,y:var_9)
            var_10:float = var_4 int to float
            var_11:float = MULT var_10, var_7
            var_12:float = PLUS var_3, var_11
            var_14:float = 12.00F
            var_15:float = call float mult(pp:var_14)
            var_13:int = call int xptc(z:var_15)
            var_16:int = DIV var_13, var_0
            var_17:float = var_16 int to float
            var_18:float = MINUS var_12, var_17
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int {
            var_0:int = PLUS xb, b
            var_1:int = MULT var_0, a
            return int var_1
        }

        fn gfn_main_sum(x:int,y:int):float {
            var_0:float = 2.25
            var_1:float = x int to float
            var_2:float = PLUS var_0, var_1
            var_3:float = y int to float
            var_4:float = PLUS var_2, var_3
            return float var_4
        }
    )";

    const std::string input = R"(
        fn mult(pp:float): float {return 1.3 }
        fn xptc(z:float): int {return 2 }

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:mult(pp:12.00F)) / xb
        }

    )";

    runAnalysis(input, output);
}
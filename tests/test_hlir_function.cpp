#include "test_hlir_common.cpp"

// Test fixture for function-related HLIR tests
class HlirFunctionTests : public HlirTestBase {};

TEST_F(HlirFunctionTests, TestNestedFunctions)
{
    const std::string output = R"(
       fn soma(n:float,j:int):int {
            var_0:fn = gfn_soma_block1
            var_1:int = call int block1(j:j)
            return int var_1
        }

        fn gfn_soma_block1(j:int):int {
            var_0:int = 25
            var_1:fn = gfn_gfn_soma_block1_block2
            var_2:int = call int block2(j:j,x:var_0)
            return int var_2
        }

        fn gfn_gfn_soma_block1_block2(j:int,x:int):int {
            var_1:int = 2
            var_2:int = MULT var_1, j
            var_3:int = MULT var_2, x
            var_0:int = var_3
            var_4:int = 25
            var_5:fn = gfn_gfn_gfn_soma_block1_block2_block3
            var_7:int = 14524
            var_6:int = call int block3(n:var_7,j:j,x:var_4)
            return int var_6
        }

        fn gfn_gfn_gfn_soma_block1_block2_block3(n:int,j:int,x:int):int {
            var_1:int = 2
            var_2:int = MULT var_1, j
            var_3:int = MULT var_2, x
            var_4:int = MULT var_3, n
            var_0:int = var_4
            return int var_0
        }

        fn main():void {
            var_1:float = 2.3
            var_2:int = 3
            var_0:int = call int soma(n:var_1,j:var_2)
        }
    )";

    const std::string input = R"(

        fn soma(n:float, j:int): int {

            let block1:fn = ():int -> {
                   let x:int = 25
                   let block2:fn = ():int -> {
                        let r:int = 2 * j * x
                        let x:int = 25

                        let block3:fn = (n:int):int -> {
                            let r:int = 2 * j * x * n
                            return r
                        }

                        return block3(n:14524)
                    }
                    return block2()
                }
            return block1()
        }

        fn main() {
            let r:int = soma(n:2.3, j:3)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionTests, TestBasicFunctionCall)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sub(ax:int,bx:int,nx:int):int {
            var_0:int = MULT bx, nx
            var_1:int = PLUS ax, var_0
            return int var_1
        }

        fn main():void {
            var_1:float = 32.25
            var_3:int = 25
            var_4:int = 32
            var_5:int = 25
            var_2:int = call int sub(ax:var_3,bx:var_4,nx:var_5)
            var_6:float = var_2 int to float
            var_7:float = MULT var_1, var_6
            var_0:float = var_7
            var_8:string = "result %f\n"
            call int printf(result:var_8,r:var_0)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sub(ax:int, bx:int, nx:int): int { return ax + bx * nx}

        fn main() {
            let r:float = 32.25 * sub(ax: 25, bx: 32, nx: 25)
            // result 26606.250000
            printf(result:"result %f\n",r:r)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionTests, TestNestedFunctionCalls)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn mult(n:int,p:float):float {
            var_0:float = n int to float
            var_1:float = MULT var_0, p
            return float var_1
        }

        fn sub(ax:int,bx:float):float {
            var_0:float = 1.0
            var_1:float = MULT bx, var_0
            var_2:float = ax int to float
            var_3:float = MINUS var_2, var_1
            return float var_3
        }

        fn main():void {
            var_0:float = 25.00
            var_2:float = 32.25
            var_4:int = 1
            var_5:int = 22
            var_6:float = call float mult(n:var_5,p:var_0)
            var_3:float = call float sub(ax:var_4,bx:var_6)
            var_7:float = MULT var_2, var_3
            var_1:float = var_7
            var_8:string = "result %f\n"
            call int printf(result:var_8,r:var_1)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn mult(n:int, p:float): float {return n * p}

        fn sub(ax:int, bx:float): float { return ax - bx * 1.0 }

        fn main() {
            let x: float = 25.00
            let r:float = 32.25 * sub(ax: 1, bx: mult(n:22, p:x))
            // result -17705.250000
            printf(result:"result %f\n",r:r)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionTests, TestInlineFunctionReturn)
{
    const std::string output = R"(
        fn mult(n:int,p:float):float {
            var_0:float = 0.0
            return float var_0
        }

        fn sub(ax:int,bx:float):int {
            var_0:int = 0
            return int var_0
        }

        fn main():float {
            var_0:float = 25.00
            var_1:fn = gfn_main_inline
            var_2:float = 32.25
            var_4:int = 1
            var_5:int = 22
            var_6:int = 25
            var_7:float = call float inline(a:var_6,x:var_0)
            var_8:float = call float mult(n:var_5,p:var_7)
            var_3:int = call int sub(ax:var_4,bx:var_8)
            var_9:float = var_3 int to float
            var_10:float = MULT var_2, var_9
            return float var_10
        }

        fn gfn_main_inline(a:int,x:float):float {
            var_0:float = a int to float
            var_1:float = MULT var_0, x
            return float var_1
        }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int {return 0 }

        fn main(): float {
            let x: float = 25.00
            let inline:fn = (a:int):float -> a * x
            return 32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:25)))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlirFunctionTests, TestInlineFunctionReturnRepeated)
{
    const std::string output = R"(
        fn mult(n:int,p:float):float {
            var_0:float = 0.0
            return float var_0
        }

        fn sub(ax:int,bx:float):int {
            var_0:int = 0
            return int var_0
        }

        fn main():float {
            var_0:float = 25.00
            var_1:fn = gfn_main_inline
            var_2:float = 32.25
            var_4:int = 1
            var_5:int = 22
            var_6:int = 25
            var_7:float = call float inline(a:var_6,x:var_0)
            var_8:float = call float mult(n:var_5,p:var_7)
            var_3:int = call int sub(ax:var_4,bx:var_8)
            var_9:float = var_3 int to float
            var_10:float = MULT var_2, var_9
            return float var_10
        }

        fn gfn_main_inline(a:int,x:float):float {
            var_0:float = a int to float
            var_1:float = MULT var_0, x
            return float var_1
        }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int {return 0 }

        fn main(): float {
            let x: float = 25.00
            let inline:fn = (a:int):float -> a * x
            return 32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:25)))
        }

    )";

    runAnalysis(input, output);
}
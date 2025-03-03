#include "test_hlir_common.cpp"

// Test fixture for loop-related HLIR tests
class HlirLoopTests : public HlirTestBase {};

TEST_F(HlirLoopTests, TestComplexWhileLoopWithBreak)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn main():void {
            var_0:int = 3
            jump while_cond_0

         block while_cond_0:
            var_1:int = 5
            var_2:boolean = cmp LT var_0, var_1
            cond var_2 while_body_1, while_end_2

         block while_body_1:
            var_3:int = 3
            var_4:int = 3
            var_5:boolean = cmp NEQ var_3, var_4
            cond var_5 then_4, else_5

         block then_4:
            var_6:int = 55
            jump end_3

         block else_5:
            var_7:boolean = false
            cond var_7 then_6, else_7

         block then_6:
            var_8:int = 1254
            jump end_3

         block else_7:
            var_9:int = 665
            jump while_end_2

         block end_3:
            var_11:int = 3
            var_12:int = MULT var_3, var_11
            var_10:int = var_12
            jump while_cond_0

         block while_end_2:
            var_13:string = "Finalizou\n"
            call int printf(format:var_13)
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
            mut let x:int = 3
            while (x < 5) {
                let z:int = 3
                if (z != 3) {
                    let z:int = 55
                } else if (false) {
                    let op:int = 1254
                } else {
                    let pp:int = 665
                    break
                }
                let n:int = z * 3
            }

            printf(format:"Finalizou\n")
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlirLoopTests, TestSimpleWhileLoop)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn main():void {
            var_0:int = 0
            jump while_cond_0

         block while_cond_0:
            var_1:int = 10
            var_2:boolean = cmp LT var_0, var_1
            cond var_2 while_body_1, while_end_2

         block while_body_1:
            var_3:int = 1
            var_4:int = PLUS var_0, var_3
            var_0:int = var_4
            var_5:string = "value if x: %i\n"
            call int printf(format:var_5,r:var_0)
            jump while_cond_0

         block while_end_2:
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
            mut let x: int = 0
            while x < 10 {
                x = x + 1
                printf(format:"value if x: %i\n", r:x)
            }
        }
    )";

    runAnalysis(input, output);
}
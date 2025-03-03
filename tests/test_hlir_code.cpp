#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "antlr4-runtime.h"

#include "../src/headers/HLIRGenerator.h"
#include "../src/headers/Hlir.h"
#include "../src/headers/SemanticAnalysis.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"

// Create a test fixture in the same style
class HlIrTestCode : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialize anything before each test if necessary.
    }

    /**
     * @brief Removes all whitespace characters from a given string.
     * @param str The input string.
     * @return A new string without any whitespace characters.
     */
    // Função que remove todos os caracteres de espaço em branco
    // Função que remove todos os caracteres de espaço em branco após aplicar o trim
    static std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        result.reserve(str.size());

        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c) { return !std::isspace(c); });

        return result;
    }

    /**
     * @brief Compares two strings for equality, ignoring any whitespace differences.
     * @param input The generated string from the test.
     * @param expectedOutput The expected string to compare against.
     *
     * If the strings match (ignoring whitespace), the test passes.
     * Otherwise, it fails and outputs the generated and expected strings.
     */
    void runAnalysis(const std::string &input, const std::string &expectedOutput)
    {
        auto hlirOutPut = getHighLevelCode(input);
        const auto cleanInput = removeWhitespace(hlirOutPut);
        const auto cleanExpected = removeWhitespace(expectedOutput);
        if (cleanInput == cleanExpected)
        {
            // Test passed
            return;
        }
        else
        {
            FAIL() << "Generated code does not match the expected code.\n"
                   << "Got (cleaned):      " << cleanInput << "\n"
                   << "Expected (cleaned): " << cleanExpected << "\n";
        }
    }

    static std::vector<std::string> loadStringAsLines(const std::string &code)
    {
        std::vector<std::string> lines;
        std::stringstream ss(code);

        std::string line;
        while (std::getline(ss, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    static std::string getHighLevelCode(const std::string &input)
    {
        auto config = std::make_shared<config::Configuration>("compiler_config.yaml");

        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto const parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticAnalysis analysis(parser, std::make_unique<scope::ScopeManager>(), loadStringAsLines(input),
                                        config);

        // Rewind
        tokens.seek(0);
        parser->reset();

        const auto exportContexts = std::make_shared<std::map<std::string, std::shared_ptr<hlir::Context>>>();
        const auto context = std::make_shared<hlir::Context>();
        hlir::HLIRGenerator highLevelCodeGenerator(parser, context, config, exportContexts);
        highLevelCodeGenerator.getContext();
        return context->getText();
    }
};

//-----------------------------------------------------------
// TESTS FOR THE CLASS FunctionArgs
//-----------------------------------------------------------

TEST_F(HlIrTestCode, T1)
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

TEST_F(HlIrTestCode, T2)
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

TEST_F(HlIrTestCode, T3)
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

TEST_F(HlIrTestCode, T4)
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

TEST_F(HlIrTestCode, T5)
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

// parei aqui
TEST_F(HlIrTestCode, T6)
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

TEST_F(HlIrTestCode, T7)
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

TEST_F(HlIrTestCode, T8)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T9)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T10)
{
    const std::string output = R"(


    )";

    const std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x:int, y:float):float -> x + y

            inline(a:12, b:14) + 5.22 / sum(x:2, y:3.26F)
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T11)
{
    const std::string output = R"(


    )";

    const std::string input = R"(
        fn mult(pp:float): float {return 1.0 }
        fn xptc(z:float): int {return 0 }

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:mult(pp:12.00F)) / xb
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T18)
{
    const std::string output = R"(


    )";

    const std::string input = R"(
        fn main() {
           //false ok
           let exprBool1:boolean = not 3 > 1

           //true ok
           let exprBool2:boolean = 3 > 1

           //true ok
           let exprBool3:boolean = 3 != 1

           //false
           let exprBool4:boolean = 3 == 1

           //false ok
           let exprBool5:boolean = 5 > 3 != (25 * 6) < 5 != (25 == 25)

           //true true ok
           let exprBool6:boolean = 5 > 3 != (25 * 6) < 5 != (25 == 25) or (32 /2) > 5

           let a:int = 12
           let b:float = 1.6

           //true ok
           let exprBool7:boolean = 5 > 3 != (a * 6) < 5 != (25 == b) or (32 /2) > a and 2 > 2

           // false ok
           let exprBool8:boolean = 5 > a != ((25 * 6) < a != 2) == (not (25 == 25))
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T19)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T21)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T22)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T23)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T24)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T25)
{
    const std::string output = R"(

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

TEST_F(HlIrTestCode, T26)
{
    const std::string output = R"(


    )";

    const std::string input = R"(


    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T27)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn main():void {
         let x:int = 3
         jump while_cond_0
         block while_cond_0:
         let var_0:int = 5
         let var_1:boolean = cmp LT x, var_0
         cond var_1 while_body_1, while_end_2
         block while_body_1:
         let z:int = 3
         let var_2:int = 3
         let var_3:boolean = cmp NEQ z, var_2
         cond var_3 then_4, else_5
         block then_4:
         let z:int = 55
         jump end_3
         block else_5:
         let var_4:boolean = false
         cond var_4 then_6, else_7
         block then_6:
         let op:int = 1254
         jump end_3
         block else_7:
         let pp:int = 665
         jump while_end_2
         block end_3:
         let var_5:int = 3
         let var_6:int = MULT z, var_5
         let n:int = var_6
         jump while_cond_0
         block while_end_2:
         let var_7:string = "Finalizou\n"
         call int printf(format:var_7)
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

TEST_F(HlIrTestCode, T28)
{
    const std::string output = R"(


    )";

    const std::string input = R"(


    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T29)
{
    const std::string output = R"(


    )";

    const std::string input = R"(


    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T30)
{
    const std::string output = R"(


    )";

    const std::string input = R"(


    )";

    runAnalysis(input, output);
}

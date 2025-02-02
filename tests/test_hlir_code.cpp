#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include "antlr4-runtime.h"

#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "../src/headers/Hlir.h"
#include "../src/headers/SemanticalAnalysis.h"
#include "../src/headers/HLIRGenerator.h"

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
                     [](unsigned char c)
                     { return !std::isspace(c); });

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

    std::string getHighLevelCode(std::string input)
    {
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticalAnalysis analysis(parser, std::move(std::make_unique<scope::ScopeManager>()));
        analysis.analyze();

        // Rewind
        tokens.seek(0);
        parser->reset();

        auto context = std::make_shared<hlir::Context>();
        hlir::HLIRGenerator hightLevelCodeGenerator(parser, context);
        const auto hlirCode = hightLevelCodeGenerator.generateCode();
        return hlirCode;
    }
};

//-----------------------------------------------------------
// TESTS FOR THE CLASS FunctionArgs
//-----------------------------------------------------------

TEST_F(HlIrTestCode, T1)
{
    std::string output = R"(
        fn soma(n:float,j:int):int { 
        call int gfn_soma_block(j:j)
        }

        fn gfn_soma_block(j:int):int { 
        let x:int = 25
        call int gfn_gfn_soma_block_block(j:j,x:x)
        }

        fn gfn_gfn_soma_block_block(j:int,x:int):int { 
        let var_1:int = 2
        let var_2:int = MULT var_1, j
        let var_3:int = MULT var_2, x
        let r:int = var_3
        let x:float = 25.25
        call int gfn_gfn_gfn_soma_block_block_block(n:14524.25D,j:j,x:x)
        }

        fn gfn_gfn_gfn_soma_block_block_block(n:double,j:int,x:float):int { 
        let var_1:int = 2
        let var_2:int = MULT var_1, j
        let var_3:float = var_2 int to float
        let var_4:float = MULT var_3, x
        let var_5:int = var_4 float to int
        let r:int = var_5
        }
    )";

    std::string input = R"(
        fn soma(n:float, j:int): int {

            let block:fn = ():int -> {
            let x:int = 25
               let block:fn = ():int -> {
                    let r:int = 2 * j * x
                    let x:float = 25.25
                    
                    let block:fn = (n:double):int -> {
                        let r:int = 2 * j * x
                    }

                    block(n:14524.25D)
                }
                block()
            }
            block()
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T2)
{
    std::string output = R"(
        fn soma():void { 
            let b:int = 12
            let x:int = b
            let var_1:int = 25
            let var_2:int = MULT x, var_1
            let var_3:int = PLUS b, var_2
        }
    )";

    std::string input = R"(
        fn soma() {
            let b:int = 12
            let x:int = b
            b + x * 25
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T3)
{
    std::string output = R"(
        fn teste():void { 
            let a:int = 25
            let b:int = 32
            let var_1:float = 1.25
            let var_2:float = a int to float
            let var_3:float = PLUS var_2, var_1
            let var_4:float = 2.36
            let var_5:float = b int to float
            let var_6:float = MULT var_5, var_4
            let var_7:float = PLUS var_3, var_6
            let var_8:float = a int to float
            let var_9:float = MINUS var_7, var_8
        }
    )";

    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:int = 32
            a + 1.25 + b * 2.36 - a
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T4)
{
    std::string output = R"(
        fn teste():void { 
            let a:int = 10
            let b:double = 20.00
            let c:int = 30
            let var_1:double = a int to double
            let var_2:double = PLUS var_1, b
            let var_3:double = c int to double
            let var_4:double = MULT var_2, var_3
            let var_5:double = a int to double
            let var_6:double = MINUS var_4, var_5
            let var_7:float = var_6 double to float
            let r:float = var_7
        }
    )";

    std::string input = R"(
        fn teste() {
            let a:int = 10
            let b:double = 20.00
            let c:int = 30
            let r:float = (a + b) * c - a
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T5)
{
    std::string output = R"(
        fn soma(x:int,b:int):void { 
            let var_1:float = 1.145
            let var_2:float = b int to float
            let var_3:float = MULT var_2, var_1
            let var_4:float = x int to float
            let var_5:float = PLUS var_4, var_3
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
    std::string output = R"(
        fn sub(ax:int,bx:int,nx:int):int { }

        fn soma():int { 
            let var_1:float = 32.25
            let var_2:int = call int sub(ax:1,bx:32,nx:25)
            let var_3:float = var_2 int to float
            let var_4:float = MULT var_1, var_3
        }

    )";

    std::string input = R"(
        fn sub(ax:int, bx:int, nx:int): int {}

        fn soma(): int {
            32.25 * sub(ax: 1, bx: 32, nx: 25)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T7)
{
    std::string output = R"(
        fn mult(n:int,p:float):float { }

        fn sub(ax:int,bx:float):int { }

        fn soma():int { 
            let x:float = 25.00
            let var_1:float = 32.25
            let var_3:float = call float mult(n:22,p:x)
            let var_2:int = call int sub(ax:1,bx:var_3)
            let var_4:float = var_2 int to float
            let var_5:float = MULT var_1, var_4
        }

    )";

    std::string input = R"(
        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            let x: float = 25.00
            32.25 * sub(ax: 1, bx: mult(n:22, p:x))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T8)
{
    std::string output = R"(
        fn mult(n:int,p:float):float { }

        fn sub(ax:int,bx:float):int { }

        fn soma():int { 
            let x:float = 25.00
            let var_1:float = 32.25
            let var_3:float = call float gfn_soma_inline(a:25,x:x)
            let var_4:float = call float mult(n:22,p:var_3)
            let var_2:int = call int sub(ax:1,bx:var_4)
            let var_5:float = var_2 int to float
            let var_6:float = MULT var_1, var_5
            }

            fn gfn_soma_inline(a:int,x:float):float { 
            let var_1:float = a int to float
            let var_2:float = MULT var_1, x
        }

    )";

    std::string input = R"(
        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            let x: float = 25.00
            let inline:fn = (a:int):float -> a * x
            32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:25)))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T9)
{
    std::string output = R"(
        fn mult(n:int,p:float):float { }

        fn sub(ax:int,bx:float):int { }

        fn soma():int { 
            let x:float = 25.00
            let var_1:float = 32.25
            let var_3:int = call int gfn_soma_block(a:25,x:x)
            let var_4:float = call float gfn_soma_inline(a:var_3,x:x)
            let var_5:float = call float mult(n:22,p:var_4)
            let var_2:int = call int sub(ax:1,bx:var_5)
            let var_6:float = var_2 int to float
            let var_7:float = MULT var_1, var_6
        }

        fn gfn_soma_block(a:int,x:float):int { }

        fn gfn_soma_inline(a:int,x:float):float { 
            let var_1:float = a int to float
            let var_2:float = MULT var_1, x
        }

    )";

    std::string input = R"(
        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            let x: float = 25.00
            
            let block:fn = (a:int):int -> {
            }

            let inline:fn = (a:int):float -> a * x
            32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:block(a:25))))
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T10)
{
    std::string output = R"(
        fn main():void { 
            let xb:int = 36
            let var_1:int = call int gfn_main_inline(a:12,b:14,xb:xb)
            let var_2:float = 5.22
            let var_3:float = call float gfn_main_sum(x:2,y:3.26F)
            let var_4:float = DIV var_2, var_3
            let var_5:float = var_1 int to float
            let var_6:float = PLUS var_5, var_4
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int { 
            let var_1:int = PLUS xb, b
            let var_2:int = MULT var_1, a
        }

        fn gfn_main_sum(x:int,y:float):float { 
            let var_1:float = x int to float
            let var_2:float = PLUS var_1, y
        }

    )";

    std::string input = R"(
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
    std::string output = R"(
        fn mult(pp:float):float { }

        fn xptc(z:float):int { }

        fn main():void { 
            let xb:int = 36
            let var_1:float = 5.22
            let var_2:int = call int gfn_main_inline(a:12,b:14,xb:xb)
            let var_3:float = call float gfn_main_sum(x:12,y:87)
            let var_4:float = var_2 int to float
            let var_5:float = MULT var_4, var_3
            let var_6:float = PLUS var_1, var_5
            let var_8:float = call float mult(pp:12.00F)
            let var_7:int = call int xptc(z:var_8)
            let var_9:int = DIV var_7, xb
            let var_10:float = var_9 int to float
            let var_11:float = MINUS var_6, var_10
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int { 
            let var_1:int = PLUS xb, b
            let var_2:int = MULT var_1, a
        }

        fn gfn_main_sum(x:int,y:int):float { 
            let var_1:float = 2.25
            let var_2:float = x int to float
            let var_3:float = PLUS var_1, var_2
            let var_4:float = y int to float
            let var_5:float = PLUS var_3, var_4
        }

    )";

    std::string input = R"(
        fn mult(pp:float): float {}
        fn xptc(z:float): int {}

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:mult(pp:12.00F)) / xb
        }

    )";

    runAnalysis(input, output);
}

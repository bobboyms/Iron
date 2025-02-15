#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include "antlr4-runtime.h"

#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "../src/headers/Hlir.h"
#include "../src/headers/SemanticAnalysis.h"
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

    static std::string getHighLevelCode(const std::string& input)
    {
        auto config = std::make_shared<config::Configuration>("compiler_config.yaml");

        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto const parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticAnalysis analysis(parser, std::make_unique<scope::ScopeManager>(),
                                        loadStringAsLines(input), config);

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
         let var_1:int = call int gfn_soma_block(j:j)
         return int var_1
        }

        fn gfn_soma_block(j:int):int {
         let x:int = 25
         let var_1:int = call int gfn_gfn_soma_block_block(j:j,x:x)
         return int var_1
        }

        fn gfn_gfn_soma_block_block(j:int,x:int):int {
         let var_1:int = 2
         let var_2:int = MULT var_1, j
         let var_3:int = MULT var_2, x
         let r:int = var_3
         let x:float = 25.25
         let var_5:double = 14524.25D
         let var_4:int = call int gfn_gfn_gfn_soma_block_block_block(n:var_5,j:j,x:x)
         return int var_4
        }

        fn gfn_gfn_gfn_soma_block_block_block(n:double,j:int,x:float):int {
         let var_1:int = 2
         let var_2:int = MULT var_1, j
         let var_3:float = var_2 int to float
         let var_4:float = MULT var_3, x
         let var_5:int = var_4 float to int
         let r:int = var_5
         return int r
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
                            return r
                        }

                        return block(n:14524.25D)
                    }
                    return block()
                }
            return block()
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T2)
{
    const std::string output = R"(
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
            let b:double = 20.00D
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

    const std::string input = R"(
        fn teste() {
            let a:int = 10
            let b:double = 20.00D
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
    const std::string output = R"(
        fn sub(ax:int,bx:int,nx:int):int {
         let var_1:int = 0
         return int var_1
        }

        fn soma():void {
         let var_1:float = 32.25
         let var_3:int = 1
         let var_4:int = 32
         let var_5:int = 25
         let var_2:int = call int sub(ax:var_3,bx:var_4,nx:var_5)
         let var_6:float = var_2 int to float
         let var_7:float = MULT var_1, var_6
        }

    )";

    std::string input = R"(
        fn sub(ax:int, bx:int, nx:int): int { return 0 }

        fn soma() {
            32.25 * sub(ax: 1, bx: 32, nx: 25)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T7)
{
    const std::string output = R"(
        fn mult(n:int,p:float):float {
         let var_1:float = 0.0
         return float var_1
        }

        fn sub(ax:int,bx:float):int {
         let var_1:int = 0
         return int var_1
        }

        fn soma():void {
         let x:float = 25.00
         let var_1:float = 32.25
         let var_3:int = 1
         let var_4:int = 22
         let var_5:float = call float mult(n:var_4,p:x)
         let var_2:int = call int sub(ax:var_3,bx:var_5)
         let var_6:float = var_2 int to float
         let var_7:float = MULT var_1, var_6
        }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int { return 0 }

        fn soma() {
            let x: float = 25.00
            32.25 * sub(ax: 1, bx: mult(n:22, p:x))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T8)
{
    std::string output = R"(
        fn mult(n:int,p:float):float {
         let var_1:float = 0.0
         return float var_1
        }

        fn sub(ax:int,bx:float):int {
         let var_1:int = 0
         return int var_1
        }

        fn soma():float {
         let x:float = 25.00
         let var_1:float = 32.25
         let var_3:int = 1
         let var_4:int = 22
         let var_5:int = 25
         let var_6:float = call float gfn_soma_inline(a:var_5,x:x)
         let var_7:float = call float mult(n:var_4,p:var_6)
         let var_2:int = call int sub(ax:var_3,bx:var_7)
         let var_8:float = var_2 int to float
         let var_9:float = MULT var_1, var_8
         return float var_9
        }

        fn gfn_soma_inline(a:int,x:float):float {
         let var_1:float = a int to float
         let var_2:float = MULT var_1, x
         return float var_2
        }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int {return 0 }

        fn soma(): float {
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
        fn mult(n:int,p:float):float {
         let var_1:float = 0.0
         return float var_1
        }

        fn sub(ax:int,bx:float):int {
         let var_1:int = 0
         return int var_1
        }

        fn soma():void {
         let x:float = 25.00
         let var_1:float = 32.25
         let var_3:int = 1
         let var_4:int = 22
         let var_5:int = 25
         let var_6:int = call int gfn_soma_block(a:var_5,x:x)
         let var_7:float = call float gfn_soma_inline(a:var_6,x:x)
         let var_8:float = call float mult(n:var_4,p:var_7)
         let var_2:int = call int sub(ax:var_3,bx:var_8)
         let var_9:float = var_2 int to float
         let var_10:float = MULT var_1, var_9
        }

        fn gfn_soma_block(a:int,x:float):int {
         let var_1:int = 0
         return int var_1
        }

        fn gfn_soma_inline(a:int,x:float):float {
         let var_1:float = a int to float
         let var_2:float = MULT var_1, x
         return float var_2
        }

    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0 }
        fn sub (ax:int, bx:float): int {return 0 }

        fn soma() {
            let x: float = 25.00

            let block:fn = (a:int):int -> {
                return 0
            }

            let inline:fn = (a:int):float -> a * x
            32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:block(a:25))))
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T10)
{
    const std::string output = R"(
        fn main():void {
         let xb:int = 36
         let var_2:int = 12
         let var_3:int = 14
         let var_1:int = call int gfn_main_inline(a:var_2,b:var_3,xb:xb)
         let var_4:float = 5.22
         let var_6:int = 2
         let var_7:float = 3.26F
         let var_5:float = call float gfn_main_sum(x:var_6,y:var_7)
         let var_8:float = DIV var_4, var_5
         let var_9:float = var_1 int to float
         let var_10:float = PLUS var_9, var_8
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int {
         let var_1:int = PLUS xb, b
         let var_2:int = MULT var_1, a
         return int var_2
        }

        fn gfn_main_sum(x:int,y:float):float {
         let var_1:float = x int to float
         let var_2:float = PLUS var_1, y
         return float var_2
        }

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
        fn mult(pp:float):float {
         let var_1:float = 1.0
         return float var_1
        }

        fn xptc(z:float):int {
         let var_1:int = 0
         return int var_1
        }

        fn main():void {
         let xb:int = 36
         let var_1:float = 5.22
         let var_3:int = 12
         let var_4:int = 14
         let var_2:int = call int gfn_main_inline(a:var_3,b:var_4,xb:xb)
         let var_6:int = 12
         let var_7:int = 87
         let var_5:float = call float gfn_main_sum(x:var_6,y:var_7)
         let var_8:float = var_2 int to float
         let var_9:float = MULT var_8, var_5
         let var_10:float = PLUS var_1, var_9
         let var_12:float = 12.00F
         let var_13:float = call float mult(pp:var_12)
         let var_11:int = call int xptc(z:var_13)
         let var_14:int = DIV var_11, xb
         let var_15:float = var_14 int to float
         let var_16:float = MINUS var_10, var_15
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int {
         let var_1:int = PLUS xb, b
         let var_2:int = MULT var_1, a
         return int var_2
        }

        fn gfn_main_sum(x:int,y:int):float {
         let var_1:float = 2.25
         let var_2:float = x int to float
         let var_3:float = PLUS var_1, var_2
         let var_4:float = y int to float
         let var_5:float = PLUS var_3, var_4
         return float var_5
        }

    )";

    std::string input = R"(
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

TEST_F(HlIrTestCode, T12)
{
    const std::string output = R"(
        fn teste():float {
         let var_1:float = 42.0
         return float var_1
        }

    )";

    const std::string input = R"(
        fn teste():float {
            return 42.0
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T13)
{
    const std::string output = R"(
        fn teste():int {
         let j:int = 56
         return int j
        }
    )";

    const std::string input = R"(

        fn teste():int {
            let j:int = 56
            return j
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T15)
{
    const std::string output = R"(
        fn teste():int {
         let j:int = 56
         let var_1:int = 25
         let var_2:int = PLUS j, var_1
         let var_3:int = 2
         let var_4:int = PLUS j, var_3
         let var_5:int = DIV var_2, var_4
         return int var_5
        }
    )";

    const std::string input = R"(
        fn teste():int {
            let j:int = 56
            return (j + 25) / (j + 2)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T16)
{
    const std::string output = R"(
        fn teste():double {
            let var_1:double = call double gfn_teste_inline()
            return double var_1
        }

        fn gfn_teste_inline():double {
            let var_1:double = 12.00D
            return double var_1
        }

    )";

    const std::string input = R"(
        fn teste():double {
            let inline:fn = ():double -> 12.00D
            return inline()
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T17)
{
    const std::string output = R"(
        fn teste():void {
         call void gfn_teste_inline()
        }

        fn gfn_teste_inline():void {
         let var_1:double = 12.00D
        }
    )";

    const std::string input = R"(
        fn teste() {
            let inline:fn = () -> 12.00D
            inline()
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T18)
{
    const std::string output = R"(


    )";

    const std::string input = R"(


    )";

    runAnalysis(input, output);
}

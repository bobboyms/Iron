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
        fn mult(n:int,p:float):float {
         let var_0:float = 0.0
         return float var_0
        }

        fn sub(ax:int,bx:float):int {
         let var_0:int = 0
         return int var_0
        }

        fn main():float {
         let x:float = 25.00
         let inline:fn = gfn_main_inline
         let var_0:float = 32.25
         let var_2:int = 1
         let var_3:int = 22
         let var_4:int = 25
         let var_5:float = call float inline(a:var_4,x:x)
         let var_6:float = call float mult(n:var_3,p:var_5)
         let var_1:int = call int sub(ax:var_2,bx:var_6)
         let var_7:float = var_1 int to float
         let var_8:float = MULT var_0, var_7
         return float var_8
        }

        fn gfn_main_inline(a:int,x:float):float {
         let var_0:float = a int to float
         let var_1:float = MULT var_0, x
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

TEST_F(HlIrTestCode, T9)
{
    const std::string output = R"(
        fn mult(n:int,p:float):float {
         let var_0:float = 0.0
         return float var_0
        }

        fn sub(ax:int,bx:float):int {
         let var_0:int = 0
         return int var_0
        }

        fn main():float {
         let x:float = 25.00
         let inline:fn = gfn_main_inline
         let var_0:float = 32.25
         let var_2:int = 1
         let var_3:int = 22
         let var_4:int = 25
         let var_5:float = call float inline(a:var_4,x:x)
         let var_6:float = call float mult(n:var_3,p:var_5)
         let var_1:int = call int sub(ax:var_2,bx:var_6)
         let var_7:float = var_1 int to float
         let var_8:float = MULT var_0, var_7
         return float var_8
        }

        fn gfn_main_inline(a:int,x:float):float {
         let var_0:float = a int to float
         let var_1:float = MULT var_0, x
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

TEST_F(HlIrTestCode, T10)
{
    const std::string output = R"(
        fn main():void {
         let xb:int = 36
         let inline:fn = gfn_main_inline
         let sum:fn = gfn_main_sum
         let var_1:int = 12
         let var_2:int = 14
         let var_0:int = call int inline(a:var_1,b:var_2,xb:xb)
         let var_3:float = 5.22
         let var_5:int = 2
         let var_6:float = 3.26F
         let var_4:float = call float sum(x:var_5,y:var_6)
         let var_7:float = DIV var_3, var_4
         let var_8:float = var_0 int to float
         let var_9:float = PLUS var_8, var_7
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int {
         let var_0:int = PLUS xb, b
         let var_1:int = MULT var_0, a
         return int var_1
        }

        fn gfn_main_sum(x:int,y:float):float {
         let var_0:float = x int to float
         let var_1:float = PLUS var_0, y
         return float var_1
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
         let var_0:float = 1.0
         return float var_0
        }

        fn xptc(z:float):int {
         let var_0:int = 0
         return int var_0
        }

        fn main():void {
         let xb:int = 36
         let inline:fn = gfn_main_inline
         let sum:fn = gfn_main_sum
         let var_0:float = 5.22
         let var_2:int = 12
         let var_3:int = 14
         let var_1:int = call int inline(a:var_2,b:var_3,xb:xb)
         let var_5:int = 12
         let var_6:int = 87
         let var_4:float = call float sum(x:var_5,y:var_6)
         let var_7:float = var_1 int to float
         let var_8:float = MULT var_7, var_4
         let var_9:float = PLUS var_0, var_8
         let var_11:float = 12.00F
         let var_12:float = call float mult(pp:var_11)
         let var_10:int = call int xptc(z:var_12)
         let var_13:int = DIV var_10, xb
         let var_14:float = var_13 int to float
         let var_15:float = MINUS var_9, var_14
        }

        fn gfn_main_inline(a:int,b:int,xb:int):int {
         let var_0:int = PLUS xb, b
         let var_1:int = MULT var_0, a
         return int var_1
        }

        fn gfn_main_sum(x:int,y:int):float {
         let var_0:float = 2.25
         let var_1:float = x int to float
         let var_2:float = PLUS var_0, var_1
         let var_3:float = y int to float
         let var_4:float = PLUS var_2, var_3
         return float var_4
        }

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
        fn main():int {
         let j:int = 56
         let var_0:int = 25
         let var_1:int = PLUS j, var_0
         let var_2:int = 2
         let var_3:int = PLUS j, var_2
         let var_4:int = DIV var_1, var_3
         return int var_4
        }
    )";

    const std::string input = R"(
        fn main():int {
            let j:int = 56
            return (j + 25) / (j + 2)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T16)
{
    const std::string output = R"(
        fn main():double {
         let inline:fn = gfn_main_inline
         let var_0:double = call double inline()
         return double var_0
        }

        fn gfn_main_inline():double {
         let var_0:double = 12.00D
         return double var_0
        }
    )";

    const std::string input = R"(
        fn main():double {
            let inline:fn = ():double -> 12.00D
            return inline()
        }

    )";

    runAnalysis(input, output);
}

TEST_F(HlIrTestCode, T18)
{
    const std::string output = R"(
        fn main():void {
         let var_0:boolean = true
         let var_1:int = 3
         let var_2:int = 1
         let var_3:boolean = cmp GT var_1, var_2
         let var_4:boolean = NOT var_3, var_0
         let exprBool1:boolean = var_4
         let var_5:int = 3
         let var_6:int = 1
         let var_7:boolean = cmp GT var_5, var_6
         let exprBool2:boolean = var_7
         let var_8:int = 3
         let var_9:int = 1
         let var_10:boolean = cmp NEQ var_8, var_9
         let exprBool3:boolean = var_10
         let var_11:int = 3
         let var_12:int = 1
         let var_13:boolean = cmp EQEQ var_11, var_12
         let exprBool4:boolean = var_13
         let var_14:int = 5
         let var_15:int = 3
         let var_16:boolean = cmp GT var_14, var_15
         let var_17:int = 25
         let var_18:int = 6
         let var_19:int = MULT var_17, var_18
         let var_20:boolean = var_19 int to boolean
         let var_21:boolean = cmp NEQ var_16, var_20
         let var_22:int = 5
         let var_23:boolean = var_22 int to boolean
         let var_24:boolean = cmp LT var_21, var_23
         let var_25:int = 25
         let var_26:int = 25
         let var_27:boolean = cmp EQEQ var_25, var_26
         let var_28:boolean = cmp NEQ var_24, var_27
         let exprBool5:boolean = var_28
         let var_29:int = 5
         let var_30:int = 3
         let var_31:boolean = cmp GT var_29, var_30
         let var_32:int = 25
         let var_33:int = 6
         let var_34:int = MULT var_32, var_33
         let var_35:boolean = var_34 int to boolean
         let var_36:boolean = cmp NEQ var_31, var_35
         let var_37:int = 5
         let var_38:boolean = var_37 int to boolean
         let var_39:boolean = cmp LT var_36, var_38
         let var_40:int = 25
         let var_41:int = 25
         let var_42:boolean = cmp EQEQ var_40, var_41
         let var_43:boolean = cmp NEQ var_39, var_42
         let var_44:int = 32
         let var_45:int = 2
         let var_46:int = DIV var_44, var_45
         let var_47:int = 5
         let var_48:boolean = cmp GT var_46, var_47
         let var_49:boolean = OR var_43, var_48
         let exprBool6:boolean = var_49
         let a:int = 12
         let b:float = 1.6
         let var_50:int = 5
         let var_51:int = 3
         let var_52:boolean = cmp GT var_50, var_51
         let var_53:int = 6
         let var_54:int = MULT a, var_53
         let var_55:boolean = var_54 int to boolean
         let var_56:boolean = cmp NEQ var_52, var_55
         let var_57:int = 5
         let var_58:boolean = var_57 int to boolean
         let var_59:boolean = cmp LT var_56, var_58
         let var_60:int = 25
         let var_61:float = var_60 int to float
         let var_62:boolean = cmp EQEQ var_61, b
         let var_63:boolean = cmp NEQ var_59, var_62
         let var_64:int = 32
         let var_65:int = 2
         let var_66:int = DIV var_64, var_65
         let var_67:boolean = cmp GT var_66, a
         let var_68:int = 2
         let var_69:int = 2
         let var_70:boolean = cmp GT var_68, var_69
         let var_71:boolean = AND var_67, var_70
         let var_72:boolean = OR var_63, var_71
         let exprBool7:boolean = var_72
         let var_73:int = 5
         let var_74:boolean = cmp GT var_73, a
         let var_75:int = 25
         let var_76:int = 6
         let var_77:int = MULT var_75, var_76
         let var_78:boolean = cmp LT var_77, a
         let var_79:int = 2
         let var_80:boolean = var_79 int to boolean
         let var_81:boolean = cmp NEQ var_78, var_80
         let var_82:boolean = cmp NEQ var_74, var_81
         let var_83:boolean = true
         let var_84:int = 25
         let var_85:int = 25
         let var_86:boolean = cmp EQEQ var_84, var_85
         let var_87:boolean = NOT var_86, var_83
         let var_88:boolean = cmp EQEQ var_82, var_87
         let exprBool8:boolean = var_88
        }

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
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn,a:int,b:int):int {
         let var_0:int = call int func(a:a,b:b)
         return int var_0
        }

        fn main():void {
         let inline:fn = gfn_main_inline
         let var_0:string = "result:%u\n"
         let var_1:int = 2
         let var_2:int = 3
         let var_3:int = call int sum(func:inline,a:var_1,b:var_2)
         call int printf(format:var_0,r:var_3)
        }

        fn gfn_main_inline(a:int,b:int):int {
         let var_0:int = MULT a, b
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

TEST_F(HlIrTestCode, T21)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn,c:int):void {
         let var_0:int = 2
         let r:int = call int func(a:c,b:var_0)
         let var_1:string = "result: %u\n"
         call int printf(format:var_1,r:r)
        }

        fn sub(a:int,b:int):int {
         let var_0:int = MINUS a, b
         return int var_0
        }

        fn main():void {
         let var_0:int = 10
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

TEST_F(HlIrTestCode, T22)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sum(func:fn,p:int):int {
         let inline:fn = gfn_sum_inline
         let var_1:int = call int inline(x:p,p:p)
         let var_0:int = call int func(a:var_1)
         return int var_0
        }

        fn gfn_sum_inline(x:int,p:int):int {
         let var_0:int = 2
         let var_1:int = MULT x, var_0
         let var_2:int = MULT var_1, p
         return int var_2
        }

        fn main():void {
         let inline:fn = gfn_main_inline
         let var_0:string = "result %u\n"
         let var_1:int = 3
         let var_2:int = call int sum(func:inline,p:var_1)
         call int printf(format:var_0,r:var_2)
        }

        fn gfn_main_inline(a:int):int {
         let var_0:int = 8
         let var_1:int = MULT a, var_0
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

TEST_F(HlIrTestCode, T23)
{
    const std::string output = R"(
    extern C fn printf(format:ptr char, ...):int

    fn sum(func:fn,p:int):int {
     let var_0:int = call int func(a:p)
     return int var_0
    }

    fn main():void {
     let inline:fn = gfn_main_inline
     let var_0:string = "result %u\n"
     let var_1:int = 3
     let var_2:int = call int sum(func:inline,p:var_1)
     call int printf(format:var_0,r:var_2)
    }

    fn gfn_main_inline(a:int):int {
     let var_0:int = 8
     let var_1:int = MULT a, var_0
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

TEST_F(HlIrTestCode, T24)
{
    const std::string output = R"(
        extern C fn printf(format:ptr char, ...):int

        fn sub(a:int):int {
         let var_0:int = 2
         let var_1:int = MINUS a, var_0
         return int var_1
        }

        fn sum(p:int):int {
         let block:fn = gfn_sum_block
         let var_1:int = 3
         let var_0:int = call int block(x:var_1,p:p)
         return int var_0
        }

        fn gfn_sum_block(x:int,p:int):int {
         let var_0:int = call int sub(a:p)
         let var_1:int = MULT var_0, x
         return int var_1
        }

        fn main():void {
         let var_0:string = "resutl: %u\n"
         let var_1:int = 3
         let var_2:int = call int sum(p:var_1)
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

TEST_F(HlIrTestCode, T25)
{
    const std::string output = R"(
    extern C fn printf(format:ptr char, ...):int

    fn sum(sub:fn,p:int):int {
     let block:fn = gfn_sum_block
     let var_1:int = 3
     let var_0:int = call int block(x:var_1,sub:sub,p:p)
     return int var_0
    }

    fn gfn_sum_block(x:int,sub:fn,p:int):int {
     let var_0:int = call int sub(a:p)
     let var_1:int = MULT var_0, x
     return int var_1
    }

    fn main():void {
     let inline:fn = gfn_main_inline
     let var_0:string = "resutl: %u\n"
     let var_1:int = 3
     let var_2:int = call int sum(sub:inline,p:var_1)
     call int printf(format:var_0,r:var_2)
    }

    fn gfn_main_inline(a:int):int {
     let var_0:int = 2
     let var_1:int = MINUS a, var_0
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

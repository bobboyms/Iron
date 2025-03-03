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

TEST_F(HlIrTestCode, T9)
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

TEST_F(HlIrTestCode, T10)
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

TEST_F(HlIrTestCode, T11)
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

TEST_F(HlIrTestCode, T18)
{
    const std::string output = R"(
        fn main():void {
            var_1:boolean = true
            var_2:int = 3
            var_3:int = 1
            var_4:boolean = cmp GT var_2, var_3
            var_5:boolean = NOT var_4, var_1
            var_0:boolean = var_5
            var_7:int = 3
            var_8:int = 1
            var_9:boolean = cmp GT var_7, var_8
            var_6:boolean = var_9
            var_11:int = 3
            var_12:int = 1
            var_13:boolean = cmp NEQ var_11, var_12
            var_10:boolean = var_13
            var_15:int = 3
            var_16:int = 1
            var_17:boolean = cmp EQEQ var_15, var_16
            var_14:boolean = var_17
            var_19:int = 5
            var_20:int = 3
            var_21:boolean = cmp GT var_19, var_20
            var_22:int = 25
            var_23:int = 6
            var_24:int = MULT var_22, var_23
            var_25:boolean = var_24 int to boolean
            var_26:boolean = cmp NEQ var_21, var_25
            var_27:int = 5
            var_28:boolean = var_27 int to boolean
            var_29:boolean = cmp LT var_26, var_28
            var_30:int = 25
            var_31:int = 25
            var_32:boolean = cmp EQEQ var_30, var_31
            var_33:boolean = cmp NEQ var_29, var_32
            var_18:boolean = var_33
            var_35:int = 5
            var_36:int = 3
            var_37:boolean = cmp GT var_35, var_36
            var_38:int = 25
            var_39:int = 6
            var_40:int = MULT var_38, var_39
            var_41:boolean = var_40 int to boolean
            var_42:boolean = cmp NEQ var_37, var_41
            var_43:int = 5
            var_44:boolean = var_43 int to boolean
            var_45:boolean = cmp LT var_42, var_44
            var_46:int = 25
            var_47:int = 25
            var_48:boolean = cmp EQEQ var_46, var_47
            var_49:boolean = cmp NEQ var_45, var_48
            var_50:int = 32
            var_51:int = 2
            var_52:int = DIV var_50, var_51
            var_53:int = 5
            var_54:boolean = cmp GT var_52, var_53
            var_55:boolean = OR var_49, var_54
            var_34:boolean = var_55
            var_56:int = 12
            var_57:float = 1.6
            var_59:int = 5
            var_60:int = 3
            var_61:boolean = cmp GT var_59, var_60
            var_62:int = 6
            var_63:int = MULT var_56, var_62
            var_64:boolean = var_63 int to boolean
            var_65:boolean = cmp NEQ var_61, var_64
            var_66:int = 5
            var_67:boolean = var_66 int to boolean
            var_68:boolean = cmp LT var_65, var_67
            var_69:int = 25
            var_70:float = var_69 int to float
            var_71:boolean = cmp EQEQ var_70, var_57
            var_72:boolean = cmp NEQ var_68, var_71
            var_73:int = 32
            var_74:int = 2
            var_75:int = DIV var_73, var_74
            var_76:boolean = cmp GT var_75, var_56
            var_77:int = 2
            var_78:int = 2
            var_79:boolean = cmp GT var_77, var_78
            var_80:boolean = AND var_76, var_79
            var_81:boolean = OR var_72, var_80
            var_58:boolean = var_81
            var_83:int = 5
            var_84:boolean = cmp GT var_83, var_56
            var_85:int = 25
            var_86:int = 6
            var_87:int = MULT var_85, var_86
            var_88:boolean = cmp LT var_87, var_56
            var_89:int = 2
            var_90:boolean = var_89 int to boolean
            var_91:boolean = cmp NEQ var_88, var_90
            var_92:boolean = cmp NEQ var_84, var_91
            var_93:boolean = true
            var_94:int = 25
            var_95:int = 25
            var_96:boolean = cmp EQEQ var_94, var_95
            var_97:boolean = NOT var_96, var_93
            var_98:boolean = cmp EQEQ var_92, var_97
            var_82:boolean = var_98
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

TEST_F(HlIrTestCode, T21)
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

TEST_F(HlIrTestCode, T22)
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

TEST_F(HlIrTestCode, T23)
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

TEST_F(HlIrTestCode, T24)
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

TEST_F(HlIrTestCode, T25)
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

TEST_F(HlIrTestCode, T27)
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

TEST_F(HlIrTestCode, T28)
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

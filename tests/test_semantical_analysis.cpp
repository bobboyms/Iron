#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>

// Ajuste os includes conforme a organização do seu projeto
#include "../src/headers/SemanticalAnalysis.h"
#include "../src/headers/Exceptions.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "antlr4-runtime.h" // Removida a barra '/'

// Fixture de teste
class SemanticalAnalysisTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Cria um gerenciador de escopos
        scopeManager = std::make_unique<scope::ScopeManager>();
    }

    void runAnalysis(const std::string &input)
    {
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_unique<IronParser>(&tokens);
        semanticalAnalysis = std::make_unique<iron::SemanticalAnalysis>(std::move(parser), std::move(scopeManager), loadStringAsLines(input));

        // Executa a análise semântica
        semanticalAnalysis->analyze();
    }

    std::vector<std::string> loadStringAsLines(const std::string &code)
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

    std::unique_ptr<scope::ScopeManager> scopeManager;
    std::unique_ptr<iron::SemanticalAnalysis> semanticalAnalysis;
};

TEST_F(SemanticalAnalysisTest, T1)
{
    std::string input = R"(
        fn main() {
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T2)
{
    std::string input = R"(
        fn main():int {
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T3)
{
    std::string input = R"(
        fn main():int {
        }

        fn main() {
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionRedefinitionException);
}

TEST_F(SemanticalAnalysisTest, T4)
{
    std::string input = R"(
        fn main():int {
            let x:int = 25
            let b:float = 25.00
        }

    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T5)
{
    std::string input = R"(
        fn main():int {
            let x:int = 25
            let x:float = 25.00
        }

    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableRedefinitionException);
}

TEST_F(SemanticalAnalysisTest, T6)
{
    std::string input = R"(
        fn main():int {
            let x:int
        }

    )";

    EXPECT_THROW(runAnalysis(input), iron::UninitializedVariableException);
}

TEST_F(SemanticalAnalysisTest, T7)
{
    std::string input = R"(
        fn main() {
            let x:int = 25
            let y:float = 25.00
            let z:double = 250.00D
            let d:string = "Olá mundo doido!"
        }

    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T8)
{
    std::string input = R"(
        fn main() {
            let x:int = 25.00
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T9)
{
    std::string input = R"(
        fn main() {
            let y:float = 25
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T10)
{
    std::string input = R"(
        fn main() {
            let z:double = 250.00
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T11)
{
    std::string input = R"(
        fn main() {
            let d:string = 2
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T12)
{
    std::string input = R"(
        fn teste() {
            x
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T13)
{
    std::string input = R"(
        fn teste() {
            x = 10
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T14)
{
    std::string input = R"(
        fn teste() {
            let x:int = b
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T15)
{
    std::string input = R"(
        fn soma() {
            let b:int = 12
            let x:int = b
            b + x * 25
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T16)
{
    std::string input = R"(
        fn teste() {
            let b:int = 12
            let x:int = b
            25 + x * b * x
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T17)
{
    std::string input = R"(
        fn teste() {
            let b:int = 12
            let x:int = b
            25 + x * x * c
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T18)
{
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:int = 32
            let c:int = 28
            let d:int = 15
            let e:string = "olá mundo"
            (a + b * (c + d) - e)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T19)
{
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:string = "32"
            let c:int = 28
            let d:int = 15
            let e:string = "olá mundo"
            (a + b * (c + d) - e)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T20)
{
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:double = 32.26D
            a + 1.25 + b * 2.36 - a
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T21)
{
    std::string input = R"(
        fn teste() {
            (10 * 1.36 / (250.1254D - 25) + 28)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T22)
{
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma(): int {
            let x: int = 10
            x + sub()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T23)
{
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma(): int {
            let y: string = "hello"
            y * sub()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T24)
{
    std::string input = R"(
        fn soma(x:int, b:int, n:string) {
            x + b * z
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T25)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}

        fn main() {
            sub(a:10,p:5) * 36
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionArgNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T26)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}

        fn main() {
            sub(a:10,b:5) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T27)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}

        fn main() {
            sub(a:10,b:5.00) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T28)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}

        fn main(x:int) {
            sub(a:10,b:x) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T29)
{
    std::string input = R"(
        fn sub(a:float, b:int):int {}

        fn main(x:int) {
            let a:float = 6.23
            sub(a:a,b:x) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T30)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}

        fn main() {
            sub(a:10,b:p) * 8958.12554D
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T31)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div():int {}

        fn main() {
            sub(a:10,b:div()) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T32)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div():float {}

        fn main() {
            sub(a:10,b:div()) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T33)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div(d:double):int {}

        fn main() {
            sub(a:10,b:div(d:254.022D)) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T34)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div(d:double):int {}
        fn mult(x:float):double {}

        fn main() {
            sub(a:10,b:div(d:mult(x:15.0))) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T35)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div(d:double):float {}

        fn main() {
            sub(a:10,b:div(d:254.022D)) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T36)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div(d:double):int {}
        fn mult(x:float):double {}

        fn main() {
            sub(a:10,b:div(d:mult(x:15))) / 15
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T37)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {}
        fn div(d:double):int {}
        fn mult(x:float):double {}

        fn main(z:float) {
            sub(a:10,b:div(d:mult(x:z))) / 15
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T38)
{
    std::string input = R"(
        fn addOne(): int {
            return 1
        }

        fn doubleValue(num: int): int {
            return num * 2
        }

        fn main(): int {
            let base: int = 5
            return doubleValue(num:base) + addOne()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T39)
{
    std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }
                block(a:10,x:20)
            }

            block(a:10,x:30)

        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T40)
{
    std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }
                block(a:10,x:20.25)
            }

            block(a:10,x:30)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T41)
{
    std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }
                block(a:10,x:20)
            }

            block(a:10,x:30.5)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T42)
{
    std::string input = R"(
        fn main() {
            // let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }
                block(a:10,x:20)
            }

            block(a:10,x:30.5)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T43)
{
    std::string input = R"(
        fn main() {
            let p:string = "16"
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }
                block(a:10,x:20)
            }

            block(a:10,x:30.5)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T44)
{
    std::string input = R"(
        fn sub(a:int):int {}

        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }
                block(a:10,x:sub(a:25))
            }

            block(a:10,x:30)

        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T45)
{
    std::string input = R"(
        fn sub(ax:int, bx:int): int {}

        fn soma(): int {
            let y: string = "hello"
            32.25 * sub(ax: 1, nx: 25)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionArgNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T46)
{
    std::string input = R"(
        fn sub(ax:int, bx:int, nx:int): int {}

        fn soma(): int {
            32.25 * sub(ax: 1, bx: 32, nx: 25)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T47)
{
    std::string input = R"(
        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            32.25 * sub(ax: 1, bx: 25.32D)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T48)
{
    std::string input = R"(
        fn sub(ax:int, bx:float): int {}

        fn soma(n:float): int {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: n)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T49)
{
    std::string input = R"(
        fn sub(ax:int, bx:float): int {}

        fn soma(n:float): int {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: x)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T50)
{
    std::string input = R"(
        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: n)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, T51)
{
    std::string input = R"(
        fn sub(ax:int, bx:int): int {}

        fn soma(): int {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T52)
{
    std::string input = R"(
        fn sub(ax:double, bx:int): int {}

        fn soma(): int {
            let x: int = 25
            32.25 * sub(ax: 1, bx: x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T53)
{
    std::string input = R"(
        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            32.25 * sub(ax: 1, bx: mult(n:22, p:22.25D))
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T54)
{
    std::string input = R"(
        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            32.25 * sub(ax: 1, bx: mult(n:22, p:25))
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, T55)
{
    std::string input = R"(
        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            let x: float = 25.00
            32.25 * sub(ax: 1, bx: mult(n:22, p:x))
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T56)
{
    std::string input = R"(
        fn main() {
            let inline: fn = (a: int, b: int) -> a + b
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T57)
{
    std::string input = R"(
        fn main() {
            let inline: fn = (a: int, b: int) -> a + b
            inline(a:12, b:14)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T58)
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

TEST_F(SemanticalAnalysisTest, T59)
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

TEST_F(SemanticalAnalysisTest, T60)
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

TEST_F(SemanticalAnalysisTest, T61)
{
    std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x:int, y:float):float -> x + y

            inline(a:12, b:14) + 5.22 / sum(x:2, y:3.26F)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T62)
{
    std::string input = R"(
        fn xptc(): int {
        }

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T63)
{
    std::string input = R"(
        fn xptc(z:int): int {
        }

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:32) / xb
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T64)
{
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

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, T65)
{
    std::string input = R"(
        fn sub(x:int, y:int):int {}

        fn main() {
            let add:fn = (pp:int):int -> pp + 32
            let inline:fn = (a:int,b:float, c:boolean):int -> a + b
            sub(x:12, y:add(pp:25)) * inline(a:32, c:false)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
}

TEST_F(SemanticalAnalysisTest, T66)
{
    std::string input = R"(
        fn adicionar(a:int, b:int): int {
            return a + b
        }

        fn main() {
            let soma: int = adicionar(a: 5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
}

TEST_F(SemanticalAnalysisTest, T67)
{
    std::string input = R"(
        fn sub(x:int, y:int):int {}

        fn main() {
            let add:fn = (pp:int):int -> pp + 32
            let inline:fn = (a:int,b:float, c:boolean):int -> a + b
            sub(x:12, y:add(pp:25)) * inline(b:25.00F,a:32, c:false)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticalAnalysisTest, T68)
{
    std::string input = R"(
        fn main() {
            let inline:fn = (a:int, b:float, c:boolean):int -> a + b
            inline(c:true, a:32, b:25.00F)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticalAnalysisTest, T69)
{
    std::string input = R"(
        fn multiply(x:int, y:float):float {}

        fn main() {
            multiply(y:25.00F, x:10)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticalAnalysisTest, T70)
{
    std::string input = R"(
        fn sub(a:int, b:int, c:boolean):int {}

        fn main() {
            let x:int = 10
            let y:int = 20
            sub(b:y, c:false, a:x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticalAnalysisTest, T71)
{
    std::string input = R"(
        fn addOne(n:int):int {
            return n + 1
        }

        fn doubleValue(x:int, y:int):int {}

        fn main() {
            doubleValue(y:addOne(n:2), x:5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticalAnalysisTest, T72)
{
    std::string input = R"(
        fn value():int{
            25
        }
        fn main() {
            let blockFn : fn = (a:int, c:int):int ->{}
            (blockFn(a:32, c:25) * (36 / value()))
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

// Teste 1: Redeclaração de variáveis em escopos aninhados
TEST_F(SemanticalAnalysisTest, T73)
{
    std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {}
                    let result:float =  block(a:12, b:12.26) * x
                }
                let result:float =  27 * block(a:12, b:12.26)
            }
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

// Teste 2: Uso de variável indefinida lança exceção
TEST_F(SemanticalAnalysisTest, T74)
{
    std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {}
                    let result:float =  block(a:12, b:12.26) * xt
                }
                let result:float =  block(a:12, b:12.26)
            }
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

// Teste 3: Declarações de funções aninhadas com chamadas de funções
TEST_F(SemanticalAnalysisTest, T75)
{
    std::string input = R"(
        fn sub(a:int):int {}

        fn main() {
            let p:string = "16"
            let inline:fn = (a:int, b:int):int -> a * b

            let block2:fn = (a:int, x:int):int -> {
                    let p:int = 12 
                    let r:int = a * x
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - p
                    }
                }

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - 10
                    let block:fn = (a:int, x:int):int -> {
                        ((a * x) / r) - 20 * inline(a:a,b:x)
                    }
                }

                block(a:10,x:block2(a:25, x:sub(a:12)))
            }

            (block(a:10,x:30) - block2(a:25, x:sub(a:12)) * 2.98) / sub(a:15)

        }

    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>

// Ajuste os includes conforme a organização do seu projeto
#include "../src/headers/Exceptions.h"
#include "../src/headers/SemanticAnalysis.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "antlr4-runtime.h" // Removida a barra '/'

// Fixture de teste
class SemanticAnalysisTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        scopeManager = std::make_unique<scope::ScopeManager>();
    }

    void runAnalysis(const std::string &input)
    {
        auto config = std::make_shared<config::Configuration>("compiler_config.yaml");

        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_unique<IronParser>(&tokens);
        semanticAnalysis = std::make_unique<iron::SemanticAnalysis>(std::move(parser), std::move(scopeManager),
                                                                    loadStringAsLines(input), config);

        // Executa a análise semântica
        semanticAnalysis->analyze();
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

    std::unique_ptr<scope::ScopeManager> scopeManager;
    std::unique_ptr<iron::SemanticAnalysis> semanticAnalysis;
};

TEST_F(SemanticAnalysisTest, T1)
{
    const std::string input = R"(
        fn main() {
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T2)
{
    const std::string input = R"(
        fn main():int {
            return 0
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T3)
{
    const std::string input = R"(
        fn main():int {
        }

        fn main() {
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionRedefinitionException);
}

TEST_F(SemanticAnalysisTest, T4)
{
    const std::string input = R"(
        fn main():int {
            let x:int = 25
            let b:float = 25.00
            return x
        }

    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T5)
{
    const std::string input = R"(
        fn main():int {
            let x:int = 25
            let x:float = 25.00
        }

    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableRedefinitionException);
}

TEST_F(SemanticAnalysisTest, T6)
{
    std::string input = R"(
        fn main():int {
            let x:int
        }

    )";

    EXPECT_THROW(runAnalysis(input), iron::UninitializedVariableException);
}

TEST_F(SemanticAnalysisTest, T7)
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

TEST_F(SemanticAnalysisTest, T8)
{
    std::string input = R"(
        fn main() {
            let x:int = 25.00
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T9)
{
    std::string input = R"(
        fn main() {
            let y:float = 25
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T10)
{
    std::string input = R"(
        fn main() {
            let z:double = 250.00
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T11)
{
    std::string input = R"(
        fn main() {
            let d:string = 2
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T12)
{
    std::string input = R"(
        fn teste() {
            x
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T13)
{
    std::string input = R"(
        fn teste() {
            x = 10
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T14)
{
    std::string input = R"(
        fn teste() {
            let x:int = b
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T15)
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

TEST_F(SemanticAnalysisTest, T16)
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

TEST_F(SemanticAnalysisTest, T17)
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

TEST_F(SemanticAnalysisTest, T18)
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

TEST_F(SemanticAnalysisTest, T19)
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

TEST_F(SemanticAnalysisTest, T20)
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

TEST_F(SemanticAnalysisTest, T21)
{
    std::string input = R"(
        fn teste() {
            (10 * 1.36 / (250.1254D - 25) + 28)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T22)
{
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma() {
            let x: int = 10
            x + sub()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T23)
{
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma() {
            let y: string = "hello"
            y * sub()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T24)
{
    std::string input = R"(
        fn soma(x:int, b:int, n:string) {
            x + b * z
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T25)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 5}

        fn main() {
            sub(a:10,p:5) * 36
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionArgNotFoundException);
}

TEST_F(SemanticAnalysisTest, T26)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 22 }

        fn main() {
            sub(a:10,b:5) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T27)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}

        fn main() {
            sub(a:10,b:5.00) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T28)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0 }

        fn main(x:int) {
            sub(a:10,b:x) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T29)
{
    std::string input = R"(
        fn sub(a:float, b:int):int { return 0}

        fn main(x:int) {
            let a:float = 6.23
            sub(a:a,b:x) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T30)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0 }

        fn main() {
            sub(a:10,b:p) * 8958.12554D
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T31)
{
    std::string input = R"(
        fn sub(a:int, b:int):int {  return 0 }
        fn div():int { return 0 }

        fn main() {
            sub(a:10,b:div()) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T32)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div():float { return 0}

        fn main() {
            sub(a:10,b:div()) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T33)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):int { return 0}

        fn main() {
            sub(a:10,b:div(d:254.022D)) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T34)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):int { return 0}
        fn mult(x:float):double { return 0.0D}

        fn main() {
            sub(a:10,b:div(d:mult(x:15.0))) * 36.69
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T35)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):float { return 0.0 }

        fn main() {
            sub(a:10,b:div(d:254.022D)) * 36.69
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T36)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):int { return 0}
        fn mult(x:float):double { return 0.0D}

        fn main() {
            sub(a:10,b:div(d:mult(x:15))) / 15
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T37)
{
    std::string input = R"(
        fn sub(a:int, b:int):int { return 0}
        fn div(d:double):int { return 0}
        fn mult(x:float):double { return 0.0D}

        fn main(z:float) {
            sub(a:10,b:div(d:mult(x:z))) / 15
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T38)
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

TEST_F(SemanticAnalysisTest, T39)
{
    const std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }

                    return r
                }
                return block(a:10,x:20)
            }

            block(a:10,x:30)

        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T40)
{
    std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:20.25)
            }

            block(a:10,x:30)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T41)
{
    const std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:20)
            }

            block(a:10,x:30.5)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T42)
{
    std::string input = R"(
        fn main() {
            // let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:20)
            }

            block(a:10,x:30.5)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T43)
{
    const std::string input = R"(
        fn main() {
            let p:string = "16"
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return 25

                }
                return block(a:10,x:20)
            }

            block(a:10,x:30.5)

        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T44)
{
    const std::string input = R"(
        fn sub(a:int):int { return 0 }

        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:sub(a:25))
            }

            block(a:10,x:30)

        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T45)
{
    const std::string input = R"(
        fn sub(ax:int, bx:int): int {return 0}

        fn soma() {
            let y: string = "hello"
            32.25 * sub(ax: 1, nx: 25)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionArgNotFoundException);
}

TEST_F(SemanticAnalysisTest, T46)
{
    std::string input = R"(
        fn sub(ax:int, bx:int, nx:int): int {return 0}

        fn soma() {
            32.25 * sub(ax: 1, bx: 32, nx: 25)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T47)
{
    const std::string input = R"(
        fn sub(ax:int, bx:float): int {return 0}

        fn soma() {
            32.25 * sub(ax: 1, bx: 25.32D)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T48)
{
    const std::string input = R"(
        fn sub(ax:int, bx:float): int {return 0}

        fn soma(n:float) {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: n)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T49)
{
    const std::string input = R"(
        fn sub(ax:int, bx:float): int {return 0}

        fn soma(n:float) {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: x)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T50)
{
    const std::string input = R"(
        fn sub(ax:int, bx:float): int {return 0}

        fn soma() {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: n)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, T51)
{
    const std::string input = R"(
        fn sub(ax:int, bx:int): int {return 0}

        fn soma() {
            let x: float = 25.32
            32.25 * sub(ax: 1, bx: x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T52)
{
    const std::string input = R"(
        fn sub(ax:double, bx:int): int {return 0}

        fn soma() {
            let x: int = 25
            32.25 * sub(ax: 1, bx: x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T53)
{
    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int {return 0}

        fn soma() {
            32.25 * sub(ax: 1, bx: mult(n:22, p:22.25D))
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T54)
{
    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int {return 0}

        fn soma() {
            32.25 * sub(ax: 1, bx: mult(n:22, p:25))
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T55)
{
    const std::string input = R"(
        fn mult(n:int, p:float): float {return 0.0}

        fn sub(ax:int, bx:float): int {return 0}

        fn soma() {
            let x: float = 25.00
            32.25 * sub(ax: 1, bx: mult(n:22, p:x))
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T56)
{
    const std::string input = R"(
        fn main() {
            let inline: fn = (a: int, b: int) -> a + b
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T57)
{
    const std::string input = R"(
        fn main() {
            let inline: fn = (a: int, b: int) -> a + b
            inline(a:12, b:14)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T58)
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

TEST_F(SemanticAnalysisTest, T59)
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

TEST_F(SemanticAnalysisTest, T60)
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

TEST_F(SemanticAnalysisTest, T61)
{
    const std::string input = R"(
        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x:int, y:float):float -> x + y

            inline(a:12, b:14) + 5.22 / sum(x:2, y:3.26F)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T62)
{
    const std::string input = R"(
        fn etc(): int {
            return 0
        }

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - etc()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T63)
{
    std::string input = R"(
        fn xptc(z:int): int {
            return 0
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

TEST_F(SemanticAnalysisTest, T64)
{
    std::string input = R"(
        fn mult(pp:float): float {return 0.0}
        fn xptc(z:float): int {return 0}

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:mult(pp:12.00F)) / xb
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T65)
{
    std::string input = R"(
        fn sub(x:int, y:int):int {return 0}

        fn main() {
            let add:fn = (pp:int):int -> pp + 32
            let inline:fn = (a:int,b:float, c:boolean):int -> a + b
            sub(x:12, y:add(pp:25)) * inline(a:32, c:false)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
}

TEST_F(SemanticAnalysisTest, T66)
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

TEST_F(SemanticAnalysisTest, T67)
{
    std::string input = R"(
        fn sub(x:int, y:int):int {return 0}

        fn main() {
            let add:fn = (pp:int):int -> pp + 32
            let inline:fn = (a:int,b:float, c:boolean):int -> a + b
            sub(x:12, y:add(pp:25)) * inline(b:25.00F,a:32, c:false)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticAnalysisTest, T68)
{
    std::string input = R"(
        fn main() {
            let inline:fn = (a:int, b:float, c:boolean):int -> a + b
            inline(c:true, a:32, b:25.00F)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticAnalysisTest, T69)
{
    std::string input = R"(
        fn multiply(x:int, y:float):float {return 0.0}

        fn main() {
            multiply(y:25.00F, x:10)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticAnalysisTest, T70)
{
    std::string input = R"(
        fn sub(a:int, b:int, c:boolean):int {return 0}

        fn main() {
            let x:int = 10
            let y:int = 20
            sub(b:y, c:false, a:x)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticAnalysisTest, T71)
{
    std::string input = R"(
        fn addOne(n:int):int {
            return n + 1
        }

        fn doubleValue(x:int, y:int):int {return 0}

        fn main() {
            doubleValue(y:addOne(n:2), x:5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
}

TEST_F(SemanticAnalysisTest, T72)
{
    std::string input = R"(
        fn value():int{
            return 25
        }
        fn main() {
            let blockFn : fn = (a:int, c:int):int ->{return 0}
            (blockFn(a:32, c:25) * (36 / value()))
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

// Teste 1: Redeclaração de variáveis em escopos aninhados
TEST_F(SemanticAnalysisTest, T73)
{
    const std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {return 0}
                    let result:float =  block(a:12, b:12.26) * x
                    return 0
                }
                let result:int =  27 * block(a:12, b:12.26)
                return 22
            }
            return 0
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

// Teste 2: Uso de variável indefinida lança exceção
TEST_F(SemanticAnalysisTest, T74)
{
    std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {return 0}
                    let result:float =  block(a:12, b:12.26) * xt
                    return 0
                }
                let result:float =  block(a:12, b:12.26)
                return 0
            }
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

// Teste 3: Declarações de funções aninhadas com chamadas de funções
TEST_F(SemanticAnalysisTest, T75)
{
    std::string input = R"(
        fn sub(a:int):int {return 0}

        fn main() {
            let p:string = "16"
            let inline:fn = (a:int, b:int):int -> a * b

            let block2:fn = (a:int, x:int):int -> {
                    let p:int = 12
                    let r:int = a * x
                    let block:fn = (a:int, x:int):int -> {
                       return ((a * x) / r) - p
                    }
                    return 0
                }

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - 10
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - 20 * inline(a:a,b:x)
                    }
                    return 2
                }

                return block(a:10,x:block2(a:25, x:sub(a:12)))
            }

            (block(a:10,x:30) - block2(a:25, x:sub(a:12)) * 2.98) / sub(a:15)

        }

    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T76)
{
    std::string input = R"(
        fn sub():float {
            let x:int = 25
            return x
        }

        fn main() {
            sub() * 2
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T77)
{
    std::string input = R"(
        fn sub():int {
            let x:int = 25
            return x
        }

        fn main() {
            sub() * 2
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T78)
{
    std::string input = R"(
        fn returnFN():fn {
            let inline:fn = (a:int):int -> a * 2
            return inline
        }

        fn main() {
            returnFN()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T79)
{
    std::string input = R"(
        fn returnFN():string {
            let inline:fn = (a:int):int -> a * 2
            return inline
        }

        fn main() {
            returnFN()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T80)
{
    std::string input = R"(
        fn returnDouble():double {
            return 10.0
        }

        fn main() {
            returnDouble() * 9
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T81)
{
    std::string input = R"(
        fn returnFloat():float {
            return 10
        }

        fn main() {
            returnFloat() * 9
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T82)
{
    std::string input = R"(
        fn returnInt():int {
            return 10.00
        }

        fn main() {
            returnFloat() * 9
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T83)
{
    std::string input = R"(
        fn returnInt():int {
            return 10
        }

        fn main() {
            returnInt() * 9
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T84)
{
    std::string input = R"(
        fn returnFloat():float {
            return 10.00
        }

        fn main() {
            returnFloat() * 9.00
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T85)
{
    std::string input = R"(
        fn returnFloat():float {
            return 10.00
        }

        fn main():float {
            return returnFloat()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T86)
{
    std::string input = R"(
        fn main():double {
            let inline:fn = (a:int):double -> a * 6
            return inline(a:10)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T87)
{
    std::string input = R"(
        fn main():double {
            let inline:fn = (a:int):float -> a * 6
            return inline(a:10)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T88)
{
    std::string input = R"(
        fn returnFloat():float {
            return 10.00
        }

        fn main():int {
            return returnFloat()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, T89)
{
    std::string input = R"(

        fn main():int {
            return returnFloat()
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticAnalysisTest, T90)
{
    std::string input = R"(
        fn main():int {
            // let inline:fn = (a:int):float -> a * 6
            return inline(a:10)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticAnalysisTest, T100)
{
    const std::string input = R"(
        fn main():float {
            let block:fn = (a:int):float -> {
                2.5 / a
            }
            return block(a:25)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ReturnNotFoundException);
}

TEST_F(SemanticAnalysisTest, T101)
{
    const std::string input = R"(
        //import std.output.printf

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticAnalysisTest, T102)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, T103)
{
    const std::string input = R"(
        import std.output.printex

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ModuleNotFoundException);
}

TEST_F(SemanticAnalysisTest, T104)
{
    const std::string input = R"(
        import std.output.printf
        import std.output.printf

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ModuleRedefinitionException);
}

TEST_F(SemanticAnalysisTest, T105)
{
    const std::string input = R"(
        import std.output.printf
        // import std.math.PI

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina", pi:PI())
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticAnalysisTest, T106)
{
    const std::string input = R"(
        fn main():int {
           let inline:fn = ():int -> 12
           let r:int = inline()
           return r
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

// Testes para expressões booleanas

// Caso 1: Literal booleano simples
TEST_F(SemanticAnalysisTest, 107)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = true
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

// Caso 2: Operador not com literal booleano
TEST_F(SemanticAnalysisTest, 108)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = not false
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

// Caso 3: Operadores and e or combinados
TEST_F(SemanticAnalysisTest, 109)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = true and false or true
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

// Caso 4: Expressão relacional que resulta em booleano
TEST_F(SemanticAnalysisTest, 110)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = 5 < 10
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

// Caso 5: Expressão com parênteses misturando booleanos e relacionais
TEST_F(SemanticAnalysisTest, 111)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = (true or false) and (5 == 5)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

// Caso 6: Uso de variável não definida na expressão booleana
TEST_F(SemanticAnalysisTest, 112)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = x and true
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

// Caso 7: Mistura de tipos – operador booleano aplicado a número e booleano
TEST_F(SemanticAnalysisTest, 113)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = 5 and false
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}


// Caso 9: Chamada de função que retorna um tipo não booleano em contexto booleano
TEST_F(SemanticAnalysisTest, 114)
{
    const std::string input = R"(
        fn getNumber():int {
            return 5
        }
        fn main() {
            let b:boolean = getNumber()
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

// Caso 10: Expressão booleana complexa com not e operadores relacionais
TEST_F(SemanticAnalysisTest, 115)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = not (5 > 3 and (10 <= 10))
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 106)
{
    const std::string input = R"(
        fn main() {
            let b:boolean = not (5 > 3 and (10 <= 10))
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 116)
{
    const std::string input = R"(
        fn main() {
            let inline:fn = (a:int):int -> a * 8
            let x:fn = inline
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 117)
{
    const std::string input = R"(
        fn sum(a:int, b:int) {
            let r:int = a + b
        }

        fn main() {
            let inline:fn = (a:int):int -> a * 8
            let x:fn = sum
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 118)
{
    const std::string input = R"(
        import std.output.printf

        fn main() {
            let inline:fn = (a:int):int -> a * 8
            let x:fn = printf
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 119)
{
    const std::string input = R"(
        import std.output.printf

        fn main() {
            let x:fn = printf
            let y:fn = x
            let z:fn = y
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 120)
{
    const std::string input = R"(

        fn main() {
            let x:fn = printf
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticAnalysisTest, 121)
{
    const std::string input = R"(
        fn main() {
            let inline:int = 10
            let x:fn = inline
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, 122)
{
    const std::string input = R"(
        fn sum(func:fn(a:float):int, c:int) {}

        fn main() {
            let inline:fn = (a:int):int -> a * 3
            sum(func:inline, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticAnalysisTest, 123)
{
    const std::string input = R"(
        fn sum(func:fn(a:int):float, c:int) {}

        fn main() {
            let inline:fn = (a:int):int -> a * 3
            sum(func:inline, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticAnalysisTest, 124)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int,c:float):int, c:int) {}

        fn main() {
            let inline:fn = (a:int,b:int,c:float):int -> a * 3
            sum(func:inline, c:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 125)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int, b:float):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticAnalysisTest, 126)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::SignatureMismatchException);
}

TEST_F(SemanticAnalysisTest, 127)
{
    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int,b:int):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 128)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let inline:fn = (x:int):int -> x * 2 * p
            func(a:inline(x:p))
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}


TEST_F(SemanticAnalysisTest, 129)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:float):int {
            let inline:fn = (x:int):int -> x * 2 * p
            func(a:inline(x:p))
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}


TEST_F(SemanticAnalysisTest, 130)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            func(a:x)
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, 131)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:float):int {
            func(a:p)
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, 132)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            func(a:2.3)
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, 133)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            func(a:p)
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 134)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            func(a:p)
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 135)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let inline:fn = (x:int):int -> x * 2 * p
            func(a:inline(x:p))
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           let block:fn = (func:fn (x:fn):int):int -> {
                func(x:inline)
                return 0
           }

           let func:fn = (x:fn):int -> 2 * 2
           block(func:func)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::FunctionSignatureNotDefined);
}

TEST_F(SemanticAnalysisTest, 136)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let inline:fn = (x:int):float -> x * 2.0 * p
            func(a:inline(x:p))
            return 0
        }

        fn main() {
           let inline:fn = (a:int):int -> a * 8
           sum(func:inline, p:3)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, 137)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            return func(a:p)
        }

        fn main() {
            let inline:fn = (x:int):int -> x * 3
            sum(func:inline, p:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 138)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let r:int = func(a:p)
            return r
        }

        fn main() {
            let inline:fn = (x:int):int -> x * 3
            sum(func:inline, p:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 139)
{
    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            let inline:fn = (x:int):int -> x * 3
            return inline(x:func(a:p))
        }

        fn main() {
            let inline:fn = (x:int):int -> x * 3
            sum(func:inline, p:2)
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 140)
{
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
    EXPECT_NO_THROW(runAnalysis(input));
}


TEST_F(SemanticAnalysisTest, 141)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 3

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else {
                printf(format:"X < Y\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 142)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 30

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else if (x < y) {
                printf(format:"X < Y\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 143)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 30

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else if (false) {
                printf(format:"X < Y\n")
            } else {
                printf(format:"Entrou no else\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 144)
{
    const std::string input = R"(
        fn main() {
           let inline:fn = (a:int):int -> a * 8

           let block:fn = (func:fn (x:fn):int):int -> {
                func(x:inline)
                return 0
           }

           let func:fn = (x:fn(a:int):int):int -> 2 * 2
           block(func:func)
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::FunctionSignatureNotDefined);
}

TEST_F(SemanticAnalysisTest, 145)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int {

            let x:float = 3.1
            let y:int = 30

            if (x > y) {
                printf(format:"X > Y\n")
                if (true) {
                    printf(format:"É true\n")
                }
            } else if (false) {
                printf(format:"X < Y\n")
            } else {
                printf(format:"Entrou no else\n")
            }

            printf(format:"Terminou\n")

            return 0
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticAnalysisTest, 146)
{
    const std::string input = R"(
        fn main() {
            let x:int = 3
            while (x < 5) {
                x = x + 1
            }
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableCannotBeChangedException);
}

TEST_F(SemanticAnalysisTest, 147)
{
    const std::string input = R"(
        fn main() {
            mut let x:int = 3
            let z:float = 0.25
            while (x < 5) {
                x = z
            }
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticAnalysisTest, 148)
{
    const std::string input = R"(
        fn main() {
            mut let x:int = 3
            while (x < 5) {
                x = z
            }
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticAnalysisTest, 149)
{
    const std::string input = R"(
    import std.output.printf

    fn main() {
        mut let x:int = 0
        while x < 100 {
            x = x + 1
            if (x == 5) {
                printf(format:"x = 5\n")
            } else {
                x = x + 1
                 printf(format:"else x = %u\n", x:x)
                 if (x == 59) {
                    break
                 }
            }
        }

        printf(format:"x1 = %u\n", r:x)
    }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}
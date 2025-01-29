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

// TEST_F(SemanticalAnalysisTest, T27)
// {
//     std::string input = R"(
//          fn soma(): int {
//              return sub() + 10
//          }

//         fn sub(): int {
//             return 5
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, TypeMismatchIntAndFloatLiteral)
// {
//     std::string input = R"(
//         fn soma(x:int, b:int) {
//             x + b * 1.145
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, FunctionArgNotFound)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:int): int {}

//         fn soma(): int {
//             let y: string = "hello"
//             32.25 * sub(ax: 1, nx: 25)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::FunctionArgNotFoundException);
// }

// TEST_F(SemanticalAnalysisTest, FunctionArgFound)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:int, nx:int): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: 32, nx: 25)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, SubIntFloat_IntLiteralInFloatParam_ShouldFail)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: 25)
//         }
//     )";

//     // Esperamos que esse caso gere incompatibilidade de tipos
//     // e lance TypeMismatchException (ajuste se usa outro tipo de exceção)
//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, SubIntFloat_DoubleLiteralInFloatParam_ShouldFail)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: 25.32D)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, SubDoubleFloat_CompatibleRealNumbers_ShouldPass)
// {
//     std::string input = R"(
//         fn sub(ax:double, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1.365D, bx: 25.32F)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, SubIntFloatLNotiteral_ShouldFail)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:double): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: 25.32)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCall)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:float): int {}

//         fn soma(n:float): int {
//             let x: float = 25.32
//             32.25 * sub(ax: 1, bx: n)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCall2)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:float): int {}

//         fn soma(n:float): int {
//             let x: float = 25.32
//             32.25 * sub(ax: 1, bx: x)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, VarNotFoundInFunctionCall)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             let x: float = 25.32
//             32.25 * sub(ax: 1, bx: n)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch)
// {
//     std::string input = R"(
//         fn sub(ax:int, bx:int): int {}

//         fn soma(): int {
//             let x: float = 25.32
//             32.25 * sub(ax: 1, bx: x)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch2)
// {
//     std::string input = R"(
//         fn sub(ax:double, bx:int): int {}

//         fn soma(): int {
//             let x: int = 25
//             32.25 * sub(ax: 1, bx: x)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallNotTypeMismatch)
// {
//     std::string input = R"(
//         fn sub(ax:double, bx:int): int {}

//         fn soma(x: int = 25): int {
//             32.25 * sub(ax: 36.26D, bx: x)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallNotTypeMismatch1)
// {
//     std::string input = R"(
//         fn sub(ax:double, bx:double): int {}

//         fn soma(c:double, k:double=25.34): int {
//             32.25 * sub(ax: c, bx: k)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch3)
// {
//     std::string input = R"(
//         fn sub(ax:double, bx:double): int {}

//         fn soma(c:float, k:double=25.34): int {
//             32.25 * sub(ax: c, bx: k)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch4)
// {
//     std::string input = R"(
//         fn mult(n:int, p:float): float {}

//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: mult(n:22, p:22.25D))
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch5)
// {
//     std::string input = R"(
//         fn mult(n:int, p:float): float {}

//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: mult(n:22, p:25))
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallNotTypeMismatch2)
// {
//     std::string input = R"(
//         fn mult(n:int, p:float): float {}

//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             let x: float = 25.00
//             32.25 * sub(ax: 1, bx: mult(n:22, p:x))
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch6)
// {
//     std::string input = R"(
//         fn mult(n:int, p:float): double {}

//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: mult(n:22, p:25))
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch7)
// {
//     std::string input = R"(
//         fn mult(n:int, p:float): int {}

//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: mult(n:22, p:25))
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, VarFoundInFunctionCallTypeMismatch8)
// {
//     std::string input = R"(
//         fn div(): int {}
//         fn mult(n:int, p:float): boolean {}

//         fn sub(ax:int, bx:float): int {}

//         fn soma(): int {
//             32.25 * sub(ax: 1, bx: mult(n:22, p:25))
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionDeclaration)
// {
//     std::string input = R"(
//         fn main() {
//             let inline: fn = (a: int, b: int) -> a + b
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionDeclarationWhithCall)
// {
//     std::string input = R"(
//         fn main() {
//             let inline: fn = (a: int, b: int) -> a + b
//             inline(a:12, b:14)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionDeclarationWhithCallAndLocalVariable)
// {
//     std::string input = R"(
//         fn main() {
//             let xb: int = 36
//             let inline: fn = (a: int, b: int): int -> (xb + b) * a
//             inline(a:12, b:14)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionTypeMismatchException)
// {
//     std::string input = R"(
//         fn main() {
//             let xb: int = 36
//             let inline: fn = (a: int, b: int) -> (xb + b) * a
//             inline(a:12, b:14) + 5.22
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionNoTypeMismatchException)
// {
//     std::string input = R"(
//         fn main() {
//             let xb: int = 36
//             let inline: fn = (a: int, b: int): int -> (xb + b) * a
//             inline(a:12, b:14) + 5.22
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionNoTypeMismatchException2)
// {
//     std::string input = R"(
//         fn main() {
//             let xb: int = 36
//             let inline:fn = (a: int, b: int):int -> (xb + b) * a
//             let sum:fn = (x:int, y:float):float -> x + y

//             inline(a:12, b:14) + 5.22 / sum(x:2, y:3.26F)
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionNoTypeMismatchException3)
// {
//     std::string input = R"(
//         fn xptc(): int {
//         }

//         fn main() {
//             let xb: int = 36
//             let inline:fn = (a: int, b: int):int -> (xb + b) * a
//             let sum:fn = (x: int, y: int):float -> 2.25 + x + y

//             5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc()
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionNoTypeMismatchException4)
// {
//     std::string input = R"(
//         fn xptc(z:int): int {
//         }

//         fn main() {
//             let xb: int = 36
//             let inline:fn = (a: int, b: int):int -> (xb + b) * a
//             let sum:fn = (x: int, y: int):float -> 2.25 + x + y

//             5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:32) / xb
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, InlineFunctionNoTypeMismatchException5)
// {
//     std::string input = R"(
//         fn mult(pp:float): float {}
//         fn xptc(z:float): int {}

//         fn main() {
//             let xb: int = 36
//             let inline:fn = (a: int, b: int):int -> (xb + b) * a
//             let sum:fn = (x: int, y: int):float -> 2.25 + x + y

//             5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:mult(pp:12.00F)) / xb
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, BooleanArgumentTypeMismatchWithInteger)
// {
//     std::string input = R"(
//         fn main(x:boolean = 21) {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, BooleanArgumentTypeMismatchWithFloat)
// {
//     std::string input = R"(
//         fn main(x:boolean = 21.36) {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, BooleanArgumentTypeMismatchWithString)
// {
//     std::string input = R"(
//         fn main(x:boolean = "olá mundo") {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// //

// TEST_F(SemanticalAnalysisTest, IntegerArgumentTypeMismatchWithFloat)
// {
//     std::string input = R"(
//         fn main(x:int = 21.2) {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, IntegerArgumentTypeMismatchWithString)
// {
//     std::string input = R"(
//         fn main(x:int = "olá mundo") {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// //

// TEST_F(SemanticalAnalysisTest, FloatArgumentTypeMismatchWithInteger)
// {
//     std::string input = R"(
//         fn main(x:float = 12) {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, DoubleArgumentTypeMismatchWithInteger)
// {
//     std::string input = R"(
//         fn main(x:double = 15) {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, FloatArgumentTypeMismatchWithString)
// {
//     std::string input = R"(
//         fn main(x:float = "22.37") {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, DoubleArgumentTypeMismatchWithInvalidString)
// {
//     std::string input = R"(
//         fn main(x:double = "15. + olá") {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// //*****

// TEST_F(SemanticalAnalysisTest, DoubleArgumentValidAssignmentWithTrue)
// {
//     std::string input = R"(
//         fn main(x:boolean = true) {}
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, DoubleArgumentValidAssignmentWithFalse)
// {
//     std::string input = R"(
//         fn main(x:boolean = false) {}
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, IntegerArgumentValidAssignment)
// {
//     std::string input = R"(
//         fn main(x:int = 25) {}
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, FloatArgumentValidAssignment)
// {
//     std::string input = R"(
//         fn main(x:float = 25.00) {}
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, DoubleArgumentValidAssignmentWithPreciseValue)
// {
//     std::string input = R"(
//         fn main(x:double = 32.2541250) {}
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, MultipleArgumentsValidAssignment)
// {
//     std::string input = R"(
//         fn main(x:double = 32.2541250, n:int, z:float, bb:string = "olá mundo", pp:boolean) {}
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// TEST_F(SemanticalAnalysisTest, BooleanArgumentTypeMismatchWithFloatValue)
// {
//     std::string input = R"(
//         fn main(x:double = 32.2541250, n:int, z:float, bb:string = "olá mundo", pp:boolean = 2.36) {}
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, UninitializedVariableWithFloatAssignment)
// {
//     std::string input = R"(
//         fn main() {
//             let x: string
//             let n: float = 12.25
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::UninitializedVariableException);
// }

// TEST_F(SemanticalAnalysisTest, UninitializedVariableWithStringAssignment)
// {
//     std::string input = R"(
//         fn main() {
//             let x: string = "hi lorena"
//             let n: int
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::UninitializedVariableException);
// }

// //*****

// TEST_F(SemanticalAnalysisTest, ArgumentCountMismatch_InlineFunctionMissingParameter)
// {
//     std::string input = R"(
//         fn main() {
//             let inline:fn = (a:int, b:float, c:boolean) -> a + b
//             inline(a:12,c:true)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentCountMismatch_InlineFunctionAndSubMissingParameter)
// {
//     std::string input = R"(
//         fn sub(x:int, y:float):int {
//         }

//         fn main() {
//             let inline:fn = (a:int,b:float, c:boolean) -> a + b
//             inline(a:23,b:12.00F,c:true) * sub(x:12)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentCountMismatch_SubCallAndInlineDeclaration)
// {
//     std::string input = R"(
//         fn sub(x:int, y:int):int {}

//         fn main() {
//             let add:fn = (pp:int):int -> pp + 32
//             let inline:fn = (a:int,b:float, c:boolean):int -> a + b
//             sub(x:12, y:add(pp:25)) * inline(a:32, c:false)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, FunctionCallWithMissingArguments)
// {
//     std::string input = R"(
//         fn adicionar(a:int, b:int): int {
//             return a + b
//         }

//         fn main() {
//             let soma: int = adicionar(a: 5)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentCountMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentOrderMismatchException)
// {
//     std::string input = R"(
//         fn sub(x:int, y:int):int {}

//         fn main() {
//             let add:fn = (pp:int):int -> pp + 32
//             let inline:fn = (a:int,b:float, c:boolean):int -> a + b
//             sub(x:12, y:add(pp:25)) * inline(b:25.00F,a:32, c:false)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentOrderMismatchException_InlineFunction)
// {
//     std::string input = R"(
//         fn main() {
//             let inline:fn = (a:int, b:float, c:boolean):int -> a + b
//             inline(c:true, a:32, b:25.00F)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentOrderMismatchException_NestedFunction)
// {
//     std::string input = R"(
//         fn multiply(x:int, y:float):float {}

//         fn main() {
//             multiply(y:25.00F, x:10)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentOrderMismatchException_MixedVariablesAndFunctions)
// {
//     std::string input = R"(
//         fn sub(a:int, b:int, c:boolean):int {}

//         fn main() {
//             let x:int = 10
//             let y:int = 20
//             sub(b:y, c:false, a:x)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArgumentOrderMismatchException_FunctionReturn)
// {
//     std::string input = R"(
//         fn addOne(n:int):int {
//             return n + 1
//         }

//         fn doubleValue(x:int, y:int):int {}

//         fn main() {
//             doubleValue(y:addOne(n:2), x:5)
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::ArgumentOrderMismatchException);
// }

// TEST_F(SemanticalAnalysisTest, ArrowFunctionBlockNoError)
// {
//     std::string input = R"(
//         fn value():int{
//             25
//         }
//         fn main() {
//             let blockFn : fn = (a:int, c:int):int ->{}
//             (blockFn(a:32, c:25) * (36 / value()))
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// // Teste 1: Redeclaração de variáveis em escopos aninhados
// TEST_F(SemanticalAnalysisTest, VariableRedeclarationInNestedScopes_DoesNotThrow)
// {
//     std::string input = R"(
//         fn soma(n:float): int {
//             let x: float = 25.32
//             let block:fn = (a:int, b:float):int -> {
//                 let block:fn = (a:int, b:float):int -> {
//                     let block:fn = (a:int, b:float):int -> {}
//                     let result:float =  block(a:12, b:12.26) * x
//                 }
//                 let result:float =  27 * block(a:12, b:12.26)
//             }
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

// // Teste 2: Uso de variável indefinida lança exceção
// TEST_F(SemanticalAnalysisTest, UndefinedVariableUsage_ThrowsVariableNotFoundException)
// {
//     std::string input = R"(
//         fn soma(n:float): int {
//             let x: float = 25.32
//             let block:fn = (a:int, b:float):int -> {
//                 let block:fn = (a:int, b:float):int -> {
//                     let block:fn = (a:int, b:float):int -> {}
//                     let result:float =  block(a:12, b:12.26) * xt
//                 }
//                 let result:float =  block(a:12, b:12.26)
//             }
//         }
//     )";

//     EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
// }

// // Teste 3: Declarações de funções aninhadas com chamadas de funções
// TEST_F(SemanticalAnalysisTest, NestedFunctionDeclarationsWithFunctionCalls_DoesNotThrow)
// {
//     std::string input = R"(
//         fn sub():double {
//             return 5.25
//         }
//         fn soma(n:float): int {
//             let x: float = 25.32
//             let block:fn = (a:int, b:float):int -> {
//                 let block:fn = (a:int, b:float):int -> {
//                     let block:fn = (a:int, b:float):int -> {}
//                     let result:float =  block(a:12, b:12.26) * x
//                 }
//                 let result:float =  27 * block(a:12, b:12.26) / sub()
//             }
//         }
//     )";

//     EXPECT_NO_THROW(runAnalysis(input));
// }

#include <gtest/gtest.h>
#include <memory>
#include "../src/headers/SemanticalAnalysis.h"
#include "../src/headers/ScopeManager.h"
#include "../src/headers/IronExceptions.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "antlr4-runtime.h"

class SemanticalAnalysisTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Cria um gerenciador de escopos
        scopeManager = std::make_unique<ScopeManager>();
    }

    void runAnalysis(const std::string& input) {
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_unique<IronParser>(&tokens);
        semanticalAnalysis = std::make_unique<SemanticalAnalysis>(std::move(parser), std::move(scopeManager));

        // Executa a análise semântica
        semanticalAnalysis->analyze();
    }

    std::unique_ptr<ScopeManager> scopeManager;
    std::unique_ptr<SemanticalAnalysis> semanticalAnalysis;
};

// --- Testes Positivos ---
TEST_F(SemanticalAnalysisTest, ValidFunctionDeclaration) {
    std::string input = R"(
        fn soma(): int {
            let x: int = 10
        }

        fn subtracao(): int {
            let y: int = 20
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, ValidNestedScopes) {
    std::string input = R"(
        fn teste(): int {
            let x: int = 10
            {
                let y: int = 20
            }
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, ValidExpr) {
    std::string input = R"(
        fn test() {
            let b:int = 12
            let x:int = b
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, VariableWithFn) {
    std::string input = R"(
        fn another() {
            let x: int
            let b: fn = (a: int, b: int) -> a * b
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

// --- Testes Negativos ---
TEST_F(SemanticalAnalysisTest, DuplicateFunctionDeclaration) {
    std::string input = R"(
        fn soma(): int {
            let x: int = 25
        }

        fn soma(): int {
            let y: int = 30
        }
    )";

    EXPECT_THROW(runAnalysis(input), FunctionRedefinitionException);
}

TEST_F(SemanticalAnalysisTest, DuplicateVariableInSameScope) {
    std::string input = R"(
        fn soma(): int {
            let x: int = 10
            let x: int = 20
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableRedefinitionException);
}

TEST_F(SemanticalAnalysisTest, VariableAlreadyDeclaredInNestedScope) {
    std::string input = R"(
        fn teste() {
            let x: int
            let x: float
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableRedefinitionException);
}

TEST_F(SemanticalAnalysisTest, DuplicateVariableWithDifferentType) {
    std::string input = R"(
        fn teste() {
            let x: int
            let x: fn = (a: int, b: int) -> a * b
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableRedefinitionException);
}

TEST_F(SemanticalAnalysisTest, VariableNotFoundInExpression) {
    std::string input = R"(
        fn teste() {
            x
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, VariableNotFoundInAssignment) {
    std::string input = R"(
        fn teste() {
            x = 10
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, VariableNotExpression) {
    std::string input = R"(
        fn teste() {
            let x:int = b
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, ValidVariableAndExpression) {
    std::string input = R"(
        fn soma() {
            let b:int = 12
            let x:int = b
            b + x * 25
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, ValidComplexExpression) {
    std::string input = R"(
        fn teste() {
            let b:int = 12
            let x:int = b
            25 + x * b * x
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, VariableNotFoundInExpression2) {
    std::string input = R"(
        fn teste() {
            let b:int = 12
            let x:int = b
            25 + x * x * c
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, TypeMismatchExceptionVare) {
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

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, TypeMismatchExceptionVarb) {
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

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, TypeMismatchExceptionVarc) {
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:int = 32
            let c:string = "456"
            let d:int = 15
            let e:string = "olá mundo"
            let n:int = (a + b * (c + d) - e)
        }
    )";

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, TypeMismatchException_VariableWithDifferentType) {
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:string = "32"
            25 + 1.25 + a * 2.36 - b
        }
    )";

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, TypeMismatchException_NumberWithString) {
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:string = "32"
            25 + 1.25 + b * 2.36 - a
        }
    )";

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, ValidExpression_NoException) {
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:int = 32
            a + 1.25 + b * 2.36 - a
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, TypeMismatchException_OperationBetweenNumberAndString) {
    std::string input = R"(
        fn teste() {
            let a:int = 25
            let b:string = "hello"
            a + b
        }
    )";

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, ValidNestedExpression) {
    std::string input = R"(
        fn teste() {
            let a:int = 10
            let b:int = 20
            let c:int = 30
            (a + b) * c - a
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, TypeMismatchException_NestedExpression) {
    std::string input = R"(
        fn teste() {
            let a:int = 10
            let b:string = "20"
            let c:int = 30
            (a + b) * c
        }
    )";

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, IncompatibleTypesStringAndInt) {
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma(): int {
            let y: string = "hello"
            y * sub()
        }
    )";

    EXPECT_THROW(runAnalysis(input), TypeMismatchException);
}

TEST_F(SemanticalAnalysisTest, UseFunctionBeforeDeclaration) {
    std::string input = R"(
        fn soma(): int {
            return sub() + 10
        }

        fn sub(): int {
            return 5
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, CompatibleTypesWithFunctionCalls) {
    std::string input = R"(
        fn sub(): int {
            return 5
        }

        fn soma(): int {
            let x: int = 10
            return x + sub()  // ambos int, operação válida
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, ChainedFunctionCallsCompatible) {
    std::string input = R"(
        fn addOne(): int {
            return 1
        }

        fn doubleValue(num: int): int {
            return num * 2
        }

        fn main(): int {
            let base: int = 5
            return doubleValue(base) + addOne()
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticalAnalysisTest, UndeclaredVariableInFunction) {
    std::string input = R"(
        fn soma(x:int, b:int, n:string) {
            x + b * z
        }
    )";

    EXPECT_THROW(runAnalysis(input), VariableNotFoundException);
}

TEST_F(SemanticalAnalysisTest, TypeMismatchIntAndFloatLiteral) {
    std::string input = R"(
        fn soma(x:int, b:int) {
            x + b * 1.145
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

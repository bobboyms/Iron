#include <gtest/gtest.h>
#include <memory>
#include "../src/headers/SemanticalAnalysis.h"
#include "../src/headers/HighLevelIR.h"
#include "../src/headers/ScopeManager.h"
#include "../src/headers/IronExceptions.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "antlr4-runtime.h"

std::string removeLineBreaks(const std::string& input) {
    std::string output;
    output.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\r') {
            continue;
        }
        if (input[i] == '\n') {
            continue;
        }
        output += input[i];
    }

    return output;
}

std::string removeWhitespace(const std::string& str) {
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](unsigned char c) { return !std::isspace(c); });
    return result;
}

class HlIrTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Cria um gerenciador de escopos
        scopeManager = std::make_unique<iron::ScopeManager>();
    }

    void runAnalysis(const std::string& input, const std::string& expectedOutput) {
        // Inicializa os componentes do ANTLR
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        iron::SemanticalAnalysis analysis(parser, std::move(std::make_unique<iron::ScopeManager>()));
        analysis.analyze();

        // Rewind
        tokens.seek(0);
        parser->reset();

        iron::HighLevelIR hightLevelCodeGenerator(parser, std::move(std::make_unique<iron::ScopeManager>()));
        const auto code = hightLevelCodeGenerator.generateCode();

        if (removeWhitespace(code) == removeWhitespace(expectedOutput)) {
            return;
        } else {
            FAIL() << "Generated code does not match the expected code";
        }

    }

    std::unique_ptr<iron::ScopeManager> scopeManager;
    std::unique_ptr<iron::SemanticalAnalysis> semanticalAnalysis;
};

TEST_F(HlIrTest, HlIrTestFuncDeclarationTest) {
    std::string input = R"(
        fn sub() {}
        public fn main(name:string):int {}
    )";

    std::string output = R"(
        private fn sub (): void { 
        }
        public fn main (name:string): int { 
        }
    )";

    

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, AssignmentNoConversionTest) {
    std::string input = R"(
        public fn main(name:string):int {
            let a:int = 10
            let result:int = a
        }
    )";

    std::string output = R"(
        public fn main (name:string): int { 
            let a:int = 10
            let result:int = a
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, HlIrTestVarDeclaraTest) {
    std::string input = R"(
        public fn main(name:string):int {
            let a:float = 10.00F
            let b:double = 12.00D
            let c:float = 65.00F
            let e:int = 12
        }
    )";

    std::string output = R"(
        public fn main (name:string): int { 
            let a:float = 10.00F
            let b:double = 12.00D
            let c:float = 65.00F
            let e:int = 12
        }
    )";

    

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, HlIrTestExpr1Test) {
    std::string input = R"(
        fn value():float {}

        public fn main(name:string):int {
            let a:float = 10.00F
            let b:double = 12.00D
            let c:float = 65.00F
            let e:int = 12

            let result:int = ((a + b) * value())
        }
    )";

    std::string output = R"(
        private fn value (): float { 
        } 
        public fn main (name:string): int { 
        let a:float = 10.00F
        let b:double = 12.00D
        let c:float = 65.00F
        let e:int = 12
        let tmp_1:double = a float to double
        let tmp_2:double = PLUS tmp_1, b
        let tmp_3:float = value()
        let tmp_4:double = tmp_3 float to double
        let tmp_5:double = MULT tmp_2, tmp_4
        let tmp_6:int = tmp_5 double to int
        let result:int = tmp_6
} 
    )";

    

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, HlIrTestExpr2Test) {
    std::string input = R"(
        fn value():float {}

        public fn main(name:string):int {
            let a:float = 10.00F
            let b:double = 12.00D
            let c:float = 65.00F
            let e:int = 12

            let result:float = a + b * value()
        }
    )";

    std::string output = R"(
        private fn value (): float { 
        } 
        public fn main (name:string): int { 
            let a:float = 10.00F
            let b:double = 12.00D
            let c:float = 65.00F
            let e:int = 12
            let tmp_1:float = value()
            let tmp_2:double = tmp_1 float to double
            let tmp_3:double = MULT b, tmp_2
            let tmp_4:double = a float to double
            let tmp_5:double = PLUS tmp_4, tmp_3
            let tmp_6:float = tmp_5 double to float
            let result:float = tmp_6
        } 
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, HlIrTestExpr3Test) {
    std::string input = R"(
        fn value():float {}

        public fn main(name:string):int {
            let a:int = 10
            let b:int = 12
            let c:int = 65
            let e:int = 12

            let result:double = (a + (b * 26) / value()) - e
        }
    )";

    std::string output = R"(
    private fn value (): float { 
} 
public fn main (name:string): int { 
let a:int = 10
let b:int = 12
let c:int = 65
let e:int = 12
let tmp_1:int = 26
let tmp_2:int = MULT b, tmp_1
let tmp_3:float = value()
let tmp_4:float = tmp_2 int to float
let tmp_5:float = DIV tmp_4, tmp_3
let tmp_6:float = a int to float
let tmp_7:float = PLUS tmp_6, tmp_5
let tmp_8:float = e int to float
let tmp_9:float = MINUS tmp_7, tmp_8
let tmp_10:double = tmp_9 float to double
let result:double = tmp_10
} 
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

// Test 2: Atribuição com conversão segura (int para float)
TEST_F(HlIrTest, AssignmentIntToFloatConversionTest) {
    std::string input = R"(
        public fn main(name:string):float {
            let a:int = 10
            let result:float = a
        }
    )";

    std::string output = R"(
        public fn main (name:string): float { 
            let a:int = 10
            let tmp_1:float = a int to float
            let result:float = tmp_1
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

// Test 3: Operação entre variáveis do mesmo tipo (float + float)
TEST_F(HlIrTest, OperationSameTypeTest) {
    std::string input = R"(
        public fn main(name:string):float {
            let a:float = 10.0F
            let b:float = 20.0F
            let result:float = a + b
        }
    )";

    std::string output = R"(
        public fn main (name:string): float { 
            let a:float = 10.0F
            let b:float = 20.0F
            let tmp_1:float = PLUS a, b
            let result:float = tmp_1
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

// Test 4: Operação entre tipos diferentes com conversão (int + float)
TEST_F(HlIrTest, OperationIntAndFloatConversionTest) {
    std::string input = R"(
        public fn main(name:string):float {
            let a:int = 10
            let b:float = 20.5F
            let result:float = a + b
        }
    )";

    std::string output = R"(
        public fn main (name:string): float { 
            let a:int = 10
            let b:float = 20.5F
            let tmp_1:float = a int to float
            let tmp_2:float = PLUS tmp_1, b
            let result:float = tmp_2
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

// Test 5: Conversão em operações aritméticas complexas
TEST_F(HlIrTest, ComplexArithmeticOperationConversionTest) {
    std::string input = R"(
        fn value():double {}
    
        public fn main(name:string):double {
            let a:int = 5
            let b:float = 3.2F
            let c:double = 7.8D
            let result:double = (a + b) * value()
        }
    )";

    std::string output = R"(
        private fn value (): double { 
        } 
        public fn main (name:string): double { 
            let a:int = 5
            let b:float = 3.2F
            let c:double = 7.8D
            let tmp_1:float = a int to float
            let tmp_2:float = PLUS tmp_1, b
            let tmp_3:double = value()
            let tmp_4:double = tmp_2 float to double
            let tmp_5:double = MULT tmp_4, tmp_3
            let result:double = tmp_5
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, AssignmentDoubleToDoubleNoConversionTest) {
    std::string input = R"(
        public fn main(name:string):double {
            let a:double = 10.0D
            let result:double = a
        }
    )";

    std::string output = R"(
        public fn main (name:string): double { 
            let a:double = 10.0D
            let result:double = a
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}
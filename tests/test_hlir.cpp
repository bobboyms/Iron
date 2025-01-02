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
            let tmp_1:int = a float to int
            let tmp_2:int = b double to int
            let tmp_3:int = PLUS tmp_1, tmp_2
            let tmp_4:float = value()
            let tmp_5:int = MULT tmp_3, tmp_4
            let result:int = tmp_5
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

            let result:int = a + b * value()
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
            let tmp_1:int = a float to int
            let tmp_2:int = b double to int
            let tmp_3:float = value()
            let tmp_4:int = MULT tmp_2, tmp_3
            let tmp_5:int = PLUS tmp_1, tmp_4
            let result:int = tmp_5
        } 
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}

TEST_F(HlIrTest, HlIrTestExpr3Test) {
    std::string input = R"(
        fn value():float {}

        public fn main(name:string):int {
            let a:float = 10.00F
            let b:double = 12.00D
            let c:float = 65.00F
            let e:int = 12

            let result:int = (a + (b * 26) / value())
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
        let tmp_1:int = a float to int
        let tmp_2:int = b double to int
        let tmp_3:int = 26
        let tmp_4:int = MULT tmp_2, tmp_3
        let tmp_5:float = value()
        let tmp_6:int = DIV tmp_4, tmp_5
        let tmp_7:int = PLUS tmp_1, tmp_6
        let result:int = tmp_7
        } 
    )";

    EXPECT_NO_THROW(runAnalysis(input, output));
}
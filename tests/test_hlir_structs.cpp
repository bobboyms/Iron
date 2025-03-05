#include "test_hlir_common.cpp"

// Test fixture for loop-related HLIR tests
class HlirStructTests : public HlirTestBase {};

TEST_F(HlirStructTests, T1)
{
    const std::string output = R"(
        fn main():void {
            var_0:struct = Pessoa
            var_0:struct = Pessoa {name:string = "Thiago", idade:int = 37}
        }

        struct Pessoa {name:string,idade:int}
    )";

    const std::string input = R"(
        struct Pessoa {
            mut name:string,
            idade:int
        }

        fn main() {
            let pessoa:Pessoa = {name:"Thiago", idade:37}
        }

    )";

    runAnalysis(input, output);
}
#include "test_hlir_common.cpp"

// Test fixture for loop-related HLIR tests
class HlirStructTests : public HlirTestBase {};

TEST_F(HlirStructTests, T1)
{
    const std::string output = R"(
        fn main():void {
            var_0:struct = Pessoa
            var_1:string = "Thiago"
            var_2:int = 37
            var_3:float = 1.75
            var_4:double = 2500.2541D
            var_5:boolean = true
            var_0:struct = Pessoa {name:string = var_1, idade:int = var_2, altura:float = var_3, salario:double = var_4, casado:boolean = var_5}
        }

        struct Pessoa {name:string,idade:int,altura:float,salario:double,casado:boolean}
    )";

    const std::string input = R"(
        struct Pessoa {
            mut name:string,
            idade:int,
            altura:float,
            salario:double,
            casado:boolean
        }

        fn main() {
            let pessoa:Pessoa = {name:"Thiago", idade:37, altura:1.75, salario:2500.2541D, casado:true}
        }

    )";

    runAnalysis(input, output);
}
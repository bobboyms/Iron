#include "test_hlir_common.cpp"

// Test fixture for loop-related HLIR tests
class HlirStructTests : public HlirTestBase {};

TEST_F(HlirStructTests, T1)
{
    const std::string output = R"(
        fn main():void {
            var_0:struct Pessoa = Pessoa
            var_1:string = "Thiago"
            var_2:int = 37
            var_3:float = 1.75
            var_4:double = 2500.2541D
            var_5:boolean = true
            var_0:struct Pessoa = Pessoa {name:string = var_1, idade:int = var_2, altura:float = var_3, salario:double = var_4, casado:boolean = var_5}
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

TEST_F(HlirStructTests, T2)
{
    const std::string output = R"(
        fn main():void {
            var_0:struct Pessoa = Pessoa
            var_1:string = "Talibas"
            var_2:struct Endereco = Endereco
            var_3:string = "32"
            var_4:struct Cidade = Cidade
            var_5:string = "curitiba"
            var_4:struct Cidade = Cidade {nome:string = var_5}
            var_2:struct Endereco = Endereco {rua:string = var_3, cidade:struct Cidade = var_4}
            var_0:struct Pessoa = Pessoa {name:string = var_1, endereco:struct Endereco = var_2}
        }

        struct Cidade {nome:string}

        struct Endereco {rua:string,cidade:struct Cidade}

        struct Pessoa {name:string,endereco:struct Endereco}
    )";

    const std::string input = R"(
      struct Cidade {
         mut nome:string
      }

      struct Endereco {
         mut rua:string,
         cidade: Cidade
      }

      struct Pessoa {
            mut name:string,
            mut endereco: Endereco
      }

      fn main() {
           mut let pessoa:Pessoa = {name:"Talibas" ,endereco:{rua:"32", cidade:{nome:"curitiba"}}}
      }

    )";

    runAnalysis(input, output);
}
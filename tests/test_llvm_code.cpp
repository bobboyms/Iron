#include <algorithm>
#include <cctype>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "antlr4-runtime.h"

#include "../src/headers/Files.h"
#include "../src/headers/HLIRGenerator.h"
#include "../src/headers/Hlir.h"
#include "../src/headers/LLVMIR.h"
#include "../src/headers/SemanticAnalysis.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"

// Certifique-se de que os namespaces utilizados (ex.: config, iron, scope, util, hlir, llvm)
// estejam devidamente definidos e que os headers correspondentes sejam incluídos.


class LLVMTestCode : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Inicializações necessárias antes de cada teste.
    }

    /**
     * @brief Remove todos os caracteres de espaço em branco de uma string.
     * @param str A string de entrada.
     * @return Uma nova string sem espaços em branco.
     */
    static std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        result.reserve(str.size());

        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c) { return !std::isspace(c); });
        return result;
    }

    static std::string llvmCode(const std::unique_ptr<llvm::Module> &module)
    {
        std::string irStr;
        llvm::raw_string_ostream irStream(irStr);
        module->print(irStream, nullptr);
        return irStr;
    }


    /**
     * @brief Compara duas strings ignorando diferenças de espaçamento.
     *
     * Se as strings coincidirem (desconsiderando espaços em branco), o teste passa.
     * Caso contrário, falha e exibe as strings geradas e esperadas.
     *
     * @param input A string gerada pelo teste.
     * @param expectedOutput A string esperada para comparação.
     */
    void runAnalysis(const std::string &input, const std::string &expectedOutput)
    {
        auto hlirOutPut = getHighLevelCode(input);
        const auto cleanInput = removeWhitespace(hlirOutPut);
        const auto cleanExpected = removeWhitespace(expectedOutput);
        if (cleanInput == cleanExpected)
        {
            // Teste passou.
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

    static std::string getFileNameWithoutExtension(const std::string &filePath)
    {
        const std::filesystem::path path(filePath); // Cria um objeto 'path' a partir do caminho do arquivo
        return path.stem().string() + ".o";
    }

    /**
     * @brief Gera o código de alto nível a partir de uma string de entrada.
     *
     * @param input A string de código de entrada.
     * @return Uma string contendo o código de alto nível gerado.
     */
    static std::string getHighLevelCode(const std::string &input)
    {
        // Cria uma configuração a partir de um arquivo YAML
        auto config = std::make_shared<config::Configuration>("compiler_config.yaml");

        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticAnalysis analysis(parser, std::make_unique<scope::ScopeManager>(), loadStringAsLines(input),
                                        config);

        // Reposiciona o token stream para reiniciar a análise
        tokens.seek(0);
        parser->reset();

        auto exportContexts = std::make_shared<std::map<std::string, std::shared_ptr<hlir::Context>>>();
        auto hlirContext = std::make_shared<hlir::Context>();
        hlir::HLIRGenerator highLevelCodeGenerator(parser, hlirContext, config, exportContexts);
        highLevelCodeGenerator.getContext();
        exportContexts->emplace("main", hlirContext);

        // Salva o código HLIR em arquivo
        const auto hlirPath = util::format("{}", config->outputHLIR());
        const auto pathAndFile = iron::saveToFile(hlirContext->getText(), hlirPath, "main.hlir");

        std::vector<std::unique_ptr<llvm::Module>> modules;
        std::vector<std::string> objectFiles;
        llvm::LLVMContext llvmContext;

        for (const auto &[path, hlirCont]: *exportContexts)
        {
            // printf("%s\n", "******************************");
            printf("%s\n", path.c_str());
            const auto filename = getFileNameWithoutExtension(path);
            objectFiles.push_back(filename);

            iron::LLVM llvm(hlirCont, llvmContext, filename);
            auto module = llvm.generateCode();

            if (!module)
            {
                std::cerr << "Erro: llvm.generateCode() retornou um ponteiro nulo." << std::endl;
            }

            modules.push_back(std::move(module));
        }

        auto mainModule = iron::LLVM::mergeModules(std::move(modules));

        // Retorna o código de alto nível gerado
        return llvmCode(mainModule);
    }
};


//-----------------------------------------------------------
// TESTS FOR THE CLASS FunctionArgs
//-----------------------------------------------------------

TEST_F(LLVMTestCode, T1)
{
    const std::string output = R"(
        ; ModuleID = 'main.o'
        source_filename = "main.o"

        define void @main() {
        entry:
          %r = alloca float, align 4
          %var_8 = alloca float, align 4
          %var_7 = alloca float, align 4
          %var_6 = alloca i32, align 4
          %var_5 = alloca float, align 4
          %var_4 = alloca float, align 4
          %var_3 = alloca float, align 4
          %var_2 = alloca float, align 4
          %var_1 = alloca i32, align 4
          %b = alloca float, align 4
          %a = alloca i32, align 4
          store i32 10, ptr %a, align 4
          store float 2.050000e+01, ptr %b, align 4
          store i32 2, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          %cast_var_1 = sitofp i32 %load_var_1 to float
          store float %cast_var_1, ptr %var_2, align 4
          %load_b = load float, ptr %b, align 4
          %load_var_2 = load float, ptr %var_2, align 4
          %rdiv = fdiv float %load_b, %load_var_2
          store float %rdiv, ptr %var_3, align 4
          %load_a = load i32, ptr %a, align 4
          %cast_a = sitofp i32 %load_a to float
          store float %cast_a, ptr %var_4, align 4
          %load_var_4 = load float, ptr %var_4, align 4
          %load_var_3 = load float, ptr %var_3, align 4
          %rplus = fadd float %load_var_4, %load_var_3
          store float %rplus, ptr %var_5, align 4
          store i32 3, ptr %var_6, align 4
          %load_var_6 = load i32, ptr %var_6, align 4
          %cast_var_6 = sitofp i32 %load_var_6 to float
          store float %cast_var_6, ptr %var_7, align 4
          %load_var_5 = load float, ptr %var_5, align 4
          %load_var_7 = load float, ptr %var_7, align 4
          %rmult = fmul float %load_var_5, %load_var_7
          store float %rmult, ptr %var_8, align 4
          %load_var_8 = load float, ptr %var_8, align 4
          store float %load_var_8, ptr %r, align 4
          ret void
        }
    )";

    const std::string input = R"(
        fn main() {
            let a:int = 10
            let b:float = 20.5

            let r:float = (a + b / 2) * 3
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T2)
{
    const std::string output = R"(
; ModuleID = 'main.o'
source_filename = "main.o"

define void @main() {
entry:
  %r2 = alloca double, align 8
  %var_13 = alloca double, align 8
  %var_12 = alloca double, align 8
  %var_11 = alloca double, align 8
  %var_10 = alloca double, align 8
  %var_9 = alloca float, align 4
  %r = alloca float, align 4
  %var_8 = alloca float, align 4
  %var_7 = alloca float, align 4
  %var_6 = alloca i32, align 4
  %var_5 = alloca float, align 4
  %var_4 = alloca float, align 4
  %var_3 = alloca float, align 4
  %var_2 = alloca float, align 4
  %var_1 = alloca i32, align 4
  %d = alloca double, align 8
  %b = alloca float, align 4
  %a = alloca i32, align 4
  store i32 10, ptr %a, align 4
  store float 0x4026B851E0000000, ptr %b, align 4
  store double 2.050000e+01, ptr %d, align 8
  store i32 2, ptr %var_1, align 4
  %load_var_1 = load i32, ptr %var_1, align 4
  %cast_var_1 = sitofp i32 %load_var_1 to float
  store float %cast_var_1, ptr %var_2, align 4
  %load_b = load float, ptr %b, align 4
  %load_var_2 = load float, ptr %var_2, align 4
  %rdiv = fdiv float %load_b, %load_var_2
  store float %rdiv, ptr %var_3, align 4
  %load_a = load i32, ptr %a, align 4
  %cast_a = sitofp i32 %load_a to float
  store float %cast_a, ptr %var_4, align 4
  %load_var_4 = load float, ptr %var_4, align 4
  %load_var_3 = load float, ptr %var_3, align 4
  %rplus = fadd float %load_var_4, %load_var_3
  store float %rplus, ptr %var_5, align 4
  store i32 3, ptr %var_6, align 4
  %load_var_6 = load i32, ptr %var_6, align 4
  %cast_var_6 = sitofp i32 %load_var_6 to float
  store float %cast_var_6, ptr %var_7, align 4
  %load_var_5 = load float, ptr %var_5, align 4
  %load_var_7 = load float, ptr %var_7, align 4
  %rmult = fmul float %load_var_5, %load_var_7
  store float %rmult, ptr %var_8, align 4
  %load_var_8 = load float, ptr %var_8, align 4
  store float %load_var_8, ptr %r, align 4
  store float 2.500000e+00, ptr %var_9, align 4
  %load_var_9 = load float, ptr %var_9, align 4
  %cast_var_9 = fpext float %load_var_9 to double
  store double %cast_var_9, ptr %var_10, align 8
  %load_var_10 = load double, ptr %var_10, align 8
  %load_d = load double, ptr %d, align 8
  %rdiv1 = fdiv double %load_var_10, %load_d
  store double %rdiv1, ptr %var_11, align 8
  %load_r = load float, ptr %r, align 4
  %cast_r = fpext float %load_r to double
  store double %cast_r, ptr %var_12, align 8
  %load_var_12 = load double, ptr %var_12, align 8
  %load_var_11 = load double, ptr %var_11, align 8
  %rminus = fsub double %load_var_12, %load_var_11
  store double %rminus, ptr %var_13, align 8
  %load_var_13 = load double, ptr %var_13, align 8
  store double %load_var_13, ptr %r2, align 8
  ret void
}
    )";

    const std::string input = R"(
        fn main() {
            let a:int = 10
            let b:float = 11.36
            let d:double = 20.5D

            let r:float = (a + b / 2) * 3
            let r2:double = r - 2.5 / d
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T3)
{
    const std::string output = R"(
; ModuleID = 'main.o'
source_filename = "main.o"

define i32 @main() {
entry:
  %var_10 = alloca i32, align 4
  %var_9 = alloca float, align 4
  %var_8 = alloca float, align 4
  %var_7 = alloca float, align 4
  %var_6 = alloca float, align 4
  %var_5 = alloca float, align 4
  %var_4 = alloca float, align 4
  %var_3 = alloca float, align 4
  %var_2 = alloca float, align 4
  %var_1 = alloca float, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 25, ptr %a, align 4
  store i32 32, ptr %b, align 4
  store float 1.250000e+00, ptr %var_1, align 4
  %load_a = load i32, ptr %a, align 4
  %cast_a = sitofp i32 %load_a to float
  store float %cast_a, ptr %var_2, align 4
  %load_var_2 = load float, ptr %var_2, align 4
  %load_var_1 = load float, ptr %var_1, align 4
  %rplus = fadd float %load_var_2, %load_var_1
  store float %rplus, ptr %var_3, align 4
  store float 0x4002E147A0000000, ptr %var_4, align 4
  %load_b = load i32, ptr %b, align 4
  %cast_b = sitofp i32 %load_b to float
  store float %cast_b, ptr %var_5, align 4
  %load_var_5 = load float, ptr %var_5, align 4
  %load_var_4 = load float, ptr %var_4, align 4
  %rmult = fmul float %load_var_5, %load_var_4
  store float %rmult, ptr %var_6, align 4
  %load_var_3 = load float, ptr %var_3, align 4
  %load_var_6 = load float, ptr %var_6, align 4
  %rplus1 = fadd float %load_var_3, %load_var_6
  store float %rplus1, ptr %var_7, align 4
  %load_a2 = load i32, ptr %a, align 4
  %cast_a3 = sitofp i32 %load_a2 to float
  store float %cast_a3, ptr %var_8, align 4
  %load_var_7 = load float, ptr %var_7, align 4
  %load_var_8 = load float, ptr %var_8, align 4
  %rminus = fsub float %load_var_7, %load_var_8
  store float %rminus, ptr %var_9, align 4
  store i32 0, ptr %var_10, align 4
  %load_var_10 = load i32, ptr %var_10, align 4
  ret i32 %load_var_10
}
    )";

    const std::string input = R"(
        fn main():int {
            let a:int = 25
            let b:int = 32
            a + 1.25 + b * 2.36 - a
            return 0
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T4)
{
    const std::string output = R"(
; ModuleID = 'main.o'
source_filename = "main.o"

define void @main(i32 %x, i32 %b) {
entry:
  %r = alloca float, align 4
  %var_5 = alloca float, align 4
  %x_alloca = alloca i32, align 4
  %var_4 = alloca float, align 4
  %var_3 = alloca float, align 4
  %b_alloca = alloca i32, align 4
  %var_2 = alloca float, align 4
  %var_1 = alloca float, align 4
  store float 0x3FF251EB80000000, ptr %var_1, align 4
  store i32 %b, ptr %b_alloca, align 4
  %load_b = load i32, ptr %b_alloca, align 4
  %cast_b = sitofp i32 %load_b to float
  store float %cast_b, ptr %var_2, align 4
  %load_var_2 = load float, ptr %var_2, align 4
  %load_var_1 = load float, ptr %var_1, align 4
  %rmult = fmul float %load_var_2, %load_var_1
  store float %rmult, ptr %var_3, align 4
  store i32 %x, ptr %x_alloca, align 4
  %load_x = load i32, ptr %x_alloca, align 4
  %cast_x = sitofp i32 %load_x to float
  store float %cast_x, ptr %var_4, align 4
  %load_var_4 = load float, ptr %var_4, align 4
  %load_var_3 = load float, ptr %var_3, align 4
  %rplus = fadd float %load_var_4, %load_var_3
  store float %rplus, ptr %var_5, align 4
  %load_var_5 = load float, ptr %var_5, align 4
  store float %load_var_5, ptr %r, align 4
  ret void
}

    )";

    const std::string input = R"(
        fn main(x:int, b:int) {
            let r:float = x + b * 1.145
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T5)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define i32 @sub(i32 %ax, i32 %bx, i32 %nx) {
    entry:
      %nx_alloca = alloca i32, align 4
      %var_4 = alloca i32, align 4
      %bx_alloca = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %ax_alloca = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_1 = alloca i32, align 4
      store i32 2, ptr %var_1, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %rdiv = sdiv i32 %load_ax, %load_var_1
      store i32 %rdiv, ptr %var_2, align 4
      store i32 %bx, ptr %bx_alloca, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_bx = load i32, ptr %bx_alloca, align 4
      %rplus = add i32 %load_var_2, %load_bx
      store i32 %rplus, ptr %var_3, align 4
      store i32 %nx, ptr %nx_alloca, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_nx = load i32, ptr %nx_alloca, align 4
      %rminus = sub i32 %load_var_3, %load_nx
      store i32 %rminus, ptr %var_4, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      ret i32 %load_var_4
    }

    define void @main() {
    entry:
      %r = alloca float, align 4
      %var_7 = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_2 = alloca i32, align 4
      %var_5 = alloca i32, align 4
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_1 = alloca float, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      store i32 1, ptr %var_3, align 4
      store i32 32, ptr %var_4, align 4
      store i32 25, ptr %var_5, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      %load_var_5 = load i32, ptr %var_5, align 4
      %call_sub = call i32 @sub(i32 %load_var_3, i32 %load_var_4, i32 %load_var_5)
      store i32 %call_sub, ptr %var_2, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %cast_var_2 = sitofp i32 %load_var_2 to float
      store float %cast_var_2, ptr %var_6, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      %rmult = fmul float %load_var_1, %load_var_6
      store float %rmult, ptr %var_7, align 4
      %load_var_7 = load float, ptr %var_7, align 4
      store float %load_var_7, ptr %r, align 4
      ret void
    }
    )";

    const std::string input = R"(
        fn sub(ax:int, bx:int, nx:int): int {
            return ax / 2 + bx - nx
        }

        fn main() {
            let r:float = 32.25 * sub(ax: 1, bx: 32, nx: 25)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T6)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define float @mult(i32 %n, float %p) {
    entry:
      %p_alloca = alloca float, align 4
      %var_2 = alloca float, align 4
      %n_alloca = alloca i32, align 4
      %var_1 = alloca float, align 4
      store i32 %n, ptr %n_alloca, align 4
      %load_n = load i32, ptr %n_alloca, align 4
      %cast_n = sitofp i32 %load_n to float
      store float %cast_n, ptr %var_1, align 4
      store float %p, ptr %p_alloca, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_p = load float, ptr %p_alloca, align 4
      %rmult = fmul float %load_var_1, %load_p
      store float %rmult, ptr %var_2, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      ret float %load_var_2
    }

    define float @sub(i32 %ax, float %bx) {
    entry:
      %bx_alloca = alloca float, align 4
      %var_2 = alloca float, align 4
      %ax_alloca = alloca i32, align 4
      %var_1 = alloca float, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %cast_ax = sitofp i32 %load_ax to float
      store float %cast_ax, ptr %var_1, align 4
      store float %bx, ptr %bx_alloca, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_bx = load float, ptr %bx_alloca, align 4
      %rminus = fsub float %load_var_1, %load_bx
      store float %rminus, ptr %var_2, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      ret float %load_var_2
    }

    define void @main() {
    entry:
      %var_6 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_5 = alloca float, align 4
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_1 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      store i32 1, ptr %var_3, align 4
      store i32 22, ptr %var_4, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      %load_x = load float, ptr %x, align 4
      %call_mult = call float @mult(i32 %load_var_4, float %load_x)
      store float %call_mult, ptr %var_5, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_var_5 = load float, ptr %var_5, align 4
      %call_sub = call float @sub(i32 %load_var_3, float %load_var_5)
      store float %call_sub, ptr %var_2, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rmult = fmul float %load_var_1, %load_var_2
      store float %rmult, ptr %var_6, align 4
      ret void
    }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {
            return n * p
        }

        fn sub(ax:int, bx:float): float {
            return ax - bx
        }

        fn main() {
            let x: float = 25.00
            32.25 * sub(ax: 1, bx: mult(n:22, p:x))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T7)
{
    const std::string output = R"(
        ; ModuleID = 'main.o'
        source_filename = "main.o"

        define float @mult(i32 %n, float %p) {
        entry:
          %p_alloca = alloca float, align 4
          %var_2 = alloca float, align 4
          %n_alloca = alloca i32, align 4
          %var_1 = alloca float, align 4
          store i32 %n, ptr %n_alloca, align 4
          %load_n = load i32, ptr %n_alloca, align 4
          %cast_n = sitofp i32 %load_n to float
          store float %cast_n, ptr %var_1, align 4
          store float %p, ptr %p_alloca, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %load_p = load float, ptr %p_alloca, align 4
          %rmult = fmul float %load_var_1, %load_p
          store float %rmult, ptr %var_2, align 4
          %load_var_2 = load float, ptr %var_2, align 4
          ret float %load_var_2
        }

        define float @sub(i32 %ax, float %bx) {
        entry:
          %bx_alloca = alloca float, align 4
          %var_2 = alloca float, align 4
          %ax_alloca = alloca i32, align 4
          %var_1 = alloca float, align 4
          store i32 %ax, ptr %ax_alloca, align 4
          %load_ax = load i32, ptr %ax_alloca, align 4
          %cast_ax = sitofp i32 %load_ax to float
          store float %cast_ax, ptr %var_1, align 4
          store float %bx, ptr %bx_alloca, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %load_bx = load float, ptr %bx_alloca, align 4
          %rminus = fsub float %load_var_1, %load_bx
          store float %rminus, ptr %var_2, align 4
          %load_var_2 = load float, ptr %var_2, align 4
          ret float %load_var_2
        }

        define void @main() {
        entry:
          %var_8 = alloca float, align 4
          %var_2 = alloca float, align 4
          %var_7 = alloca float, align 4
          %var_6 = alloca float, align 4
          %var_5 = alloca i32, align 4
          %var_4 = alloca i32, align 4
          %var_3 = alloca i32, align 4
          %var_1 = alloca float, align 4
          %x = alloca float, align 4
          store float 2.500000e+01, ptr %x, align 4
          store float 3.225000e+01, ptr %var_1, align 4
          store i32 1, ptr %var_3, align 4
          store i32 22, ptr %var_4, align 4
          store i32 25, ptr %var_5, align 4
          %load_var_5 = load i32, ptr %var_5, align 4
          %load_x = load float, ptr %x, align 4
          %call_gfn_main_inline = call float @gfn_main_inline(i32 %load_var_5, float %load_x)
          store float %call_gfn_main_inline, ptr %var_6, align 4
          %load_var_4 = load i32, ptr %var_4, align 4
          %load_var_6 = load float, ptr %var_6, align 4
          %call_mult = call float @mult(i32 %load_var_4, float %load_var_6)
          store float %call_mult, ptr %var_7, align 4
          %load_var_3 = load i32, ptr %var_3, align 4
          %load_var_7 = load float, ptr %var_7, align 4
          %call_sub = call float @sub(i32 %load_var_3, float %load_var_7)
          store float %call_sub, ptr %var_2, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %load_var_2 = load float, ptr %var_2, align 4
          %rmult = fmul float %load_var_1, %load_var_2
          store float %rmult, ptr %var_8, align 4
          ret void
        }

        define float @gfn_main_inline(i32 %a, float %x) {
        entry:
          %x_alloca = alloca float, align 4
          %var_2 = alloca float, align 4
          %a_alloca = alloca i32, align 4
          %var_1 = alloca float, align 4
          store i32 %a, ptr %a_alloca, align 4
          %load_a = load i32, ptr %a_alloca, align 4
          %cast_a = sitofp i32 %load_a to float
          store float %cast_a, ptr %var_1, align 4
          store float %x, ptr %x_alloca, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %load_x = load float, ptr %x_alloca, align 4
          %rmult = fmul float %load_var_1, %load_x
          store float %rmult, ptr %var_2, align 4
          %load_var_2 = load float, ptr %var_2, align 4
          ret float %load_var_2
        }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {
            return n * p
        }

        fn sub(ax:int, bx:float): float {
            return ax - bx
        }

        fn main() {
            let x: float = 25.00
            let inline:fn = (a:int):float -> a * x
            32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:25)))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T8)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define float @mult(i32 %n, float %p) {
    entry:
      %p_alloca = alloca float, align 4
      %var_2 = alloca float, align 4
      %n_alloca = alloca i32, align 4
      %var_1 = alloca float, align 4
      store i32 %n, ptr %n_alloca, align 4
      %load_n = load i32, ptr %n_alloca, align 4
      %cast_n = sitofp i32 %load_n to float
      store float %cast_n, ptr %var_1, align 4
      store float %p, ptr %p_alloca, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_p = load float, ptr %p_alloca, align 4
      %rmult = fmul float %load_var_1, %load_p
      store float %rmult, ptr %var_2, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      ret float %load_var_2
    }

    define float @sub(i32 %ax, float %bx) {
    entry:
      %bx_alloca = alloca float, align 4
      %var_2 = alloca float, align 4
      %ax_alloca = alloca i32, align 4
      %var_1 = alloca float, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %cast_ax = sitofp i32 %load_ax to float
      store float %cast_ax, ptr %var_1, align 4
      store float %bx, ptr %bx_alloca, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_bx = load float, ptr %bx_alloca, align 4
      %rminus = fsub float %load_var_1, %load_bx
      store float %rminus, ptr %var_2, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      ret float %load_var_2
    }

    define float @main() {
    entry:
      %var_9 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_8 = alloca float, align 4
      %var_7 = alloca float, align 4
      %var_6 = alloca i32, align 4
      %var_5 = alloca i32, align 4
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_1 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      store i32 1, ptr %var_3, align 4
      store i32 22, ptr %var_4, align 4
      store i32 25, ptr %var_5, align 4
      %load_var_5 = load i32, ptr %var_5, align 4
      %load_x = load float, ptr %x, align 4
      %call_gfn_main_block = call i32 @gfn_main_block(i32 %load_var_5, float %load_x)
      store i32 %call_gfn_main_block, ptr %var_6, align 4
      %load_var_6 = load i32, ptr %var_6, align 4
      %load_x1 = load float, ptr %x, align 4
      %call_gfn_main_inline = call float @gfn_main_inline(i32 %load_var_6, float %load_x1)
      store float %call_gfn_main_inline, ptr %var_7, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      %load_var_7 = load float, ptr %var_7, align 4
      %call_mult = call float @mult(i32 %load_var_4, float %load_var_7)
      store float %call_mult, ptr %var_8, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_var_8 = load float, ptr %var_8, align 4
      %call_sub = call float @sub(i32 %load_var_3, float %load_var_8)
      store float %call_sub, ptr %var_2, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rmult = fmul float %load_var_1, %load_var_2
      store float %rmult, ptr %var_9, align 4
      %load_var_9 = load float, ptr %var_9, align 4
      ret float %load_var_9
    }

    define i32 @gfn_main_block(i32 %a, float %x) {
    entry:
      %a_alloca = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_1 = alloca i32, align 4
      store i32 125, ptr %var_1, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %rmult = mul i32 %load_a, %load_var_1
      store i32 %rmult, ptr %var_2, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      ret i32 %load_var_2
    }

    define float @gfn_main_inline(i32 %a, float %x) {
    entry:
      %x_alloca = alloca float, align 4
      %var_2 = alloca float, align 4
      %a_alloca = alloca i32, align 4
      %var_1 = alloca float, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %cast_a = sitofp i32 %load_a to float
      store float %cast_a, ptr %var_1, align 4
      store float %x, ptr %x_alloca, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_x = load float, ptr %x_alloca, align 4
      %rmult = fmul float %load_var_1, %load_x
      store float %rmult, ptr %var_2, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      ret float %load_var_2
    }
    )";

    const std::string input = R"(
        fn mult(n:int, p:float): float {
            return n * p
        }

        fn sub(ax:int, bx:float): float {
            return ax - bx
        }

        fn main(): float {
            let x: float = 25.00

            let block:fn = (a:int):int -> {
                return a * 125
            }

            let inline:fn = (a:int):float -> a * x
            return 32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:block(a:25))))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T9)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define void @main() {
    entry:
      %exprBool8 = alloca i1, align 1
      %var_89 = alloca i1, align 1
      %var_88 = alloca i1, align 1
      %var_87 = alloca i1, align 1
      %var_86 = alloca i32, align 4
      %var_85 = alloca i32, align 4
      %var_84 = alloca i1, align 1
      %var_83 = alloca i1, align 1
      %var_82 = alloca i1, align 1
      %var_81 = alloca i1, align 1
      %var_80 = alloca i32, align 4
      %var_79 = alloca i1, align 1
      %var_78 = alloca i32, align 4
      %var_77 = alloca i32, align 4
      %var_76 = alloca i32, align 4
      %var_75 = alloca i1, align 1
      %var_74 = alloca i32, align 4
      %exprBool7 = alloca i1, align 1
      %var_73 = alloca i1, align 1
      %var_72 = alloca i1, align 1
      %var_71 = alloca i1, align 1
      %var_70 = alloca i32, align 4
      %var_69 = alloca i32, align 4
      %var_68 = alloca i1, align 1
      %var_67 = alloca i32, align 4
      %var_66 = alloca i32, align 4
      %var_65 = alloca i32, align 4
      %var_64 = alloca i1, align 1
      %var_63 = alloca i1, align 1
      %var_62 = alloca float, align 4
      %var_61 = alloca i32, align 4
      %var_60 = alloca i1, align 1
      %var_59 = alloca i1, align 1
      %var_58 = alloca i32, align 4
      %var_57 = alloca i1, align 1
      %var_56 = alloca i1, align 1
      %var_55 = alloca i32, align 4
      %var_54 = alloca i32, align 4
      %var_53 = alloca i1, align 1
      %var_52 = alloca i32, align 4
      %var_51 = alloca i32, align 4
      %b = alloca float, align 4
      %a = alloca i32, align 4
      %exprBool6 = alloca i1, align 1
      %var_50 = alloca i1, align 1
      %var_49 = alloca i1, align 1
      %var_48 = alloca i32, align 4
      %var_47 = alloca i32, align 4
      %var_46 = alloca i32, align 4
      %var_45 = alloca i32, align 4
      %var_44 = alloca i1, align 1
      %var_43 = alloca i1, align 1
      %var_42 = alloca i32, align 4
      %var_41 = alloca i32, align 4
      %var_40 = alloca i1, align 1
      %var_39 = alloca i1, align 1
      %var_38 = alloca i32, align 4
      %var_37 = alloca i1, align 1
      %var_36 = alloca i1, align 1
      %var_35 = alloca i32, align 4
      %var_34 = alloca i32, align 4
      %var_33 = alloca i32, align 4
      %var_32 = alloca i1, align 1
      %var_31 = alloca i32, align 4
      %var_30 = alloca i32, align 4
      %exprBool5 = alloca i1, align 1
      %var_29 = alloca i1, align 1
      %var_28 = alloca i1, align 1
      %var_27 = alloca i32, align 4
      %var_26 = alloca i32, align 4
      %var_25 = alloca i1, align 1
      %var_24 = alloca i1, align 1
      %var_23 = alloca i32, align 4
      %var_22 = alloca i1, align 1
      %var_21 = alloca i1, align 1
      %var_20 = alloca i32, align 4
      %var_19 = alloca i32, align 4
      %var_18 = alloca i32, align 4
      %var_17 = alloca i1, align 1
      %var_16 = alloca i32, align 4
      %var_15 = alloca i32, align 4
      %exprBool4 = alloca i1, align 1
      %var_14 = alloca i1, align 1
      %var_13 = alloca i32, align 4
      %var_12 = alloca i32, align 4
      %exprBool3 = alloca i1, align 1
      %var_11 = alloca i1, align 1
      %var_10 = alloca i32, align 4
      %var_9 = alloca i32, align 4
      %exprBool2 = alloca i1, align 1
      %var_8 = alloca i1, align 1
      %var_7 = alloca i32, align 4
      %var_6 = alloca i32, align 4
      %exprBool1 = alloca i1, align 1
      %var_5 = alloca i1, align 1
      %var_4 = alloca i1, align 1
      %var_3 = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_1 = alloca i1, align 1
      store i1 true, ptr %var_1, align 1
      store i32 3, ptr %var_2, align 4
      store i32 1, ptr %var_3, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %cmp_gt = icmp sgt i32 %load_var_2, %load_var_3
      store i1 %cmp_gt, ptr %var_4, align 1
      %load_var_4 = load i1, ptr %var_4, align 1
      %load_var_1 = load i1, ptr %var_1, align 1
      %not_ = xor i1 %load_var_4, %load_var_1
      store i1 %not_, ptr %var_5, align 1
      %load_var_5 = load i1, ptr %var_5, align 1
      store i1 %load_var_5, ptr %exprBool1, align 1
      store i32 3, ptr %var_6, align 4
      store i32 1, ptr %var_7, align 4
      %load_var_6 = load i32, ptr %var_6, align 4
      %load_var_7 = load i32, ptr %var_7, align 4
      %cmp_gt1 = icmp sgt i32 %load_var_6, %load_var_7
      store i1 %cmp_gt1, ptr %var_8, align 1
      %load_var_8 = load i1, ptr %var_8, align 1
      store i1 %load_var_8, ptr %exprBool2, align 1
      store i32 3, ptr %var_9, align 4
      store i32 1, ptr %var_10, align 4
      %load_var_9 = load i32, ptr %var_9, align 4
      %load_var_10 = load i32, ptr %var_10, align 4
      %cmp_neq = icmp ne i32 %load_var_9, %load_var_10
      store i1 %cmp_neq, ptr %var_11, align 1
      %load_var_11 = load i1, ptr %var_11, align 1
      store i1 %load_var_11, ptr %exprBool3, align 1
      store i32 3, ptr %var_12, align 4
      store i32 1, ptr %var_13, align 4
      %load_var_12 = load i32, ptr %var_12, align 4
      %load_var_13 = load i32, ptr %var_13, align 4
      %cmp_eq = icmp eq i32 %load_var_12, %load_var_13
      store i1 %cmp_eq, ptr %var_14, align 1
      %load_var_14 = load i1, ptr %var_14, align 1
      store i1 %load_var_14, ptr %exprBool4, align 1
      store i32 5, ptr %var_15, align 4
      store i32 3, ptr %var_16, align 4
      %load_var_15 = load i32, ptr %var_15, align 4
      %load_var_16 = load i32, ptr %var_16, align 4
      %cmp_gt2 = icmp sgt i32 %load_var_15, %load_var_16
      store i1 %cmp_gt2, ptr %var_17, align 1
      store i32 25, ptr %var_18, align 4
      store i32 6, ptr %var_19, align 4
      %load_var_18 = load i32, ptr %var_18, align 4
      %load_var_19 = load i32, ptr %var_19, align 4
      %rmult = mul i32 %load_var_18, %load_var_19
      store i32 %rmult, ptr %var_20, align 4
      %load_var_20 = load i32, ptr %var_20, align 4
      %cast_var_20 = icmp ne i32 %load_var_20, 0
      store i1 %cast_var_20, ptr %var_21, align 1
      %load_var_17 = load i1, ptr %var_17, align 1
      %load_var_21 = load i1, ptr %var_21, align 1
      %cmp_neq3 = icmp ne i1 %load_var_17, %load_var_21
      store i1 %cmp_neq3, ptr %var_22, align 1
      store i32 5, ptr %var_23, align 4
      %load_var_23 = load i32, ptr %var_23, align 4
      %cast_var_23 = icmp ne i32 %load_var_23, 0
      store i1 %cast_var_23, ptr %var_24, align 1
      %load_var_22 = load i1, ptr %var_22, align 1
      %load_var_24 = load i1, ptr %var_24, align 1
      %cmp_lt = icmp slt i1 %load_var_22, %load_var_24
      store i1 %cmp_lt, ptr %var_25, align 1
      store i32 25, ptr %var_26, align 4
      store i32 25, ptr %var_27, align 4
      %load_var_26 = load i32, ptr %var_26, align 4
      %load_var_27 = load i32, ptr %var_27, align 4
      %cmp_eq4 = icmp eq i32 %load_var_26, %load_var_27
      store i1 %cmp_eq4, ptr %var_28, align 1
      %load_var_25 = load i1, ptr %var_25, align 1
      %load_var_28 = load i1, ptr %var_28, align 1
      %cmp_neq5 = icmp ne i1 %load_var_25, %load_var_28
      store i1 %cmp_neq5, ptr %var_29, align 1
      %load_var_29 = load i1, ptr %var_29, align 1
      store i1 %load_var_29, ptr %exprBool5, align 1
      store i32 5, ptr %var_30, align 4
      store i32 3, ptr %var_31, align 4
      %load_var_30 = load i32, ptr %var_30, align 4
      %load_var_31 = load i32, ptr %var_31, align 4
      %cmp_gt6 = icmp sgt i32 %load_var_30, %load_var_31
      store i1 %cmp_gt6, ptr %var_32, align 1
      store i32 25, ptr %var_33, align 4
      store i32 6, ptr %var_34, align 4
      %load_var_33 = load i32, ptr %var_33, align 4
      %load_var_34 = load i32, ptr %var_34, align 4
      %rmult7 = mul i32 %load_var_33, %load_var_34
      store i32 %rmult7, ptr %var_35, align 4
      %load_var_35 = load i32, ptr %var_35, align 4
      %cast_var_35 = icmp ne i32 %load_var_35, 0
      store i1 %cast_var_35, ptr %var_36, align 1
      %load_var_32 = load i1, ptr %var_32, align 1
      %load_var_36 = load i1, ptr %var_36, align 1
      %cmp_neq8 = icmp ne i1 %load_var_32, %load_var_36
      store i1 %cmp_neq8, ptr %var_37, align 1
      store i32 5, ptr %var_38, align 4
      %load_var_38 = load i32, ptr %var_38, align 4
      %cast_var_38 = icmp ne i32 %load_var_38, 0
      store i1 %cast_var_38, ptr %var_39, align 1
      %load_var_37 = load i1, ptr %var_37, align 1
      %load_var_39 = load i1, ptr %var_39, align 1
      %cmp_lt9 = icmp slt i1 %load_var_37, %load_var_39
      store i1 %cmp_lt9, ptr %var_40, align 1
      store i32 25, ptr %var_41, align 4
      store i32 25, ptr %var_42, align 4
      %load_var_41 = load i32, ptr %var_41, align 4
      %load_var_42 = load i32, ptr %var_42, align 4
      %cmp_eq10 = icmp eq i32 %load_var_41, %load_var_42
      store i1 %cmp_eq10, ptr %var_43, align 1
      %load_var_40 = load i1, ptr %var_40, align 1
      %load_var_43 = load i1, ptr %var_43, align 1
      %cmp_neq11 = icmp ne i1 %load_var_40, %load_var_43
      store i1 %cmp_neq11, ptr %var_44, align 1
      store i32 32, ptr %var_45, align 4
      store i32 2, ptr %var_46, align 4
      %load_var_45 = load i32, ptr %var_45, align 4
      %load_var_46 = load i32, ptr %var_46, align 4
      %rdiv = sdiv i32 %load_var_45, %load_var_46
      store i32 %rdiv, ptr %var_47, align 4
      store i32 5, ptr %var_48, align 4
      %load_var_47 = load i32, ptr %var_47, align 4
      %load_var_48 = load i32, ptr %var_48, align 4
      %cmp_gt12 = icmp sgt i32 %load_var_47, %load_var_48
      store i1 %cmp_gt12, ptr %var_49, align 1
      %load_var_44 = load i1, ptr %var_44, align 1
      %load_var_49 = load i1, ptr %var_49, align 1
      %or_ = or i1 %load_var_44, %load_var_49
      store i1 %or_, ptr %var_50, align 1
      %load_var_50 = load i1, ptr %var_50, align 1
      store i1 %load_var_50, ptr %exprBool6, align 1
      store i32 12, ptr %a, align 4
      store float 0x3FF99999A0000000, ptr %b, align 4
      store i32 5, ptr %var_51, align 4
      store i32 3, ptr %var_52, align 4
      %load_var_51 = load i32, ptr %var_51, align 4
      %load_var_52 = load i32, ptr %var_52, align 4
      %cmp_gt13 = icmp sgt i32 %load_var_51, %load_var_52
      store i1 %cmp_gt13, ptr %var_53, align 1
      store i32 6, ptr %var_54, align 4
      %load_a = load i32, ptr %a, align 4
      %load_var_54 = load i32, ptr %var_54, align 4
      %rmult14 = mul i32 %load_a, %load_var_54
      store i32 %rmult14, ptr %var_55, align 4
      %load_var_55 = load i32, ptr %var_55, align 4
      %cast_var_55 = icmp ne i32 %load_var_55, 0
      store i1 %cast_var_55, ptr %var_56, align 1
      %load_var_53 = load i1, ptr %var_53, align 1
      %load_var_56 = load i1, ptr %var_56, align 1
      %cmp_neq15 = icmp ne i1 %load_var_53, %load_var_56
      store i1 %cmp_neq15, ptr %var_57, align 1
      store i32 5, ptr %var_58, align 4
      %load_var_58 = load i32, ptr %var_58, align 4
      %cast_var_58 = icmp ne i32 %load_var_58, 0
      store i1 %cast_var_58, ptr %var_59, align 1
      %load_var_57 = load i1, ptr %var_57, align 1
      %load_var_59 = load i1, ptr %var_59, align 1
      %cmp_lt16 = icmp slt i1 %load_var_57, %load_var_59
      store i1 %cmp_lt16, ptr %var_60, align 1
      store i32 25, ptr %var_61, align 4
      %load_var_61 = load i32, ptr %var_61, align 4
      %cast_var_61 = sitofp i32 %load_var_61 to float
      store float %cast_var_61, ptr %var_62, align 4
      %load_var_62 = load float, ptr %var_62, align 4
      %load_b = load float, ptr %b, align 4
      %cmp_eq17 = fcmp oeq float %load_var_62, %load_b
      store i1 %cmp_eq17, ptr %var_63, align 1
      %load_var_60 = load i1, ptr %var_60, align 1
      %load_var_63 = load i1, ptr %var_63, align 1
      %cmp_neq18 = icmp ne i1 %load_var_60, %load_var_63
      store i1 %cmp_neq18, ptr %var_64, align 1
      store i32 32, ptr %var_65, align 4
      store i32 2, ptr %var_66, align 4
      %load_var_65 = load i32, ptr %var_65, align 4
      %load_var_66 = load i32, ptr %var_66, align 4
      %rdiv19 = sdiv i32 %load_var_65, %load_var_66
      store i32 %rdiv19, ptr %var_67, align 4
      %load_var_67 = load i32, ptr %var_67, align 4
      %load_a20 = load i32, ptr %a, align 4
      %cmp_gt21 = icmp sgt i32 %load_var_67, %load_a20
      store i1 %cmp_gt21, ptr %var_68, align 1
      store i32 2, ptr %var_69, align 4
      store i32 2, ptr %var_70, align 4
      %load_var_69 = load i32, ptr %var_69, align 4
      %load_var_70 = load i32, ptr %var_70, align 4
      %cmp_gt22 = icmp sgt i32 %load_var_69, %load_var_70
      store i1 %cmp_gt22, ptr %var_71, align 1
      %load_var_68 = load i1, ptr %var_68, align 1
      %load_var_71 = load i1, ptr %var_71, align 1
      %and_ = and i1 %load_var_68, %load_var_71
      store i1 %and_, ptr %var_72, align 1
      %load_var_64 = load i1, ptr %var_64, align 1
      %load_var_72 = load i1, ptr %var_72, align 1
      %or_23 = or i1 %load_var_64, %load_var_72
      store i1 %or_23, ptr %var_73, align 1
      %load_var_73 = load i1, ptr %var_73, align 1
      store i1 %load_var_73, ptr %exprBool7, align 1
      store i32 5, ptr %var_74, align 4
      %load_var_74 = load i32, ptr %var_74, align 4
      %load_a24 = load i32, ptr %a, align 4
      %cmp_gt25 = icmp sgt i32 %load_var_74, %load_a24
      store i1 %cmp_gt25, ptr %var_75, align 1
      store i32 25, ptr %var_76, align 4
      store i32 6, ptr %var_77, align 4
      %load_var_76 = load i32, ptr %var_76, align 4
      %load_var_77 = load i32, ptr %var_77, align 4
      %rmult26 = mul i32 %load_var_76, %load_var_77
      store i32 %rmult26, ptr %var_78, align 4
      %load_var_78 = load i32, ptr %var_78, align 4
      %load_a27 = load i32, ptr %a, align 4
      %cmp_lt28 = icmp slt i32 %load_var_78, %load_a27
      store i1 %cmp_lt28, ptr %var_79, align 1
      store i32 2, ptr %var_80, align 4
      %load_var_80 = load i32, ptr %var_80, align 4
      %cast_var_80 = icmp ne i32 %load_var_80, 0
      store i1 %cast_var_80, ptr %var_81, align 1
      %load_var_79 = load i1, ptr %var_79, align 1
      %load_var_81 = load i1, ptr %var_81, align 1
      %cmp_neq29 = icmp ne i1 %load_var_79, %load_var_81
      store i1 %cmp_neq29, ptr %var_82, align 1
      %load_var_75 = load i1, ptr %var_75, align 1
      %load_var_82 = load i1, ptr %var_82, align 1
      %cmp_neq30 = icmp ne i1 %load_var_75, %load_var_82
      store i1 %cmp_neq30, ptr %var_83, align 1
      store i1 true, ptr %var_84, align 1
      store i32 25, ptr %var_85, align 4
      store i32 25, ptr %var_86, align 4
      %load_var_85 = load i32, ptr %var_85, align 4
      %load_var_86 = load i32, ptr %var_86, align 4
      %cmp_eq31 = icmp eq i32 %load_var_85, %load_var_86
      store i1 %cmp_eq31, ptr %var_87, align 1
      %load_var_87 = load i1, ptr %var_87, align 1
      %load_var_84 = load i1, ptr %var_84, align 1
      %not_32 = xor i1 %load_var_87, %load_var_84
      store i1 %not_32, ptr %var_88, align 1
      %load_var_83 = load i1, ptr %var_83, align 1
      %load_var_88 = load i1, ptr %var_88, align 1
      %cmp_eq33 = icmp eq i1 %load_var_83, %load_var_88
      store i1 %cmp_eq33, ptr %var_89, align 1
      %load_var_89 = load i1, ptr %var_89, align 1
      store i1 %load_var_89, ptr %exprBool8, align 1
      ret void
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

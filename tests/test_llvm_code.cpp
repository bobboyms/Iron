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
      %var_7 = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_5 = alloca i32, align 4
      %var_4 = alloca float, align 4
      %var_3 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_1 = alloca float, align 4
      %var_0 = alloca i32, align 4
      %b = alloca float, align 4
      %a = alloca i32, align 4
      store i32 10, ptr %a, align 4
      store float 2.050000e+01, ptr %b, align 4
      store i32 2, ptr %var_0, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %cast_var_0 = sitofp i32 %load_var_0 to float
      store float %cast_var_0, ptr %var_1, align 4
      %load_b = load float, ptr %b, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %rdiv = fdiv float %load_b, %load_var_1
      store float %rdiv, ptr %var_2, align 4
      %load_a = load i32, ptr %a, align 4
      %cast_a = sitofp i32 %load_a to float
      store float %cast_a, ptr %var_3, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rplus = fadd float %load_var_3, %load_var_2
      store float %rplus, ptr %var_4, align 4
      store i32 3, ptr %var_5, align 4
      %load_var_5 = load i32, ptr %var_5, align 4
      %cast_var_5 = sitofp i32 %load_var_5 to float
      store float %cast_var_5, ptr %var_6, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      %rmult = fmul float %load_var_4, %load_var_6
      store float %rmult, ptr %var_7, align 4
      %load_var_7 = load float, ptr %var_7, align 4
      store float %load_var_7, ptr %r, align 4
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
      %var_12 = alloca double, align 8
      %var_11 = alloca double, align 8
      %var_10 = alloca double, align 8
      %var_9 = alloca double, align 8
      %var_8 = alloca float, align 4
      %r = alloca float, align 4
      %var_7 = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_5 = alloca i32, align 4
      %var_4 = alloca float, align 4
      %var_3 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_1 = alloca float, align 4
      %var_0 = alloca i32, align 4
      %d = alloca double, align 8
      %b = alloca float, align 4
      %a = alloca i32, align 4
      store i32 10, ptr %a, align 4
      store float 0x4026B851E0000000, ptr %b, align 4
      store double 2.050000e+01, ptr %d, align 8
      store i32 2, ptr %var_0, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %cast_var_0 = sitofp i32 %load_var_0 to float
      store float %cast_var_0, ptr %var_1, align 4
      %load_b = load float, ptr %b, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %rdiv = fdiv float %load_b, %load_var_1
      store float %rdiv, ptr %var_2, align 4
      %load_a = load i32, ptr %a, align 4
      %cast_a = sitofp i32 %load_a to float
      store float %cast_a, ptr %var_3, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rplus = fadd float %load_var_3, %load_var_2
      store float %rplus, ptr %var_4, align 4
      store i32 3, ptr %var_5, align 4
      %load_var_5 = load i32, ptr %var_5, align 4
      %cast_var_5 = sitofp i32 %load_var_5 to float
      store float %cast_var_5, ptr %var_6, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      %rmult = fmul float %load_var_4, %load_var_6
      store float %rmult, ptr %var_7, align 4
      %load_var_7 = load float, ptr %var_7, align 4
      store float %load_var_7, ptr %r, align 4
      store float 2.500000e+00, ptr %var_8, align 4
      %load_var_8 = load float, ptr %var_8, align 4
      %cast_var_8 = fpext float %load_var_8 to double
      store double %cast_var_8, ptr %var_9, align 8
      %load_var_9 = load double, ptr %var_9, align 8
      %load_d = load double, ptr %d, align 8
      %rdiv1 = fdiv double %load_var_9, %load_d
      store double %rdiv1, ptr %var_10, align 8
      %load_r = load float, ptr %r, align 4
      %cast_r = fpext float %load_r to double
      store double %cast_r, ptr %var_11, align 8
      %load_var_11 = load double, ptr %var_11, align 8
      %load_var_10 = load double, ptr %var_10, align 8
      %rminus = fsub double %load_var_11, %load_var_10
      store double %rminus, ptr %var_12, align 8
      %load_var_12 = load double, ptr %var_12, align 8
      store double %load_var_12, ptr %r2, align 8
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
      %var_9 = alloca i32, align 4
      %var_8 = alloca float, align 4
      %var_7 = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_5 = alloca float, align 4
      %var_4 = alloca float, align 4
      %var_3 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_1 = alloca float, align 4
      %var_0 = alloca float, align 4
      %b = alloca i32, align 4
      %a = alloca i32, align 4
      store i32 25, ptr %a, align 4
      store i32 32, ptr %b, align 4
      store float 1.250000e+00, ptr %var_0, align 4
      %load_a = load i32, ptr %a, align 4
      %cast_a = sitofp i32 %load_a to float
      store float %cast_a, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %rplus = fadd float %load_var_1, %load_var_0
      store float %rplus, ptr %var_2, align 4
      store float 0x4002E147A0000000, ptr %var_3, align 4
      %load_b = load i32, ptr %b, align 4
      %cast_b = sitofp i32 %load_b to float
      store float %cast_b, ptr %var_4, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %rmult = fmul float %load_var_4, %load_var_3
      store float %rmult, ptr %var_5, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %load_var_5 = load float, ptr %var_5, align 4
      %rplus1 = fadd float %load_var_2, %load_var_5
      store float %rplus1, ptr %var_6, align 4
      %load_a2 = load i32, ptr %a, align 4
      %cast_a3 = sitofp i32 %load_a2 to float
      store float %cast_a3, ptr %var_7, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      %load_var_7 = load float, ptr %var_7, align 4
      %rminus = fsub float %load_var_6, %load_var_7
      store float %rminus, ptr %var_8, align 4
      store i32 0, ptr %var_9, align 4
      %load_var_9 = load i32, ptr %var_9, align 4
      ret i32 %load_var_9
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
      %var_4 = alloca float, align 4
      %x_alloca = alloca i32, align 4
      %var_3 = alloca float, align 4
      %var_2 = alloca float, align 4
      %b_alloca = alloca i32, align 4
      %var_1 = alloca float, align 4
      %var_0 = alloca float, align 4
      store float 0x3FF251EB80000000, ptr %var_0, align 4
      store i32 %b, ptr %b_alloca, align 4
      %load_b = load i32, ptr %b_alloca, align 4
      %cast_b = sitofp i32 %load_b to float
      store float %cast_b, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %rmult = fmul float %load_var_1, %load_var_0
      store float %rmult, ptr %var_2, align 4
      store i32 %x, ptr %x_alloca, align 4
      %load_x = load i32, ptr %x_alloca, align 4
      %cast_x = sitofp i32 %load_x to float
      store float %cast_x, ptr %var_3, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rplus = fadd float %load_var_3, %load_var_2
      store float %rplus, ptr %var_4, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      store float %load_var_4, ptr %r, align 4
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
      %var_3 = alloca i32, align 4
      %bx_alloca = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %ax_alloca = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 2, ptr %var_0, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %rdiv = sdiv i32 %load_ax, %load_var_0
      store i32 %rdiv, ptr %var_1, align 4
      store i32 %bx, ptr %bx_alloca, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %load_bx = load i32, ptr %bx_alloca, align 4
      %rplus = add i32 %load_var_1, %load_bx
      store i32 %rplus, ptr %var_2, align 4
      store i32 %nx, ptr %nx_alloca, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_nx = load i32, ptr %nx_alloca, align 4
      %rminus = sub i32 %load_var_2, %load_nx
      store i32 %rminus, ptr %var_3, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      ret i32 %load_var_3
    }

    define void @main() {
    entry:
      %r = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_5 = alloca float, align 4
      %var_1 = alloca i32, align 4
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_0 = alloca float, align 4
      store float 3.225000e+01, ptr %var_0, align 4
      store i32 1, ptr %var_2, align 4
      store i32 32, ptr %var_3, align 4
      store i32 25, ptr %var_4, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      %call_sub = call i32 @sub(i32 %load_var_2, i32 %load_var_3, i32 %load_var_4)
      store i32 %call_sub, ptr %var_1, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %cast_var_1 = sitofp i32 %load_var_1 to float
      store float %cast_var_1, ptr %var_5, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_var_5 = load float, ptr %var_5, align 4
      %rmult = fmul float %load_var_0, %load_var_5
      store float %rmult, ptr %var_6, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      store float %load_var_6, ptr %r, align 4
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
      %var_1 = alloca float, align 4
      %n_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %n, ptr %n_alloca, align 4
      %load_n = load i32, ptr %n_alloca, align 4
      %cast_n = sitofp i32 %load_n to float
      store float %cast_n, ptr %var_0, align 4
      store float %p, ptr %p_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_p = load float, ptr %p_alloca, align 4
      %rmult = fmul float %load_var_0, %load_p
      store float %rmult, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
    }

    define float @sub(i32 %ax, float %bx) {
    entry:
      %bx_alloca = alloca float, align 4
      %var_1 = alloca float, align 4
      %ax_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %cast_ax = sitofp i32 %load_ax to float
      store float %cast_ax, ptr %var_0, align 4
      store float %bx, ptr %bx_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_bx = load float, ptr %bx_alloca, align 4
      %rminus = fsub float %load_var_0, %load_bx
      store float %rminus, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
    }

    define void @main() {
    entry:
      %var_5 = alloca float, align 4
      %var_1 = alloca float, align 4
      %var_4 = alloca float, align 4
      %var_3 = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_0 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      store float 3.225000e+01, ptr %var_0, align 4
      store i32 1, ptr %var_2, align 4
      store i32 22, ptr %var_3, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_x = load float, ptr %x, align 4
      %call_mult = call float @mult(i32 %load_var_3, float %load_x)
      store float %call_mult, ptr %var_4, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      %call_sub = call float @sub(i32 %load_var_2, float %load_var_4)
      store float %call_sub, ptr %var_1, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %rmult = fmul float %load_var_0, %load_var_1
      store float %rmult, ptr %var_5, align 4
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
      %var_1 = alloca float, align 4
      %n_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %n, ptr %n_alloca, align 4
      %load_n = load i32, ptr %n_alloca, align 4
      %cast_n = sitofp i32 %load_n to float
      store float %cast_n, ptr %var_0, align 4
      store float %p, ptr %p_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_p = load float, ptr %p_alloca, align 4
      %rmult = fmul float %load_var_0, %load_p
      store float %rmult, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
    }

    define float @sub(i32 %ax, float %bx) {
    entry:
      %bx_alloca = alloca float, align 4
      %var_1 = alloca float, align 4
      %ax_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %cast_ax = sitofp i32 %load_ax to float
      store float %cast_ax, ptr %var_0, align 4
      store float %bx, ptr %bx_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_bx = load float, ptr %bx_alloca, align 4
      %rminus = fsub float %load_var_0, %load_bx
      store float %rminus, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
    }

    define void @main() {
    entry:
      %var_7 = alloca float, align 4
      %var_1 = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_5 = alloca float, align 4
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_0 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      %inline = alloca ptr, align 8
      store ptr @gfn_main_inline, ptr %inline, align 8
      store float 3.225000e+01, ptr %var_0, align 4
      store i32 1, ptr %var_2, align 4
      store i32 22, ptr %var_3, align 4
      store i32 25, ptr %var_4, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      %load_x = load float, ptr %x, align 4
      %arrow_inline_loaded = load ptr, ptr %inline, align 8
      %call_inline = call float %arrow_inline_loaded(i32 %load_var_4, float %load_x)
      store float %call_inline, ptr %var_5, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_var_5 = load float, ptr %var_5, align 4
      %call_mult = call float @mult(i32 %load_var_3, float %load_var_5)
      store float %call_mult, ptr %var_6, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      %call_sub = call float @sub(i32 %load_var_2, float %load_var_6)
      store float %call_sub, ptr %var_1, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %rmult = fmul float %load_var_0, %load_var_1
      store float %rmult, ptr %var_7, align 4
      ret void
    }

    define float @gfn_main_inline(i32 %a, float %x) {
    entry:
      %x_alloca = alloca float, align 4
      %var_1 = alloca float, align 4
      %a_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %cast_a = sitofp i32 %load_a to float
      store float %cast_a, ptr %var_0, align 4
      store float %x, ptr %x_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_x = load float, ptr %x_alloca, align 4
      %rmult = fmul float %load_var_0, %load_x
      store float %rmult, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
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
      %var_1 = alloca float, align 4
      %n_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %n, ptr %n_alloca, align 4
      %load_n = load i32, ptr %n_alloca, align 4
      %cast_n = sitofp i32 %load_n to float
      store float %cast_n, ptr %var_0, align 4
      store float %p, ptr %p_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_p = load float, ptr %p_alloca, align 4
      %rmult = fmul float %load_var_0, %load_p
      store float %rmult, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
    }

    define float @sub(i32 %ax, float %bx) {
    entry:
      %bx_alloca = alloca float, align 4
      %var_1 = alloca float, align 4
      %ax_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %ax, ptr %ax_alloca, align 4
      %load_ax = load i32, ptr %ax_alloca, align 4
      %cast_ax = sitofp i32 %load_ax to float
      store float %cast_ax, ptr %var_0, align 4
      store float %bx, ptr %bx_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_bx = load float, ptr %bx_alloca, align 4
      %rminus = fsub float %load_var_0, %load_bx
      store float %rminus, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
    }

    define float @main() {
    entry:
      %var_8 = alloca float, align 4
      %var_1 = alloca float, align 4
      %var_7 = alloca float, align 4
      %var_6 = alloca float, align 4
      %var_5 = alloca i32, align 4
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %var_0 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      %block = alloca ptr, align 8
      store ptr @gfn_main_block, ptr %block, align 8
      %inline = alloca ptr, align 8
      store ptr @gfn_main_inline, ptr %inline, align 8
      store float 3.225000e+01, ptr %var_0, align 4
      store i32 1, ptr %var_2, align 4
      store i32 22, ptr %var_3, align 4
      store i32 25, ptr %var_4, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      %load_x = load float, ptr %x, align 4
      %arrow_block_loaded = load ptr, ptr %block, align 8
      %call_block = call i32 %arrow_block_loaded(i32 %load_var_4, float %load_x)
      store i32 %call_block, ptr %var_5, align 4
      %load_var_5 = load i32, ptr %var_5, align 4
      %load_x1 = load float, ptr %x, align 4
      %arrow_inline_loaded = load ptr, ptr %inline, align 8
      %call_inline = call float %arrow_inline_loaded(i32 %load_var_5, float %load_x1)
      store float %call_inline, ptr %var_6, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      %call_mult = call float @mult(i32 %load_var_3, float %load_var_6)
      store float %call_mult, ptr %var_7, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %load_var_7 = load float, ptr %var_7, align 4
      %call_sub = call float @sub(i32 %load_var_2, float %load_var_7)
      store float %call_sub, ptr %var_1, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %rmult = fmul float %load_var_0, %load_var_1
      store float %rmult, ptr %var_8, align 4
      %load_var_8 = load float, ptr %var_8, align 4
      ret float %load_var_8
    }

    define i32 @gfn_main_block(i32 %a, float %x) {
    entry:
      %a_alloca = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 125, ptr %var_0, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %rmult = mul i32 %load_a, %load_var_0
      store i32 %rmult, ptr %var_1, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      ret i32 %load_var_1
    }

    define float @gfn_main_inline(i32 %a, float %x) {
    entry:
      %x_alloca = alloca float, align 4
      %var_1 = alloca float, align 4
      %a_alloca = alloca i32, align 4
      %var_0 = alloca float, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %cast_a = sitofp i32 %load_a to float
      store float %cast_a, ptr %var_0, align 4
      store float %x, ptr %x_alloca, align 4
      %load_var_0 = load float, ptr %var_0, align 4
      %load_x = load float, ptr %x_alloca, align 4
      %rmult = fmul float %load_var_0, %load_x
      store float %rmult, ptr %var_1, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      ret float %load_var_1
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
      %var_88 = alloca i1, align 1
      %var_87 = alloca i1, align 1
      %var_86 = alloca i1, align 1
      %var_85 = alloca i32, align 4
      %var_84 = alloca i32, align 4
      %var_83 = alloca i1, align 1
      %var_82 = alloca i1, align 1
      %var_81 = alloca i1, align 1
      %var_80 = alloca i1, align 1
      %var_79 = alloca i32, align 4
      %var_78 = alloca i1, align 1
      %var_77 = alloca i32, align 4
      %var_76 = alloca i32, align 4
      %var_75 = alloca i32, align 4
      %var_74 = alloca i1, align 1
      %var_73 = alloca i32, align 4
      %exprBool7 = alloca i1, align 1
      %var_72 = alloca i1, align 1
      %var_71 = alloca i1, align 1
      %var_70 = alloca i1, align 1
      %var_69 = alloca i32, align 4
      %var_68 = alloca i32, align 4
      %var_67 = alloca i1, align 1
      %var_66 = alloca i32, align 4
      %var_65 = alloca i32, align 4
      %var_64 = alloca i32, align 4
      %var_63 = alloca i1, align 1
      %var_62 = alloca i1, align 1
      %var_61 = alloca float, align 4
      %var_60 = alloca i32, align 4
      %var_59 = alloca i1, align 1
      %var_58 = alloca i1, align 1
      %var_57 = alloca i32, align 4
      %var_56 = alloca i1, align 1
      %var_55 = alloca i1, align 1
      %var_54 = alloca i32, align 4
      %var_53 = alloca i32, align 4
      %var_52 = alloca i1, align 1
      %var_51 = alloca i32, align 4
      %var_50 = alloca i32, align 4
      %b = alloca float, align 4
      %a = alloca i32, align 4
      %exprBool6 = alloca i1, align 1
      %var_49 = alloca i1, align 1
      %var_48 = alloca i1, align 1
      %var_47 = alloca i32, align 4
      %var_46 = alloca i32, align 4
      %var_45 = alloca i32, align 4
      %var_44 = alloca i32, align 4
      %var_43 = alloca i1, align 1
      %var_42 = alloca i1, align 1
      %var_41 = alloca i32, align 4
      %var_40 = alloca i32, align 4
      %var_39 = alloca i1, align 1
      %var_38 = alloca i1, align 1
      %var_37 = alloca i32, align 4
      %var_36 = alloca i1, align 1
      %var_35 = alloca i1, align 1
      %var_34 = alloca i32, align 4
      %var_33 = alloca i32, align 4
      %var_32 = alloca i32, align 4
      %var_31 = alloca i1, align 1
      %var_30 = alloca i32, align 4
      %var_29 = alloca i32, align 4
      %exprBool5 = alloca i1, align 1
      %var_28 = alloca i1, align 1
      %var_27 = alloca i1, align 1
      %var_26 = alloca i32, align 4
      %var_25 = alloca i32, align 4
      %var_24 = alloca i1, align 1
      %var_23 = alloca i1, align 1
      %var_22 = alloca i32, align 4
      %var_21 = alloca i1, align 1
      %var_20 = alloca i1, align 1
      %var_19 = alloca i32, align 4
      %var_18 = alloca i32, align 4
      %var_17 = alloca i32, align 4
      %var_16 = alloca i1, align 1
      %var_15 = alloca i32, align 4
      %var_14 = alloca i32, align 4
      %exprBool4 = alloca i1, align 1
      %var_13 = alloca i1, align 1
      %var_12 = alloca i32, align 4
      %var_11 = alloca i32, align 4
      %exprBool3 = alloca i1, align 1
      %var_10 = alloca i1, align 1
      %var_9 = alloca i32, align 4
      %var_8 = alloca i32, align 4
      %exprBool2 = alloca i1, align 1
      %var_7 = alloca i1, align 1
      %var_6 = alloca i32, align 4
      %var_5 = alloca i32, align 4
      %exprBool1 = alloca i1, align 1
      %var_4 = alloca i1, align 1
      %var_3 = alloca i1, align 1
      %var_2 = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i1, align 1
      store i1 true, ptr %var_0, align 1
      store i32 3, ptr %var_1, align 4
      store i32 1, ptr %var_2, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %cmp_gt = icmp sgt i32 %load_var_1, %load_var_2
      store i1 %cmp_gt, ptr %var_3, align 1
      %load_var_3 = load i1, ptr %var_3, align 1
      %load_var_0 = load i1, ptr %var_0, align 1
      %not_ = xor i1 %load_var_3, %load_var_0
      store i1 %not_, ptr %var_4, align 1
      %load_var_4 = load i1, ptr %var_4, align 1
      store i1 %load_var_4, ptr %exprBool1, align 1
      store i32 3, ptr %var_5, align 4
      store i32 1, ptr %var_6, align 4
      %load_var_5 = load i32, ptr %var_5, align 4
      %load_var_6 = load i32, ptr %var_6, align 4
      %cmp_gt1 = icmp sgt i32 %load_var_5, %load_var_6
      store i1 %cmp_gt1, ptr %var_7, align 1
      %load_var_7 = load i1, ptr %var_7, align 1
      store i1 %load_var_7, ptr %exprBool2, align 1
      store i32 3, ptr %var_8, align 4
      store i32 1, ptr %var_9, align 4
      %load_var_8 = load i32, ptr %var_8, align 4
      %load_var_9 = load i32, ptr %var_9, align 4
      %cmp_neq = icmp ne i32 %load_var_8, %load_var_9
      store i1 %cmp_neq, ptr %var_10, align 1
      %load_var_10 = load i1, ptr %var_10, align 1
      store i1 %load_var_10, ptr %exprBool3, align 1
      store i32 3, ptr %var_11, align 4
      store i32 1, ptr %var_12, align 4
      %load_var_11 = load i32, ptr %var_11, align 4
      %load_var_12 = load i32, ptr %var_12, align 4
      %cmp_eq = icmp eq i32 %load_var_11, %load_var_12
      store i1 %cmp_eq, ptr %var_13, align 1
      %load_var_13 = load i1, ptr %var_13, align 1
      store i1 %load_var_13, ptr %exprBool4, align 1
      store i32 5, ptr %var_14, align 4
      store i32 3, ptr %var_15, align 4
      %load_var_14 = load i32, ptr %var_14, align 4
      %load_var_15 = load i32, ptr %var_15, align 4
      %cmp_gt2 = icmp sgt i32 %load_var_14, %load_var_15
      store i1 %cmp_gt2, ptr %var_16, align 1
      store i32 25, ptr %var_17, align 4
      store i32 6, ptr %var_18, align 4
      %load_var_17 = load i32, ptr %var_17, align 4
      %load_var_18 = load i32, ptr %var_18, align 4
      %rmult = mul i32 %load_var_17, %load_var_18
      store i32 %rmult, ptr %var_19, align 4
      %load_var_19 = load i32, ptr %var_19, align 4
      %cast_var_19 = icmp ne i32 %load_var_19, 0
      store i1 %cast_var_19, ptr %var_20, align 1
      %load_var_16 = load i1, ptr %var_16, align 1
      %load_var_20 = load i1, ptr %var_20, align 1
      %cmp_neq3 = icmp ne i1 %load_var_16, %load_var_20
      store i1 %cmp_neq3, ptr %var_21, align 1
      store i32 5, ptr %var_22, align 4
      %load_var_22 = load i32, ptr %var_22, align 4
      %cast_var_22 = icmp ne i32 %load_var_22, 0
      store i1 %cast_var_22, ptr %var_23, align 1
      %load_var_21 = load i1, ptr %var_21, align 1
      %load_var_23 = load i1, ptr %var_23, align 1
      %cmp_lt = icmp slt i1 %load_var_21, %load_var_23
      store i1 %cmp_lt, ptr %var_24, align 1
      store i32 25, ptr %var_25, align 4
      store i32 25, ptr %var_26, align 4
      %load_var_25 = load i32, ptr %var_25, align 4
      %load_var_26 = load i32, ptr %var_26, align 4
      %cmp_eq4 = icmp eq i32 %load_var_25, %load_var_26
      store i1 %cmp_eq4, ptr %var_27, align 1
      %load_var_24 = load i1, ptr %var_24, align 1
      %load_var_27 = load i1, ptr %var_27, align 1
      %cmp_neq5 = icmp ne i1 %load_var_24, %load_var_27
      store i1 %cmp_neq5, ptr %var_28, align 1
      %load_var_28 = load i1, ptr %var_28, align 1
      store i1 %load_var_28, ptr %exprBool5, align 1
      store i32 5, ptr %var_29, align 4
      store i32 3, ptr %var_30, align 4
      %load_var_29 = load i32, ptr %var_29, align 4
      %load_var_30 = load i32, ptr %var_30, align 4
      %cmp_gt6 = icmp sgt i32 %load_var_29, %load_var_30
      store i1 %cmp_gt6, ptr %var_31, align 1
      store i32 25, ptr %var_32, align 4
      store i32 6, ptr %var_33, align 4
      %load_var_32 = load i32, ptr %var_32, align 4
      %load_var_33 = load i32, ptr %var_33, align 4
      %rmult7 = mul i32 %load_var_32, %load_var_33
      store i32 %rmult7, ptr %var_34, align 4
      %load_var_34 = load i32, ptr %var_34, align 4
      %cast_var_34 = icmp ne i32 %load_var_34, 0
      store i1 %cast_var_34, ptr %var_35, align 1
      %load_var_31 = load i1, ptr %var_31, align 1
      %load_var_35 = load i1, ptr %var_35, align 1
      %cmp_neq8 = icmp ne i1 %load_var_31, %load_var_35
      store i1 %cmp_neq8, ptr %var_36, align 1
      store i32 5, ptr %var_37, align 4
      %load_var_37 = load i32, ptr %var_37, align 4
      %cast_var_37 = icmp ne i32 %load_var_37, 0
      store i1 %cast_var_37, ptr %var_38, align 1
      %load_var_36 = load i1, ptr %var_36, align 1
      %load_var_38 = load i1, ptr %var_38, align 1
      %cmp_lt9 = icmp slt i1 %load_var_36, %load_var_38
      store i1 %cmp_lt9, ptr %var_39, align 1
      store i32 25, ptr %var_40, align 4
      store i32 25, ptr %var_41, align 4
      %load_var_40 = load i32, ptr %var_40, align 4
      %load_var_41 = load i32, ptr %var_41, align 4
      %cmp_eq10 = icmp eq i32 %load_var_40, %load_var_41
      store i1 %cmp_eq10, ptr %var_42, align 1
      %load_var_39 = load i1, ptr %var_39, align 1
      %load_var_42 = load i1, ptr %var_42, align 1
      %cmp_neq11 = icmp ne i1 %load_var_39, %load_var_42
      store i1 %cmp_neq11, ptr %var_43, align 1
      store i32 32, ptr %var_44, align 4
      store i32 2, ptr %var_45, align 4
      %load_var_44 = load i32, ptr %var_44, align 4
      %load_var_45 = load i32, ptr %var_45, align 4
      %rdiv = sdiv i32 %load_var_44, %load_var_45
      store i32 %rdiv, ptr %var_46, align 4
      store i32 5, ptr %var_47, align 4
      %load_var_46 = load i32, ptr %var_46, align 4
      %load_var_47 = load i32, ptr %var_47, align 4
      %cmp_gt12 = icmp sgt i32 %load_var_46, %load_var_47
      store i1 %cmp_gt12, ptr %var_48, align 1
      %load_var_43 = load i1, ptr %var_43, align 1
      %load_var_48 = load i1, ptr %var_48, align 1
      %or_ = or i1 %load_var_43, %load_var_48
      store i1 %or_, ptr %var_49, align 1
      %load_var_49 = load i1, ptr %var_49, align 1
      store i1 %load_var_49, ptr %exprBool6, align 1
      store i32 12, ptr %a, align 4
      store float 0x3FF99999A0000000, ptr %b, align 4
      store i32 5, ptr %var_50, align 4
      store i32 3, ptr %var_51, align 4
      %load_var_50 = load i32, ptr %var_50, align 4
      %load_var_51 = load i32, ptr %var_51, align 4
      %cmp_gt13 = icmp sgt i32 %load_var_50, %load_var_51
      store i1 %cmp_gt13, ptr %var_52, align 1
      store i32 6, ptr %var_53, align 4
      %load_a = load i32, ptr %a, align 4
      %load_var_53 = load i32, ptr %var_53, align 4
      %rmult14 = mul i32 %load_a, %load_var_53
      store i32 %rmult14, ptr %var_54, align 4
      %load_var_54 = load i32, ptr %var_54, align 4
      %cast_var_54 = icmp ne i32 %load_var_54, 0
      store i1 %cast_var_54, ptr %var_55, align 1
      %load_var_52 = load i1, ptr %var_52, align 1
      %load_var_55 = load i1, ptr %var_55, align 1
      %cmp_neq15 = icmp ne i1 %load_var_52, %load_var_55
      store i1 %cmp_neq15, ptr %var_56, align 1
      store i32 5, ptr %var_57, align 4
      %load_var_57 = load i32, ptr %var_57, align 4
      %cast_var_57 = icmp ne i32 %load_var_57, 0
      store i1 %cast_var_57, ptr %var_58, align 1
      %load_var_56 = load i1, ptr %var_56, align 1
      %load_var_58 = load i1, ptr %var_58, align 1
      %cmp_lt16 = icmp slt i1 %load_var_56, %load_var_58
      store i1 %cmp_lt16, ptr %var_59, align 1
      store i32 25, ptr %var_60, align 4
      %load_var_60 = load i32, ptr %var_60, align 4
      %cast_var_60 = sitofp i32 %load_var_60 to float
      store float %cast_var_60, ptr %var_61, align 4
      %load_var_61 = load float, ptr %var_61, align 4
      %load_b = load float, ptr %b, align 4
      %cmp_eq17 = fcmp oeq float %load_var_61, %load_b
      store i1 %cmp_eq17, ptr %var_62, align 1
      %load_var_59 = load i1, ptr %var_59, align 1
      %load_var_62 = load i1, ptr %var_62, align 1
      %cmp_neq18 = icmp ne i1 %load_var_59, %load_var_62
      store i1 %cmp_neq18, ptr %var_63, align 1
      store i32 32, ptr %var_64, align 4
      store i32 2, ptr %var_65, align 4
      %load_var_64 = load i32, ptr %var_64, align 4
      %load_var_65 = load i32, ptr %var_65, align 4
      %rdiv19 = sdiv i32 %load_var_64, %load_var_65
      store i32 %rdiv19, ptr %var_66, align 4
      %load_var_66 = load i32, ptr %var_66, align 4
      %load_a20 = load i32, ptr %a, align 4
      %cmp_gt21 = icmp sgt i32 %load_var_66, %load_a20
      store i1 %cmp_gt21, ptr %var_67, align 1
      store i32 2, ptr %var_68, align 4
      store i32 2, ptr %var_69, align 4
      %load_var_68 = load i32, ptr %var_68, align 4
      %load_var_69 = load i32, ptr %var_69, align 4
      %cmp_gt22 = icmp sgt i32 %load_var_68, %load_var_69
      store i1 %cmp_gt22, ptr %var_70, align 1
      %load_var_67 = load i1, ptr %var_67, align 1
      %load_var_70 = load i1, ptr %var_70, align 1
      %and_ = and i1 %load_var_67, %load_var_70
      store i1 %and_, ptr %var_71, align 1
      %load_var_63 = load i1, ptr %var_63, align 1
      %load_var_71 = load i1, ptr %var_71, align 1
      %or_23 = or i1 %load_var_63, %load_var_71
      store i1 %or_23, ptr %var_72, align 1
      %load_var_72 = load i1, ptr %var_72, align 1
      store i1 %load_var_72, ptr %exprBool7, align 1
      store i32 5, ptr %var_73, align 4
      %load_var_73 = load i32, ptr %var_73, align 4
      %load_a24 = load i32, ptr %a, align 4
      %cmp_gt25 = icmp sgt i32 %load_var_73, %load_a24
      store i1 %cmp_gt25, ptr %var_74, align 1
      store i32 25, ptr %var_75, align 4
      store i32 6, ptr %var_76, align 4
      %load_var_75 = load i32, ptr %var_75, align 4
      %load_var_76 = load i32, ptr %var_76, align 4
      %rmult26 = mul i32 %load_var_75, %load_var_76
      store i32 %rmult26, ptr %var_77, align 4
      %load_var_77 = load i32, ptr %var_77, align 4
      %load_a27 = load i32, ptr %a, align 4
      %cmp_lt28 = icmp slt i32 %load_var_77, %load_a27
      store i1 %cmp_lt28, ptr %var_78, align 1
      store i32 2, ptr %var_79, align 4
      %load_var_79 = load i32, ptr %var_79, align 4
      %cast_var_79 = icmp ne i32 %load_var_79, 0
      store i1 %cast_var_79, ptr %var_80, align 1
      %load_var_78 = load i1, ptr %var_78, align 1
      %load_var_80 = load i1, ptr %var_80, align 1
      %cmp_neq29 = icmp ne i1 %load_var_78, %load_var_80
      store i1 %cmp_neq29, ptr %var_81, align 1
      %load_var_74 = load i1, ptr %var_74, align 1
      %load_var_81 = load i1, ptr %var_81, align 1
      %cmp_neq30 = icmp ne i1 %load_var_74, %load_var_81
      store i1 %cmp_neq30, ptr %var_82, align 1
      store i1 true, ptr %var_83, align 1
      store i32 25, ptr %var_84, align 4
      store i32 25, ptr %var_85, align 4
      %load_var_84 = load i32, ptr %var_84, align 4
      %load_var_85 = load i32, ptr %var_85, align 4
      %cmp_eq31 = icmp eq i32 %load_var_84, %load_var_85
      store i1 %cmp_eq31, ptr %var_86, align 1
      %load_var_86 = load i1, ptr %var_86, align 1
      %load_var_83 = load i1, ptr %var_83, align 1
      %not_32 = xor i1 %load_var_86, %load_var_83
      store i1 %not_32, ptr %var_87, align 1
      %load_var_82 = load i1, ptr %var_82, align 1
      %load_var_87 = load i1, ptr %var_87, align 1
      %cmp_eq33 = icmp eq i1 %load_var_82, %load_var_87
      store i1 %cmp_eq33, ptr %var_88, align 1
      %load_var_88 = load i1, ptr %var_88, align 1
      store i1 %load_var_88, ptr %exprBool8, align 1
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


TEST_F(LLVMTestCode, T10)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define void @sum(ptr %func, i32 %c) {
    entry:
      ret void
    }

    define void @main() {
    entry:
      %var_0 = alloca i32, align 4
      %inline = alloca ptr, align 8
      store ptr @gfn_main_inline, ptr %inline, align 8
      store i32 2, ptr %var_0, align 4
      %load_inline = load ptr, ptr %inline, align 8
      %load_var_0 = load i32, ptr %var_0, align 4
      call void @sum(ptr %load_inline, i32 %load_var_0)
      ret void
    }

    define i32 @gfn_main_inline(i32 %a, i32 %b, float %c) {
    entry:
      %a_alloca = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 3, ptr %var_0, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %rmult = mul i32 %load_a, %load_var_0
      store i32 %rmult, ptr %var_1, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      ret i32 %load_var_1
    }
    )";

    const std::string input = R"(
        fn sum(func:fn(a:int,b:int,c:float):int, c:int) {}

        fn main() {
            let inline:fn = (a:int,b:int,c:float):int -> a * 3
            sum(func:inline, c:2)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T11)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define void @sum(ptr %func, i32 %c) {
    entry:
      ret void
    }

    define i32 @sub(i32 %a, i32 %b) {
    entry:
      %var_0 = alloca i32, align 4
      store i32 1, ptr %var_0, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      ret i32 %load_var_0
    }

    define void @main() {
    entry:
      %var_0 = alloca i32, align 4
      store i32 2, ptr %var_0, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      call void @sum(ptr @sub, i32 %load_var_0)
      ret void
    }
    )";

    const std::string input = R"(
        fn sum(func:fn(a:int,b:int):int, c:int) {}

        fn sub(a:int,b:int):int {
            return 1
        }

        fn main() {
            sum(func:sub, c:2)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T12)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define i32 @sum(ptr %func, i32 %p) {
    entry:
      %var_1 = alloca i32, align 4
      %p_alloca1 = alloca i32, align 4
      %p_alloca = alloca i32, align 4
      %var_0 = alloca i32, align 4
      %inline = alloca ptr, align 8
      store ptr @gfn_sum_inline, ptr %inline, align 8
      store i32 %p, ptr %p_alloca, align 4
      %load_p = load i32, ptr %p_alloca, align 4
      store i32 %p, ptr %p_alloca1, align 4
      %load_p2 = load i32, ptr %p_alloca1, align 4
      %arrow_inline_loaded = load ptr, ptr %inline, align 8
      %call_inline = call i32 %arrow_inline_loaded(i32 %load_p, i32 %load_p2)
      store i32 %call_inline, ptr %var_0, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %call_func_arg = call i32 %func(i32 %load_var_0)
      store i32 0, ptr %var_1, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      ret i32 %load_var_1
    }

    define i32 @gfn_sum_inline(i32 %x, i32 %p) {
    entry:
      %p_alloca = alloca i32, align 4
      %var_2 = alloca i32, align 4
      %x_alloca = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 2, ptr %var_0, align 4
      store i32 %x, ptr %x_alloca, align 4
      %load_x = load i32, ptr %x_alloca, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %rmult = mul i32 %load_x, %load_var_0
      store i32 %rmult, ptr %var_1, align 4
      store i32 %p, ptr %p_alloca, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %load_p = load i32, ptr %p_alloca, align 4
      %rmult1 = mul i32 %load_var_1, %load_p
      store i32 %rmult1, ptr %var_2, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      ret i32 %load_var_2
    }

    define void @main() {
    entry:
      %var_0 = alloca i32, align 4
      %inline = alloca ptr, align 8
      store ptr @gfn_main_inline, ptr %inline, align 8
      store i32 3, ptr %var_0, align 4
      %load_inline = load ptr, ptr %inline, align 8
      %load_var_0 = load i32, ptr %var_0, align 4
      %call_sum = call i32 @sum(ptr %load_inline, i32 %load_var_0)
      ret void
    }

    define i32 @gfn_main_inline(i32 %a) {
    entry:
      %a_alloca = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 8, ptr %var_0, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %rmult = mul i32 %load_a, %load_var_0
      store i32 %rmult, ptr %var_1, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      ret i32 %load_var_1
    }
    )";

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

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T13)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define i32 @sum(ptr %func, i32 %p) {
    entry:
      %var_0 = alloca i32, align 4
      %p_alloca = alloca i32, align 4
      store i32 %p, ptr %p_alloca, align 4
      %load_p = load i32, ptr %p_alloca, align 4
      %call_func_arg = call i32 %func(i32 %load_p)
      store i32 0, ptr %var_0, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      ret i32 %load_var_0
    }

    define void @main() {
    entry:
      %var_0 = alloca i32, align 4
      %inline = alloca ptr, align 8
      store ptr @gfn_main_inline, ptr %inline, align 8
      store i32 3, ptr %var_0, align 4
      %load_inline = load ptr, ptr %inline, align 8
      %load_var_0 = load i32, ptr %var_0, align 4
      %call_sum = call i32 @sum(ptr %load_inline, i32 %load_var_0)
      ret void
    }

    define i32 @gfn_main_inline(i32 %a) {
    entry:
      %a_alloca = alloca i32, align 4
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 8, ptr %var_0, align 4
      store i32 %a, ptr %a_alloca, align 4
      %load_a = load i32, ptr %a_alloca, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %rmult = mul i32 %load_a, %load_var_0
      store i32 %rmult, ptr %var_1, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      ret i32 %load_var_1
    }
    )";

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

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T14)
{
    const std::string output = R"(
        ; ModuleID = 'main.o'
        source_filename = "main.o"

        define void @main() {
        entry:
          %inline = alloca ptr, align 8
          store ptr @gfn_main_inline, ptr %inline, align 8
          %block = alloca ptr, align 8
          store ptr @gfn_main_block, ptr %block, align 8
          %func = alloca ptr, align 8
          store ptr @gfn_main_func, ptr %func, align 8
          %load_func = load ptr, ptr %func, align 8
          %load_inline = load ptr, ptr %inline, align 8
          %arrow_block_loaded = load ptr, ptr %block, align 8
          %call_block = call i32 %arrow_block_loaded(ptr %load_func, ptr %load_inline)
          ret void
        }

        define i32 @gfn_main_inline(i32 %a, ptr %inline) {
        entry:
          %a_alloca = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 8, ptr %var_0, align 4
          store i32 %a, ptr %a_alloca, align 4
          %load_a = load i32, ptr %a_alloca, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          %rmult = mul i32 %load_a, %load_var_0
          store i32 %rmult, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          ret i32 %load_var_1
        }

        define i32 @gfn_main_block(ptr %func, ptr %inline) {
        entry:
          %var_0 = alloca i32, align 4
          %inline_alloca = alloca ptr, align 8
          store ptr %inline, ptr %inline_alloca, align 8
          %load_inline = load ptr, ptr %inline_alloca, align 8
          %call_func_arg = call i32 %func(ptr %load_inline)
          store i32 0, ptr %var_0, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          ret i32 %load_var_0
        }

        define i32 @gfn_main_func(ptr %zz) {
        entry:
          %var_2 = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 2, ptr %var_0, align 4
          store i32 2, ptr %var_1, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          %rmult = mul i32 %load_var_0, %load_var_1
          store i32 %rmult, ptr %var_2, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          ret i32 %load_var_2
        }
    )";

    const std::string input = R"(
        fn main() {
           let inline:fn = (a:int):int -> a * 8

           let block:fn = (func:fn(x:fn(a:int):int):int):int -> {
                func(x:inline)
                return 0
           }

           let func:fn = (zz:fn(a:int):int):int -> 2 * 2
           block(func:func)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T15)
{
    const std::string output = R"(
        ; ModuleID = 'main.o'
        source_filename = "main.o"

        define i32 @sum(ptr %func, i32 %p) {
        entry:
          %p_alloca = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 %p, ptr %p_alloca, align 4
          %load_p = load i32, ptr %p_alloca, align 4
          %call_func_arg = call i32 %func(i32 %load_p)
          store i32 %call_func_arg, ptr %var_0, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          ret i32 %load_var_0
        }

        define void @main() {
        entry:
          %var_0 = alloca i32, align 4
          %inline = alloca ptr, align 8
          store ptr @gfn_main_inline, ptr %inline, align 8
          store i32 2, ptr %var_0, align 4
          %load_inline = load ptr, ptr %inline, align 8
          %load_var_0 = load i32, ptr %var_0, align 4
          %call_sum = call i32 @sum(ptr %load_inline, i32 %load_var_0)
          ret void
        }

        define i32 @gfn_main_inline(i32 %x) {
        entry:
          %x_alloca = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 3, ptr %var_0, align 4
          store i32 %x, ptr %x_alloca, align 4
          %load_x = load i32, ptr %x_alloca, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          %rmult = mul i32 %load_x, %load_var_0
          store i32 %rmult, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          ret i32 %load_var_1
        }
    )";

    const std::string input = R"(
        fn sum(func:fn (a:int):int, p:int):int {
            return func(a:p)
        }

        fn main() {
            let inline:fn = (x:int):int -> x * 3
            sum(func:inline, p:2)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T16)
{
    const std::string output = R"(
        ; ModuleID = 'output.o'
        source_filename = "output.o"

        declare i32 @printf(ptr, ...)

        define i32 @main() {
        entry:
          %var_9 = alloca i32, align 4
          %var_5 = alloca i1, align 1
          %var_3 = alloca i1, align 1
          %var_1 = alloca i1, align 1
          %var_0 = alloca float, align 4
          %y = alloca i32, align 4
          %x = alloca float, align 4
          store float 0x4008CCCCC0000000, ptr %x, align 4
          store i32 30, ptr %y, align 4
          %load_y = load i32, ptr %y, align 4
          %cast_y = sitofp i32 %load_y to float
          store float %cast_y, ptr %var_0, align 4
          %load_x = load float, ptr %x, align 4
          %load_var_0 = load float, ptr %var_0, align 4
          %cmp_gt = fcmp ogt float %load_x, %load_var_0
          store i1 %cmp_gt, ptr %var_1, align 1
          %cond_ = load i1, ptr %var_1, align 1
          br i1 %cond_, label %then_1, label %else_2

        then_1:                                           ; preds = %entry
          %var_2 = alloca [10 x i8], align 1
          store [7 x i8] c"X > Y\0A\00", ptr %var_2, align 1
          %str_ptr = getelementptr [10 x i8], ptr %var_2, i32 0, i32 0
          %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr)
          store i1 true, ptr %var_3, align 1
          %cond_1 = load i1, ptr %var_3, align 1
          br i1 %cond_1, label %then_4, label %end_3

        then_4:                                           ; preds = %then_1
          %var_4 = alloca [12 x i8], align 1
          store [9 x i8] c"\C3\89 true\0A\00", ptr %var_4, align 1
          %str_ptr2 = getelementptr [12 x i8], ptr %var_4, i32 0, i32 0
          %call_printf3 = call i32 (ptr, ...) @printf(ptr %str_ptr2)
          br label %end_3

        end_3:                                            ; preds = %then_4, %then_1
          br label %end_0

        else_2:                                           ; preds = %entry
          store i1 false, ptr %var_5, align 1
          %cond_4 = load i1, ptr %var_5, align 1
          br i1 %cond_4, label %then_6, label %else_7

        then_6:                                           ; preds = %else_2
          %var_6 = alloca [10 x i8], align 1
          store [7 x i8] c"X < Y\0A\00", ptr %var_6, align 1
          %str_ptr5 = getelementptr [10 x i8], ptr %var_6, i32 0, i32 0
          %call_printf6 = call i32 (ptr, ...) @printf(ptr %str_ptr5)
          br label %end_0

        else_7:                                           ; preds = %else_2
          %var_7 = alloca [19 x i8], align 1
          store [16 x i8] c"Entrou no else\0A\00", ptr %var_7, align 1
          %str_ptr7 = getelementptr [19 x i8], ptr %var_7, i32 0, i32 0
          %call_printf8 = call i32 (ptr, ...) @printf(ptr %str_ptr7)
          br label %end_0

        end_0:                                            ; preds = %else_7, %then_6, %end_3
          %var_8 = alloca [13 x i8], align 1
          store [10 x i8] c"Terminou\0A\00", ptr %var_8, align 1
          %str_ptr9 = getelementptr [13 x i8], ptr %var_8, i32 0, i32 0
          %call_printf10 = call i32 (ptr, ...) @printf(ptr %str_ptr9)
          store i32 0, ptr %var_9, align 4
          %load_var_9 = load i32, ptr %var_9, align 4
          ret i32 %load_var_9
        }
    )";

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

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T17)
{
    const std::string output = R"(

    )";

    const std::string input = R"(

    )";

    runAnalysis(input, output);
}
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
        ; ModuleID = 'output.o'
        source_filename = "output.o"

        declare i32 @printf(ptr, ...)

        define i32 @soma(float %n, i32 %j) {
        entry:
          %j_alloca = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_0 = alloca ptr, align 8
          store ptr @gfn_soma_block1, ptr %var_0, align 8
          store i32 %j, ptr %j_alloca, align 4
          %load_j = load i32, ptr %j_alloca, align 4
          %call_gfn_soma_block1 = call i32 @gfn_soma_block1(i32 %load_j)
          store i32 %call_gfn_soma_block1, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          ret i32 %load_var_1
        }

        define i32 @gfn_soma_block1(i32 %j) {
        entry:
          %j_alloca = alloca i32, align 4
          %var_2 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 25, ptr %var_0, align 4
          %var_1 = alloca ptr, align 8
          store ptr @gfn_gfn_soma_block1_block2, ptr %var_1, align 8
          store i32 %j, ptr %j_alloca, align 4
          %load_j = load i32, ptr %j_alloca, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          %call_gfn_gfn_soma_block1_block2 = call i32 @gfn_gfn_soma_block1_block2(i32 %load_j, i32 %load_var_0)
          store i32 %call_gfn_gfn_soma_block1_block2, ptr %var_2, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          ret i32 %load_var_2
        }

        define i32 @gfn_gfn_soma_block1_block2(i32 %j, i32 %x) {
        entry:
          %j_alloca4 = alloca i32, align 4
          %var_6 = alloca i32, align 4
          %var_7 = alloca i32, align 4
          %var_4 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          %x_alloca2 = alloca i32, align 4
          %x_alloca = alloca i32, align 4
          %var_3 = alloca i32, align 4
          %j_alloca1 = alloca i32, align 4
          %j_alloca = alloca i32, align 4
          %var_2 = alloca i32, align 4
          %var_1 = alloca i32, align 4
          store i32 2, ptr %var_1, align 4
          store i32 %j, ptr %j_alloca, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          store i32 %j, ptr %j_alloca1, align 4
          %load_j = load i32, ptr %j_alloca1, align 4
          %rmult = mul i32 %load_var_1, %load_j
          store i32 %rmult, ptr %var_2, align 4
          store i32 %x, ptr %x_alloca, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          store i32 %x, ptr %x_alloca2, align 4
          %load_x = load i32, ptr %x_alloca2, align 4
          %rmult3 = mul i32 %load_var_2, %load_x
          store i32 %rmult3, ptr %var_3, align 4
          %load_var_3 = load i32, ptr %var_3, align 4
          store i32 %load_var_3, ptr %var_0, align 4
          store i32 25, ptr %var_4, align 4
          %var_5 = alloca ptr, align 8
          store ptr @gfn_gfn_gfn_soma_block1_block2_block3, ptr %var_5, align 8
          store i32 14524, ptr %var_7, align 4
          %load_var_7 = load i32, ptr %var_7, align 4
          store i32 %j, ptr %j_alloca4, align 4
          %load_j5 = load i32, ptr %j_alloca4, align 4
          %load_var_4 = load i32, ptr %var_4, align 4
          %call_gfn_gfn_gfn_soma_block1_block2_block3 = call i32 @gfn_gfn_gfn_soma_block1_block2_block3(i32 %load_var_7, i32 %load_j5, i32 %load_var_4)
          store i32 %call_gfn_gfn_gfn_soma_block1_block2_block3, ptr %var_6, align 4
          %load_var_6 = load i32, ptr %var_6, align 4
          ret i32 %load_var_6
        }

        define i32 @gfn_gfn_gfn_soma_block1_block2_block3(i32 %n, i32 %j, i32 %x) {
        entry:
          %var_0 = alloca i32, align 4
          %n_alloca4 = alloca i32, align 4
          %n_alloca = alloca i32, align 4
          %var_4 = alloca i32, align 4
          %x_alloca2 = alloca i32, align 4
          %x_alloca = alloca i32, align 4
          %var_3 = alloca i32, align 4
          %j_alloca1 = alloca i32, align 4
          %j_alloca = alloca i32, align 4
          %var_2 = alloca i32, align 4
          %var_1 = alloca i32, align 4
          store i32 2, ptr %var_1, align 4
          store i32 %j, ptr %j_alloca, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          store i32 %j, ptr %j_alloca1, align 4
          %load_j = load i32, ptr %j_alloca1, align 4
          %rmult = mul i32 %load_var_1, %load_j
          store i32 %rmult, ptr %var_2, align 4
          store i32 %x, ptr %x_alloca, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          store i32 %x, ptr %x_alloca2, align 4
          %load_x = load i32, ptr %x_alloca2, align 4
          %rmult3 = mul i32 %load_var_2, %load_x
          store i32 %rmult3, ptr %var_3, align 4
          store i32 %n, ptr %n_alloca, align 4
          %load_var_3 = load i32, ptr %var_3, align 4
          store i32 %n, ptr %n_alloca4, align 4
          %load_n = load i32, ptr %n_alloca4, align 4
          %rmult5 = mul i32 %load_var_3, %load_n
          store i32 %rmult5, ptr %var_4, align 4
          %load_var_4 = load i32, ptr %var_4, align 4
          store i32 %load_var_4, ptr %var_0, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          ret i32 %load_var_0
        }

        define void @main() {
        entry:
          %var_0 = alloca i32, align 4
          %var_2 = alloca i32, align 4
          %var_1 = alloca float, align 4
          store float 0x4002666660000000, ptr %var_1, align 4
          store i32 3, ptr %var_2, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          %call_soma = call i32 @soma(float %load_var_1, i32 %load_var_2)
          store i32 %call_soma, ptr %var_0, align 4
          %var_3 = alloca [15 x i8], align 1
          store [12 x i8] c"result: %i\0A\00", ptr %var_3, align 1
          %str_ptr = getelementptr [15 x i8], ptr %var_3, i32 0, i32 0
          %load_var_0 = load i32, ptr %var_0, align 4
          %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, i32 %load_var_0)
          ret void
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn soma(n:float, j:int): int {

            let block1:fn = ():int -> {
                   let x:int = 25
                   let block2:fn = ():int -> {
                        let r:int = 2 * j * x
                        let x:int = 25

                        let block3:fn = (n:int):int -> {
                            let r:int = 2 * j * x * n
                            return r
                        }

                        return block3(n:14524)
                    }
                    return block2()
                }
            return block1()
        }

        fn main() {
            let r:int = soma(n:2.3, j:3)
            printf(format:"result: %i\n", r:r)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T2)
{
    const std::string output = R"(
        ; ModuleID = 'output.o'
        source_filename = "output.o"

        declare i32 @printf(ptr, ...)

        define float @mult(i32 %n, float %p) {
        entry:
          %var_4 = alloca float, align 4
          %var_3 = alloca float, align 4
          %var_2 = alloca i32, align 4
          %p_alloca1 = alloca float, align 4
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
          store float %p, ptr %p_alloca1, align 4
          %load_p = load float, ptr %p_alloca1, align 4
          %rmult = fmul float %load_var_0, %load_p
          store float %rmult, ptr %var_1, align 4
          store i32 2, ptr %var_2, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          %cast_var_2 = sitofp i32 %load_var_2 to float
          store float %cast_var_2, ptr %var_3, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %load_var_3 = load float, ptr %var_3, align 4
          %rdiv = fdiv float %load_var_1, %load_var_3
          store float %rdiv, ptr %var_4, align 4
          %load_var_4 = load float, ptr %var_4, align 4
          ret float %load_var_4
        }

        define float @sub(i32 %ax, float %bx) {
        entry:
          %var_3 = alloca float, align 4
          %ax_alloca = alloca i32, align 4
          %var_2 = alloca float, align 4
          %bx_alloca1 = alloca float, align 4
          %bx_alloca = alloca float, align 4
          %var_1 = alloca float, align 4
          %var_0 = alloca float, align 4
          store float 1.000000e+00, ptr %var_0, align 4
          store float %bx, ptr %bx_alloca, align 4
          store float %bx, ptr %bx_alloca1, align 4
          %load_bx = load float, ptr %bx_alloca1, align 4
          %load_var_0 = load float, ptr %var_0, align 4
          %rmult = fmul float %load_bx, %load_var_0
          store float %rmult, ptr %var_1, align 4
          store i32 %ax, ptr %ax_alloca, align 4
          %load_ax = load i32, ptr %ax_alloca, align 4
          %cast_ax = sitofp i32 %load_ax to float
          store float %cast_ax, ptr %var_2, align 4
          %load_var_2 = load float, ptr %var_2, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          %rminus = fsub float %load_var_2, %load_var_1
          store float %rminus, ptr %var_3, align 4
          %load_var_3 = load float, ptr %var_3, align 4
          ret float %load_var_3
        }

        define float @main() {
        entry:
          %var_2 = alloca float, align 4
          %var_10 = alloca float, align 4
          %var_4 = alloca float, align 4
          %var_9 = alloca float, align 4
          %var_8 = alloca float, align 4
          %var_7 = alloca i32, align 4
          %var_6 = alloca i32, align 4
          %var_5 = alloca i32, align 4
          %var_3 = alloca float, align 4
          %var_0 = alloca float, align 4
          store float 2.500000e+01, ptr %var_0, align 4
          %var_1 = alloca ptr, align 8
          store ptr @gfn_main_inline, ptr %var_1, align 8
          store float 3.225000e+01, ptr %var_3, align 4
          store i32 1, ptr %var_5, align 4
          store i32 22, ptr %var_6, align 4
          store i32 25, ptr %var_7, align 4
          %load_var_7 = load i32, ptr %var_7, align 4
          %load_var_0 = load float, ptr %var_0, align 4
          %call_gfn_main_inline = call float @gfn_main_inline(i32 %load_var_7, float %load_var_0)
          store float %call_gfn_main_inline, ptr %var_8, align 4
          %load_var_6 = load i32, ptr %var_6, align 4
          %load_var_8 = load float, ptr %var_8, align 4
          %call_mult = call float @mult(i32 %load_var_6, float %load_var_8)
          store float %call_mult, ptr %var_9, align 4
          %load_var_5 = load i32, ptr %var_5, align 4
          %load_var_9 = load float, ptr %var_9, align 4
          %call_sub = call float @sub(i32 %load_var_5, float %load_var_9)
          store float %call_sub, ptr %var_4, align 4
          %load_var_3 = load float, ptr %var_3, align 4
          %load_var_4 = load float, ptr %var_4, align 4
          %rmult = fmul float %load_var_3, %load_var_4
          store float %rmult, ptr %var_10, align 4
          %load_var_10 = load float, ptr %var_10, align 4
          store float %load_var_10, ptr %var_2, align 4
          %var_11 = alloca [14 x i8], align 1
          store [11 x i8] c"result %f\0A\00", ptr %var_11, align 1
          %str_ptr = getelementptr [14 x i8], ptr %var_11, i32 0, i32 0
          %load_var_2 = load float, ptr %var_2, align 4
          %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, float %load_var_2)
          %load_var_21 = load float, ptr %var_2, align 4
          ret float %load_var_21
        }

        define float @gfn_main_inline(i32 %a, float %x) {
        entry:
          %x_alloca1 = alloca float, align 4
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
          store float %x, ptr %x_alloca1, align 4
          %load_x = load float, ptr %x_alloca1, align 4
          %rmult = fmul float %load_var_0, %load_x
          store float %rmult, ptr %var_1, align 4
          %load_var_1 = load float, ptr %var_1, align 4
          ret float %load_var_1
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn mult(n:int, p:float): float {return n * p / 2}
        fn sub(ax:int, bx:float): float {return ax - bx * 1.0 }

        fn main(): float {
            let x: float = 25.00
            let inline:fn = (a:int):float -> a * x
            let r:float = 32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:25)))
            // result -221686.500000
            printf(format:"result %f\n", r:r)
            return r
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T3)
{
    const std::string output = R"(
    ; ModuleID = 'main.o'
    source_filename = "main.o"

    define void @main() {
    entry:
      %var_82 = alloca i1, align 1
      %var_98 = alloca i1, align 1
      %var_97 = alloca i1, align 1
      %var_96 = alloca i1, align 1
      %var_95 = alloca i32, align 4
      %var_94 = alloca i32, align 4
      %var_93 = alloca i1, align 1
      %var_92 = alloca i1, align 1
      %var_91 = alloca i1, align 1
      %var_90 = alloca i1, align 1
      %var_89 = alloca i32, align 4
      %var_88 = alloca i1, align 1
      %var_87 = alloca i32, align 4
      %var_86 = alloca i32, align 4
      %var_85 = alloca i32, align 4
      %var_84 = alloca i1, align 1
      %var_83 = alloca i32, align 4
      %var_58 = alloca i1, align 1
      %var_81 = alloca i1, align 1
      %var_80 = alloca i1, align 1
      %var_79 = alloca i1, align 1
      %var_78 = alloca i32, align 4
      %var_77 = alloca i32, align 4
      %var_76 = alloca i1, align 1
      %var_75 = alloca i32, align 4
      %var_74 = alloca i32, align 4
      %var_73 = alloca i32, align 4
      %var_72 = alloca i1, align 1
      %var_71 = alloca i1, align 1
      %var_70 = alloca float, align 4
      %var_69 = alloca i32, align 4
      %var_68 = alloca i1, align 1
      %var_67 = alloca i1, align 1
      %var_66 = alloca i32, align 4
      %var_65 = alloca i1, align 1
      %var_64 = alloca i1, align 1
      %var_63 = alloca i32, align 4
      %var_62 = alloca i32, align 4
      %var_61 = alloca i1, align 1
      %var_60 = alloca i32, align 4
      %var_59 = alloca i32, align 4
      %var_57 = alloca float, align 4
      %var_56 = alloca i32, align 4
      %var_34 = alloca i1, align 1
      %var_55 = alloca i1, align 1
      %var_54 = alloca i1, align 1
      %var_53 = alloca i32, align 4
      %var_52 = alloca i32, align 4
      %var_51 = alloca i32, align 4
      %var_50 = alloca i32, align 4
      %var_49 = alloca i1, align 1
      %var_48 = alloca i1, align 1
      %var_47 = alloca i32, align 4
      %var_46 = alloca i32, align 4
      %var_45 = alloca i1, align 1
      %var_44 = alloca i1, align 1
      %var_43 = alloca i32, align 4
      %var_42 = alloca i1, align 1
      %var_41 = alloca i1, align 1
      %var_40 = alloca i32, align 4
      %var_39 = alloca i32, align 4
      %var_38 = alloca i32, align 4
      %var_37 = alloca i1, align 1
      %var_36 = alloca i32, align 4
      %var_35 = alloca i32, align 4
      %var_18 = alloca i1, align 1
      %var_33 = alloca i1, align 1
      %var_32 = alloca i1, align 1
      %var_31 = alloca i32, align 4
      %var_30 = alloca i32, align 4
      %var_29 = alloca i1, align 1
      %var_28 = alloca i1, align 1
      %var_27 = alloca i32, align 4
      %var_26 = alloca i1, align 1
      %var_25 = alloca i1, align 1
      %var_24 = alloca i32, align 4
      %var_23 = alloca i32, align 4
      %var_22 = alloca i32, align 4
      %var_21 = alloca i1, align 1
      %var_20 = alloca i32, align 4
      %var_19 = alloca i32, align 4
      %var_14 = alloca i1, align 1
      %var_17 = alloca i1, align 1
      %var_16 = alloca i32, align 4
      %var_15 = alloca i32, align 4
      %var_10 = alloca i1, align 1
      %var_13 = alloca i1, align 1
      %var_12 = alloca i32, align 4
      %var_11 = alloca i32, align 4
      %var_6 = alloca i1, align 1
      %var_9 = alloca i1, align 1
      %var_8 = alloca i32, align 4
      %var_7 = alloca i32, align 4
      %var_0 = alloca i1, align 1
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
      store i1 %load_var_5, ptr %var_0, align 1
      store i32 3, ptr %var_7, align 4
      store i32 1, ptr %var_8, align 4
      %load_var_7 = load i32, ptr %var_7, align 4
      %load_var_8 = load i32, ptr %var_8, align 4
      %cmp_gt1 = icmp sgt i32 %load_var_7, %load_var_8
      store i1 %cmp_gt1, ptr %var_9, align 1
      %load_var_9 = load i1, ptr %var_9, align 1
      store i1 %load_var_9, ptr %var_6, align 1
      store i32 3, ptr %var_11, align 4
      store i32 1, ptr %var_12, align 4
      %load_var_11 = load i32, ptr %var_11, align 4
      %load_var_12 = load i32, ptr %var_12, align 4
      %cmp_neq = icmp ne i32 %load_var_11, %load_var_12
      store i1 %cmp_neq, ptr %var_13, align 1
      %load_var_13 = load i1, ptr %var_13, align 1
      store i1 %load_var_13, ptr %var_10, align 1
      store i32 3, ptr %var_15, align 4
      store i32 1, ptr %var_16, align 4
      %load_var_15 = load i32, ptr %var_15, align 4
      %load_var_16 = load i32, ptr %var_16, align 4
      %cmp_eq = icmp eq i32 %load_var_15, %load_var_16
      store i1 %cmp_eq, ptr %var_17, align 1
      %load_var_17 = load i1, ptr %var_17, align 1
      store i1 %load_var_17, ptr %var_14, align 1
      store i32 5, ptr %var_19, align 4
      store i32 3, ptr %var_20, align 4
      %load_var_19 = load i32, ptr %var_19, align 4
      %load_var_20 = load i32, ptr %var_20, align 4
      %cmp_gt2 = icmp sgt i32 %load_var_19, %load_var_20
      store i1 %cmp_gt2, ptr %var_21, align 1
      store i32 25, ptr %var_22, align 4
      store i32 6, ptr %var_23, align 4
      %load_var_22 = load i32, ptr %var_22, align 4
      %load_var_23 = load i32, ptr %var_23, align 4
      %rmult = mul i32 %load_var_22, %load_var_23
      store i32 %rmult, ptr %var_24, align 4
      %load_var_24 = load i32, ptr %var_24, align 4
      %cast_var_24 = icmp ne i32 %load_var_24, 0
      store i1 %cast_var_24, ptr %var_25, align 1
      %load_var_21 = load i1, ptr %var_21, align 1
      %load_var_25 = load i1, ptr %var_25, align 1
      %cmp_neq3 = icmp ne i1 %load_var_21, %load_var_25
      store i1 %cmp_neq3, ptr %var_26, align 1
      store i32 5, ptr %var_27, align 4
      %load_var_27 = load i32, ptr %var_27, align 4
      %cast_var_27 = icmp ne i32 %load_var_27, 0
      store i1 %cast_var_27, ptr %var_28, align 1
      %load_var_26 = load i1, ptr %var_26, align 1
      %load_var_28 = load i1, ptr %var_28, align 1
      %cmp_lt = icmp slt i1 %load_var_26, %load_var_28
      store i1 %cmp_lt, ptr %var_29, align 1
      store i32 25, ptr %var_30, align 4
      store i32 25, ptr %var_31, align 4
      %load_var_30 = load i32, ptr %var_30, align 4
      %load_var_31 = load i32, ptr %var_31, align 4
      %cmp_eq4 = icmp eq i32 %load_var_30, %load_var_31
      store i1 %cmp_eq4, ptr %var_32, align 1
      %load_var_29 = load i1, ptr %var_29, align 1
      %load_var_32 = load i1, ptr %var_32, align 1
      %cmp_neq5 = icmp ne i1 %load_var_29, %load_var_32
      store i1 %cmp_neq5, ptr %var_33, align 1
      %load_var_33 = load i1, ptr %var_33, align 1
      store i1 %load_var_33, ptr %var_18, align 1
      store i32 5, ptr %var_35, align 4
      store i32 3, ptr %var_36, align 4
      %load_var_35 = load i32, ptr %var_35, align 4
      %load_var_36 = load i32, ptr %var_36, align 4
      %cmp_gt6 = icmp sgt i32 %load_var_35, %load_var_36
      store i1 %cmp_gt6, ptr %var_37, align 1
      store i32 25, ptr %var_38, align 4
      store i32 6, ptr %var_39, align 4
      %load_var_38 = load i32, ptr %var_38, align 4
      %load_var_39 = load i32, ptr %var_39, align 4
      %rmult7 = mul i32 %load_var_38, %load_var_39
      store i32 %rmult7, ptr %var_40, align 4
      %load_var_40 = load i32, ptr %var_40, align 4
      %cast_var_40 = icmp ne i32 %load_var_40, 0
      store i1 %cast_var_40, ptr %var_41, align 1
      %load_var_37 = load i1, ptr %var_37, align 1
      %load_var_41 = load i1, ptr %var_41, align 1
      %cmp_neq8 = icmp ne i1 %load_var_37, %load_var_41
      store i1 %cmp_neq8, ptr %var_42, align 1
      store i32 5, ptr %var_43, align 4
      %load_var_43 = load i32, ptr %var_43, align 4
      %cast_var_43 = icmp ne i32 %load_var_43, 0
      store i1 %cast_var_43, ptr %var_44, align 1
      %load_var_42 = load i1, ptr %var_42, align 1
      %load_var_44 = load i1, ptr %var_44, align 1
      %cmp_lt9 = icmp slt i1 %load_var_42, %load_var_44
      store i1 %cmp_lt9, ptr %var_45, align 1
      store i32 25, ptr %var_46, align 4
      store i32 25, ptr %var_47, align 4
      %load_var_46 = load i32, ptr %var_46, align 4
      %load_var_47 = load i32, ptr %var_47, align 4
      %cmp_eq10 = icmp eq i32 %load_var_46, %load_var_47
      store i1 %cmp_eq10, ptr %var_48, align 1
      %load_var_45 = load i1, ptr %var_45, align 1
      %load_var_48 = load i1, ptr %var_48, align 1
      %cmp_neq11 = icmp ne i1 %load_var_45, %load_var_48
      store i1 %cmp_neq11, ptr %var_49, align 1
      store i32 32, ptr %var_50, align 4
      store i32 2, ptr %var_51, align 4
      %load_var_50 = load i32, ptr %var_50, align 4
      %load_var_51 = load i32, ptr %var_51, align 4
      %rdiv = sdiv i32 %load_var_50, %load_var_51
      store i32 %rdiv, ptr %var_52, align 4
      store i32 5, ptr %var_53, align 4
      %load_var_52 = load i32, ptr %var_52, align 4
      %load_var_53 = load i32, ptr %var_53, align 4
      %cmp_gt12 = icmp sgt i32 %load_var_52, %load_var_53
      store i1 %cmp_gt12, ptr %var_54, align 1
      %load_var_49 = load i1, ptr %var_49, align 1
      %load_var_54 = load i1, ptr %var_54, align 1
      %or_ = or i1 %load_var_49, %load_var_54
      store i1 %or_, ptr %var_55, align 1
      %load_var_55 = load i1, ptr %var_55, align 1
      store i1 %load_var_55, ptr %var_34, align 1
      store i32 12, ptr %var_56, align 4
      store float 0x3FF99999A0000000, ptr %var_57, align 4
      store i32 5, ptr %var_59, align 4
      store i32 3, ptr %var_60, align 4
      %load_var_59 = load i32, ptr %var_59, align 4
      %load_var_60 = load i32, ptr %var_60, align 4
      %cmp_gt13 = icmp sgt i32 %load_var_59, %load_var_60
      store i1 %cmp_gt13, ptr %var_61, align 1
      store i32 6, ptr %var_62, align 4
      %load_var_56 = load i32, ptr %var_56, align 4
      %load_var_62 = load i32, ptr %var_62, align 4
      %rmult14 = mul i32 %load_var_56, %load_var_62
      store i32 %rmult14, ptr %var_63, align 4
      %load_var_63 = load i32, ptr %var_63, align 4
      %cast_var_63 = icmp ne i32 %load_var_63, 0
      store i1 %cast_var_63, ptr %var_64, align 1
      %load_var_61 = load i1, ptr %var_61, align 1
      %load_var_64 = load i1, ptr %var_64, align 1
      %cmp_neq15 = icmp ne i1 %load_var_61, %load_var_64
      store i1 %cmp_neq15, ptr %var_65, align 1
      store i32 5, ptr %var_66, align 4
      %load_var_66 = load i32, ptr %var_66, align 4
      %cast_var_66 = icmp ne i32 %load_var_66, 0
      store i1 %cast_var_66, ptr %var_67, align 1
      %load_var_65 = load i1, ptr %var_65, align 1
      %load_var_67 = load i1, ptr %var_67, align 1
      %cmp_lt16 = icmp slt i1 %load_var_65, %load_var_67
      store i1 %cmp_lt16, ptr %var_68, align 1
      store i32 25, ptr %var_69, align 4
      %load_var_69 = load i32, ptr %var_69, align 4
      %cast_var_69 = sitofp i32 %load_var_69 to float
      store float %cast_var_69, ptr %var_70, align 4
      %load_var_70 = load float, ptr %var_70, align 4
      %load_var_57 = load float, ptr %var_57, align 4
      %cmp_eq17 = fcmp oeq float %load_var_70, %load_var_57
      store i1 %cmp_eq17, ptr %var_71, align 1
      %load_var_68 = load i1, ptr %var_68, align 1
      %load_var_71 = load i1, ptr %var_71, align 1
      %cmp_neq18 = icmp ne i1 %load_var_68, %load_var_71
      store i1 %cmp_neq18, ptr %var_72, align 1
      store i32 32, ptr %var_73, align 4
      store i32 2, ptr %var_74, align 4
      %load_var_73 = load i32, ptr %var_73, align 4
      %load_var_74 = load i32, ptr %var_74, align 4
      %rdiv19 = sdiv i32 %load_var_73, %load_var_74
      store i32 %rdiv19, ptr %var_75, align 4
      %load_var_75 = load i32, ptr %var_75, align 4
      %load_var_5620 = load i32, ptr %var_56, align 4
      %cmp_gt21 = icmp sgt i32 %load_var_75, %load_var_5620
      store i1 %cmp_gt21, ptr %var_76, align 1
      store i32 2, ptr %var_77, align 4
      store i32 2, ptr %var_78, align 4
      %load_var_77 = load i32, ptr %var_77, align 4
      %load_var_78 = load i32, ptr %var_78, align 4
      %cmp_gt22 = icmp sgt i32 %load_var_77, %load_var_78
      store i1 %cmp_gt22, ptr %var_79, align 1
      %load_var_76 = load i1, ptr %var_76, align 1
      %load_var_79 = load i1, ptr %var_79, align 1
      %and_ = and i1 %load_var_76, %load_var_79
      store i1 %and_, ptr %var_80, align 1
      %load_var_72 = load i1, ptr %var_72, align 1
      %load_var_80 = load i1, ptr %var_80, align 1
      %or_23 = or i1 %load_var_72, %load_var_80
      store i1 %or_23, ptr %var_81, align 1
      %load_var_81 = load i1, ptr %var_81, align 1
      store i1 %load_var_81, ptr %var_58, align 1
      store i32 5, ptr %var_83, align 4
      %load_var_83 = load i32, ptr %var_83, align 4
      %load_var_5624 = load i32, ptr %var_56, align 4
      %cmp_gt25 = icmp sgt i32 %load_var_83, %load_var_5624
      store i1 %cmp_gt25, ptr %var_84, align 1
      store i32 25, ptr %var_85, align 4
      store i32 6, ptr %var_86, align 4
      %load_var_85 = load i32, ptr %var_85, align 4
      %load_var_86 = load i32, ptr %var_86, align 4
      %rmult26 = mul i32 %load_var_85, %load_var_86
      store i32 %rmult26, ptr %var_87, align 4
      %load_var_87 = load i32, ptr %var_87, align 4
      %load_var_5627 = load i32, ptr %var_56, align 4
      %cmp_lt28 = icmp slt i32 %load_var_87, %load_var_5627
      store i1 %cmp_lt28, ptr %var_88, align 1
      store i32 2, ptr %var_89, align 4
      %load_var_89 = load i32, ptr %var_89, align 4
      %cast_var_89 = icmp ne i32 %load_var_89, 0
      store i1 %cast_var_89, ptr %var_90, align 1
      %load_var_88 = load i1, ptr %var_88, align 1
      %load_var_90 = load i1, ptr %var_90, align 1
      %cmp_neq29 = icmp ne i1 %load_var_88, %load_var_90
      store i1 %cmp_neq29, ptr %var_91, align 1
      %load_var_84 = load i1, ptr %var_84, align 1
      %load_var_91 = load i1, ptr %var_91, align 1
      %cmp_neq30 = icmp ne i1 %load_var_84, %load_var_91
      store i1 %cmp_neq30, ptr %var_92, align 1
      store i1 true, ptr %var_93, align 1
      store i32 25, ptr %var_94, align 4
      store i32 25, ptr %var_95, align 4
      %load_var_94 = load i32, ptr %var_94, align 4
      %load_var_95 = load i32, ptr %var_95, align 4
      %cmp_eq31 = icmp eq i32 %load_var_94, %load_var_95
      store i1 %cmp_eq31, ptr %var_96, align 1
      %load_var_96 = load i1, ptr %var_96, align 1
      %load_var_93 = load i1, ptr %var_93, align 1
      %not_32 = xor i1 %load_var_96, %load_var_93
      store i1 %not_32, ptr %var_97, align 1
      %load_var_92 = load i1, ptr %var_92, align 1
      %load_var_97 = load i1, ptr %var_97, align 1
      %cmp_eq33 = icmp eq i1 %load_var_92, %load_var_97
      store i1 %cmp_eq33, ptr %var_98, align 1
      %load_var_98 = load i1, ptr %var_98, align 1
      store i1 %load_var_98, ptr %var_82, align 1
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

TEST_F(LLVMTestCode, T4)
{
    const std::string output = R"(
        ; ModuleID = 'output.o'
        source_filename = "output.o"

        declare i32 @printf(ptr, ...)

        define i32 @sub(i32 %a) {
        entry:
          %a_alloca1 = alloca i32, align 4
          %a_alloca = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 2, ptr %var_0, align 4
          store i32 %a, ptr %a_alloca, align 4
          store i32 %a, ptr %a_alloca1, align 4
          %load_a = load i32, ptr %a_alloca1, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          %rminus = sub i32 %load_a, %load_var_0
          store i32 %rminus, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          ret i32 %load_var_1
        }

        define i32 @sum(i32 %p) {
        entry:
          %p_alloca = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_2 = alloca i32, align 4
          %var_0 = alloca ptr, align 8
          store ptr @gfn_sum_block, ptr %var_0, align 8
          store i32 3, ptr %var_2, align 4
          %load_var_2 = load i32, ptr %var_2, align 4
          store i32 %p, ptr %p_alloca, align 4
          %load_p = load i32, ptr %p_alloca, align 4
          %call_gfn_sum_block = call i32 @gfn_sum_block(i32 %load_var_2, i32 %load_p)
          store i32 %call_gfn_sum_block, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          ret i32 %load_var_1
        }

        define i32 @gfn_sum_block(i32 %x, i32 %p) {
        entry:
          %x_alloca1 = alloca i32, align 4
          %x_alloca = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %p_alloca = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 %p, ptr %p_alloca, align 4
          %load_p = load i32, ptr %p_alloca, align 4
          %call_sub = call i32 @sub(i32 %load_p)
          store i32 %call_sub, ptr %var_0, align 4
          store i32 %x, ptr %x_alloca, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          store i32 %x, ptr %x_alloca1, align 4
          %load_x = load i32, ptr %x_alloca1, align 4
          %rmult = mul i32 %load_var_0, %load_x
          store i32 %rmult, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          ret i32 %load_var_1
        }

        define void @main() {
        entry:
          %var_2 = alloca i32, align 4
          %var_1 = alloca i32, align 4
          %var_0 = alloca [15 x i8], align 1
          store [12 x i8] c"resutl: %u\0A\00", ptr %var_0, align 1
          store i32 3, ptr %var_1, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          %call_sum = call i32 @sum(i32 %load_var_1)
          store i32 %call_sum, ptr %var_2, align 4
          %str_ptr = getelementptr [15 x i8], ptr %var_0, i32 0, i32 0
          %load_var_2 = load i32, ptr %var_2, align 4
          %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, i32 %load_var_2)
          ret void
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn sub(a:int):int {
            return a - 2
        }

        fn sum(p:int):int {

            let block:fn = (x:int):int -> {
                return sub(a:p) * x
            }

            return block(x:3)
        }

        fn main() {
           printf(format: "resutl: %u\n", r:sum(p:3))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T5)
{
    const std::string output = R"(
        ; ModuleID = 'output.o'
        source_filename = "output.o"

        declare i32 @printf(ptr, ...)

        define void @main() {
        entry:
          %var_10 = alloca i32, align 4
          %var_12 = alloca i32, align 4
          %var_11 = alloca i32, align 4
          %var_9 = alloca i32, align 4
          %var_8 = alloca i32, align 4
          %var_7 = alloca i1, align 1
          %var_6 = alloca i32, align 4
          %var_5 = alloca i1, align 1
          %var_4 = alloca i32, align 4
          %var_3 = alloca i32, align 4
          %var_2 = alloca i1, align 1
          %var_1 = alloca i32, align 4
          %var_0 = alloca i32, align 4
          store i32 3, ptr %var_0, align 4
          br label %while_cond_0

        while_cond_0:                                     ; preds = %end_3, %entry
          store i32 5, ptr %var_1, align 4
          %load_var_0 = load i32, ptr %var_0, align 4
          %load_var_1 = load i32, ptr %var_1, align 4
          %cmp_lt = icmp slt i32 %load_var_0, %load_var_1
          store i1 %cmp_lt, ptr %var_2, align 1
          %cond_ = load i1, ptr %var_2, align 1
          br i1 %cond_, label %while_body_1, label %while_end_2

        while_body_1:                                     ; preds = %while_cond_0
          store i32 3, ptr %var_3, align 4
          store i32 3, ptr %var_4, align 4
          %load_var_3 = load i32, ptr %var_3, align 4
          %load_var_4 = load i32, ptr %var_4, align 4
          %cmp_neq = icmp ne i32 %load_var_3, %load_var_4
          store i1 %cmp_neq, ptr %var_5, align 1
          %cond_1 = load i1, ptr %var_5, align 1
          br i1 %cond_1, label %then_4, label %else_5

        then_4:                                           ; preds = %while_body_1
          store i32 55, ptr %var_6, align 4
          br label %end_3

        else_5:                                           ; preds = %while_body_1
          store i1 false, ptr %var_7, align 1
          %cond_2 = load i1, ptr %var_7, align 1
          br i1 %cond_2, label %then_6, label %else_7

        then_6:                                           ; preds = %else_5
          store i32 1254, ptr %var_8, align 4
          br label %end_3

        else_7:                                           ; preds = %else_5
          store i32 665, ptr %var_9, align 4
          br label %while_end_2

        end_3:                                            ; preds = %then_6, %then_4
          store i32 3, ptr %var_11, align 4
          %load_var_33 = load i32, ptr %var_3, align 4
          %load_var_11 = load i32, ptr %var_11, align 4
          %rmult = mul i32 %load_var_33, %load_var_11
          store i32 %rmult, ptr %var_12, align 4
          %load_var_12 = load i32, ptr %var_12, align 4
          store i32 %load_var_12, ptr %var_10, align 4
          br label %while_cond_0

        while_end_2:                                      ; preds = %else_7, %while_cond_0
          %var_13 = alloca [14 x i8], align 1
          store [11 x i8] c"Finalizou\0A\00", ptr %var_13, align 1
          %str_ptr = getelementptr [14 x i8], ptr %var_13, i32 0, i32 0
          %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr)
          ret void
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
            mut let x:int = 3
            while (x < 5) {
                let z:int = 3
                if (z != 3) {
                    let z:int = 55
                } else if (false) {
                    let op:int = 1254
                } else {
                    let pp:int = 665
                    break
                }
                let n:int = z * 3
            }

            printf(format:"Finalizou\n")
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T6)
{
    const std::string output = R"(
     ; ModuleID = 'output.o'
    source_filename = "output.o"

    declare i32 @printf(ptr, ...)

    define void @main() {
    entry:
      %var_4 = alloca i32, align 4
      %var_3 = alloca i32, align 4
      %var_2 = alloca i1, align 1
      %var_1 = alloca i32, align 4
      %var_0 = alloca i32, align 4
      store i32 0, ptr %var_0, align 4
      br label %while_cond_0

    while_cond_0:                                     ; preds = %while_body_1, %entry
      store i32 10, ptr %var_1, align 4
      %load_var_0 = load i32, ptr %var_0, align 4
      %load_var_1 = load i32, ptr %var_1, align 4
      %cmp_lt = icmp slt i32 %load_var_0, %load_var_1
      store i1 %cmp_lt, ptr %var_2, align 1
      %cond_ = load i1, ptr %var_2, align 1
      br i1 %cond_, label %while_body_1, label %while_end_2

    while_body_1:                                     ; preds = %while_cond_0
      store i32 1, ptr %var_3, align 4
      %load_var_01 = load i32, ptr %var_0, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %rplus = add i32 %load_var_01, %load_var_3
      store i32 %rplus, ptr %var_4, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      store i32 %load_var_4, ptr %var_0, align 4
      %var_5 = alloca [19 x i8], align 1
      store [16 x i8] c"value if x: %i\0A\00", ptr %var_5, align 1
      %str_ptr = getelementptr [19 x i8], ptr %var_5, i32 0, i32 0
      %load_var_02 = load i32, ptr %var_0, align 4
      %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, i32 %load_var_02)
      br label %while_cond_0

        while_end_2:                                      ; preds = %while_cond_0
          ret void
        }
    )";

    const std::string input = R"(
        import std.output.printf

        fn main() {
            mut let x: int = 0
            while x < 10 {
                x = x + 1
                printf(format:"value if x: %i\n", r:x)
            }
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T7)
{
    const std::string output = R"(
        ; ModuleID = 'main.o'
        source_filename = "main.o"

        %struct.Pessoa = type { ptr, i32, float, double, i1 }

        define void @main() {
        entry:
          %var_5 = alloca i1, align 1
          %var_4 = alloca double, align 8
          %var_3 = alloca float, align 4
          %var_2 = alloca i32, align 4
          %var_0 = alloca %struct.Pessoa, align 8
          %var_1 = alloca [9 x i8], align 1
          store [7 x i8] c"Thiago\00", ptr %var_1, align 1
          store i32 37, ptr %var_2, align 4
          store float 1.750000e+00, ptr %var_3, align 4
          store double 0x40A3888219652BD4, ptr %var_4, align 8
          store i1 true, ptr %var_5, align 1
          %load_var_1 = load ptr, ptr %var_1, align 8
          %name = getelementptr inbounds %struct.Pessoa, ptr %var_0, i32 0, i32 0
          store ptr %load_var_1, ptr %name, align 8
          %load_var_2 = load i32, ptr %var_2, align 4
          %idade = getelementptr inbounds %struct.Pessoa, ptr %var_0, i32 0, i32 1
          store i32 %load_var_2, ptr %idade, align 4
          %load_var_3 = load float, ptr %var_3, align 4
          %altura = getelementptr inbounds %struct.Pessoa, ptr %var_0, i32 0, i32 2
          store float %load_var_3, ptr %altura, align 4
          %load_var_4 = load double, ptr %var_4, align 8
          %salario = getelementptr inbounds %struct.Pessoa, ptr %var_0, i32 0, i32 3
          store double %load_var_4, ptr %salario, align 8
          %load_var_5 = load i1, ptr %var_5, align 1
          %casado = getelementptr inbounds %struct.Pessoa, ptr %var_0, i32 0, i32 4
          store i1 %load_var_5, ptr %casado, align 1
          ret void
        }
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
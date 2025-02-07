#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include "antlr4-runtime.h"

#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "../src/headers/Hlir.h"
#include "../src/headers/LLVMIR.h"
#include "../src/headers/SemanticalAnalysis.h"
#include "../src/headers/HLIRGenerator.h"

// Create a test fixture in the same style
class LLVMTestCode : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialize anything before each test if necessary.
    }

    /**
     * @brief Removes all whitespace characters from a given string.
     * @param str The input string.
     * @return A new string without any whitespace characters.
     */
    // Função que remove todos os caracteres de espaço em branco
    // Função que remove todos os caracteres de espaço em branco após aplicar o trim
    static std::string removeWhitespace(const std::string& str)
    {
        std::string result;
        result.reserve(str.size());

        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });

        return result;
    }

    /**
     * @brief Compares two strings for equality, ignoring any whitespace differences.
     * @param input The generated string from the test.
     * @param expectedOutput The expected string to compare against.
     *
     * If the strings match (ignoring whitespace), the test passes.
     * Otherwise, it fails and outputs the generated and expected strings.
     */
    static void runAnalysis(const std::string& input, const std::string &expectedOutput)
    {
        const auto hlirOutPut = getHighLevelCode(input);
        const auto cleanInput = removeWhitespace(hlirOutPut);
        if (const auto cleanExpected = removeWhitespace(expectedOutput); cleanInput == cleanExpected)
        {
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

    static std::string getHighLevelCode(const std::string& input)
    {
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticAnalysis analysis(parser, std::move(std::make_unique<scope::ScopeManager>()),loadStringAsLines(input));
        analysis.analyze();

        // Rewind
        tokens.seek(0);
        parser->reset();

        auto context = std::make_shared<hlir::Context>();
        hlir::HLIRGenerator hightLevelCodeGenerator(parser, context);
        const auto hlirCode = hightLevelCodeGenerator.generateCode();
        // std::cout << hlirCode << std::endl;

        iron::LLVM llvm(context);
        auto llvmCode = llvm.generateCode();
        // std::cout << llvmCode << std::endl;
        return llvmCode;
    }
};

//-----------------------------------------------------------
// TESTS FOR THE CLASS FunctionArgs
//-----------------------------------------------------------

TEST_F(LLVMTestCode, T1)
{
    const std::string output = R"(
        ; ModuleID = 'file_1'
        source_filename = "file_1"
        target triple = "arm64-apple-macosx15.0.0"

        define i32 @main() {
        entry:
          %r = alloca i32, align 4
          %var_9 = alloca i32, align 4
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
          %cast_var_8 = fptosi float %load_var_8 to i32
          store i32 %cast_var_8, ptr %var_9, align 4
          %load_var_9 = load i32, ptr %var_9, align 4
          store i32 %load_var_9, ptr %r, align 4
          %load_r = load i32, ptr %r, align 4
          ret i32 %load_r
        }
    )";

    const std::string input = R"(
        fn main(): int {
            let a:int = 10
            let b:float = 20.5

            let r:int = (a + b / 2) * 3
            return r
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T2)
{
    const std::string output = R"(
        ; ModuleID = 'file_1'
        source_filename = "file_1"
        target triple = "arm64-apple-macosx15.0.0"

        define void @main() {
        entry:
          %r2 = alloca float, align 4
          %var_15 = alloca float, align 4
          %var_14 = alloca double, align 8
          %var_13 = alloca double, align 8
          %var_12 = alloca double, align 8
          %var_11 = alloca double, align 8
          %var_10 = alloca float, align 4
          %r = alloca i32, align 4
          %var_9 = alloca i32, align 4
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
          %cast_var_8 = fptosi float %load_var_8 to i32
          store i32 %cast_var_8, ptr %var_9, align 4
          %load_var_9 = load i32, ptr %var_9, align 4
          store i32 %load_var_9, ptr %r, align 4
          store float 2.500000e+00, ptr %var_10, align 4
          %load_var_10 = load float, ptr %var_10, align 4
          %cast_var_10 = fpext float %load_var_10 to double
          store double %cast_var_10, ptr %var_11, align 8
          %load_var_11 = load double, ptr %var_11, align 8
          %load_d = load double, ptr %d, align 8
          %rdiv1 = fdiv double %load_var_11, %load_d
          store double %rdiv1, ptr %var_12, align 8
          %load_r = load i32, ptr %r, align 4
          %cast_r = sitofp i32 %load_r to double
          store double %cast_r, ptr %var_13, align 8
          %load_var_13 = load double, ptr %var_13, align 8
          %load_var_12 = load double, ptr %var_12, align 8
          %rminus = fsub double %load_var_13, %load_var_12
          store double %rminus, ptr %var_14, align 8
          %load_var_14 = load double, ptr %var_14, align 8
          %cast_var_14 = fptrunc double %load_var_14 to float
          store float %cast_var_14, ptr %var_15, align 4
          %load_var_15 = load float, ptr %var_15, align 4
          store float %load_var_15, ptr %r2, align 4
          ret void
        }
    )";

    const std::string input = R"(
        fn main() {
            let a:int = 10
            let b:float = 11.36
            let d:double = 20.5D

            let r:int = (a + b / 2) * 3
            let r2:float = r - 2.5 / d
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T3)
{
    const std::string output = R"(
    ; ModuleID = 'file_1'
    source_filename = "file_1"
    target triple = "arm64-apple-macosx15.0.0"

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

    std::string input = R"(
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
    ; ModuleID = 'file_1'
    source_filename = "file_1"
    target triple = "arm64-apple-macosx15.0.0"

    define void @soma(i32 %x, i32 %b) {
    entry:
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
    ret void
    }
    )";

    const std::string input = R"(
        fn soma(x:int, b:int) {
            x + b * 1.145
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T5)
{
    const std::string output = R"(
    ; ModuleID = 'file_1'
    source_filename = "file_1"
    target triple = "arm64-apple-macosx15.0.0"

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
      %rplus = add i32 %load_bx, %load_bx
      store i32 %rplus, ptr %var_3, align 4
      store i32 %nx, ptr %nx_alloca, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_nx = load i32, ptr %nx_alloca, align 4
      %rminus = sub i32 %load_var_3, %load_nx
      store i32 %rminus, ptr %var_4, align 4
      %load_var_4 = load i32, ptr %var_4, align 4
      ret i32 %load_var_4
    }

    define void @soma() {
    entry:
      %var_4 = alloca float, align 4
      %var_3 = alloca float, align 4
      %var_2 = alloca i32, align 4
      %var_1 = alloca float, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      %call_sub = call i32 @sub(i32 1, i32 32, i32 25)
      store i32 %call_sub, ptr %var_2, align 4
      %load_var_2 = load i32, ptr %var_2, align 4
      %cast_var_2 = sitofp i32 %load_var_2 to float
      store float %cast_var_2, ptr %var_3, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %rmult = fmul float %load_var_1, %load_var_3
      store float %rmult, ptr %var_4, align 4
      ret void
    }
    )";

    const std::string input = R"(
        fn sub(ax:int, bx:int, nx:int): int {
            return ax / 2 + bx - nx
        }

        fn soma() {
            32.25 * sub(ax: 1, bx: 32, nx: 25)
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T6)
{
    const std::string output = R"(
    ; ModuleID = 'file_1'
    source_filename = "file_1"
    target triple = "arm64-apple-macosx15.0.0"

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

    define void @soma() {
    entry:
      %var_4 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_3 = alloca float, align 4
      %var_1 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      %load_x = load float, ptr %x, align 4
      %call_mult = call float @mult(i32 22, float %load_x)
      store float %call_mult, ptr %var_3, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %call_sub = call float @sub(i32 1, float %load_var_3)
      store float %call_sub, ptr %var_2, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rmult = fmul float %load_var_1, %load_var_2
      store float %rmult, ptr %var_4, align 4
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

        fn soma() {
            let x: float = 25.00
            32.25 * sub(ax: 1, bx: mult(n:22, p:x))
        }
    )";

    runAnalysis(input, output);
}

TEST_F(LLVMTestCode, T7)
{
    const std::string output = R"(
    ; ModuleID = 'file_1'
    source_filename = "file_1"
    target triple = "arm64-apple-macosx15.0.0"

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

    define void @soma() {
    entry:
      %var_5 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_4 = alloca float, align 4
      %var_3 = alloca float, align 4
      %var_1 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      %load_x = load float, ptr %x, align 4
      %call_gfn_soma_inline = call float @gfn_soma_inline(i32 25, float %load_x)
      store float %call_gfn_soma_inline, ptr %var_3, align 4
      %load_var_3 = load float, ptr %var_3, align 4
      %call_mult = call float @mult(i32 22, float %load_var_3)
      store float %call_mult, ptr %var_4, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      %call_sub = call float @sub(i32 1, float %load_var_4)
      store float %call_sub, ptr %var_2, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rmult = fmul float %load_var_1, %load_var_2
      store float %rmult, ptr %var_5, align 4
      ret void
    }

    define float @gfn_soma_inline(i32 %a, float %x) {
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

        fn soma() {
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
    ; ModuleID = 'file_1'
    source_filename = "file_1"
    target triple = "arm64-apple-macosx15.0.0"

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

    define float @soma() {
    entry:
      %var_6 = alloca float, align 4
      %var_2 = alloca float, align 4
      %var_5 = alloca float, align 4
      %var_4 = alloca float, align 4
      %var_3 = alloca i32, align 4
      %var_1 = alloca float, align 4
      %x = alloca float, align 4
      store float 2.500000e+01, ptr %x, align 4
      store float 3.225000e+01, ptr %var_1, align 4
      %load_x = load float, ptr %x, align 4
      %call_gfn_soma_block = call i32 @gfn_soma_block(i32 25, float %load_x)
      store i32 %call_gfn_soma_block, ptr %var_3, align 4
      %load_var_3 = load i32, ptr %var_3, align 4
      %load_x1 = load float, ptr %x, align 4
      %call_gfn_soma_inline = call float @gfn_soma_inline(i32 %load_var_3, float %load_x1)
      store float %call_gfn_soma_inline, ptr %var_4, align 4
      %load_var_4 = load float, ptr %var_4, align 4
      %call_mult = call float @mult(i32 22, float %load_var_4)
      store float %call_mult, ptr %var_5, align 4
      %load_var_5 = load float, ptr %var_5, align 4
      %call_sub = call float @sub(i32 1, float %load_var_5)
      store float %call_sub, ptr %var_2, align 4
      %load_var_1 = load float, ptr %var_1, align 4
      %load_var_2 = load float, ptr %var_2, align 4
      %rmult = fmul float %load_var_1, %load_var_2
      store float %rmult, ptr %var_6, align 4
      %load_var_6 = load float, ptr %var_6, align 4
      ret float %load_var_6
    }

    define i32 @gfn_soma_block(i32 %a, float %x) {
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

    define float @gfn_soma_inline(i32 %a, float %x) {
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

        fn soma(): float {
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

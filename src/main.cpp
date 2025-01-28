#include <iostream>
#include <memory>
#include "headers/SemanticalAnalysis.h"
#include "headers/Hlir.h"
#include "headers/HLIRGenerator.h"
#include "scope/ScopeManager.h"
#include "parsers/IronLexer.h"
#include <antlr4-runtime.h>

#include <sstream> // std::stringstream
#include <string>
#include <vector>

// Recebe todo o código em uma única string e devolve um vetor de strings,
// onde cada elemento corresponde a uma linha.
std::vector<std::string> loadStringAsLines(const std::string &code)
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

int runAnalysis(const std::string &input)
{
    try
    {

        // Inicializa os componentes do ANTLR
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticalAnalysis analysis(parser, std::move(std::make_unique<scope::ScopeManager>()), loadStringAsLines(input));
        analysis.analyze();

        // // Rewind
        tokens.seek(0);
        parser->reset();

        // auto context = std::make_shared<hlir::Context>();
        // hlir::HLIRGenerator hightLevelCodeGenerator(parser, context);
        // const auto hlirCode = hightLevelCodeGenerator.generateCode();
        // std::cout << hlirCode << std::endl;

        // iron::LLVM llvm(context);
        // auto llvmCode = llvm.generateCode();
        // std::cout << llvmCode << std::endl;

        return 0; // Sucesso
    }
    catch (const iron::SemanticException &e)
    {
        std::cerr << color::colorText("Semantic error: ", color::RED) << e.what() << std::endl;
        return 1; // Erro semântico específico
    }
    catch (const hlir::HLIRException e)
    {
        std::cerr << color::colorText("HLIRE error: ", color::RED) << e.what() << std::endl;
        return 1; // Erro semântico específico
    }
    catch (const iron::LLVMException e)
    {
        std::cerr << color::colorText("LLVM error: ", color::RED) << e.what() << std::endl;
        return 1; // Erro semântico específico
    }
    catch (const std::exception &e)
    {
        std::cerr << color::colorText("Unexpected error: ", color::RED) << e.what() << std::endl;
        return 2; // Outros erros padrão
    }
    catch (...)
    {
        std::cerr << color::colorText("I panicked, I need a psychoanalyst: ", color::BOLD_RED) << std::endl;
        return 3; // Exceções não esperadas
    }
}

int main()
{
    std::string input = R"(

        fn sub(a:int, b:int):int {}

        fn main() {
            sub(a:10,b:p) * 36.69
        }


    )";

    return runAnalysis(input);
}

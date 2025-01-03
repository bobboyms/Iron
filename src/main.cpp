#include <iostream>
#include <memory>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"
#include "headers/SemanticalAnalysis.h"
#include "headers/ScopeManager.h"
#include "headers/IronExceptions.h"
#include "headers/HighLevelIR.h"
#include "headers/Colors.h"

int runAnalysis(const std::string& input) {
    try {
        // Inicializa os componentes do ANTLR
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticalAnalysis analysis(parser, std::move(std::make_unique<iron::ScopeManager>()));
        analysis.analyze();

        // Rewind
        tokens.seek(0);
        parser->reset();

        //iron::HighLevelIR hightLevelCodeGenerator(parser, std::move(std::make_unique<iron::ScopeManager>()));
        //const auto hlir = hightLevelCodeGenerator.generateCode();

        //std::cout << hlir << std::endl;

        //std::cout << "Análise semântica concluída com sucesso." << std::endl;
        return 0; // Sucesso

    } catch (const SemanticException& e) {
        std::cerr << color::colorText("Semantic error: ", color::RED) << e.what() << std::endl;
        return 1; // Erro semântico específico
    } catch (const std::exception& e) {
        std::cerr << color::colorText("Unexpected error: ", color::RED) << e.what() << std::endl;
        return 2; // Outros erros padrão
    } catch (...) {
        std::cerr << color::colorText("I panicked, I need a psychoanalyst: ", color::BOLD_RED) << std::endl;
        return 3; // Exceções não esperadas
    }
}

int main() {
    std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {}
                    let result:float =  block(a:12, b:12.26) * x
                }
                let result:float =  27 * block(a:12, b:12.26)
            }
        }
    )";

    return runAnalysis(input);
}

    
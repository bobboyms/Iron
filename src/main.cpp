#include <iostream>
#include <memory>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"
#include "headers/SemanticalAnalysis.h"
#include "headers/ScopeManager.h"
#include "headers/IronExceptions.h"
#include "headers/Colors.h"

int runAnalysis(const std::string& input) {
    try {
        // Inicializa os componentes do ANTLR
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_unique<IronParser>(&tokens);
        auto scopeManager = std::make_unique<ScopeManager>();

        // Executa a análise semântica
        SemanticalAnalysis analysis(std::move(parser), std::move(scopeManager));
        analysis.analyze();

        std::cout << "Análise semântica concluída com sucesso." << std::endl;
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

        fn mult(pp:float):float {
        }

        fn xptc(z:float):int {
        }

        fn main() {
            let xb: int = 36
            let inline:fn = (a: int, b: int):int -> (xb + b) * a
            let sum:fn = (x: int, y: int):float -> 2.25 + x + y

            5.22 + inline(a:12, b:14) * sum(x:12, y:87) - xptc(z:mult(pp:12.00F)) / xb
        }
    )";

    return runAnalysis(input);
}

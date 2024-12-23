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
        
        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            32.25 * sub(ax: 1, bx: 25.32)
        }
    )";

    return runAnalysis(input);
}

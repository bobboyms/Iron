#include <iostream>
#include <memory>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"
#include "headers/SemanticalAnalysis.h"
#include "headers/ScopeManager.h"
#include "headers/SemanticException.h"
#include "Utils.cpp"

int main() {
    std::string input = R"(
        fn teste() {
            let x: int
            let b: fn = (a: int, b: int) -> a * b
        }
    )";

    // Inicializa os componentes do ANTLR
    antlr4::ANTLRInputStream inputStream(input);
    IronLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    auto parser = std::make_unique<IronParser>(&tokens);
    auto scopeManager = std::make_unique<ScopeManager>();

    // Executa a análise semântica
    SemanticalAnalysis analysis(std::move(parser), std::move(scopeManager));

    analysis.analyze();

    return 0;
}

#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>

// Ajuste os includes conforme a organização do seu projeto
#include "../src/headers/Exceptions.h"
#include "../src/headers/SemanticAnalysis.h"
#include "../src/parsers/IronLexer.h"
#include "../src/parsers/IronParser.h"
#include "antlr4-runtime.h" // Removida a barra '/'

// Base test fixture for semantic analysis tests
class SemanticAnalysisTestBase : public ::testing::Test
{
protected:
    void SetUp() override
    {
        scopeManager = std::make_unique<scope::ScopeManager>();
    }

    void runAnalysis(const std::string &input)
    {
        auto config = std::make_shared<config::Configuration>("compiler_config.yaml");

        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_unique<IronParser>(&tokens);
        semanticAnalysis = std::make_unique<iron::SemanticAnalysis>(std::move(parser), std::move(scopeManager),
                                                                loadStringAsLines(input), config);

        // Executa a análise semântica
        semanticAnalysis->analyze();
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

    std::unique_ptr<scope::ScopeManager> scopeManager;
    std::unique_ptr<iron::SemanticAnalysis> semanticAnalysis;
};
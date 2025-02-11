//
// Created by Thiago Rodrigues on 07/02/25.
//

#include "../headers/Analyser.h"
#include "../headers/Files.h"
#include "../headers/HLIRGenerator.h"
#include "../headers/Hlir.h"

namespace iron
{
    Analyser::Analyser(const std::shared_ptr<config::Configuration> &config) : config(config)
    {
    }

    Analyser::~Analyser() = default;

    std::vector<std::string> Analyser::loadStringAsLines(const std::string &code)
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

    std::shared_ptr<hlir::Context> Analyser::hlir(const std::string &fileName)
    {
        // Certifique-se de que o código de entrada esteja disponível para o parser.
        // Por exemplo, se você tiver o código em uma string 'input':
        // printf("File: %s\n", fileName.c_str());
        const auto input = fileContent(fileName);
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        parser = std::make_shared<IronParser>(&tokens);

        const auto context = std::make_shared<hlir::Context>();
        hlir::HLIRGenerator highLevelCodeGenerator(parser, context, config);
        highLevelCodeGenerator.getContext();

        const auto hlirPath = util::format("{}", config->outputTempFiles());
        saveToFile(context->getText(), hlirPath, "main.hlir");

        return context;
    }

    std::vector<std::shared_ptr<scope::Function>> Analyser::semantic(const std::string &fileName)
    {

        const auto input = fileContent(fileName);

        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        SemanticAnalysis analysis(parser, std::move(std::make_unique<scope::ScopeManager>()),
                                        loadStringAsLines(input), config);



        return analysis.analyze();







        //
        // iron::LLVM llvm(context);
        // auto llvmCode = llvm.generateCode();
        // std::cout << llvmCode << std::endl;


    }
} // namespace iron

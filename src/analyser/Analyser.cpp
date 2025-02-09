//
// Created by Thiago Rodrigues on 07/02/25.
//

#include "../headers/Analyser.h"
#include "../headers/Files.h"
// #include "../headers/Utils.h"

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

    int Analyser::run(const std::string &fileName)
    {
        try
        {
            const auto input = fileContent(fileName);

            antlr4::ANTLRInputStream inputStream(input);
            IronLexer lexer(&inputStream);
            antlr4::CommonTokenStream tokens(&lexer);
            parser = std::make_shared<IronParser>(&tokens);

            // Executa a análise semântica
            SemanticAnalysis analysis(parser, std::move(std::make_unique<scope::ScopeManager>()),
                                            loadStringAsLines(input), config);
            analysis.analyze();

            // // Rewind
            tokens.seek(0);
            parser->reset();



            // auto context = std::make_shared<hlir::Context>();
            // hlir::HLIRGenerator hightLevelCodeGenerator(parser, context);
            // const auto hlirCode = hightLevelCodeGenerator.generateCode();
            // std::cout << hlirCode << std::endl;
            //
            // iron::LLVM llvm(context);
            // auto llvmCode = llvm.generateCode();
            // std::cout << llvmCode << std::endl;

            return 0;
        }
        catch (const iron::SemanticException &e)
        {
            std::cerr << color::colorText("Semantic error: ", color::RED) << e.what() << std::endl;
            return 1;
        }
        catch (const hlir::HLIRException &e)
        {
            std::cerr << color::colorText("HLIRE error: ", color::RED) << e.what() << std::endl;
            return 2; // Erro semântico específico
        }
        catch (const iron::LLVMException &e)
        {
            std::cerr << color::colorText("LLVM error: ", color::RED) << e.what() << std::endl;
            return 3; // Erro semântico específico
        }
        catch (const std::exception &e)
        {
            std::cerr << color::colorText("Unexpected error: ", color::RED) << e.what() << std::endl;
            return 4; // Outros erros padrão
        }
        catch (...)
        {
            std::cerr << color::colorText("I panicked, I need a psychoanalyst: ", color::BOLD_RED) << std::endl;
            return 6;
        }
    }
} // namespace iron

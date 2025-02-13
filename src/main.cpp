#include <antlr4-runtime.h>
#include "headers/Analyser.h"
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <yaml-cpp/yaml.h>
// #include "headers/Configuration.h"
// #include "headers/LLVM.h"
#include "headers/Analyser.h"
// #include "parsers/IronLexer.h"
// #include "scope/ScopeManager.h"

// Recebe todo o código em uma única string e devolve um vetor de strings,
// onde cada elemento corresponde a uma linha.


std::string getFileNameWithoutExtension(const std::string &filePath)
{
    const std::filesystem::path path(filePath); // Cria um objeto 'path' a partir do caminho do arquivo
    return path.stem().string() + ".o";
}

void runAnalysis(const std::string &file)
{
    try
    {
        const auto contexts = std::make_shared<std::map<std::string, std::shared_ptr<hlir::Context>>>();

        const auto config = std::make_shared<config::Configuration>("compiler_config.yaml");
        const iron::Analyser analyser(config);
        analyser.semantic(file);
        const auto context = analyser.hlir(file, contexts);
        contexts->emplace("main", context);

        auto objectFiles = std::vector<std::string>();
        for (const auto &[path, context]: *contexts)
        {
            printf("%s\n", "******************************");
            printf("%s\n", path.c_str());
            const auto filename = getFileNameWithoutExtension(path);
            objectFiles.push_back(filename);

            // printf("%s\n", filename.c_str());
            iron::LLVM llvm(context, filename);
            auto module = llvm.generateCode();
            iron::LLVM::emitObjectFile(std::move(module).get(), filename);
        }

        std::string exeName = "my_executable";
        iron::LLVM::linkExecutable(objectFiles, exeName, "arm64", "15.0.0");


        // printf("%s", context->getText().c_str());
    }
    catch (const iron::SemanticException &e)
    {
        std::cerr << color::colorText("Semantic error: ", color::RED) << e.what() << std::endl;
    }
    catch (const hlir::HLIRException &e)
    {
        std::cerr << color::colorText("HLIRE error: ", color::RED) << e.what() << std::endl;
    }
    catch (const iron::LLVMException &e)
    {
        std::cerr << color::colorText("LLVM error: ", color::RED) << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << color::colorText("Unexpected error: ", color::RED) << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << color::colorText("I panicked, I need a psychoanalyst: ", color::BOLD_RED) << std::endl;
    }
}

int main()
{
    runAnalysis("main.iron");
    return 0;
}

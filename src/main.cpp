#include <antlr4-runtime.h>
#include "headers/Analyser.h"
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <yaml-cpp/yaml.h>
// #include "headers/Configuration.h"
// #include "headers/LLVMIR.h"
#include "headers/Analyser.h"
// #include "parsers/IronLexer.h"
// #include "scope/ScopeManager.h"

// Recebe todo o código em uma única string e devolve um vetor de strings,
// onde cada elemento corresponde a uma linha.


void runAnalysis(const std::string &file)
{
    try
    {
        const auto config = std::make_shared<config::Configuration>("compiler_config.yaml");
        iron::Analyser analyser(config);
        analyser.semantic(file);
        const auto context = analyser.hlir(file);

        printf("%s", context->getText().c_str());

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

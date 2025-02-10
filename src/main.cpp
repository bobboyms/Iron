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
    const auto config = std::make_shared<config::Configuration>("compiler_config.yaml");
    iron::Analyser analyser(config);
    analyser.run(file);

}

int main()
{
    runAnalysis("main.iron");
    return 0;
}

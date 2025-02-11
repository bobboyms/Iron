//
// Created by Thiago Rodrigues on 07/02/25.
//

#ifndef ANALYSER_H
#define ANALYSER_H

#include <antlr4-runtime.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "../headers/Configuration.h"
#include "../headers/LLVMIR.h"
#include "../headers/SemanticAnalysis.h"
#include "../parsers/IronLexer.h"
#include "../scope/ScopeManager.h"

namespace iron
{
    class Analyser {
    private:
        std::shared_ptr<IronParser> parser;
        std::shared_ptr<config::Configuration> config;
        std::shared_ptr<std::vector<std::string>> files;
    public:
        explicit Analyser(const std::shared_ptr<config::Configuration> &config);
        ~Analyser();
        std::vector<std::shared_ptr<scope::Function>> semantic(const std::string &fileName);
        static std::vector<std::string> loadStringAsLines(const std::string &code);
        std::shared_ptr<hlir::Context>
        hlir(const std::string &fileName,
             const std::shared_ptr<std::vector<std::pair<std::string, std::string>>> &hilirFiles) const;

        // std::shared_ptr<hlir::Context> hlir(const std::string &fileName,
        //      const std::shared_ptr<std::vector<std::pair<std::string, std::string>>> &hilirFiles) const;
    };
}





#endif //ANALYSER_H

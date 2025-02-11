//
// Created by Thiago Rodrigues on 07/02/25.
//
#include "../headers/Configuration.h"


namespace config
{
    std::string Configuration::stdFolder()
    {
        if (configFile["libs"] && configFile["libs"]["std"]) {
            return configFile["libs"]["std"].as<std::string>();
        }

        throw std::runtime_error("key libs and std not found in compiler_config.yaml");
    }

    std::string Configuration::outputHLIR()
    {
        if (configFile["compiler"] && configFile["compiler"]["output_hlir"]) {
            return configFile["compiler"]["output_hlir"].as<std::string>();
        }

        throw std::runtime_error("key compiler and output_hlir not found in compiler_config.yaml");
    }

    std::string Configuration::outputLLVM()
    {
        if (configFile["compiler"] && configFile["compiler"]["output_llvm"]) {
            return configFile["compiler"]["output_llvm"].as<std::string>();
        }

        throw std::runtime_error("key compiler and output_llvm not found in compiler_config.yaml");
    }

    Configuration::Configuration(const std::string &configFolder)
    {
        if (configFolder.empty())
        {
            throw std::runtime_error("empty folder path to find compiler_config.yaml");
        }

        configFile = YAML::LoadFile(configFolder);
    }
}



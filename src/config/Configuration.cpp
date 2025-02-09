//
// Created by Thiago Rodrigues on 07/02/25.
//
#include "../headers/Configuration.h"


namespace config
{
    std::string Configuration::getStdFolder()
    {
        if (configFile["libs"] && configFile["libs"]["std"]) {
            return configFile["libs"]["std"].as<std::string>();
        }

        throw std::runtime_error("key libs not found in compiler_config.yaml");
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



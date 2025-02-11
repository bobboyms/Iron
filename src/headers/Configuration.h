//
// Created by Thiago Rodrigues on 07/02/25.
//

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "yaml-cpp/yaml.h"
#include <string>


namespace config
{
    class Configuration
    {
    private:
        YAML::Node configFile;

    public:
        std::string stdFolder();
        std::string outputTempFiles();
        explicit Configuration(const std::string &configFolder);
    };


} // namespace config

#endif // CONFIGURATION_H

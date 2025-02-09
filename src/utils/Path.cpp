#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include "../headers/Files.h"
#include "../headers/Utils.h"


namespace iron
{
    std::pair<std::string, std::string> convertImportPath(const std::string &importPath)
    {
        std::vector<std::string> parts;
        std::istringstream iss(importPath);
        std::string token;

        while (std::getline(iss, token, '.'))
        {
            if (!token.empty())
            {
                parts.push_back(token);
            }
        }

        // There must be at least two tokens (one for the module and one for the function)
        if (parts.size() < 2)
        {
            throw std::invalid_argument(
                "The importPath must contain at least one '.' separator to indicate the module and function.");
        }

        // The last token is the function name
        std::string functionName = parts.back();
        parts.pop_back();

        // Build the module file path using the remaining tokens
        std::string moduleFilePath;
        for (const std::string &part : parts)
        {
            moduleFilePath += "/" + part;
        }
        moduleFilePath += ".iron";

        return std::make_pair(moduleFilePath, functionName);
    }

    std::string fileContent(const std::string &importPath)
    {
        std::ifstream file(importPath);

        if (!file)
        {
            throw SemanticException(util::format("Module not found: {}", importPath));
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }
}

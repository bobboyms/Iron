#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "../headers/Files.h"
#include "../headers/Utils.h"

namespace fs = std::filesystem;

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

    std::pair<std::string, std::string> saveToFile(const std::string &text, const std::string &directory, const std::string &filename)
    {
        // 1. Substitui os pontos por sublinhados no diretório e no nome do arquivo.
        std::string fixedDirectory = directory;
        std::replace(fixedDirectory.begin(), fixedDirectory.end(), '.', '_');

        std::string fixedFilename = filename;
        // std::replace(fixedFilename.begin(), fixedFilename.end(), '.', '_');

        // 2. Cria o diretório, se necessário.
        if (fs::path dir(fixedDirectory); !fs::exists(dir))
        {
            if (!create_directories(dir))
            {
                throw::std::runtime_error("Não foi possível criar o diretório:  " + fixedDirectory);
            }
        }

        // 3. Constrói o caminho completo para o arquivo.
        std::string fullPath = fixedDirectory;
        if (!fullPath.empty() && fullPath.back() != PATH_SEPARATOR)
        {
            fullPath.push_back(PATH_SEPARATOR);
        }
        fullPath += fixedFilename;

        // 4. Abre o arquivo para escrita, sobrescrevendo se ele já existir.
        std::ofstream outFile(fullPath, std::ios::out | std::ios::trunc);
        if (!outFile.is_open())
        {
            throw::std::runtime_error("Erro: Não foi possível abrir o arquivo para escrita: " + fullPath);
        }

        // 5. Escreve o conteúdo e fecha o arquivo.
        outFile << text;
        outFile.close();

        return std::make_pair(fixedDirectory, fixedFilename);

    }
} // namespace iron

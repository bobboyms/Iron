#ifndef FILES_UTILS_H
#define FILES_UTILS_H

#ifdef _WIN32
    const char PATH_SEPARATOR = '\\';
#else
const char PATH_SEPARATOR = '/';
#endif

#include <iostream>
#include <string>
#include <fstream>

namespace iron
{
    std::pair<std::string, std::string> convertImportPath(const std::string &importPath);
    std::string fileContent(const std::string &importPath);
    void saveToFile(const std::string &text, const std::string &directory, const std::string &filename);

}
#endif // FILES_UTILS_H
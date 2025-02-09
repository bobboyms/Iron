#ifndef FILES_UTILS_H
#define FILES_UTILS_H

#include <iostream>
#include <string>
#include <fstream>

namespace iron
{
    std::pair<std::string, std::string> convertImportPath(const std::string &importPath);
    std::string fileContent(const std::string &importPath);

}
#endif // FILES_UTILS_H
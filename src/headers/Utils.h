#ifndef HLIR_UTILS_H
#define HLIR_UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include "TokenMap.h"

namespace util
{

    // Função auxiliar recursiva que substitui o primeiro placeholder "{}" pelo argumento atual
    template<typename T>
    std::string format(const std::string &str, const T &value)
    {
        std::ostringstream oss;
        oss << value;

        std::string result = str;
        if (const size_t pos = result.find("{}"); pos != std::string::npos)
        {
            result.replace(pos, 2, oss.str());
        }
        return result;
    }

    // Função recursiva que substitui todos os placeholders "{}" pelos argumentos fornecidos
    template<typename T, typename... Args>
    std::string format(const std::string &str, const T &value, Args... args)
    {
        return format(format(str, value), args...);
    }

    // Implementação do printf caseiro
    template<typename... Args>
    void printf(const std::string &str, Args... args)
    {
        const std::string result = format(str, args...);
        std::cout << result << "\n";
    }

} // namespace util

namespace iron
{
    inline int typeOfRealNumber(const std::string &valor)
    {
        if (!valor.empty() && valor.back() == 'F')
        {
            return tokenMap::TYPE_FLOAT;
        }
        if (!valor.empty() && valor.back() == 'D')
        {
            return tokenMap::TYPE_DOUBLE;
        }
        return tokenMap::NO_REAL_NUMBER;
    }

    inline std::string createFunctionName(const std::string &currentScopeName, std::string functionName)
    {
        return util::format("gfn_{}_{}", currentScopeName, std::move(functionName));
    }
} // namespace iron

#endif // HLIR_UTILS_H

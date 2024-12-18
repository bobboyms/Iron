#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <string>

namespace iron {

    // Função auxiliar recursiva que substitui o primeiro placeholder "{}" pelo argumento atual
    template <typename T>
    std::string format(const std::string& str, T value) {
        std::ostringstream oss;
        oss << value;

        std::string result = str;
        size_t pos = result.find("{}");
        if (pos != std::string::npos) {
            result.replace(pos, 2, oss.str());
        }
        return result;
    }

    // Função recursiva que substitui todos os placeholders "{}" pelos argumentos fornecidos
    template <typename T, typename... Args>
    std::string format(const std::string& str, T value, Args... args) {
        return format(format(str, value), args...);
    }

    // Implementação do printf caseiro
    template <typename... Args>
    void printf(const std::string& str, Args... args) {
        std::string result = format(str, args...);
        std::cout << result << "\n";
    }

} // namespace iron

#endif // UTILS_H

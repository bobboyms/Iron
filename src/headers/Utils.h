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

    std::optional<std::pair<std::string, int>> getArgumentByName(const SymbolInfo& info, const std::string& argName)
    {
        for (const auto& arg : info.args) {
            if (arg.first == argName) {
                return arg;
            }
        }
        return std::nullopt;
    }

    int typeOfRealNumber(const std::string valor) {
        if (!valor.empty() && valor.back() == 'F') {
            return TokenMap::TYPE_FLOAT;
        } else 
        if (!valor.empty() && valor.back() == 'D') {
            return TokenMap::TYPE_DOUBLE;
        }
        return TokenMap::NO_REAL_NUMBER;
    }

    #include <string>

    // Função para obter todo o texto após o primeiro "_"
    std::string getTextAfterUnderscore(const std::string& input) {
        // Encontra a posição do primeiro "_"
        size_t pos = input.find('_');
        
        // Verifica se "_" foi encontrado
        if (pos != std::string::npos && pos + 1 < input.length()) {
            // Retorna a substring após o "_"
            return input.substr(pos + 1);
        }
        
        // Retorna string vazia se "_" não for encontrado ou não houver texto após "_"
        return input;
    }


} // namespace iron

#endif // UTILS_H

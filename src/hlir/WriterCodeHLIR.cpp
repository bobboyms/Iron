// WriterCodeHLIR.cpp
#include "../headers/WriterCodeHLIR.h"
#include <stdexcept>

namespace iron
{

    Writer *WriterCodeHLIR::enterScope(const std::string &scopeName)
    {
        auto it = writerMap.find(scopeName);
        if (it != writerMap.end())
        {
            throw std::runtime_error("Scope '" + scopeName + "' already exists in Writers map.");
        }

        Writer newWriter{scopeName, std::make_shared<std::stringstream>()};
        // Insere no map e retorna ponteiro
        auto [insertIt, _] = writerMap.emplace(scopeName, newWriter);
        return &insertIt->second;
    }

    Writer *WriterCodeHLIR::getWriter(const std::string &scopeName)
    {
        auto it = writerMap.find(scopeName);
        if (it != writerMap.end())
        {
            return &it->second;
        }
        // Se não existe, cria um novo escopo
        return enterScope(scopeName);
    }

    void WriterCodeHLIR::exitScope(const std::string &scopeName)
    {
        auto it = writerMap.find(scopeName);
        if (it == writerMap.end())
        {
            throw std::runtime_error("Attempted to exit a non-existent scope: '" + scopeName + "'.");
        }
        writerMap.erase(it);
    }

    std::string WriterCodeHLIR::getCode()
    {
        std::stringstream sb;
        for (const auto &[scope, writer] : writerMap)
        {
            sb << writer.localSb->str();
        }
        return sb.str();
    }

} // namespace iron
/**
 * @file WriterCodeHLIR.cpp
 * @brief Implementation of the WriterCodeHLIR class for scope-based code generation
 */
#include "../../headers/WriterCodeHLIR.h"
#include <stdexcept>

namespace iron
{
    /**
     * @brief Create and enter a new scope for code generation
     * 
     * @param scopeName Unique name for the scope
     * @return Writer* Pointer to the new Writer object
     * @throws std::runtime_error If a scope with the same name already exists
     */
    Writer *WriterCodeHLIR::enterScope(const std::string &scopeName)
    {
        // Check for existing scope with the same name
        auto it = writerMap.find(scopeName);
        if (it != writerMap.end())
        {
            throw std::runtime_error("Scope '" + scopeName + "' already exists in Writers map.");
        }

        // Create a new writer with its own string stream
        Writer newWriter{scopeName, std::make_shared<std::stringstream>()};
        
        // Insert into map and return pointer to the inserted Writer
        auto [insertIt, _] = writerMap.emplace(scopeName, newWriter);
        return &insertIt->second;
    }

    /**
     * @brief Get an existing writer or create a new one if it doesn't exist
     * 
     * @param scopeName Name of the scope to find or create
     * @return Writer* Pointer to the Writer object
     */
    Writer *WriterCodeHLIR::getWriter(const std::string &scopeName)
    {
        auto it = writerMap.find(scopeName);
        if (it != writerMap.end())
        {
            return &it->second;
        }
        // If it doesn't exist, create a new scope
        return enterScope(scopeName);
    }

    /**
     * @brief Exit and remove a scope
     * 
     * @param scopeName Name of the scope to exit
     * @throws std::runtime_error If the scope doesn't exist
     */
    void WriterCodeHLIR::exitScope(const std::string &scopeName)
    {
        auto it = writerMap.find(scopeName);
        if (it == writerMap.end())
        {
            throw std::runtime_error("Attempted to exit a non-existent scope: '" + scopeName + "'.");
        }
        writerMap.erase(it);
    }

    /**
     * @brief Get all generated code from all scopes
     * 
     * @return std::string The combined code from all scopes
     */
    std::string WriterCodeHLIR::getCode()
    {
        std::stringstream result;
        for (const auto &[scope, writer]: writerMap)
        {
            result << writer.localSb->str();
        }
        return result.str();
    }

} // namespace iron

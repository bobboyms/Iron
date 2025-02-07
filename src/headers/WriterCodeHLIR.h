// WriterCodeHLIR.h
#ifndef WRITER_CODE_HLIR_H
#define WRITER_CODE_HLIR_H

#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

namespace iron
{

    struct Writer
    {
        std::string key;
        std::shared_ptr<std::stringstream> localSb;
    };

    class WriterCodeHLIR
    {
    private:
        // Mapeia o nome do escopo (‘string’) para o Writer correspondente
        std::unordered_map<std::string, Writer> writerMap;

    public:
        Writer *enterScope(const std::string &scopeName);
        Writer *getWriter(const std::string &scopeName);
        void exitScope(const std::string &scopeName);
        std::string getCode();
    };

} // namespace iron

#endif // WRITER_CODE_HLIR_H

#ifndef HLIR_EXCEPTION_H
#define HLIR_EXCEPTION_H

#include <exception>
#include <string>

namespace hlir
{
    class HLIRException : public std::exception
    {
    private:
        std::string message; // Mensagem de erro

    public:
        explicit HLIRException(const std::string &msg) : message(msg) {}

        // Retorna a mensagem de erro
        const char *what() const noexcept override
        {
            return message.c_str();
        }
    };

    class TokenException : public std::exception
    {
    private:
        std::string message; // Mensagem de erro

    public:
        explicit TokenException(const std::string &msg) : message(msg) {}

        // Retorna a mensagem de erro
        const char *what() const noexcept override
        {
            return message.c_str();
        }
    };

    class TokenNotFoundException : public TokenException
    {
    public:
        explicit TokenNotFoundException(const std::string &message)
            : TokenException(message) {}
    };
} // namespace hlir

#endif
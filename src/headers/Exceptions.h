#ifndef SEMANTIC_EXCEPTION_H
#define SEMANTIC_EXCEPTION_H

#include <exception>
#include <string>
namespace hlir
{
    class HLIRException final : public std::exception
    {
    private:
        std::string message;

    public:
        explicit HLIRException(std::string msg) : message(std::move(msg))
        {
        }

        [[nodiscard]] const char *what() const noexcept override
        {
            return message.c_str();
        }
    };

}

namespace iron
{
    class LLVMException final : public std::exception
    {
    private:
        std::string message;

    public:
        explicit LLVMException(std::string msg) : message(std::move(msg))
        {
        }

        // Retorna a mensagem de erro
        [[nodiscard]] const char *what() const noexcept override
        {
            return message.c_str();
        }
    };

    class SemanticException : public std::exception
    {
    private:
        std::string message; // Mensagem de erro

    public:
        explicit SemanticException(std::string msg) : message(std::move(msg))
        {
        }

        // Retorna a mensagem de erro
        [[nodiscard]] const char *what() const noexcept override
        {
            return message.c_str();
        }
    };

    // class ModuleNotFoundException final : public std::exception
    // {
    // private:
    //     std::string message;
    //
    // public:
    //     explicit ModuleNotFoundException(std::string msg) : message(std::move(msg))
    //     {
    //     }
    //
    //     [[nodiscard]] const char *what() const noexcept override
    //     {
    //         return message.c_str();
    //     }
    // };

    class ModuleNotFoundException final : public SemanticException
    {
    public:
        explicit ModuleNotFoundException(const std::string &message) : SemanticException(message)
        {
        }
    };

    class SignatureMismatchException final : public SemanticException
    {
    public:
        explicit SignatureMismatchException(const std::string &message) : SemanticException(message)
        {
        }
    };


    class ModuleRedefinitionException final : public SemanticException
    {
    public:
        explicit ModuleRedefinitionException(const std::string &message) : SemanticException(message)
        {
        }
    };



    class ArgumentOrderMismatchException final : public SemanticException
    {
    public:
        explicit ArgumentOrderMismatchException(const std::string &message) : SemanticException(message)
        {
        }
    };

    class ReturnNotFoundException final : public SemanticException
    {
    public:
        explicit ReturnNotFoundException(const std::string &message) : SemanticException(message)
        {
        }
    };

    class UnrecognizedIdentifierException final : public SemanticException
    {
    public:
        explicit UnrecognizedIdentifierException(const std::string &message) : SemanticException(message)
        {
        }
    };



    class ArgumentCountMismatchException final : public SemanticException
    {
    public:
        explicit ArgumentCountMismatchException(const std::string &message) : SemanticException(message)
        {
        }
    };

    class UninitializedVariableException final : public SemanticException
    {
    public:
        explicit UninitializedVariableException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class VariableRedefinitionException final : public SemanticException
    {
    public:
        explicit VariableRedefinitionException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class FunctionRedefinitionException final : public SemanticException
    {
    public:
        explicit FunctionRedefinitionException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class VariableNotFoundException final : public SemanticException
    {
    public:
        explicit VariableNotFoundException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class ScopeNotFoundException final : public SemanticException
    {
    public:
        explicit ScopeNotFoundException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class TypeMismatchException final : public SemanticException
    {
    public:
        explicit TypeMismatchException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class FunctionNotFoundException final : public SemanticException
    {
    public:
        explicit FunctionNotFoundException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class FunctionArgNotFoundException final : public SemanticException
    {
    public:
        explicit FunctionArgNotFoundException(const std::string &msg) : SemanticException(msg)
        {
        }
    };

    class LexusNotFoundException final : public std::exception
    {
    private:
        std::string message; // Mensagem de erro

    public:
        explicit LexusNotFoundException(std::string msg) : message(std::move(msg))
        {
        }

        // Retorna a mensagem de erro
        [[nodiscard]] const char *what() const noexcept override
        {
            return message.c_str();
        }
    };
} // namespace iron

namespace tokenMap
{
    class TokenException : public std::exception
    {
    private:
        std::string message; // Mensagem de erro

    public:
        explicit TokenException(const std::string &msg) : message(msg)
        {
        }

        // Retorna a mensagem de erro
        [[nodiscard]] const char *what() const noexcept override
        {
            return message.c_str();
        }
    };

    class TokenNotFoundException final : public TokenException
    {
    public:
        explicit TokenNotFoundException(const std::string &message) : TokenException(message)
        {
        }
    };
} // namespace tokenMap

#endif // SEMANTIC_EXCEPTION_H

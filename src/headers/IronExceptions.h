#ifndef SEMANTIC_EXCEPTION_H
#define SEMANTIC_EXCEPTION_H

#include <exception>
#include <string>

class LLVMException : public std::exception
{
private:
    std::string message; // Mensagem de erro

public:
    explicit LLVMException(const std::string &msg) : message(msg) {}

    // Retorna a mensagem de erro
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

class SemanticException : public std::exception
{
private:
    std::string message; // Mensagem de erro

public:
    explicit SemanticException(const std::string &msg) : message(msg) {}

    // Retorna a mensagem de erro
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

class ArgumentOrderMismatchException : public SemanticException
{
public:
    explicit ArgumentOrderMismatchException(const std::string &message)
        : SemanticException(message) {}
};

class ArgumentCountMismatchException : public SemanticException
{
public:
    explicit ArgumentCountMismatchException(const std::string &message)
        : SemanticException(message) {}
};

class UninitializedVariableException : public SemanticException
{
public:
    explicit UninitializedVariableException(const std::string &msg)
        : SemanticException(msg) {}
};

class VariableRedefinitionException : public SemanticException
{
public:
    explicit VariableRedefinitionException(const std::string &msg)
        : SemanticException(msg) {}
};

class FunctionRedefinitionException : public SemanticException
{
public:
    explicit FunctionRedefinitionException(const std::string &msg)
        : SemanticException(msg) {}
};

class VariableNotFoundException : public SemanticException
{
public:
    explicit VariableNotFoundException(const std::string &msg)
        : SemanticException(msg) {}
};

class ScopeNotFoundException : public SemanticException
{
public:
    explicit ScopeNotFoundException(const std::string &msg)
        : SemanticException(msg) {}
};

class TypeMismatchException : public SemanticException
{
public:
    explicit TypeMismatchException(const std::string &msg)
        : SemanticException(msg) {}
};

class FunctionNotFoundException : public SemanticException
{
public:
    explicit FunctionNotFoundException(const std::string &msg)
        : SemanticException(msg) {}
};

class FunctionArgNotFoundException : public SemanticException
{
public:
    explicit FunctionArgNotFoundException(const std::string &msg)
        : SemanticException(msg) {}
};

class LexusNotFoundException : public std::exception
{
private:
    std::string message; // Mensagem de erro

public:
    explicit LexusNotFoundException(const std::string &msg) : message(msg) {}

    // Retorna a mensagem de erro
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

#endif // SEMANTIC_EXCEPTION_H

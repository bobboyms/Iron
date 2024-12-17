#ifndef SEMANTIC_EXCEPTION_H
#define SEMANTIC_EXCEPTION_H

#include <exception>
#include <string>

class SemanticException : public std::exception {
private:
    std::string message; // Mensagem de erro

public:
    explicit SemanticException(const std::string& msg) : message(msg) {}

    // Retorna a mensagem de erro
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class VariableRedefinitionException : public SemanticException {
public:
    explicit VariableRedefinitionException(const std::string& msg)
        : SemanticException(msg) {}
};

class FunctionRedefinitionException : public SemanticException {
public:
    explicit FunctionRedefinitionException(const std::string& msg)
        : SemanticException(msg) {}
};

#endif // SEMANTIC_EXCEPTION_H

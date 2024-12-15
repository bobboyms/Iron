#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory> // Para std::unique_ptr
#include <antlr4-runtime.h>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"

// Listener personalizado para capturar mensagens de erro
class SyntaxErrorListener : public antlr4::BaseErrorListener {
public:
    std::vector<std::string> errors;

    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                     size_t line, size_t charPositionInLine, const std::string &msg,
                     std::exception_ptr e) override {
        std::ostringstream errorMessage;
        errorMessage << "Erro de sintaxe na linha " << line
                     << ", coluna " << charPositionInLine
                     << ": " << msg;
        if (offendingSymbol) {
            errorMessage << " (token: '" << offendingSymbol->getText() << "')";
        }
        errors.push_back(errorMessage.str());
    }
};

// Função para criar o parser
std::unique_ptr<IronParser> createParser(const std::string &input, SyntaxErrorListener &errorListener) {
    // Cria objetos no stack
    auto inputStream = std::make_unique<antlr4::ANTLRInputStream>(input);
    auto lexer = std::make_unique<IronLexer>(inputStream.get());
    auto tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
    auto parser = std::make_unique<IronParser>(tokens.get());

    // Configura o listener de erros
    parser->removeErrorListeners();
    parser->addErrorListener(&errorListener);

    return parser; // Retorna o parser como um unique_ptr
}

void debugTokens(IronLexer &lexer) {
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << "Token: " << token->getText()
                  << " Tipo: " << token->getType() << std::endl;
    }
}

#include <antlr4-runtime.h>
#include "parsers/IronLexer.h"

#include <iostream>
#include <antlr4-runtime.h>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"

#include <iostream>
#include <antlr4-runtime.h>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"

int main() {
    std::string input = "let x: int\n"; // Entrada inválida
    antlr4::ANTLRInputStream inputStream(input);
    IronLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    IronParser parser(&tokens);

    // Processa o programa
    parser.program();

    // Número de erros de sintaxe
    int syntaxErrors = parser.getNumberOfSyntaxErrors();
    std::cout  << syntaxErrors << std::endl;

    return 0;
}




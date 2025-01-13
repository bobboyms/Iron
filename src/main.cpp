#include <iostream>
#include <memory>
#include "parsers/IronLexer.h"
#include "parsers/IronParser.h"
#include "headers/SemanticalAnalysis.h"
#include "headers/HighLevelIR.h"
#include "headers/LLVMIR.h"
#include "headers/Colors.h"
#include "headers/Hlir.h"

int runAnalysis(const std::string &input)
{
    try
    {
        auto emptyArgs = std::make_shared<hlir::FunctionArgs>();
        // Create an int Type
        auto returnInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

        // Instantiate the Function
        hlir::Function func("foo", emptyArgs, returnInt);

        // Expect "fn foo():int"
        runAnalysis(func.getText(), "fn foo():int");

        // Inicializa os componentes do ANTLR
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticalAnalysis analysis(parser, std::move(std::make_unique<iron::ScopeManager>()));
        // analysis.analyze();

        // Rewind
        tokens.seek(0);
        parser->reset();

        iron::HighLevelIR hightLevelCodeGenerator(parser, std::move(std::make_unique<iron::ScopeManager>()));
        // const auto hlirCode = hightLevelCodeGenerator.generateCode();

        // std::cout << hlirCode << std::endl;

        // iron::LLVMIR llvmir(hlirCode, std::move(std::make_unique<iron::ScopeManager>()));
        //  std::cout << llvmir.generateCode() << std::endl;

        // std::cout << "Análise semântica concluída com sucesso." << std::endl;
        return 0; // Sucesso
    }
    catch (const iron::SemanticException &e)
    {
        std::cerr << color::colorText("Semantic error: ", color::RED) << e.what() << std::endl;
        return 1; // Erro semântico específico
    }
    catch (const iron::LLVMException e)
    {
        std::cerr << color::colorText("LLVM error: ", color::RED) << e.what() << std::endl;
        return 1; // Erro semântico específico
    }
    catch (const std::exception &e)
    {
        std::cerr << color::colorText("Unexpected error: ", color::RED) << e.what() << std::endl;
        return 2; // Outros erros padrão
    }
    catch (...)
    {
        std::cerr << color::colorText("I panicked, I need a psychoanalyst: ", color::BOLD_RED) << std::endl;
        return 3; // Exceções não esperadas
    }
}

int main()
{
    std::string input = R"(
        
        public fn sub(a:int, b:int) {
             a * 2 + b
        }

        public fn main() {
            // let x: int = 22
            sub(a:2, b:2)
        }
    )";

    return runAnalysis(input);
}

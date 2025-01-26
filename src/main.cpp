#include <iostream>
#include <memory>
#include "headers/SemanticalAnalysis.h"
#include "headers/Hlir.h"
#include "headers/LLVMIR.h"
#include "headers/HLIRGenerator.h"
#include "parsers/IronLexer.h"
#include <antlr4-runtime.h>

int runAnalysis(const std::string &input)
{
    try
    {

        // Inicializa os componentes do ANTLR
        antlr4::ANTLRInputStream inputStream(input);
        IronLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        auto parser = std::make_shared<IronParser>(&tokens);

        // Executa a análise semântica
        iron::SemanticalAnalysis analysis(parser, std::move(std::make_unique<iron::ScopeManager>()));
        analysis.analyze();

        // Rewind
        tokens.seek(0);
        parser->reset();

        auto context = std::make_shared<hlir::Context>();
        hlir::HLIRGenerator hightLevelCodeGenerator(parser, context);
        const auto hlirCode = hightLevelCodeGenerator.generateCode();
        std::cout << hlirCode << std::endl;

        iron::LLVM llvm(context);
        auto llvmCode = llvm.generateCode();
        std::cout << llvmCode << std::endl;

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
    catch (const hlir::HLIRException e)
    {
        std::cerr << color::colorText("HLIRE error: ", color::RED) << e.what() << std::endl;
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
        

        fn mult(n:int, p:float): float {}

        fn sub(ax:int, bx:float): int {}

        fn soma(): int {
            let x: float = 25.00
            
            let block:fn = (a:int):int -> {
            }

            let inline:fn = (a:int):float -> a * x
            32.25 * sub(ax: 1, bx: mult(n:22, p:inline(a:block(a:25))))
        }
        

    )";

    return runAnalysis(input);
}

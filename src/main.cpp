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
        

        fn sub(n:int, j:int): int {   
        }

        fn main(): int {
            let x:int = 25
            let p:float = 12.14

            let block:fn = (a:int,b:int):int -> {
                let n:int = sub(n:a, j:x) * sub(n:5, j:9)
                let block:fn = (a:int,b:int):int -> {
                    let g:float = sub(n:n, j:x) * sub(n:5, j:9) * x
                    let block:fn = (a:float,b:int):int -> {
                        let block:fn = (a:float,b:int, c:float):int -> {
                            c * a / b
                        }
                        block(a:10.00, b:20, c:30.00) * p
                    }

                    let r:int = block(a:g, b:20) * n
                }

                let v:int = block(a:a, b:20) * n
            }

            block(a:10, b:20)

            
        }

        

    )";

    return runAnalysis(input);
}

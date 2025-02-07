#include <iostream>
#include <memory>
#include "scope/ScopeManager.h"

int main()
{
    // Cria um gerenciador de escopos
    scope::ScopeManager scopeManager;

    // ============================
    // 1) Criar um escopo global
    // ============================
    // Podemos usar a própria classe GlobalScope ou criar uma classe derivada se quisermos mais funcionalidades.
    // Aqui, para ficar mais simples, criaremos uma instância de GlobalScope e ajustaremos alguns valores.
    auto global = std::make_shared<scope::GlobalScope>();

    // Para ilustrar, usaremos cast 'GlobalScope*' para acessar variáveis 'protected'.
    // Por padrão, no seu .h, 'name' e 'type' são protected. Se quiser setar de fora,
    // considere criar métodos 'setName', 'setType' etc. Aqui, exemplificamos de forma simples:
    {
        // Acesse name e type diretamente (apenas para DEMO, já que estão protected):
        // global->name = "Global"; // NÃO FUNCIONA diretamente pois 'name' é protected.
        // global->type = 1;        // idem.

        // Uma maneira de contornar é criar métodos ou usar um construtor especializado.
        // Suponha que criemos as funções setName() e setType().
        // Vamos simular isso rapidamente (exemplo AD-HOC):

        // Exemplo de "ajuste" no escopo da classe (improvisado):
        // Você pode implementar de forma real no .h/.cpp:
        //   global->setName("GlobalScope");
        //   global->setType(1);

        // Entretanto, para demonstrar, vamos imaginar que o GlobalScope retorna
        // string vazia em getName() e 0 em getType() se não definirmos nada.
    }

    // Entramos nesse escopo global
    scopeManager.enterScope(global);

    std::cout << "Escopo atual após entrar no GlobalScope: " << scopeManager.currentScopeName() << "\n\n";

    // ============================
    // 2) Criar uma função
    // ============================
    // Digamos que nossa função tenha dois parâmetros.
    auto arg1 = std::make_shared<scope::FunctionCallArg>("x", 1); // type 1 (int, por ex.)
    auto arg2 = std::make_shared<scope::FunctionCallArg>("y", 1); // type 1 (int, por ex.)
    std::vector<std::shared_ptr<scope::FunctionCallArg>> funcArgs = {arg1, arg2};

    // Cria uma instância de Function (nome, args, returnType).
    auto myFunction = std::make_shared<scope::Function>("minhaFuncao", funcArgs, 1 /*int*/);

    // Entrar no escopo da função (a função é um tipo de GlobalScope, pois herda de GlobalScope).
    scopeManager.enterScope(myFunction);

    std::cout << "Escopo atual após entrar na funcao: " << scopeManager.currentScopeName() << "\n\n";

    // Podemos pesquisar esse escopo pelo nome:
    auto foundScope = scopeManager.getScopeByName("minhaFuncao");
    if (foundScope)
    {
        std::cout << "Escopo 'minhaFuncao' encontrado. Type = " << foundScope->getType() << "\n";
    }
    else
    {
        std::cout << "Escopo 'minhaFuncao' nao encontrado.\n";
    }

    // Verificar argumentos da função
    {

        // Fazemos cast para 'Function' para acessar métodos específicos
        auto funcPtr = std::dynamic_pointer_cast<scope::Function>(foundScope);
        if (funcPtr)
        {
            auto arg = funcPtr->getArgByName("x");
            if (arg)
            {
                std::cout << "Argumento 'x' encontrado. type = " << arg->type << "\n";
            }
            else
            {
                std::cout << "Argumento 'x' nao encontrado.\n";
            }
        }
    }
    std::cout << "\n";

    // ============================
    // 3) Criar um escopo local
    // ============================
    // Dentro da função, podemos ter escopos locais diferentes.
    // Exemplo: blocos internos, laços, etc.
    // Vamos criar um escopo local de 'Variables' (que herda de LocalScope).
    auto localVars = std::make_shared<scope::Variables>();
    // (Aqui também temos o mesmo "problema" de name e type serem protected.)
    // Adicionamos variáveis:
    localVars->addVariable("contador", 1); // int
    localVars->addVariable("nome", 2); // 2 = string, etc.

    // Entramos nesse novo escopo (ainda dentro da função).
    // Aqui não estamos usando scopeManager para gerenciar LocalScopes, mas poderíamos,
    // desde que ajustássemos a lógica. Vamos simular com a própria classe Function.
    auto funcPtr = std::dynamic_pointer_cast<scope::Function>(scopeManager.currentScope());
    if (funcPtr)
    {
        funcPtr->enterLocalScope(localVars);
    }

    // std::cout << "Escopo atual após entrar no LocalScope: "
    //           << scopeManager.currentScopeName() << "\n";

    // Vamos checar a variável "contador"
    auto currentLocal = funcPtr->getCurrentLocalScope();
    if (currentLocal)
    {
        // Como getCurrentLocalScope() retorna um LocalScope, precisamos de cast para Variables.
        auto varScope = std::dynamic_pointer_cast<scope::Variables>(currentLocal);
        if (varScope)
        {
            auto var = varScope->getVariable("contador");
            if (var)
            {
                std::cout << "Variavel 'contador' encontrada. type = " << var->type << "\n";
            }
        }
    }

    // ============================
    // 4) Sair dos escopos
    // ============================
    // Sair do escopo local
    if (funcPtr)
    {
        funcPtr->exitLocalScope();
    }

    // Sair do escopo da função
    scopeManager.exitScope();
    std::cout << "\nEscopo atual após sair da funcao: " << scopeManager.currentScopeName() << "\n";

    // Finalmente, sair do escopo global
    scopeManager.exitScope();
    std::cout << "Escopo atual apos sair do GlobalScope: " << scopeManager.currentScopeName() << "\n";

    return 0;
}

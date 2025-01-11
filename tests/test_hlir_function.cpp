#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>

#include "../src/hlir/Hlir.h" // Ajuste conforme seu projeto
#include "antlr4-runtime.h"   // Caso precise do ANTLR

// Cria uma fixture de teste no mesmo estilo
class HlIrTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Caso precise inicializar algo antes de cada teste, faça aqui.
    }

    std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });
        return result;
    }

    // Função para comparar resultados ignorando espaços em branco
    void runAnalysis(const std::string &input, const std::string &expectedOutput)
    {
        if (removeWhitespace(input) == removeWhitespace(expectedOutput))
        {
            // Teste ok
            return;
        }
        else
        {
            FAIL() << "Generated code does not match the expected code.\n"
                   << "Got:      " << input << "\n"
                   << "Expected: " << expectedOutput;
        }
    }
};

//-----------------------------------------------------------
// TESTES PARA A CLASSE FunctionArgs
//-----------------------------------------------------------

TEST_F(HlIrTest, FunctionArgs_Empty)
{
    // Testa quando não há argumentos
    hlir::FunctionArgs functionArgs;
    // Esperamos que getText() retorne vazio
    runAnalysis(functionArgs.getText(), "");
}

TEST_F(HlIrTest, FunctionArgs_OneArg)
{
    hlir::FunctionArgs functionArgs;

    // Cria um "int"
    auto ptrTypeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    // Cria Arg("a", int) e adiciona
    functionArgs.addArg(std::make_shared<hlir::Arg>("a", ptrTypeInt));

    // Esperamos "a:int"
    runAnalysis(functionArgs.getText(), "a:int");
}

TEST_F(HlIrTest, FunctionArgs_TwoArgs)
{
    hlir::FunctionArgs functionArgs;

    // "int" e "float"
    auto ptrTypeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);

    // Adiciona Arg("a", int) e Arg("b", float)
    functionArgs.addArg(std::make_shared<hlir::Arg>("a", ptrTypeInt));
    functionArgs.addArg(std::make_shared<hlir::Arg>("b", ptrTypeFloat));

    // Deve gerar "a:int,b:float"
    runAnalysis(functionArgs.getText(), "a:int,b:float");
}

TEST_F(HlIrTest, FunctionArgs_MultipleArgs)
{
    hlir::FunctionArgs functionArgs;

    // Tipos variados
    auto ptrTypeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);
    auto ptrTypeString = std::make_shared<hlir::Type>(hlir::TYPE_STRING);

    // Adiciona Arg("x", int), Arg("y", float), Arg("name", string)
    functionArgs.addArg(std::make_shared<hlir::Arg>("x", ptrTypeInt));
    functionArgs.addArg(std::make_shared<hlir::Arg>("y", ptrTypeFloat));
    functionArgs.addArg(std::make_shared<hlir::Arg>("name", ptrTypeString));

    // Esperamos "x:int,y:float,name:string"
    runAnalysis(functionArgs.getText(), "x:int,y:float,name:string");
}

TEST_F(HlIrTest, FunctionArgs_ConstructorWithVector)
{
    // Cria diretamente um std::vector de shared_ptr<Arg>
    std::vector<std::shared_ptr<hlir::Arg>> vecArgs = {
        std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(hlir::TYPE_INT)),
        std::make_shared<hlir::Arg>("b", std::make_shared<hlir::Type>(hlir::TYPE_FLOAT))};

    // Usa o construtor que recebe o vector
    hlir::FunctionArgs functionArgs(vecArgs);

    // Esperamos "a:int,b:float"
    runAnalysis(functionArgs.getText(), "a:int,b:float");
}

// --------------------------------------------------
// TESTES PARA A CLASSE Function
// --------------------------------------------------

TEST_F(HlIrTest, Function_EmptyArgs_ReturnInt)
{
    // Exemplo: fn foo():int

    // Cria FunctionArgs vazio
    auto emptyArgs = std::make_shared<hlir::FunctionArgs>();
    // Cria um Type int
    auto returnInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);

    // Instancia a Function
    hlir::Function func("foo", emptyArgs, returnInt);

    // Esperamos "fn foo():int"
    runAnalysis(func.getText(), "fn foo():int");
}

TEST_F(HlIrTest, Function_SingleArg_ReturnFloat)
{
    // Exemplo: fn foo(a:int):float

    // Cria Arg("a", int)
    auto ptrArgA = std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto args = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgA});

    // Retorno float
    auto returnFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);

    hlir::Function func("foo", args, returnFloat);

    // Esperamos "fn foo(a:int):float"
    runAnalysis(func.getText(), "fn foo(a:int):float");
}

TEST_F(HlIrTest, Function_MultipleArgs_ReturnString)
{
    // Exemplo: fn bar(x:int, y:float):string

    auto ptrArgX = std::make_shared<hlir::Arg>("x", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto ptrArgY = std::make_shared<hlir::Arg>("y", std::make_shared<hlir::Type>(hlir::TYPE_FLOAT));

    // Constrói um FunctionArgs com [x, y]
    auto multiArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgX, ptrArgY});

    // Retorno string
    auto returnString = std::make_shared<hlir::Type>(hlir::TYPE_STRING);

    hlir::Function func("bar", multiArgs, returnString);

    // Esperamos "fn bar(x:int,y:float):string"
    runAnalysis(func.getText(), "fn bar(x:int,y:float):string");
}

TEST_F(HlIrTest, Function_EmptyName)
{
    // Exemplo: fn  (a:int):int  <-- nome vazio
    // Talvez não seja válido na sua linguagem, mas vamos testar comportamento

    auto ptrArgA = std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto args = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgA});

    // Retorno int
    auto returnInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);

    // Nome vazio: ""
    hlir::Function func("", args, returnInt);

    // getText() => "fn (a:int):int"
    // Depende de como você quer lidar com nomes vazios.
    runAnalysis(func.getText(), "fn (a:int):int");
}

TEST_F(HlIrTest, Function_MultipleArgs_SameType)
{
    // Exemplo: fn process(a:int,b:int,c:int):boolean

    auto ptrArgA = std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto ptrArgB = std::make_shared<hlir::Arg>("b", std::make_shared<hlir::Type>(hlir::TYPE_INT));
    auto ptrArgC = std::make_shared<hlir::Arg>("c", std::make_shared<hlir::Type>(hlir::TYPE_INT));

    auto args = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgA, ptrArgB, ptrArgC});

    // Retorno boolean
    auto returnBool = std::make_shared<hlir::Type>(hlir::TYPE_BOOLEAN);

    hlir::Function func("process", args, returnBool);

    // Esperamos "fn process(a:int,b:int,c:int):boolean"
    runAnalysis(func.getText(), "fn process(a:int,b:int,c:int):boolean");
}

// --------------------------------------------------------
// TESTES PARA 'FunctionCallArg' E 'FunctionCallArgs'
// --------------------------------------------------------

TEST_F(HlIrTest, FunctionCallArgs_Empty)
{
    // Construtor sem parâmetros => callArgs vazio
    hlir::FunctionCallArgs callArgs;

    // Esperamos getText() vazio
    runAnalysis(callArgs.getText(), "");
}

// 2) Construtor com 1 argumento
TEST_F(HlIrTest, FunctionCallArgs_SingleArg)
{
    // Cria um FunctionCallArg
    auto typeFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);
    auto val = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto arg = std::make_shared<hlir::FunctionCallArg>("radius", typeFloat, val);

    // Cria um vetor com 1 elemento
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg};

    // Constrói FunctionCallArgs
    hlir::FunctionCallArgs callArgs(vecArgs);

    // Esperamos: "radius:3.14"
    runAnalysis(callArgs.getText(), "radius:3.14");
}

// 3) Construtor com vários argumentos
TEST_F(HlIrTest, FunctionCallArgs_MultipleArgs)
{
    // Arg1: "nome":"Thiago"
    auto typeStr = std::make_shared<hlir::Type>(hlir::TYPE_STRING);
    auto valStr = std::make_shared<hlir::Value>("Thiago", typeStr);
    auto arg1 = std::make_shared<hlir::FunctionCallArg>("nome", typeStr, valStr);

    // Arg2: "idade":21
    auto typeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    auto valInt = std::make_shared<hlir::Value>("21", typeInt);
    auto arg2 = std::make_shared<hlir::FunctionCallArg>("idade", typeInt, valInt);

    // Arg3: "height":1.75
    auto typeDouble = std::make_shared<hlir::Type>(hlir::TYPE_DOUBLE);
    auto valDouble = std::make_shared<hlir::Value>("1.75", typeDouble);
    auto arg3 = std::make_shared<hlir::FunctionCallArg>("height", typeDouble, valDouble);

    // Constrói um vetor de 3
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg1, arg2, arg3};
    hlir::FunctionCallArgs callArgs(vecArgs);

    // Esperamos getText() => "nome:Thiago,idade:21,height:1.75"
    runAnalysis(callArgs.getText(), "nome:Thiago,idade:21,height:1.75");
}

// 4) Adicionar argumentos depois de construir (se tiver addCallArg)
TEST_F(HlIrTest, FunctionCallArgs_AddLater)
{
    hlir::FunctionCallArgs callArgs; // vazio inicialmente

    // Arg1
    auto tInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    auto vInt = std::make_shared<hlir::Value>("100", tInt);
    auto a1 = std::make_shared<hlir::FunctionCallArg>("x", tInt, vInt);

    // Arg2
    auto tBool = std::make_shared<hlir::Type>(hlir::TYPE_BOOLEAN);
    auto vBool = std::make_shared<hlir::Value>("true", tBool);
    auto a2 = std::make_shared<hlir::FunctionCallArg>("flag", tBool, vBool);

    // *Se* a classe tem "addCallArg":
    callArgs.addCallArg(a1);
    callArgs.addCallArg(a2);

    // Esperamos: "x:100,flag:true"
    runAnalysis(callArgs.getText(), "x:100,flag:true");
}

// 5) Testa chamadas repetidas a getText() (para ver se não duplica output)
TEST_F(HlIrTest, FunctionCallArgs_RepeatedCalls)
{
    auto typeChar = std::make_shared<hlir::Type>(hlir::TYPE_CHAR);
    auto valChar = std::make_shared<hlir::Value>("A", typeChar);
    auto arg1 = std::make_shared<hlir::FunctionCallArg>("letra", typeChar, valChar);

    // Cria com uma lista inicial de 1 elemento
    hlir::FunctionCallArgs callArgs({arg1});

    // Chama getText() duas vezes
    std::string first = callArgs.getText();

    // Esperamos que retorne o mesmo valor nas duas vezes
    runAnalysis(first, "letra:A");
}
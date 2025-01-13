#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>

#include "../src/headers/Hlir.h" // Adjust according to your project structure
#include "antlr4-runtime.h"      // Include if ANTLR is required

// Create a test fixture in the same style
class HlIrTestFunction : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialize anything before each test if necessary.
    }

    // Função para remover espaços em branco do início e do final
    static std::string trim(const std::string &str)
    {
        size_t first = 0;
        while (first < str.size() && std::isspace(static_cast<unsigned char>(str[first])))
        {
            ++first;
        }

        if (first == str.size())
        {
            return "";
        }

        size_t last = str.size() - 1;
        while (last > first && std::isspace(static_cast<unsigned char>(str[last])))
        {
            --last;
        }

        return str.substr(first, last - first + 1);
    }

    /**
     * @brief Removes all whitespace characters from a given string.
     * @param str The input string.
     * @return A new string without any whitespace characters.
     */
    // Função que remove todos os caracteres de espaço em branco
    // Função que remove todos os caracteres de espaço em branco após aplicar o trim
    static std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        result.reserve(str.size());

        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });

        return result;
    }

    /**
     * @brief Compares two strings for equality, ignoring any whitespace differences.
     * @param input The generated string from the test.
     * @param expectedOutput The expected string to compare against.
     *
     * If the strings match (ignoring whitespace), the test passes.
     * Otherwise, it fails and outputs the generated and expected strings.
     */
    void runAnalysis(const std::string &input, const std::string &expectedOutput)
    {
        const auto cleanInput = removeWhitespace(input);
        const auto cleanExpected = removeWhitespace(expectedOutput);
        if (cleanInput == cleanExpected)
        {
            // Test passed
            return;
        }
        else
        {
            FAIL() << "Generated code does not match the expected code.\n"
                   << "Got (cleaned):      " << cleanInput << "\n"
                   << "Expected (cleaned): " << cleanExpected << "\n";
        }
    }
};

//-----------------------------------------------------------
// TESTS FOR THE CLASS FunctionArgs
//-----------------------------------------------------------

TEST_F(HlIrTestFunction, FunctionArgs_Empty)
{
    // Test when there are no arguments
    hlir::FunctionArgs functionArgs;
    // Expect getText() to return an empty string
    runAnalysis(functionArgs.getText(), "");
}

TEST_F(HlIrTestFunction, FunctionArgs_OneArg)
{
    hlir::FunctionArgs functionArgs;

    // Create a "int" type
    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    // Create Arg("a", int) and add it
    functionArgs.addArg(std::make_shared<hlir::Arg>("a", ptrTypeInt));

    // Expect "a:int"
    runAnalysis(functionArgs.getText(), "a:int");
}

TEST_F(HlIrTestFunction, FunctionArgs_TwoArgs)
{
    hlir::FunctionArgs functionArgs;

    // Create "int" and "float" types
    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Add Arg("a", int) and Arg("b", float)
    functionArgs.addArg(std::make_shared<hlir::Arg>("a", ptrTypeInt));
    functionArgs.addArg(std::make_shared<hlir::Arg>("b", ptrTypeFloat));

    // Should generate "a:int,b:float"
    runAnalysis(functionArgs.getText(), "a:int,b:float");
}

TEST_F(HlIrTestFunction, FunctionArgs_MultipleArgs)
{
    hlir::FunctionArgs functionArgs;

    // Create varied types
    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto ptrTypeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Add Arg("x", int), Arg("y", float), Arg("name", string)
    functionArgs.addArg(std::make_shared<hlir::Arg>("x", ptrTypeInt));
    functionArgs.addArg(std::make_shared<hlir::Arg>("y", ptrTypeFloat));
    functionArgs.addArg(std::make_shared<hlir::Arg>("name", ptrTypeString));

    // Expect "x:int,y:float,name:string"
    runAnalysis(functionArgs.getText(), "x:int,y:float,name:string");
}

TEST_F(HlIrTestFunction, FunctionArgs_ConstructorWithVector)
{
    // Create a std::vector of shared_ptr<hlir::Arg>
    std::vector<std::shared_ptr<hlir::Arg>> vecArgs = {
        std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(tokenMap::TYPE_INT)),
        std::make_shared<hlir::Arg>("b", std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT))};

    // Use the constructor that takes the vector
    hlir::FunctionArgs functionArgs(vecArgs);

    // Expect "a:int,b:float"
    runAnalysis(functionArgs.getText(), "a:int,b:float");
}

// --------------------------------------------------
// TESTS FOR THE CLASS Function
// --------------------------------------------------

TEST_F(HlIrTestFunction, Function_EmptyArgs_ReturnInt)
{
    // Example: fn foo():int

    // Create empty FunctionArgs
    auto emptyArgs = std::make_shared<hlir::FunctionArgs>();
    // Create an int Type
    auto returnInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Instantiate the Function
    hlir::Function func("foo", emptyArgs, returnInt);

    // Expect "fn foo():int"
    runAnalysis(func.getText(), "fn foo():int { }");
}

TEST_F(HlIrTestFunction, Function_SingleArg_ReturnFloat)
{
    // Example: fn foo(a:int):float

    // Create Arg("a", int)
    auto ptrArgA = std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto args = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgA});

    // Return float
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    hlir::Function func("foo", args, returnFloat);

    // Expect "fn foo(a:int):float"
    runAnalysis(func.getText(), "fn foo(a:int):float { }");
}

TEST_F(HlIrTestFunction, Function_MultipleArgs_ReturnString)
{
    // Example: fn bar(x:int, y:float):string

    auto ptrArgX = std::make_shared<hlir::Arg>("x", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto ptrArgY = std::make_shared<hlir::Arg>("y", std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT));

    // Construct FunctionArgs with [x, y]
    auto multiArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgX, ptrArgY});

    // Return string
    auto returnString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    hlir::Function func("bar", multiArgs, returnString);

    // Expect "fn bar(x:int,y:float):string"
    runAnalysis(func.getText(), "fn bar(x:int,y:float):string { }");
}

TEST_F(HlIrTestFunction, Function_EmptyName)
{
    // Example: fn  (a:int):int  <-- empty name
    // This may not be valid in your language, but we'll test behavior

    auto ptrArgA = std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto args = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgA});

    // Return int
    auto returnInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Empty name: ""
    hlir::Function func("", args, returnInt);

    // getText() => "fn (a:int):int"
    // Depends on how you want to handle empty names.
    runAnalysis(func.getText(), "fn (a:int):int { }");
}

TEST_F(HlIrTestFunction, Function_MultipleArgs_SameType)
{
    // Example: fn process(a:int,b:int,c:int):boolean

    auto ptrArgA = std::make_shared<hlir::Arg>("a", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto ptrArgB = std::make_shared<hlir::Arg>("b", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto ptrArgC = std::make_shared<hlir::Arg>("c", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));

    auto args = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{ptrArgA, ptrArgB, ptrArgC});

    // Return boolean
    auto returnBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    hlir::Function func("process", args, returnBool);

    // Expect "fn process(a:int,b:int,c:int):boolean"
    runAnalysis(func.getText(), "fn process(a:int,b:int,c:int):boolean { }");
}

// --------------------------------------------------------
// TESTS FOR 'FunctionCallArg' AND 'FunctionCallArgs'
// --------------------------------------------------------

TEST_F(HlIrTestFunction, FunctionCallArgs_Empty)
{
    // Construct without parameters => empty callArgs
    hlir::FunctionCallArgs callArgs;

    // Expect getText() to return an empty string
    runAnalysis(callArgs.getText(), "");
}

// 2) Constructor with 1 argument
TEST_F(HlIrTestFunction, FunctionCallArgs_SingleArg)
{
    // Create a FunctionCallArg
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto val = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto arg = std::make_shared<hlir::FunctionCallArg>("radius", typeFloat, val);

    // Create a vector with 1 element
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg};

    // Construct FunctionCallArgs
    hlir::FunctionCallArgs callArgs(vecArgs);

    // Expect: "radius:3.14"
    runAnalysis(callArgs.getText(), "radius:3.14");
}

// 3) Constructor with multiple arguments
TEST_F(HlIrTestFunction, FunctionCallArgs_MultipleArgs)
{
    // Arg1: "nome":"Thiago"
    auto typeStr = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto valStr = std::make_shared<hlir::Value>("Thiago", typeStr);
    auto arg1 = std::make_shared<hlir::FunctionCallArg>("nome", typeStr, valStr);

    // Arg2: "idade":21
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto valInt = std::make_shared<hlir::Value>("21", typeInt);
    auto arg2 = std::make_shared<hlir::FunctionCallArg>("idade", typeInt, valInt);

    // Arg3: "height":1.75
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);
    auto valDouble = std::make_shared<hlir::Value>("1.75", typeDouble);
    auto arg3 = std::make_shared<hlir::FunctionCallArg>("height", typeDouble, valDouble);

    // Construct a vector of 3
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg1, arg2, arg3};
    hlir::FunctionCallArgs callArgs(vecArgs);

    // Expect getText() => "nome:Thiago,idade:21,height:1.75"
    runAnalysis(callArgs.getText(), "nome:Thiago,idade:21,height:1.75");
}

// 4) Add arguments after construction (if FunctionCallArgs has addCallArg)
TEST_F(HlIrTestFunction, FunctionCallArgs_AddLater)
{
    hlir::FunctionCallArgs callArgs; // initially empty

    // Arg1
    auto tInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto vInt = std::make_shared<hlir::Value>("100", tInt);
    auto a1 = std::make_shared<hlir::FunctionCallArg>("x", tInt, vInt);

    // Arg2
    auto tBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    auto vBool = std::make_shared<hlir::Value>("true", tBool);
    auto a2 = std::make_shared<hlir::FunctionCallArg>("flag", tBool, vBool);

    // *If* the class has "addCallArg":
    callArgs.addCallArg(a1);
    callArgs.addCallArg(a2);

    // Expect: "x:100,flag:true"
    runAnalysis(callArgs.getText(), "x:100,flag:true");
}

// 5) Test repeated calls to getText() (to ensure no duplication in output)
TEST_F(HlIrTestFunction, FunctionCallArgs_RepeatedCalls)
{
    auto typeChar = std::make_shared<hlir::Type>(tokenMap::TYPE_CHAR);
    auto valChar = std::make_shared<hlir::Value>("A", typeChar);
    auto arg1 = std::make_shared<hlir::FunctionCallArg>("letra", typeChar, valChar);

    // Create with an initial list of 1 element
    hlir::FunctionCallArgs callArgs({arg1});

    // Call getText() twice
    std::string first = callArgs.getText();
    std::string second = callArgs.getText();

    // Verify both texts are the same
    runAnalysis(first, "letra:A");
    runAnalysis(second, "letra:A");
}

// -------------------------------------------------------------------
// TESTS FOR THE CLASS "FunctionCall"
// -------------------------------------------------------------------

TEST_F(HlIrTestFunction, FunctionCall_SingleArg_IntReturn)
{
    // 1) Create an Arg "a:int"
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto argA = std::make_shared<hlir::Arg>("a", typeInt);

    // Put that arg into FunctionArgs
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argA});

    // Return type is int
    auto returnInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Create a Function "fn foo(a:int):int"
    auto func = std::make_shared<hlir::Function>("foo", funcArgs, returnInt);

    // 2) Create a FunctionCallArg "a" => "12"
    auto val12 = std::make_shared<hlir::Value>("12", typeInt);
    auto callArg = std::make_shared<hlir::FunctionCallArg>("a", typeInt, val12);

    // Put that callArg into FunctionCallArgs
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> callArgVec = {callArg};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(callArgVec);

    // 3) Create the FunctionCall: "call int foo(a:12)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Expect: "call int foo(a:12)"
    // Or whatever the actual format from getText() is: "call {returnType} {functionName}({argName:argValue})"
    runAnalysis(functionCall->getText(), "call int foo(a:12)");
}

TEST_F(HlIrTestFunction, FunctionCall_MultipleArgs_FloatReturn)
{
    // Function args: (x:int, y:float)
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Return type is float
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Create the Function "fn sum(x:int,y:float):float"
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat);

    // Now the call arguments: "x:10", "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);
    runAnalysis(functionCall->getText(), "call float sum(x:10,y:3.14)");
}

TEST_F(HlIrTestFunction, FunctionCall_NoArgs_VoidReturn)
{
    // If you have a TYPE_VOID or similar
    auto typeVoid = std::make_shared<hlir::Type>(tokenMap::VOID);

    // Function with no arguments
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    auto func = std::make_shared<hlir::Function>("doSomething", funcArgs, typeVoid);

    // The callArgs is also empty
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>();

    // "call void doSomething()"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);
    runAnalysis(functionCall->getText(), "call void doSomething()");
}

TEST_F(HlIrTestFunction, FunctionCall_BooleanReturn)
{
    // Return type is boolean
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    // Single param "flag:boolean"
    auto argFlag = std::make_shared<hlir::Arg>("flag", typeBool);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argFlag});

    auto func = std::make_shared<hlir::Function>("checkFlag", funcArgs, typeBool);

    // CallArg "flag:true"
    auto valTrue = std::make_shared<hlir::Value>("true", typeBool);
    auto callArgFlag = std::make_shared<hlir::FunctionCallArg>("flag", typeBool, valTrue);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgFlag});

    // "call boolean checkFlag(flag:true)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);
    runAnalysis(functionCall->getText(), "call boolean checkFlag(flag:true)");
}

TEST_F(HlIrTestFunction, FunctionCall_RepeatedCallsToGetText)
{
    // Return type double
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);
    // Args (n:int)
    auto argN = std::make_shared<hlir::Arg>("n", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argN});
    auto func = std::make_shared<hlir::Function>("sqrtCalc", funcArgs, typeDouble);

    // CallArg "n:25"
    auto val25 = std::make_shared<hlir::Value>("25", std::make_shared<hlir::Type>(tokenMap::TYPE_INT));
    auto callArgN = std::make_shared<hlir::FunctionCallArg>("n", std::make_shared<hlir::Type>(tokenMap::TYPE_INT), val25);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgN});

    // "call double sqrtCalc(n:25)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Check repeated calls
    std::string first = functionCall->getText();
    std::string second = functionCall->getText();

    // If your internal stringstream accumulates, second might differ
    // We expect them both to be the same
    runAnalysis(first, "call double sqrtCalc(n:25)");
    runAnalysis(second, "call double sqrtCalc(n:25)");
}
// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "hlir::Statement"
// ---------------------------------------------------------------------

// Teste para o construtor padrão
TEST_F(HlIrTestFunction, Statement_DefaultConstructor)
{
    hlir::Statement stmt;

    std::string text = stmt.getText();
    runAnalysis(text, "");
}

// Teste para o construtor com uma lista de ValidStatement
TEST_F(HlIrTestFunction, Statement_ConstructorWithList)
{
    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>(varRes, functionCall);

    // Criar a lista de ValidStatement
    std::vector<hlir::ValidStatement> stmtList = {expr1, functionCall, expr2};

    // Criar o Statement com a lista
    hlir::Statement stmt(stmtList);

    // Verificar a saída de getText()
    std::string expectedText = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    std::string actualText = stmt.getText();
    // EXPECT_EQ(actualText, expectedText);
    runAnalysis(actualText, expectedText);
}

// Teste para adicionar um ValidStatement usando addStatement
TEST_F(HlIrTestFunction, Statement_AddStatement)
{
    hlir::Statement stmt;

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>(varRes, functionCall);

    // Adicionar declarações ao Statement
    stmt.addStatement(expr1);
    stmt.addStatement(functionCall);
    stmt.addStatement(expr2);

    // Definir a string esperada sem quebra de linha inicial e sem indentação
    std::string expectedText = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    // Obter a saída real do getText()
    std::string actualText = stmt.getText();

    // Comparar diretamente as strings
    runAnalysis(actualText, expectedText);
}

// Teste para obter a lista de statements e verificar a saída de getText()
TEST_F(HlIrTestFunction, Statement_GetText_MultipleStatements)
{
    hlir::Statement stmt;

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>(varRes, functionCall);

    // Adicionar declarações ao Statement
    stmt.addStatement(expr1);
    stmt.addStatement(functionCall);
    stmt.addStatement(expr2);

    // Verificar a saída de getText()
    std::string expectedText = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    std::string actualText = stmt.getText();
    runAnalysis(actualText, expectedText);
}

// Teste para getText() com uma única Expr
TEST_F(HlIrTestFunction, Statement_GetText_SingleExpr)
{
    hlir::Statement stmt;

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>(varA, plusOp);

    // Adicionar apenas a expressão ao Statement
    stmt.addStatement(expr1);

    // Verificar a saída de getText()
    std::string expectedText = " let a:int = PLUS a, b\n";
    std::string actualText = stmt.getText();
    runAnalysis(actualText, expectedText);
}

// Teste para getText() com uma única FunctionCall
TEST_F(HlIrTestFunction, Statement_GetText_SingleFunctionCall)
{
    hlir::Statement stmt;

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>("x", typeInt);
    auto argY = std::make_shared<hlir::Arg>("y", typeFloat);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(
        std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>("10", typeInt);
    auto val3_14 = std::make_shared<hlir::Value>("3.14", typeFloat);
    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(
        std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Adicionar apenas a FunctionCall ao Statement
    stmt.addStatement(functionCall);

    // Verificar a saída de getText()
    std::string expectedText = " call float sum(x:10,y:3.14)\n";
    std::string actualText = stmt.getText();
    runAnalysis(actualText, expectedText);
}

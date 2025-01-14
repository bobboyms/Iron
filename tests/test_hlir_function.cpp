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
    auto functionArgs = std::make_shared<hlir::FunctionArgs>();
    // Expect getText() to return an empty string
    runAnalysis(functionArgs->getText(), "");
}

TEST_F(HlIrTestFunction, FunctionArgs_OneArg)
{
    // Cria um shared_ptr para FunctionArgs
    auto functionArgs = std::make_shared<hlir::FunctionArgs>();

    // Cria um "int" type
    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria Arg("a", int) e adiciona
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", ptrTypeInt);
    functionArgs->addArg(argA);

    // Espera "a:int"
    runAnalysis(functionArgs->getText(), "a:int");
}

TEST_F(HlIrTestFunction, FunctionArgs_TwoArgs)
{
    // Cria um shared_ptr para FunctionArgs
    auto functionArgs = std::make_shared<hlir::FunctionArgs>();

    // Create "int" and "float" types
    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Add Arg("a", int) and Arg("b", float)
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", ptrTypeInt);
    functionArgs->addArg(argA);

    auto argB = std::make_shared<hlir::Arg>();
    argB->set("b", ptrTypeFloat);
    functionArgs->addArg(argB);

    // Should generate "a:int,b:float"
    runAnalysis(functionArgs->getText(), "a:int,b:float");
}

TEST_F(HlIrTestFunction, FunctionArgs_MultipleArgs)
{
    // Cria um shared_ptr para FunctionArgs
    auto functionArgs = std::make_shared<hlir::FunctionArgs>();

    // Create varied types
    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto ptrTypeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Add Arg("x", int), Arg("y", float), Arg("name", string)
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", ptrTypeInt);
    functionArgs->addArg(argX);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", ptrTypeFloat);
    functionArgs->addArg(argY);

    auto argName = std::make_shared<hlir::Arg>();
    argName->set("name", ptrTypeString);
    functionArgs->addArg(argName);

    // Expect "x:int,y:float,name:string"
    runAnalysis(functionArgs->getText(), "x:int,y:float,name:string");
}

TEST_F(HlIrTestFunction, FunctionArgs_ConstructorWithVector)
{
    // Use the constructor that takes the vector

    auto ptrTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto ptrTypeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", ptrTypeInt);

    auto argB = std::make_shared<hlir::Arg>();
    argB->set("b", ptrTypeFloat);

    auto functionArgs = std::make_shared<hlir::FunctionArgs>();
    functionArgs->addArg(argA);
    functionArgs->addArg(argB);

    // Expect "a:int,b:float"
    runAnalysis(functionArgs->getText(), "a:int,b:float");
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
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", emptyArgs, returnInt);

    // Expect "fn foo():int { }"
    runAnalysis(func->getText(), "fn foo():int { }");
}

TEST_F(HlIrTestFunction, Function_SingleArg_ReturnFloat)
{
    // Example: fn foo(a:int):float

    // Create Arg("a", int)
    auto argA = std::make_shared<hlir::Arg>();
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    argA->set("a", typeInt);

    // Create FunctionArgs
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Return float
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Instantiate the Function
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", funcArgs, returnFloat);

    // Expect "fn foo(a:int):float { }"
    runAnalysis(func->getText(), "fn foo(a:int):float { }");
}

TEST_F(HlIrTestFunction, Function_MultipleArgs_ReturnString)
{
    // Example: fn bar(x:int, y:float):string

    auto argX = std::make_shared<hlir::Arg>();
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    argY->set("y", typeFloat);

    // Construct FunctionArgs with [x, y]
    auto multiArgs = std::make_shared<hlir::FunctionArgs>();
    multiArgs->addArg(argX);
    multiArgs->addArg(argY);

    // Return string
    auto returnString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Instantiate the Function
    auto func = std::make_shared<hlir::Function>();
    func->set("bar", multiArgs, returnString);

    // Expect "fn bar(x:int,y:float):string { }"
    runAnalysis(func->getText(), "fn bar(x:int,y:float):string { }");
}

TEST_F(HlIrTestFunction, Function_EmptyName)
{
    // Example: fn  (a:int):int  <-- empty name
    // This may not be valid in your language, but we'll test behavior

    auto argA = std::make_shared<hlir::Arg>();
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    argA->set("a", typeInt);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Return int
    auto returnInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Empty name: ""
    auto func = std::make_shared<hlir::Function>();
    func->set("", funcArgs, returnInt);

    // getText() => "fn (a:int):int { }"
    // Depends on how you want to handle empty names.
    runAnalysis(func->getText(), "fn (a:int):int { }");
}

TEST_F(HlIrTestFunction, Function_MultipleArgs_SameType)
{
    // Example: fn process(a:int,b:int,c:int):boolean

    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeBoolean = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);

    auto argB = std::make_shared<hlir::Arg>();
    argB->set("b", typeInt);

    auto argC = std::make_shared<hlir::Arg>();
    argC->set("c", typeInt);

    auto args = std::make_shared<hlir::FunctionArgs>();
    args->addArg(argA);
    args->addArg(argB);
    args->addArg(argC);

    // Return boolean
    auto returnBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    // Instantiate the Function
    auto func = std::make_shared<hlir::Function>();
    func->set("process", args, returnBool);

    // Expect "fn process(a:int,b:int,c:int):boolean { }"
    runAnalysis(func->getText(), "fn process(a:int,b:int,c:int):boolean { }");
}

// --------------------------------------------------------
// TESTS FOR 'FunctionCallArg' AND 'FunctionCallArgs'
// --------------------------------------------------------

TEST_F(HlIrTestFunction, FunctionCallArgs_Empty)
{
    // Construct without parameters => empty callArgs
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>();

    // Expect getText() to return an empty string
    runAnalysis(callArgs->getText(), "");
}

// 2) Constructor with 1 argument
TEST_F(HlIrTestFunction, FunctionCallArgs_SingleArg)
{
    // Create a FunctionCallArg
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto val = std::make_shared<hlir::Value>();
    val->set("3.14", typeFloat);
    auto arg = std::make_shared<hlir::FunctionCallArg>("radius", typeFloat, val);

    // Create a vector with 1 element
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg};

    // Construct FunctionCallArgs
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(vecArgs);

    // Expect: "radius:3.14"
    runAnalysis(callArgs->getText(), "radius:3.14");
}

// 3) Constructor with multiple arguments
TEST_F(HlIrTestFunction, FunctionCallArgs_MultipleArgs)
{
    // Arg1: "nome":"Thiago"
    auto typeStr = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto valStr = std::make_shared<hlir::Value>();
    valStr->set("Thiago", typeStr);
    auto arg1 = std::make_shared<hlir::FunctionCallArg>("nome", typeStr, valStr);

    // Arg2: "idade":21
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto valInt = std::make_shared<hlir::Value>();
    valInt->set(21, typeInt);
    auto arg2 = std::make_shared<hlir::FunctionCallArg>("idade", typeInt, valInt);

    // Arg3: "height":1.75
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);
    auto valDouble = std::make_shared<hlir::Value>();
    valDouble->set(1.75, typeDouble);
    auto arg3 = std::make_shared<hlir::FunctionCallArg>("height", typeDouble, valDouble);

    // Construct a vector of 3
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg1, arg2, arg3};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(vecArgs);

    // Expect getText() => "nome:Thiago,idade:21,height:1.75"
    runAnalysis(callArgs->getText(), "nome:Thiago,idade:21,height:1.75");
}

// 4) Add arguments after construction (if FunctionCallArgs has addCallArg)
TEST_F(HlIrTestFunction, FunctionCallArgs_AddLater)
{
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(); // initially empty

    // Arg1
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto valInt = std::make_shared<hlir::Value>();
    valInt->set(100, typeInt);
    auto a1 = std::make_shared<hlir::FunctionCallArg>("x", typeInt, valInt);

    // Arg2
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    auto valBool = std::make_shared<hlir::Value>();
    valBool->set(true, typeBool);
    auto a2 = std::make_shared<hlir::FunctionCallArg>("flag", typeBool, valBool);

    // *If* the class has "addCallArg":
    callArgs->addCallArg(a1);
    callArgs->addCallArg(a2);

    // Expect: "x:100,flag:true"
    runAnalysis(callArgs->getText(), "x:100,flag:true");
}

// 5) Test repeated calls to getText() (to ensure no duplication in output)
TEST_F(HlIrTestFunction, FunctionCallArgs_RepeatedCalls)
{
    auto typeChar = std::make_shared<hlir::Type>(tokenMap::TYPE_CHAR);
    auto valChar = std::make_shared<hlir::Value>();
    valChar->set("A", typeChar);
    auto arg1 = std::make_shared<hlir::FunctionCallArg>("letra", typeChar, valChar);

    // Create with an initial list of 1 element
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> vecArgs = {arg1};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(vecArgs);

    // Call getText() twice
    std::string first = callArgs->getText();
    std::string second = callArgs->getText();

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
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);

    // Put that arg into FunctionArgs
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Return type is int
    auto returnInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Create a Function "fn foo(a:int):int"
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", funcArgs, returnInt);

    // 2) Create a FunctionCallArg "a" => "12"
    auto val12 = std::make_shared<hlir::Value>();
    val12->set(12, typeInt);
    auto callArg = std::make_shared<hlir::FunctionCallArg>("a", typeInt, val12);

    // Put that callArg into FunctionCallArgs
    std::vector<std::shared_ptr<hlir::FunctionCallArg>> callArgVec = {callArg};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(callArgVec);

    // 3) Create the FunctionCall: "call int foo(a:12)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Expect: "call int foo(a:12)"
    // Or whatever the actual format from getText() is: "call {returnType} {functionName}({argName:argValue})"
    runAnalysis(functionCall->getText(), "call int foo(a:12)");
}

TEST_F(HlIrTestFunction, FunctionCall_MultipleArgs_FloatReturn)
{
    // Function args: (x:int, y:float)
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeFloat);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Return type is float
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Create the Function "fn sum(x:int,y:float):float"
    auto func = std::make_shared<hlir::Function>();
    func->set("sum", funcArgs, returnFloat);

    // Now the call arguments: "x:10", "y:3.14"
    auto val10 = std::make_shared<hlir::Value>();
    val10->set(10, typeInt);

    auto val3_14 = std::make_shared<hlir::Value>();
    val3_14->set(3.14f, typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgsVec = std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(callArgsVec);

    // "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    runAnalysis(functionCall->getText(), "call float sum(x:10,y:3.14)");
}

TEST_F(HlIrTestFunction, FunctionCall_NoArgs_VoidReturn)
{
    // If you have a TYPE_VOID or similar
    auto typeVoid = std::make_shared<hlir::Type>(tokenMap::VOID);

    // Function with no arguments
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    auto func = std::make_shared<hlir::Function>();
    func->set("doSomething", funcArgs, typeVoid);

    // The callArgs is also empty
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>();

    // "call void doSomething()"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    runAnalysis(functionCall->getText(), "call void doSomething()");
}

TEST_F(HlIrTestFunction, FunctionCall_BooleanReturn)
{
    // Return type is boolean
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    // Single param "flag:boolean"
    auto argFlag = std::make_shared<hlir::Arg>();
    argFlag->set("flag", typeBool);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argFlag);

    auto func = std::make_shared<hlir::Function>();
    func->set("checkFlag", funcArgs, typeBool);

    // CallArg "flag:true"
    auto valTrue = std::make_shared<hlir::Value>();
    valTrue->set(true, typeBool);
    auto callArgFlag = std::make_shared<hlir::FunctionCallArg>("flag", typeBool, valTrue);

    auto callArgsVec = std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgFlag};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(callArgsVec);

    // "call boolean checkFlag(flag:true)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    runAnalysis(functionCall->getText(), "call boolean checkFlag(flag:true)");
}

TEST_F(HlIrTestFunction, FunctionCall_RepeatedCallsToGetText)
{
    // Return type double
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);
    // Args (n:int)
    auto argN = std::make_shared<hlir::Arg>();
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    argN->set("n", typeInt);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argN);

    auto func = std::make_shared<hlir::Function>();
    func->set("sqrtCalc", funcArgs, typeDouble);

    // CallArg "n:25"
    auto val25 = std::make_shared<hlir::Value>();
    val25->set(25, typeInt);
    auto callArgN = std::make_shared<hlir::FunctionCallArg>("n", typeInt, val25);
    auto callArgsVec = std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgN};
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(callArgsVec);

    // "call double sqrtCalc(n:25)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Check repeated calls
    std::string first = functionCall->getText();
    std::string second = functionCall->getText();

    // If your internal stringstream accumulates, second might differ
    // We expect them both to be the same
    runAnalysis(first, "call double sqrtCalc(n:25)");
    runAnalysis(second, "call double sqrtCalc(n:25)");
}

// ---------------------------------------------------------------------
// TESTS FOR THE CLASS "hlir::Statement"
// ---------------------------------------------------------------------

// Teste para o construtor padrão
TEST_F(HlIrTestFunction, Statement_DefaultConstructor)
{
    auto stmt = std::make_shared<hlir::Statement>();

    std::string text = stmt->getText();
    runAnalysis(text, "");
}

// Teste para o construtor com uma lista de ValidStatement
TEST_F(HlIrTestFunction, Statement_ConstructorWithList)
{
    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeFloat);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>();
    func->set("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>();
    val10->set(10, typeInt);

    auto val3_14 = std::make_shared<hlir::Value>();
    val3_14->set(3.14f, typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>();
    expr1->set(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>();
    varRes->set("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>();
    expr2->set(varRes, functionCall);

    // Criar o Statement com a lista
    auto stmt = std::make_shared<hlir::Statement>();
    stmt->addStatement(expr1);
    stmt->addStatement(functionCall);
    stmt->addStatement(expr2);

    // Definir a string esperada sem quebra de linha inicial e sem indentação
    std::string expectedText = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    std::string actualText = stmt->getText();
    // EXPECT_EQ(actualText, expectedText);
    runAnalysis(actualText, expectedText);
}

// Teste para adicionar um ValidStatement usando addStatement
TEST_F(HlIrTestFunction, Statement_AddStatement)
{
    auto stmt = std::make_shared<hlir::Statement>();

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeFloat);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>();
    func->set("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>();
    val10->set(10, typeInt);

    auto val3_14 = std::make_shared<hlir::Value>();
    val3_14->set(3.14f, typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>();
    expr1->set(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>();
    varRes->set("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>();
    expr2->set(varRes, functionCall);

    // Adicionar declarações ao Statement
    stmt->addStatement(expr1);
    stmt->addStatement(functionCall);
    stmt->addStatement(expr2);

    // Definir a string esperada sem quebra de linha inicial e sem indentação
    std::string expectedText = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    // Obter a saída real do getText()
    std::string actualText = stmt->getText();

    // Comparar diretamente as strings
    runAnalysis(actualText, expectedText);
}

// Teste para obter a lista de statements e verificar a saída de getText()
TEST_F(HlIrTestFunction, Statement_GetText_MultipleStatements)
{
    auto stmt = std::make_shared<hlir::Statement>();

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeFloat);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>();
    func->set("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>();
    val10->set(10, typeInt);

    auto val3_14 = std::make_shared<hlir::Value>();
    val3_14->set(3.14f, typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>();
    expr1->set(varA, plusOp);

    // Criar a expressão Expr para "let res:int = call float sum(x:10,y:3.14)"
    auto varRes = std::make_shared<hlir::Variable>();
    varRes->set("res", typeInt);
    auto expr2 = std::make_shared<hlir::Expr>();
    expr2->set(varRes, functionCall);

    // Adicionar declarações ao Statement
    stmt->addStatement(expr1);
    stmt->addStatement(functionCall);
    stmt->addStatement(expr2);

    // Verificar a saída de getText()
    std::string expectedText = " let a:int = PLUS a, b\n call float sum(x:10,y:3.14)\n let res:int = call float sum(x:10,y:3.14)\n";

    std::string actualText = stmt->getText();
    runAnalysis(actualText, expectedText);
}

// Teste para getText() com uma única Expr
TEST_F(HlIrTestFunction, Statement_GetText_SingleExpr)
{
    auto stmt = std::make_shared<hlir::Statement>();

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeFloat);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>();
    func->set("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>();
    val10->set(10, typeInt);

    auto val3_14 = std::make_shared<hlir::Value>();
    val3_14->set(3.14f, typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Criar as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Criar o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Criar a expressão Expr para "let a:int = PLUS a, b"
    auto expr1 = std::make_shared<hlir::Expr>();
    expr1->set(varA, plusOp);

    // Adicionar apenas a expressão ao Statement
    stmt->addStatement(expr1);

    // Verificar a saída de getText()
    std::string expectedText = " let a:int = PLUS a, b\n";
    std::string actualText = stmt->getText();
    runAnalysis(actualText, expectedText);
}

// Teste para getText() com uma única FunctionCall
TEST_F(HlIrTestFunction, Statement_GetText_SingleFunctionCall)
{
    auto stmt = std::make_shared<hlir::Statement>();

    // Criar os tipos
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Criar os argumentos da função
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeInt);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeFloat);

    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Criar a função "fn sum(x:int,y:float):float"
    auto returnFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto func = std::make_shared<hlir::Function>();
    func->set("sum", funcArgs, returnFloat);

    // Criar os call arguments "x:10" e "y:3.14"
    auto val10 = std::make_shared<hlir::Value>();
    val10->set(10, typeInt);

    auto val3_14 = std::make_shared<hlir::Value>();
    val3_14->set(3.14f, typeFloat);

    auto callArgX = std::make_shared<hlir::FunctionCallArg>("x", typeInt, val10);
    auto callArgY = std::make_shared<hlir::FunctionCallArg>("y", typeFloat, val3_14);

    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgX, callArgY});

    // Criar a FunctionCall "call float sum(x:10,y:3.14)"
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Adicionar apenas a FunctionCall ao Statement
    stmt->addStatement(functionCall);

    // Verificar a saída de getText()
    std::string expectedText = " call float sum(x:10,y:3.14)\n";
    std::string actualText = stmt->getText();
    runAnalysis(actualText, expectedText);
}

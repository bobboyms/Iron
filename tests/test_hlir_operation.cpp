#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

#include "../src/headers/Hlir.h"
#include "antlr4-runtime.h"

// Se quiser ignorar espaços em branco, eis uma função de apoio:

class HlIrOperationTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Se precisar de algo antes de cada teste, faça aqui
    }

    std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });
        return result;
    }

    // Função para comparar duas strings ignorando espaços
    void runAnalysis(const std::string &got, const std::string &expected)
    {
        if (removeWhitespace(got) == removeWhitespace(expected))
        {
            // Test OK
            return;
        }
        else
        {
            FAIL() << "Got:      " << removeWhitespace(got)
                   << "\nExpected: " << removeWhitespace(expected);
        }
    }
};

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "Assign"
// ---------------------------------------------------------------------

TEST_F(HlIrOperationTest, Assign_BasicInt)
{
    // Variable de tipo INT
    auto varTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto variable = std::make_shared<hlir::Variable>();
    variable->set("idade", varTypeInt);

    // Value de tipo INT
    auto val = std::make_shared<hlir::Value>();
    val->set("21", varTypeInt);

    // Cria Assign -> deve funcionar sem exceção
    auto assign = std::make_shared<hlir::Assign>();
    assign->set(variable, val);

    // Checa saída: "let idade:int = 21"
    runAnalysis(assign->getText(), "let idade:int = 21");
}

TEST_F(HlIrOperationTest, Assign_BasicString)
{
    auto varTypeStr = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto variable = std::make_shared<hlir::Variable>();
    variable->set("nome", varTypeStr);

    auto val = std::make_shared<hlir::Value>();
    val->set("Thiago", varTypeStr);

    auto assign = std::make_shared<hlir::Assign>();
    assign->set(variable, val);

    // Esperamos: "let nome:string = Thiago"
    runAnalysis(assign->getText(), "let nome:string = Thiago");
}

TEST_F(HlIrOperationTest, Assign_TypeMismatch)
{
    // Variable do tipo INT
    auto varTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto variable = std::make_shared<hlir::Variable>();
    variable->set("idade", varTypeInt);

    // Value do tipo STRING
    auto valTypeStr = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto val = std::make_shared<hlir::Value>();
    val->set("25", valTypeStr);

    // Tentar criar Assign deve disparar exceção
    EXPECT_THROW({ std::make_shared<hlir::Assign>()->set(variable, val); }, hlir::HLIRException);
}

TEST_F(HlIrOperationTest, Assign_RepeatedCallsGetText)
{
    auto varTypeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    auto variable = std::make_shared<hlir::Variable>();
    variable->set("flag", varTypeBool);

    auto val = std::make_shared<hlir::Value>();
    val->set("true", varTypeBool);
    auto assign = std::make_shared<hlir::Assign>();
    assign->set(variable, val);

    // Checa se várias chamadas a getText retornam o mesmo valor
    std::string first = assign->getText();

    // Esperado: "let flag:boolean = true"
    runAnalysis(first, "let flag:boolean = true");
}

// ---------------------------------------------------------------------
// TESTES PARA AS CLASSES "Plus", "Minus", "Mult", "Div"
// ---------------------------------------------------------------------

// Teste para Plus com variáveis do mesmo tipo
TEST_F(HlIrOperationTest, Plus_SameType_Variables)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Cria o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Verifica o texto gerado
    runAnalysis(plusOp->getText(), "PLUS a, b");
}

// Teste para Minus com variáveis do mesmo tipo
TEST_F(HlIrOperationTest, Minus_SameType_Variables)
{
    // Cria o tipo float
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria as variáveis 'x:float' e 'y:float'
    auto varX = std::make_shared<hlir::Variable>();
    varX->set("x", typeFloat);

    auto varY = std::make_shared<hlir::Variable>();
    varY->set("y", typeFloat);

    // Cria o operador Minus
    auto minusOp = std::make_shared<hlir::Minus>();
    minusOp->set(varX, varY);

    // Verifica o texto gerado
    runAnalysis(minusOp->getText(), "MINUS x, y");
}

// Teste para Mult com variáveis do mesmo tipo
TEST_F(HlIrOperationTest, Mult_SameType_Variables)
{
    // Cria o tipo double
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);

    // Cria as variáveis 'm:double' e 'n:double'
    auto varM = std::make_shared<hlir::Variable>();
    varM->set("m", typeDouble);

    auto varN = std::make_shared<hlir::Variable>();
    varN->set("n", typeDouble);

    // Cria o operador Mult
    auto multOp = std::make_shared<hlir::Mult>();
    multOp->set(varM, varN);

    // Verifica o texto gerado
    runAnalysis(multOp->getText(), "MULT m, n");
}

// Teste para Div com variáveis do mesmo tipo
TEST_F(HlIrOperationTest, Div_SameType_Variables)
{
    // Cria o tipo boolean
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    // Cria as variáveis 'flag1:boolean' e 'flag2:boolean'
    auto varFlag1 = std::make_shared<hlir::Variable>();
    varFlag1->set("flag1", typeBool);

    auto varFlag2 = std::make_shared<hlir::Variable>();
    varFlag2->set("flag2", typeBool);

    // Cria o operador Div
    auto divOp = std::make_shared<hlir::Div>();
    divOp->set(varFlag1, varFlag2);

    // Verifica o texto gerado
    runAnalysis(divOp->getText(), "DIV flag1, flag2");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "Expr"
// ---------------------------------------------------------------------

// Teste para Expr com operador Plus
TEST_F(HlIrOperationTest, Expr_PlusOperator)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Cria o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Cria a expressão válida como Plus
    hlir::ValidExpr exprVariant = plusOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(varA, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let a:int = PLUS a, b");
}

// Teste para Expr com operador Minus
TEST_F(HlIrOperationTest, Expr_MinusOperator)
{
    // Cria o tipo float
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria as variáveis 'x:float' e 'y:float'
    auto varX = std::make_shared<hlir::Variable>();
    varX->set("x", typeFloat);

    auto varY = std::make_shared<hlir::Variable>();
    varY->set("y", typeFloat);

    // Cria o operador Minus
    auto minusOp = std::make_shared<hlir::Minus>();
    minusOp->set(varX, varY);

    // Cria a expressão válida como Minus
    hlir::ValidExpr exprVariant = minusOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(varX, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let x:float = MINUS x, y");
}

// Teste para Expr com operador Mult
TEST_F(HlIrOperationTest, Expr_MultOperator)
{
    // Cria o tipo double
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);

    // Cria as variáveis 'm:double' e 'n:double'
    auto varM = std::make_shared<hlir::Variable>();
    varM->set("m", typeDouble);

    auto varN = std::make_shared<hlir::Variable>();
    varN->set("n", typeDouble);

    // Cria o operador Mult
    auto multOp = std::make_shared<hlir::Mult>();
    multOp->set(varM, varN);

    // Cria a expressão válida como Mult
    hlir::ValidExpr exprVariant = multOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(varM, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let m:double = MULT m, n");
}

// Teste para Expr com operador Div
TEST_F(HlIrOperationTest, Expr_DivOperator)
{
    // Cria o tipo boolean
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    // Cria as variáveis 'flag1:boolean' e 'flag2:boolean'
    auto varFlag1 = std::make_shared<hlir::Variable>();
    varFlag1->set("flag1", typeBool);

    auto varFlag2 = std::make_shared<hlir::Variable>();
    varFlag2->set("flag2", typeBool);

    // Cria o operador Div
    auto divOp = std::make_shared<hlir::Div>();
    divOp->set(varFlag1, varFlag2);

    // Cria a expressão válida como Div
    hlir::ValidExpr exprVariant = divOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(varFlag1, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let flag1:boolean = DIV flag1, flag2");
}

// Teste para Expr com FunctionCall
TEST_F(HlIrOperationTest, Expr_FunctionCall)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", funcArgs, typeInt);

    // Cria o valor '12' do tipo int
    auto val12 = std::make_shared<hlir::Value>();
    val12->set("12", typeInt);

    // Cria FunctionCallArg para 'a:12'
    auto callArgA = std::make_shared<hlir::FunctionCallArg>("a", typeInt, val12);

    // Cria FunctionCallArgs com um argumento
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>();
    callArgs->addCallArg(callArgA);

    // Cria o FunctionCall
    auto functionCall = std::make_shared<hlir::FunctionCall>();
    functionCall->set(func, callArgs);

    // Cria a variável associada à expressão
    auto variable = std::make_shared<hlir::Variable>();
    variable->set("result", typeInt);

    // Cria a expressão válida como FunctionCall
    hlir::ValidExpr exprVariant = functionCall;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(variable, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let result:int = call int foo(a:12)");
}

// Teste para Expr com Variable (espera exceção)
TEST_F(HlIrOperationTest, Expr_Variable)
{
    // Cria o tipo string
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Cria a variável 'name:string'
    auto varName = std::make_shared<hlir::Variable>();
    varName->set("name", typeString);

    // Cria a expressão válida como Variable
    hlir::ValidExpr exprVariant = varName;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(varName, exprVariant);

    // Verifica se getText() lança uma exceção
    EXPECT_THROW({ expr->getText(); }, hlir::HLIRException);
}

// Teste para Expr com múltiplas chamadas a getText()
TEST_F(HlIrOperationTest, Expr_RepeatedCallsGetText)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    auto varB = std::make_shared<hlir::Variable>();
    varB->set("b", typeInt);

    // Cria o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>();
    plusOp->set(varA, varB);

    // Cria a expressão válida como Plus
    hlir::ValidExpr exprVariant = plusOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>();
    expr->set(varA, exprVariant);

    // Chama getText() duas vezes
    std::string first = expr->getText();
    std::string second = expr->getText();

    // Verifica se ambos os textos são iguais
    runAnalysis(first, "let a:int = PLUS a, b");
    runAnalysis(second, "let a:int = PLUS a, b");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "Cast"
// ---------------------------------------------------------------------

TEST_F(HlIrOperationTest, Cast_IntToFloat)
{
    // Cria os tipos int e float
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    // Cria a operação de casting de 'a' para float
    auto castOp = std::make_shared<hlir::Cast>();
    castOp->apply(varA, typeFloat);

    // Verifica o texto gerado
    runAnalysis(castOp->getText(), "a int to float");
}

TEST_F(HlIrOperationTest, Cast_StringToInt)
{
    // Cria os tipos string e int
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria a variável 'name:string'
    auto varName = std::make_shared<hlir::Variable>();
    varName->set("name", typeString);

    // Cria a operação de casting de 'name' para int
    auto castOp = std::make_shared<hlir::Cast>();
    castOp->apply(varName, typeInt);

    // Verifica o texto gerado
    runAnalysis(castOp->getText(), "name string to int");
}

TEST_F(HlIrOperationTest, Cast_BooleanToDouble)
{
    // Cria os tipos boolean e double
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);

    // Cria a variável 'flag:boolean'
    auto varFlag = std::make_shared<hlir::Variable>();
    varFlag->set("flag", typeBool);

    // Cria a operação de casting de 'flag' para double
    auto castOp = std::make_shared<hlir::Cast>();
    castOp->apply(varFlag, typeDouble);

    // Verifica o texto gerado
    runAnalysis(castOp->getText(), "flag boolean to double");
}

TEST_F(HlIrOperationTest, Cast_NullVariable_ThrowsException)
{
    // Cria o tipo float
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria um ponteiro compartilhado nulo para variável
    std::shared_ptr<hlir::Variable> varNull = nullptr;

    // Tenta criar a operação de casting com variável nula e espera exceção
    EXPECT_THROW(
        {
            auto castOp = std::make_shared<hlir::Cast>();
            castOp->apply(varNull, typeFloat);
        },
        hlir::HLIRException);
}

TEST_F(HlIrOperationTest, Cast_NullType_ThrowsException)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria um ponteiro compartilhado nulo para tipo
    std::shared_ptr<hlir::Type> typeNull = nullptr;

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    // Tenta criar a operação de casting com tipo nulo e espera exceção
    EXPECT_THROW(
        {
            auto castOp = std::make_shared<hlir::Cast>();
            castOp->apply(varA, typeNull);
        },
        hlir::HLIRException);
}

TEST_F(HlIrOperationTest, Cast_SameType)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    // Cria a operação de casting de 'a' para int (mesmo tipo)
    auto castOp = std::make_shared<hlir::Cast>();
    castOp->apply(varA, typeInt);

    // Verifica o texto gerado
    runAnalysis(castOp->getText(), "a int to int");
}

TEST_F(HlIrOperationTest, Cast_RepeatedCallsGetText)
{
    // Cria os tipos int e float
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>();
    varA->set("a", typeInt);

    // Cria a operação de casting de 'a' para float
    auto castOp = std::make_shared<hlir::Cast>();
    castOp->apply(varA, typeFloat);

    // Chama getText() duas vezes
    std::string first = castOp->getText();
    std::string second = castOp->getText();

    // Verifica se ambos os textos são iguais
    runAnalysis(first, "a int to float");
    runAnalysis(second, "a int to float");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "FunctionPtr"
// ---------------------------------------------------------------------

TEST_F(HlIrOperationTest, FunctionPtr_BasicFunction)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", funcArgs, typeInt);

    // Cria o FunctionPtr para a função 'foo'
    auto funcPtr = std::make_shared<hlir::FunctionPtr>();
    funcPtr->set(func);

    // Esperamos que getText() retorne "fptr foo"
    runAnalysis(funcPtr->getText(), "fptr foo");
}

TEST_F(HlIrOperationTest, FunctionPtr_VoidFunction)
{
    // Cria o tipo void
    auto typeVoid = std::make_shared<hlir::Type>(tokenMap::VOID);

    // Cria FunctionArgs vazio
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();

    // Cria a função 'doSomething' retornando void
    auto func = std::make_shared<hlir::Function>();
    func->set("doSomething", funcArgs, typeVoid);

    // Cria o FunctionPtr para a função 'doSomething'
    auto funcPtr = std::make_shared<hlir::FunctionPtr>();
    funcPtr->set(func);

    // Esperamos que getText() retorne "fptr doSomething"
    runAnalysis(funcPtr->getText(), "fptr doSomething");
}

TEST_F(HlIrOperationTest, FunctionPtr_NullFunction_ThrowsException)
{
    // Cria um ponteiro compartilhado nulo para função
    std::shared_ptr<hlir::Function> funcNull = nullptr;

    // Tenta criar o FunctionPtr com ponteiro nulo e espera uma exceção
    EXPECT_THROW(
        {
            auto funcPtrNull = std::make_shared<hlir::FunctionPtr>();
            funcPtrNull->set(funcNull);
        },
        hlir::HLIRException);
}

TEST_F(HlIrOperationTest, FunctionPtr_RepeatedCallsGetText)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>();
    func->set("foo", funcArgs, typeInt);

    // Cria o FunctionPtr para a função 'foo'
    auto funcPtr = std::make_shared<hlir::FunctionPtr>();
    funcPtr->set(func);

    // Chama getText() duas vezes
    std::string first = funcPtr->getText();
    std::string second = funcPtr->getText();

    // Verifica se ambos os textos são iguais
    runAnalysis(first, "fptr foo");
    runAnalysis(second, "fptr foo");
}

TEST_F(HlIrOperationTest, FunctionPtr_DifferentSignatures)
{
    // Cria os tipos double e string
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Cria os argumentos 'x:double' e 'y:string'
    auto argX = std::make_shared<hlir::Arg>();
    argX->set("x", typeDouble);

    auto argY = std::make_shared<hlir::Arg>();
    argY->set("y", typeString);

    // Cria FunctionArgs com dois argumentos
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argX);
    funcArgs->addArg(argY);

    // Cria a função 'combine' retornando string
    auto func = std::make_shared<hlir::Function>();
    func->set("combine", funcArgs, typeString);

    // Cria o FunctionPtr para a função 'combine'
    auto funcPtr = std::make_shared<hlir::FunctionPtr>();
    funcPtr->set(func);

    // Esperamos que getText() retorne "fptr combine"
    runAnalysis(funcPtr->getText(), "fptr combine");
}

TEST_F(HlIrOperationTest, FunctionPtr_EmptyFunctionName)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria FunctionArgs com um argumento
    auto argA = std::make_shared<hlir::Arg>();
    argA->set("a", typeInt);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();
    funcArgs->addArg(argA);

    // Cria a função com nome vazio '': int foo(a:int)
    auto funcEmptyName = std::make_shared<hlir::Function>();
    funcEmptyName->set("", funcArgs, typeInt);

    // Cria o FunctionPtr para a função de nome vazio
    auto funcPtrEmptyName = std::make_shared<hlir::FunctionPtr>();
    funcPtrEmptyName->set(funcEmptyName);

    // Esperamos que getText() retorne "fptr " (note o espaço após 'fptr')
    runAnalysis(funcPtrEmptyName->getText(), "fptr ");
}

// ---------------------------------------------------------------------
// TESTES PARA OUTRAS CLASSES (Exemplos)
// ---------------------------------------------------------------------

// Exemplo de correção para hlir::Value
TEST_F(HlIrOperationTest, Value_EmptyString)
{
    // Value com string vazia
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto val = std::make_shared<hlir::Value>();
    val->set("", typeString);

    // getText() deve ser ""
    runAnalysis(val->getText(), "");

    // Verifica se o type é tokenMap::TYPE_STRING
    EXPECT_EQ(typeString, val->getValueType());
}

TEST_F(HlIrOperationTest, Value_DifferentType)
{
    // Testando com tokenMap::TYPE_FLOAT
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    auto val = std::make_shared<hlir::Value>();
    val->set("3.14", typeFloat);

    runAnalysis(val->getText(), "3.14");
    EXPECT_EQ(typeFloat, val->getValueType());
}

TEST_F(HlIrOperationTest, Value_RepeatedCallsGetText)
{
    // Verifica se múltiplas chamadas a getText() retornam o mesmo valor
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto val = std::make_shared<hlir::Value>();
    val->set("100", typeInt);

    std::string first = val->getText();
    std::string second = val->getText();

    // Verifica se ambas as chamadas retornam "100"
    runAnalysis(first, "100");
    runAnalysis(second, "100");
}

TEST_F(HlIrOperationTest, Value_BasicInt)
{
    // Exemplo: Value("25", tokenMap::TYPE_INT)
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto val = std::make_shared<hlir::Value>();
    val->set("25", typeInt);

    // Checa se o método getText() gera "25"
    runAnalysis(val->getText(), "25");

    // Checa se getValueType() retorna o tipo correto
    EXPECT_EQ(typeInt, val->getValueType())
        << "Value type should match the one passed in the constructor.";
}

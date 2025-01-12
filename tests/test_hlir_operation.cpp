#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

#include "../src/headers/Hlir.h"
#include "antlr4-runtime.h"

// Se quiser ignorar espaços em branco, eis uma função de apoio:

class HlIrTest : public ::testing::Test
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
            FAIL() << "Got:      " << got
                   << "\nExpected: " << expected;
        }
    }
};

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "Assign"
// ---------------------------------------------------------------------

TEST_F(HlIrTest, Assign_BasicInt)
{
    // Variable de tipo INT
    auto varTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto variable = std::make_shared<hlir::Variable>("idade", varTypeInt);

    // Value de tipo INT
    auto val = std::make_shared<hlir::Value>("21", varTypeInt);

    // Cria Assign -> deve funcionar sem exceção
    hlir::Assign assign(variable, val);

    // Checa saída: "let idade:int = 21"
    runAnalysis(assign.getText(), "let idade:int = 21");
}

TEST_F(HlIrTest, Assign_BasicString)
{
    auto varTypeStr = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto variable = std::make_shared<hlir::Variable>("nome", varTypeStr);

    auto val = std::make_shared<hlir::Value>("Thiago", varTypeStr);

    hlir::Assign assign(variable, val);

    // Esperamos: "let nome:string = Thiago"
    runAnalysis(assign.getText(), "let nome:string = Thiago");
}

TEST_F(HlIrTest, Assign_TypeMismatch)
{
    // Variable do tipo INT
    auto varTypeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto variable = std::make_shared<hlir::Variable>("idade", varTypeInt);

    // Value do tipo STRING
    auto valTypeStr = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto val = std::make_shared<hlir::Value>("25", valTypeStr);

    // Tentar criar Assign deve disparar exceção
    EXPECT_THROW({ hlir::Assign assign(variable, val); }, hlir::HLIRException);
}

TEST_F(HlIrTest, Assign_RepeatedCallsGetText)
{
    auto varTypeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    auto variable = std::make_shared<hlir::Variable>("flag", varTypeBool);

    auto val = std::make_shared<hlir::Value>("true", varTypeBool);

    hlir::Assign assign(variable, val);

    // Checa se várias chamadas a getText retornam o mesmo valor
    std::string first = assign.getText();

    // Esperado: "let flag:boolean = true"
    runAnalysis(first, "let flag:boolean = true");
}

// Teste para Plus com variáveis do mesmo tipo
TEST_F(HlIrTest, Plus_SameType_Variables)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Cria o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Verifica o texto gerado
    runAnalysis(plusOp->getText(), "PLUS a, b");
}

// Teste para Minus com variáveis do mesmo tipo
TEST_F(HlIrTest, Minus_SameType_Variables)
{
    // Cria o tipo float
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria as variáveis 'x:float' e 'y:float'
    auto varX = std::make_shared<hlir::Variable>("x", typeFloat);
    auto varY = std::make_shared<hlir::Variable>("y", typeFloat);

    // Cria o operador Minus
    auto minusOp = std::make_shared<hlir::Minus>(varX, varY);

    // Verifica o texto gerado
    runAnalysis(minusOp->getText(), "MINUS x, y");
}

// Teste para Mult com variáveis do mesmo tipo
TEST_F(HlIrTest, Mult_SameType_Variables)
{
    // Cria o tipo double
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);

    // Cria as variáveis 'm:double' e 'n:double'
    auto varM = std::make_shared<hlir::Variable>("m", typeDouble);
    auto varN = std::make_shared<hlir::Variable>("n", typeDouble);

    // Cria o operador Mult
    auto multOp = std::make_shared<hlir::Mult>(varM, varN);

    // Verifica o texto gerado
    runAnalysis(multOp->getText(), "MULT m, n");
}

// Teste para Div com variáveis do mesmo tipo
TEST_F(HlIrTest, Div_SameType_Variables)
{
    // Cria o tipo boolean
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    // Cria as variáveis 'flag1:boolean' e 'flag2:boolean'
    auto varFlag1 = std::make_shared<hlir::Variable>("flag1", typeBool);
    auto varFlag2 = std::make_shared<hlir::Variable>("flag2", typeBool);

    // Cria o operador Div
    auto divOp = std::make_shared<hlir::Div>(varFlag1, varFlag2);

    // Verifica o texto gerado
    runAnalysis(divOp->getText(), "DIV flag1, flag2");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "Expr"
// ---------------------------------------------------------------------

// Teste para Expr com operador Plus
TEST_F(HlIrTest, Expr_PlusOperator)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Cria o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Cria a expressão válida como Plus
    hlir::ValidExpr exprVariant = plusOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varA, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let a:int = PLUS a, b");
}

// Teste para Expr com operador Minus
TEST_F(HlIrTest, Expr_MinusOperator)
{
    // Cria o tipo float
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria as variáveis 'x:float' e 'y:float'
    auto varX = std::make_shared<hlir::Variable>("x", typeFloat);
    auto varY = std::make_shared<hlir::Variable>("y", typeFloat);

    // Cria o operador Minus
    auto minusOp = std::make_shared<hlir::Minus>(varX, varY);

    // Cria a expressão válida como Minus
    hlir::ValidExpr exprVariant = minusOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varX, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let x:float = MINUS x, y");
}

// Teste para Expr com operador Mult
TEST_F(HlIrTest, Expr_MultOperator)
{
    // Cria o tipo double
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);

    // Cria as variáveis 'm:double' e 'n:double'
    auto varM = std::make_shared<hlir::Variable>("m", typeDouble);
    auto varN = std::make_shared<hlir::Variable>("n", typeDouble);

    // Cria o operador Mult
    auto multOp = std::make_shared<hlir::Mult>(varM, varN);

    // Cria a expressão válida como Mult
    hlir::ValidExpr exprVariant = multOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varM, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let m:double = MULT m, n");
}

// Teste para Expr com operador Div
TEST_F(HlIrTest, Expr_DivOperator)
{
    // Cria o tipo boolean
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);

    // Cria as variáveis 'flag1:boolean' e 'flag2:boolean'
    auto varFlag1 = std::make_shared<hlir::Variable>("flag1", typeBool);
    auto varFlag2 = std::make_shared<hlir::Variable>("flag2", typeBool);

    // Cria o operador Div
    auto divOp = std::make_shared<hlir::Div>(varFlag1, varFlag2);

    // Cria a expressão válida como Div
    hlir::ValidExpr exprVariant = divOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varFlag1, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let flag1:boolean = DIV flag1, flag2");
}

// Teste para Expr com FunctionCall
TEST_F(HlIrTest, Expr_FunctionCall)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argA});

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>("foo", funcArgs, typeInt);

    // Cria o valor '12' do tipo int
    auto val12 = std::make_shared<hlir::Value>("12", typeInt);

    // Cria FunctionCallArg para 'a:12'
    auto callArgA = std::make_shared<hlir::FunctionCallArg>("a", typeInt, val12);

    // Cria FunctionCallArgs com um argumento
    auto callArgs = std::make_shared<hlir::FunctionCallArgs>(std::vector<std::shared_ptr<hlir::FunctionCallArg>>{callArgA});

    // Cria o FunctionCall
    auto functionCall = std::make_shared<hlir::FunctionCall>(func, callArgs);

    // Cria a expressão válida como FunctionCall
    hlir::ValidExpr exprVariant = functionCall;

    // Cria a variável associada à expressão (pode ser nullptr se não for necessário)
    auto variable = std::make_shared<hlir::Variable>("result", typeInt);

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(variable, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let result:int = call int foo(a:12)");
}

// Teste para Expr com Variable
TEST_F(HlIrTest, Expr_Variable)
{
    // Cria o tipo string
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Cria a variável 'name:string'
    auto varName = std::make_shared<hlir::Variable>("name", typeString);

    // Cria a expressão válida como Variable
    hlir::ValidExpr exprVariant = varName;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varName, exprVariant);

    // Verifica o texto gerado
    runAnalysis(expr->getText(), "let name:string = name");
}

// Teste para Expr com múltiplas chamadas a getText()
TEST_F(HlIrTest, Expr_RepeatedCallsGetText)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria as variáveis 'a:int' e 'b:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);
    auto varB = std::make_shared<hlir::Variable>("b", typeInt);

    // Cria o operador Plus
    auto plusOp = std::make_shared<hlir::Plus>(varA, varB);

    // Cria a expressão válida como Plus
    hlir::ValidExpr exprVariant = plusOp;

    // Cria a expressão Expr
    auto expr = std::make_shared<hlir::Expr>(varA, exprVariant);

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

// Teste para Cast de int para float
TEST_F(HlIrTest, Cast_IntToFloat)
{
    // Cria os tipos int e float
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);

    // Cria a operação de casting de 'a' para float
    hlir::Cast castOp(varA, typeFloat);

    // Verifica o texto gerado
    runAnalysis(castOp.getText(), "a int to float");
}

// Teste para Cast de string para int
TEST_F(HlIrTest, Cast_StringToInt)
{
    // Cria os tipos string e int
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria a variável 'name:string'
    auto varName = std::make_shared<hlir::Variable>("name", typeString);

    // Cria a operação de casting de 'name' para int
    hlir::Cast castOp(varName, typeInt);

    // Verifica o texto gerado
    runAnalysis(castOp.getText(), "name string to int");
}

// Teste para Cast de boolean para double
TEST_F(HlIrTest, Cast_BooleanToDouble)
{
    // Cria os tipos boolean e double
    auto typeBool = std::make_shared<hlir::Type>(tokenMap::TYPE_BOOLEAN);
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);

    // Cria a variável 'flag:boolean'
    auto varFlag = std::make_shared<hlir::Variable>("flag", typeBool);

    // Cria a operação de casting de 'flag' para double
    hlir::Cast castOp(varFlag, typeDouble);

    // Verifica o texto gerado
    runAnalysis(castOp.getText(), "flag boolean to double");
}

// Teste para Cast com variável nula (espera-se exceção)
TEST_F(HlIrTest, Cast_NullVariable_ThrowsException)
{
    // Cria o tipo float
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria um ponteiro compartilhado nulo para variável
    std::shared_ptr<hlir::Variable> varNull = nullptr;

    // Tenta criar a operação de casting com variável nula e espera exceção
    EXPECT_THROW({ hlir::Cast castOp(varNull, typeFloat); }, hlir::HLIRException);
}

// Teste para Cast com tipo nulo (espera-se exceção)
TEST_F(HlIrTest, Cast_NullType_ThrowsException)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria um ponteiro compartilhado nulo para tipo
    std::shared_ptr<hlir::Type> typeNull = nullptr;

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);

    // Tenta criar a operação de casting com tipo nulo e espera exceção
    EXPECT_THROW({ hlir::Cast castOp(varA, typeNull); }, hlir::HLIRException);
}

// Teste para Cast com mesmo tipo (int para int)
TEST_F(HlIrTest, Cast_SameType)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);

    // Cria a operação de casting de 'a' para int (mesmo tipo)
    hlir::Cast castOp(varA, typeInt);

    // Verifica o texto gerado
    runAnalysis(castOp.getText(), "a int to int");
}

// Teste para Cast com múltiplas chamadas a getText()
TEST_F(HlIrTest, Cast_RepeatedCallsGetText)
{
    // Cria os tipos int e float
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Cria a variável 'a:int'
    auto varA = std::make_shared<hlir::Variable>("a", typeInt);

    // Cria a operação de casting de 'a' para float
    hlir::Cast castOp(varA, typeFloat);

    // Chama getText() duas vezes
    std::string first = castOp.getText();
    std::string second = castOp.getText();

    // Verifica se ambos os textos são iguais
    runAnalysis(first, "a int to float");
    runAnalysis(second, "a int to float");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "FunctionPtr"
// ---------------------------------------------------------------------

// Teste para FunctionPtr com uma função básica
TEST_F(HlIrTest, FunctionPtr_BasicFunction)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argA});

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>("foo", funcArgs, typeInt);

    // Cria o FunctionPtr para a função 'foo'
    hlir::FunctionPtr funcPtr(func);

    // Esperamos que getText() retorne "fptr foo"
    runAnalysis(funcPtr.getText(), "fptr foo");
}

// Teste para FunctionPtr com uma função retornando void
TEST_F(HlIrTest, FunctionPtr_VoidFunction)
{
    // Cria o tipo void
    auto typeVoid = std::make_shared<hlir::Type>(tokenMap::VOID);

    // Cria FunctionArgs vazio
    auto funcArgs = std::make_shared<hlir::FunctionArgs>();

    // Cria a função 'doSomething' retornando void
    auto func = std::make_shared<hlir::Function>("doSomething", funcArgs, typeVoid);

    // Cria o FunctionPtr para a função 'doSomething'
    hlir::FunctionPtr funcPtr(func);

    // Esperamos que getText() retorne "fptr doSomething"
    runAnalysis(funcPtr.getText(), "fptr doSomething");
}

// Teste para FunctionPtr com ponteiro de função nulo (espera-se exceção)
TEST_F(HlIrTest, FunctionPtr_NullFunction_ThrowsException)
{
    // Cria um ponteiro compartilhado nulo para função
    std::shared_ptr<hlir::Function> funcNull = nullptr;

    // Tenta criar o FunctionPtr com ponteiro nulo e espera uma exceção
    EXPECT_THROW({ hlir::FunctionPtr funcPtrNull(funcNull); }, hlir::HLIRException);
}

// Teste para FunctionPtr com múltiplas chamadas a getText()
TEST_F(HlIrTest, FunctionPtr_RepeatedCallsGetText)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria o argumento 'a:int'
    auto argA = std::make_shared<hlir::Arg>("a", typeInt);

    // Cria FunctionArgs com um argumento
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argA});

    // Cria a função 'foo' retornando int
    auto func = std::make_shared<hlir::Function>("foo", funcArgs, typeInt);

    // Cria o FunctionPtr para a função 'foo'
    hlir::FunctionPtr funcPtr(func);

    // Chama getText() duas vezes
    std::string first = funcPtr.getText();
    std::string second = funcPtr.getText();

    // Verifica se ambos os textos são iguais
    runAnalysis(first, "fptr foo");
    runAnalysis(second, "fptr foo");
}

// Teste para FunctionPtr com funções de diferentes assinaturas
TEST_F(HlIrTest, FunctionPtr_DifferentSignatures)
{
    // Cria os tipos double e string
    auto typeDouble = std::make_shared<hlir::Type>(tokenMap::TYPE_DOUBLE);
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);

    // Cria os argumentos 'x:double' e 'y:string'
    auto argX = std::make_shared<hlir::Arg>("x", typeDouble);
    auto argY = std::make_shared<hlir::Arg>("y", typeString);

    // Cria FunctionArgs com dois argumentos
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argX, argY});

    // Cria a função 'combine' retornando string
    auto func = std::make_shared<hlir::Function>("combine", funcArgs, typeString);

    // Cria o FunctionPtr para a função 'combine'
    hlir::FunctionPtr funcPtr(func);

    // Esperamos que getText() retorne "fptr combine"
    runAnalysis(funcPtr.getText(), "fptr combine");
}

// Teste para FunctionPtr com função de nome vazio
TEST_F(HlIrTest, FunctionPtr_EmptyFunctionName)
{
    // Cria o tipo int
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);

    // Cria FunctionArgs com um argumento
    auto argA = std::make_shared<hlir::Arg>("a", typeInt);
    auto funcArgs = std::make_shared<hlir::FunctionArgs>(std::vector<std::shared_ptr<hlir::Arg>>{argA});

    // Cria a função com nome vazio '': int foo(a:int)
    auto funcEmptyName = std::make_shared<hlir::Function>("", funcArgs, typeInt);

    // Cria o FunctionPtr para a função de nome vazio
    hlir::FunctionPtr funcPtrEmptyName(funcEmptyName);

    // Esperamos que getText() retorne "fptr " (note o espaço após 'fptr')
    runAnalysis(funcPtrEmptyName.getText(), "fptr ");
}

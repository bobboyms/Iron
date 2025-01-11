#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>

#include "../src/hlir/Hlir.h" // Ajuste conforme seu projeto
#include "antlr4-runtime.h"   // Se você precisar do runtime do ANTLR nos testes

// ---------------------------------------------------------------------
// 1) Função auxiliar para remover espaços em branco
//    (usada para comparar strings se quiser ignorar detalhes de formatação).
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// 2) Fixture de teste (padrão Google Test)
// ---------------------------------------------------------------------
class HlIrTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Se precisar inicializar algo antes de cada teste, faça aqui.
    }

    std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });
        return result;
    }

    // Função para comparar strings (ignorando espaços em branco)
    void runAnalysis(const std::string &got, const std::string &expected)
    {
        if (removeWhitespace(got) == removeWhitespace(expected))
        {
            // Test OK
            return;
        }
        else
        {
            FAIL() << "Generated text does not match the expected text.\n"
                   << "Got:      " << got << "\n"
                   << "Expected: " << expected;
        }
    }
};

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE 'Value'
// ---------------------------------------------------------------------

TEST_F(HlIrTest, Value_BasicInt)
{
    // Exemplo: Value("25", TYPE_INT)
    auto typeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    hlir::Value val("25", typeInt);

    // Check getText() => "25"
    runAnalysis(val.getText(), "25");

    // Check getValueType() => deve ser TYPE_INT
    EXPECT_EQ(typeInt, val.getValueType())
        << "Value type should match the one passed in the constructor.";
}

TEST_F(HlIrTest, Value_EmptyString)
{
    // Value com string vazia
    auto typeString = std::make_shared<hlir::Type>(hlir::TYPE_STRING);
    hlir::Value val("", typeString);

    // getText() deve ser ""
    runAnalysis(val.getText(), "");

    // Verifica se o type é TYPE_STRING
    EXPECT_EQ(typeString, val.getValueType());
}

TEST_F(HlIrTest, Value_DifferentType)
{
    // Testando com TYPE_FLOAT
    auto typeFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);
    hlir::Value val("3.14", typeFloat);

    runAnalysis(val.getText(), "3.14");
    EXPECT_EQ(typeFloat, val.getValueType());
}

TEST_F(HlIrTest, Value_RepeatedCallsGetText)
{
    // Verifica se múltiplas chamadas a getText() retornam o mesmo valor
    auto typeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    hlir::Value val("100", typeInt);

    std::string first = val.getText();
    std::string second = val.getText();

    // Dependendo de como `sb` é usado,
    // se não for limpo, poderia acumular texto.
    // Vamos checar se continua o mesmo:
    runAnalysis(first, "100");
    runAnalysis(second, "100");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE 'Variable'
// ---------------------------------------------------------------------

TEST_F(HlIrTest, Variable_BasicInt)
{
    // Exemplo: Variable("idade", TYPE_INT)
    auto typeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    hlir::Variable var("idade", typeInt);

    // Esperamos "let idade:int" (conforme implementação)
    runAnalysis(var.getText(), "let idade:int");
}

TEST_F(HlIrTest, Variable_EmptyName)
{
    // Nome vazio, mas TYPE_FLOAT
    auto typeFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);
    hlir::Variable var("", typeFloat);

    // Esperamos "let :float" ou similar
    // Se a formatação for "let {}:{}", então sairá "let :float"
    runAnalysis(var.getText(), "let :float");
}

TEST_F(HlIrTest, Variable_DifferentTypeString)
{
    // Variable com TYPE_STRING
    auto typeString = std::make_shared<hlir::Type>(hlir::TYPE_STRING);
    hlir::Variable var("nome", typeString);

    runAnalysis(var.getText(), "let nome:string");
}

// ---------------------------------------------------------------------
// FIM DOS TESTES
// ---------------------------------------------------------------------

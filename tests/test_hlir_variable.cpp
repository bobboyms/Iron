#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>

// Ajuste os includes conforme a organização do seu projeto
#include "../src/headers/Hlir.h"     // Onde Assign, Variable, Value, Type, etc., estão declarados
#include "../src/headers/TokenMap.h" // Onde as constantes tokenMap::TYPE_* estão declaradas
#include "antlr4-runtime.h"          // Se necessário para seu projeto

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

    /**
     * @brief Remove todos os caracteres de espaço em branco de uma string.
     * @param str A string de entrada.
     * @return Uma nova string sem espaços em branco.
     */
    std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });
        return result;
    }

    /**
     * @brief Compara duas strings para igualdade, ignorando diferenças de espaços em branco.
     * @param got A string gerada pelo teste.
     * @param expected A string esperada para comparação.
     *
     * Se as strings corresponderem (ignorando espaços), o teste passa.
     * Caso contrário, falha e exibe as strings geradas e esperadas.
     */
    void runAnalysis(const std::string &got, const std::string &expected)
    {
        if (removeWhitespace(got) == removeWhitespace(expected))
        {
            // Teste passou
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
    // Exemplo: Value("25", tokenMap::TYPE_INT)
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    hlir::Value val("25", typeInt);

    // Checa se o método getText() gera "25"
    runAnalysis(val.getText(), "25");

    // Checa se getValueType() retorna o tipo correto
    EXPECT_EQ(typeInt, val.getValueType())
        << "Value type should match the one passed in the constructor.";
}

TEST_F(HlIrTest, Value_EmptyString)
{
    // Value com string vazia
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    hlir::Value val("", typeString);

    // getText() deve ser ""
    runAnalysis(val.getText(), "");

    // Verifica se o type é tokenMap::TYPE_STRING
    EXPECT_EQ(typeString, val.getValueType());
}

TEST_F(HlIrTest, Value_DifferentType)
{
    // Testando com tokenMap::TYPE_FLOAT
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);
    hlir::Value val("3.14", typeFloat);

    runAnalysis(val.getText(), "3.14");
    EXPECT_EQ(typeFloat, val.getValueType());
}

TEST_F(HlIrTest, Value_RepeatedCallsGetText)
{
    // Verifica se múltiplas chamadas a getText() retornam o mesmo valor
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    hlir::Value val("100", typeInt);

    std::string first = val.getText();
    std::string second = val.getText();

    // Verifica se ambas as chamadas retornam "100"
    runAnalysis(first, "100");
    runAnalysis(second, "100");
}

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE 'Variable'
// ---------------------------------------------------------------------

TEST_F(HlIrTest, Variable_BasicInt)
{
    // Exemplo: Variable("idade", tokenMap::TYPE_INT)
    auto typeInt = std::make_shared<hlir::Type>(tokenMap::TYPE_INT);
    hlir::Variable var("idade", typeInt);

    // Esperamos "let idade:int" (conforme implementação)
    runAnalysis(var.getText(), "let idade:int");
}

TEST_F(HlIrTest, Variable_EmptyName)
{
    // Nome vazio, mas tokenMap::TYPE_FLOAT
    auto typeFloat = std::make_shared<hlir::Type>(tokenMap::TYPE_FLOAT);

    // Tenta criar uma variável com nome vazio e espera exceção
    EXPECT_THROW({ hlir::Variable var("", typeFloat); }, hlir::HLIRException);
}

TEST_F(HlIrTest, Variable_DifferentTypeString)
{
    // Variable com tokenMap::TYPE_STRING
    auto typeString = std::make_shared<hlir::Type>(tokenMap::TYPE_STRING);
    hlir::Variable var("nome", typeString);

    runAnalysis(var.getText(), "let nome:string");
}
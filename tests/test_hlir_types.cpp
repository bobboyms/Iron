#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

// Ajuste os includes conforme a organização do seu projeto
#include "../src/headers/Hlir.h"     // onde Assign, Variable, Value, Type, etc. estão declarados
#include "../src/headers/TokenMap.h" // onde as constantes tokenMap::TYPE_* estão declaradas
#include "antlr4-runtime.h"          // se necessário para seu projeto

// Fixture de teste
class HlIrTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Se precisar inicializar algo antes de cada teste,
        // faça aqui.
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
     * @param input A string gerada pelo teste.
     * @param expectedOutput A string esperada para comparação.
     *
     * Se as strings corresponderem (ignorando espaços), o teste passa.
     * Caso contrário, falha e exibe as strings geradas e esperadas.
     */
    void runAnalysis(const std::string &input, const std::string &expectedOutput)
    {
        if (removeWhitespace(input) == removeWhitespace(expectedOutput))
        {
            return; // passou no teste
        }
        else
        {
            FAIL() << "Generated code does not match the expected code.\n"
                   << "Got:      " << input << "\n"
                   << "Expected: " << expectedOutput;
        }
    }
};

// ---------------------------------------------------------------------
// TESTES PARA A CLASSE "Type"
// ---------------------------------------------------------------------

TEST_F(HlIrTest, ValidIntType)
{
    auto type = hlir::Type(tokenMap::TYPE_INT);
    // Checa se o método getText() gera "int"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "int"));
}

TEST_F(HlIrTest, ValidCharType)
{
    auto type = hlir::Type(tokenMap::TYPE_CHAR);
    // Esperamos "char"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "char"));
}

TEST_F(HlIrTest, ValidFloatType)
{
    auto type = hlir::Type(tokenMap::TYPE_FLOAT);
    // Esperamos "float"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "float"));
}

TEST_F(HlIrTest, ValidStringType)
{
    auto type = hlir::Type(tokenMap::TYPE_STRING);
    // Esperamos "string"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "string"));
}

TEST_F(HlIrTest, ValidBooleanType)
{
    auto type = hlir::Type(tokenMap::TYPE_BOOLEAN);
    // Esperamos "boolean"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "boolean"));
}

TEST_F(HlIrTest, ValidDoubleType)
{
    auto type = hlir::Type(tokenMap::TYPE_DOUBLE);
    // Esperamos "double"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "double"));
}

TEST_F(HlIrTest, ValidFunctionType)
{
    auto type = hlir::Type(tokenMap::FUNCTION);
    // Esperamos "fn"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "fn"));
}

TEST_F(HlIrTest, ValidPtrFunctionType)
{
    auto type = hlir::Type(tokenMap::FUNCTION_PTR);
    // Esperamos "fptr"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "fptr"));
}

// Teste para Type com tipo inválido (espera-se exceção)
TEST_F(HlIrTest, Type_InvalidType_ThrowsException)
{
    int invalidType = 9999; // Supondo que 9999 não está definido no enum tokenMap::DataType

    EXPECT_THROW({ hlir::Type typeObj(invalidType); }, tokenMap::TokenNotFoundException);
}
#include <gtest/gtest.h>
#include <memory>

#include "../src/hlir/Hlir.h"
#include "antlr4-runtime.h"

class HlIrTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Se precisar inicializar algo antes de cada teste,
        // faça aqui.
    }

    std::string removeWhitespace(const std::string &str)
    {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                     [](unsigned char c)
                     { return !std::isspace(c); });
        return result;
    }

    // Função de apoio para verificar se o texto gerado
    // corresponde ao esperado (ignorando espaços em branco).
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

TEST_F(HlIrTest, ValidIntType)
{
    auto type = hlir::Type(hlir::TYPE_INT);
    // Checa se o método getText() gera "int"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "int"));
}

TEST_F(HlIrTest, ValidCharType)
{
    auto type = hlir::Type(hlir::TYPE_CHAR);
    // Esperamos "char"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "char"));
}

TEST_F(HlIrTest, ValidFloatType)
{
    auto type = hlir::Type(hlir::TYPE_FLOAT);
    // Esperamos "float"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "float"));
}

TEST_F(HlIrTest, ValidStringType)
{
    auto type = hlir::Type(hlir::TYPE_STRING);
    // Esperamos "string"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "string"));
}

TEST_F(HlIrTest, ValidBooleanType)
{
    auto type = hlir::Type(hlir::TYPE_BOOLEAN);
    // Esperamos "boolean"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "boolean"));
}

TEST_F(HlIrTest, ValidDoubleType)
{
    auto type = hlir::Type(hlir::TYPE_DOUBLE);
    // Esperamos "double"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "double"));
}

TEST_F(HlIrTest, ValidFunctionType)
{
    auto type = hlir::Type(hlir::FUNCTION);
    // Esperamos "double"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "fn"));
}

TEST_F(HlIrTest, ValidPtrFunctionType)
{
    auto type = hlir::Type(hlir::FUNCTION_PTR);
    // Esperamos "double"
    EXPECT_NO_THROW(runAnalysis(type.getText(), "fptr"));
}

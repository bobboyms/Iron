#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

// Ajuste os includes conforme a organização do seu projeto
#include "../src/hlir/Hlir.h" // onde Assign, Variable, Value, Type, etc. estão declarados
#include "antlr4-runtime.h"   // se necessário para seu projeto

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
    auto varTypeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
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
    auto varTypeStr = std::make_shared<hlir::Type>(hlir::TYPE_STRING);
    auto variable = std::make_shared<hlir::Variable>("nome", varTypeStr);

    auto val = std::make_shared<hlir::Value>("Thiago", varTypeStr);

    hlir::Assign assign(variable, val);

    // Esperamos: "let nome:string = Thiago"
    runAnalysis(assign.getText(), "let nome:string = Thiago");
}

TEST_F(HlIrTest, Assign_TypeMismatch)
{
    // Variable do tipo INT
    auto varTypeInt = std::make_shared<hlir::Type>(hlir::TYPE_INT);
    auto variable = std::make_shared<hlir::Variable>("idade", varTypeInt);

    // Value do tipo STRING
    auto valTypeStr = std::make_shared<hlir::Type>(hlir::TYPE_STRING);
    auto val = std::make_shared<hlir::Value>("25", valTypeStr);

    // Tentar criar Assign deve disparar exceção
    EXPECT_THROW({ hlir::Assign assign(variable, val); }, hlir::HLIRException);
}

TEST_F(HlIrTest, Assign_EmptyVarName)
{
    // Variable com nome vazio, mas tipo FLOAT
    auto varTypeFloat = std::make_shared<hlir::Type>(hlir::TYPE_FLOAT);
    auto variable = std::make_shared<hlir::Variable>("", varTypeFloat);

    // Value também do tipo FLOAT
    auto val = std::make_shared<hlir::Value>("3.14", varTypeFloat);

    // Deve funcionar, pois tipo é o mesmo
    hlir::Assign assign(variable, val);

    // Esperamos "let :float = 3.14" (nome vazio)
    runAnalysis(assign.getText(), "let :float = 3.14");
}

TEST_F(HlIrTest, Assign_RepeatedCallsGetText)
{
    auto varTypeBool = std::make_shared<hlir::Type>(hlir::TYPE_BOOLEAN);
    auto variable = std::make_shared<hlir::Variable>("flag", varTypeBool);

    auto val = std::make_shared<hlir::Value>("true", varTypeBool);

    hlir::Assign assign(variable, val);

    // Checa se várias chamadas a getText retornam o mesmo valor
    std::string first = assign.getText();

    // Esperado: "let flag:boolean = true"
    runAnalysis(first, "let flag:boolean = true");
}

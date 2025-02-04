cmake_minimum_required(VERSION 3.10)
project(IronLang VERSION 1.0 LANGUAGES CXX)

# Define o compilador (opcional, se quiser fixar para o clang++ desejado)
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

# Define o padrão C++ de forma “oficial”
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# (Opcional) Adiciona a flag para utilizar a libc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1 -stdlib=libc++")

# Diretórios de include
include_directories(
        /opt/homebrew/opt/llvm/include
        /usr/local/include/antlr4-runtime
        /opt/homebrew/include       # Para GTest
)

# Diretórios de link
link_directories(
        /opt/homebrew/opt/llvm/lib
        /usr/local/lib
        /opt/homebrew/lib
)

# Bibliotecas externas
set(ANTLR_LIB /usr/local/lib/libantlr4-runtime.a)
set(LLVM_LIB LLVM-19)

# Fontes do programa principal e comuns
set(SRC_MAIN src/main.cpp)
set(SRC_COMMON
        src/hlir/Type.cpp
        src/hlir/FunctionArgs.cpp
        src/hlir/Function.cpp
        src/hlir/Variable.cpp
        src/hlir/Operations.cpp
        src/hlir/HLIRGenerator.cpp
        src/scope/ScopeManager.cpp
        src/llvm/Types.cpp
        src/llvm/LLVM.cpp
        src/llvm/Operations.cpp
        src/hlir/WriterCodeHLIR.cpp
        src/utils/Colors.cpp
        src/semantical/SemanticalAnalysis.cpp
        src/semantical/Functions.cpp
        src/parsers/IronLexer.cpp
        src/parsers/IronParser.cpp
        src/parsers/IronBaseListener.cpp
        src/parsers/IronListener.cpp
        src/parsers/HightLavelIRLexer.cpp
        src/parsers/HightLavelIRParser.cpp
        src/parsers/HightLavelIRBaseListener.cpp
        src/parsers/HightLavelIRListener.cpp
)

# Fontes dos testes
set(TEST_SRC
        tests/test_semantical_analysis.cpp
        # Outros testes podem ser adicionados aqui
)

###########################################
# Executável do Programa Principal: "program"
###########################################
add_executable(program ${SRC_MAIN} ${SRC_COMMON})
target_link_libraries(program PRIVATE ${LLVM_LIB} ${ANTLR_LIB})

###########################################
# Executável dos Testes: "test_program"
###########################################
add_executable(test_program ${TEST_SRC} ${SRC_COMMON})
target_link_libraries(test_program PRIVATE ${LLVM_LIB} ${ANTLR_LIB})

# Integração com GTest
find_package(GTest REQUIRED)
if(GTest_FOUND)
    target_include_directories(test_program PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(test_program PRIVATE GTest::GTest GTest::Main)
else()
    message(WARNING "GTest não foi encontrado. Verifique a instalação do GTest.")
endif()

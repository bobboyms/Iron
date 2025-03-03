cmake_minimum_required(VERSION 3.15)
project(IronLang VERSION 1.0 LANGUAGES C CXX)
###############################################################################
# 1. Configuração do compilador (clang++)
###############################################################################
# Tenta localizar o clang++ automaticamente
find_program(CLANGPP_EXECUTABLE clang++)
if(CLANGPP_EXECUTABLE)
    message(STATUS "clang++ encontrado: ${CLANGPP_EXECUTABLE}")
else()
    message(WARNING "clang++ não foi encontrado; será usado o compilador padrão: ${CMAKE_CXX_COMPILER}")
endif()

# Se o compilador atual não for o clang++, exibe aviso.
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(WARNING "O compilador atual não é o clang++. Recomenda-se utilizar o clang++ para este projeto.")
endif()

###############################################################################
# 2. Configuração do padrão C++
###############################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adiciona flags de compilação para tornar a compilação mais rigorosa
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall) # -Wextra -Werror
endif()


###############################################################################
# 3. Encontrar e configurar o LLVM 19
###############################################################################
# Caso o CMake não encontre automaticamente o LLVM, defina a variável LLVM_DIR.
# Exemplo (descomente se necessário):
# set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")

# LLVM 19.1.7
find_package(LLVM REQUIRED CONFIG)
if(NOT LLVM_FOUND)
    message(FATAL_ERROR "LLVM 19 não foi encontrado!")
endif()
message(STATUS "LLVM ${LLVM_PACKAGE_VERSION} encontrado.")

# Inclui os diretórios de include e define macros conforme as configurações do LLVM
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Mapeia os componentes necessários do LLVM para as bibliotecas de linkagem.
llvm_map_components_to_libnames(llvm_libs
        core
        support
        linker
        codegen
        asmprinter
        mc
        target
        executionengine
        mcjit
        interpreter
        AArch64CodeGen
        AArch64AsmParser
)

#llvm_map_components_to_libnames(llvm_libs
#        core
#        support
#        codegen
#        asmprinter
#        mc
#        target
#        executionengine      # Adicione este componente
#        AArch64CodeGen
#        AArch64AsmParser
#)

#llvm_map_components_to_libnames(llvm_libs
#        core
#        support
#        irreader
#        bitwriter
#        codegen
#        asmprinter
#        asmparser
#        target
#        mc
#        AArch64CodeGen
#        AArch64AsmParser
#)

message(STATUS "Bibliotecas do LLVM mapeadas: ${llvm_libs}")

###############################################################################
# 4. Encontrar o yaml-cpp
###############################################################################
find_package(yaml-cpp REQUIRED)
if(NOT yaml-cpp_FOUND)
    message(FATAL_ERROR "yaml-cpp não foi encontrado!")
endif()
message(STATUS "yaml-cpp encontrado.")

###############################################################################
# 5. Encontrar o GTest
###############################################################################
find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
    message(FATAL_ERROR "GTest não foi encontrado!")
endif()
message(STATUS "GTest encontrado.")

###############################################################################
# 6. Encontrar o ANTLR4
###############################################################################
# Procura pela biblioteca do runtime do ANTLR4
find_library(ANTLR4_LIBRARY
        NAMES antlr4-runtime
        PATHS /usr/lib /usr/local/lib /opt/homebrew/lib
)
if(NOT ANTLR4_LIBRARY)
    message(FATAL_ERROR "A biblioteca antlr4-runtime não foi encontrada!")
endif()
message(STATUS "antlr4-runtime encontrado: ${ANTLR4_LIBRARY}")

# Procura também o diretório de includes do ANTLR4 (para que os headers sejam encontrados)
find_path(ANTLR4_INCLUDE_DIR
        NAMES antlr4-runtime.h
        PATH_SUFFIXES antlr4-runtime
        PATHS /usr/include /usr/local/include /opt/homebrew/include
)
if(ANTLR4_INCLUDE_DIR)
    message(STATUS "Diretório de include do ANTLR4 encontrado: ${ANTLR4_INCLUDE_DIR}")
    include_directories(${ANTLR4_INCLUDE_DIR})
else()
    message(WARNING "Diretório de include do ANTLR4 não foi encontrado automaticamente.")
endif()



###############################################################################
# 7. Lista de fontes do projeto
###############################################################################
set(SRC_MAIN
        src/main.cpp
)

set(SRC_COMMON
        src/hlir/scope/Type.cpp
        src/hlir/scope/FunctionArgs.cpp
        src/hlir/scope/Function.cpp
        src/hlir/scope/Variable.cpp
        src/hlir/scope/Operations.cpp
        src/hlir/scope/IFelse.cpp
        src/hlir/scope/ScopeGuard.cpp
        src/scope/ScopeManager.cpp
        src/hlir/generator/Expr.cpp
        src/hlir/generator/Function.cpp
        src/hlir/generator/HLIRGenerator.cpp
        src/hlir/generator/IFelse.cpp
        src/llvm/Types.cpp
        src/llvm/LLVM.cpp
        src/llvm/functions.cpp
        src/llvm/Operations.cpp
        src/llvm/EmitObject.cpp
        src/llvm/LLD.cpp
        src/llvm/VM.cpp
        src/utils/Colors.cpp
        src/semantic/SemanticAnalysis.cpp
        src/semantic/BoolExpr.cpp
        src/semantic/IFElse.cpp
        src/semantic/Functions.cpp
        src/semantic/Expr.cpp
        src/semantic/Extern.cpp
        src/semantic/Format.cpp
        src/parsers/IronLexer.cpp
        src/parsers/IronParser.cpp
        src/parsers/IronBaseListener.cpp
        src/parsers/IronListener.cpp
        src/config/Configuration.cpp
        src/analyser/Analyser.cpp
        src/headers/Analyser.h
        src/utils/Path.cpp
        src/semantic/Loops.cpp
        src/hlir/generator/Loops.cpp
        src/hlir/scope/Statements.cpp
        src/hlir/scope/Utilities.cpp

)

set(TEST_SRC
        tests/test_semantic_analysis.cpp
        tests/test_hlir_code.cpp
        tests/test_llvm_code.cpp
)

# Cópia do arquivo YAML para a pasta de build
configure_file(
        ${CMAKE_SOURCE_DIR}/compiler_config.yaml
        ${CMAKE_BINARY_DIR}/compiler_config.yaml
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/main.iron
        ${CMAKE_BINARY_DIR}/main.iron
        COPYONLY
)




###############################################################################
# 8. Criação dos executáveis e linkagem
###############################################################################
# Executável do programa principal
add_executable(program ${SRC_MAIN} ${SRC_COMMON})
target_link_libraries(program PRIVATE
        ${llvm_libs}         # Bibliotecas do LLVM mapeadas
        ${ANTLR4_LIBRARY}    # Biblioteca do ANTLR4
        yaml-cpp::yaml-cpp   # Imported target do yaml-cpp (cuida dos includes e linkagem)
)

# Executável dos testes
add_executable(test_program ${TEST_SRC} ${SRC_COMMON})
target_link_libraries(test_program PRIVATE
        ${llvm_libs}
        ${ANTLR4_LIBRARY}
        yaml-cpp::yaml-cpp
        GTest::GTest
        GTest::Main
)

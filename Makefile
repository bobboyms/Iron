#################################
# COMPILADOR E FLAGS
#################################
CXX        = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS   = -g -std=c++17 -I/opt/homebrew/opt/llvm/include -O1
LDFLAGS    = -L/opt/homebrew/opt/llvm/lib -lLLVM-19

# Ativa compilação em paralelo com até 6 tarefas
MAKEFLAGS += -j6

#################################
# INCLUDES E BIBLIOTECAS EXTERNAS
#################################
ANTLR_INCLUDES = -I/usr/local/include/antlr4-runtime
ANTLR_LIBS     = /usr/local/lib/libantlr4-runtime.a

GTEST_INCLUDES = -I/opt/homebrew/include
GTEST_LIBS     = -L/opt/homebrew/lib -lgtest -lgtest_main

#################################
# FONTES E ALVOS
#################################
TARGET      = program
TEST_TARGET = test_program

# Fontes do programa principal
SRC_MAIN    = src/main.cpp

# Fontes compartilhadas (antlr, hlir, llvm, etc.)
SRC_COMMON  = src/hlir/Type.cpp \
			  src/hlir/FunctionArgs.cpp \
                    src/hlir/Function.cpp \
                    src/hlir/Variable.cpp \
                    src/hlir/Operations.cpp \
                    src/hlir/HLIRGenerator.cpp \
                    src/scope/ScopeManager.cpp \
              src/llvm/Types.cpp \
              src/llvm/LLVM.cpp \
              src/llvm/Operations.cpp \
              src/hlir/WriterCodeHLIR.cpp \
              src/utils/Colors.cpp \
              src/semantical/SemanticalAnalysis.cpp \
              src/parsers/IronLexer.cpp \
              src/parsers/IronParser.cpp \
              src/parsers/IronBaseListener.cpp \
              src/parsers/IronListener.cpp \
              src/parsers/HightLavelIRLexer.cpp \
              src/parsers/HightLavelIRParser.cpp \
              src/parsers/HightLavelIRBaseListener.cpp \
              src/parsers/HightLavelIRListener.cpp

# Fontes de teste
TEST_SRC    = tests/test_semantical_analysis.cpp tests/test_hlir_code.cpp tests/test_llvm_code.cpp
                        
            #   tests/test_lexer.cpp \
            #   tests/test_hlir_types.cpp \
            #   tests/test_hlir_code.cpp \
			#   tests/test_hlir_function.cpp \
                  #   tests/test_hlir_variable.cpp \
                  #   tests/test_hlir_operation.cpp

#################################
# Geração de listas de objetos
#################################
OBJ_MAIN    = $(SRC_MAIN:.cpp=.o)
OBJ_COMMON  = $(SRC_COMMON:.cpp=.o)
OBJ_TEST    = $(TEST_SRC:.cpp=.o)

#################################
# REGRA PADRÃO: COMPILA TUDO
#################################
all: $(TARGET) $(TEST_TARGET)

#################################
# LINK DO PROGRAMA PRINCIPAL
#################################
$(TARGET): $(OBJ_MAIN) $(OBJ_COMMON)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) $^ -o $@

#################################
# LINK DO PROGRAMA DE TESTE
#################################
$(TEST_TARGET): $(OBJ_TEST) $(OBJ_COMMON)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) \
	       $(GTEST_INCLUDES) $(GTEST_LIBS) $^ -o $@

#################################
# REGRA GERAL PARA COMPILAR .cpp -> .o
#################################
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(ANTLR_INCLUDES) $(GTEST_INCLUDES) -c $< -o $@

#################################
# RODAR PROGRAMA
#################################
run: $(TARGET)
	./$(TARGET)

#################################
# RODAR TESTES
#################################
test: $(TEST_TARGET)
	./$(TEST_TARGET)

#################################
# LIMPEZA
#################################
clean:
	rm -f $(TARGET) $(TEST_TARGET) \
	      $(OBJ_MAIN) $(OBJ_COMMON) $(OBJ_TEST)

# Caminho do compilador e flags
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -g -std=c++17  -I/opt/homebrew/opt/llvm/include -L/opt/homebrew/opt/llvm/lib -lLLVM-19

# -fsanitize=address,undefined -fno-omit-frame-pointer
# 
ANTLR_INCLUDES = -I/usr/local/include/antlr4-runtime  # Headers do runtime ANTLR
ANTLR_LIBS = /usr/local/lib/libantlr4-runtime.a       # Biblioteca estática do runtime ANTLR

# Caminhos do Google Test instalados via Homebrew
GTEST_INCLUDES = -I/opt/homebrew/include
GTEST_LIBS = -L/opt/homebrew/lib -lgtest -lgtest_main

# Nome do executável e arquivo fonte
TARGET = program 
SRC = src/main.cpp
TEST_TARGET = test_program
TEST_SRC = tests/test_semantical_analysis.cpp tests/test_lexer.cpp tests/test_hlir.cpp

ANTLR_CPP = src/WriterCodeHLIR.cpp src/Colors.cpp src/ScopeManager.cpp src/HighLevelIR.cpp src/SemanticalAnalysis.cpp src/parsers/IronLexer.cpp src/parsers/IronParser.cpp src/parsers/IronBaseListener.cpp src/parsers/IronListener.cpp

# Alvo padrão: compilar o programa
all: $(TARGET) $(TEST_TARGET)

# Regra para compilar o programa principal com linkagem estática do ANTLR
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) $(SRC) $(ANTLR_CPP) -o $(TARGET)

# Regra para compilar o programa de testes
$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) $(GTEST_INCLUDES) $(GTEST_LIBS) $(TEST_SRC) $(ANTLR_CPP) -o $(TEST_TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)
#	rm -f $(TARGET) 

# Regra para executar os testes
test: $(TEST_TARGET)
	./$(TEST_TARGET)
	rm -f $(TEST_TARGET)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET) $(TEST_TARGET)
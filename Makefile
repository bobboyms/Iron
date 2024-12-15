# Caminho do compilador e flags
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -g -std=c++17 -I/opt/homebrew/opt/llvm/include -L/opt/homebrew/opt/llvm/lib -lLLVM-19
ANTLR_INCLUDES = -I/usr/local/include/antlr4-runtime  # Headers do runtime ANTLR
ANTLR_LIBS = /usr/local/lib/libantlr4-runtime.a       # Biblioteca estática do runtime ANTLR

# Caminhos do Google Test instalados via Homebrew
GTEST_INCLUDES = -I/opt/homebrew/include
GTEST_LIBS = -L/opt/homebrew/lib -lgtest -lgtest_main

# Nome do executável e arquivo fonte
TARGET = program
SRC = main.cpp
TEST_TARGET = test_program
TEST_SRC = tests/test_lexer.cpp tests/test_var_parser.cpp
# Arquivos .cpp gerados pelo ANTLR4

# 
ANTLR_CPP = parsers/IronLexer.cpp parsers/IronParser.cpp parsers/IronBaseListener.cpp parsers/IronListener.cpp

# Alvo padrão: compilar o programa
all: $(TARGET) $(TEST_TARGET)

# Regra para compilar o programa principal com linkagem estática do ANTLR
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) $(SRC) $(ANTLR_CPP) -o $(TARGET)

# Regra para compilar o programa de testes
$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) $(GTEST_INCLUDES) $(GTEST_LIBS) $(TEST_SRC) $(ANTLR_CPP) -o $(TEST_TARGET)
	./$(TEST_TARGET)
	rm -f $(TEST_TARGET)


# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para executar os testes
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET) $(TEST_TARGET)
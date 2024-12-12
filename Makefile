# Caminho do compilador e flags
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -g -I/opt/homebrew/opt/llvm/include -L/opt/homebrew/opt/llvm/lib -lLLVM-19
ANTLR_INCLUDES = -I/usr/local/include/antlr4-runtime  # Headers do runtime ANTLR
ANTLR_LIBS = /usr/local/lib/libantlr4-runtime.a       # Biblioteca estática do runtime ANTLR

# Nome do executável e arquivo fonte
TARGET = program
SRC = main.cpp

# Alvo padrão: compilar o programa
all: $(TARGET)

# Regra para compilar o programa com linkagem estática do ANTLR
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(ANTLR_INCLUDES) $(ANTLR_LIBS) $(SRC) -o $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)

# Makefile para compilar soma.ll usando clang

# Variáveis
CLANG = /opt/homebrew/opt/llvm/bin/clang++
LLVM_IR = program.ll
EXECUTABLE = program

# Target padrão
all: $(EXECUTABLE)

# Regra para compilar o LLVM IR em um executável
$(EXECUTABLE): $(LLVM_IR)
	$(CLANG) $(LLVM_IR) -o $(EXECUTABLE)

# Regra para limpar os arquivos gerados
clean:
	rm -f $(EXECUTABLE)

# Declaração de targets que não correspondem a arquivos
.PHONY: all clean

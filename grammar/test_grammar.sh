#!/bin/bash

# Configura o ambiente para ANTLR4 e GRUN
export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"
alias antlr4="java -Xmx500M -cp \"/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH\" org.antlr.v4.Tool"
alias grun="java -Xmx500M -cp \"/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH\" org.antlr.v4.gui.TestRig"

# Aplica os aliases no ambiente atual
shopt -s expand_aliases

# Verifica se antlr4 e grun estão configurados corretamente
echo "Verificando configuração de antlr4 e grun..."
if ! command -v antlr4 &> /dev/null || ! command -v grun &> /dev/null; then
    echo "Os comandos antlr4 ou grun não foram configurados corretamente."
    exit 1
fi

# Executa os comandos especificados
antlr4 Iron.g4
if [ $? -ne 0 ]; then
    echo "Erro ao executar antlr4."
    exit 1
fi

javac Iron*.java
if [ $? -ne 0 ]; then
    echo "Erro ao compilar arquivos Java."
    exit 1
fi

grun Iron program -gui < variables.txt
if [ $? -ne 0 ]; then
    echo "Erro ao executar grun."
    exit 1
fi

# Sucesso
echo "Script executado com sucesso!"

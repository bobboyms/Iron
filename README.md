# Configurando o Ambiente de Desenvolvimento no macOS (LLVM, Clang++, ANTLR e VSCode)

Este guia irá ajudá-lo a configurar seu ambiente de desenvolvimento no macOS para compilar e depurar projetos em C++ que utilizam LLVM, Clang++ e a runtime C++ do ANTLR. Além disso, mostra como configurar o VSCode para fornecer autocompletar, linting, depuração e outras funcionalidades úteis.

## Pré-requisitos

- **Homebrew** instalado: Caso não tenha, siga as instruções no site oficial ([https://brew.sh/](https://brew.sh/)) para instalar.
- **Python 3** instalado (geralmente já vem no macOS, mas você pode instalar/atualizar via Homebrew).

---

## Passo 1: Instalar LLVM (inclui Clang++)

1. Abra o Terminal.
2. Instale o LLVM via Homebrew:
   ```bash
   brew install llvm
   ```
   
   Isso instalará o LLVM e o clang++ em `/opt/homebrew/opt/llvm`.

3. Para que o sistema encontre o clang++ instalado pelo LLVM (ao invés do clang padrão do macOS), adicione as ferramentas ao seu PATH. No caso do shell Zsh (padrão no macOS atuais):

   ```bash
   echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
   export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
   export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
   ```
   
   Em seguida, recarregue o arquivo de configuração do seu shell:
   ```bash
   source ~/.zshrc
   ```

4. Teste se o LLVM foi instalado corretamente:
   ```bash
   llvm-config --version
   ```
   
   Você deve ver a versão do LLVM instalada.

---

## Passo 2: Instalar e Configurar o ANTLR

O ANTLR é uma ferramenta para geração de analisadores léxicos e sintáticos a partir de gramáticas. Usaremos o ANTLR para gerar código C++ a partir de uma gramática `.g4` e também sua runtime C++.

### 2.1 Instalar o ANTLR4 (para gerar código)

1. Faça o download do ANTLR:
   ```bash
   cd /usr/local/lib
   sudo curl -O https://www.antlr.org/download/antlr-4.13.2-complete.jar
   ```
   
2. Instale a ferramenta do ANTLR4 (Python):
   ```bash
   echo 'export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"' >> ~/.zshrc
   echo 'alias antlr4="java -Xmx500M -cp \"/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH\" org.antlr.v4.Tool"' >> ~/.zshrc
   echo 'alias grun="java -Xmx500M -cp \"/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH\" org.antlr.v4.gui.TestRig"' >> ~/.zshrc
   ```

   Em seguida, recarregue o arquivo de configuração do seu shell:
   ```bash
   source ~/.zshrc
   ```

3. Testar a instalação

  ```bash
      antlr4 Expr.g4
      javac Expr*.java
   ```

   ```bash
      grun Expr expr -gui < input.txt
   ```

   ```bash
      grun Expr expr -tree < input.txt
   ```

   ```bash
      grun Expr expr -tokens < input.txt
   ```

### 2.2 Instalar a Runtime C++ do ANTLR

1. Obtenha o código-fonte do ANTLR a partir do GitHub:
   ```bash
   git clone https://github.com/antlr/antlr4.git
   ```
   
2. Vá para o diretório da runtime C++:
   ```bash
   cd antlr4/runtime/Cpp
   ```
   
3. Crie um diretório de build (opcional, mas organizado):
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++ -DCMAKE_INSTALL_PREFIX=/usr/local
   ```
   
   **O que este comando faz?**
   - `-DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++` garante que a compilação use o clang++ do LLVM instalado.
   - `-DCMAKE_INSTALL_PREFIX=/usr/local` definirá onde a runtime será instalada.
   
4. Compile e instale:
   ```bash
   make
   sudo make install
   ```
   
5. Verifique a instalação da runtime:
   ```bash
   ls /usr/local/include/antlr4-runtime
   ```
   
   Se aparecerem arquivos header do ANTLR4, a instalação foi bem-sucedida.

---

## Passo 3: Gerando Código C++ a partir de Gramáticas ANTLR

Sempre que você tiver um arquivo de gramática, por exemplo `MyGrammar.g4`, poderá gerar código C++ com o comando:

```bash
antlr4 -Dlanguage=Cpp -o ./src/parsers Iron.g4

antlr4 -Dlanguage=Cpp -o ./src/parsers HightLavelIR.g4
```

Isso criará arquivos `.h` e `.cpp` correspondentes à sua gramática. Lembre-se de executar este comando dentro do ambiente virtual (caso esteja usando o `venv`).

---

## Passo 4: Configurando o Visual Studio Code

O VSCode é um editor moderno que, com a configuração adequada, pode oferecer autocompletar, highlight, linting e depuração para C++ usando clang++, LLVM e o ANTLR runtime.

### 4.1 Instalar Extensões VSCode

Abra o VSCode e instale as seguintes extensões:

- **ANTLR4 grammar syntax support:** Fornece highlight para gramáticas ANTLR.
- **C/C++ Extension Pack:** Pacote de extensões que adiciona IntelliSense, debug e outras funcionalidades para C/C++.
- **CMake:** Facilita a integração com projetos baseados em CMake (opcional, mas útil).

### 4.2 Arquivo `c_cpp_properties.json`

Crie ou edite o arquivo `.vscode/c_cpp_properties.json` no seu projeto. Esse arquivo orienta o IntelliSense sobre onde encontrar headers:

```json
{
    "configurations": [
      {
        "name": "Mac",
        "includePath": [
          "${workspaceFolder}/**",
          "/usr/local/include/antlr4-runtime",
          "/opt/homebrew/opt/llvm/include"
        ],
        "defines": [
          "__STDC_CONSTANT_MACROS",
          "__STDC_FORMAT_MACROS",
          "__STDC_LIMIT_MACROS"
        ],
        "macFrameworkPath": [
          "/System/Library/Frameworks",
          "/Library/Frameworks"
        ],
        "compilerPath": "/opt/homebrew/opt/llvm/bin/clang++",
        "cStandard": "c17",
        "cppStandard": "c++17",
        "intelliSenseMode": "macos-clang-x64",
        "browse": {
          "path": [
            "${workspaceFolder}",
            "/opt/homebrew/opt/llvm/include",
            "/usr/local/include/antlr4-runtime"
          ],
          "limitSymbolsToIncludedHeaders": true
        }
      }
    ],
    "version": 4
}
```

**O que este arquivo faz?**  
- Define quais diretórios serão usados pelo IntelliSense para encontrar cabeçalhos (headers) do LLVM e do ANTLR.
- Especifica qual compilador será usado para análise (clang++ do LLVM).
- Ajusta o padrão de C/C++ (c17, c++17).

### 4.3 Arquivo `launch.json` (Depuração)

O `launch.json` define como o VSCode irá executar e depurar seu programa em C++.

Crie ou edite `.vscode/launch.json`:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Depuração: clang++",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "lldb",
            "setupCommands": [
                {
                    "description": "Habilita formatação de valores no depurador",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

**O que este arquivo faz?**  
- Configura o uso do LLDB (depurador nativo do macOS).
- Determina qual executável será rodado e onde.
- Habilita a formatação amigável de variáveis no depurador.

### 4.4 Arquivo `tasks.json` (Compilação)

O `tasks.json` define como o VSCode compilará seu arquivo quando você pressionar `Ctrl+Shift+B` (ou `Cmd+Shift+B` no Mac).

Crie ou edite `.vscode/tasks.json`:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: clang++ (LLVM)",
            "command": "/opt/homebrew/opt/llvm/bin/clang++",
            "args": [
                "-fcolor-diagnostics",
                "-fansi-escape-codes",
                "-g",                             // Ativa informações de depuração
                "${file}",                        // Arquivo sendo editado atualmente
                "-o",                             // Saída do executável
                "${fileDirname}/${fileBasenameNoExtension}",
                "-I/opt/homebrew/opt/llvm/include",   // Inclui headers do LLVM
                "-I/usr/local/include/antlr4-runtime", // Inclui headers do ANTLR runtime
                "-L/opt/homebrew/opt/llvm/lib",       // Biblioteca do LLVM
                "-lLLVM-19"                           // Ajuste conforme a versão do LLVM instalada
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": ["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Compilação com Clang++ e LLVM"
        }
    ]
}
```

**O que este arquivo faz?**  
- Usa o clang++ do LLVM para compilar.
- Inclui caminhos para os headers do LLVM e do ANTLR.
- Linka com a biblioteca principal do LLVM (verifique o nome da lib com `llvm-config --libs` se necessário).
- Gera um executável com nome igual ao do arquivo fonte atual (sem extensão).

---

## Considerações Finais

- Caso encontre problemas com a biblioteca do LLVM (por exemplo, `-lLLVM-19` não existir), verifique o nome da biblioteca com:
  ```bash
  llvm-config --libs
  ```
  Ajuste o `tasks.json` de acordo.
  
- Para atualizar as variáveis de ambiente no futuro, lembre-se de editar o `~/.zshrc` e executar `source ~/.zshrc`.

- Se usar outro shell (bash, fish), ajuste o procedimento de acordo com o shell.

Com esses passos, você deve ter um ambiente de desenvolvimento funcional no macOS, pronto para trabalhar com C++, LLVM, Clang++ e ANTLR no VSCode.


echo 'export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"' >> ~/.zshrc


alias antlr4='java -Xmx500M -cp "/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH" org.antlr.v4.Tool'
alias grun='java -Xmx500M -cp "/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH" org.antlr.v4.gui.TestRig'



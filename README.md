Segue abaixo a documentação completa revisada, incorporando as correções solicitadas:

---

# Configurando o Ambiente de Desenvolvimento no macOS (LLVM, Clang++, ANTLR e VSCode)

Este guia auxiliará na configuração do ambiente de desenvolvimento no macOS para compilar e depurar projetos em C++ utilizando LLVM, Clang++ e a runtime C++ do ANTLR. Além disso, ele demonstra como configurar o Visual Studio Code para oferecer recursos como autocompletar, linting e depuração.

---

## Pré-requisitos

- **Homebrew** instalado: Caso não possua, siga as instruções no site oficial ([https://brew.sh/](https://brew.sh/)).
- **Python 3** instalado (geralmente já vem no macOS, mas você pode instalar ou atualizar via Homebrew).
- **Java Development Kit (JDK)** instalado:  
  O ANTLR necessita do Java para ser executado. Se necessário, instale-o via Homebrew:
  ```bash
  brew install openjdk
  ```
  ou utilize outro método de sua preferência.

---

## Passo 1: Instalar o LLVM (inclui Clang++)

1. **Abra o Terminal.**

2. **Instale o LLVM via Homebrew:**
   ```bash
   brew install llvm
   brew install lld
   ```
   **Observação:**
   - Em Macs com chip Apple Silicon, o LLVM é instalado em `/opt/homebrew/opt/llvm`;
   - Em Macs Intel, o caminho normalmente é `/usr/local/opt/llvm`.  
     Para confirmar o caminho, execute:
   ```bash
   brew --prefix llvm
   ```
   https://releases.llvm.org/download.html

3. **Configure o PATH e defina variáveis de ambiente:**  
   Para que o sistema utilize o `clang++` instalado pelo LLVM e para que os compiladores encontrem os headers e bibliotecas do LLVM, adicione as seguintes linhas ao arquivo de configuração do seu shell (por exemplo, `~/.zshrc` se você utiliza Zsh):

   ```bash
   export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
   export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
   export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
   ```
   *Ajuste os caminhos se o LLVM estiver instalado em outro diretório (como `/usr/local/opt/llvm`).*

   Em seguida, recarregue as configurações:
   ```bash
   source ~/.zshrc
   ```

4. **Teste a instalação do LLVM:**
   ```bash
   llvm-config --version
   ```
   Você deverá visualizar a versão do LLVM instalada.

---

## Passo 2: Instalar e Configurar o ANTLR

O ANTLR é uma ferramenta para gerar analisadores léxicos e sintáticos a partir de gramáticas. Neste guia, usaremos o ANTLR para gerar código C++ a partir de arquivos `.g4` e para utilizar sua runtime C++.

### 2.1 Instalar o ANTLR4 (para geração de código)

1. **Faça o download do ANTLR:**
   ```bash
   cd /usr/local/lib
   sudo curl -O https://www.antlr.org/download/antlr-4.13.2-complete.jar
   ```

2. **Configure o CLASSPATH e defina os aliases:**  
   Adicione as seguintes linhas ao seu arquivo de configuração (por exemplo, `~/.zshrc`):

   ```bash
   export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"
   alias antlr4='java -Xmx500M -cp "/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH" org.antlr.v4.Tool'
   alias grun='java -Xmx500M -cp "/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH" org.antlr.v4.gui.TestRig'
   ```

   Recarregue as configurações:
   ```bash
   source ~/.zshrc
   ```

3. **Teste a instalação com um exemplo:**  
   Suponha que você possua um arquivo de gramática, como `Expr.g4`. Execute:
   ```bash
   antlr4 Expr.g4
   javac Expr*.java
   ```
   Para testar, utilize um arquivo de entrada (por exemplo, `input.txt`):
   ```bash
   grun Expr expr -gui < input.txt
   grun Expr expr -tree < input.txt
   grun Expr expr -tokens < input.txt
   ```

### 2.2 Instalar a Runtime C++ do ANTLR

Utilize o Homebrew para instalar a runtime C++:
```bash
brew install antlr4-cpp-runtime
```

---

## Passo 3: Instalar Bibliotecas Adicionais

Instale as bibliotecas necessárias para o projeto:

- **GoogleTest:**
  ```bash
  brew install googletest
  ```
- **yaml-cpp:**
  ```bash
  brew install yaml-cpp
  ```

---

## Passo 4: Gerar Código C++ a partir de Gramáticas ANTLR

Sempre que você tiver um arquivo de gramática, por exemplo, `MyGrammar.g4`, poderá gerar o código C++ correspondente com o comando:

```bash
antlr4 -Dlanguage=Cpp -o ./src/parsers MyGrammar.g4
```

Para múltiplas gramáticas, por exemplo:
```bash
antlr4 -Dlanguage=Cpp -o ./src/parsers Iron.g4
antlr4 -Dlanguage=Cpp -o ./src/parsers HighLevelIR.g4
```
*Certifique-se de que os nomes dos arquivos estejam corretos (por exemplo, utilize `HighLevelIR.g4` e não “HightLavelIR.g4”).*

---

## Passo 5: Configurar o Visual Studio Code

O VSCode pode ser configurado para oferecer recursos como autocompletar, realce de sintaxe, linting e depuração para C++ utilizando clang++, LLVM e a runtime do ANTLR.

### 5.1 Instalar Extensões no VSCode

No VSCode, instale as seguintes extensões:

- **ANTLR4 grammar syntax support:** Para realce de sintaxe em gramáticas ANTLR.
- **C/C++ Extension Pack:** Conjunto de extensões que adiciona IntelliSense, depuração e outras funcionalidades para C/C++.
- **CMake:** (Opcional) Facilita a integração com projetos baseados em CMake.

### 5.2 Configurar o IntelliSense (`c_cpp_properties.json`)

Crie ou edite o arquivo `.vscode/c_cpp_properties.json` no seu projeto:

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
*Ajuste os caminhos se o LLVM estiver instalado em outro diretório.*

### 5.3 Configurar a Depuração (`launch.json`)

Crie ou edite o arquivo `.vscode/launch.json`:

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
          "description": "Habilitar formatação amigável de variáveis",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    }
  ]
}
```

### 5.4 Configurar a Compilação (`tasks.json`)

Crie ou edite o arquivo `.vscode/tasks.json`:

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
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}",
        "-I/opt/homebrew/opt/llvm/include",
        "-I/usr/local/include/antlr4-runtime",
        "-L/opt/homebrew/opt/llvm/lib",
        "-lLLVM-19"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "Compilação utilizando Clang++ e LLVM"
    }
  ]
}
```
*Observação:* Caso a versão do LLVM seja diferente, verifique-a com `llvm-config --libs` e ajuste o parâmetro de link (`-lLLVM-19`) conforme necessário.

---

## Considerações Finais

- Se houver problemas com a biblioteca do LLVM (por exemplo, se `-lLLVM-19` não corresponder à versão instalada), verifique o nome da biblioteca com:
  ```bash
  llvm-config --libs
  ```
  e ajuste o `tasks.json` conforme necessário.
- Se utilizar outro shell (como bash ou fish), adapte os comandos de configuração (PATH, CLASSPATH, aliases) para o respectivo arquivo de configuração.
- Mantenha esta documentação atualizada, verificando periodicamente se as versões das ferramentas (LLVM, ANTLR, etc.) sofreram alterações que possam impactar as instruções.


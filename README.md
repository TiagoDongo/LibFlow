# Library-Management

É um sistema de gerenciamento de biblioteca que permite cadastrar, buscar, atualizar e remover livros e usuários, além de salvar e carregar listas em formato JSON. O projeto é implementado em C com suporte a manipulação de arquivos JSON utilizando a biblioteca `cJSON`.

## Estrutura do Projeto

- **public/**: Contém o arquivo principal (`main.c`) e os módulos do sistema.
- **src/**: Contém os cabeçalhos e definições de estruturas e funções.
- **data/**: Diretório onde são armazenados os arquivos JSON gerados.
- **scripts/**: Scripts em Python para geração de dados aleatórios e análise de dados.

## ⚙ Pré-requisitos

- **Windows**:
  - Instale o [MinGW](https://sourceforge.net/projects/mingw/) para compilar o código.
  - Adicione o `gcc` ao PATH do sistema.
  - `Opcional`: duplique o executavel mingw32_make e o renomeio para `make`

- **Linux**:
  - Certifique-se de que o GCC está instalado:
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
- **Execução dos scripts python**:
  - Faker (para geração de dados aleatórios)
    ```bash
    pip install faker 
    ```

## 🚀Instalação

1. Clone este repositório:
   ```bash
   git clone https://github.com/TiagoDongo/Library-Management.git
   ```

2. Navegue até o diretório do projeto:
    ```bash
   cd Library-Management
   ```

3. Compile o projeto:
   - Linux
    ```bash
    make
    ```

    - Windows
    ```bash
    mingw32_make
    ```

4. Execute o projeto:
   - Linux
    ```bash
    make run
    ```

    - Windows
    ```bash
    mingw32_make run
    ```

5. Caso de duvidas execute o comando:
   - Linux
    ```bash
    make help
    ```

    - Windows
    ```bash
    mingw32_make help
    ```
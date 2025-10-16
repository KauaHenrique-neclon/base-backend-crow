## Projeto Web em C++ com Crow e PostgreSQL

Este projeto é uma aplicação web desenvolvida em C++ utilizando o microframework [Crow](https://github.com/CrowCpp/crow) para o backend e a biblioteca [libpqxx](https://github.com/jtv/libpqxx) para comunicação com o banco de dados PostgreSQL.

### 🧱 Estrutura do Projeto

pasta_raiz/
├── main.cpp    # Arquivo principal da aplicação
├── views/
│ └── login/
│ ├── login.hpp      # Header das rotas de login
│ └── loginViews.cpp      # Implementação das rotas de login
├── models/
│ └── login/
│ └── loginModel.cpp     # Operações com banco de dados para login
├── static/         # Arquivos estáticos (CSS, JS, imagens)
├── templates/      # Arquivos HTML (templating)
│ └── login.html
├── erro.txt        # Arquivo gerado em caso de erro
└── output/
└── main.exe        # Executável gerado após compilação

### ⚙️ Requisitos

- **g++** com suporte a C++17
- **Crow** (copie ou instale os headers em `include/crow`)
- **libpqxx** (instalada via MSYS2 ou seu gerenciador de pacotes preferido)
- **PostgreSQL** rodando e acessível com as credenciais fornecidas

### 🔧 Compilação

Você pode compilar seu projeto com o seguinte comando:


g++ -std=c++17 -o "c:/pasta_raiz/output/main.exe" \
    "C:/pasta_raiz/main.cpp" \
    "c:/pasta_raiz/views/login/loginViews.cpp" \
    "c:/pasta_raiz/models/login/loginModel.cpp" \
    -I"C:/msys64/mingw64/include" \
    -I"C:/msys64/mingw64/include/crow" \
    -lpqxx -lpq

### 🚀 Executando

Após a compilação, execute o binário:

./output/main.exe


O servidor irá iniciar na porta 18080:

http://localhost:18080/

### 🔌 Configuração da Conexão com Banco de Dados

No arquivo main.cpp, altere a CONNECTION_STRING com suas credenciais do PostgreSQL:

const std::string CONNECTION_STRING = "dbname=db user=user password=senha host=host port=5432";

### 📄 Funcionalidades

Roteamento modular com Blueprints do Crow

View login com separação MVC (Model-View-Controller)

Conexão com PostgreSQL usando libpqxx

Tratamento de erros com logging em erro.txt

### 🧪 Testes

Por enquanto, testes manuais via browser ou ferramentas como curl, Postman, etc.

### 📝 Licença

Este projeto é livre para uso pessoal e educacional

Desenvolvido com ❤️ em C++

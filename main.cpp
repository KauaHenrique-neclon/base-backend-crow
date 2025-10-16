#include <iostream>
#include <fstream>
#include <crow.h>
#include <pqxx/pqxx>

// importando suas views
#include "views/login/login.hpp"


const std::string CONNECTION_STRING = "dbname=db user=user password=senha host=host port=5432"; 



int main() {
    pqxx::connection* conn_ptr = nullptr;
    
    try{
        crow::SimpleApp app;
        
        // conexão com o banco de dados
        pqxx::connection conn(CONNECTION_STRING);
        conn_ptr = &conn;
        if (!conn_ptr->is_open()) {
             throw std::runtime_error("Não foi possível abrir a conexão com o banco de dados.");
        }

        // criando os blueprints
        crow::Blueprint login("login", "C:/pasta_raiz/static" ,"C:/pasta_raiz/templates");
        std::cout << "Caminho do template: " << "C:/pasta_raiz/templates/login.html" << std::endl;
        Login loginRoute;
        loginRoute.set_conn(conn_ptr);
        loginRoute.definirRotas(login);


        // regristando os blueprint
        app.register_blueprint(login);
        app.port(18080).run();

    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        std::ofstream erroArquivo("erro.txt");
        if (erroArquivo.is_open()) {
            erroArquivo << "Erro: " << e.what() << std::endl;
            erroArquivo.close();
            std::cerr << "Erro gravado em erro.txt" << std::endl;
        } else {
            std::cerr << "Erro ao abrir arquivo de erro: " << e.what() << std::endl;
        }
    }
    return 0;
}

// g++ -std=c++17 -o  "c:/pasta_raiz/output/main.exe" "C:/pasta_raiz/main.cpp" "c:/pasta_raiz/views/login/loginViews.cpp" "c:/pasta_raiz/models/login/loginModel.cpp"  -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/crow" -lpqxx -lpq
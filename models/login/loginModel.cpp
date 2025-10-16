#include "LoginModel.hpp"
#include <sstream>

void logError(const std::string& message) {
    std::ofstream errorLog("error_log.txt", std::ios::app);
    if (errorLog.is_open()) {
        errorLog << message << std::endl;
        errorLog.close();
    } else {
        std::cerr << "Não foi possível abrir o arquivo de log." << std::endl;
    }
}


LoginModel::LoginModel(std::string username, std::string password, pqxx::connection* db_conn)
    : username(std::move(username)), password(std::move(password)), conn(db_conn) {
    if (!conn) {
        logError("LoginModel constructed with a NULL pqxx::connection pointer.");
    }
    std::cerr << "LoginModel inicializado." << std::endl;
}


std::string LoginModel::getUsername() const { return username; }
std::string LoginModel::getPassword() const { return password; }

crow::response LoginModel::authenticate(pqxx::connection* db_conn) {
    pqxx::connection* ativo_conn = db_conn;
    
    if (ativo_conn == nullptr) {
        logError("Authenticate called with a NULL database connection.");
        return crow::response(500, "Erro interno: Conexão com o BD não estabelecida.");
    }

    if (username.empty() || password.empty() || username.size() > 256 || password.size() > 256) {
        return crow::response(400, "Usuário ou senha muito longos ou vazios.");
    }

    try {
        std::cerr << "Preparando e executando a Query (pqxx::work)" << std::endl;

        pqxx::work W(*ativo_conn);

        pqxx::result R = W.exec_params(
            "SELECT nome FROM usuarios WHERE username = $1 AND password = $2",
            username, 
            password
        );

        std::cerr << "Resultado verificado" << std::endl;
        
        if (R.size() == 1) {
            std::cerr << "Login bem-sucedido para o usuário: " << R[0][0].as<std::string>() << std::endl;
            return crow::response(200);
        } else {
            std::cerr << "Usuário ou senha inválidos. Rows returned: " << R.size() << std::endl;
            return crow::response(401, "Usuário ou senha inválidos.");
        }
        
    } catch (const pqxx::sql_error &e) {
        std::string msg = "SQL Error: " + std::string(e.what()) + ". Query was: " + e.query();
        logError(msg);
        return crow::response(500, crow::json::wvalue{{"error", "Erro de banco de dados: " + std::string(e.what())}});
    } catch (const std::exception &e) {
        logError("Erro inesperado: " + std::string(e.what()));
        return crow::response(500, crow::json::wvalue{{"error", "Erro inesperado: " + std::string(e.what())}});
    }
}
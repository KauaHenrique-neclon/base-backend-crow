#include "login.hpp"

Login::Login() {}

void Login::definirRotas(crow::Blueprint& login) {
    CROW_BP_ROUTE(login,"/").methods("GET"_method)([this](const crow::request& req) {
        return get(req);
    });
    CROW_BP_ROUTE(login, "/").methods("POST"_method)([this](const crow::request& req) {
        return post(req);
    });
}

crow::response Login::get(const crow::request& req) {
    crow::mustache::context ctx;
    try {
        auto rendered = crow::mustache::load("login.html").render(ctx);
        return crow::response(200, rendered);
    } catch (const std::exception& e) {
        return crow::response(500, "Erro ao carregar o pagina " + std::string(e.what()));
    }
}


std::map<std::string, std::string> parse_urlencoded(const std::string& body) {
    std::map<std::string, std::string> params;
    std::stringstream ss(body);
    std::string item;

    while (std::getline(ss, item, '&')) {
        auto pos = item.find('=');
        if (pos != std::string::npos) {
            std::string key = item.substr(0, pos);
            std::string value = item.substr(pos + 1);
            params[key] = value;
        }
    }
    return params;
}


crow::response Login::post(const crow::request& req) {
    try{
        std::cerr << "Requisição: " << req.body << std::endl;

        std::string body = req.body;

        if (body.empty()) {
            return crow::response(400, "Corpo da requisição vazio.");
        }

        std::map<std::string, std::string> params = parse_urlencoded(body);

        std::string username = params.count("username") ? params["username"] : "";
        std::string password = params.count("password") ? params["password"] : "";

        std::cerr << "Username: " << username << ", Password: " << password << std::endl;

        if (username.empty() || password.empty()) {
            return crow::response(400, "Preencha os dados");
        }

        if (conn == nullptr) {
            return crow::response(500, "Erro de conexão com o banco de dados");
        }

        LoginModel loginModel(username, password, conn);
        crow::response response = loginModel.authenticate(conn);
        std::cerr << "depois do authenticar" << std::endl;
        
        if(response.code == 200){
            response.code = 302; 
            response.add_header("Location", "/home/home");
            return response;
        }else{
            return crow::response(400, "Acesso negado");
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return crow::response(500, "Erro interno do servidor");
    }
}
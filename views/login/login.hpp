#ifndef LOGINVIEWS_HPP
#define LOGIN_HPP

#include <crow.h>
#include <pqxx/pqxx>
#include <iostream>
#include <sstream>
#include <map>
#include "../../models/login/loginModel.hpp"

class Login {
public:
    Login();

    void set_conn(pqxx::connection* new_conn) {
        conn = new_conn;
    }
    void definirRotas(crow::Blueprint& login);


private:
    pqxx::connection* conn = nullptr;
    crow::response get(const crow::request& req);
    crow::response post(const crow::request& req);
};


#endif // LOGIN_HPP
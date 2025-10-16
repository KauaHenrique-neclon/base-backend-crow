#ifndef LOGINMODEL_HPP
#define LOGINMODEL_HPP

#include <string>
#include <crow.h>
#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
// #include <bcrypt/BCrypt.hpp>

class LoginModel {
private:
    std::string username;
    std::string password;
    pqxx::connection* conn;

public:

    LoginModel(std::string username, std::string password, pqxx::connection* db_conn);

    std::string getUsername() const;
    std::string getPassword() const;

    crow::response authenticate(pqxx::connection* db_conn);
};

#endif // LOGINMODEL_HPP
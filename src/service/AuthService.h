#pragma once

#include <string>

class AuthService
{
public:
    std::string hashPassword(const std::string& password);

    bool verifyPassword(const std::string& password,
                        const std::string& passwordHash);

    bool login(const std::string& email,
               const std::string& password);
};
#pragma once

#include <string>
#include <optional>

#include "../model/User.h"

class UserRepository
{
public:
    bool userExists(const std::string& email);

    bool registerUser(
        const std::string& name,
        const std::string& email,
        const std::string& passwordHash,
        const std::string& role
    );

    std::string getPasswordHash(
        const std::string& email
    );

    std::optional<User> getUserByEmail(
        const std::string& email
    );
};
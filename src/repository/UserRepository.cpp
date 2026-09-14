#include "UserRepository.h"
#include <drogon/drogon.h>

bool UserRepository::userExists(const std::string& email)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id FROM users WHERE email = $1",
            email
        );

        return !result.empty();
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool UserRepository::registerUser(
    const std::string& name,
    const std::string& email,
    const std::string& passwordHash,
    const std::string& role)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "INSERT INTO users (name, email, password_hash, role) "
            "VALUES ($1, $2, $3, $4)",
            name,
            email,
            passwordHash,
            role
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

std::string UserRepository::getPasswordHash(const std::string& email)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT password_hash FROM users WHERE email = $1",
            email
        );

        if (!result.empty())
        {
            return result[0]["password_hash"].as<std::string>();
        }
    }
    catch (const std::exception&)
    {
    }

    return "";
}
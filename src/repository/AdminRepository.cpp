#include "AdminRepository.h"
#include <drogon/drogon.h>

std::vector<User> AdminRepository::getAllUsers()
{
    std::vector<User> users;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, name, email, password_hash, role "
            "FROM users "
            "ORDER BY id"
        );

        for (const auto& row : result)
        {
            User user;

            user.id = row["id"].as<int>();
            user.name = row["name"].as<std::string>();
            user.email = row["email"].as<std::string>();
            user.password_hash =
                row["password_hash"].as<std::string>();
            user.role = row["role"].as<std::string>();

            users.push_back(user);
        }
    }
    catch (const std::exception&)
    {
    }

    return users;
}

bool AdminRepository::deleteUser(int userId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "DELETE FROM users WHERE id = $1::integer",
            std::to_string(userId)
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
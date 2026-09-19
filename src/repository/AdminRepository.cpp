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

            user.role =
                row["role"].as<std::string>();

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
        auto result = client->execSqlSync(
            "DELETE FROM users "
            "WHERE id = $1::integer",
            std::to_string(userId)
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

std::vector<Order> AdminRepository::getAllOrders()
{
    std::vector<Order> orders;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, buyer_id, status, total_amount_cents "
            "FROM orders "
            "ORDER BY id DESC"
        );

        for (const auto& row : result)
        {
            Order order;

            order.id =
                row["id"].as<int>();

            order.buyer_id =
                row["buyer_id"].as<int>();

            order.status =
                row["status"].as<std::string>();

            order.total_amount_cents =
                row["total_amount_cents"].as<long long>();

            orders.push_back(order);
        }
    }
    catch (const std::exception&)
    {
    }

    return orders;
}

bool AdminRepository::deleteProduct(int productId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "DELETE FROM products "
            "WHERE id = $1::integer",
            std::to_string(productId)
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
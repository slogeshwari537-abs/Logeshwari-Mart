#include "AdminRepository.h"

#include <drogon/drogon.h>
#include <iostream>

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
    catch (const std::exception& e)
    {
        std::cerr << "Admin getAllProducts error: " << e.what() << std::endl;
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
    catch (const std::exception& e)
    {
        std::cerr << "Admin getAllProducts error: " << e.what() << std::endl;
    }

    return orders;
}

std::vector<Product> AdminRepository::getAllProducts()
{
    std::vector<Product> products;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, seller_id, name, description, "
            "price_cents, stock_qty, category, image_url, is_active "
            "FROM products "
            "ORDER BY id DESC"
        );

        for (const auto& row : result)
        {
            Product product;

            product.id = row["id"].as<int>();
            product.seller_id = row["seller_id"].as<int>();
            product.name = row["name"].as<std::string>();
            product.description = row["description"].isNull()
                ? ""
                : row["description"].as<std::string>();
            product.price_cents = row["price_cents"].as<long long>();
            product.stock_qty = row["stock_qty"].as<int>();
            product.category = row["category"].as<std::string>();
            product.image_url = row["image_url"].isNull()
                ? ""
                : row["image_url"].as<std::string>();
            product.is_active = row["is_active"].as<bool>();

            products.push_back(product);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Admin getAllProducts error: " << e.what() << std::endl;
    }

    return products;
}

bool AdminRepository::deleteProduct(int productId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "UPDATE products "
            "SET is_active = FALSE "
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



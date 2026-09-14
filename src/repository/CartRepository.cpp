#include "CartRepository.h"



#include <drogon/drogon.h>

bool CartRepository::addToCart(
    int userId,
    int productId,
    int quantity)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "INSERT INTO cart_items "
            "(user_id, product_id, quantity) "
            "VALUES ($1::integer, $2::integer, $3::integer) "
            "ON CONFLICT (user_id, product_id) "
            "DO UPDATE SET quantity = cart_items.quantity + EXCLUDED.quantity",
            std::to_string(userId),
            std::to_string(productId),
            std::to_string(quantity)
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

std::vector<CartItem> CartRepository::getCart(int userId)
{
    std::vector<CartItem> cart;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, user_id, product_id, quantity "
            "FROM cart_items "
            "WHERE user_id = $1::integer "
            "ORDER BY id",
            std::to_string(userId)
        );

        for (const auto& row : result)
        {
            CartItem item;

            item.id = row["id"].as<int>();
            item.user_id = row["user_id"].as<int>();
            item.product_id = row["product_id"].as<int>();
            item.quantity = row["quantity"].as<int>();

            cart.push_back(item);
        }
    }
    catch (const std::exception&)
    {
    }

    return cart;
}

bool CartRepository::updateCartItem(
    int userId,
    int productId,
    int quantity)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "UPDATE cart_items SET quantity = $1::integer "
            "WHERE user_id = $2::integer "
            "AND product_id = $3::integer",
            std::to_string(quantity),
            std::to_string(userId),
            std::to_string(productId)
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool CartRepository::removeFromCart(
    int userId,
    int productId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "DELETE FROM cart_items "
            "WHERE user_id = $1::integer "
            "AND product_id = $2::integer",
            std::to_string(userId),
            std::to_string(productId)
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool CartRepository::clearCart(int userId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "DELETE FROM cart_items "
            "WHERE user_id = $1::integer",
            std::to_string(userId)
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
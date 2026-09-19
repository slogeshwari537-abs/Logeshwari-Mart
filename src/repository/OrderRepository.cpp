#include "OrderRepository.h"

#include <drogon/drogon.h>

bool OrderRepository::createOrder(
    int buyerId,
    long long totalAmountCents)
{
    auto client = drogon::app().getDbClient();

    try
    {
        // Start transaction
        auto transaction = client->newTransaction();

        // Get buyer cart with product details
        auto cartResult = transaction->execSqlSync(
            "SELECT cart_items.product_id, "
            "cart_items.quantity, "
            "products.price_cents, "
            "products.stock_qty "
            "FROM cart_items "
            "JOIN products "
            "ON products.id = cart_items.product_id "
            "WHERE cart_items.user_id = $1::integer",
            std::to_string(buyerId)
        );

        // Cart is empty
        if (cartResult.empty())
        {
            return false;
        }

        long long calculatedTotal = 0;

        // Validate quantity and stock
        for (const auto& row : cartResult)
        {
            int quantity = row["quantity"].as<int>();

            long long price =
                row["price_cents"].as<long long>();

            int stock =
                row["stock_qty"].as<int>();

            if (quantity <= 0 || quantity > stock)
            {
                return false;
            }

            calculatedTotal += price * quantity;
        }

        // Validate total amount
        if (calculatedTotal != totalAmountCents)
        {
            return false;
        }

        // Create order
        auto orderResult = transaction->execSqlSync(
            "INSERT INTO orders "
            "(buyer_id, status, total_amount_cents) "
            "VALUES ($1::integer, 'PENDING', $2::bigint) "
            "RETURNING id",
            std::to_string(buyerId),
            std::to_string(calculatedTotal)
        );

        int orderId =
            orderResult[0]["id"].as<int>();

        // Create order items and reduce stock
        for (const auto& row : cartResult)
        {
            int productId =
                row["product_id"].as<int>();

            int quantity =
                row["quantity"].as<int>();

            long long price =
                row["price_cents"].as<long long>();

            transaction->execSqlSync(
                "INSERT INTO order_items "
                "(order_id, product_id, quantity, unit_price_cents) "
                "VALUES ($1::integer, $2::integer, "
                "$3::integer, $4::bigint)",
                std::to_string(orderId),
                std::to_string(productId),
                std::to_string(quantity),
                std::to_string(price)
            );

            transaction->execSqlSync(
                "UPDATE products "
                "SET stock_qty = stock_qty - $1::integer "
                "WHERE id = $2::integer",
                std::to_string(quantity),
                std::to_string(productId)
            );
        }

        // Clear buyer cart
        transaction->execSqlSync(
            "DELETE FROM cart_items "
            "WHERE user_id = $1::integer",
            std::to_string(buyerId)
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}


std::vector<Order> OrderRepository::getOrdersByBuyer(
    int buyerId)
{
    std::vector<Order> orders;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, buyer_id, status, total_amount_cents "
            "FROM orders "
            "WHERE buyer_id = $1::integer "
            "ORDER BY id DESC",
            std::to_string(buyerId)
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


// =====================================================
// SELLER ORDER HISTORY
// =====================================================

std::vector<Order> OrderRepository::getOrdersBySeller(
    int sellerId)
{
    std::vector<Order> orders;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT DISTINCT "
            "o.id, "
            "o.buyer_id, "
            "o.status, "
            "o.total_amount_cents "
            "FROM orders o "
            "JOIN order_items oi "
            "ON oi.order_id = o.id "
            "JOIN products p "
            "ON p.id = oi.product_id "
            "WHERE p.seller_id = $1::integer "
            "ORDER BY o.id DESC",
            std::to_string(sellerId)
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
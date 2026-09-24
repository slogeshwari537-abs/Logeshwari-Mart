#include "ProductRepository.h"

#include <drogon/drogon.h>

bool ProductRepository::addProduct(
    const Product& product)
{
    auto client = drogon::app().getDbClient();

    try
    {
        client->execSqlSync(
            "INSERT INTO products "
            "(seller_id, name, description, price_cents, stock_qty, category, image_url) "
            "VALUES ($1::integer, $2, $3, $4::bigint, $5::integer, $6, $7)",
            std::to_string(product.seller_id),
            product.name,
            product.description,
            std::to_string(product.price_cents),
            std::to_string(product.stock_qty),
            product.category,
            product.image_url
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

std::vector<Product> ProductRepository::getProducts()
{
    std::vector<Product> products;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, seller_id, name, description, "
            "price_cents, stock_qty, category, image_url "
            "FROM products "
            "ORDER BY id DESC"
        );

        for (const auto& row : result)
        {
            Product product;

            product.id =
                row["id"].as<int>();

            product.seller_id =
                row["seller_id"].as<int>();

            product.name =
                row["name"].as<std::string>();

            product.description =
                row["description"].as<std::string>();

            product.price_cents =
                row["price_cents"].as<long long>();

            product.stock_qty =
                row["stock_qty"].as<int>();

            product.category =
                row["category"].as<std::string>();

            product.image_url =
                row["image_url"].isNull()
                    ? ""
                    : row["image_url"].as<std::string>();

            products.push_back(product);
        }
    }
    catch (const std::exception&)
    {
    }

    return products;
}

std::vector<Product> ProductRepository::searchProducts(
    const std::string& keyword,
    const std::string& category)
{
    std::vector<Product> products;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, seller_id, name, description, "
            "price_cents, stock_qty, category, image_url "
            "FROM products "
            "WHERE (name ILIKE '%' || $1 || '%' "
            "OR description ILIKE '%' || $1 || '%') "
            "AND ($2 = '' OR category = $2) "
            "ORDER BY id DESC",
            keyword,
            category
        );

        for (const auto& row : result)
        {
            Product product;

            product.id =
                row["id"].as<int>();

            product.seller_id =
                row["seller_id"].as<int>();

            product.name =
                row["name"].as<std::string>();

            product.description =
                row["description"].as<std::string>();

            product.price_cents =
                row["price_cents"].as<long long>();

            product.stock_qty =
                row["stock_qty"].as<int>();

            product.category =
                row["category"].as<std::string>();

            product.image_url =
                row["image_url"].isNull()
                    ? ""
                    : row["image_url"].as<std::string>();

            products.push_back(product);
        }
    }
    catch (const std::exception&)
    {
    }

    return products;
}

bool ProductRepository::updateProduct(
    const Product& product,
    int sellerId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "UPDATE products "
            "SET name = $1, "
            "description = $2, "
            "price_cents = $3::bigint, "
            "stock_qty = $4::integer, "
            "category = $5, "
            "image_url = $6 "
            "WHERE id = $7::integer "
            "AND seller_id = $8::integer",
            product.name,
            product.description,
            std::to_string(product.price_cents),
            std::to_string(product.stock_qty),
            product.category,
            product.image_url,
            std::to_string(product.id),
            std::to_string(sellerId)
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool ProductRepository::deleteProduct(
    int productId,
    int sellerId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "DELETE FROM products "
            "WHERE id = $1::integer "
            "AND seller_id = $2::integer",
            std::to_string(productId),
            std::to_string(sellerId)
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
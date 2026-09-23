#include "ReviewRepository.h"
#include <drogon/drogon.h>

bool ReviewRepository::hasCompletedOrder(
    int productId,
    int userId)
{
    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT 1 "
            "FROM orders o "
            "JOIN order_items oi ON o.id = oi.order_id "
            "WHERE o.buyer_id = $1::integer "
            "AND oi.product_id = $2::integer "
            "AND o.status = 'DELIVERED' "
            "LIMIT 1",
            std::to_string(userId),
            std::to_string(productId)
        );

        return !result.empty();
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool ReviewRepository::addReview(
    int productId,
    int userId,
    int rating,
    const std::string& comment)
{
    auto client = drogon::app().getDbClient();

    try
    {
        // Prevent duplicate review
        auto existingReview = client->execSqlSync(
            "SELECT 1 "
            "FROM reviews "
            "WHERE product_id = $1::integer "
            "AND user_id = $2::integer "
            "LIMIT 1",
            std::to_string(productId),
            std::to_string(userId)
        );

        if (!existingReview.empty())
        {
            return false;
        }

        // Add new review
        client->execSqlSync(
            "INSERT INTO reviews "
            "(product_id, user_id, rating, comment) "
            "VALUES ($1::integer, $2::integer, $3::integer, $4)",
            std::to_string(productId),
            std::to_string(userId),
            std::to_string(rating),
            comment
        );

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

std::vector<Review> ReviewRepository::getReviewsByProduct(
    int productId)
{
    std::vector<Review> reviews;

    auto client = drogon::app().getDbClient();

    try
    {
        auto result = client->execSqlSync(
            "SELECT id, product_id, user_id, rating, comment "
            "FROM reviews "
            "WHERE product_id = $1::integer "
            "ORDER BY id DESC",
            std::to_string(productId)
        );

        for (const auto& row : result)
        {
            Review review;

            review.id =
                row["id"].as<int>();

            review.product_id =
                row["product_id"].as<int>();

            review.user_id =
                row["user_id"].as<int>();

            review.rating =
                row["rating"].as<int>();

            review.comment =
                row["comment"].as<std::string>();

            reviews.push_back(review);
        }
    }
    catch (const std::exception&)
    {
    }

    return reviews;
}
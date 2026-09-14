#include "ReviewRepository.h"
#include <drogon/drogon.h>

bool ReviewRepository::addReview(
    int productId,
    int userId,
    int rating,
    const std::string& comment)
{
    auto client = drogon::app().getDbClient();

    try
    {
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

            review.id = row["id"].as<int>();
            review.product_id = row["product_id"].as<int>();
            review.user_id = row["user_id"].as<int>();
            review.rating = row["rating"].as<int>();
            review.comment = row["comment"].as<std::string>();

            reviews.push_back(review);
        }
    }
    catch (const std::exception&)
    {
    }

    return reviews;
}

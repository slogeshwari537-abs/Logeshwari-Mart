#include <drogon/drogon.h>
#include "../repository/ReviewRepository.h"

using namespace drogon;

void registerReviewRoutes()
{
    // Add Review
    app().registerHandler(
        "/api/reviews",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("product_id") ||
                !json->isMember("user_id") ||
                !json->isMember("rating") ||
                !json->isMember("comment"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})"
                );
                callback(response);
                return;
            }

            int productId = (*json)["product_id"].asInt();
            int userId = (*json)["user_id"].asInt();
            int rating = (*json)["rating"].asInt();
            std::string comment = (*json)["comment"].asString();

            if (rating < 1 || rating > 5)
            {
                response->setBody(
                    R"({"success":false,"message":"Rating must be between 1 and 5"})"
                );
                callback(response);
                return;
            }

            if (comment.empty())
            {
                response->setBody(
                    R"({"success":false,"message":"Comment cannot be empty"})"
                );
                callback(response);
                return;
            }

            ReviewRepository repository;

            if (repository.addReview(
                    productId,
                    userId,
                    rating,
                    comment))
            {
                response->setBody(
                    R"({"success":true,"message":"Review added successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to add review"})"
                );
            }

            callback(response);
        },
        {Post}
    );

    // View Reviews
    app().registerHandler(
        "/api/reviews/{productId}",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int productId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            ReviewRepository repository;

            auto reviews =
                repository.getReviewsByProduct(productId);

            Json::Value result(Json::arrayValue);

            for (const auto& review : reviews)
            {
                Json::Value item;

                item["id"] = review.id;
                item["product_id"] = review.product_id;
                item["user_id"] = review.user_id;
                item["rating"] = review.rating;
                item["comment"] = review.comment;

                result.append(item);
            }

            response->setBody(result.toStyledString());

            callback(response);
        },
        {Get}
    );
}
#include <drogon/drogon.h>

#include "../repository/ReviewRepository.h"
#include "../service/SessionManager.h"

using namespace drogon;


// ============================================================
// GET AUTHENTICATED USER ID
// ============================================================

int getReviewUserId(const HttpRequestPtr& req)
{
    // Check X-Auth-Token header
    std::string token =
        req->getHeader("X-Auth-Token");

    // If header is empty, check session_token cookie
    if (token.empty())
    {
        std::string cookie =
            req->getHeader("Cookie");

        const std::string cookieName =
            "session_token=";

        std::size_t position =
            cookie.find(cookieName);

        if (position != std::string::npos)
        {
            position += cookieName.length();

            std::size_t end =
                cookie.find(";", position);

            if (end == std::string::npos)
            {
                token =
                    cookie.substr(position);
            }
            else
            {
                token =
                    cookie.substr(
                        position,
                        end - position
                    );
            }
        }
    }

    // No token
    if (token.empty())
    {
        return -1;
    }

    // Get user ID from our project's SessionManager
    return ::SessionManager::getInstance()
        .getUserId(token);
}


// ============================================================
// REGISTER REVIEW ROUTES
// ============================================================

void registerReviewRoutes()
{

    // ========================================================
    // ADD REVIEW
    // ========================================================

    app().registerHandler(
        "/api/reviews",

        [](const HttpRequestPtr& req,
           std::function<void(
               const HttpResponsePtr&)>&& callback)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON
            );


            // ------------------------------------------------
            // CHECK LOGIN
            // ------------------------------------------------

            int userId =
                getReviewUserId(req);

            if (userId <= 0)
            {
                response->setStatusCode(
                    k401Unauthorized
                );

                response->setBody(
                    R"({"success":false,"message":"Please login first"})"
                );

                callback(response);
                return;
            }


            // ------------------------------------------------
            // GET JSON
            // ------------------------------------------------

            auto json =
                req->getJsonObject();


            if (!json ||
                !json->isMember("product_id") ||
                !json->isMember("rating") ||
                !json->isMember("comment"))
            {
                response->setStatusCode(
                    k400BadRequest
                );

                response->setBody(
                    R"({"success":false,"message":"Product ID, rating and comment are required"})"
                );

                callback(response);
                return;
            }


            // ------------------------------------------------
            // READ DATA
            // ------------------------------------------------

            int productId =
                (*json)["product_id"].asInt();

            int rating =
                (*json)["rating"].asInt();

            std::string comment =
                (*json)["comment"].asString();


            // ------------------------------------------------
            // VALIDATE PRODUCT ID
            // ------------------------------------------------

            if (productId <= 0)
            {
                response->setStatusCode(
                    k400BadRequest
                );

                response->setBody(
                    R"({"success":false,"message":"Invalid product ID"})"
                );

                callback(response);
                return;
            }


            // ------------------------------------------------
            // VALIDATE RATING
            // ------------------------------------------------

            if (rating < 1 ||
                rating > 5)
            {
                response->setStatusCode(
                    k400BadRequest
                );

                response->setBody(
                    R"({"success":false,"message":"Rating must be between 1 and 5"})"
                );

                callback(response);
                return;
            }


            // ------------------------------------------------
            // VALIDATE COMMENT
            // ------------------------------------------------

            if (comment.empty())
            {
                response->setStatusCode(
                    k400BadRequest
                );

                response->setBody(
                    R"({"success":false,"message":"Comment cannot be empty"})"
                );

                callback(response);
                return;
            }


            // ------------------------------------------------
            // ADD REVIEW TO DATABASE
            // ------------------------------------------------

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
                response->setStatusCode(
                    k400BadRequest
                );

                response->setBody(
                    R"({"success":false,"message":"Failed to add review"})"
                );
            }

            callback(response);
        },

        {Post},

        {"AuthFilter"}
    );


    // ========================================================
    // VIEW REVIEWS
    // ========================================================

    app().registerHandler(
        "/api/reviews/{1}",

        [](const HttpRequestPtr&,
           std::function<void(
               const HttpResponsePtr&)>&& callback,
           int productId)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON
            );


            // ------------------------------------------------
            // VALIDATE PRODUCT ID
            // ------------------------------------------------

            if (productId <= 0)
            {
                response->setStatusCode(
                    k400BadRequest
                );

                response->setBody(
                    R"({"success":false,"message":"Invalid product ID"})"
                );

                callback(response);
                return;
            }


            // ------------------------------------------------
            // GET REVIEWS
            // ------------------------------------------------

            ReviewRepository repository;

            auto reviews =
                repository.getReviewsByProduct(
                    productId
                );


            Json::Value result(
                Json::arrayValue
            );


            for (const auto& review : reviews)
            {
                Json::Value item;

                item["id"] =
                    review.id;

                item["product_id"] =
                    review.product_id;

                item["user_id"] =
                    review.user_id;

                item["rating"] =
                    review.rating;

                item["comment"] =
                    review.comment;

                result.append(item);
            }


            // ------------------------------------------------
            // RESPONSE
            // ------------------------------------------------

            Json::Value body;

            body["success"] = true;
            body["reviews"] = result;

            response->setBody(
                body.toStyledString()
            );

            callback(response);
        },

        {Get}
    );
}
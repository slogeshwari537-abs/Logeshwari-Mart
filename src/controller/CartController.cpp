#include <drogon/drogon.h>
#include "../repository/CartRepository.h"

using namespace drogon;

void registerCartRoutes()
{
    // ============================
    // ADD TO CART
    // ============================

    app().registerHandler(
        "/api/cart",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()->get<int>("authenticatedUserId");

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("user_id") ||
                !json->isMember("product_id") ||
                !json->isMember("quantity"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})");
                callback(response);
                return;
            }

            int userId = (*json)["user_id"].asInt();
            int productId = (*json)["product_id"].asInt();
            int quantity = (*json)["quantity"].asInt();

            if (userId != authenticatedUserId)
            {
                response->setStatusCode(k403Forbidden);
                response->setBody(
                    R"({"success":false,"message":"You can only access your own cart"})");
                callback(response);
                return;
            }

            if (quantity <= 0)
            {
                response->setBody(
                    R"({"success":false,"message":"Quantity must be greater than zero"})");
                callback(response);
                return;
            }

            CartRepository repository;

            if (repository.addToCart(
                    authenticatedUserId,
                    productId,
                    quantity))
            {
                response->setBody(
                    R"({"success":true,"message":"Product added to cart"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to add product to cart"})");
            }

            callback(response);
        },
        {Post, "AuthFilter"}
    );

    // ============================
    // VIEW CART
    // ============================

    app().registerHandler(
        "/api/cart/{userId}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()->get<int>("authenticatedUserId");

            if (userId != authenticatedUserId)
            {
                response->setStatusCode(k403Forbidden);
                response->setBody(
                    R"({"success":false,"message":"You can only access your own cart"})");
                callback(response);
                return;
            }

            CartRepository repository;
            auto cart = repository.getCart(authenticatedUserId);

            Json::Value result(Json::arrayValue);

            for (const auto& item : cart)
            {
                Json::Value cartItem;

                cartItem["id"] = item.id;
                cartItem["user_id"] = item.user_id;
                cartItem["product_id"] = item.product_id;
                cartItem["quantity"] = item.quantity;

                result.append(cartItem);
            }

            response->setBody(result.toStyledString());
            callback(response);
        },
        {Get, "AuthFilter"}
    );

    // ============================
    // CLEAR CART
    // ============================

    app().registerHandler(
        "/api/cart/clear/{userId}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()->get<int>("authenticatedUserId");

            if (userId != authenticatedUserId)
            {
                response->setStatusCode(k403Forbidden);
                response->setBody(
                    R"({"success":false,"message":"You can only clear your own cart"})");
                callback(response);
                return;
            }

            CartRepository repository;

            if (repository.clearCart(authenticatedUserId))
            {
                response->setBody(
                    R"({"success":true,"message":"Cart cleared successfully"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to clear cart"})");
            }

            callback(response);
        },
        {Delete, "AuthFilter"}
    );

    // ============================
    // UPDATE CART
    // ============================

    app().registerHandler(
        "/api/cart/{userId}/{productId}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId,
           int productId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()->get<int>("authenticatedUserId");

            if (userId != authenticatedUserId)
            {
                response->setStatusCode(k403Forbidden);
                response->setBody(
                    R"({"success":false,"message":"You can only update your own cart"})");
                callback(response);
                return;
            }

            auto json = req->getJsonObject();

            if (!json || !json->isMember("quantity"))
            {
                response->setBody(
                    R"({"success":false,"message":"Quantity is required"})");
                callback(response);
                return;
            }

            int quantity = (*json)["quantity"].asInt();

            if (quantity <= 0)
            {
                response->setBody(
                    R"({"success":false,"message":"Quantity must be greater than zero"})");
                callback(response);
                return;
            }

            CartRepository repository;

            if (repository.updateCartItem(
                    authenticatedUserId,
                    productId,
                    quantity))
            {
                response->setBody(
                    R"({"success":true,"message":"Cart updated successfully"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to update cart"})");
            }

            callback(response);
        },
        {Put, "AuthFilter"}
    );

    // ============================
    // REMOVE FROM CART
    // ============================

    app().registerHandler(
        "/api/cart/{userId}/{productId}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId,
           int productId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()->get<int>("authenticatedUserId");

            if (userId != authenticatedUserId)
            {
                response->setStatusCode(k403Forbidden);
                response->setBody(
                    R"({"success":false,"message":"You can only remove items from your own cart"})");
                callback(response);
                return;
            }

            CartRepository repository;

            if (repository.removeFromCart(
                    authenticatedUserId,
                    productId))
            {
                response->setBody(
                    R"({"success":true,"message":"Product removed from cart"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to remove product from cart"})");
            }

            callback(response);
        },
        {Delete, "AuthFilter"}
    );
}
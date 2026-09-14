
#include <drogon/drogon.h>
#include "../repository/CartRepository.h"

using namespace drogon;

void registerCartRoutes()
{
    // Add to Cart
    app().registerHandler(
        "/api/cart",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("user_id") ||
                !json->isMember("product_id") ||
                !json->isMember("quantity"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})"
                );
                callback(response);
                return;
            }

            int userId = (*json)["user_id"].asInt();
            int productId = (*json)["product_id"].asInt();
            int quantity = (*json)["quantity"].asInt();

            if (quantity <= 0)
            {
                response->setBody(
                    R"({"success":false,"message":"Quantity must be greater than zero"})"
                );
                callback(response);
                return;
            }

            CartRepository repository;

            if (repository.addToCart(userId, productId, quantity))
            {
                response->setBody(
                    R"({"success":true,"message":"Product added to cart"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to add product to cart"})"
                );
            }

            callback(response);
        },
        {Post}
    );

    // View Cart
    app().registerHandler(
        "/api/cart/{userId}",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            CartRepository repository;
            auto cart = repository.getCart(userId);

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
        {Get}
    );

    // Clear Cart
    // IMPORTANT: This route is before /api/cart/{userId}/{productId}
    app().registerHandler(
        "/api/cart/clear/{userId}",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            CartRepository repository;

            if (repository.clearCart(userId))
            {
                response->setBody(
                    R"({"success":true,"message":"Cart cleared successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to clear cart"})"
                );
            }

            callback(response);
        },
        {Delete}
    );

    // Update Cart
    app().registerHandler(
        "/api/cart/{userId}/{productId}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId,
           int productId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json || !json->isMember("quantity"))
            {
                response->setBody(
                    R"({"success":false,"message":"Quantity is required"})"
                );
                callback(response);
                return;
            }

            int quantity = (*json)["quantity"].asInt();

            if (quantity <= 0)
            {
                response->setBody(
                    R"({"success":false,"message":"Quantity must be greater than zero"})"
                );
                callback(response);
                return;
            }

            CartRepository repository;

            if (repository.updateCartItem(userId, productId, quantity))
            {
                response->setBody(
                    R"({"success":true,"message":"Cart updated successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to update cart"})"
                );
            }

            callback(response);
        },
        {Put}
    );

    // Remove from Cart
    app().registerHandler(
        "/api/cart/{userId}/{productId}",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId,
           int productId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            CartRepository repository;

            if (repository.removeFromCart(userId, productId))
            {
                response->setBody(
                    R"({"success":true,"message":"Product removed from cart"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to remove product from cart"})"
                );
            }

            callback(response);
        },
        {Delete}
    );
}


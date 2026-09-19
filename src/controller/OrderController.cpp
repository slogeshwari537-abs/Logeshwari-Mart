#include "OrderController.h"
#include "../repository/OrderRepository.h"

#include <drogon/drogon.h>

void registerOrderRoutes()
{
    // ============================
    // CHECKOUT + MOCK PAYMENT
    // AUTHENTICATED USER ONLY
    // ============================

    drogon::app().registerHandler(
        "/api/checkout/{1}",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback,
           int buyerId)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()
                    ->get<int>("authenticatedUserId");

            // Prevent user ID spoofing
            if (buyerId != authenticatedUserId)
            {
                response->setStatusCode(
                    drogon::k403Forbidden);

                response->setBody(
                    R"({"success":false,"message":"You can only checkout your own cart"})");

                callback(response);
                return;
            }

            auto json =
                req->getJsonObject();

            if (!json ||
                !json->isMember("total_amount_cents"))
            {
                Json::Value result;

                result["success"] = false;
                result["message"] =
                    "total_amount_cents is required";

                callback(
                    drogon::HttpResponse::
                        newHttpJsonResponse(result));

                return;
            }

            long long totalAmountCents =
                (*json)["total_amount_cents"]
                    .asInt64();

            if (totalAmountCents <= 0)
            {
                Json::Value result;

                result["success"] = false;
                result["message"] =
                    "Invalid total amount";

                callback(
                    drogon::HttpResponse::
                        newHttpJsonResponse(result));

                return;
            }

            // Mock payment
            bool paymentSuccess = true;

            if (!paymentSuccess)
            {
                Json::Value result;

                result["success"] = false;
                result["payment_success"] = false;
                result["message"] = "Payment failed";

                callback(
                    drogon::HttpResponse::
                        newHttpJsonResponse(result));

                return;
            }

            OrderRepository repository;

            bool orderSuccess =
                repository.createOrder(
                    authenticatedUserId,
                    totalAmountCents);

            Json::Value result;

            result["success"] = orderSuccess;
            result["payment_success"] = true;

            if (orderSuccess)
            {
                result["message"] =
                    "Payment successful. Order created successfully";
            }
            else
            {
                result["message"] =
                    "Payment successful, but order creation failed";
            }

            callback(
                drogon::HttpResponse::
                    newHttpJsonResponse(result));
        },
        {drogon::Post, "AuthFilter"}
    );

    // ============================
    // ORDER HISTORY
    // AUTHENTICATED USER ONLY
    // ============================

    drogon::app().registerHandler(
        "/api/orders/{1}",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback,
           int buyerId)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()
                    ->get<int>("authenticatedUserId");

            // Prevent user ID spoofing
            if (buyerId != authenticatedUserId)
            {
                response->setStatusCode(
                    drogon::k403Forbidden);

                response->setBody(
                    R"({"success":false,"message":"You can only view your own orders"})");

                callback(response);
                return;
            }

            OrderRepository repository;

            auto orders =
                repository.getOrdersByBuyer(
                    authenticatedUserId);

            Json::Value result(
                Json::arrayValue);

            for (const auto& order : orders)
            {
                Json::Value item;

                item["id"] = order.id;
                item["buyer_id"] = order.buyer_id;
                item["status"] = order.status;

                item["total_amount_cents"] =
                    Json::Int64(
                        order.total_amount_cents);

                result.append(item);
            }

            response->setBody(
                result.toStyledString());

            callback(response);
        },
        {drogon::Get, "AuthFilter"}
    );
}
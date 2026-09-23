#include "ProductController.h"

#include <drogon/drogon.h>

#include "../repository/ProductRepository.h"
#include "../repository/UserRepository.h"

using namespace drogon;

void registerProductRoutes()
{
    // ============================
    // ADD PRODUCT - SELLER ONLY
    // ============================

    app().registerHandler(
        "/api/products",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()
                    ->get<int>("authenticatedUserId");

            UserRepository userRepository;

            auto user =
                userRepository.getUserById(
                    authenticatedUserId);

            if (!user || user->role != "SELLER")
            {
                response->setStatusCode(
                    k403Forbidden);

                response->setBody(
                    R"({"success":false,"message":"Seller access required"})");

                callback(response);
                return;
            }

            auto json =
                req->getJsonObject();

            if (!json ||
                !json->isMember("name") ||
                !json->isMember("description") ||
                !json->isMember("price_cents") ||
                !json->isMember("stock_qty") ||
                !json->isMember("category") ||
                !json->isMember("image_url"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})");

                callback(response);
                return;
            }

            Product product;

            product.seller_id =
                authenticatedUserId;

            product.name =
                (*json)["name"].asString();

            product.description =
                (*json)["description"].asString();

            product.price_cents =
                (*json)["price_cents"].asInt64();

            product.stock_qty =
                (*json)["stock_qty"].asInt();

            product.category =
                (*json)["category"].asString();

            product.image_url =
                (*json)["image_url"].asString();

            if (product.name.empty() ||
                product.description.empty() ||
                product.category.empty() ||
                product.price_cents <= 0 ||
                product.stock_qty < 0)
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid product data"})");

                callback(response);
                return;
            }

            ProductRepository repository;

            if (repository.addProduct(product))
            {
                response->setBody(
                    R"({"success":true,"message":"Product added successfully"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to add product"})");
            }

            callback(response);
        },
        {Post, "AuthFilter"});


    // ============================
    // VIEW PRODUCTS - PUBLIC
    // ============================

    app().registerHandler(
        "/api/products",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON);

            ProductRepository repository;

            auto products =
                repository.getProducts();

            Json::Value result(
                Json::arrayValue);

            for (const auto& product : products)
            {
                Json::Value item;

                item["id"] =
                    product.id;

                item["seller_id"] =
                    product.seller_id;

                item["name"] =
                    product.name;

                item["description"] =
                    product.description;

                item["price_cents"] =
                    static_cast<Json::Int64>(
                        product.price_cents);

                item["stock_qty"] =
                    product.stock_qty;

                item["category"] =
                    product.category;

                item["image_url"] =
                    product.image_url;

                result.append(item);
            }

            response->setBody(
                result.toStyledString());

            callback(response);
        },
        {Get});


    // ============================
    // SEARCH / FILTER - PUBLIC
    // ============================

    app().registerHandler(
        "/api/products/search",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON);

            std::string keyword =
                req->getParameter("keyword");

            std::string category =
                req->getParameter("category");

            ProductRepository repository;

            auto products =
                repository.searchProducts(
                    keyword,
                    category);

            Json::Value result(
                Json::arrayValue);

            for (const auto& product : products)
            {
                Json::Value item;

                item["id"] =
                    product.id;

                item["seller_id"] =
                    product.seller_id;

                item["name"] =
                    product.name;

                item["description"] =
                    product.description;

                item["price_cents"] =
                    static_cast<Json::Int64>(
                        product.price_cents);

                item["stock_qty"] =
                    product.stock_qty;

                item["category"] =
                    product.category;

                item["image_url"] =
                    product.image_url;

                result.append(item);
            }

            response->setBody(
                result.toStyledString());

            callback(response);
        },
        {Get});


    // ============================
    // UPDATE PRODUCT
    // SELLER + OWN PRODUCT ONLY
    // ============================

    app().registerHandler(
        "/api/products/{id}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int id)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()
                    ->get<int>("authenticatedUserId");

            UserRepository userRepository;

            auto user =
                userRepository.getUserById(
                    authenticatedUserId);

            if (!user || user->role != "SELLER")
            {
                response->setStatusCode(
                    k403Forbidden);

                response->setBody(
                    R"({"success":false,"message":"Seller access required"})");

                callback(response);
                return;
            }

            auto json =
                req->getJsonObject();

            if (!json ||
                !json->isMember("name") ||
                !json->isMember("description") ||
                !json->isMember("price_cents") ||
                !json->isMember("stock_qty") ||
                !json->isMember("category") ||
                !json->isMember("image_url"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})");

                callback(response);
                return;
            }

            Product product;

            product.id =
                id;

            product.name =
                (*json)["name"].asString();

            product.description =
                (*json)["description"].asString();

            product.price_cents =
                (*json)["price_cents"].asInt64();

            product.stock_qty =
                (*json)["stock_qty"].asInt();

            product.category =
                (*json)["category"].asString();

            product.image_url =
                (*json)["image_url"].asString();

            if (product.name.empty() ||
                product.description.empty() ||
                product.category.empty() ||
                product.price_cents <= 0 ||
                product.stock_qty < 0)
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid product data"})");

                callback(response);
                return;
            }

            ProductRepository repository;

            if (repository.updateProduct(
                    product,
                    authenticatedUserId))
            {
                response->setBody(
                    R"({"success":true,"message":"Product updated successfully"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Product update failed or product does not belong to seller"})");
            }

            callback(response);
        },
        {Put, "AuthFilter"});


    // ============================
    // DELETE PRODUCT
    // SELLER + OWN PRODUCT ONLY
    // ============================

    app().registerHandler(
        "/api/products/{id}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int id)
        {
            auto response =
                HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON);

            int authenticatedUserId =
                req->getAttributes()
                    ->get<int>("authenticatedUserId");

            UserRepository userRepository;

            auto user =
                userRepository.getUserById(
                    authenticatedUserId);

            if (!user || user->role != "SELLER")
            {
                response->setStatusCode(
                    k403Forbidden);

                response->setBody(
                    R"({"success":false,"message":"Seller access required"})");

                callback(response);
                return;
            }

            ProductRepository repository;

            if (repository.deleteProduct(
                    id,
                    authenticatedUserId))
            {
                response->setBody(
                    R"({"success":true,"message":"Product deleted successfully"})");
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Product deletion failed or product does not belong to seller"})");
            }

            callback(response);
        },
        {Delete, "AuthFilter"});
}
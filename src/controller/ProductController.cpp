
#include <drogon/drogon.h>
#include "../repository/ProductRepository.h"

using namespace drogon;

void registerProductRoutes()
{
    // Add Product
    app().registerHandler(
        "/api/products",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("seller_id") ||
                !json->isMember("name") ||
                !json->isMember("description") ||
                !json->isMember("price_cents") ||
                !json->isMember("stock_qty") ||
                !json->isMember("category"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})"
                );
                callback(response);
                return;
            }

            Product product;

            product.seller_id = (*json)["seller_id"].asInt();
            product.name = (*json)["name"].asString();
            product.description = (*json)["description"].asString();
            product.price_cents = (*json)["price_cents"].asInt64();
            product.stock_qty = (*json)["stock_qty"].asInt();
            product.category = (*json)["category"].asString();

            ProductRepository repository;

            if (repository.addProduct(product))
            {
                response->setBody(
                    R"({"success":true,"message":"Product added successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to add product"})"
                );
            }

            callback(response);
        },
        {Post}
    );

    // View Products
    app().registerHandler(
        "/api/products",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            ProductRepository repository;
            auto products = repository.getProducts();

            Json::Value result(Json::arrayValue);

            for (const auto& product : products)
            {
                Json::Value item;

                item["id"] = product.id;
                item["seller_id"] = product.seller_id;
                item["name"] = product.name;
                item["description"] = product.description;
                item["price_cents"] =
                    static_cast<Json::Int64>(product.price_cents);
                item["stock_qty"] = product.stock_qty;
                item["category"] = product.category;

                result.append(item);
            }

            response->setBody(result.toStyledString());

            callback(response);
        },
        {Get}
    );

    // Search and Filter Products
    app().registerHandler(
        "/api/products/search",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            std::string keyword =
                req->getParameter("keyword");

            std::string category =
                req->getParameter("category");

            ProductRepository repository;

            auto products =
                repository.searchProducts(keyword, category);

            Json::Value result(Json::arrayValue);

            for (const auto& product : products)
            {
                Json::Value item;

                item["id"] = product.id;
                item["seller_id"] = product.seller_id;
                item["name"] = product.name;
                item["description"] = product.description;
                item["price_cents"] =
                    static_cast<Json::Int64>(product.price_cents);
                item["stock_qty"] = product.stock_qty;
                item["category"] = product.category;

                result.append(item);
            }

            response->setBody(result.toStyledString());

            callback(response);
        },
        {Get}
    );

    // Update Product
    app().registerHandler(
        "/api/products/{id}",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int id)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("name") ||
                !json->isMember("description") ||
                !json->isMember("price_cents") ||
                !json->isMember("stock_qty") ||
                !json->isMember("category"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})"
                );
                callback(response);
                return;
            }

            Product product;

            product.id = id;
            product.name = (*json)["name"].asString();
            product.description = (*json)["description"].asString();
            product.price_cents = (*json)["price_cents"].asInt64();
            product.stock_qty = (*json)["stock_qty"].asInt();
            product.category = (*json)["category"].asString();

            ProductRepository repository;

            if (repository.updateProduct(product))
            {
                response->setBody(
                    R"({"success":true,"message":"Product updated successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to update product"})"
                );
            }

            callback(response);
        },
        {Put}
    );

    // Delete Product
    app().registerHandler(
        "/api/products/{id}",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int id)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            ProductRepository repository;

            if (repository.deleteProduct(id))
            {
                response->setBody(
                    R"({"success":true,"message":"Product deleted successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to delete product"})"
                );
            }

            callback(response);
        },
        {Delete}
    );
}


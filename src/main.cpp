#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include <iostream>

void registerAuthRoutes();
void registerProductRoutes();
void registerCartRoutes();
void registerOrderRoutes();
void registerAdminRoutes();
void registerReviewRoutes();
void registerChatbotRoutes();

int main()
{
    spdlog::info("Starting LogeshwariMart...");

    drogon::app().loadConfigFile("config.json");

    drogon::app().registerHandler(
        "/",
        [](const drogon::HttpRequestPtr&,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            spdlog::info("Home route called");

            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setBody(
                "LogeshwariMart - Database Connected!"
            );

            callback(response);
        },
        {drogon::Get}
    );

    registerAuthRoutes();
    registerProductRoutes();
    registerCartRoutes();
    registerOrderRoutes();
    registerAdminRoutes();
    registerReviewRoutes();
    registerChatbotRoutes();

    drogon::app().addListener("127.0.0.1", 8080);

    spdlog::info("Starting Drogon server on port 8080...");

    drogon::app().run();

    return 0;
}
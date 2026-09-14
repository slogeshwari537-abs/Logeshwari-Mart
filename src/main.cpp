
#include <drogon/drogon.h>

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
    std::cout << "Starting LogeshwariMart..." << std::endl;

    drogon::app().loadConfigFile("config.json");

    drogon::app().registerHandler(
        "/",
        [](const drogon::HttpRequestPtr&,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
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

    std::cout << "Starting Drogon server..." << std::endl;

    drogon::app().run();

    return 0;
}
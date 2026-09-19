#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

void registerAuthRoutes();
void registerProductRoutes();
void registerCartRoutes();
void registerOrderRoutes();
void registerAdminRoutes();
void registerReviewRoutes();
void registerChatbotRoutes();
void registerHealthRoutes();

int main()
{
    spdlog::info("Starting LogeshwariMart...");

    drogon::app().loadConfigFile("config.json");

    registerAuthRoutes();
    registerProductRoutes();
    registerCartRoutes();
    registerOrderRoutes();
    registerAdminRoutes();
    registerReviewRoutes();
    registerChatbotRoutes();

    spdlog::info("Calling registerHealthRoutes()...");
    registerHealthRoutes();

    drogon::app().setDocumentRoot("./frontend");

    drogon::app().addListener(
        "127.0.0.1",
        8080
    );

    spdlog::info(
        "Starting Drogon server on port 8080..."
    );

    drogon::app().run();

    return 0;
}
#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include "filter/AuthFilter.h"

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

    // Load database and server configuration
    drogon::app().loadConfigFile("config.json");

    // Register application routes
    registerAuthRoutes();
    registerProductRoutes();
    registerCartRoutes();
    registerOrderRoutes();
    registerAdminRoutes();
    registerReviewRoutes();
    registerChatbotRoutes();

    // Serve frontend files
    drogon::app().setDocumentRoot("./frontend");

    // Start server
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
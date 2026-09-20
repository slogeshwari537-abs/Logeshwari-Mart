#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include <cstdlib>
#include <string>

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

    const char* portEnvironment =
        std::getenv("PORT");

    int port = 8080;

    if (portEnvironment != nullptr &&
        std::string(portEnvironment).empty() == false)
    {
        try
        {
            port = std::stoi(portEnvironment);
        }
        catch (...)
        {
            spdlog::warn(
                "Invalid PORT value. Using port 8080.");
            port = 8080;
        }
    }

    drogon::app().addListener(
        "0.0.0.0",
        port
    );

    spdlog::info(
        "Starting Drogon server on port {}...",
        port
    );

    drogon::app().run();

    return 0;
}
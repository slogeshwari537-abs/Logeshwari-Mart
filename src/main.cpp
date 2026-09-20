#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>

void registerAuthRoutes();
void registerProductRoutes();
void registerCartRoutes();
void registerOrderRoutes();
void registerAdminRoutes();
void registerReviewRoutes();
void registerChatbotRoutes();
void registerHealthRoutes();

namespace
{
    std::string getEnvironmentVariable(
        const char* name)
    {
        const char* value =
            std::getenv(name);

        if (value == nullptr)
        {
            return "";
        }

        return std::string(value);
    }

    bool createRenderConfig()
    {
        const std::string databaseUrl =
            getEnvironmentVariable("DATABASE_URL");

        if (databaseUrl.empty())
        {
            return false;
        }

        /*
         * Expected Render PostgreSQL URL:
         *
         * postgres://username:password@hostname:5432/database
         *
         * or:
         *
         * postgresql://username:password@hostname:5432/database
         */

        const std::regex pattern(
            R"(^(?:postgres|postgresql)://([^:]+):([^@]+)@([^:]+):([0-9]+)/(.+)$)"
        );

        std::smatch matches;

        if (!std::regex_match(
                databaseUrl,
                matches,
                pattern))
        {
            spdlog::error(
                "Invalid DATABASE_URL format."
            );

            return false;
        }

        const std::string user =
            matches[1].str();

        const std::string password =
            matches[2].str();

        const std::string host =
            matches[3].str();

        const std::string port =
            matches[4].str();

        const std::string database =
            matches[5].str();

        std::ofstream configFile(
            "render_config.json"
        );

        if (!configFile.is_open())
        {
            spdlog::error(
                "Unable to create Render database configuration."
            );

            return false;
        }

        configFile
            << "{\n"
            << "  \"db_clients\": [\n"
            << "    {\n"
            << "      \"name\": \"default\",\n"
            << "      \"rdbms\": \"postgresql\",\n"
            << "      \"host\": \""
            << host
            << "\",\n"
            << "      \"port\": "
            << port
            << ",\n"
            << "      \"dbname\": \""
            << database
            << "\",\n"
            << "      \"user\": \""
            << user
            << "\",\n"
            << "      \"passwd\": \""
            << password
            << "\",\n"
            << "      \"is_fast\": false,\n"
            << "      \"connection_number\": 1\n"
            << "    }\n"
            << "  ]\n"
            << "}\n";

        configFile.close();

        return true;
    }

    void loadDatabaseConfiguration()
    {
        const std::string databaseUrl =
            getEnvironmentVariable("DATABASE_URL");

        if (!databaseUrl.empty())
        {
            spdlog::info(
                "DATABASE_URL detected. "
                "Using Render PostgreSQL configuration."
            );

            if (!createRenderConfig())
            {
                throw std::runtime_error(
                    "Unable to create Render database configuration."
                );
            }

            drogon::app().loadConfigFile(
                "render_config.json"
            );

            return;
        }

        spdlog::info(
            "DATABASE_URL not found. "
            "Using local config.json."
        );

        drogon::app().loadConfigFile(
            "config.json"
        );
    }
}

int main()
{
    spdlog::info(
        "Starting LogeshwariMart..."
    );

    /*
     * Local:
     *     Uses config.json
     *
     * Render:
     *     Uses DATABASE_URL
     */
    loadDatabaseConfiguration();

    static std::atomic<unsigned long long>
        requestCounter{0};

    drogon::app().registerPreRoutingAdvice(
        [](const drogon::HttpRequestPtr& req)
        {
            const auto requestNumber =
                ++requestCounter;

            const std::string requestId =
                "REQ-" +
                std::to_string(requestNumber);

            req->attributes()->insert(
                "requestId",
                requestId
            );

            spdlog::info(
                "[{}] {} {}",
                requestId,
                req->methodString(),
                req->path()
            );
        }
    );

    registerAuthRoutes();
    registerProductRoutes();
    registerCartRoutes();
    registerOrderRoutes();
    registerAdminRoutes();
    registerReviewRoutes();
    registerChatbotRoutes();

    spdlog::info(
        "Calling registerHealthRoutes()..."
    );

    registerHealthRoutes();

    drogon::app().setDocumentRoot(
        "./frontend"
    );

    const char* portEnvironment =
        std::getenv("PORT");

    int port = 8080;

    if (portEnvironment != nullptr &&
        std::string(portEnvironment).empty() == false)
    {
        try
        {
            port =
                std::stoi(portEnvironment);
        }
        catch (...)
        {
            spdlog::warn(
                "Invalid PORT value. "
                "Using port 8080."
            );

            port = 8080;
        }
    }

    spdlog::info(
        "Starting Drogon server on port {}...",
        port
    );

    drogon::app().addListener(
        "0.0.0.0",
        port
    );

    drogon::app().run();

    return 0;
}
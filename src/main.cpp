#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include <atomic>
#include <cstdlib>
#include <fstream>
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
    std::string getEnvironmentVariable(const char* name)
    {
        const char* value = std::getenv(name);

        if (value == nullptr)
        {
            return "";
        }

        return std::string(value);
    }

    std::string percentDecode(const std::string& value)
    {
        std::string result;

        for (size_t i = 0; i < value.length(); ++i)
        {
            if (value[i] == '%' &&
                i + 2 < value.length())
            {
                try
                {
                    const int number =
                        std::stoi(
                            value.substr(i + 1, 2),
                            nullptr,
                            16
                        );

                    result +=
                        static_cast<char>(number);

                    i += 2;
                }
                catch (...)
                {
                    result += value[i];
                }
            }
            else if (value[i] == '+')
            {
                result += ' ';
            }
            else
            {
                result += value[i];
            }
        }

        return result;
    }

    std::string jsonEscape(const std::string& value)
    {
        std::string result;

        for (char c : value)
        {
            switch (c)
            {
                case '\\':
                    result += "\\\\";
                    break;

                case '"':
                    result += "\\\"";
                    break;

                case '\n':
                    result += "\\n";
                    break;

                case '\r':
                    result += "\\r";
                    break;

                case '\t':
                    result += "\\t";
                    break;

                default:
                    result += c;
                    break;
            }
        }

        return result;
    }

    bool createRenderConfig()
    {
        const std::string databaseUrl =
            getEnvironmentVariable("DATABASE_URL");

        if (databaseUrl.empty())
        {
            spdlog::error(
                "DATABASE_URL is empty."
            );

            return false;
        }

        spdlog::info(
            "Parsing DATABASE_URL..."
        );

        std::string url = databaseUrl;

        const std::string postgresScheme =
            "postgres://";

        const std::string postgresqlScheme =
            "postgresql://";

        if (url.rfind(postgresqlScheme, 0) == 0)
        {
            url =
                url.substr(
                    postgresqlScheme.length()
                );
        }
        else if (url.rfind(postgresScheme, 0) == 0)
        {
            url =
                url.substr(
                    postgresScheme.length()
                );
        }
        else
        {
            spdlog::error(
                "DATABASE_URL must start with "
                "postgres:// or postgresql://."
            );

            return false;
        }

        const size_t atPosition =
            url.rfind('@');

        if (atPosition == std::string::npos)
        {
            spdlog::error(
                "DATABASE_URL does not contain "
                "a valid user/password section."
            );

            return false;
        }

        const std::string userInfo =
            url.substr(
                0,
                atPosition
            );

        std::string serverPart =
            url.substr(
                atPosition + 1
            );

        const size_t colonPosition =
            userInfo.find(':');

        if (colonPosition == std::string::npos)
        {
            spdlog::error(
                "DATABASE_URL user/password format "
                "is invalid."
            );

            return false;
        }

        const std::string user =
            percentDecode(
                userInfo.substr(
                    0,
                    colonPosition
                )
            );

        const std::string password =
            percentDecode(
                userInfo.substr(
                    colonPosition + 1
                )
            );

        const size_t slashPosition =
            serverPart.find('/');

        if (slashPosition == std::string::npos)
        {
            spdlog::error(
                "DATABASE_URL does not contain "
                "a database name."
            );

            return false;
        }

        std::string hostPart =
            serverPart.substr(
                0,
                slashPosition
            );

        std::string databasePart =
            serverPart.substr(
                slashPosition + 1
            );

        const size_t queryPosition =
            databasePart.find('?');

        if (queryPosition != std::string::npos)
        {
            databasePart =
                databasePart.substr(
                    0,
                    queryPosition
                );
        }

        std::string host;
        std::string port = "5432";

        if (!hostPart.empty() &&
            hostPart.front() == '[')
        {
            const size_t closingBracket =
                hostPart.find(']');

            if (closingBracket == std::string::npos)
            {
                spdlog::error(
                    "Invalid IPv6 host format."
                );

                return false;
            }

            host =
                hostPart.substr(
                    1,
                    closingBracket - 1
                );

            if (closingBracket + 1 < hostPart.length() &&
                hostPart[closingBracket + 1] == ':')
            {
                port =
                    hostPart.substr(
                        closingBracket + 2
                    );
            }
        }
        else
        {
            const size_t portPosition =
                hostPart.rfind(':');

            if (portPosition != std::string::npos &&
                hostPart.find(':') == portPosition)
            {
                host =
                    hostPart.substr(
                        0,
                        portPosition
                    );

                port =
                    hostPart.substr(
                        portPosition + 1
                    );
            }
            else
            {
                host = hostPart;
            }
        }

        host =
            percentDecode(host);

        const std::string database =
            percentDecode(databasePart);

        if (user.empty() ||
            password.empty() ||
            host.empty() ||
            database.empty())
        {
            spdlog::error(
                "DATABASE_URL contains missing "
                "database connection information."
            );

            return false;
        }

        spdlog::info(
            "Render PostgreSQL host detected: {}",
            host
        );

        spdlog::info(
            "Render PostgreSQL port: {}",
            port
        );

        spdlog::info(
            "Render PostgreSQL database detected."
        );

        std::ofstream configFile(
            "render_config.json"
        );

        if (!configFile.is_open())
        {
            spdlog::error(
                "Unable to create render_config.json."
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
            << jsonEscape(host)
            << "\",\n"
            << "      \"port\": "
            << port
            << ",\n"
            << "      \"dbname\": \""
            << jsonEscape(database)
            << "\",\n"
            << "      \"user\": \""
            << jsonEscape(user)
            << "\",\n"
            << "      \"passwd\": \""
            << jsonEscape(password)
            << "\",\n"
            << "      \"is_fast\": false,\n"
            << "      \"connection_number\": 1\n"
            << "    }\n"
            << "  ]\n"
            << "}\n";

        configFile.close();

        spdlog::info(
            "render_config.json created successfully."
        );

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
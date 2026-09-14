#include <drogon/drogon.h>
#include "../repository/UserRepository.h"
#include "../service/AuthService.h"

using namespace drogon;

void registerAuthRoutes()
{
    app().registerHandler(
        "/api/register",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("name") ||
                !json->isMember("email") ||
                !json->isMember("password") ||
                !json->isMember("role"))
            {
                response->setBody(
                    R"({"success":false,"message":"All fields are required"})"
                );

                callback(response);
                return;
            }

            std::string name = (*json)["name"].asString();
            std::string email = (*json)["email"].asString();
            std::string password = (*json)["password"].asString();
            std::string role = (*json)["role"].asString();

            UserRepository repository;

            if (repository.userExists(email))
            {
                response->setBody(
                    R"({"success":false,"message":"Email already exists"})"
                );

                callback(response);
                return;
            }

            AuthService authService;

            std::string passwordHash =
                authService.hashPassword(password);

            if (passwordHash.empty())
            {
                response->setBody(
                    R"({"success":false,"message":"Password hashing failed"})"
                );

                callback(response);
                return;
            }

            bool registered = repository.registerUser(
                name,
                email,
                passwordHash,
                role
            );

            if (registered)
            {
                response->setBody(
                    R"({"success":true,"message":"Registration successful"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Registration failed"})"
                );
            }

            callback(response);
        },
        {Post}
    );

    app().registerHandler(
        "/api/login",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("email") ||
                !json->isMember("password"))
            {
                response->setBody(
                    R"({"success":false,"message":"Email and password are required"})"
                );

                callback(response);
                return;
            }

            std::string email = (*json)["email"].asString();
            std::string password = (*json)["password"].asString();

            UserRepository repository;

            if (!repository.userExists(email))
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid email or password"})"
                );

                callback(response);
                return;
            }

            std::string passwordHash =
                repository.getPasswordHash(email);

            AuthService authService;

            if (authService.verifyPassword(password, passwordHash))
            {
                response->setBody(
                    R"({"success":true,"message":"Login successful"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid email or password"})"
                );
            }

            callback(response);
        },
        {Post}
    );
}
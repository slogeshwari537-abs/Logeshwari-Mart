#include <drogon/drogon.h>

#include "../repository/UserRepository.h"
#include "../service/AuthService.h"
#include "../service/SessionManager.h"

using namespace drogon;

void registerAuthRoutes()
{
    // =========================
    // REGISTER
    // =========================
    app().registerHandler(
        "/api/register",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON
            );

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

            std::string name =
                (*json)["name"].asString();

            std::string email =
                (*json)["email"].asString();

            std::string password =
                (*json)["password"].asString();

            std::string role =
                (*json)["role"].asString();

            // Admin registration is not allowed
            if (role == "ADMIN")
            {
                response->setBody(
                    R"({"success":false,"message":"Admin registration is not allowed"})"
                );

                callback(response);
                return;
            }

            // Only BUYER and SELLER are allowed
            if (role != "BUYER" &&
                role != "SELLER")
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid role"})"
                );

                callback(response);
                return;
            }

            // Empty field validation
            if (name.empty() ||
                email.empty() ||
                password.empty())
            {
                response->setBody(
                    R"({"success":false,"message":"Name, email and password cannot be empty"})"
                );

                callback(response);
                return;
            }

            UserRepository repository;

            // Check existing email
            if (repository.userExists(email))
            {
                response->setBody(
                    R"({"success":false,"message":"Email already exists"})"
                );

                callback(response);
                return;
            }

            // Hash password
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

            // Register user
            bool registered =
                repository.registerUser(
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


    // =========================
    // LOGIN
    // =========================
    app().registerHandler(
        "/api/login",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                CT_APPLICATION_JSON
            );

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

            std::string email =
                (*json)["email"].asString();

            std::string password =
                (*json)["password"].asString();

            // Empty field validation
            if (email.empty() ||
                password.empty())
            {
                response->setBody(
                    R"({"success":false,"message":"Email and password cannot be empty"})"
                );

                callback(response);
                return;
            }

            UserRepository repository;

            // Check user
            if (!repository.userExists(email))
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid email or password"})"
                );

                callback(response);
                return;
            }

            // Get password hash
            std::string passwordHash =
                repository.getPasswordHash(email);

            AuthService authService;

            // Verify password
            if (!authService.verifyPassword(
                    password,
                    passwordHash))
            {
                response->setBody(
                    R"({"success":false,"message":"Invalid email or password"})"
                );

                callback(response);
                return;
            }

            // Get user details
            auto user =
                repository.getUserByEmail(email);

            if (!user.has_value())
            {
                response->setBody(
                    R"({"success":false,"message":"User information not found"})"
                );

                callback(response);
                return;
            }

            // =========================
            // CREATE LOGIN SESSION
            // =========================

            std::string sessionToken =
                ::SessionManager::getInstance()
                    .createSession(user->id);

            if (sessionToken.empty())
            {
                response->setBody(
                    R"({"success":false,"message":"Session creation failed"})"
                );

                callback(response);
                return;
            }

            // =========================
            // SET SESSION COOKIE
            // =========================

            response->addHeader(
                "Set-Cookie",
                "session_token=" + sessionToken +
                "; Path=/; HttpOnly"
            );

            // =========================
            // LOGIN RESPONSE
            // =========================

            Json::Value result;

            result["success"] = true;
            result["message"] = "Login successful";
            result["userId"] = user->id;
            result["name"] = user->name;
            result["email"] = user->email;
            result["role"] = user->role;

            // Keep token in response also
            result["token"] = sessionToken;

            response->setBody(
                result.toStyledString()
            );

            callback(response);
        },
        {Post}
    );
}
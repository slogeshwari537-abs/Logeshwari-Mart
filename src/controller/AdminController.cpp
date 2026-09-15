#include <drogon/drogon.h>

#include "../repository/AdminRepository.h"
#include "../util/RoleUtil.h"

void registerAdminRoutes()
{
    drogon::app().registerHandler(
        "/api/admin/users",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            auto role = req->getParameter("role");

            if (!isAdmin(role))
            {
                auto response =
                    drogon::HttpResponse::newHttpResponse();

                response->setStatusCode(
                    drogon::k403Forbidden
                );

                response->setBody(
                    "Admin access required"
                );

                callback(response);
                return;
            }

            AdminRepository repository;
            auto users = repository.getAllUsers();

            Json::Value result(Json::arrayValue);

            for (const auto& user : users)
            {
                Json::Value item;

                item["id"] = user.id;
                item["name"] = user.name;
                item["email"] = user.email;
                item["role"] = user.role;

                result.append(item);
            }

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(result);

            callback(response);
        },
        {drogon::Get}
    );

    drogon::app().registerHandler(
        "/api/admin/users/{1}",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto role = req->getParameter("role");

            if (!isAdmin(role))
            {
                auto response =
                    drogon::HttpResponse::newHttpResponse();

                response->setStatusCode(
                    drogon::k403Forbidden
                );

                response->setBody(
                    "Admin access required"
                );

                callback(response);
                return;
            }

            AdminRepository repository;

            if (!repository.deleteUser(userId))
            {
                auto response =
                    drogon::HttpResponse::newHttpResponse();

                response->setStatusCode(
                    drogon::k400BadRequest
                );

                response->setBody(
                    "Failed to delete user"
                );

                callback(response);
                return;
            }

            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setBody(
                "User deleted successfully"
            );

            callback(response);
        },
        {drogon::Delete}
    );
}
#include <drogon/drogon.h>
#include "../repository/AdminRepository.h"

using namespace drogon;

void registerAdminRoutes()
{
    // View All Users
    app().registerHandler(
        "/api/admin/users",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

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

            response->setBody(result.toStyledString());

            callback(response);
        },
        {Get}
    );

    // Delete User
    app().registerHandler(
        "/api/admin/users/{userId}",
        [](const HttpRequestPtr&,
           std::function<void(const HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto response = HttpResponse::newHttpResponse();
            response->setContentTypeCode(CT_APPLICATION_JSON);

            AdminRepository repository;

            if (repository.deleteUser(userId))
            {
                response->setBody(
                    R"({"success":true,"message":"User deleted successfully"})"
                );
            }
            else
            {
                response->setBody(
                    R"({"success":false,"message":"Failed to delete user"})"
                );
            }

            callback(response);
        },
        {Delete}
    );
}
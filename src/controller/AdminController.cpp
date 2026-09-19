#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include "../repository/AdminRepository.h"
#include "../repository/UserRepository.h"
#include "../service/SessionManager.h"


// ============================================================
// GET AUTHENTICATED USER ID DIRECTLY FROM SESSION TOKEN
// ============================================================

int getAuthenticatedUserId(
    const drogon::HttpRequestPtr& req)
{
    // First check X-Auth-Token header
    std::string token =
        req->getHeader("X-Auth-Token");

    // If header is empty, check session_token cookie
    if (token.empty())
    {
        std::string cookie =
            req->getHeader("Cookie");

        const std::string cookieName =
            "session_token=";

        std::size_t position =
            cookie.find(cookieName);

        if (position != std::string::npos)
        {
            position += cookieName.length();

            std::size_t end =
                cookie.find(";", position);

            if (end == std::string::npos)
            {
                token =
                    cookie.substr(position);
            }
            else
            {
                token =
                    cookie.substr(
                        position,
                        end - position
                    );
            }
        }
    }

    // No token found
    if (token.empty())
    {
        return -1;
    }

    // Get user ID from SessionManager
    return SessionManager::getInstance()
        .getUserId(token);
}


// ============================================================
// ADMIN ROUTES
// ============================================================

void registerAdminRoutes()
{

    // ========================================================
    // GET ALL USERS
    // ========================================================

    drogon::app().registerHandler(
        "/api/admin/users",

        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&)>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );

            // Get logged-in user directly from session
            int authenticatedUserId =
                getAuthenticatedUserId(req);

            spdlog::info(
                "Admin check - authenticatedUserId: {}",
                authenticatedUserId
            );

            UserRepository userRepository;

            auto adminUser =
                userRepository.getUserById(
                    authenticatedUserId
                );

            spdlog::info(
                "Admin check - role: {}",
                adminUser.has_value()
                    ? adminUser->role
                    : "NO USER"
            );

            // Check ADMIN role
            if (!adminUser.has_value() ||
                adminUser->role != "ADMIN")
            {
                response->setStatusCode(
                    drogon::k403Forbidden
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Admin access required";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            // Get all users
            AdminRepository repository;

            auto users =
                repository.getAllUsers();

            Json::Value result(
                Json::arrayValue
            );

            for (const auto& user : users)
            {
                Json::Value item;

                item["id"] = user.id;
                item["name"] = user.name;
                item["email"] = user.email;
                item["role"] = user.role;

                result.append(item);
            }

            Json::Value body;

            body["success"] = true;
            body["users"] = result;

            response->setBody(
                body.toStyledString()
            );

            callback(response);
        },

        {drogon::Get},

        {"AuthFilter"}
    );


    // ========================================================
    // DELETE USER
    // ========================================================

    drogon::app().registerHandler(
        "/api/admin/users/{1}",

        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&)>&& callback,
           int userId)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );

            int authenticatedUserId =
                getAuthenticatedUserId(req);

            UserRepository userRepository;

            auto adminUser =
                userRepository.getUserById(
                    authenticatedUserId
                );

            // Check ADMIN role
            if (!adminUser.has_value() ||
                adminUser->role != "ADMIN")
            {
                response->setStatusCode(
                    drogon::k403Forbidden
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Admin access required";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            // Prevent admin deleting own account
            if (userId == authenticatedUserId)
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Admin cannot delete their own account";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            AdminRepository repository;

            if (!repository.deleteUser(userId))
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Failed to delete user";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            Json::Value body;

            body["success"] = true;
            body["message"] =
                "User deleted successfully";

            response->setBody(
                body.toStyledString()
            );

            callback(response);
        },

        {drogon::Delete},

        {"AuthFilter"}
    );


    // ========================================================
    // GET ALL ORDERS
    // ========================================================

    drogon::app().registerHandler(
        "/api/admin/orders",

        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&)>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );

            int authenticatedUserId =
                getAuthenticatedUserId(req);

            UserRepository userRepository;

            auto adminUser =
                userRepository.getUserById(
                    authenticatedUserId
                );

            // Check ADMIN role
            if (!adminUser.has_value() ||
                adminUser->role != "ADMIN")
            {
                response->setStatusCode(
                    drogon::k403Forbidden
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Admin access required";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            // Get all orders
            AdminRepository repository;

            auto orders =
                repository.getAllOrders();

            Json::Value result(
                Json::arrayValue
            );

            for (const auto& order : orders)
            {
                Json::Value item;

                item["id"] = order.id;
                item["buyer_id"] = order.buyer_id;
                item["status"] = order.status;

                item["total_amount_cents"] =
                    static_cast<Json::Int64>(
                        order.total_amount_cents
                    );

                result.append(item);
            }

            Json::Value body;

            body["success"] = true;
            body["orders"] = result;

            response->setBody(
                body.toStyledString()
            );

            callback(response);
        },

        {drogon::Get},

        {"AuthFilter"}
    );


    // ========================================================
    // DELETE LISTING / PRODUCT
    // ========================================================

    drogon::app().registerHandler(
        "/api/admin/products/{1}",

        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&)>&& callback,
           int productId)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();

            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );

            int authenticatedUserId =
                getAuthenticatedUserId(req);

            UserRepository userRepository;

            auto adminUser =
                userRepository.getUserById(
                    authenticatedUserId
                );

            // Check ADMIN role
            if (!adminUser.has_value() ||
                adminUser->role != "ADMIN")
            {
                response->setStatusCode(
                    drogon::k403Forbidden
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Admin access required";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            AdminRepository repository;

            if (!repository.deleteProduct(productId))
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );

                Json::Value body;

                body["success"] = false;
                body["message"] =
                    "Failed to remove listing";

                response->setBody(
                    body.toStyledString()
                );

                callback(response);
                return;
            }

            Json::Value body;

            body["success"] = true;
            body["message"] =
                "Listing removed successfully";

            response->setBody(
                body.toStyledString()
            );

            callback(response);
        },

        {drogon::Delete},

        {"AuthFilter"}
    );
}
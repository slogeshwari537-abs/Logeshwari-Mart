#pragma once

#include <drogon/drogon.h>
#include "../service/SessionManager.h"

class AuthFilter
    : public drogon::HttpFilter<AuthFilter>
{
public:

    AuthFilter()
    {
    }

    void doFilter(
        const drogon::HttpRequestPtr& req,
        drogon::FilterCallback&& fcb,
        drogon::FilterChainCallback&& fccb) override
    {
        // =========================
        // GET AUTHENTICATION TOKEN
        // =========================

        std::string token =
            req->getHeader("X-Auth-Token");

        // If header token is missing,
        // check session_token cookie
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

        // =========================
        // TOKEN MISSING
        // =========================

        if (token.empty())
        {
            Json::Value body;

            body["success"] = false;
            body["message"] =
                "Authentication required";

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(
                    body
                );

            response->setStatusCode(
                drogon::k401Unauthorized
            );

            fcb(response);
            return;
        }

        // =========================
        // SESSION MANAGER
        // =========================

        SessionManager& sessionManager =
            SessionManager::getInstance();

        // =========================
        // CHECK SESSION
        // =========================

        if (!sessionManager.isValidSession(token))
        {
            Json::Value body;

            body["success"] = false;
            body["message"] =
                "Invalid or expired session";

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(
                    body
                );

            response->setStatusCode(
                drogon::k401Unauthorized
            );

            fcb(response);
            return;
        }

        // =========================
        // GET USER ID
        // =========================

        int userId =
            sessionManager.getUserId(token);

        if (userId <= 0)
        {
            Json::Value body;

            body["success"] = false;
            body["message"] =
                "Invalid authentication session";

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(
                    body
                );

            response->setStatusCode(
                drogon::k401Unauthorized
            );

            fcb(response);
            return;
        }

        // =========================
        // STORE USER ID AS INTEGER
        // =========================

        req->attributes()->insert(
            "authenticatedUserId",
            userId
        );

        // =========================
        // AUTHENTICATION SUCCESS
        // =========================

        fccb();
    }
};
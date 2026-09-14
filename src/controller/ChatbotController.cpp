#include "ChatbotController.h"
#include "../service/ChatbotService.h"

#include <drogon/drogon.h>

void registerChatbotRoutes()
{
    drogon::app().registerHandler(
        "/api/chat",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            auto json = req->getJsonObject();

            if (!json ||
                !json->isMember("message") ||
                !(*json)["message"].isString())
            {
                Json::Value error;
                error["success"] = false;
                error["message"] = "Message is required";

                auto response =
                    drogon::HttpResponse::newHttpJsonResponse(error);

                callback(response);
                return;
            }

            std::string message =
                (*json)["message"].asString();

            ChatbotService chatbot;

            std::string reply =
                chatbot.getResponse(message);

            Json::Value result;
            result["success"] = true;
            result["reply"] = reply;

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(result);

            callback(response);
        },
        {drogon::Post}
    );
}
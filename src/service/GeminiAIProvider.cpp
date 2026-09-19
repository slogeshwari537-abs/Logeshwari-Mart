#include "GeminiAIProvider.h"

#include <drogon/drogon.h>

#include <cstdlib>
#include <stdexcept>
#include <string>

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

    std::string getEnvOrDefault(
        const char* name,
        const std::string& defaultValue)
    {
        std::string value =
            getEnvironmentVariable(name);

        if (value.empty())
        {
            return defaultValue;
        }

        return value;
    }
}

GeminiAIProvider::GeminiAIProvider()
{
    apiKey_ =
        getEnvironmentVariable("GEMINI_API_KEY");

    model_ =
        getEnvOrDefault(
            "GEMINI_MODEL",
            "gemini-3.5-flash");

    std::string timeoutText =
        getEnvOrDefault(
            "AI_CHATBOT_TIMEOUT_SECONDS",
            "10");

    try
    {
        timeoutSeconds_ =
            std::stoi(timeoutText);
    }
    catch (...)
    {
        timeoutSeconds_ = 10;
    }

    if (timeoutSeconds_ <= 0)
    {
        timeoutSeconds_ = 10;
    }
}

std::string GeminiAIProvider::getResponse(
    const std::string& prompt)
{
    if (apiKey_.empty())
    {
        return "AI service is not configured. "
               "Please try again later.";
    }

    auto request =
        drogon::HttpRequest::newHttpRequest();

    request->setMethod(
        drogon::Post);

    request->setPath(
        "/v1beta/models/" +
        model_ +
        ":generateContent");

    request->addHeader(
        "x-goog-api-key",
        apiKey_);

    request->setContentTypeCode(
        drogon::CT_APPLICATION_JSON);

    Json::Value body;

    Json::Value systemInstruction;
    Json::Value systemParts;

    systemParts["text"] =
        "You are the official LogeshwariMart "
        "shopping assistant. "
        "Answer only questions related to "
        "LogeshwariMart products, shopping, "
        "cart, orders, checkout, payment, "
        "reviews, ratings and seller information. "
        "Be concise, friendly and helpful. "
        "Do not invent product prices, stock "
        "quantities or order information. "
        "If the question is outside the "
        "LogeshwariMart domain, politely say "
        "that you can only help with LogeshwariMart.";

    systemInstruction["parts"] =
        systemParts;

    body["system_instruction"] =
        systemInstruction;

    Json::Value contents;
    Json::Value userParts;

    userParts["text"] =
        prompt;

    contents["parts"] =
        userParts;

    body["contents"] =
        contents;

    Json::Value generationConfig;

    generationConfig["temperature"] = 0.3;
    generationConfig["maxOutputTokens"] = 300;

    body["generationConfig"] =
        generationConfig;

    request->setBody(
        body.toStyledString());

    try
    {
        auto client =
            drogon::HttpClient::newHttpClient(
                "https://generativelanguage.googleapis.com");

        client->setConnectionTimeout(
            timeoutSeconds_);

        client->setRecvTimeout(
            timeoutSeconds_);

        client->setSendTimeout(
            timeoutSeconds_);

        auto result =
            client->sendRequest(request);

        if (result.first !=
            drogon::ReqResult::Ok)
        {
            return "Sorry, the AI service is "
                   "temporarily unavailable. "
                   "Please try again later.";
        }

        auto response =
            result.second;

        if (!response)
        {
            return "Sorry, the AI service did not "
                   "return a response.";
        }

        if (response->getStatusCode() < 200 ||
            response->getStatusCode() >= 300)
        {
            return "Sorry, the AI service is "
                   "temporarily unavailable.";
        }

        auto responseJson =
            response->getJsonObject();

        if (!responseJson)
        {
            return "Sorry, I received an invalid "
                   "response from the AI service.";
        }

        if (!responseJson->isMember("candidates") ||
            !(*responseJson)["candidates"].isArray() ||
            (*responseJson)["candidates"].empty())
        {
            return "Sorry, the AI service could "
                   "not generate a response.";
        }

        const auto& candidate =
            (*responseJson)["candidates"][0];

        if (!candidate.isMember("content"))
        {
            return "Sorry, the AI service returned "
                   "an empty response.";
        }

        const auto& content =
            candidate["content"];

        if (!content.isMember("parts") ||
            !content["parts"].isArray() ||
            content["parts"].empty())
        {
            return "Sorry, the AI service returned "
                   "an empty response.";
        }

        const auto& part =
            content["parts"][0];

        if (!part.isMember("text") ||
            !part["text"].isString())
        {
            return "Sorry, the AI service returned "
                   "an empty response.";
        }

        return part["text"].asString();
    }
    catch (const std::exception&)
    {
        return "Sorry, the AI service is "
               "temporarily unavailable. "
               "Please try again later.";
    }
}
#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

void registerHealthRoutes()
{
    spdlog::info("REGISTERING HEALTH ROUTE");

    drogon::app().registerHandler(
        "/api/v1/health",
        [](const drogon::HttpRequestPtr&,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            spdlog::info("HEALTH ROUTE CALLED");

            Json::Value response;
            response["status"] = "UP";
            response["db"] = "UP";

            auto httpResponse =
                drogon::HttpResponse::newHttpJsonResponse(response);

            callback(httpResponse);
        },
        {drogon::Get}
    );
}
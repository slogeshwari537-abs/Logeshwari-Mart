#pragma once

#include "IAIProvider.h"

#include <string>

/**
 * @brief Provides Google Gemini-based AI responses.
 */
class GeminiAIProvider : public IAIProvider
{
public:
    /**
     * @brief Creates a Gemini AI provider using environment configuration.
     */
    GeminiAIProvider();

    /**
     * @brief Sends a prompt to the Gemini API and returns the response.
     *
     * @param prompt User prompt sent to the AI provider.
     * @return AI-generated response or a safe error message.
     */
    std::string getResponse(
        const std::string& prompt) override;

private:
    std::string apiKey_;
    std::string model_;
    int timeoutSeconds_;
};
#pragma once

#include <memory>
#include <string>

#include "IAIProvider.h"

/**
 * @brief Provides chatbot functionality for Logeshwari Mart.
 */
class ChatbotService
{
public:
    /**
     * @brief Creates a chatbot service with the configured AI provider.
     */
    ChatbotService();

    /**
     * @brief Generates a response for a user's chatbot message.
     *
     * @param message User's chatbot message.
     * @return AI-generated or fallback chatbot response.
     */
    std::string getResponse(
        const std::string& message
    );

private:
    std::unique_ptr<IAIProvider> provider_;
};
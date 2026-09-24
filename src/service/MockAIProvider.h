#pragma once

#include "IAIProvider.h"

/**
 * @brief Provides a local mock implementation of the AI provider.
 */
class MockAIProvider : public IAIProvider
{
public:
    /**
     * @brief Generates a mock chatbot response.
     *
     * @param prompt User prompt.
     * @return Mock response generated for the prompt.
     */
    std::string getResponse(
        const std::string& prompt) override;
};
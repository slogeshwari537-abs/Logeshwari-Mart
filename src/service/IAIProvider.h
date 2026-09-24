#pragma once

#include <string>

/**
 * @brief Interface for AI response providers.
 */
class IAIProvider
{
public:
    /**
     * @brief Virtual destructor for the AI provider interface.
     */
    virtual ~IAIProvider() = default;

    /**
     * @brief Generates a response for a given prompt.
     *
     * @param prompt Input prompt sent to the AI provider.
     * @return Generated response.
     */
    virtual std::string getResponse(
        const std::string& prompt) = 0;
};
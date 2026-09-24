#pragma once

#include <memory>
#include <string>

#include "IAIProvider.h"

/**
 * @brief Creates the configured AI provider implementation.
 */
class AIProviderFactory
{
public:
    /**
     * @brief Creates an AI provider based on the provider name.
     *
     * @param provider Provider name such as "gemini" or "mock".
     * @return A unique pointer to the selected AI provider.
     */
    static std::unique_ptr<IAIProvider> createProvider(
        const std::string& provider);
};
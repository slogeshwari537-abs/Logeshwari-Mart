#include "AIProviderFactory.h"
#include "MockAIProvider.h"

#include <stdexcept>

std::unique_ptr<IAIProvider> AIProviderFactory::createProvider(
    const std::string& provider)
{
    if (provider == "mock")
    {
        return std::make_unique<MockAIProvider>();
    }

    throw std::runtime_error("Unsupported AI provider: " + provider);
}
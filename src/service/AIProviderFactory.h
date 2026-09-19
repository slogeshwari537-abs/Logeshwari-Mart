#pragma once

#include <memory>
#include <string>

#include "IAIProvider.h"

class AIProviderFactory
{
public:
    static std::unique_ptr<IAIProvider> createProvider(
        const std::string& provider);
};
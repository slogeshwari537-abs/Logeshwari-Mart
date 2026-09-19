#pragma once

#include <memory>
#include <string>

#include "IAIProvider.h"

class ChatbotService
{
public:
    ChatbotService();

    std::string getResponse(const std::string& message);

private:
    std::unique_ptr<IAIProvider> provider_;
};
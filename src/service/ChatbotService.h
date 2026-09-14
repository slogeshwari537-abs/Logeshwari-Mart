#pragma once

#include <string>

class ChatbotService
{
public:
    std::string getResponse(const std::string& message);
};
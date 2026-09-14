#include "ChatbotService.h"

#include <algorithm>
#include <cctype>

std::string ChatbotService::getResponse(
    const std::string& message)
{
    std::string text = message;

    std::transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        });

    if (text.find("hello") != std::string::npos ||
        text.find("hi") != std::string::npos)
    {
        return "Hello! Welcome to LogeshwariMart. How can I help you?";
    }

    if (text.find("product") != std::string::npos)
    {
        return "You can browse products using the product API.";
    }

    if (text.find("cart") != std::string::npos)
    {
        return "You can add products to your cart and update the quantity.";
    }

    if (text.find("order") != std::string::npos)
    {
        return "You can view your order history using the orders API.";
    }

    if (text.find("review") != std::string::npos ||
        text.find("rating") != std::string::npos)
    {
        return "You can give a rating from 1 to 5 and add a review.";
    }

    if (text.find("help") != std::string::npos)
    {
        return "I can help with products, cart, orders, reviews and ratings.";
    }

    return "Sorry, I did not understand. Please ask about products, cart, orders or reviews.";
}
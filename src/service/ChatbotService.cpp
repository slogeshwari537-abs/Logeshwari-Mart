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

    // Greeting
    if (text.find("hello") != std::string::npos ||
        text.find("hi") != std::string::npos ||
        text.find("hey") != std::string::npos)
    {
        return "Hello! Welcome to LogeshwariMart. How can I help you?";
    }

    // Cart-related questions
    if (text.find("cart") != std::string::npos ||
        text.find("add to cart") != std::string::npos ||
        text.find("remove from cart") != std::string::npos ||
        text.find("update cart") != std::string::npos)
    {
        return "You can add products to your cart, update the quantity, remove products and clear your cart.";
    }

    // Order-related questions
    if (text.find("order") != std::string::npos ||
        text.find("checkout") != std::string::npos ||
        text.find("payment") != std::string::npos)
    {
        return "You can checkout your cart using mock payment and view your order history.";
    }

    // Review-related questions
    if (text.find("review") != std::string::npos ||
        text.find("rating") != std::string::npos)
    {
        return "You can give a rating from 1 to 5 and add a review for a product.";
    }

    // Product-related questions
    if (text.find("product") != std::string::npos ||
        text.find("products") != std::string::npos ||
        text.find("search") != std::string::npos ||
        text.find("category") != std::string::npos)
    {
        return "You can browse, search and filter products by keyword and category.";
    }

    // Help
    if (text.find("help") != std::string::npos)
    {
        return "I can help with products, cart, orders, checkout, reviews and ratings.";
    }

    // Default response
    return "Sorry, I did not understand. Please ask about products, cart, orders, checkout or reviews.";
}
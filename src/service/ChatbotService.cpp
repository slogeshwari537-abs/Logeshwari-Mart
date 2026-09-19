
#include "ChatbotService.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <drogon/drogon.h>

namespace
{
    std::string toLower(std::string text)
    {
        std::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(
                    std::tolower(c));
            });

        return text;
    }
}

std::string ChatbotService::getResponse(
    const std::string& message)
{
    std::string text = toLower(message);

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

    // Product price / stock questions
    if (text.find("price") != std::string::npos ||
        text.find("cost") != std::string::npos ||
        text.find("how much") != std::string::npos ||
        text.find("stock") != std::string::npos ||
        text.find("available") != std::string::npos)
    {
        try
        {
            auto client =
                drogon::app().getDbClient();

            auto result =
                client->execSqlSync(
                    "SELECT name, price_cents, stock_qty "
                    "FROM products "
                    "ORDER BY id");

            for (const auto& row : result)
            {
                std::string productName =
                    row["name"].as<std::string>();

                std::string lowerProductName =
                    toLower(productName);

                if (text.find(lowerProductName) !=
                    std::string::npos)
                {
                    long long priceCents =
                        row["price_cents"].as<long long>();

                    int stock =
                        row["stock_qty"].as<int>();

                    if (text.find("stock") !=
                            std::string::npos ||
                        text.find("available") !=
                            std::string::npos)
                    {
                        return productName +
                               " has " +
                               std::to_string(stock) +
                               " item(s) in stock.";
                    }

                    double price =
                        static_cast<double>(
                            priceCents) /
                        100.0;

                    char priceText[50];

                    std::snprintf(
                        priceText,
                        sizeof(priceText),
                        "%.2f",
                        price);

                    return "The price of " +
                           productName +
                           " is ₹" +
                           priceText + ".";
                }
            }

            return "I could not find that product. Please check the product name.";
        }
        catch (const std::exception&)
        {
            return "Sorry, I could not access the product information right now.";
        }
    }

    // General product questions
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


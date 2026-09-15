#pragma once

#include <string>

inline bool isAdmin(const std::string& role)
{
    return role == "ADMIN";
}

inline bool isSeller(const std::string& role)
{
    return role == "SELLER";
}

inline bool isBuyer(const std::string& role)
{
    return role == "BUYER";
}
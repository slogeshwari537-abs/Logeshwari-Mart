#pragma once

#include <string>

struct User
{
    int id;
    std::string name;
    std::string email;
    std::string password_hash;
    std::string role;

    bool isAdmin() const
    {
        return role == "ADMIN";
    }

    bool isSeller() const
    {
        return role == "SELLER";
    }

    bool isBuyer() const
    {
        return role == "BUYER";
    }
};
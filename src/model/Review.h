#pragma once

#include <string>

struct Review
{
    int id;
    int product_id;
    int user_id;
    int rating;
    std::string comment;
};
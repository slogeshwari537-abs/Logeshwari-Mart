#pragma once

#include <vector>
#include "../model/User.h"

class AdminRepository
{
public:
    std::vector<User> getAllUsers();

    bool deleteUser(int userId);
};
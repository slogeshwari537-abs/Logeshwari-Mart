#pragma once

#include <vector>

#include "../model/User.h"
#include "../model/Order.h"

class AdminRepository
{
public:
    std::vector<User> getAllUsers();

    bool deleteUser(int userId);

    std::vector<Order> getAllOrders();

    bool deleteProduct(int productId);
};
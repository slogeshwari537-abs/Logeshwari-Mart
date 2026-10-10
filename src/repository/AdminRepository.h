#pragma once

#include <vector>

#include "../model/Order.h"
#include "../model/Product.h"
#include "../model/User.h"

/**
 * @brief Provides database operations used by administrators.
 */
class AdminRepository
{
public:
    std::vector<User> getAllUsers();

    bool deleteUser(int userId);

    std::vector<Order> getAllOrders();

    std::vector<Product> getAllProducts();

    bool deleteProduct(int productId);
};

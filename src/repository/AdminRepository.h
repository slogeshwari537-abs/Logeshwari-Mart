#pragma once

#include <vector>

#include "../model/Order.h"
#include "../model/User.h"

/**
 * @brief Provides database operations used by administrators.
 */
class AdminRepository
{
public:
    /**
     * @brief Retrieves all registered users.
     *
     * @return A vector containing all users.
     */
    std::vector<User> getAllUsers();

    /**
     * @brief Deletes a user by ID.
     *
     * @param userId ID of the user to delete.
     * @return true if the user is deleted successfully; otherwise false.
     */
    bool deleteUser(int userId);

    /**
     * @brief Retrieves all orders.
     *
     * @return A vector containing all orders.
     */
    std::vector<Order> getAllOrders();

    /**
     * @brief Removes a product listing by ID.
     *
     * @param productId ID of the product to delete.
     * @return true if the product is deleted successfully; otherwise false.
     */
    bool deleteProduct(int productId);
};
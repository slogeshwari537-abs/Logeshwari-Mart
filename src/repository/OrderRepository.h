#pragma once

#include <vector>

#include "../model/Order.h"

/**
 * @brief Provides database operations for customer orders.
 */
class OrderRepository
{
public:
    /**
     * @brief Creates a new order for a buyer.
     *
     * @param buyerId ID of the buyer.
     * @param totalAmountCents Total order amount in cents.
     * @return true if the order is created successfully; otherwise false.
     */
    bool createOrder(
        int buyerId,
        long long totalAmountCents
    );

    /**
     * @brief Retrieves orders belonging to a buyer.
     *
     * @param buyerId ID of the buyer.
     * @return A vector containing the buyer's orders.
     */
    std::vector<Order> getOrdersByBuyer(
        int buyerId
    );

    /**
     * @brief Retrieves orders containing products from a seller.
     *
     * @param sellerId ID of the seller.
     * @return A vector containing the seller's incoming orders.
     */
    std::vector<Order> getOrdersBySeller(
        int sellerId
    );
};
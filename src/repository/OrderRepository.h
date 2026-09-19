#pragma once

#include <vector>
#include "../model/Order.h"

class OrderRepository
{
public:
    bool createOrder(
        int buyerId,
        long long totalAmountCents
    );

    std::vector<Order> getOrdersByBuyer(
        int buyerId
    );

    std::vector<Order> getOrdersBySeller(
        int sellerId
    );
};
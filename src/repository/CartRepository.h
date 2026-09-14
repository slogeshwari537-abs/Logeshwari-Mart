#pragma once

#include <vector>
#include "../model/CartItem.h"

class CartRepository
{
public:
    bool addToCart(int userId, int productId, int quantity);

    std::vector<CartItem> getCart(int userId);

    bool updateCartItem(int userId, int productId, int quantity);

    bool removeFromCart(int userId, int productId);

    bool clearCart(int userId);
};
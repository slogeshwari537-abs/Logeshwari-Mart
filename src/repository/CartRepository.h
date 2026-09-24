#pragma once

#include <vector>

#include "../model/CartItem.h"

/**
 * @brief Provides database operations for shopping carts.
 */
class CartRepository
{
public:
    /**
     * @brief Adds a product to a user's shopping cart.
     *
     * @param userId ID of the user.
     * @param productId ID of the product.
     * @param quantity Quantity to add.
     * @return true if the item is added successfully; otherwise false.
     */
    bool addToCart(
        int userId,
        int productId,
        int quantity
    );

    /**
     * @brief Retrieves all items in a user's shopping cart.
     *
     * @param userId ID of the user.
     * @return A vector containing the user's cart items.
     */
    std::vector<CartItem> getCart(
        int userId
    );

    /**
     * @brief Updates the quantity of a cart item.
     *
     * @param userId ID of the user.
     * @param productId ID of the product.
     * @param quantity New quantity.
     * @return true if the item is updated successfully; otherwise false.
     */
    bool updateCartItem(
        int userId,
        int productId,
        int quantity
    );

    /**
     * @brief Removes a product from a user's cart.
     *
     * @param userId ID of the user.
     * @param productId ID of the product.
     * @return true if the item is removed successfully; otherwise false.
     */
    bool removeFromCart(
        int userId,
        int productId
    );

    /**
     * @brief Removes all items from a user's cart.
     *
     * @param userId ID of the user.
     * @return true if the cart is cleared successfully; otherwise false.
     */
    bool clearCart(
        int userId
    );
};
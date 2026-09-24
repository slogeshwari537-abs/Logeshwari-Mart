#pragma once

#include <string>
#include <vector>

#include "../model/Review.h"

/**
 * @brief Provides database operations for product reviews.
 */
class ReviewRepository
{
public:
    /**
     * @brief Adds a review for a product.
     *
     * @param productId ID of the reviewed product.
     * @param userId ID of the user submitting the review.
     * @param rating Rating from 1 to 5.
     * @param comment Review comment.
     * @return true if the review is added successfully; otherwise false.
     */
    bool addReview(
        int productId,
        int userId,
        int rating,
        const std::string& comment
    );

    /**
     * @brief Checks whether a user has completed an order for a product.
     *
     * @param productId ID of the product.
     * @param userId ID of the user.
     * @return true if the user has a completed order containing the product.
     */
    bool hasCompletedOrder(
        int productId,
        int userId
    );

    /**
     * @brief Retrieves all reviews for a product.
     *
     * @param productId ID of the product.
     * @return A vector containing the product's reviews.
     */
    std::vector<Review> getReviewsByProduct(
        int productId
    );
};
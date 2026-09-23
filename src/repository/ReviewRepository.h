#pragma once

#include <vector>
#include <string>
#include "../model/Review.h"

class ReviewRepository
{
public:
    bool addReview(int productId,
                   int userId,
                   int rating,
                   const std::string& comment);

    bool hasCompletedOrder(int productId,
                           int userId);

    std::vector<Review> getReviewsByProduct(int productId);
};
#pragma once

#include <vector>
#include "../model/Review.h"

class ReviewRepository
{
public:
    bool addReview(int productId,
                   int userId,
                   int rating,
                   const std::string& comment);

    std::vector<Review> getReviewsByProduct(int productId);
};

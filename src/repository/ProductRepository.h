
#pragma once

#include <string>
#include <vector>

#include "../model/Product.h"

class ProductRepository
{
public:
    bool addProduct(
        const Product& product
    );

    std::vector<Product> getProducts();

    std::vector<Product> searchProducts(
        const std::string& keyword,
        const std::string& category
    );

    bool updateProduct(
        const Product& product,
        int sellerId
    );

    bool deleteProduct(
        int productId,
        int sellerId
    );
};

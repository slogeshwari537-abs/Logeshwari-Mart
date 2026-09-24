#pragma once

#include <string>
#include <vector>

#include "../model/Product.h"

/**
 * @brief Provides database operations for products.
 */
class ProductRepository
{
public:
    /**
     * @brief Adds a new product to the database.
     *
     * @param product Product details to insert.
     * @return true if the product is added successfully; otherwise false.
     */
    bool addProduct(
        const Product& product
    );

    /**
     * @brief Retrieves all products.
     *
     * @return A vector containing available products.
     */
    std::vector<Product> getProducts();

    /**
     * @brief Searches products using a keyword and category.
     *
     * @param keyword Search keyword.
     * @param category Product category filter.
     * @return Products matching the search criteria.
     */
    std::vector<Product> searchProducts(
        const std::string& keyword,
        const std::string& category
    );

    /**
     * @brief Updates an existing product owned by a seller.
     *
     * @param product Updated product details.
     * @param sellerId ID of the seller who owns the product.
     * @return true if the product is updated successfully; otherwise false.
     */
    bool updateProduct(
        const Product& product,
        int sellerId
    );

    /**
     * @brief Deletes a product owned by a seller.
     *
     * @param productId ID of the product to delete.
     * @param sellerId ID of the seller who owns the product.
     * @return true if the product is deleted successfully; otherwise false.
     */
    bool deleteProduct(
        int productId,
        int sellerId
    );
};
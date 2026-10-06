# Logeshwari Mart

Logeshwari Mart is a C++20-based e-commerce web application developed using Drogon and PostgreSQL.

## Features

- User registration and login
- Buyer, Seller and Admin roles
- Session-based authentication
- Product management
- Product image URL support
- Product search and filtering
- Shopping cart
- Mock payment checkout
- Buyer order history
- Seller incoming orders
- Admin dashboard
- Product reviews and ratings
- Google Gemini AI chatbot
- Chatbot rate limiting
- Chatbot response caching
- PostgreSQL database integration
- Docker deployment support

## Technologies

- C++20
- Drogon
- PostgreSQL
- Google Gemini API
- libsodium
- GoogleTest
- CMake
- vcpkg
- Docker

## Project Structure

```text
Logeshwari Mart/
├── db/
│   ├── migrations/
│   ├── 001_initial_schema.sql
│   ├── 002_add_product_image_url.sql
│   ├── schema.sql
│   └── seed.sql
├── frontend/
├── src/
│   ├── controller/
│   ├── dto/
│   ├── filter/
│   ├── model/
│   ├── repository/
│   ├── service/
│   └── util/
├── test/
├── uploads/
├── CMakeLists.txt
├── CONTRIBUTING.md
├── CHANGELOG.md
├── .clang-format
├── .dockerignore
├── Dockerfile
└── README.md
## API Endpoints

### Health
- GET /api/v1/health - Check application and database health

### Authentication
- POST /api/register - Register a Buyer or Seller
- POST /api/login - Login and create a session

### Products
- GET /api/products - Get all products
- GET /api/products/search - Search products by keyword
- POST /api/products - Create a product
- PUT /api/products/{id} - Update a product
- DELETE /api/products/{id} - Delete a product

### Cart
- GET /api/cart/{userId} - Get user's cart
- POST /api/cart - Add a product to cart
- PUT /api/cart/{userId}/{productId} - Update cart quantity
- DELETE /api/cart/{userId}/{productId} - Remove a product from cart
- DELETE /api/cart/clear/{userId} - Clear the cart

### Orders
- POST /api/checkout/{userId} - Checkout and create an order
- GET /api/orders/{userId} - Get buyer order history

### Reviews
- POST /api/reviews - Add a product review
- GET /api/reviews/{productId} - Get product reviews

### Chatbot
- POST /api/chat - Ask the AI chatbot

### Admin
- GET /api/admin/users - Get all users
- DELETE /api/admin/users/{userId} - Delete a user
- GET /api/admin/orders - Get all orders
- GET /api/admin/products - Get all products
- DELETE /api/admin/products/{productId} - Remove a product

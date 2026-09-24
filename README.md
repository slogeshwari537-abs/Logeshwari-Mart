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
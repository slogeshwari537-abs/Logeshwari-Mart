# Logeshwari Mart

Logeshwari Mart is a C++20-based e-commerce web application developed using Drogon and PostgreSQL.

## Features

- User registration and login
- Buyer, Seller and Admin roles
- Product management
- Product image URL support
- Product search and filtering
- Shopping cart
- Mock payment checkout
- Buyer order history
- Seller incoming orders
- Admin dashboard
- Product reviews and ratings
- AI chatbot
- Session-based authentication

## Technologies

- C++20
- Drogon
- PostgreSQL
- Google Gemini API
- libsodium
- GoogleTest
- CMake

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
│   ├── filter/
│   ├── repository/
│   └── service/
├── test/
├── uploads/
├── CMakeLists.txt
├── CONTRIBUTING.md
├── .clang-format
└── README.md
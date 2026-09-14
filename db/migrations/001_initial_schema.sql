-- LogeshwariMart
-- Migration 001: Initial Database Schema

CREATE TABLE IF NOT EXISTS users
(
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    role VARCHAR(20) NOT NULL
        CHECK (role IN ('BUYER', 'SELLER', 'ADMIN')),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS products
(
    id SERIAL PRIMARY KEY,
    seller_id INTEGER NOT NULL,
    name VARCHAR(200) NOT NULL,
    description TEXT,
    price_cents BIGINT NOT NULL,
    stock_qty INTEGER NOT NULL,
    category VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_products_seller
        FOREIGN KEY (seller_id)
        REFERENCES users(id)
);

CREATE INDEX IF NOT EXISTS idx_products_seller_id
ON products(seller_id);


CREATE TABLE IF NOT EXISTS orders
(
    id SERIAL PRIMARY KEY,
    buyer_id INTEGER NOT NULL,
    status VARCHAR(20) NOT NULL
        CHECK (
            status IN
            ('PENDING', 'CONFIRMED', 'SHIPPED',
             'DELIVERED', 'CANCELLED')
        ),
    total_amount_cents BIGINT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_orders_buyer
        FOREIGN KEY (buyer_id)
        REFERENCES users(id)
);

CREATE INDEX IF NOT EXISTS idx_orders_buyer_id
ON orders(buyer_id);


CREATE TABLE IF NOT EXISTS order_items
(
    id SERIAL PRIMARY KEY,
    order_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    unit_price_cents BIGINT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_order_items_order
        FOREIGN KEY (order_id)
        REFERENCES orders(id),

    CONSTRAINT fk_order_items_product
        FOREIGN KEY (product_id)
        REFERENCES products(id)
);

CREATE INDEX IF NOT EXISTS idx_order_items_order_id
ON order_items(order_id);

CREATE INDEX IF NOT EXISTS idx_order_items_product_id
ON order_items(product_id);


CREATE TABLE IF NOT EXISTS cart_items
(
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_cart_items_user
        FOREIGN KEY (user_id)
        REFERENCES users(id),

    CONSTRAINT fk_cart_items_product
        FOREIGN KEY (product_id)
        REFERENCES products(id),

    CONSTRAINT unique_cart_user_product
        UNIQUE(user_id, product_id)
);

CREATE INDEX IF NOT EXISTS idx_cart_items_user_id
ON cart_items(user_id);

CREATE INDEX IF NOT EXISTS idx_cart_items_product_id
ON cart_items(product_id);


CREATE TABLE IF NOT EXISTS reviews
(
    id SERIAL PRIMARY KEY,
    product_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    rating INTEGER NOT NULL
        CHECK (rating BETWEEN 1 AND 5),
    comment TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_reviews_product
        FOREIGN KEY (product_id)
        REFERENCES products(id),

    CONSTRAINT fk_reviews_user
        FOREIGN KEY (user_id)
        REFERENCES users(id)
);

CREATE INDEX IF NOT EXISTS idx_reviews_product_id
ON reviews(product_id);

CREATE INDEX IF NOT EXISTS idx_reviews_user_id
ON reviews(user_id);
-- LogeshwariMart
-- Migration 002: Add product image URL

ALTER TABLE products
ADD COLUMN IF NOT EXISTS image_url TEXT;
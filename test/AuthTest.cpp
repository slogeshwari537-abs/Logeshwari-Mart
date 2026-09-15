#include <gtest/gtest.h>

#include "../src/util/RoleUtil.h"

TEST(RoleTest, AdminRole)
{
    EXPECT_TRUE(isAdmin("ADMIN"));
    EXPECT_FALSE(isSeller("ADMIN"));
    EXPECT_FALSE(isBuyer("ADMIN"));
}

TEST(RoleTest, SellerRole)
{
    EXPECT_TRUE(isSeller("SELLER"));
    EXPECT_FALSE(isAdmin("SELLER"));
    EXPECT_FALSE(isBuyer("SELLER"));
}

TEST(RoleTest, BuyerRole)
{
    EXPECT_TRUE(isBuyer("BUYER"));
    EXPECT_FALSE(isAdmin("BUYER"));
    EXPECT_FALSE(isSeller("BUYER"));
}

TEST(RoleTest, InvalidRole)
{
    EXPECT_FALSE(isAdmin("INVALID"));
    EXPECT_FALSE(isSeller("INVALID"));
    EXPECT_FALSE(isBuyer("INVALID"));
}
#include <gtest/gtest.h>

#include "../src/util/RoleUtil.h"

TEST(RoleTest, AdminRole)
{
    EXPECT_TRUE(isAdmin("ADMIN"));
    EXPECT_FALSE(isAdmin("BUYER"));
    EXPECT_FALSE(isAdmin("SELLER"));
}

TEST(RoleTest, SellerRole)
{
    EXPECT_TRUE(isSeller("SELLER"));
    EXPECT_FALSE(isSeller("ADMIN"));
    EXPECT_FALSE(isSeller("BUYER"));
}

TEST(RoleTest, BuyerRole)
{
    EXPECT_TRUE(isBuyer("BUYER"));
    EXPECT_FALSE(isBuyer("ADMIN"));
    EXPECT_FALSE(isBuyer("SELLER"));
}
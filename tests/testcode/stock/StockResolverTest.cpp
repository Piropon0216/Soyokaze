// StockResolverTest.cpp
#include <gtest/gtest.h>
// StockResolverTest.cpp
#include <gtest/gtest.h>
#include "commands/stock/StockResolver.h"

TEST(StockResolverTest, ResolveKnownJapaneseName) {
    auto res = StockResolver::Resolve("トヨタ");
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), "7203");
}

TEST(StockResolverTest, ResolveUnknownName) {
    auto res = StockResolver::Resolve("UnknownCompanyXYZ");
    EXPECT_FALSE(res.has_value());
}

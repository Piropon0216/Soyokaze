// SymbolUrlBuilderTest.cpp
#include <gtest/gtest.h>
#include "commands/stock/SymbolUrlBuilder.h"

TEST(SymbolUrlBuilderTest, BuildUrlJP) {
    // Yahoo Japan format: https://stocks.finance.yahoo.co.jp/stocks/detail/?code=<code>
    auto url = SymbolUrlBuilder::BuildJP("7203");
    EXPECT_NE(url.find("https://stocks.finance.yahoo.co.jp/stocks/detail/?code=7203"), std::string::npos);
}

TEST(SymbolUrlBuilderTest, BuildUrlUS) {
    // Yahoo US format: https://finance.yahoo.com/quote/<symbol>
    auto url = SymbolUrlBuilder::BuildUS("MSFT");
    EXPECT_NE(url.find("https://finance.yahoo.com/quote/MSFT"), std::string::npos);
}

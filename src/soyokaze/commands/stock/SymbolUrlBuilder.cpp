// SymbolUrlBuilder.cpp
#include "commands/stock/SymbolUrlBuilder.h"

std::string SymbolUrlBuilder::BuildJP(const std::string &code) {
    return "https://stocks.finance.yahoo.co.jp/stocks/detail/?code=" + code;
}

std::string SymbolUrlBuilder::BuildUS(const std::string &symbol) {
    return "https://finance.yahoo.com/quote/" + symbol;
}

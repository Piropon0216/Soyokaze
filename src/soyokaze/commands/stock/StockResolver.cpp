// StockResolver.cpp
#include "commands/stock/StockResolver.h"
#include <unordered_map>

std::optional<std::string> StockResolver::Resolve(const std::string &name) {
    static const std::unordered_map<std::string, std::string> map = {
        {"トヨタ", "7203"},
        {"トヨタ自動車", "7203"},
        {"Toyota", "7203"},
        {"ソニー", "6758"},
        {"Sony", "6758"},
        {"Microsoft", "MSFT"},
        {"マイクロソフト", "MSFT"}
    };

    auto it = map.find(name);
    if (it != map.end()) return it->second;
    return std::nullopt;
}

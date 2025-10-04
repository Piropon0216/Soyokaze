// StockResolver.h
#pragma once
#include <string>
#include <optional>

class StockResolver {
public:
    // Resolve company name (Japanese or English) to security code (as string)
    // Returns std::nullopt when unknown
    static std::optional<std::string> Resolve(const std::string &name);
};

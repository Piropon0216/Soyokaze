// SymbolUrlBuilder.h
#pragma once
#include <string>

class SymbolUrlBuilder {
public:
    static std::string BuildJP(const std::string &code);
    static std::string BuildUS(const std::string &symbol);
};

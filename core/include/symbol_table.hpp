#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct Symbol {
    std::string name;
    std::string type;
    int firstOccurrenceOrder;
};

class SymbolTable {
public:
    bool insert(const std::string& name, const std::string& type = "numeric");
    const std::vector<Symbol>& getSymbols() const;

private:
    std::unordered_map<std::string, Symbol> table;
    std::vector<Symbol> symbolOrder;
};
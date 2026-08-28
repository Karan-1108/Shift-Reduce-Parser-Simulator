#include "symbol_table.hpp"

bool SymbolTable::insert(const std::string& name, const std::string& type) {
    if (table.find(name) != table.end()) return false;
    Symbol sym{name, type, static_cast<int>(symbolOrder.size() + 1)};
    table[name] = sym;
    symbolOrder.push_back(sym);
    return true;
}

const std::vector<Symbol>& SymbolTable::getSymbols() const {
    return symbolOrder;
}
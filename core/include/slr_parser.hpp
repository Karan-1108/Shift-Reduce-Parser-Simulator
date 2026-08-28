#pragma once
#include "lexer.hpp"
#include "symbol_table.hpp"
#include "tac_generator.hpp"
#include <vector>
#include <string>

struct ParseStepTrace {
    int step;
    std::string stackState;
    std::string inputBuffer;
    std::string action;
};

class SLRParser {
public:
    SLRParser();
    bool parse(const std::vector<Token>& tokens);
    const std::vector<ParseStepTrace>& getTrace() const { return traceLog; }
    const SymbolTable& getSymbolTable() const { return symbolTable; }
    const TACGenerator& getTAC() const { return tacGen; }

private:
    SymbolTable symbolTable;
    TACGenerator tacGen;
    std::vector<ParseStepTrace> traceLog;
    
    struct StackNode {
        int state;
        std::string symbol;
        std::string place;
    };
};
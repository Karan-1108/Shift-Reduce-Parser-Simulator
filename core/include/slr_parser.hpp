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
    
    std::vector<Token> tokStream;
    size_t index = 0;
    std::vector<std::string> traceStack;

    bool parseE(std::string& place);
    bool parseT(std::string& place);
    bool parseF(std::string& place);
    bool parseU(std::string& place);
    bool parseP(std::string& place);
    bool consume(TokenType type, const char* action, std::string* place = nullptr);
    void reduce(const std::string& rule, const std::string& place);
    void addTrace(const std::string& action);
};
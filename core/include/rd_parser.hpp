#pragma once
#include "lexer.hpp"

struct ComparisonMetrics {
    double executionTimeMs;
    size_t peakStackDepth;
    bool success;
};

class RecursiveDescentParser {
public:
    ComparisonMetrics parse(const std::vector<Token>& tokens);

private:
    std::vector<Token> tokStream;
    size_t index = 0;
    size_t currentDepth = 0;
    size_t maxDepth = 0;

    void trackDepthEnter() { currentDepth++; if (currentDepth > maxDepth) maxDepth = currentDepth; }
    void trackDepthLeave() { currentDepth--; }

    bool parseE();
    bool parseT();
    bool parseF();
    bool parseU();
    bool parseP();
};
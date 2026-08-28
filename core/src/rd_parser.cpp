#include "rd_parser.hpp"
#include <chrono>

ComparisonMetrics RecursiveDescentParser::parse(const std::vector<Token>& tokens) {
    tokStream = tokens;
    index = 0;
    currentDepth = 0;
    maxDepth = 0;

    auto start = std::chrono::high_resolution_clock::now();
    bool res = parseE() && (tokStream[index].type == TokenType::END_OF_FILE);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
    return {elapsed, maxDepth, res};
}

bool RecursiveDescentParser::parseE() {
    trackDepthEnter();
    bool ok = parseT() && parseEPrime();
    trackDepthLeave();
    return ok;
}

bool RecursiveDescentParser::parseEPrime() {
    trackDepthEnter();
    if (tokStream[index].type == TokenType::PLUS) {
        index++;
        bool ok = parseT() && parseEPrime();
        trackDepthLeave();
        return ok;
    }
    trackDepthLeave();
    return true;
}

bool RecursiveDescentParser::parseT() {
    trackDepthEnter();
    bool ok = parseF() && parseTPrime();
    trackDepthLeave();
    return ok;
}

bool RecursiveDescentParser::parseTPrime() {
    trackDepthEnter();
    if (tokStream[index].type == TokenType::STAR) {
        index++;
        bool ok = parseF() && parseTPrime();
        trackDepthLeave();
        return ok;
    }
    trackDepthLeave();
    return true;
}

bool RecursiveDescentParser::parseF() {
    trackDepthEnter();
    if (tokStream[index].type == TokenType::ID) {
        index++;
        trackDepthLeave();
        return true;
    } else if (tokStream[index].type == TokenType::LPAREN) {
        index++;
        if (parseE()) {
            if (tokStream[index].type == TokenType::RPAREN) {
                index++;
                trackDepthLeave();
                return true;
            }
        }
    }
    trackDepthLeave();
    return false;
}
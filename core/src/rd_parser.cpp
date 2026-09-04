#include "rd_parser.hpp"
#include <chrono>

ComparisonMetrics RecursiveDescentParser::parse(const std::vector<Token>& tokens) {
    tokStream = tokens;
    index = 0;
    currentDepth = 0;
    maxDepth = 0;

    auto start = std::chrono::high_resolution_clock::now();
    bool res = parseE() && index < tokStream.size() && tokStream[index].type == TokenType::END_OF_FILE;
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
    return {elapsed, maxDepth, res};
}

bool RecursiveDescentParser::parseE() {
    trackDepthEnter();
    bool ok = parseT();
    while (ok && index < tokStream.size() && (tokStream[index].type == TokenType::PLUS || tokStream[index].type == TokenType::MINUS)) {
        index++;
        ok = parseT();
    }
    trackDepthLeave();
    return ok;
}

bool RecursiveDescentParser::parseT() {
    trackDepthEnter();
    bool ok = parseF();
    while (ok && index < tokStream.size() && (tokStream[index].type == TokenType::STAR || tokStream[index].type == TokenType::SLASH)) {
        index++;
        ok = parseF();
    }
    trackDepthLeave();
    return ok;
}

bool RecursiveDescentParser::parseF() {
    trackDepthEnter();
    bool ok = parseU();
    while (ok && index < tokStream.size() && tokStream[index].type == TokenType::CARET) {
        index++;
        ok = parseU();
    }
    trackDepthLeave();
    return ok;
}

bool RecursiveDescentParser::parseU() {
    trackDepthEnter();
    bool ok;
    if (index < tokStream.size() && tokStream[index].type == TokenType::MINUS) {
        index++;
        ok = parseU();
    } else {
        ok = parseP();
    }
    trackDepthLeave();
    return ok;
}

bool RecursiveDescentParser::parseP() {
    trackDepthEnter();
    if (index >= tokStream.size()) {
        trackDepthLeave();
        return false;
    }
    if (tokStream[index].type == TokenType::ID || tokStream[index].type == TokenType::NUM) {
        index++;
        trackDepthLeave();
        return true;
    }
    if (tokStream[index].type == TokenType::LPAREN) {
        index++;
        bool ok = parseE();
        if (ok && index < tokStream.size() && tokStream[index].type == TokenType::RPAREN) {
            index++;
            trackDepthLeave();
            return true;
        }
    }
    trackDepthLeave();
    return false;
}

#include "slr_parser.hpp"

SLRParser::SLRParser() {}

void SLRParser::addTrace(const std::string& action) {
    std::string stackState = "0";
    for (const auto& symbol : traceStack) stackState += " " + symbol;
    std::string buffer;
    for (size_t i = index; i < tokStream.size(); ++i) buffer += tokStream[i].lexeme + " ";
    traceLog.push_back({static_cast<int>(traceLog.size() + 1), stackState, buffer, action});
}

bool SLRParser::consume(TokenType type, const char* action, std::string* place) {
    if (index >= tokStream.size() || tokStream[index].type != type) return false;
    const Token token = tokStream[index++];
    if (place) *place = token.lexeme;
    if (type == TokenType::ID) symbolTable.insert(token.lexeme);
    traceStack.push_back(token.lexeme);
    addTrace(action);
    return true;
}

void SLRParser::reduce(const std::string& rule, const std::string& place) {
    if (!traceStack.empty()) traceStack.pop_back();
    traceStack.push_back(place);
    addTrace("Reduce " + rule);
}

bool SLRParser::parse(const std::vector<Token>& tokens) {
    tokStream = tokens;
    index = 0;
    traceStack.clear();
    traceLog.clear();

    std::string place;
    const bool success = parseE(place)
        && index < tokStream.size()
        && tokStream[index].type == TokenType::END_OF_FILE;

    addTrace(success ? "Accept" : "Syntax Error");
    return success;
}

bool SLRParser::parseE(std::string& place) {
    if (!parseT(place)) return false;
    while (index < tokStream.size() && (tokStream[index].type == TokenType::PLUS || tokStream[index].type == TokenType::MINUS)) {
        const std::string op = tokStream[index].lexeme;
        consume(tokStream[index].type, op == "+" ? "Shift +" : "Shift -");
        std::string rhs;
        if (!parseT(rhs)) return false;
        const std::string lhs = place;
        place = tacGen.createTemp();
        tacGen.emit(place, lhs, op, rhs);
        reduce(op == "+" ? "E -> E + T" : "E -> E - T", place);
    }
    reduce("E -> T", place);
    return true;
}

bool SLRParser::parseT(std::string& place) {
    if (!parseF(place)) return false;
    while (index < tokStream.size() && (tokStream[index].type == TokenType::STAR || tokStream[index].type == TokenType::SLASH)) {
        const std::string op = tokStream[index].lexeme;
        consume(tokStream[index].type, op == "*" ? "Shift *" : "Shift /");
        std::string rhs;
        if (!parseF(rhs)) return false;
        const std::string lhs = place;
        place = tacGen.createTemp();
        tacGen.emit(place, lhs, op, rhs);
        reduce(op == "*" ? "T -> T * F" : "T -> T / F", place);
    }
    reduce("T -> F", place);
    return true;
}

bool SLRParser::parseF(std::string& place) {
    if (!parseU(place)) return false;
    while (index < tokStream.size() && tokStream[index].type == TokenType::CARET) {
        consume(TokenType::CARET, "Shift ^");
        std::string rhs;
        if (!parseU(rhs)) return false;
        const std::string lhs = place;
        place = tacGen.createTemp();
        tacGen.emit(place, lhs, "^", rhs);
        reduce("F -> F ^ U", place);
    }
    return true;
}

bool SLRParser::parseU(std::string& place) {
    if (index < tokStream.size() && tokStream[index].type == TokenType::MINUS) {
        consume(TokenType::MINUS, "Shift -");
        std::string operand;
        if (!parseU(operand)) return false;
        place = tacGen.createTemp();
        tacGen.emit(place, "0", "-", operand);
        reduce("U -> - U", place);
        return true;
    }
    if (!parseP(place)) return false;
    reduce("U -> P", place);
    return true;
}

bool SLRParser::parseP(std::string& place) {
    if (index < tokStream.size() && tokStream[index].type == TokenType::ID) {
        if (!consume(TokenType::ID, "Shift id", &place)) return false;
        reduce("P -> id", place);
        return true;
    }
    if (index < tokStream.size() && tokStream[index].type == TokenType::NUM) {
        if (!consume(TokenType::NUM, "Shift num", &place)) return false;
        reduce("P -> num", place);
        return true;
    }
    if (!consume(TokenType::LPAREN, "Shift (")) return false;
    if (!parseE(place)) return false;
    if (!consume(TokenType::RPAREN, "Shift )")) return false;
    reduce("P -> ( E )", place);
    return true;
}

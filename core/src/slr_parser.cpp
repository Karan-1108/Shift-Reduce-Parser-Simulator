#include "slr_parser.hpp"

SLRParser::SLRParser() {}

bool SLRParser::parse(const std::vector<Token>& tokens) {
    std::vector<StackNode> stack;
    stack.push_back({0, "$", ""});
    size_t tokenIdx = 0;
    int stepCounter = 1;

    auto formatStack = [](const std::vector<StackNode>& st) {
        std::string s;
        for (const auto& node : st) s += std::to_string(node.state) + " ";
        return s;
    };

    auto formatBuffer = [](const std::vector<Token>& tkns, size_t idx) {
        std::string s;
        for (size_t i = idx; i < tkns.size(); ++i) s += tkns[i].lexeme + " ";
        return s;
    };

    while (true) {
        int currentState = stack.back().state;
        Token currentToken = tokens[tokenIdx];
        std::string termStr;
        switch(currentToken.type) {
            case TokenType::ID: termStr = "id"; break;
            case TokenType::PLUS: termStr = "+"; break;
            case TokenType::STAR: termStr = "*"; break;
            case TokenType::LPAREN: termStr = "("; break;
            case TokenType::RPAREN: termStr = ")"; break;
            case TokenType::END_OF_FILE: termStr = "$"; break;
            default: termStr = "ERR";
        }

        std::string actDesc = "";
        
        if (currentState == 0 && termStr == "id") {
            symbolTable.insert(currentToken.lexeme);
            stack.push_back({5, "id", currentToken.lexeme});
            tokenIdx++; actDesc = "Shift 5";
        } else if (currentState == 0 && termStr == "(") {
            stack.push_back({4, "(", ""}); tokenIdx++; actDesc = "Shift 4";
        } else if (currentState == 1 && termStr == "+") {
            stack.push_back({6, "+", ""}); tokenIdx++; actDesc = "Shift 6";
        } else if (currentState == 1 && termStr == "$") {
            traceLog.push_back({stepCounter++, formatStack(stack), formatBuffer(tokens, tokenIdx), "Accept"});
            return true;
        } else if (currentState == 2 && termStr == "*") {
            stack.push_back({7, "*", ""}); tokenIdx++; actDesc = "Shift 7";
        } else if (currentState == 2 && (termStr == "+" || termStr == ")" || termStr == "$")) {
            auto top = stack.back(); stack.pop_back();
            int topState = stack.back().state;
            int gotoState = (topState == 0) ? 1 : (topState == 4 ? 8 : -1);
            stack.push_back({gotoState, "E", top.place});
            actDesc = "Reduce E -> T";
        } else if (currentState == 3 && (termStr == "+" || termStr == "*" || termStr == ")" || termStr == "$")) {
            auto top = stack.back(); stack.pop_back();
            int topState = stack.back().state;
            int gotoState = (topState == 0 || topState == 4) ? 2 : (topState == 6 ? 9 : -1);
            stack.push_back({gotoState, "T", top.place});
            actDesc = "Reduce T -> F";
        } else if (currentState == 5 && (termStr == "+" || termStr == "*" || termStr == ")" || termStr == "$")) {
            auto top = stack.back(); stack.pop_back();
            int topState = stack.back().state;
            int gotoState = (topState == 0 || topState == 4) ? 3 : (topState == 6 ? 3 : (topState == 7 ? 10 : -1));
            stack.push_back({gotoState, "F", top.place});
            actDesc = "Reduce F -> id";
        } else if (currentState == 6 && termStr == "id") {
            symbolTable.insert(currentToken.lexeme);
            stack.push_back({5, "id", currentToken.lexeme}); tokenIdx++; actDesc = "Shift 5";
        } else if (currentState == 6 && termStr == "(") {
            stack.push_back({4, "(", ""}); tokenIdx++; actDesc = "Shift 4";
        } else if (currentState == 7 && termStr == "id") {
            symbolTable.insert(currentToken.lexeme);
            stack.push_back({5, "id", currentToken.lexeme}); tokenIdx++; actDesc = "Shift 5";
        } else if (currentState == 7 && termStr == "(") {
            stack.push_back({4, "(", ""}); tokenIdx++; actDesc = "Shift 4";
        } else if (currentState == 8 && termStr == "+") {
            stack.push_back({6, "+", ""}); tokenIdx++; actDesc = "Shift 6";
        } else if (currentState == 8 && termStr == ")") {
            stack.push_back({11, ")", ""}); tokenIdx++; actDesc = "Shift 11";
        } else if (currentState == 9 && termStr == "*") {
            stack.push_back({7, "*", ""}); tokenIdx++; actDesc = "Shift 7";
        } else if (currentState == 9 && (termStr == "+" || termStr == ")" || termStr == "$")) {
            auto tNode = stack.back(); stack.pop_back();
            stack.pop_back();
            auto eNode = stack.back(); stack.pop_back();
            std::string temp = tacGen.createTemp();
            tacGen.emit(temp, eNode.place, "+", tNode.place);
            int topState = stack.back().state;
            int gotoState = (topState == 0) ? 1 : (topState == 4 ? 8 : -1);
            stack.push_back({gotoState, "E", temp});
            actDesc = "Reduce E -> E + T";
        } else if (currentState == 10 && (termStr == "+" || termStr == "*" || termStr == ")" || termStr == "$")) {
            auto fNode = stack.back(); stack.pop_back();
            stack.pop_back();
            auto tNode = stack.back(); stack.pop_back();
            std::string temp = tacGen.createTemp();
            tacGen.emit(temp, tNode.place, "*", fNode.place);
            int topState = stack.back().state;
            int gotoState = (topState == 0 || topState == 4) ? 2 : (topState == 6 ? 9 : -1);
            stack.push_back({gotoState, "T", temp});
            actDesc = "Reduce T -> T * F";
        } else if (currentState == 11 && (termStr == "+" || termStr == "*" || termStr == ")" || termStr == "$")) {
            stack.pop_back();
            auto eNode = stack.back(); stack.pop_back();
            stack.pop_back();
            int topState = stack.back().state;
            int gotoState = (topState == 0 || topState == 4) ? 3 : (topState == 6 ? 3 : (topState == 7 ? 10 : -1));
            stack.push_back({gotoState, "F", eNode.place});
            actDesc = "Reduce F -> ( E )";
        } else if (currentState == 4 && termStr == "id") {
            symbolTable.insert(currentToken.lexeme);
            stack.push_back({5, "id", currentToken.lexeme}); tokenIdx++; actDesc = "Shift 5";
        } else if (currentState == 4 && termStr == "(") {
            stack.push_back({4, "(", ""}); tokenIdx++; actDesc = "Shift 4";
        } else {
            traceLog.push_back({stepCounter, formatStack(stack), formatBuffer(tokens, tokenIdx), "Syntax Error"});
            return false;
        }

        traceLog.push_back({stepCounter++, formatStack(stack), formatBuffer(tokens, tokenIdx), actDesc});
    }
}
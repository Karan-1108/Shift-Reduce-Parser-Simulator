#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(std::string input) : src(std::move(input)) {}

void Lexer::skipWhitespace() {
    while (cursor < src.length() && std::isspace(src[cursor])) cursor++;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (cursor < src.length()) {
        skipWhitespace();
        if (cursor >= src.length()) break;

        char current = src[cursor];
        int pos = static_cast<int>(cursor);

        if (std::isalpha(static_cast<unsigned char>(current)) || current == '_') {
            std::string idStr;
            while (cursor < src.length() && (std::isalnum(static_cast<unsigned char>(src[cursor])) || src[cursor] == '_')) {
                idStr += src[cursor++];
            }
            tokens.push_back({TokenType::ID, idStr, pos});
        } else if (std::isdigit(static_cast<unsigned char>(current))) {
            std::string number;
            while (cursor < src.length() && std::isdigit(static_cast<unsigned char>(src[cursor]))) {
                number += src[cursor++];
            }
            tokens.push_back({TokenType::NUM, number, pos});
        } else if (current == '+') {
            tokens.push_back({TokenType::PLUS, "+", pos}); cursor++;
        } else if (current == '-') {
            tokens.push_back({TokenType::MINUS, "-", pos}); cursor++;
        } else if (current == '*') {
            tokens.push_back({TokenType::STAR, "*", pos}); cursor++;
        } else if (current == '/') {
            tokens.push_back({TokenType::SLASH, "/", pos}); cursor++;
        } else if (current == '^') {
            tokens.push_back({TokenType::CARET, "^", pos}); cursor++;
        } else if (current == '(') {
            tokens.push_back({TokenType::LPAREN, "(", pos}); cursor++;
        } else if (current == ')') {
            tokens.push_back({TokenType::RPAREN, ")", pos}); cursor++;
        } else {
            tokens.push_back({TokenType::INVALID, std::string(1, current), pos});
            cursor++;
        }
    }
    tokens.push_back({TokenType::END_OF_FILE, "$", static_cast<int>(src.length())});
    return tokens;
}
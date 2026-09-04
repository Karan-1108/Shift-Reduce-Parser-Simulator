#pragma once
#include <string>
#include <vector>

enum class TokenType {
    ID,
    NUM,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    CARET,
    LPAREN,
    RPAREN,
    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;
    int position;
};

class Lexer {
public:
    explicit Lexer(std::string input);
    std::vector<Token> tokenize();

private:
    std::string src;
    size_t cursor = 0;
    void skipWhitespace();
};
#pragma once
#include "token.h"
#include <string>
#include <vector>

class Lexer {
public:
    // take source code as string
    explicit Lexer(const std::string& source);

    // main interface
    Token next();       // consume and return next token
    Token peek();       // look at next token without consuming
    bool at_eof() const;

private:
    std::string source_;
    std::size_t pos_ = 0;
    int line_ = 1;
    int col_ = 1;
    Token peeked_;
    bool has_peeked_ = false;

    // helpers
    char current() const;   // return character at pos_ without advancing
    char advance();         // return character at pos_ and increment pos_
    char peek_char() const;
    void skip_whitespace_and_comments();

    // tokenization logic
    Token next_token();
    Token lex_identifier_or_keyword();
    Token lex_number();
    Token lex_symbol();

    Token make_token(TokenKind kind, const std::string& text = "");
    Token make_int_token(int64_t val, const std::string& text);
    Token make_float_token(double val, const std::string& text);
};
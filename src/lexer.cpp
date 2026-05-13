#include "lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& source)
    : source_(source) {}

Token Lexer::next() {
    if (has_peeked_) {
        has_peeked_ = false;
        return peeked_;
    }
    return next_token();
}

Token Lexer::peek() {
    if (!has_peeked_) {
        peeked_ = next_token();
        has_peeked_ = true;
    }
    return peeked_;
}

// check EOF comparing token position and source length
bool Lexer::at_eof() const {
    return pos_ >= source_.size();
}

// check current char using position
char Lexer::current() const {
    if (at_eof()) {
        return '\0';
    }
    return source_[pos_];
}

// move to next char, reset column to 1 if newline found
char Lexer::advance() {
    char c = source_[pos_++];
    if (c == '\n') {
        ++line_;
        col_ = 1;
    }
    else {
        ++col_;
    }
    return c;
}

// check next char without incrementing
char Lexer::peek_char() const {
    if (pos_ + 1 >= source_.size()) {
        return '\0';
    }
    return source_[pos_ + 1];
}

void Lexer::skip_whitespace_and_comments() {
    while (!at_eof()) {
        char c = current();

        // if whitespace
        if (std::isspace(c)) {
            advance();
            continue;
        }
        
        // if single line comment denoted by '//'
        if (c == '/' && peek_char() == '/') {
            while (!at_eof() && current() != '\n') {
                advance();
            }
            continue;
        }
        break;
    }
}


Token Lexer::next_token() {
    skip_whitespace_and_comments();

    if (at_eof())
        return make_token(TokenKind::EOF_TOKEN, "");

    char c = current();

    if (std::isalpha(c) || c == '_')
        return lex_identifier_or_keyword();

    if (std::isdigit(c))
        return lex_number();

    return lex_symbol();
}

Token Lexer::lex_identifier_or_keyword() {
    std::string text;
    while (!at_eof() && (std::isalnum(current()) || current() == '_'))
        text += advance();

    // keyword matching
    if (text == "kernel") return make_token(TokenKind::KERNEL, text);
    if (text == "if")     return make_token(TokenKind::IF, text);
    if (text == "else")   return make_token(TokenKind::ELSE, text);
    if (text == "for")    return make_token(TokenKind::FOR, text);
    if (text == "return") return make_token(TokenKind::RETURN, text);
    if (text == "i32")    return make_token(TokenKind::I32, text);
    if (text == "i64")    return make_token(TokenKind::I64, text);
    if (text == "f32")    return make_token(TokenKind::F32, text);
    if (text == "f64")    return make_token(TokenKind::F64, text);
    if (text == "ptr")    return make_token(TokenKind::PTR, text);

    return make_token(TokenKind::IDENTIFIER, text);
}

Token Lexer::lex_number() {
    std::string text;
    bool is_float = false;

    while (!at_eof() && std::isdigit(current()))
        text += advance();

    // check for decimal point
    if (!at_eof() && current() == '.' && std::isdigit(peek_char())) {
        is_float = true;
        text += advance(); // consume '.'
        while (!at_eof() && std::isdigit(current()))
            text += advance();
    }

    if (is_float)
        return make_float_token(std::stod(text), text);
    return make_int_token(std::stoll(text), text);
}

Token Lexer::lex_symbol() {
    char c = advance();

    switch (c) {
        case '(': return make_token(TokenKind::LPAREN,    "(");
        case ')': return make_token(TokenKind::RPAREN,    ")");
        case '{': return make_token(TokenKind::LBRACE,    "{");
        case '}': return make_token(TokenKind::RBRACE,    "}");
        case '[': return make_token(TokenKind::LBRACKET,  "[");
        case ']': return make_token(TokenKind::RBRACKET,  "]");
        case ',': return make_token(TokenKind::COMMA,     ",");
        case ':': return make_token(TokenKind::COLON,     ":");
        case ';': return make_token(TokenKind::SEMICOLON, ";");
        case '+': return make_token(TokenKind::PLUS,      "+");
        case '-': return make_token(TokenKind::MINUS,     "-");
        case '*': return make_token(TokenKind::STAR,      "*");
        case '/': return make_token(TokenKind::SLASH,     "/");
        case '&': return make_token(TokenKind::AMP,       "&");
        case '|': return make_token(TokenKind::PIPE,      "|");
        case '^': return make_token(TokenKind::CARET,     "^");

        // two character operators
        case '=':
            if (!at_eof() && current() == '=') {
                advance();
                return make_token(TokenKind::EQ, "==");
            }
            return make_token(TokenKind::ASSIGN, "=");

        case '!':
            if (!at_eof() && current() == '=') {
                advance();
                return make_token(TokenKind::NEQ, "!=");
            }
            throw std::runtime_error("unexpected character '!'");

        case '<':
            if (!at_eof() && current() == '=') {
                advance();
                return make_token(TokenKind::LEQ, "<=");
            }
            if (!at_eof() && current() == '<') {
                advance();
                return make_token(TokenKind::LSHIFT, "<<");
            }
            return make_token(TokenKind::LT, "<");

        case '>':
            if (!at_eof() && current() == '=') {
                advance();
                return make_token(TokenKind::GEQ, ">=");
            }
            if (!at_eof() && current() == '>') {
                advance();
                return make_token(TokenKind::RSHIFT, ">>");
            }
            return make_token(TokenKind::GT, ">");

        default: {
            std::string msg = "krnlcc: error at line " + std::to_string(line_) +
                              ", col " + std::to_string(col_) +
                              ": unexpected character '" + c + "'";
            throw std::runtime_error(msg);
}
    }
}

Token Lexer::make_token(TokenKind kind, const std::string& text) {
    Token t;
    t.kind = kind;
    t.text = text;
    t.line = line_;
    t.col = col_;
    t.int_val = 0;
    t.float_val = 0.0;
    return t;
}

Token Lexer::make_int_token(int64_t val, const std::string& text) {
    Token t = make_token(TokenKind::INT_LIT, text);
    t.int_val = val;
    return t;
}

Token Lexer::make_float_token(double val, const std::string& text) {
    Token t = make_token(TokenKind::FLOAT_LIT, text);
    t.float_val = val;
    return t;
}

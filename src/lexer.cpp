#include "lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& source)
    : source_(source) {}

// parser calls peek() - tokenizes "kernel", caches it, returns "kernel"
// parser calls peek() - has_peeked_ true, returns cached "kernel" again
// parser calls next() - has_peeked_ true, clears cache, returns "kernel"
// parser calls next() - has_peeked_ false, tokenizes fresh, returns "vector_add"

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
bool Lexer::at_end() const {
    return pos_ >= source_.size();
}

// check current char using position
char Lexer::current() const {
    if (at_end()) {
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
    
}

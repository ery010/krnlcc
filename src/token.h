#pragma once
#include <string>

enum class TokenKind {
    EOF_TOKEN, // end of file

    // keywords
    KERNEL,     // 'kernel definition keyword'
    IF,
    ELSE,
    FOR,
    RETURN,

    // types - int-32, int-64, float-32, float-64
    I32,
    I64,
    F32,
    F64,
    PTR,        // pointer type for GPU memory

    // literals
    INT_LIT,
    FLOAT_LIT,

    // identifier
    IDENTIFIER,

    // symbols
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE,     // }
    LBRACKET,   // [
    RBRACKET,   // ]
    COMMA,      // ,
    COLON,      // :
    SEMICOLON,  // ;
    ASSIGN,     // =
    PLUS,      // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    LT,         // <
    GT,         // >
    EQ,         // ==
    NEQ,        // !=
    LEQ,        // <=
    GEQ,        // >=
    AMP,        // &
    PIPE,       // |
    CARET,      // ^ 
    RSHIFT,     // >>
    LSHIFT,     // <<
};

struct Token {
    TokenKind kind;
    std::string text;       // text from source
    int line;               // line and col for error messages
    int col;

    // literal values
    int64_t int_val;
    double float_val;
};

// helper function to convert token kind to string for error messages
inline std::string token_kind_str(TokenKind kind) {
    switch (kind) {
        case TokenKind::EOF_TOKEN:  return "EOF";
        case TokenKind::KERNEL:     return "kernel";
        case TokenKind::IF:         return "if";
        case TokenKind::ELSE:       return "else";
        case TokenKind::FOR:        return "for";
        case TokenKind::RETURN:     return "return";
        case TokenKind::I32:        return "i32";
        case TokenKind::I64:        return "i64";
        case TokenKind::F32:        return "f32";
        case TokenKind::F64:        return "f64";
        case TokenKind::PTR:        return "ptr";
        case TokenKind::INT_LIT:    return "int literal";
        case TokenKind::FLOAT_LIT:  return "float literal";
        case TokenKind::IDENTIFIER: return "identifier";
        case TokenKind::LPAREN:     return "(";
        case TokenKind::RPAREN:     return ")";
        case TokenKind::LBRACE:     return "{";
        case TokenKind::RBRACE:     return "}";
        case TokenKind::LBRACKET:   return "[";
        case TokenKind::RBRACKET:   return "]";
        case TokenKind::COMMA:      return ",";
        case TokenKind::COLON:      return ":";
        case TokenKind::SEMICOLON:  return ";";
        case TokenKind::ASSIGN:     return "=";
        case TokenKind::PLUS:       return "+";
        case TokenKind::MINUS:      return "-";
        case TokenKind::STAR:       return "*";
        case TokenKind::SLASH:      return "/";
        case TokenKind::LT:         return "<";
        case TokenKind::GT:         return ">";
        case TokenKind::EQ:         return "==";
        case TokenKind::NEQ:        return "!=";
        case TokenKind::LEQ:        return "<=";
        case TokenKind::GEQ:        return ">=";
        case TokenKind::AMP:        return "&";
        case TokenKind::PIPE:       return "|";
        case TokenKind::CARET:      return "^";
        case TokenKind::RSHIFT:     return ">>";
        case TokenKind::LSHIFT:     return "<<";
        default:                    return "unknown";
    }
}
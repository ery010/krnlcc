#pragma once
#include <string>

enum class TokenKind {
    EOF_TOKEN = -1, // end of file

    // keywords
    KERNEL      = -2,   // 'kernel definition keyword'
    IF          = -3,
    ELSE        = -4,
    FOR         = -5,
    RETURN      = -6,

    // types - int-32, int-64, float-32, float-64
    I32         = -7,
    I64         = -8,
    F32         = -9,
    F64         = -10,
    PTR         = -11,   // pointer type for GPU memory

    // literals
    INT_LIT     = -12,
    FLOAT_LIT   = -13,

    // identifier
    IDENTIFIER  = -14,

    // symbols
    LPAREN      = -15,   // (
    RPAREN      = -16,   // )
    LBRACE      = -17,   // {
    RBRACE      = -18,   // }
    LBRACKET    = -19,   // [
    RBRACKET    = -20,   // ]
    COMMA       = -21,   // ,
    COLON       = -22,   // :
    SEMICOLON   = -23,  // ;
    ASSIGN      = -24,  // =
    PLUS        = -25,  // +
    MINUS       = -26,  // -
    STAR        = -27,  // *
    SLASH       = -28,  // /
    LT          = -29,  // <
    GT          = -30,  // >
    EQ          = -31,  // ==
    NEQ         = -32,  // !=
    LEQ         = -33,  // <=
    GEQ         = -34,  // >=
    AMP         = -35,  // &
    PIPE        = -36,  // |
    CARET       = -37,  // ^ 
    RSHIFT      = -38,  // >>
    LSHIFT      = -39,  // <<
};

struct Token {
    TokenKind kind;
    std::string text;       // text from source
    int line;               // error messages
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
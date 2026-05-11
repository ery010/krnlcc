#pragma once
#include <string>

enum TokenKind {
    TOK_EOF = -1, // end of file

    // keywords
    TOK_KERNEL      = -2,   // 'kernel definition keyword'
    TOK_IF          = -3,
    TOK_ELSE        = -4,
    TOK_FOR         = -5,
    TOK_RETURN      = -6,

    // types - int-32, int-64, float-32, float-64
    TOK_I32         = -7,
    TOK_I64         = -8,
    TOK_F32         = -9,
    TOK_F64         = -10,
    TOK_PTR         = -11,   // pointer type for GPU memory

    // literals
    TOK_INT_LIT     = -12,
    TOK_FLOAT_LIT   = -13,

    // identifier
    TOK_IDENTIFIER  = -14,

    // symbols
    TOK_LPAREN      = -15,   // (
    TOK_RPAREN      = -16,   // )
    TOK_LBRACE      = -17,   // {
    TOK_RBRACE      = -18,   // }
    TOK_LBRACKET    = -19,   // [
    TOK_RBRACKET    = -20,   // ]
    TOK_COMMA       = -21,   // ,
    TOK_COLON       = -22,   // :
    TOK_SEMICOLON   = -23,  // ;
    TOK_ASSIGN      = -24,  // =
    TOK_PLUS        = -25,  // +
    TOK_MINUS       = -26,  // -
    TOK_STAR        = -27,  // *
    TOK_SLASH       = -28,  // /
    TOK_LT          = -29,  // <
    TOK_GT          = -30,  // >
    TOK_EQ          = -31,  // ==
    TOK_NEQ         = -32,  // !=
    TOK_LEQ         = -33,  // <=
    TOK_GEQ         = -34,  // >=
    TOK_AMP         = -35,  // &
    TOK_PIPE        = -36,  // |
    TOK_CARET       = -37,  // ^ 
    TOK_RSHIFT      = -38,  // >>
    TOK_LSHIFT      = -39,  // <<
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
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "token.h"

// Types

enum class Type {
    I32, I64,
    F32, F64,
    PTR_I32, PTR_I64, PTR_F32, PTR_F64,
    VOID
};

// Base expression and statement nodes

struct ExprNode {
    virtual ~ExprNode() = default;
    Type type = Type::I32;
    int line = 0;
    int col = 0;
};

struct StmtNode {
    virtual ~StmtNode() = default;
    int line = 0;
    int col = 0;
};

// Expr nodes

struct IntLitExpr : ExprNode {
    int64_t value;
};

struct FloatLitExpr : ExprNode {
    double value;
};

struct VarExpr : ExprNode {
    std::string name;
};




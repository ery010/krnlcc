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

struct IntLitExprNode : ExprNode {
    int64_t value;
};

struct FloatLitExprNode : ExprNode {
    double value;
};

struct VarExprNode : ExprNode {
    std::string name;
};

struct BinaryExprNode : ExprNode {
    std::string op;
    std::unique_ptr<ExprNode> left;
    std::unique_ptr<ExprNode> right;
};

// keys[i]
struct IndexExprNode : ExprNode {
    std::unique_ptr<ExprNode> array;
    std::unique_ptr<ExprNode> index;
};

// thread_id()
struct CallExprNode : ExprNode {
    std::string name;
    std::vector<std::unique_ptr<ExprNode>> args;
};

// Statement nodes

struct DeclVarStmtNode : StmtNode {
    std::string name;
    Type type;
    std::unique_ptr<ExprNode> init;
};




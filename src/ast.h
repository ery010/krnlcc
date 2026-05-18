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

struct AssignStmtNode : StmtNode {
    std::unique_ptr<ExprNode> target;   // VarExpr or IndexExpr
    std::unique_ptr<ExprNode> value;
};

struct IfStmtNode : StmtNode {
    std::unique_ptr<ExprNode> condition;
    std::vector<std::unique_ptr<StmtNode>> then_body;
    std::vector<std::unique_ptr<StmtNode>> else_body;
};

struct ForStmtNode : StmtNode {
    std::string var;
    std::unique_ptr<ExprNode> start;
    std::unique_ptr<ExprNode> end;
    std::vector<std::unique_ptr<StmtNode>> body;
};

struct ReturnStmtNode : StmtNode {
    std::unique_ptr<ExprNode> value;    // nullptr for void return
};

struct ExprStmtNode : StmtNode {
    std::unique_ptr<ExprNode> expr;
};

// top level
struct Param {
    std::string name;
    Type type;
};

struct KernelDefNode {
    std::string name;
    std::vector<Param> params;
    std::vector<std::unique_ptr<StmtNode>> body;
};

struct ProgramNode {
    std::vector<std::unique_ptr<KernelDefNode>> kernels;
};



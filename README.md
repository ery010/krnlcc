# krnlcc - Custom GPU Language to PTX Assembly Compiler

**krnlcc** is a compiler for a custom programming language (`.krnl`). This is mainly a project for learning about compilers, specifically GPU programming language to PTX assembly.

## Implementation Progress

### Frontend
- [x] Token definitions (`token.h`)
- [x] Lexer (`lexer.h` / `lexer.cpp`)
- [x] AST node definitions (`ast.h`)
- [ ] Parser (`parser.h` / `parser.cpp`)
- [ ] Semantic analysis / type checking

### Middle-end
- [ ] IR design (`ir.h`)
- [ ] IR generator — AST to IR (`ir.cpp`)

### Backend
- [ ] Custom PTX emitter (`codegen.h` / `codegen.cpp`)
- [ ] LLVM NVPTX backend (optional)
- [ ] CUDA Driver API runtime (`runtime/runner.cpp`)

### Example Kernels
- [ ] `vector_add.krnl` — compiles and runs on GPU
- [ ] `bloom_query.krnl` — Bloom filter lookup kernel

### Polish
- [ ] Error messages with line and column
- [ ] README benchmark results
- [ ] Nsight Compute profiling comparison vs nvcc
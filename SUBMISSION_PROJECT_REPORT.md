# Project Submission Report

## Linear Language Compiler / Interpreter Project

**Compiler Design Laboratory**
**Course No.: CSE 3212**

**Submitted To:**  
**Badiuzzaman Shuvo**  
Lecturer, CSE, KUET  
  
**Subha Nawar**  
Lecturer, CSE, KUET  

---

## Submitted By

- **Name:** Khadimul Islam Mahi
- **Roll:** 2107076
- **Section:** B
- **Year:** 3rd Year
- **Term:** 2nd Term
- **Department:** Computer Science and Engineering (CSE)
- **Institution:** Khulna University of Engineering & Technology (KUET)

---

## Project Title

### Linear: A Custom Compiler Front-End and Tree-Walking Interpreter with Native Data Structures

---

## Project Overview

This project presents a full custom language pipeline for **Linear**, implemented using **Flex**, **Bison**, and **C**. The system performs lexical analysis, grammar parsing, AST construction, semantic checks, and runtime interpretation. The language is designed for algorithmic and data-structure-oriented programming, with built-in support for advanced structures and operations.

---

## Key Unique Features of This Compiler Project

### 1. Custom Language with Native Advanced Data Structures

Unlike many mini compilers that only support primitive types, this project includes **first-class language-level support** for:

- `Graph`
- `Tree`
- `RangeTree` (Segment Tree)
- `DSU` (Disjoint Set Union)
- `Matrix`
- `OrderedSet`
- `Stack`
- `Queue`

These are not mock features; they are fully implemented in the runtime (`ds_runtime.c/h`) and directly callable from `.linear` programs.

### 2. Conflict-Free Grammar Stabilization

A major technical achievement was eliminating parser ambiguities (shift/reduce conflicts) by refactoring assignment handling as expression-based grammar. This made parsing deterministic and stable for complex expression statements and control structures.

### 3. End-to-End Compiler Pipeline

The project demonstrates the complete classical flow:

1. **Lexical Analysis** (`lexer.l` → `lex.yy.c`)
2. **Syntax Analysis / Parsing** (`parser.y` → `parser.tab.c`)
3. **AST Construction** (`ast.h`, `ast.c`)
4. **Semantic Symbol Handling** (`symbol_table.h`, `symbol_table.c`)
5. **Tree-Walking Evaluation** (`eval.c`)
6. **Native DS Runtime Execution** (`ds_runtime.h`, `ds_runtime.c`)

This gives the project educational depth and practical completeness.

### 4. Structured AST Design with Multi-Node Support

The AST supports rich node categories including declarations, assignments, conditions, loops, binary/unary operations, literals, function calls, breaks/continues, and returns. The interpreter executes these nodes recursively with proper scope behavior.

### 5. Scope-Aware Symbol Table Integration

The symbol table supports scope entry/exit during block parsing and enforces semantic checks such as undeclared-identifier detection. This adds semantic correctness beyond basic syntax parsing.

### 6. Runtime Memory Safety for Complex Objects

The evaluator uses controlled ownership logic (`value_dup`, `value_clear`) and runtime grab/free patterns for DS objects, reducing memory leak risks in a C-based interpreter.

### 7. Built-in I/O and Functional Runtime Hooks

Language-level built-ins like `MAHI_read` and `MAHI_write` are integrated into parsing and evaluation. DS function calls are dynamically dispatched in evaluator logic to native C runtime functions.

### 8. Comprehensive Integrated Testing

The project includes strong sample-based testing (e.g., `samples/test_eval.linear`) covering primitives, control flow, and all DS operations. Additional demo files document real execution flow through compiler components.

### 9. Documentation Depth

Multiple documentation artifacts were produced, including full documentation, usage guide, teacher explanation, and execution walkthrough. This makes the project highly suitable for academic evaluation and demonstration.

---

## Technical Highlights

- Built using **Flex + Bison + C**
- Supports both primitive and custom DS types
- Supports arithmetic, logical, relational, and compound assignment operators
- Supports `if/else`, `while`, `for`, `break`, `continue`, `return`
- Provides detailed parse error reporting with line context
- Converts parsed source into AST then interprets it

---

## Conclusion

This compiler project is unique because it goes beyond a textbook parser and implements a practical mini-language with a complete execution pipeline and native algorithmic data structure support. The work demonstrates strong understanding of compiler phases, grammar engineering, semantic design, AST modeling, and runtime systems.

The final implementation is stable, testable, and presentation-ready for academic submission.

---

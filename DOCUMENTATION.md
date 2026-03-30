# Full Project Documentation: The Linear Language

## 1. Introduction & Project Philosophy

**Linear** is a statically typed, Domain-Specific Language (DSL) built from scratch. It is accompanied by a custom **Tree-Walking Evaluator (Interpreter)** written entirely in C. 

The primary goal of Linear is to provide a high-performance, easy-to-use environment for designing and testing algorithms. It achieves this by providing out-of-the-box native support for Advanced Data Structures, allowing developers to focus on logic rather than re-implementing complex foundational structures.

---

## 2. Core Language Features

### 2.1. Data Types
*   **Primitives**: int, loat, ool, string, char

### 2.2. Control Flow
*   **Conditionals**: if, else
*   **Loops**: or, while
*   **Branching**: reak, continue, eturn

### 2.3. Native Data Structures
The true power of Linear lies in its built-in data structures, which are implemented in optimized C for maximum performance.
*   DSU (Disjoint Set Union)
*   Graph (Undirected Graphs)
*   Tree (Rooted Trees)
*   RangeTree (Segment Trees)
*   OrderedSet (Policy-Based Data Structure)
*   Matrix (Mathematical Matrices)
*   Stack (LIFO)
*   Queue (FIFO)

### 2.4. Built-in I/O
*   MAHI_read(variable): Reads from standard input, automatically matching the variable's type.
*   MAHI_write(value): Prints a value to standard output.

---

## 3. Getting Started: Setup & Execution

### 3.1. Prerequisites
To compile the Linear language engine, you must have the following tools installed and available in your system's PATH:
1.  **GCC** (GNU Compiler Collection), typically via MinGW-w64 on Windows.
2.  **Flex** (Fast Lexical Analyzer Generator), version 2.5+.
3.  **Bison** (GNU Parser Generator), version 2.4+.

You can verify their installation by running:
`powershell
gcc --version
flex --version
bison --version
`

### 3.2. Build Process
A Windows batch file, uild.bat, automates the entire compilation pipeline.

1.  Open a terminal (PowerShell is recommended) in the project's root directory.
2.  Execute the build script:
    `powershell
    .\build.bat
    `
This script coordinates Flex and Bison to generate the C code for the lexer and parser, then uses GCC to compile and link all necessary source files into a single executable: compiler.exe.

### 3.3. Running a Linear Program
Once compiler.exe is built, you can execute any .linear script.

**Syntax:**
`powershell
.\compiler.exe <path-to-your-script>.linear
`

**Example:**
`powershell
.\compiler.exe samples\test_eval.linear
`

---

## 4. Compiler Architecture Explained

The Linear interpreter is built upon the classic phases of compiler design.

### Phase 1: Lexical Analysis (The "Lexer")
*   **Role**: To scan the raw source code text and convert it into a stream of meaningful "tokens" (e.g., keywords, identifiers, numbers).
*   **Implementation**: lexer.l. This file contains rules that **Flex** uses to automatically generate the C code for the scanner (lex.yy.c).

### Phase 2: Syntactic Analysis (The "Parser")
*   **Role**: To take the stream of tokens from the lexer and verify that they conform to the language's grammatical rules.
*   **Implementation**: parser.y. This file contains the formal grammar for the Linear language. **Bison** uses these rules to generate the C code for the parser (parser.tab.c). If the grammar is violated, Bison reports a "Syntax Error."

### Phase 3: Abstract Syntax Tree (AST) Construction
*   **Role**: As the parser validates the grammar, it simultaneously builds a tree-like data structure in memory—the AST—that represents the code's hierarchical structure.
*   **Implementation**: st.h and st.c. These files define the ASTNode struct and provide functions like create_node() that the parser calls to build the tree.

### Phase 4: Semantic Analysis & The Symbol Table
*   **Role**: To manage the "memory" of the compiler, tracking variable names, their types, and their scope (i.e., which block of code they exist in). This prevents errors like using an undeclared variable or assigning a value of the wrong type.
*   **Implementation**: symbol_table.h and symbol_table.c. It provides a stack-based scope system; entering a { pushes a new scope, and exiting } pops it.

### Phase 5: Tree-Walking Evaluation (The "Interpreter")
*   **Role**: This is the engine that "runs" the code. It traverses the AST from its root, evaluating expressions and executing statements at each node.
*   **Implementation**: eval.c. This file contains the logic for handling every type of AST node, from mathematical operations (NODE_BINARY_OP) to control flow (NODE_IF, NODE_FOR).

### Phase 6: The Data Structure Runtime
*   **Role**: This is the special feature of Linear. It contains the high-performance C implementations of all the built-in data structures.
*   **Implementation**: ds_runtime.h and ds_runtime.c. When the evaluator encounters a function call like graph_new(), it calls the corresponding C function in this runtime, bridging the high-level language with the low-level C implementation.

---

## 5. Language API Reference

All Linear programs must be contained within a START main { ... } END block.

### 5.1. Basic Syntax
`c
START main {
    // Variable declaration
    int a = 10;
    float b = 15.5;
    string message = "Hello";

    // Conditional
    if (a > 5) {
        MAHI_write("It's greater!");
    }

    // Loop
    for (int i = 0; i < 5; i = i + 1) {
        MAHI_write(i);
    }
} END
`

### 5.2. Data Structure API

#### Graph
*   Graph graph_new(int num_vertices)
*   oid graph_add_edge(Graph g, int u, int v)
*   int graph_shortest_path(Graph g, int start, int end)
*   int graph_connected(Graph g, int u, int v)
*   int graph_dfs_count(Graph g, int start_node)

#### Tree
*   Tree tree_new(int num_vertices)
*   oid tree_set_parent(Tree t, int node, int parent)
*   int tree_lca(Tree t, int node_a, int node_b)
*   int tree_depth(Tree t, int node)

#### Disjoint Set Union (DSU)
*   DSU dsu_new(int num_elements)
*   oid dsu_union(DSU d, int a, int b)
*   int dsu_find(DSU d, int element)
*   int dsu_same(DSU d, int a, int b)

#### Matrix
*   Matrix matrix_new(int rows, int cols)
*   oid matrix_set(Matrix m, int row, int col, float value)
*   loat matrix_get(Matrix m, int row, int col)
*   Matrix matrix_add(Matrix a, Matrix b)
*   Matrix matrix_mul(Matrix a, Matrix b)
*   Matrix matrix_transpose(Matrix m)
*   Matrix matrix_identity(int size)

#### OrderedSet
*   OrderedSet oset_new()
*   oid oset_insert(OrderedSet s, int value)
*   oid oset_erase(OrderedSet s, int value)
*   int oset_size(OrderedSet s)
*   int oset_contains(OrderedSet s, int value)
*   int oset_nth(OrderedSet s, int k): Returns the k-th smallest element.

#### Stack
*   Stack stack_new()
*   oid stack_push(Stack s, int value)
*   int stack_pop(Stack s)
*   int stack_top(Stack s)
*   int stack_size(Stack s)
*   int stack_empty(Stack s)

#### Queue
*   Queue queue_new()
*   oid queue_push(Queue q, int value)
*   int queue_pop(Queue q)
*   int queue_front(Queue q)
*   int queue_size(Queue q)
*   int queue_empty(Queue q)

#### RangeTree (Segment Tree)
*   RangeTree segtree_new(int size)
*   oid segtree_set(RangeTree st, int index, int value)
*   int segtree_sum(RangeTree st, int left, int right)
*   int segtree_min(RangeTree st, int left, int right)

---

## 6. Memory Management: Reference Counting

To prevent memory leaks in a C-based interpreter, Linear uses a **Reference Counting** garbage collection model.

*   When a complex data structure (like a Graph or Matrix) is created, its reference count is set to 1.
*   When it is assigned to another variable, its reference count is incremented.
*   When a variable goes out of scope (e.g., a function returns or a {...} block ends), the reference count of the object it holds is decremented.
*   When the count reaches 0, the memory for that object is safely freed.

This entire process is handled automatically by the alue_clear() and alue_dup() functions within the eval.c interpreter core.

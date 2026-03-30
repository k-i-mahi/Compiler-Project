# Linear Language Compiler

**Linear** is a statically typed, Domain-Specific Language (DSL) built from scratch. It is accompanied by a custom Tree-Walking Evaluator (Interpreter) written entirely in C. Linear is uniquely designed to provide out-of-the-box native support for Advanced Data Structures, making it an excellent environment for algorithm design, competitive programming logic, and computational theory without needing to implement complex structures from scratch.

---

## 🌟 Features

- **Standard Data Types**: int, loat, ool, string, char
- **Control Flow**: if, else, while, or, reak, continue, eturn
- **Native Data Structures**: 
  - DSU (Disjoint Set Union)
  - Graph (Undirected Graphs)
  - Tree (Rooted Trees, Lowest Common Ancestor, Depth calculation)
  - RangeTree (Segment Trees for Range Sums and Range Minimums)
  - OrderedSet (Sorted Unique Integers / Policy Based Data Structures)
  - Matrix (Mathematical matrices, matrix algebra)
  - Stack (LIFO data structure)
  - Queue (FIFO data structure)
- **Built-in I/O Functions**:
  - MAHI_read(variable): Read input dynamically matching the variable type.
  - MAHI_write(value): Print output to standard output.

---

## 📂 Project Architecture

The compiler is divided into standard phases:
1. **Lexical Analysis (Scanner)**:  
   - lexer.l: Flex specifications to tokenize the raw .linear source code.
2. **Syntactic Analysis (Parser)**:  
   - parser.y: Bison specifications implementing the formal grammar. It handles operator precedence, validates syntax, and constructs the Abstract Syntax Tree (AST).
3. **Abstract Syntax Tree (AST)**:  
   - st.h / st.c: Definitions and implementations for AST nodes. It connects expressions and statements into an in-memory tree.
4. **Symbol Table (Semantic State)**:  
   - symbol_table.h / symbol_table.c: Handles scope-based state management, tracking variables and enforcing static typing through nested blocks ({ }).
5. **Tree-Walking Evaluator (Interpreter)**:  
   - eval.c: The core runtime engine. It walks the AST, managing local environments, evaluating mathematical expressions, and executing control flow dynamically.
6. **Data Structure Runtime Environment**:  
   - ds_runtime.h / ds_runtime.c: Highly optimized C implementations of the complex data structures (Graphs, DSUs, Matrices). The evaluator safely binds Linear variables to these native C structs in memory.

---

## 🛠 Prerequisites & Initial Setup

To compile and build the Linear language execution engine, ensure you have the following tools in your system's PATH:
1. **GCC** (GNU Compiler Collection - typically via MinGW-w64 on Windows).
2. **Flex** (Fast Lexical Analyzer Generator, v2.5+).
3. **Bison** (GNU Parser Generator, v2.4+).

### Verifying your tools:
Open a terminal and run:
\\\powershell
gcc --version
flex --version
bison --version
\\\

---

## 🚀 Build Instructions

A uild.bat Windows batch file is included to automate the compilation process. This resolves specific cyclic dependencies and correctly links libraries.

1. Open your terminal (PowerShell or Command Prompt) at the project root.
2. Run the build script:

\\\powershell
.\build.bat
\\\

**What happens underneath:**
- Generates parser.tab.c and parser.tab.h using Bison.
- Generates lex.yy.c using Flex.
- Compiles all C files (lex.yy.c, parser.tab.c, st.c, symbol_table.c, eval.c, ds_runtime.c) into a single executable compiler.exe.

---

## 💻 Usage & Execution

Once the executable is built, you can run any valid .linear program.

\\\powershell
.\compiler.exe <path-to-script>.linear
\\\

### Example Execution:
\\\powershell
.\compiler.exe samples\test_eval.linear
\\\

---

## 📖 Language Documentation & API

Linear programs must be enclosed within a START main { ... } END block.

### 1. Variables and Flow Control
\\\c
START main {
    int max_val = 10;
    int sum = 0;
    
    for (int j = 1; j <= max_val; j = j + 1) {
        if (j % 2 == 0) {
            sum = sum + j;
        }
    }
    MAHI_write("Sum of even numbers:");
    MAHI_write(sum);
} END
\\\

### 2. Stack & Queue API
\\\c
    Stack stck = stack_new();
    stack_push(stck, 100);
    int top_val = stack_top(stck);  // 100
    stack_pop(stck);
    int s = stack_size(stck);       // 0

    Queue q = queue_new();
    queue_push(q, 300);
    int front_val = queue_front(q); // 300
    queue_pop(q);
\\\

### 3. Graph API
\\\c
    // Create an undirected graph with 5 vertices
    Graph mygraph = graph_new(5);
    graph_add_edge(mygraph, 0, 1);
    graph_add_edge(mygraph, 1, 2);
    
    // Perform BFS to find shortest path
    int dist = graph_shortest_path(mygraph, 0, 2); // returns 2
\\\

### 4. DSU (Disjoint Set Union)
\\\c
    DSU mydsu = dsu_new(10);
    dsu_union(mydsu, 1, 2);
    dsu_union(mydsu, 2, 3);
    
    int is_connected = dsu_same(mydsu, 1, 3); // 1 (true)
    int not_connected = dsu_same(mydsu, 1, 4); // 0 (false)
\\\

### 5. Ordered Set (Policy Based Data Structure)
\\\c
    OrderedSet myset = oset_new();
    oset_insert(myset, 10);
    oset_insert(myset, 5);
    oset_insert(myset, 20);
    
    int smallest = oset_nth(myset, 0); // returns 5
    int mid = oset_nth(myset, 1);      // returns 10
\\\

### 6. Matrices Operations
\\\c
    Matrix matA = matrix_new(2, 2);
    matrix_set(matA, 0, 0, 1.0);
    
    Matrix matI = matrix_identity(2);
    Matrix matR = matrix_mul(matA, matI);
    float val = matrix_get(matR, 0, 0); // 1.0
\\\

### 7. Segment Tree (Range Queries)
\\\c
    RangeTree st = segtree_new(10);
    segtree_set(st, 0, 5);
    segtree_set(st, 1, 10);
    segtree_set(st, 2, 15);
    int rsum = segtree_sum(st, 0, 2); // 30
    int rmin = segtree_min(st, 0, 2); // 5
\\\

---

## 🧠 Memory Management Architecture

To prevent C-based memory leaks (since Linear compiles and interfaces dynamically via a tree walker), the interpreter utilizes **Reference Counting**. 

- The Value struct standardizes variants ranging from basic primitives to complex structures.
- Whenever highly complex data structures (Graph, Tree, Stack, Matrix) are passed, appended, or evaluated, they are incremented (obj_grab()) through reference linking.
- When block scopes are exited (}), the AST traversal initiates alue_clear(&v) automatically decrementing counters, wiping memory chunks exactly when references fall to 0. This simulates modern Garbage Collection locally.

# Compiler Project Explanation Guide

If your teacher asks you: *"How does your compiler work, and what do all these files do?"* you can use this guide to explain the entire pipeline.

## The Big Picture
Your project is an **Interpreter/Tree-Walking Evaluator** for a custom Domain-Specific Language (DSL) called **Linear**. 
Unlike standard C or C++ which compiles directly to machine code (0s and 1s), your language reads the code, understands its structure, builds a "Tree" out of it, and then "walks" that tree to execute the instructions one by one.

The process happens in **5 Main Phases**:

---

## Phase 1: Lexical Analysis (The Lexer)
**Question: What is a Lexical Analyzer?**
Imagine you are reading an English sentence: *"The cat ran."* Your brain first separates the letters into words. A Lexical Analyzer does this for code. It takes raw text (characters) and groups them into meaningful chunks called **Tokens** (like Keywords, Numbers, Identifiers, Operators).

**Where is it in our code?**
* **File:** lexer.l
* **Tool Used:** **Flex** (Fast Lexical Analyzer Generator). Flex is a tool that reads the rules in lexer.l and automatically generates a C engine (lex.yy.c) to scan the text.
* **Example in your code:** When the lexer sees the word if, it tells the compiler "Hey, I found a token called T_IF!". When it sees 5, it says "I found an integer literal: 5!".

---

## Phase 2: Syntactic Analysis (The Parser)
**Question: What is Bison / a Parser?**
Now that we have words (Tokens), we need to check if the sentence makes grammatical sense. *"Ran cat the"* uses real words, but it is grammatically incorrect. A parser checks the tokens against the **Grammar Rules** of your programming language. 

**Where is it in our code?**
* **File:** parser.y
* **Tool Used:** **Bison**. Bison is a Parser Generator. It reads the grammar rules you wrote in parser.y and generates C code (parser.tab.c) to check the grammar.
* **Example in your code:** In parser.y, you have a rule for a while loop: 
  T_WHILE T_LPAREN expression T_RPAREN statement.
  This means Bison expects the exact grammatical order of: while ( some math/logic ) { some code }. If the programmer misses a parenthesis, Bison throws a "Syntax Error".

---

## Phase 3: The Abstract Syntax Tree (AST)
**Question: What happens after we check the grammar?**
As Bison checks the grammar, it simultaneously builds an **Abstract Syntax Tree (AST)**. This is a data structure in memory that represents the hierarchy of the code.

For example, x = 5 + 3 becomes a tree:
       =
      / \
     x   +
        / \
       5   3

**Where is it in our code?**
* **Files:** st.h and st.c
* **How it works:** In parser.y, every time a rule correctly matches, it calls create_node() (from st.c) to build a piece of the tree. The entire program becomes one giant tree connected starting from NODE_PROGRAM.

---

## Phase 4: Semantic Analysis & Symbol Table
**Question: How does the compiler remember variables?**
If a user writes int count = 10; and later says count = count + 1;, the compiler needs to remember what count is and that it holds an int. This memory is called the **Symbol Table**.

**Where is it in our code?**
* **Files:** symbol_table.h and symbol_table.c
* **How it works:** Every time a new variable is declared in the parser, it gets inserted into the Symbol Table. When the variable is used later, the compiler looks it up to ensure it exists and the data type matches (preventing you from adding a String to a Graph, for example).

---

## Phase 5: The Evaluator (Interpreter Mode)
**Question: How does the code actually run?**
Once the AST (Tree) is fully built and grammatically correct, we need to run it. The Evaluator starts at the root of the tree and "walks" down the branches, executing what the nodes tell it to do.

**Where is it in our code?**
* **File:** eval.c
* **How it works:** This is the heart of your project. The function eval_stmt() checks the node type. 
  - If it is a NODE_IF, it evaluates the condition node. If the condition is true, it executes the body node.
  - If it is a NODE_FOR, it runs a C while(1) loop that constantly evaluates the loop structures.
  - If it sees a built-in function like MAHI_write(), it grabs the evaluated variable and uses C's printf to print it to the terminal screen.

---

## Bonus Phase: Data Structure Runtime (The Special Feature!)
**Question: Why is this language special?**
Most languages require you to build things like Graphs, Disjoint Set Unions (DSU), or Segment Trees from scratch. **Your language has them built-in natively.**

**Where is it in our code?**
* **Files:** ds_runtime.h and ds_runtime.c
* **How it works:** These files contain highly optimized, pure C implementations of complex data structures. When the user types Stack stck = stack_new(); in your language, the evaluator (eval.c) intercepts this and actually runs lin_stack_new() inside ds_runtime.c to allocate real computer memory for the stack. 

---

## Summary to tell your teacher:
"My project is a custom Interpreter built in C. I used **Flex** to scan the text into tokens (Lexer), and **Bison** to validate the grammar and generate an Abstract Syntax Tree (Parser). Then, I wrote a custom **Tree-Walking Evaluator** (eval.c) that traverses the syntax tree to run the code. Additionally, I implemented my own Symbol Table for scope management, and a native Data Structure library (ds_runtime.c) so my language can instantly use things like Graphs, Segment Trees, and Matrices without external libraries."

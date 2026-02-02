# Token Mapping Reference

**Course:** Compiler Design Laboratory  
**Project:** Linear – A Mini Compiler with Advanced Data Structures  
**Student:** Khadimul Islam Mahi | Roll: 2107076 | Section: B

---

## Keywords

| Serial | Linear Keyword | Token Type | C/C++ Equivalent | Purpose |
|:------:|----------------|------------|------------------|---------|
| 1 | `begin` | KEYWORD | `{` | Marks the start of a code block |
| 2 | `end` | KEYWORD | `}` | Marks the end of a code block |
| 3 | `if` | KEYWORD | `if` | Conditional branching |
| 4 | `else` | KEYWORD | `else` | Alternative branch in conditionals |
| 5 | `while` | KEYWORD | `while` | Loop with pre-condition check |
| 6 | `for` | KEYWORD | `for` | Iteration with counter |
| 7 | `break` | KEYWORD | `break` | Exit from loop body |
| 8 | `continue` | KEYWORD | `continue` | Skip to next loop iteration |
| 9 | `return` | KEYWORD | `return` | Return value from function |
| 10 | `func` | KEYWORD | — | Function declaration prefix |
| 11 | `read` | KEYWORD | `cin >> / scanf` | Read input from user |
| 12 | `print` | KEYWORD | `cout << / printf` | Display output to console |
| 13 | `const` | KEYWORD | `const` | Declare constant variable |
| 14 | `main` | KEYWORD | `main` | Entry point of program |
| 15 | `null` | KEYWORD | `nullptr / NULL` | Represents null reference |

---

## Data Types

### Primitive Types

| Serial | Linear Type | Token Type | C/C++ Equivalent | Description |
|:------:|-------------|------------|------------------|-------------|
| 1 | `int` | TYPE | `int` | 32-bit signed integer |
| 2 | `float` | TYPE | `float / double` | Floating point number |
| 3 | `bool` | TYPE | `bool` | Boolean (true/false) |
| 4 | `char` | TYPE | `char` | Single ASCII character |
| 5 | `string` | TYPE | `std::string` | Character sequence |
| 6 | `void` | TYPE | `void` | No return type |

### Custom Data Structures

| Serial | Linear Type | Token Type | Implementation | Supported Operations |
|:------:|-------------|------------|----------------|----------------------|
| 1 | `graph` | TYPE | Adjacency List | BFS, DFS, shortest path, connectivity check |
| 2 | `tree` | TYPE | Tree with parent pointers | LCA, subtree queries, kth ancestor |
| 3 | `range_tree` | TYPE | Segment Tree | Range sum/min/max, point update |
| 4 | `dsu` | TYPE | Union-Find | Union by rank, path compression |
| 5 | `matrix` | TYPE | 2D Array | Add, multiply, transpose, determinant |
| 6 | `ordered_set` | TYPE | PBDS Tree | Insert, erase, find_by_order, order_of_key |

---

## Operators

### Arithmetic Operators

| Serial | Symbol | Token Type | Token Value | Operation |
|:------:|:------:|------------|-------------|-----------|
| 1 | `+` | ARITH_OP | PLUS | Addition |
| 2 | `-` | ARITH_OP | MINUS | Subtraction |
| 3 | `*` | ARITH_OP | MULTIPLY | Multiplication |
| 4 | `/` | ARITH_OP | DIVIDE | Division |
| 5 | `%` | ARITH_OP | MODULO | Modulus (remainder) |

### Relational Operators

| Serial | Symbol | Token Type | Token Value | Operation |
|:------:|:------:|------------|-------------|-----------|
| 1 | `<` | REL_OP | LESS_THAN | Less than comparison |
| 2 | `>` | REL_OP | GREATER_THAN | Greater than comparison |
| 3 | `<=` | REL_OP | LESS_EQUAL | Less than or equal |
| 4 | `>=` | REL_OP | GREATER_EQUAL | Greater than or equal |
| 5 | `==` | REL_OP | EQUAL | Equality check |
| 6 | `!=` | REL_OP | NOT_EQUAL | Inequality check |

### Logical Operators

| Serial | Symbol | Token Type | Token Value | Operation |
|:------:|:------:|------------|-------------|-----------|
| 1 | `&&` | LOGICAL_OP | LOGICAL_AND | Logical AND |
| 2 | `\|\|` | LOGICAL_OP | LOGICAL_OR | Logical OR |
| 3 | `!` | LOGICAL_OP | LOGICAL_NOT | Logical NOT |
| 4 | `and` | LOGICAL_OP | AND | Logical AND (word form) |
| 5 | `or` | LOGICAL_OP | OR | Logical OR (word form) |
| 6 | `not` | LOGICAL_OP | NOT | Logical NOT (word form) |

### Assignment Operators

| Serial | Symbol | Token Type | Token Value | Operation |
|:------:|:------:|------------|-------------|-----------|
| 1 | `=` | ASSIGN_OP | ASSIGN | Simple assignment |
| 2 | `+=` | ASSIGN_OP | PLUS_ASSIGN | Add and assign |
| 3 | `-=` | ASSIGN_OP | MINUS_ASSIGN | Subtract and assign |
| 4 | `*=` | ASSIGN_OP | MULTIPLY_ASSIGN | Multiply and assign |
| 5 | `/=` | ASSIGN_OP | DIVIDE_ASSIGN | Divide and assign |
| 6 | `%=` | ASSIGN_OP | MODULO_ASSIGN | Modulus and assign |

### Increment and Decrement Operators

| Serial | Symbol | Token Type | Token Value | Operation |
|:------:|:------:|------------|-------------|-----------|
| 1 | `++` | INC_DEC_OP | INCREMENT | Increase value by 1 |
| 2 | `--` | INC_DEC_OP | DECREMENT | Decrease value by 1 |

---

## Delimiters and Punctuators

| Serial | Symbol | Token Type | Token Value | Purpose |
|:------:|:------:|------------|-------------|---------|
| 1 | `(` | DELIMITER | LPAREN | Open parenthesis |
| 2 | `)` | DELIMITER | RPAREN | Close parenthesis |
| 3 | `[` | DELIMITER | LBRACKET | Open square bracket |
| 4 | `]` | DELIMITER | RBRACKET | Close square bracket |
| 5 | `;` | DELIMITER | SEMICOLON | Statement terminator |
| 6 | `,` | DELIMITER | COMMA | Separator |
| 7 | `.` | DELIMITER | DOT | Member access |

---

## Literals

| Serial | Literal Type | Token Type | Pattern | Example |
|:------:|--------------|------------|---------|---------|
| 1 | Integer | INT_LITERAL | `[0-9]+` | `42`, `100`, `0` |
| 2 | Floating Point | FLOAT_LITERAL | `[0-9]+\.[0-9]+` | `3.14`, `0.5` |
| 3 | Boolean | BOOL_LITERAL | `true \| false` | `true`, `false` |
| 4 | Character | CHAR_LITERAL | `'.'` | `'a'`, `'Z'`, `'9'` |
| 5 | String | STRING_LITERAL | `".*"` | `"hello"`, `"test"` |

---

## Identifiers

| Attribute | Specification |
|-----------|---------------|
| Token Type | IDENTIFIER |
| Pattern | `[a-zA-Z_][a-zA-Z0-9_]*` |
| Constraints | Must begin with letter or underscore |
| Case Sensitivity | Yes |
| Reserved | Cannot match any keyword or type |

---

## Custom Functions

| Serial | Function Name | Token Type | Parameters | Return Type | Description |
|:------:|---------------|------------|------------|-------------|-------------|
| 1 | `mahi_sum` | CUSTOM_FUNC | `(arr, n)` | `int` | Computes sum of array elements |
| 2 | `mahi_reverse` | CUSTOM_FUNC | `(str)` | `string` | Reverses a string |
| 3 | `mahi_gcd` | CUSTOM_FUNC | `(a, b)` | `int` | Computes GCD using Euclidean algorithm |
| 4 | `mahi_isprime` | CUSTOM_FUNC | `(n)` | `bool` | Checks if number is prime |

### Function Specifications

#### `mahi_sum(arr, n)`
```
Input  : Integer array and its size
Output : Sum of all elements
Note   : Returns 0 if array is empty
```

#### `mahi_reverse(str)`
```
Input  : String value
Output : Reversed string
Note   : Original string remains unchanged
```

#### `mahi_gcd(a, b)`
```
Input  : Two integer values
Output : Greatest common divisor
Note   : Uses iterative Euclidean method
```

#### `mahi_isprime(n)`
```
Input  : Single integer
Output : true if prime, false otherwise
Note   : Optimized with 6k±1 check
```

---

## Comments

| Style | Token Handling | Example |
|-------|----------------|---------|
| Single-line | Ignored by lexer | `// this is a comment` |

---

## Token Output Format

The lexer generates tokens in the following format for parser consumption:

```
<TOKEN_TYPE, VALUE, line:N>
```

| Component | Description |
|-----------|-------------|
| TOKEN_TYPE | Category of the token (KEYWORD, TYPE, etc.) |
| VALUE | Actual lexeme or token sub-type |
| line:N | Source line number for error reporting |

---

## Summary Statistics

| Category | Count |
|----------|:-----:|
| Keywords | 15 |
| Primitive Types | 6 |
| Custom Types | 6 |
| Arithmetic Operators | 5 |
| Relational Operators | 6 |
| Logical Operators | 6 |
| Assignment Operators | 6 |
| Inc/Dec Operators | 2 |
| Delimiters | 7 |
| Literal Types | 5 |
| Custom Functions | 4 |
| **Total Token Categories** | **15** |

---

*Compiler Design Laboratory — 3rd Year, 2nd Term*

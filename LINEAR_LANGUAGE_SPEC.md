# Linear Language Specification

## Compiler Project Report
### "Linear" - A Mini Compiler with Advanced Data Structures

**Student:** Khadimul Islam Mahi  
**Roll No:** 2107076, Section B  
**Year:** 3rd Year, 2nd Term

---

## 1. Project Information

| Field | Details |
|-------|---------|
| Project Title | Linear – A Mini Compiler with Advanced Data Structures |
| Course Name | Compiler Design Laboratory |
| Tools Used | Flex, Bison, C/C++ |
| Student Name | Khadimul Islam Mahi |
| Roll No | 2107076 |
| Section | B |
| Year | 3rd Year |
| Term | 2nd Term |

---

## 2. Language Overview

| Aspect | Description |
|--------|-------------|
| Language Name | Linear |
| Language Type | Procedural |
| Case Sensitivity | Case-sensitive |
| Statement Terminator | Semicolon (;) |
| Comment Style | Single-line (//) |
| Execution Model | Sequential |
| Functions | User-defined, supports recursion |
| Modularization | Scope-based symbol table management |

---

## 3. Supported Data Types

### 3.1 Primitive Data Types

| Linear Type | C/C++ Equivalent | Description |
|-------------|------------------|-------------|
| `int` | `int` | Integer values |
| `float` | `float/double` | Floating-point values |
| `bool` | `bool/int` | Boolean values (true/false) |
| `char` | `char` | Single character |
| `string` | `std::string` | Sequence of characters |

### 3.2 Custom Data Types and Functionalities

| Linear Type | Functionalities |
|-------------|-----------------|
| `graph` | Store nodes/edges (adjacency list), BFS, DFS, shortest path, connectivity |
| `tree` | Hierarchical data, LCA, subtree queries, kth ancestor |
| `range_tree` | Range queries (sum/min/max), point updates, O(log N) operations |
| `dsu` | Union-find, path compression, union by rank, MST support |
| `matrix` | Addition, subtraction, multiplication, transpose, identity |
| `ordered_set` | Sorted elements, insert/erase, find by order, order-of-key |

---

## 4. Keywords

### 4.1 Original Keywords (from Proposal)

| Keyword | C/C++ Equivalent | Description |
|---------|------------------|-------------|
| `begin` | `{` | Block start |
| `end` | `}` | Block end |
| `int` | `int` | Integer type |
| `float` | `float` | Float type |
| `bool` | `bool` | Boolean type |
| `char` | `char` | Character type |
| `string` | `std::string` | String type |
| `if` | `if` | Conditional if |
| `else` | `else` | Conditional else |
| `while` | `while` | While loop |
| `for` | `for` | For loop |
| `read` | `cin >>` / `scanf` | Input statement |
| `print` | `cout <<` / `printf` | Output statement |
| `return` | `return` | Function return |

### 4.2 Additional Keywords (for Complete Language)

| Keyword | C/C++ Equivalent | Description |
|---------|------------------|-------------|
| `void` | `void` | Void return type |
| `true` | `true` / `1` | Boolean true |
| `false` | `false` / `0` | Boolean false |
| `const` | `const` | Constant declaration |
| `break` | `break` | Exit loop |
| `continue` | `continue` | Skip iteration |
| `func` | function definition | Function declaration keyword |
| `main` | `main` | Main function identifier |
| `null` | `nullptr` / `NULL` | Null value |
| `and` | `&&` | Logical AND (alternative) |
| `or` | `\|\|` | Logical OR (alternative) |
| `not` | `!` | Logical NOT (alternative) |

### 4.3 Data Structure Keywords

| Keyword | Description |
|---------|-------------|
| `graph` | Graph data structure |
| `tree` | Tree data structure |
| `range_tree` | Segment/Range tree |
| `dsu` | Disjoint Set Union |
| `matrix` | Matrix data structure |
| `ordered_set` | PBDS Ordered Set |

---

## 5. Operators

### 5.1 Arithmetic Operators

| Operator | C/C++ Equivalent | Description |
|----------|------------------|-------------|
| `+` | `+` | Addition |
| `-` | `-` | Subtraction |
| `*` | `*` | Multiplication |
| `/` | `/` | Division |
| `%` | `%` | Modulus |

### 5.2 Relational Operators

| Operator | C/C++ Equivalent | Description |
|----------|------------------|-------------|
| `==` | `==` | Equal to |
| `!=` | `!=` | Not equal to |
| `<` | `<` | Less than |
| `>` | `>` | Greater than |
| `<=` | `<=` | Less than or equal to |
| `>=` | `>=` | Greater than or equal to |

### 5.3 Logical Operators

| Operator | C/C++ Equivalent | Description |
|----------|------------------|-------------|
| `&&` | `&&` | Logical AND |
| `\|\|` | `\|\|` | Logical OR |
| `!` | `!` | Logical NOT |

### 5.4 Assignment Operators

| Operator | C/C++ Equivalent | Description |
|----------|------------------|-------------|
| `=` | `=` | Assignment |
| `+=` | `+=` | Add and assign |
| `-=` | `-=` | Subtract and assign |
| `*=` | `*=` | Multiply and assign |
| `/=` | `/=` | Divide and assign |
| `%=` | `%=` | Modulus and assign |

### 5.5 Increment/Decrement Operators

| Operator | C/C++ Equivalent | Description |
|----------|------------------|-------------|
| `++` | `++` | Increment |
| `--` | `--` | Decrement |

---

## 6. Control Structures

### 6.1 Conditional Statements

```linear
if (a > b)
begin
    print(a);
end
else
begin
    print(b);
end
```

### 6.2 Loops

```linear
// While loop
while (i < 10)
begin
    i += 1;
end

// For loop
for (i = 0; i < 5; i = i + 1)
begin
    print(i);
end
```

---

## 7. Input and Output

| Linear Statement | C++ Equivalent | Description |
|------------------|----------------|-------------|
| `read(x);` | `cin >> x;` | Input value |
| `print(x);` | `cout << x;` | Output value |
| `print("Hello");` | `cout << "Hello";` | String output |

---

## 8. Custom Functions (Unique to Mahi - 2107076)

### 8.1 `mahi_sum(arr, n)` - Array Sum with Validation

Computes the sum of an integer array with bounds checking.

```linear
// Usage
int arr[5] = {1, 2, 3, 4, 5};
int total = mahi_sum(arr, 5);
print(total);  // Output: 15
```

**C++ Translation:**
```cpp
int mahi_sum(int* arr, int n) {
    if (n <= 0) return 0;
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}
```

### 8.2 `mahi_reverse(str)` - String Reversal

Reverses a string in-place and returns it.

```linear
// Usage
string s = "hello";
string rev = mahi_reverse(s);
print(rev);  // Output: olleh
```

**C++ Translation:**
```cpp
std::string mahi_reverse(std::string str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
    return str;
}
```

### 8.3 `mahi_gcd(a, b)` - Greatest Common Divisor

Computes the GCD of two integers using Euclidean algorithm.

```linear
// Usage
int result = mahi_gcd(48, 18);
print(result);  // Output: 6
```

**C++ Translation:**
```cpp
int mahi_gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

### 8.4 `mahi_isprime(n)` - Prime Number Check

Checks if a number is prime.

```linear
// Usage
bool check = mahi_isprime(17);
if (check)
begin
    print("Prime");
end
```

**C++ Translation:**
```cpp
bool mahi_isprime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
```

---

## 9. Token Categories for Lexer

| Category | Tokens |
|----------|--------|
| **Keywords** | `begin`, `end`, `if`, `else`, `while`, `for`, `return`, `read`, `print`, `func`, `void`, `true`, `false`, `const`, `break`, `continue`, `main`, `null`, `and`, `or`, `not` |
| **Data Types** | `int`, `float`, `bool`, `char`, `string`, `graph`, `tree`, `range_tree`, `dsu`, `matrix`, `ordered_set` |
| **Custom Functions** | `mahi_sum`, `mahi_reverse`, `mahi_gcd`, `mahi_isprime` |
| **Operators** | `+`, `-`, `*`, `/`, `%`, `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `++`, `--`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `\|\|`, `!` |
| **Delimiters** | `(`, `)`, `[`, `]`, `;`, `,`, `.` |
| **Literals** | Integer, Float, String, Character |
| **Identifiers** | Variable/function names |
| **Comments** | `//` single-line comments |

---

## 10. Semantic Analysis and Error Handling

The compiler includes:
- **Symbol Table** for storing identifier information (type, scope)
- **Undeclared variable detection**
- **Redeclaration detection**
- **Type mismatch detection**
- **Line number reporting for errors**

---

## 11. Tools and Technologies

- **Flex** – Lexical analysis
- **Bison** – Syntax analysis  
- **GCC** – Compilation
- **C/C++** – Semantic and runtime support
- **PBDS** – Ordered set and tree-based operations

---

*Document Version: 1.0*  
*Author: Khadimul Islam Mahi (2107076)*

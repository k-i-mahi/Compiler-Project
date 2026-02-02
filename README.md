# Linear Compiler - Command Guide

## Author
**Khadimul Islam Mahi**  
Roll No: 2107076, Section B  
3rd Year, 2nd Term

---

## Prerequisites

Ensure the following tools are installed and in your PATH:

| Tool | Version | Check Command |
|------|---------|---------------|
| GCC | 13.2.0+ | `gcc --version` |
| Flex | 2.5.4+ | `flex --version` |
| Bison | 2.4.1+ | `bison --version` |

---

## Project Structure

```
Compiler-Project/
├── lexer.l                      # Flex lexer specification
├── LINEAR_LANGUAGE_SPEC.md      # Language specification document
├── README.md                    # This file (Command Guide)
├── Linear.pdf                   # Original proposal
├── samples/
│   ├── sample1_basic.linear     # Basic operations sample
│   ├── sample2_functions.linear # Functions sample
│   └── sample3_operators.linear # Operators sample
└── output/                      # Generated output files
```

---

## Build Commands

### Step 1: Generate C code from Flex specification

```powershell
# Navigate to project directory
cd "F:\Compiler-Project"

# Run Flex to generate lex.yy.c
flex lexer.l
```

This creates `lex.yy.c` file.

### Step 2: Compile the lexer

```powershell
# Compile with GCC
gcc lex.yy.c -o linear_lexer.exe
```

This creates `linear_lexer.exe` executable.

### One-liner (Build all):

```powershell
flex lexer.l ; gcc lex.yy.c -o linear_lexer.exe
```

---

## Usage

### Basic Usage

```powershell
# Syntax
.\linear_lexer.exe <input_file> [output_file]

# Parameters:
#   input_file  : Path to .linear source file (required)
#   output_file : Path to output tokens file (optional, default: tokens.txt)
```

### Examples

```powershell
# Tokenize sample1 with default output
.\linear_lexer.exe samples\sample1_basic.linear

# Tokenize sample2 with custom output file
.\linear_lexer.exe samples\sample2_functions.linear output\sample2_tokens.txt

# Tokenize sample3
.\linear_lexer.exe samples\sample3_operators.linear output\sample3_tokens.txt
```

---

## Quick Test Commands

```powershell
# Full build and test sequence
cd "F:\Compiler-Project"

# 1. Build the lexer
flex lexer.l
gcc lex.yy.c -o linear_lexer.exe

# 2. Create output directory
mkdir output -ErrorAction SilentlyContinue

# 3. Run on all samples
.\linear_lexer.exe samples\sample1_basic.linear output\sample1_tokens.txt
.\linear_lexer.exe samples\sample2_functions.linear output\sample2_tokens.txt
.\linear_lexer.exe samples\sample3_operators.linear output\sample3_tokens.txt

# 4. View output
Get-Content output\sample1_tokens.txt
```

---

## Output Format

The lexer outputs tokens in the following format:

```
<TOKEN_TYPE, VALUE, line:LINE_NUMBER>
```

### Token Types

| Token Type | Description | Example |
|------------|-------------|---------|
| `KEYWORD` | Reserved words | `<KEYWORD, IF, line:5>` |
| `TYPE` | Data types | `<TYPE, INT, line:1>` |
| `IDENTIFIER` | Variable names | `<IDENTIFIER, myVar, line:3>` |
| `INT_LITERAL` | Integer values | `<INT_LITERAL, 42, line:7>` |
| `FLOAT_LITERAL` | Float values | `<FLOAT_LITERAL, 3.14, line:8>` |
| `STRING_LITERAL` | String values | `<STRING_LITERAL, "hello", line:9>` |
| `ARITH_OP` | Arithmetic operators | `<ARITH_OP, PLUS, line:10>` |
| `REL_OP` | Relational operators | `<REL_OP, LESS_THAN, line:11>` |
| `LOGICAL_OP` | Logical operators | `<LOGICAL_OP, AND, line:12>` |
| `ASSIGN_OP` | Assignment operators | `<ASSIGN_OP, ASSIGN, line:13>` |
| `DELIMITER` | Punctuation | `<DELIMITER, SEMICOLON, line:14>` |
| `CUSTOM_FUNC` | Custom functions | `<CUSTOM_FUNC, MAHI_GCD, line:15>` |

---

## Custom Functions (Unique to Mahi - 2107076)

| Function | Description | Usage |
|----------|-------------|-------|
| `mahi_sum(arr, n)` | Sum of array elements | `int total = mahi_sum(arr, 5);` |
| `mahi_reverse(str)` | Reverse a string | `string rev = mahi_reverse(s);` |
| `mahi_gcd(a, b)` | Greatest Common Divisor | `int g = mahi_gcd(48, 18);` |
| `mahi_isprime(n)` | Check if number is prime | `bool p = mahi_isprime(17);` |

---

## Troubleshooting

### Flex not found
```powershell
# Check if GnuWin32 is in PATH
$env:Path = [Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [Environment]::GetEnvironmentVariable("Path", "User")
flex --version
```

### Compilation errors
```powershell
# Ensure GCC is installed
gcc --version

# If using MinGW, ensure it's in PATH
```

### File not found errors
```powershell
# Use absolute paths or navigate to project directory first
cd "F:\Compiler-Project"
```

---

## Clean Build

```powershell
# Remove generated files
Remove-Item lex.yy.c -ErrorAction SilentlyContinue
Remove-Item linear_lexer.exe -ErrorAction SilentlyContinue
Remove-Item output\*.txt -ErrorAction SilentlyContinue

# Rebuild
flex lexer.l
gcc lex.yy.c -o linear_lexer.exe
```

---

## Version Info

- **Lexer Version:** 1.0
- **Language:** Linear
- **Author:** Khadimul Islam Mahi (2107076)
- **Date:** February 2, 2026

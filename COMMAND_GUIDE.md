# Linear Lexer - Command Line Guide

**Author:** Khadimul Islam Mahi (2107076)  
**Project:** Linear Language Compiler

---

## Prerequisites

Make sure the following tools are installed and available in your system PATH:

| Tool | Version | Purpose |
|------|---------|---------|
| Flex | 2.5.4+ | Lexer generator |
| GCC | 13.0+ | C compiler |

To verify installation:
```powershell
flex --version
gcc --version
```

---

## Build Commands

### Step 1: Generate C Code from Flex Specification

```powershell
flex -o lex.yy.c lexer.l
```

| Flag | Description |
|------|-------------|
| `-o lex.yy.c` | Specifies output filename |
| `lexer.l` | Input Flex specification file |

### Step 2: Compile the Generated C Code

```powershell
gcc -o linear_lexer.exe lex.yy.c
```

| Flag | Description |
|------|-------------|
| `-o linear_lexer.exe` | Output executable name |
| `lex.yy.c` | Input C file from Flex |

### Combined Build (Single Command)

```powershell
flex -o lex.yy.c lexer.l; gcc -o linear_lexer.exe lex.yy.c
```

---

## Running the Lexer

### Basic Usage

```powershell
.\linear_lexer.exe <input_file> [output_file]
```

| Argument | Required | Description |
|----------|----------|-------------|
| `input_file` | Yes | Path to Linear source file (.linear) |
| `output_file` | No | Path for token output (default: tokens.txt) |

### Examples

**Run with default output:**
```powershell
.\linear_lexer.exe samples\sample1_basic.linear
```
Output written to `tokens.txt`

**Run with custom output:**
```powershell
.\linear_lexer.exe samples\sample1_basic.linear output\sample1_tokens.txt
```
Output written to `output\sample1_tokens.txt`

**Process multiple files:**
```powershell
.\linear_lexer.exe samples\sample1_basic.linear output\sample1.txt
.\linear_lexer.exe samples\sample2_functions.linear output\sample2.txt
.\linear_lexer.exe samples\sample3_operators.linear output\sample3.txt
```

---

## Output Format

The lexer generates tokens in this format:
```
<TOKEN_TYPE, VALUE, line:N>
```

**Example output:**
```
<TYPE, INT, line:1>
<IDENTIFIER, x, line:1>
<ASSIGN_OP, ASSIGN, line:1>
<INT_LITERAL, 10, line:1>
<DELIMITER, SEMICOLON, line:1>
```

---

## Verifying Output

### View Token Output
```powershell
Get-Content output\sample1_tokens.txt
```

### Search for Specific Tokens
```powershell
Select-String "KEYWORD" output\sample1_tokens.txt
Select-String "CUSTOM_FUNC" output\sample1_tokens.txt
Select-String "ERROR" output\sample1_tokens.txt
```

### Count Tokens by Type
```powershell
Select-String "KEYWORD" output\sample1_tokens.txt | Measure-Object
```

---

## Quick Reference

| Task | Command |
|------|---------|
| Build lexer | `flex -o lex.yy.c lexer.l; gcc -o linear_lexer.exe lex.yy.c` |
| Run lexer | `.\linear_lexer.exe input.linear output.txt` |
| View output | `Get-Content output.txt` |
| Find errors | `Select-String "Error" output.txt` |
| Count lines | `(Get-Content output.txt).Count` |

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| `flex` not recognized | Add `C:\Program Files (x86)\GnuWin32\bin` to PATH |
| `gcc` not recognized | Install MinGW and add to PATH |
| Cannot open input file | Check file path and ensure file exists |
| Cannot create output file | Ensure output directory exists |

### Create Output Directory
```powershell
New-Item -ItemType Directory -Path output -Force
```

---

## Sample Test Run

```powershell
# Build the lexer
flex -o lex.yy.c lexer.l
gcc -o linear_lexer.exe lex.yy.c

# Create output directory
New-Item -ItemType Directory -Path output -Force

# Run on all sample files
.\linear_lexer.exe samples\sample1_basic.linear output\sample1.txt
.\linear_lexer.exe samples\sample2_functions.linear output\sample2.txt
.\linear_lexer.exe samples\sample3_operators.linear output\sample3.txt

# Verify no errors
Select-String "Error" output\*.txt
```

---

*Compiler Design Laboratory — 3rd Year, 2nd Term*

# Compiler Pipeline Guide (How to Use)

## 📝 1. Creating a Code File
All programs written in the Linear language must have a .linear extension. The entry point of every program is defined by the START main { ... } END block.

**Example: my_code.linear**
\\\c
START main {
    int count = 5;
    string msg = "Hello from Linear!";
    MAHI_write(msg);
    
    for (int i = 1; i <= count; i = i + 1) {
        MAHI_write(i);
    }
} END
\\\

You can create this file using any text editor or via terminal:
\\\powershell
New-Item -Path "my_code.linear" -ItemType File -Value "START main { int x = 10; MAHI_write(x); } END"
\\\

## ⚙️ 2. Compiling the Pipeline
Before running your code, the language compiler needs to be built from the source files. A uild.bat script is provided for Windows environments.

To compile the entire language stack, open your PowerShell terminal and run:
\\\powershell
.\build.bat
\\\
*(This will generate compiler.exe using GCC, Flex, and Bison)*

## 🚀 3. Running Your Code
Once compiled, you can execute any valid .linear file by passing it to the generated compiler.exe.

**Command:**
\\\powershell
.\compiler.exe my_code.linear
\\\
**Expected Output:**
\\\	ext
Hello from Linear!
1
2
3
4
5
\\\

## 🛠 4. Common Errors to Watch Out For
1. **Semantic Errors**: Occur when calling arrays/structures that haven't been initialized, or trying to assign a string to an integer variable.
2. **Syntax Errors**: Usually caused by missing semicolons (;) or leaving out START main { or } END.  

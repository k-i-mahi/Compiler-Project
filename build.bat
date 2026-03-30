@echo off
set BISON_PKGDATADIR=C:\PROGRA~2\GnuWin32\share\bison
echo ==============================================
echo Building Linear Language Compiler
echo ==============================================

echo [1/3] Running Bison...
bison -d parser.y
if %errorlevel% neq 0 (
    echo Bison failed!
    exit /b %errorlevel%
)

echo [2/3] Running Flex...
flex lexer.l
if %errorlevel% neq 0 (
    echo Flex failed!
    exit /b %errorlevel%
)

echo [3/3] Compiling C code with GCC...
gcc parser.tab.c lex.yy.c symbol_table.c ast.c ds_runtime.c eval.c -o compiler.exe -lm
if %errorlevel% neq 0 (
    echo GCC Compile failed!
    exit /b %errorlevel%
)

echo.
echo Build Successful! 
echo You can now run the compiler: compiler.exe ^<input_file.linear^>

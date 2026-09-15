@echo off
:: Variables
set CC=gcc
set CFLAGS=-Wall -Wextra -g
set TARGET=logEditor
set SRC=TextEditor.c menu.c logs.c input.c structsHelp.c

:: Run Compilation
echo Compiling %TARGET%...
%CC% %CFLAGS% %SRC% -o %TARGET%

if %ERRORLEVEL% EQU 0 (
    echo Build successful!
) else (
    echo Build failed with error code %ERRORLEVEL%.
)

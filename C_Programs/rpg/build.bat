@echo off

:: Variables
set CC=gcc
set CFLAGS=-Wall -Wextra -g
set TARGET=rpg
set SRC=*.c jsonCFiles/*.c

if "%1" == "Build" goto build
if "%1" == "Clean" goto clean
if "%1" == "Rebuild" goto rebuild

:: Run Compilation
:build
echo Compiling %TARGET%...
%CC% %CFLAGS% %SRC% -o %TARGET%
exit /b

:clean
echo Cleaning %TARGET%...
del %TARGET%
exit /b

:rebuild
echo Rebuilding %TARGET%...
call :clean
call :build
exit /b
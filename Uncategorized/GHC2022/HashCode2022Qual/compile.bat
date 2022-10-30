@echo off
if "%1" == "" (
	echo "Usage: compile.bat source.cpp"
	exit
)
g++ -std=gnu++17 -Wall -Wno-unknown-pragmas -O3 -D_DEBUG "%1"
echo finished.

choice /m "test?"
if %errorlevel% equ 2 exit /b
start /b testAll.bat

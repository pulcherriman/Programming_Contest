@echo off
setlocal enabledelayedexpansion
cd %~dp0

for /l %%i in (10000,1,10049) do (
set p=%%i
set p=!p:~1,4!
@REM type .\tools\in\!p!.txt
..\..\a.exe < .\tools\in\!p!.txt > .\tools\out\!p!.txt
)
@echo off
setlocal enabledelayedexpansion
cd %~dp0

for /l %%i in (10000,1,10099) do (
set p=%%i
set p=!p:~1,4!
@REM type .\tools\in\!p!.txt
tester.exe a.exe < .\tools\in\!p!.txt > .\tools\out\!p!.txt
)
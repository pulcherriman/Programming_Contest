@echo off
setlocal enabledelayedexpansion
cd %~dp0

echo.>result.txt

for /l %%i in (10000,1,10199) do (
	set p=%%i
	set p=!p:~1,4!
	.\bin\tester.exe ..\..\a.exe < .\bin\in\!p!.txt > .\bin\out\!p!.txt 2>> .\result2.txt
)

set a=0
for /f "tokens=3" %%i in (.\result2.txt) do (
  set /a a+=%%i
)
echo %a%
echo %a% >> .\result2.txt
@echo off
setlocal enabledelayedexpansion
cd %~dp0

echo. > out/summary.txt
for /l %%i in (10000,1,10049) do (
	set p=%%i
	set p=!p:~1,4!
	set q=0
	for /f "usebackq tokens=*" %%a in (out/!p!.txt) do (
		if !q!==0 (
			echo %%a >> out/summary.txt
		)
		set q=1
	)
	set p=!p:~3,1!
)
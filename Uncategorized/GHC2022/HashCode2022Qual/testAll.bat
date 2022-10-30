@echo off
setlocal enabledelayedexpansion
cd %~dp0

set tm=%time: =0%;
set tm=%tm:~0,2%%tm:~3,2%%tm:~6,2%

pushd out
mkdir %tm%
popd

for %%i in (in/*.txt) do (
	set p=%%i
	set f=%tm%/!p:.in=.out!
	a.exe < in/%%i > out/!f!
)


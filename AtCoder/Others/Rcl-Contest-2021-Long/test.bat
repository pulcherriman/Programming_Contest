@echo off
setlocal enabledelayedexpansion
prompt $$$S
if "%1" == "" (
	echo ファイルを入力してください
	exit
)

pushd test_env

g++ -std=gnu++17 -Wall -Wno-unknown-pragmas -O2 %1
echo Compile Finished.

set batchsize=10
set current=0
set sum=0
set max=0
set min=100000000
for /l %%c in (1,1,100) do (
	for /l %%i in (1,1,%batchsize%) do (
		python tester/generator.py !random! > input.txt
		a.exe < input.txt > output.txt
		python tester/judge.py input.txt output.txt
		set score=!errorlevel!
		set /a sum+=!score!
		if !score! gtr !max! (
			set max=!score!
		)
		if !score! lss !min! (
			set min=!score!
		)
		set /a current+=1
	)
	set /a average=sum/!current!
	set /a expected=!average!/2
	cls
	echo   Case #: !current!
	echo  Average: !average!
	echo Expected: !expected!00
	echo      Max: !max!
	echo      Min: !min!
)
popd
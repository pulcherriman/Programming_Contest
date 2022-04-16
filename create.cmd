@echo off
setlocal enabledelayedexpansion
cd /d %~dp0

set dir[1]=AtCoder/ABC
set dir[2]=AtCoder/AGC
set dir[3]=AtCoder/AHC
set dir[4]=AtCoder/ARC
set dir[5]=AtCoder/Others
set dir[6]=Other directory

for /l %%i in (1,1,6) do echo %%i: !dir[%%i]!

choice /c 123456 /m "select directory"
if %errorlevel% equ 6 (
	set /p dir="enter directory path: "
) else (
	set dir=!dir[%errorlevel%]!
)

cd %dir%

set /p contestName="enter contest name: "
mkdir %contestName%
cd %contestName%

for %%i in (a b c d e f g h i j k l m n o p q r s t u v w x y z) do (
	call set contestName=%%contestName:%%i=%%i%%
)
call set contestName=%%contestName:-=_%%

set /p count="enter tasks count: "
set /a count-=1

set num2char=abcdefghijklmnopqrstuvwxyz
set initCodePath="C:\Users\tsumi\AppData\Local\Temp\dGVtcGxhdGU=.cpp.snippet"
set filePaths=
for /l %%i in (0,1,%count%) do (
	call set filePath="%contestName%_%%num2char:~%%i,1%%.cpp"
	call copy %initCodePath% %%filePath%%
	call set filePaths=%%filePaths%% %%filePath%%
)
code -a %filePaths%

exit
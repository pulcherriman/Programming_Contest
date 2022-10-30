# 9th Asprova Programming Contest

Please refer to the problem statement for the usage.


mapping from variables in the problem statement to
names in the source code:

I → itemN
N → operationN
J_i → procN
j → proc
M → resourceN
i → opNo
d_i → let
t_{i,j} → prodTime


///////////////////////////////////////////////////////////////////
Problem.h - defines class ProblemVar that contains variables appearing
            in the problem statement
Problem.cpp - I/O

gen.h - generator

judge.cpp - interaction between judge and contestant
judge.h defines a function reactive() that receives the contestants' output
as vector<string> input, and returns the result (score, V, D, RD, RO)
as a tuple.


///////////////////////////////////////////////////////////////////

ツールの使い方については問題文を参照してください。


問題文の変数名とプログラム上での変数名の対応:

I → itemN
N → operationN
J_i → procN
j → proc
M → resourceN
i → opNo
d_i → let
t_{i,j} → prodTime


///////////////////////////////////////////////////////////////////
Problem.h - 問題に出現する変数を class ProblemVar でまとめて管理
Problem.cpp - I/O

gen.h - 入力生成

judge.cpp - ジャッジとコンテスタント間のやりとりを行う
judge.h の関数 reactive() が稼動パターンを vector<string> input として受け取り、
結果として score, V, D, RD, RO を tuple として返します。


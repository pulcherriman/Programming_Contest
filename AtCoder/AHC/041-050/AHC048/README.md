- gdbデバッグ用のコマンドと動かし方
	```
	g++ -std=gnu++23 -Wall -Wno-unknown-pragmas -O2 -D_DEBUG -I../../lib -pg  main.cpp && gdb ./a.exe
	run < ../../in.txt
	```
- profiler実行
	```
	g++  -std=gnu++23 -Wall -Wno-unknown-pragmas -O2 -D_DEBUG -I../../lib -pg  main.cpp  && ./a.exe < ../../in.txt && gprof ./a.exe ./gmon.out > prof.txt 
	```

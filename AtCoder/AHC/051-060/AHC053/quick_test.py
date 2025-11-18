#!/usr/bin/env python3
# 5回実行による動作確認

import subprocess
import os

def main():
    print("=== 制約付き焼きなまし動作確認 ===")

    # コンパイル
    print("コンパイル中...")
    result = subprocess.run([
        'g++', '-std=gnu++23', '-fno-unroll-loops', '-Wall', '-Wno-unknown-pragmas',
        '-O2', '-D_DEBUG', '-I', r'C:\Users\tsumi\Desktop\Programming_Contest\lib',
        'main.cpp', '-o', 'main.exe'
    ], cwd=r'C:\Users\tsumi\Desktop\Programming_Contest\@private\AHC053',
    capture_output=True, text=True)

    if result.returncode != 0:
        print(f"コンパイルエラー: {result.stderr}")
        return

    print("コンパイル完了")

    # 5回実行してみる
    for i in range(5):
        print(f"\n=== 実行 {i+1}/5 ===")

        result = subprocess.run(
            ['echo', '500 50 998000000000000 1002000000000000'],
            shell=True,
            capture_output=True,
            text=True
        )
        input_data = result.stdout.strip()

        # main.exeを実行
        result = subprocess.run(
            ['./main.exe'],
            input=input_data,
            capture_output=True,
            text=True,
            cwd=r'C:\Users\tsumi\Desktop\Programming_Contest\@private\AHC053'
        )

        if result.returncode == 0:
            lines = result.stdout.strip().split('\n')
            print(f"全出力:")
            for i, line in enumerate(lines):
                print(f"  {i}: {line}")
            print()
        else:
            print(f"実行失敗: {result.stderr[:200]}")

if __name__ == "__main__":
    main()
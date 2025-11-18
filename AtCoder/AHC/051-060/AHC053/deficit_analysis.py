#!/usr/bin/env python3
# 10回実行によるB[i]-sum不足量分析スクリプト

import subprocess
import os
import statistics
from collections import defaultdict

def run_single_execution():
    """1回の実行を行い、結果を解析する"""
    try:
        # プログラム実行
        result = subprocess.run(
            ['echo', '500 50 998000000000000 1002000000000000'],
            shell=True,
            capture_output=True,
            text=True
        )

        if result.returncode != 0:
            return None

        input_data = result.stdout.strip()

        # main.exeを実行
        result = subprocess.run(
            ['./main.exe'],
            input=input_data,
            capture_output=True,
            text=True,
            cwd=r'C:\Users\tsumi\Desktop\Programming_Contest\@private\AHC053'
        )

        if result.returncode != 0:
            print(f"実行失敗: {result.stderr}")
            return None

        output_lines = result.stdout.strip().split('\n')
        if len(output_lines) < 2:
            print("出力行数不足")
            return None

        # A値とX値の抽出
        A_line = output_lines[0].strip().split()
        X_line = output_lines[1].strip().split()

        A = [int(x) for x in A_line]
        X = [int(x) for x in X_line]

        # B値（固定）
        B = [998058954691476, 998062179325428, 998148508707721, 998285976976074, 998351835498351,
             998479711871757, 998531737361836, 998639958839497, 998649984970544, 998682519402988,
             998714644947675, 998927530907961, 999037445746748, 999053442292096, 999065862502772,
             999083824925783, 999300946712789, 999416326842410, 999470655345332, 999511201564092,
             999584904930613, 999733180699583, 999800169022221, 999824602879851, 999901898078819,
             999909198157309, 1000113594410809, 1000134247761953, 1000261981388740, 1000359724494146,
             1000427823580033, 1000456844603287, 1000513933433386, 1000603144349968, 1000634389659772,
             1000669159921753, 1000767417567044, 1000814244701683, 1000898164990701, 1001035784679782,
             1001193279528182, 1001261142424287, 1001389591805148, 1001430765534724, 1001506010236612,
             1001677433222787, 1001687914384899, 1001937551585457, 1001941821349392, 1001942594092922]

        # 各山の合計を計算
        pile_sums = [0] * 50
        for i in range(len(X)):
            if X[i] > 0:
                pile_idx = X[i] - 1
                pile_sums[pile_idx] += A[i]

        # B[i] - sum[i] を計算（不足量）
        deficits = []
        for j in range(50):
            deficit = B[j] - pile_sums[j]
            deficits.append(deficit)

        return deficits

    except Exception as e:
        print(f"実行エラー: {e}")
        return None

def main():
    print("=== 10回実行によるB[i]-sum不足量分析 ===")

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

    # 10回実行
    all_deficits = []
    successful_runs = 0

    print("10回実行中...")
    for run_num in range(10):
        print(f"実行 {run_num + 1}/10")

        deficits = run_single_execution()
        if deficits is not None:
            all_deficits.append(deficits)
            successful_runs += 1
        else:
            print(f"実行 {run_num + 1} 失敗")

    print(f"成功実行回数: {successful_runs}/10")

    if successful_runs == 0:
        print("全実行が失敗しました")
        return

    # 統計分析
    print("\n=== 統計分析結果 ===")

    # 全体の不足量統計
    all_positive_deficits = []
    for deficits in all_deficits:
        for deficit in deficits:
            if deficit > 0:
                all_positive_deficits.append(deficit)

    if all_positive_deficits:
        print(f"全不足量統計:")
        print(f"  総不足回数: {len(all_positive_deficits)}")
        print(f"  最小不足量: {min(all_positive_deficits):,}")
        print(f"  最大不足量: {max(all_positive_deficits):,}")
        print(f"  平均不足量: {statistics.mean(all_positive_deficits):,.0f}")
        print(f"  中央値不足量: {statistics.median(all_positive_deficits):,.0f}")
        if len(all_positive_deficits) > 1:
            print(f"  標準偏差: {statistics.stdev(all_positive_deficits):,.0f}")

    # 不足量の範囲別分析
    deficit_ranges = [
        (1, 1000000),       # 100万以下
        (1000001, 10000000), # 1000万以下
        (10000001, 100000000), # 1億以下
        (100000001, 1000000000), # 10億以下
        (1000000001, 10000000000), # 100億以下
        (10000000001, float('inf')) # 100億超
    ]

    print(f"\n不足量分布:")
    for min_val, max_val in deficit_ranges:
        if max_val == float('inf'):
            count = sum(1 for d in all_positive_deficits if d >= min_val)
            range_str = f"{min_val:,}以上"
        else:
            count = sum(1 for d in all_positive_deficits if min_val <= d <= max_val)
            range_str = f"{min_val:,}-{max_val:,}"

        percentage = count / len(all_positive_deficits) * 100 if all_positive_deficits else 0
        print(f"  {range_str}: {count}回 ({percentage:.1f}%)")

    # 実行ごとの不足量統計
    print(f"\n実行ごとの不足量統計:")
    for run_idx in range(successful_runs):
        deficits = all_deficits[run_idx]
        positive_deficits = [d for d in deficits if d > 0]

        if positive_deficits:
            print(f"実行{run_idx+1}: 不足山数={len(positive_deficits)}, " +
                  f"平均不足量={statistics.mean(positive_deficits):,.0f}, " +
                  f"中央値={statistics.median(positive_deficits):,.0f}")

    # 小単位の推奨値を計算
    if all_positive_deficits:
        recommended_small_unit = statistics.median(all_positive_deficits)
        print(f"\n=== 小単位の推奨値 ===")
        print(f"推奨小単位値: {recommended_small_unit:,.0f}")
        print(f"（不足量の中央値に基づく）")

        # パーセンタイル分析
        percentiles = [10, 25, 50, 75, 90]
        print(f"\n不足量のパーセンタイル:")
        sorted_deficits = sorted(all_positive_deficits)
        for p in percentiles:
            idx = int(len(sorted_deficits) * p / 100)
            if idx >= len(sorted_deficits):
                idx = len(sorted_deficits) - 1
            value = sorted_deficits[idx]
            print(f"  {p}%ile: {value:,}")

    # 結果をファイルに保存
    with open('deficit_analysis_10runs.txt', 'w', encoding='utf-8') as f:
        f.write("=== 10回実行によるB[i]-sum不足量分析結果 ===\n")
        f.write(f"成功実行回数: {successful_runs}/10\n\n")

        if all_positive_deficits:
            f.write("全不足量統計:\n")
            f.write(f"  総不足回数: {len(all_positive_deficits)}\n")
            f.write(f"  最小不足量: {min(all_positive_deficits):,}\n")
            f.write(f"  最大不足量: {max(all_positive_deficits):,}\n")
            f.write(f"  平均不足量: {statistics.mean(all_positive_deficits):,.0f}\n")
            f.write(f"  中央値不足量: {statistics.median(all_positive_deficits):,.0f}\n")
            if len(all_positive_deficits) > 1:
                f.write(f"  標準偏差: {statistics.stdev(all_positive_deficits):,.0f}\n\n")

            f.write("不足量分布:\n")
            for min_val, max_val in deficit_ranges:
                if max_val == float('inf'):
                    count = sum(1 for d in all_positive_deficits if d >= min_val)
                    range_str = f"{min_val:,}以上"
                else:
                    count = sum(1 for d in all_positive_deficits if min_val <= d <= max_val)
                    range_str = f"{min_val:,}-{max_val:,}"

                percentage = count / len(all_positive_deficits) * 100 if all_positive_deficits else 0
                f.write(f"  {range_str}: {count}回 ({percentage:.1f}%)\n")

            f.write(f"\n推奨小単位値: {statistics.median(all_positive_deficits):,.0f}\n")

    print(f"\n詳細結果を 'deficit_analysis_10runs.txt' に保存しました。")

if __name__ == "__main__":
    main()
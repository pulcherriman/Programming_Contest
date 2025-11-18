#!/usr/bin/env python3
# 100回実行してB[i]-sumの値を集積する分析スクリプト

import subprocess
import os
import sys
from collections import defaultdict
import statistics

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
            print(f"Execution failed: {result.stderr}")
            return None

        output_lines = result.stdout.strip().split('\n')
        if len(output_lines) < 2:
            print("Insufficient output lines")
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

        # B[i] - sum[i] を計算
        deficits = []
        for j in range(50):
            deficit = B[j] - pile_sums[j]
            deficits.append(deficit)

        return deficits

    except Exception as e:
        print(f"Error in execution: {e}")
        return None

def main():
    print("=== 100回実行によるB[i]-sum分析 ===")

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

    # 100回実行
    all_deficits = []
    successful_runs = 0

    print("100回実行中...")
    for run_num in range(100):
        if (run_num + 1) % 10 == 0:
            print(f"実行回数: {run_num + 1}/100")

        deficits = run_single_execution()
        if deficits is not None:
            all_deficits.append(deficits)
            successful_runs += 1
        else:
            print(f"実行 {run_num + 1} 失敗")

    print(f"成功実行回数: {successful_runs}/100")

    if successful_runs == 0:
        print("全実行が失敗しました")
        return

    # 統計分析
    print("\n=== 統計分析結果 ===")

    # 各山ごとの不足量統計
    pile_stats = {}
    for pile_idx in range(50):
        pile_deficits = [deficits[pile_idx] for deficits in all_deficits if deficits[pile_idx] > 0]

        if pile_deficits:
            pile_stats[pile_idx] = {
                'count': len(pile_deficits),
                'min': min(pile_deficits),
                'max': max(pile_deficits),
                'mean': statistics.mean(pile_deficits),
                'median': statistics.median(pile_deficits),
                'stdev': statistics.stdev(pile_deficits) if len(pile_deficits) > 1 else 0
            }

    # 全体統計
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
        print(f"  標準偏差: {statistics.stdev(all_positive_deficits):,.0f}")

    # 不足量の分布分析
    deficit_ranges = [
        (1, 1000),
        (1001, 10000),
        (10001, 100000),
        (100001, 1000000),
        (1000001, 10000000),
        (10000001, 100000000),
        (100000001, 1000000000),
        (1000000001, 10000000000),
        (10000000001, float('inf'))
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

    # 結果をファイルに保存
    with open('deficit_analysis.txt', 'w', encoding='utf-8') as f:
        f.write("=== 100回実行によるB[i]-sum分析結果 ===\n")
        f.write(f"成功実行回数: {successful_runs}/100\n\n")

        if all_positive_deficits:
            f.write("全不足量統計:\n")
            f.write(f"  総不足回数: {len(all_positive_deficits)}\n")
            f.write(f"  最小不足量: {min(all_positive_deficits):,}\n")
            f.write(f"  最大不足量: {max(all_positive_deficits):,}\n")
            f.write(f"  平均不足量: {statistics.mean(all_positive_deficits):,.0f}\n")
            f.write(f"  中央値不足量: {statistics.median(all_positive_deficits):,.0f}\n")
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

        # 各山の詳細統計
        f.write(f"\n山別不足量統計（不足があった山のみ）:\n")
        f.write(f"{'Pile':>4} {'Count':>5} {'Min':>12} {'Max':>12} {'Mean':>12} {'Median':>12} {'StdDev':>12}\n")
        f.write("-" * 80 + "\n")

        for pile_idx in sorted(pile_stats.keys()):
            stats = pile_stats[pile_idx]
            f.write(f"{pile_idx+1:4d} {stats['count']:5d} {stats['min']:12,} {stats['max']:12,} "
                   f"{stats['mean']:12,.0f} {stats['median']:12,.0f} {stats['stdev']:12,.0f}\n")

    print(f"\n詳細結果を 'deficit_analysis.txt' に保存しました。")

    # 小単位の推奨値を計算
    if all_positive_deficits:
        recommended_small_unit = statistics.median(all_positive_deficits)
        print(f"\n=== 小単位の推奨値 ===")
        print(f"推奨小単位値: {recommended_small_unit:,.0f}")
        print(f"（不足量の中央値に基づく）")

        # より詳細な推奨値
        percentiles = [10, 25, 50, 75, 90]
        print(f"\n不足量のパーセンタイル:")
        for p in percentiles:
            value = sorted(all_positive_deficits)[int(len(all_positive_deficits) * p / 100)]
            print(f"  {p}%ile: {value:,}")

if __name__ == "__main__":
    main()
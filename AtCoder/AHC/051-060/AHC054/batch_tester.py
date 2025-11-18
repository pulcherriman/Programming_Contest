#!/usr/bin/env python3
import subprocess
import os
import concurrent.futures
import signal
import sys
import statistics
from tqdm import tqdm

# 設定
OUTPUTS_DIR = './batch_results/out'
SCORES_DIR = './batch_results/scores'
LOGS_DIR = './batch_results/log'
CASE = 1000
TL = 300.0
EXECUTABLE = './fast_interactive.exe'
TESTER_PATH = './tools/tester.exe'

running_processes = []
executor = None

def execute_case(seed):
    """単一のテストケースを実行してスコアを取得"""
    input_file_path = f'tools/in/{seed:04d}.txt'
    output_file_path = f'{OUTPUTS_DIR}/out_{seed:04d}.txt'
    score_file_path = f'{SCORES_DIR}/score_{seed:04d}.txt'
    log_file_path = f'{LOGS_DIR}/log_{seed:04d}.txt'

    # テスターでプログラムを実行してスコアを計算（一度に実行）
    with open(score_file_path, 'w') as fscore:
        proc = None
        try:
            proc = subprocess.Popen([TESTER_PATH, EXECUTABLE],
                                    stdin=open(input_file_path, 'r'),
                                    stdout=fscore,
                                    stderr=fscore)
            running_processes.append(proc)
            proc.wait(timeout=TL)
            if proc.returncode != 0:
                raise RuntimeError(f"Tester exited abnormally with code {proc.returncode}")
        except subprocess.TimeoutExpired as e:
            print(f"Seed {seed}: TimeoutExpired", flush=True)
            proc.terminate()
            raise e
        finally:
            if proc in running_processes:
                running_processes.remove(proc)

    # スコア結果を読み取り
    with open(score_file_path, 'r') as fscore:
        result = fscore.read().strip()

    if not result:
        raise RuntimeError(f"Score result is empty for seed {seed}")

    return seed, result

def getExecuteTime(log_file):
    """ログファイルから実行時間を取得"""
    try:
        with open(log_file, 'r') as f:
            lines = f.readlines()
            if lines:
                # 最後の行から実行時間を取得（形式: "XXX ms"）
                last_line = lines[-1].strip()
                if 'ms' in last_line:
                    return int(last_line.split()[0])
    except:
        pass
    return 0

def signal_handler(sig, frame):
    """シグナルハンドラ：Ctrl+Cで安全に終了"""
    print("\nInterrupted, terminating...")
    for proc in running_processes:
        proc.terminate()
    if executor:
        executor.shutdown(wait=False, cancel_futures=True)
    print("All processes and executor terminated. Exiting...")
    sys.exit(1)

def calculate_statistics(scores):
    """スコア統計を計算"""
    score_values = [s[0] for s in scores]

    stats = {
        'count': len(score_values),
        'sum': sum(score_values),
        'mean': statistics.mean(score_values),
        'median': statistics.median(score_values),
        'mode': statistics.mode(score_values) if len(set(score_values)) < len(score_values) else 'N/A',
        'min': min(score_values),
        'max': max(score_values),
        'range': max(score_values) - min(score_values),
        'stdev': statistics.stdev(score_values) if len(score_values) > 1 else 0,
        'variance': statistics.variance(score_values) if len(score_values) > 1 else 0
    }

    # パーセンタイル
    sorted_scores = sorted(score_values)
    n = len(sorted_scores)
    stats['p25'] = sorted_scores[n//4] if n > 3 else sorted_scores[0]
    stats['p75'] = sorted_scores[3*n//4] if n > 3 else sorted_scores[-1]
    stats['p90'] = sorted_scores[9*n//10] if n > 9 else sorted_scores[-1]
    stats['p95'] = sorted_scores[19*n//20] if n > 19 else sorted_scores[-1]

    return stats

def main():
    global executor
    signal.signal(signal.SIGINT, signal_handler)

    # 必要なディレクトリを作成
    os.makedirs(OUTPUTS_DIR, exist_ok=True)
    os.makedirs(SCORES_DIR, exist_ok=True)
    os.makedirs(LOGS_DIR, exist_ok=True)

    # 実行ファイルの存在確認
    if not os.path.exists(EXECUTABLE):
        print(f"Error: {EXECUTABLE} not found. Please compile first.")
        sys.exit(1)

    if not os.path.exists(TESTER_PATH):
        print(f"Error: {TESTER_PATH} not found.")
        sys.exit(1)

    print(f"Running {CASE} test cases with {EXECUTABLE}")
    print(f"Using tester: {TESTER_PATH}")

    scores = []

    # 並列実行（安全な制限）
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=max(os.cpu_count()-2, 2))
    futures = {executor.submit(execute_case, seed): seed for seed in range(CASE)}

    try:
        with tqdm(total=CASE, desc='Testing') as pbar:
            for future in concurrent.futures.as_completed(futures):
                seed = futures[future]
                try:
                    seed, score_result = future.result()
                    if score_result is None:
                        raise RuntimeError(f"Case {seed} returned None")

                    # スコア行を解析（例: "Score = 18"）
                    lines = score_result.split('\n')
                    score_line = [line for line in lines if 'Score' in line]
                    if score_line:
                        score_value = int(score_line[0].split('=')[-1].strip())
                        scores.append((score_value, f'{seed:04d}'))

                        # 現在の平均を表示
                        current_avg = sum(s[0] for s in scores) / len(scores)
                        tqdm.write(f"Current avg: {current_avg:.2f}")
                    else:
                        raise RuntimeError(f"Could not parse score from: {score_result}")

                except Exception as e:
                    print(f"Error in case {seed}: {e}", flush=True)
                    # エラーが発生した場合も続行（全体を止めない）
                pbar.update()
    except KeyboardInterrupt:
        print("\nKeyboardInterrupt detected, shutting down...")
        for proc in running_processes:
            proc.terminate()
        executor.shutdown(wait=False, cancel_futures=True)
        print("Shutdown complete. Exiting...")
        sys.exit(1)
    finally:
        executor.shutdown(wait=False)

    if not scores:
        print("No successful test cases!")
        sys.exit(1)

    # 統計計算
    stats = calculate_statistics(scores)

    # 結果出力
    print("\n" + "="*50)
    print("SCORE STATISTICS")
    print("="*50)
    print(f"Test cases:      {stats['count']}")
    print(f"Sum:             {stats['sum']}")
    print(f"Mean:            {stats['mean']:.2f}")
    print(f"Median:          {stats['median']}")
    print(f"Min:             {stats['min']}")
    print(f"Max:             {stats['max']}")
    print(f"Range:           {stats['range']}")
    print(f"Std Dev:         {stats['stdev']:.2f}")
    print(f"25th percentile: {stats['p25']}")
    print(f"75th percentile: {stats['p75']}")
    print(f"90th percentile: {stats['p90']}")
    print(f"95th percentile: {stats['p95']}")

    # ファイルに詳細結果を保存
    with open('./batch_summary.txt', 'w') as fout:
        fout.write("SCORE STATISTICS\n")
        fout.write("="*50 + "\n")
        fout.write(f"Test cases:      {stats['count']}\n")
        fout.write(f"Sum:             {stats['sum']}\n")
        fout.write(f"Mean:            {stats['mean']:.2f}\n")
        fout.write(f"Median:          {stats['median']}\n")
        fout.write(f"Min:             {stats['min']}\n")
        fout.write(f"Max:             {stats['max']}\n")
        fout.write(f"Range:           {stats['range']}\n")
        fout.write(f"Std Dev:         {stats['stdev']:.2f}\n")
        fout.write(f"Variance:        {stats['variance']:.2f}\n")
        fout.write(f"25th percentile: {stats['p25']}\n")
        fout.write(f"75th percentile: {stats['p75']}\n")
        fout.write(f"90th percentile: {stats['p90']}\n")
        fout.write(f"95th percentile: {stats['p95']}\n")
        fout.write("\nDETAILED RESULTS\n")
        fout.write("="*50 + "\n")
        fout.write("Seed\tScore\n")

        # ケース番号順でソート
        scores.sort(key=lambda x: x[1])
        for score, seed in scores:
            fout.write(f"{seed}\t{score}\n")

    # 実行時間の統計
    max_time = 0
    max_file = ""
    times = []
    for log_file in os.listdir(LOGS_DIR):
        log_path = os.path.join(LOGS_DIR, log_file)
        exec_time = getExecuteTime(log_path)
        times.append(exec_time)
        if exec_time > max_time:
            max_time = exec_time
            max_file = os.path.splitext(log_file)[0]

    if times:
        print(f"\nEXECUTION TIME STATISTICS")
        print("="*50)
        print(f"Max time:        {max_time}ms (Case: {max_file})")
        print(f"Avg time:        {statistics.mean(times):.1f}ms")
        print(f"Med time:        {statistics.median(times):.1f}ms")

    print(f"\nResults saved to: batch_summary.txt")

if __name__ == '__main__':
    main()
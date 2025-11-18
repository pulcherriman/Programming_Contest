#!/usr/bin/env python3
"""
全100ケースを実行してスコア下位20件を特定
"""

import subprocess
import json
import time
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor

def evaluate_single_case(case_num):
    """単一のテストケースを評価"""
    try:
        input_file = f"tools/in/{case_num:04d}.txt"
        if not Path(input_file).exists():
            return case_num, 0
            
        # ./lookahead.exe < input_file 2>/dev/null | tools/vis.exe input_file
        with open(input_file, 'r') as f:
            proc1 = subprocess.run('./lookahead.exe', stdin=f, stdout=subprocess.PIPE, 
                                 stderr=subprocess.DEVNULL, text=True, timeout=10)
        
        if proc1.returncode != 0:
            return case_num, 0
        
        proc2 = subprocess.run(['tools/vis.exe', input_file], input=proc1.stdout, 
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=5)
        
        if proc2.returncode != 0:
            return case_num, 0
            
        output = proc2.stdout.strip()
        if output.isdigit():
            return case_num, int(output)
        else:
            return case_num, 0
            
    except Exception as e:
        print(f"Case {case_num}: Error {e}")
        return case_num, 0

def main():
    print("Compiling lookahead.cpp with trial15 parameters...")
    compile_result = subprocess.run(['g++', '-std=c++23', '-O2', '-DONLINE_JUDGE', 
                                   '-o', 'lookahead.exe', 'lookahead.cpp'], 
                                  capture_output=True, text=True)
    
    if compile_result.returncode != 0:
        print(f"Compilation failed: {compile_result.stderr}")
        return
    
    print("Running all 100 test cases in parallel...")
    start_time = time.time()
    
    # 全100ケースを並列実行
    with ThreadPoolExecutor(max_workers=10) as executor:
        futures = [executor.submit(evaluate_single_case, i) for i in range(100)]
        results = [future.result() for future in futures]
    
    # 結果をソート
    results.sort(key=lambda x: x[0])  # case_numでソート
    
    # スコア情報を集計
    scores = [score for _, score in results]
    valid_scores = [score for score in scores if score > 0]
    
    print(f"\nExecution completed in {time.time() - start_time:.1f} seconds")
    print(f"Valid cases: {len(valid_scores)}/100")
    print(f"Average score: {sum(valid_scores)/len(valid_scores):.1f}")
    print(f"Min score: {min(valid_scores)}")
    print(f"Max score: {max(valid_scores)}")
    
    # スコア順でソート（昇順）
    score_sorted = [(case_num, score) for case_num, score in results if score > 0]
    score_sorted.sort(key=lambda x: x[1])
    
    # 下位20件を特定
    worst_20 = score_sorted[:20]
    print(f"\nWorst 20 cases:")
    for i, (case_num, score) in enumerate(worst_20):
        print(f"{i+1:2d}. Case {case_num:04d}: {score}")
    
    # 結果を保存
    result_data = {
        "timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
        "total_cases": len(results),
        "valid_cases": len(valid_scores),
        "average_score": sum(valid_scores)/len(valid_scores) if valid_scores else 0,
        "min_score": min(valid_scores) if valid_scores else 0,
        "max_score": max(valid_scores) if valid_scores else 0,
        "worst_20_cases": [case_num for case_num, _ in worst_20],
        "all_scores": {f"{case_num:04d}": score for case_num, score in results}
    }
    
    with open('all_scores_trial15.json', 'w') as f:
        json.dump(result_data, f, indent=2)
    
    print(f"\nResults saved to all_scores_trial15.json")
    print(f"Worst 20 cases: {[case_num for case_num, _ in worst_20]}")

if __name__ == "__main__":
    main()

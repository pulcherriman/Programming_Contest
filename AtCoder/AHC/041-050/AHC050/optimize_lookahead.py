#!/usr/bin/env python3
"""
Optuna optimization for lookahead.cpp hyperparameters
"""

import optuna
import subprocess
import json
import os
import tempfile
import re
from pathlib import Path
import time
from concurrent.futures import ThreadPoolExecutor
from typing import List, Tuple
from concurrent.futures import ThreadPoolExecutor, as_completed

class LookaheadOptimizer:
    def __init__(self, base_dir=".", test_cases_count=20):
        self.base_dir = Path(base_dir)
        self.test_cases_count = test_cases_count
        self.template_file = self.base_dir / "lookahead.cpp"
        
    def evaluate_single_case(self, case_num: int, temp_exe: str) -> Tuple[int, int]:
        """
        単一のテストケースを評価し、(case_num, score)のタプルを返す
        """
        test_input = self.base_dir / f"tools/in/{case_num:04d}.txt"
        if not test_input.exists():
            return case_num, 0
            
        try:
            with open(test_input, 'r') as f:
                input_data = f.read()
            
            # 実行（タイムアウト設定）
            proc = subprocess.run(
                [temp_exe], 
                input=input_data,
                capture_output=True, 
                text=True, 
                timeout=5.0,  # 5秒タイムアウト
                cwd=self.base_dir
            )
            
            if proc.returncode != 0:
                return case_num, 0
            
            # 出力を一時ファイルに保存
            with tempfile.NamedTemporaryFile(mode='w', suffix='.txt', delete=False) as out_f:
                out_f.write(proc.stdout)
                temp_output = out_f.name
            
            try:
                # スコア評価器を実行
                score_cmd = [
                    'tools/vis.exe',
                    str(test_input),
                    temp_output
                ]
                
                score_proc = subprocess.run(
                    score_cmd,
                    capture_output=True,
                    text=True,
                    timeout=3.0,
                    cwd=self.base_dir
                )
                
                if score_proc.returncode == 0:
                    # スコアを抽出（標準出力とエラー出力の両方をチェック）
                    score_output = score_proc.stdout.strip() + score_proc.stderr.strip()
                    score_match = re.search(r'Score = (\d+)', score_output)
                    if score_match:
                        score = int(score_match.group(1))
                        return case_num, score
                
                return case_num, 0
                
            finally:
                # 一時出力ファイルを削除
                try:
                    os.unlink(temp_output)
                except:
                    pass
                    
        except (subprocess.TimeoutExpired, Exception) as e:
            return case_num, 0
    
    def evaluate_cases_parallel(self, case_numbers: List[int], temp_exe: str, max_workers: int = 5) -> List[int]:
        """
        複数のテストケースを並列実行してスコアリストを返す
        """
        with ThreadPoolExecutor(max_workers=max_workers) as executor:
            # 全テストケースを並列実行
            futures = [executor.submit(self.evaluate_single_case, case_num, temp_exe) for case_num in case_numbers]
            
            # 結果を収集
            results = []
            for future in futures:
                case_num, score = future.result()
                results.append((case_num, score))
            
            # case_numでソート
            results.sort(key=lambda x: x[0])
            
            # スコアリストを返す
            scores = [score for _, score in results]
            for (case_num, score) in results:
                print(f"    Case {case_num}: {score}")
            
            return scores

    def create_parameterized_code(self, trial):
        """パラメータを調整したコードを生成"""
        
        # 最適化するハイパーパラメータ
        params = {
            # 確率閾値（極低確率の判定）
            'VERY_LOW_PROB_THRESHOLD': trial.suggest_float('VERY_LOW_PROB_THRESHOLD', 1e-10, 1e-6, log=True),
            
            # 近隣確率重み
            'NEIGHBOR_WEIGHT': trial.suggest_float('NEIGHBOR_WEIGHT', 0.005, 0.02),
            
            # 角ボーナス係数
            'CORNER_BONUS_BASE': trial.suggest_float('CORNER_BONUS_BASE', 0.01, 0.05),
            'CORNER_BONUS_EXTRA': trial.suggest_float('CORNER_BONUS_EXTRA', 0.01, 0.05),
            
            # 隣接空きマスペナルティ
            'ADJACENT_EMPTY_PENALTY': trial.suggest_float('ADJACENT_EMPTY_PENALTY', 0.005, 0.02),
            'ADJACENT_EMPTY_THRESHOLD': trial.suggest_int('ADJACENT_EMPTY_THRESHOLD', 2, 4),
            
            # 候補数制限
            'MAX_CANDIDATES_DEPTH0': trial.suggest_int('MAX_CANDIDATES_DEPTH0', 8, 15),
            'MAX_CANDIDATES_OTHERS': trial.suggest_int('MAX_CANDIDATES_OTHERS', 3, 8),
            'MAIN_MAX_CANDIDATES': trial.suggest_int('MAIN_MAX_CANDIDATES', 8, 20),
            
            # 先読み深度調整
            'DEPTH_THRESHOLD_HIGH': trial.suggest_int('DEPTH_THRESHOLD_HIGH', 120, 200),
            'DEPTH_THRESHOLD_LOW': trial.suggest_int('DEPTH_THRESHOLD_LOW', 15, 35),
            'MAX_DEPTH_SMALL': trial.suggest_int('MAX_DEPTH_SMALL', 2, 4),
        }
        
        # テンプレートファイルを読み込み
        with open(self.template_file, 'r', encoding='utf-8') as f:
            code = f.read()        # パラメータを置換
        replacements = [
            # 確率閾値
            (r'static const double VERY_LOW_PROB_THRESHOLD = 1e-8;', 
             f'static const double VERY_LOW_PROB_THRESHOLD = {params["VERY_LOW_PROB_THRESHOLD"]:.2e};'),
            
            # 近隣重み
            (r'static const double NEIGHBOR_WEIGHT = 0\.01;', 
             f'static const double NEIGHBOR_WEIGHT = {params["NEIGHBOR_WEIGHT"]:.6f};'),
            
            # 角ボーナス
            (r'static const double CORNER_BONUS_BASE = 0\.02;',
             f'static const double CORNER_BONUS_BASE = {params["CORNER_BONUS_BASE"]:.6f};'),
            (r'static const double CORNER_BONUS_EXTRA = 0\.03;',
             f'static const double CORNER_BONUS_EXTRA = {params["CORNER_BONUS_EXTRA"]:.6f};'),
            
            # 隣接空きマスペナルティとしきい値
            (r'static const double ADJACENT_EMPTY_PENALTY = 0\.01;',
             f'static const double ADJACENT_EMPTY_PENALTY = {params["ADJACENT_EMPTY_PENALTY"]:.6f};'),
            (r'static const int ADJACENT_EMPTY_THRESHOLD = 3;',
             f'static const int ADJACENT_EMPTY_THRESHOLD = {params["ADJACENT_EMPTY_THRESHOLD"]};'),
            
            # 候補数制限
            (r'static const int MAX_CANDIDATES_DEPTH0 = 10;',
             f'static const int MAX_CANDIDATES_DEPTH0 = {params["MAX_CANDIDATES_DEPTH0"]};'),
            (r'static const int MAX_CANDIDATES_OTHERS = 5;',
             f'static const int MAX_CANDIDATES_OTHERS = {params["MAX_CANDIDATES_OTHERS"]};'),
            (r'static const int MAIN_MAX_CANDIDATES = 12;',
             f'static const int MAIN_MAX_CANDIDATES = {params["MAIN_MAX_CANDIDATES"]};'),
            
            # 先読み深度調整
            (r'static const int DEPTH_THRESHOLD_HIGH = 150;',
             f'static const int DEPTH_THRESHOLD_HIGH = {params["DEPTH_THRESHOLD_HIGH"]};'),
            (r'static const int DEPTH_THRESHOLD_LOW = 20;',
             f'static const int DEPTH_THRESHOLD_LOW = {params["DEPTH_THRESHOLD_LOW"]};'),
            (r'static const int MAX_DEPTH_SMALL = 3;',
             f'static const int MAX_DEPTH_SMALL = {params["MAX_DEPTH_SMALL"]};'),
        ]
        
        for pattern, replacement in replacements:
            code = re.sub(pattern, replacement, code)
        
        return code, params
    
    def evaluate_parameters(self, trial):
        """パラメータの組み合わせを評価"""
        try:            # パラメータ化されたコードを生成
            parameterized_code, params = self.create_parameterized_code(trial)
            
            # 一時ファイルに保存
            with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False, encoding='utf-8') as f:
                f.write(parameterized_code)
                temp_cpp = f.name
            
            try:
                # コンパイル
                temp_exe = temp_cpp.replace('.cpp', '.exe')
                compile_cmd = [
                    'g++', '-std=c++23', '-O2', '-DONLINE_JUDGE',
                    '-o', temp_exe, temp_cpp
                ]
                
                result = subprocess.run(compile_cmd, capture_output=True, text=True, cwd=self.base_dir)                if result.returncode != 0:
                    print(f"Compile error: {result.stderr}")
                    return 0.0
                
                print(f"Trial {trial.number}: Compilation successful")
                
                # 新しい低スコアテストケースで並列実行
                bad_score_cases = [70, 71, 52, 23, 92]  # 新しい低スコアケース (0070, 0071, 0052, 0023, 0092)
                scores = self.evaluate_cases_parallel(bad_score_cases, temp_exe, max_workers=5)
                
                # 平均スコアを返す
                if scores:
                    avg_score = sum(scores) / len(scores)
                    print(f"Trial {trial.number}: {len(scores)} cases, avg_score: {avg_score:.0f}")
                    trial.set_user_attr('test_count', len(scores))
                    trial.set_user_attr('scores', scores)
                    return avg_score
                else:
                    return 0.0
                    
            finally:
                # 一時ファイルを削除
                try:
                    os.unlink(temp_cpp)
                    if os.path.exists(temp_exe):
                        os.unlink(temp_exe)
                except:
                    pass
                    
        except Exception as e:
            print(f"Error in trial {trial.number}: {e}")
            return 0.0

def main():
    # 最適化器を初期化
    optimizer = LookaheadOptimizer(".")
    
    # Optunaの設定
    study = optuna.create_study(
        direction='maximize',
        study_name='lookahead_optimization',
        storage='sqlite:///lookahead_optuna.db',
        load_if_exists=True    )
    
    print("Starting optimization...")
    if len(study.trials) > 0:
        print(f"Current best: {study.best_value:.0f}")
    else:
        print("Current best: None (no trials yet)")
      # 最適化実行
    study.optimize(
        optimizer.evaluate_parameters,
        n_trials=20,  # 試行回数を増やす
        timeout=1800,  # 30分タイムアウト
    )
    
    # 結果表示
    print("\nOptimization completed!")
    print(f"Best score: {study.best_value:.0f}")
    print("Best parameters:")
    for key, value in study.best_params.items():
        print(f"  {key}: {value}")
    
    # 最適パラメータでコードを生成
    best_trial = study.best_trial
    optimizer_temp = LookaheadOptimizer(".")
    best_code, best_params = optimizer_temp.create_parameterized_code(best_trial)
    
    # 最適化されたコードを保存
    with open('lookahead_optimized.cpp', 'w', encoding='utf-8') as f:
        f.write(best_code)
    
    print(f"\nOptimized code saved to lookahead_optimized.cpp")
    
    # パラメータをJSONで保存
    with open('best_parameters.json', 'w') as f:
        json.dump(best_params, f, indent=2)
    
    print("Best parameters saved to best_parameters.json")

if __name__ == "__main__":
    main()

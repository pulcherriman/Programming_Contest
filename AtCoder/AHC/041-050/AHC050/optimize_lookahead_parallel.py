#!/usr/bin/env python3
"""
Optuna optimization for lookahead.cpp hyperparameters with parallel execution
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

class LookaheadOptimizer:
    def __init__(self, base_dir=".", test_cases_count=20):
        self.base_dir = Path(base_dir)
        self.lookahead_cpp = self.base_dir / "lookahead.cpp"
        self.test_cases_count = test_cases_count
    
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
        """パラメータ化されたC++コードを生成"""        # Trial 24の最良パラメータを基準に、さらに狭い範囲で最適化
        best_params = {
            'VERY_LOW_PROB_THRESHOLD': 1.0460790504304567e-06,
            'NEIGHBOR_WEIGHT': 0.023506040280611193,
            'CORNER_BONUS_BASE': 0.04369608389013945,
            'CORNER_BONUS_EXTRA': 0.03690727527166102,
            'ADJACENT_EMPTY_PENALTY': 0.03986040145077578,
            'ADJACENT_EMPTY_THRESHOLD': 3,
            'MAX_CANDIDATES_DEPTH0': 20,
            'MAX_CANDIDATES_OTHERS': 8,
            'MAIN_MAX_CANDIDATES': 9,
            'DEPTH_THRESHOLD_HIGH': 203,
            'DEPTH_THRESHOLD_MID': 119,
            'DEPTH_THRESHOLD_LOW': 14,
            'MAX_DEPTH_SMALL': 4,
        }
        
        params = {
            # 確率閾値（±30%の範囲、対数スケール）
            'VERY_LOW_PROB_THRESHOLD': trial.suggest_float('VERY_LOW_PROB_THRESHOLD', 
                                                          best_params['VERY_LOW_PROB_THRESHOLD'] * 0.7, 
                                                          best_params['VERY_LOW_PROB_THRESHOLD'] * 1.3, log=True),
            
            # 重み・ボーナス系（±15%の範囲）
            'NEIGHBOR_WEIGHT': trial.suggest_float('NEIGHBOR_WEIGHT', 
                                                  best_params['NEIGHBOR_WEIGHT'] * 0.85, 
                                                  best_params['NEIGHBOR_WEIGHT'] * 1.15),
            'CORNER_BONUS_BASE': trial.suggest_float('CORNER_BONUS_BASE', 
                                                    best_params['CORNER_BONUS_BASE'] * 0.85, 
                                                    best_params['CORNER_BONUS_BASE'] * 1.15),
            'CORNER_BONUS_EXTRA': trial.suggest_float('CORNER_BONUS_EXTRA', 
                                                     best_params['CORNER_BONUS_EXTRA'] * 0.85, 
                                                     best_params['CORNER_BONUS_EXTRA'] * 1.15),
            'ADJACENT_EMPTY_PENALTY': trial.suggest_float('ADJACENT_EMPTY_PENALTY', 
                                                         best_params['ADJACENT_EMPTY_PENALTY'] * 0.85, 
                                                         best_params['ADJACENT_EMPTY_PENALTY'] * 1.15),
            'ADJACENT_EMPTY_THRESHOLD': trial.suggest_int('ADJACENT_EMPTY_THRESHOLD', 3, 3),  # 3で固定
            
            # 候補数制限（±2程度の範囲）
            'MAX_CANDIDATES_DEPTH0': trial.suggest_int('MAX_CANDIDATES_DEPTH0', 18, 22),  # 20±2
            'MAX_CANDIDATES_OTHERS': trial.suggest_int('MAX_CANDIDATES_OTHERS', 7, 9),    # 8±1
            'MAIN_MAX_CANDIDATES': trial.suggest_int('MAIN_MAX_CANDIDATES', 8, 10),       # 9±1
            
            # 深度調整（±15%程度の範囲）
            'DEPTH_THRESHOLD_HIGH': trial.suggest_int('DEPTH_THRESHOLD_HIGH', 173, 233),  # 203±30
            'DEPTH_THRESHOLD_MID': trial.suggest_int('DEPTH_THRESHOLD_MID', 101, 137),    # 119±18
            'DEPTH_THRESHOLD_LOW': trial.suggest_int('DEPTH_THRESHOLD_LOW', 12, 16),      # 14±2
            'MAX_DEPTH_SMALL': trial.suggest_int('MAX_DEPTH_SMALL', 4, 4),                # 4で固定
        }
        
        # lookahead.cppを読み込み
        with open(self.lookahead_cpp, 'r', encoding='utf-8') as f:
            code = f.read()          # パラメータ置換（Trial 24の最良パラメータ値に合わせる）
        replacements = [
            # 確率閾値 - Trial 24の値に合わせる
            (r'static const double VERY_LOW_PROB_THRESHOLD = 1\.0460790504304567e-06;',
             f'static const double VERY_LOW_PROB_THRESHOLD = {params["VERY_LOW_PROB_THRESHOLD"]:.3e};'),
            
            # 近隣重み - Trial 24の値に合わせる
            (r'static const double NEIGHBOR_WEIGHT = 0\.023506040280611193;',
             f'static const double NEIGHBOR_WEIGHT = {params["NEIGHBOR_WEIGHT"]:.6f};'),
            
            # 角ボーナス - Trial 24の値に合わせる
            (r'static const double CORNER_BONUS_BASE = 0\.04369608389013945;',
             f'static const double CORNER_BONUS_BASE = {params["CORNER_BONUS_BASE"]:.6f};'),
            (r'static const double CORNER_BONUS_EXTRA = 0\.03690727527166102;',
             f'static const double CORNER_BONUS_EXTRA = {params["CORNER_BONUS_EXTRA"]:.6f};'),
            
            # 隣接空きマスペナルティ - Trial 24の値に合わせる
            (r'static const double ADJACENT_EMPTY_PENALTY = 0\.03986040145077578;',
             f'static const double ADJACENT_EMPTY_PENALTY = {params["ADJACENT_EMPTY_PENALTY"]:.6f};'),
            (r'static const int ADJACENT_EMPTY_THRESHOLD = 3;',
             f'static const int ADJACENT_EMPTY_THRESHOLD = {params["ADJACENT_EMPTY_THRESHOLD"]};'),
            
            # 候補数制限 - Trial 24の値に合わせる
            (r'static const int MAX_CANDIDATES_DEPTH0 = 20;',
             f'static const int MAX_CANDIDATES_DEPTH0 = {params["MAX_CANDIDATES_DEPTH0"]};'),
            (r'static const int MAX_CANDIDATES_OTHERS = 8;',
             f'static const int MAX_CANDIDATES_OTHERS = {params["MAX_CANDIDATES_OTHERS"]};'),
            (r'static const int MAIN_MAX_CANDIDATES = 9;',
             f'static const int MAIN_MAX_CANDIDATES = {params["MAIN_MAX_CANDIDATES"]};'),
              
            # 先読み深度調整 - Trial 24の値に合わせる
            (r'static const int DEPTH_THRESHOLD_HIGH = 203;',
             f'static const int DEPTH_THRESHOLD_HIGH = {params["DEPTH_THRESHOLD_HIGH"]};'),
            (r'static const int DEPTH_THRESHOLD_MID = 119;',
             f'static const int DEPTH_THRESHOLD_MID = {params["DEPTH_THRESHOLD_MID"]};'),
            (r'static const int DEPTH_THRESHOLD_LOW = 14;',
             f'static const int DEPTH_THRESHOLD_LOW = {params["DEPTH_THRESHOLD_LOW"]};'),
            (r'static const int MAX_DEPTH_SMALL = 4;',
             f'static const int MAX_DEPTH_SMALL = {params["MAX_DEPTH_SMALL"]};'),
        ]
        
        for pattern, replacement in replacements:
            code = re.sub(pattern, replacement, code)
        
        return code, params
    
    def evaluate_parameters(self, trial):
        """パラメータの組み合わせを評価"""
        try:
            # パラメータ化されたコードを生成
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
                
                result = subprocess.run(compile_cmd, capture_output=True, text=True, cwd=self.base_dir)
                if result.returncode != 0:
                    print(f"Compile error: {result.stderr}")
                    return 0.0
                print(f"Trial {trial.number}: Compilation successful")                # 全100件のテストケースで並列実行
                all_cases = list(range(100))  # 0から99までの全ケース
                scores = self.evaluate_cases_parallel(all_cases, temp_exe, max_workers=10)  # 並列度を上げる
                
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
            print(f"Evaluation error: {e}")
            return 0.0

def main():
    # 最適化対象のディレクトリに移動
    optimizer = LookaheadOptimizer(base_dir=".")    # Optuna StudyをSQLiteでローカル保存（さらに狭い範囲の最適化用の新しいDB）
    study_name = "lookahead_optimization_all100_narrow2"
    storage_url = f"sqlite:///{study_name}.db"
    study = optuna.create_study(
        direction="maximize",
        study_name=study_name,
        storage=storage_url,
        load_if_exists=False,  # 新しいDBを作成
        sampler=optuna.samplers.TPESampler(n_startup_trials=15)
    )    # 全100ケースに対するさらに狭い範囲の最適化を実行
    print("Starting very narrow-range optimization for all 100 cases:")
    print("Cases: 0-99 (all test cases)")
    print("Parameter ranges: ±15% around Trial 24 best parameters")
    print("Using parallel execution for faster evaluation...")
    
    try:
        study.optimize(optimizer.evaluate_parameters, n_trials=25, timeout=5400)  # 1.5時間で25試行（さらに狭い範囲最適化）
        
        # 最良パラメータを表示・保存
        best_trial = study.best_trial
        print(f"\nBest trial: {best_trial.number}")
        print(f"Best value: {best_trial.value:.1f}")
        print("Best params:")
        for key, value in best_trial.params.items():
            print(f"  {key}: {value}")        # ベストパラメータを保存
        best_params_file = f"best_params_all100_narrow2_trial{best_trial.number}.json"
        with open(best_params_file, 'w') as f:
            json.dump({
                'trial_number': best_trial.number,
                'value': best_trial.value,
                'params': best_trial.params,
                'user_attrs': best_trial.user_attrs
            }, f, indent=2)
        print(f"\nBest parameters saved to {best_params_file}")
        
        # study統計を表示
        print(f"\nCompleted trials: {len(study.trials)}")
        print(f"Best value: {study.best_value}")
        
    except KeyboardInterrupt:
        print("\nOptimization interrupted by user.")
        if study.trials:
            best_trial = study.best_trial
            print(f"Current best: Trial {best_trial.number}, Value: {best_trial.value:.1f}")

if __name__ == "__main__":
    main()

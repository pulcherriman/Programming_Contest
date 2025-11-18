#!/usr/bin/env python3
"""
Simple hyperparameter optimization for lookahead.cpp
Optunaを使わずに、グリッドサーチやランダムサーチで最適化
"""

import subprocess
import random
import json
import re
import time
from pathlib import Path
import tempfile
import os

class SimpleOptimizer:
    def __init__(self, base_dir=".", test_cases=5):
        self.base_dir = Path(base_dir)
        self.test_cases = test_cases
        self.best_score = 0
        self.best_params = None
        
    def generate_params(self, method="random"):
        """パラメータを生成"""
        if method == "random":
            return {
                'VERY_LOW_PROB_THRESHOLD': random.uniform(1e-10, 1e-6),
                'NEIGHBOR_WEIGHT': random.uniform(0.005, 0.02),
                'CORNER_BONUS_BASE': random.uniform(0.01, 0.05),
                'CORNER_BONUS_EXTRA': random.uniform(0.01, 0.05),
                'ADJACENT_EMPTY_PENALTY': random.uniform(0.005, 0.02),
                'ADJACENT_EMPTY_THRESHOLD': random.randint(2, 4),
                'MAX_CANDIDATES_DEPTH0': random.randint(8, 15),
                'MAX_CANDIDATES_OTHERS': random.randint(3, 8),
                'MAIN_MAX_CANDIDATES': random.randint(8, 20),
                'DEPTH_THRESHOLD_HIGH': random.randint(120, 200),
                'DEPTH_THRESHOLD_MID': random.randint(60, 120),
                'DEPTH_THRESHOLD_LOW': random.randint(15, 35),
                'MAX_DEPTH_SMALL': random.randint(2, 4),
            }
        elif method == "baseline":
            # 現在の設定
            return {
                'VERY_LOW_PROB_THRESHOLD': 1e-8,
                'NEIGHBOR_WEIGHT': 0.01,
                'CORNER_BONUS_BASE': 0.02,
                'CORNER_BONUS_EXTRA': 0.03,
                'ADJACENT_EMPTY_PENALTY': 0.01,
                'ADJACENT_EMPTY_THRESHOLD': 3,
                'MAX_CANDIDATES_DEPTH0': 10,
                'MAX_CANDIDATES_OTHERS': 5,
                'MAIN_MAX_CANDIDATES': 12,
                'DEPTH_THRESHOLD_HIGH': 150,
                'DEPTH_THRESHOLD_MID': 80,
                'DEPTH_THRESHOLD_LOW': 20,
                'MAX_DEPTH_SMALL': 3,
            }
    
    def create_modified_code(self, params):
        """パラメータを適用したコードを生成"""
        with open(self.base_dir / "lookahead.cpp", 'r', encoding='utf-8') as f:
            code = f.read()
        
        # ハイパーパラメータ部分を置換
        param_section = f"""// ハイパーパラメータ設定
namespace HyperParams {{
	// 確率閾値
	static const double VERY_LOW_PROB_THRESHOLD = {params['VERY_LOW_PROB_THRESHOLD']:.2e};
	
	// 評価関数の重み
	static const double NEIGHBOR_WEIGHT = {params['NEIGHBOR_WEIGHT']:.6f};
	static const double CORNER_BONUS_BASE = {params['CORNER_BONUS_BASE']:.6f};
	static const double CORNER_BONUS_EXTRA = {params['CORNER_BONUS_EXTRA']:.6f};
	static const double ADJACENT_EMPTY_PENALTY = {params['ADJACENT_EMPTY_PENALTY']:.6f};
	static const int ADJACENT_EMPTY_THRESHOLD = {params['ADJACENT_EMPTY_THRESHOLD']};
	
	// 先読み候補数制限
	static const int MAX_CANDIDATES_DEPTH0 = {params['MAX_CANDIDATES_DEPTH0']};
	static const int MAX_CANDIDATES_OTHERS = {params['MAX_CANDIDATES_OTHERS']};
	static const int MAIN_MAX_CANDIDATES = {params['MAIN_MAX_CANDIDATES']};
	
	// 先読み深度調整
	static const int DEPTH_THRESHOLD_HIGH = {params['DEPTH_THRESHOLD_HIGH']};
	static const int DEPTH_THRESHOLD_MID = {params['DEPTH_THRESHOLD_MID']};
	static const int DEPTH_THRESHOLD_LOW = {params['DEPTH_THRESHOLD_LOW']};
	static const int MAX_DEPTH_SMALL = {params['MAX_DEPTH_SMALL']};
}}"""
        
        # 既存のHyperParams名前空間を置換
        pattern = r'// ハイパーパラメータ設定\nnamespace HyperParams \{[^}]+\}'
        code = re.sub(pattern, param_section, code, flags=re.DOTALL)
        
        return code
    
    def evaluate_params(self, params, trial_id):
        """パラメータの評価"""
        try:
            # コードを生成
            modified_code = self.create_modified_code(params)
            
            # 一時ファイルに保存
            with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False, encoding='utf-8') as f:
                f.write(modified_code)
                temp_cpp = f.name
            
            try:
                # コンパイル
                temp_exe = temp_cpp.replace('.cpp', '.exe')
                compile_cmd = ['g++', '-std=c++17', '-O2', '-o', temp_exe, temp_cpp]
                
                result = subprocess.run(compile_cmd, capture_output=True, text=True, cwd=self.base_dir)
                if result.returncode != 0:
                    print(f"Trial {trial_id}: Compile error")
                    return 0.0
                
                # テスト実行
                scores = []
                for i in range(self.test_cases):
                    test_input = self.base_dir / f"tools/in/{i:04d}.txt"
                    if not test_input.exists():
                        break
                    
                    try:
                        with open(test_input, 'r') as f:
                            input_data = f.read()
                        
                        # プログラム実行
                        proc = subprocess.run(
                            [temp_exe],
                            input=input_data,
                            capture_output=True,
                            text=True,
                            timeout=8.0,  # タイムアウト
                            cwd=self.base_dir
                        )
                        
                        if proc.returncode == 0:
                            # スコア評価（簡易版）
                            output_lines = proc.stdout.strip().split('\n')
                            if len(output_lines) >= 1:
                                # デバッグ出力からスコアを抽出
                                debug_output = proc.stderr
                                score_match = re.search(r'Final Score: (\d+)', debug_output)
                                if score_match:
                                    score = int(score_match.group(1))
                                    scores.append(score)
                    
                    except subprocess.TimeoutExpired:
                        print(f"Trial {trial_id}: Case {i} timeout")
                        break
                    except Exception as e:
                        print(f"Trial {trial_id}: Case {i} error: {e}")
                        break
                
                # 平均スコア
                if scores:
                    avg_score = sum(scores) / len(scores)
                    print(f"Trial {trial_id}: {len(scores)} cases, avg_score: {avg_score:.0f}")
                    return avg_score
                else:
                    return 0.0
                    
            finally:
                # 一時ファイル削除
                try:
                    os.unlink(temp_cpp)
                    if os.path.exists(temp_exe):
                        os.unlink(temp_exe)
                except:
                    pass
                    
        except Exception as e:
            print(f"Trial {trial_id}: Error {e}")
            return 0.0
    
    def optimize(self, trials=50):
        """最適化実行"""
        print("Starting optimization...")
        
        # ベースライン評価
        print("Evaluating baseline...")
        baseline_params = self.generate_params("baseline")
        baseline_score = self.evaluate_params(baseline_params, "baseline")
        print(f"Baseline score: {baseline_score:.0f}")
        
        self.best_score = baseline_score
        self.best_params = baseline_params
        
        # ランダム試行
        for trial in range(trials):
            print(f"\nTrial {trial + 1}/{trials}")
            params = self.generate_params("random")
            score = self.evaluate_params(params, trial + 1)
            
            if score > self.best_score:
                self.best_score = score
                self.best_params = params
                print(f"New best score: {score:.0f}")
                
                # 最良パラメータを保存
                with open('best_params_so_far.json', 'w') as f:
                    json.dump(self.best_params, f, indent=2)
        
        print(f"\nOptimization completed!")
        print(f"Best score: {self.best_score:.0f}")
        print("Best parameters:")
        for key, value in self.best_params.items():
            print(f"  {key}: {value}")
        
        # 最適化されたコードを生成
        optimized_code = self.create_modified_code(self.best_params)
        with open('lookahead_optimized.cpp', 'w', encoding='utf-8') as f:
            f.write(optimized_code)
        
        # パラメータを保存
        with open('best_parameters.json', 'w') as f:
            json.dump(self.best_params, f, indent=2)
        
        print("Optimized code saved to lookahead_optimized.cpp")
        print("Best parameters saved to best_parameters.json")

def main():
    optimizer = SimpleOptimizer(test_cases=5)  # 最初は少ないケース数でテスト
    optimizer.optimize(trials=30)  # 30回試行

if __name__ == "__main__":
    main()

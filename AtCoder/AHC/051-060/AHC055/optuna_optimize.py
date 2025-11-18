#!/usr/bin/env python3
"""
AHC055 ビームサーチパラメータ最適化（Optuna使用）
"""

import optuna
import subprocess
import tempfile
import os
import numpy as np
from pathlib import Path

def modify_beam_params(template_file, params, output_file):
    """ビームサーチパラメータを変更してC++ファイルを生成"""
    with open(template_file, 'r', encoding='utf-8') as f:
        content = f.read()

    # パラメータを置換
    replacements = {
        'int beam_width = 20;': f'int beam_width = {params["beam_width"]};',
        'int max_depth = 15;': f'int max_depth = {params["max_depth"]};',
        'int expand_count = 5;': f'int expand_count = {params["expand_count"]};',
        'double weapon_coeff = 1.0;': f'double weapon_coeff = {params["weapon_coeff"]};',
        'double progress_coeff = 4.5;': f'double progress_coeff = {params["progress_coeff"]};',
        'double cost_coeff = 1.0;': f'double cost_coeff = {params["cost_coeff"]};',
        'double completion_bonus = 50000.0;': f'double completion_bonus = {params["completion_bonus"]};',
        'double early_bonus = (8.0 - cost) * 0.5;': f'double early_bonus = (8.0 - cost) * {params["early_bonus_coeff"]};',
        'double durability_bonus = input.C[i] * 0.3;': f'double durability_bonus = input.C[i] * {params["durability_bonus_coeff"]};',
    }

    for old, new in replacements.items():
        content = content.replace(old, new)

    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(content)

def evaluate_params(params, num_cases=20):
    """パラメータを評価（限定的なケース数でスピードアップ）"""
    try:
        # 一時ファイルでパラメータ調整版を作成
        with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as temp_cpp:
            modify_beam_params('main_beam_tuned.cpp', params, temp_cpp.name)
            temp_cpp_path = temp_cpp.name

        # コンパイル
        exe_path = temp_cpp_path.replace('.cpp', '.exe')
        compile_cmd = [
            'g++', '-std=gnu++23', '-O2', temp_cpp_path, '-o', exe_path
        ]

        result = subprocess.run(compile_cmd, capture_output=True, text=True, timeout=30)
        if result.returncode != 0:
            print(f"Compile error: {result.stderr}")
            return float('inf')  # コンパイルエラーは最悪スコア

        # テスト実行（限定ケース）
        scores = []
        for i in range(min(num_cases, 100)):
            input_file = f"tools/in/{i:04d}.txt"
            if not os.path.exists(input_file):
                continue

            with open(input_file, 'r') as f:
                input_data = f.read()

            # 実行
            run_result = subprocess.run(
                [exe_path],
                input=input_data,
                capture_output=True,
                text=True,
                timeout=10
            )

            if run_result.returncode != 0:
                continue

            # スコア計算
            attacks = run_result.stdout.strip().split('\n')
            if attacks and attacks[0]:
                score = len(attacks)

                # 硬さの合計を推定（簡易）
                lines = input_data.strip().split('\n')
                if len(lines) >= 2:
                    N = int(lines[0])
                    H = list(map(int, lines[1].split()))
                    total_h = sum(H)
                    final_score = total_h - score + 1
                    scores.append(final_score)

        # クリーンアップ
        try:
            os.unlink(temp_cpp_path)
            os.unlink(exe_path)
        except:
            pass

        if not scores:
            return float('inf')

        return -np.mean(scores)  # Optunaは最小化なので負の値

    except Exception as e:
        print(f"Error in evaluation: {e}")
        return float('inf')

def objective(trial):
    """Optuna目的関数"""
    params = {
        'beam_width': trial.suggest_int('beam_width', 10, 50),
        'max_depth': trial.suggest_int('max_depth', 10, 25),
        'expand_count': trial.suggest_int('expand_count', 3, 10),
        'weapon_coeff': trial.suggest_float('weapon_coeff', 0.5, 2.0),
        'progress_coeff': trial.suggest_float('progress_coeff', 2.0, 8.0),
        'cost_coeff': trial.suggest_float('cost_coeff', 0.5, 2.0),
        'completion_bonus': trial.suggest_float('completion_bonus', 20000, 100000),
        'early_bonus_coeff': trial.suggest_float('early_bonus_coeff', 0.1, 1.0),
        'durability_bonus_coeff': trial.suggest_float('durability_bonus_coeff', 0.1, 1.0),
    }

    score = evaluate_params(params, num_cases=20)  # 20ケースで高速評価
    return score

def main():
    """メイン最適化実行"""
    print("AHC055 ビームサーチパラメータ最適化開始")

    # テストケースディレクトリ確認
    if not os.path.exists('tools/in'):
        print("Error: tools/in directory not found")
        return

    # Optuna study作成
    study = optuna.create_study(
        direction='minimize',
        sampler=optuna.samplers.TPESampler(seed=42)
    )

    # 最適化実行
    try:
        study.optimize(objective, n_trials=100, timeout=3600)  # 1時間制限

        print("=== 最適化結果 ===")
        print(f"Best score: {-study.best_value}")
        print("Best params:")
        for key, value in study.best_params.items():
            print(f"  {key}: {value}")

        # 最適パラメータでファイル生成
        modify_beam_params(
            'main_beam_tuned.cpp',
            study.best_params,
            'main_beam_optimized.cpp'
        )
        print("最適化版を main_beam_optimized.cpp に保存しました")

    except KeyboardInterrupt:
        print("最適化を中断しました")
        if study.best_trial:
            print(f"Current best score: {-study.best_value}")
            print("Current best params:")
            for key, value in study.best_params.items():
                print(f"  {key}: {value}")

if __name__ == "__main__":
    main()
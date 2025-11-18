#!/usr/bin/env python3
"""
AHC055 ビームサーチパラメータ最適化 v2（範囲改善版）
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
        'int beam_width = 37;': f'int beam_width = {params["beam_width"]};',
        'int max_depth = 14;': f'int max_depth = {params["max_depth"]};',
        'int expand_count = 7;': f'int expand_count = {params["expand_count"]};',
        'double weapon_coeff = 1.3200654190149195;': f'double weapon_coeff = {params["weapon_coeff"]};',
        'double progress_coeff = 3.109126733153162;': f'double progress_coeff = {params["progress_coeff"]};',
        'double cost_coeff = 1.9543769416468377;': f'double cost_coeff = {params["cost_coeff"]};',
        'double completion_bonus = 82010.62586888915;': f'double completion_bonus = {params["completion_bonus"]};',
        'double early_bonus = (8.0 - cost) * 0.9455490474077702;': f'double early_bonus = (8.0 - cost) * {params["early_bonus_coeff"]};',
        'double durability_bonus = input.C[i] * 0.905344615384884;': f'double durability_bonus = input.C[i] * {params["durability_bonus_coeff"]};',
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
            modify_beam_params('main_beam_optimized.cpp', params, temp_cpp.name)
            temp_cpp_path = temp_cpp.name

        # コンパイル
        exe_path = temp_cpp_path.replace('.cpp', '.exe')
        compile_cmd = [
            'g++', '-std=gnu++23', '-O2', temp_cpp_path, '-o', exe_path
        ]

        compile_result = subprocess.run(
            compile_cmd,
            capture_output=True,
            text=True,
            timeout=30
        )

        if compile_result.returncode != 0:
            return float('inf')

        # 複数ケースでテスト
        scores = []
        for case_id in range(min(num_cases, 100)):
            input_file = f'tools/in/{case_id:04d}.txt'
            if not os.path.exists(input_file):
                continue

            with open(input_file, 'r') as f:
                input_data = f.read()

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
    """改善された目的関数（範囲を最適化）"""
    params = {
        # 整数パラメータ
        'beam_width': trial.suggest_int('beam_width', 25, 50),  # 下限を上げる
        'max_depth': trial.suggest_int('max_depth', 8, 20),     # 範囲を下げる
        'expand_count': trial.suggest_int('expand_count', 5, 12), # 上限を上げる

        # 浮動小数点パラメータ（境界に近かったものを拡張）
        'weapon_coeff': trial.suggest_float('weapon_coeff', 0.8, 2.5),      # 拡張
        'progress_coeff': trial.suggest_float('progress_coeff', 1.5, 5.0),   # 範囲調整
        'cost_coeff': trial.suggest_float('cost_coeff', 1.5, 3.0),           # 上限拡張
        'completion_bonus': trial.suggest_float('completion_bonus', 60000, 120000), # 拡張
        'early_bonus_coeff': trial.suggest_float('early_bonus_coeff', 0.7, 1.5),    # 上限拡張
        'durability_bonus_coeff': trial.suggest_float('durability_bonus_coeff', 0.7, 1.5), # 上限拡張
    }

    score = evaluate_params(params, num_cases=25)  # 評価ケース数増加
    return score

def main():
    print("AHC055 ビームサーチパラメータ最適化v2開始")

    # Optunaスタディ作成
    study = optuna.create_study(direction='minimize')

    # 最適化実行（試行回数増加）
    study.optimize(objective, n_trials=100)

    # 結果表示
    print("=== 最適化結果v2 ===")
    best_score = abs(study.best_value)
    print(f"Best score: {best_score}")
    print("Best params:")
    for key, value in study.best_params.items():
        print(f"  {key}: {value}")

    # 最適化結果でC++ファイル生成
    modify_beam_params('main_beam_optimized.cpp', study.best_params, 'main_beam_optimized_v2.cpp')
    print("最適化結果を main_beam_optimized_v2.cpp に保存しました。")

if __name__ == "__main__":
    main()
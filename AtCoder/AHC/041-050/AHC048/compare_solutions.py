#!/usr/bin/env python3
import subprocess
import os
import sys
from pathlib import Path

def run_score_calculator(input_file, output_file, debug_file):
    """Run score calculator and return the score"""
    try:
        result = subprocess.run(['./score_calculator.exe', input_file, output_file, debug_file], 
                              capture_output=True, text=True, cwd='.')
        if result.returncode == 0:
            for line in result.stdout.split('\n'):
                if 'Absolute Score:' in line:
                    score_str = line.split(':')[1].strip()
                    return float(score_str)
        return None
    except Exception as e:
        print(f"Error running score calculator: {e}")
        return None

def parse_debug_file(debug_file):
    """Parse debug file to extract statistics"""
    stats = {}
    try:
        with open(debug_file, 'r') as f:
            content = f.read()
            lines = content.split('\n')
            
        for line in lines:
            if 'Total operations (type 1):' in line:
                stats['operations'] = int(line.split(':')[1].strip())
            elif 'Colors created:' in line:
                parts = line.split(':')[1].strip().split(' / ')
                stats['colors_created'] = int(parts[0])
                stats['total_colors'] = int(parts[1])
            elif 'Color Error (E):' in line:
                stats['color_error'] = float(line.split(':')[1].strip())
            elif 'Operation Cost:' in line:
                cost_part = line.split('=')[1].strip()
                stats['operation_cost'] = int(cost_part)
                
    except Exception as e:
        print(f"Error parsing debug file {debug_file}: {e}")
        
    return stats

def main():
    input_file = "in.txt"
    solutions = ["out.txt", "output_claude_2.txt", "output_claude_3.txt"]
    
    print("=== AHC048 Solutions Comparison ===")
    print()
    
    results = []
    
    # Test each solution
    for solution in solutions:
        if os.path.exists(solution):
            print(f"Processing {solution}...")
            debug_file = f"debug_{Path(solution).stem}.txt"
            
            score = run_score_calculator(input_file, solution, debug_file)
            if score is not None:
                stats = parse_debug_file(debug_file)
                results.append({
                    'solution': solution,
                    'score': score,
                    'stats': stats
                })
                print(f"  Score: {score:,.0f}")
                if 'operations' in stats:
                    print(f"  Operations: {stats['operations']}")
                if 'colors_created' in stats:
                    print(f"  Colors: {stats['colors_created']}/{stats.get('total_colors', 'N/A')}")
                if 'color_error' in stats:
                    print(f"  Color Error: {stats['color_error']:.6f}")
            else:
                print(f"  Error: Could not calculate score for {solution}")
        else:
            print(f"  Warning: {solution} not found")
        print()
    
    # Sort by score
    results.sort(key=lambda x: x['score'])
    
    print("=== Results Summary ===")
    print(f"{'Rank':<4} | {'Solution':<20} | {'Score':<12} | {'Operations':<10} | {'Colors':<7} | {'Avg Error':<10}")
    print("-" * 75)
    
    for i, result in enumerate(results):
        stats = result['stats']
        rank = i + 1
        solution = result['solution']
        score = result['score']
        operations = stats.get('operations', 'N/A')
        colors = f"{stats.get('colors_created', 'N/A')}/{stats.get('total_colors', 'N/A')}"
        avg_error = stats.get('color_error', 0) / stats.get('total_colors', 1000) if 'color_error' in stats else 'N/A'
        
        print(f"{rank:<4} | {solution:<20} | {score:<12,.0f} | {operations:<10} | {colors:<7} | {avg_error if avg_error == 'N/A' else f'{avg_error:.6f}':<10}")
    
    print()
    print("=== Performance Analysis ===")
    
    if len(results) >= 2:
        best = results[0]
        worst = results[-1]
        
        print(f"Best solution: {best['solution']}")
        print(f"Worst solution: {worst['solution']}")
        print(f"Score difference: {worst['score'] - best['score']:,.0f} ({(worst['score'] / best['score'] - 1) * 100:.1f}% worse)")
        
        if 'operations' in best['stats'] and 'operations' in worst['stats']:
            print(f"Operation difference: {worst['stats']['operations'] - best['stats']['operations']} operations")
        
        if 'color_error' in best['stats'] and 'color_error' in worst['stats']:
            print(f"Color error difference: {worst['stats']['color_error'] - best['stats']['color_error']:.6f}")
    
    print()
    print("Detailed debug files available:")
    for result in results:
        debug_file = f"debug_{Path(result['solution']).stem}.txt"
        if os.path.exists(debug_file):
            print(f"  {debug_file}")

if __name__ == "__main__":
    main()

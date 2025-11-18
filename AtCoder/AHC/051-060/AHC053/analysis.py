#!/usr/bin/env python3
# AHC053 詳細分析スクリプト

# out_full.txtからA値とX値を抽出
with open('out_full.txt', 'r') as f:
    lines = f.readlines()

# A値とX値の抽出
A_line = lines[0].strip().split()
X_line = lines[1].strip().split()

A = [int(x) for x in A_line]
X = [int(x) for x in X_line]

# B値（debug出力から抽出済み）
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

N = len(A)
M = len(B)

print("=== AHC053 詳細分析結果 ===")
print(f"カード総数: {N}")
print(f"山の数: {M}")
print()

# 廃棄されたカードの分析
discarded_cards = []
for i in range(N):
    if X[i] == 0:
        discarded_cards.append((i, A[i]))

print(f"=== 廃棄カード分析 ===")
print(f"廃棄カード数: {len(discarded_cards)}")
print(f"廃棄率: {len(discarded_cards)/N*100:.1f}%")
print()

# 廃棄カードを値でソート
discarded_cards.sort(key=lambda x: x[1], reverse=True)
print(f"廃棄カード一覧（値の大きい順）:")
for i, (card_idx, value) in enumerate(discarded_cards):
    print(f"{i+1:2d}. Card {card_idx:3d}: {value:15,}")
print()

# 各山の状況分析
pile_sums = [0] * M
pile_cards = [[] for _ in range(M)]

for i in range(N):
    if X[i] > 0:
        pile_idx = X[i] - 1
        pile_sums[pile_idx] += A[i]
        pile_cards[pile_idx].append((i, A[i]))

print(f"=== 各山の詳細分析 ===")
total_error = 0
pile_analysis = []

for j in range(M):
    current_sum = pile_sums[j]
    target = B[j]
    error = abs(current_sum - target)
    deficit = target - current_sum if current_sum < target else 0
    excess = current_sum - target if current_sum > target else 0
    card_count = len(pile_cards[j])

    pile_analysis.append({
        'pile': j + 1,
        'current_sum': current_sum,
        'target': target,
        'error': error,
        'deficit': deficit,
        'excess': excess,
        'card_count': card_count,
        'cards': pile_cards[j]
    })
    total_error += error

print(f"総誤差: {total_error:,}")
print()

# 誤差の大きい順にソート
pile_analysis.sort(key=lambda x: x['error'], reverse=True)

print(f"山の状況（誤差の大きい順）:")
print(f"{'Pile':>4} {'Current Sum':>15} {'Target':>15} {'Error':>12} {'Status':>8} {'Cards':>5}")
print("-" * 70)

for pile_info in pile_analysis:
    pile_num = pile_info['pile']
    current = pile_info['current_sum']
    target = pile_info['target']
    error = pile_info['error']
    card_count = pile_info['card_count']

    if pile_info['deficit'] > 0:
        status = f"不足{pile_info['deficit']:,}"
    elif pile_info['excess'] > 0:
        status = f"超過{pile_info['excess']:,}"
    else:
        status = "一致"

    print(f"{pile_num:4d} {current:15,} {target:15,} {error:12,} {status:>15s} {card_count:5d}")

print()

# 不足している山の詳細分析
deficit_piles = [p for p in pile_analysis if p['deficit'] > 0]
print(f"=== 不足山詳細分析 ===")
print(f"不足している山の数: {len(deficit_piles)}")

if deficit_piles:
    print(f"不足山（不足量の大きい順）:")
    deficit_piles.sort(key=lambda x: x['deficit'], reverse=True)

    for pile_info in deficit_piles[:10]:  # 上位10山
        pile_num = pile_info['pile']
        deficit = pile_info['deficit']
        print(f"山{pile_num:2d}: 不足量 {deficit:12,}")

print()

# 重要：廃棄カードと不足山のマッチング分析
print(f"=== 重要：廃棄カードによる改善可能性分析 ===")

potential_improvements = []

for card_idx, card_value in discarded_cards:
    # この廃棄カードを各不足山に追加した場合の改善を計算
    for pile_info in deficit_piles:
        pile_idx = pile_info['pile'] - 1
        current_sum = pile_info['current_sum']
        target = pile_info['target']
        deficit = pile_info['deficit']

        # 現在の誤差
        current_error = abs(current_sum - target)

        # カード追加後の誤差
        new_sum = current_sum + card_value
        new_error = abs(new_sum - target)

        # 改善量
        improvement = current_error - new_error

        if improvement > 0:  # 改善がある場合
            potential_improvements.append({
                'card_idx': card_idx,
                'card_value': card_value,
                'pile': pile_info['pile'],
                'current_sum': current_sum,
                'target': target,
                'deficit': deficit,
                'new_sum': new_sum,
                'current_error': current_error,
                'new_error': new_error,
                'improvement': improvement
            })

# 改善量でソート
potential_improvements.sort(key=lambda x: x['improvement'], reverse=True)

print(f"廃棄カードによる改善可能性（改善量の大きい順）:")
print(f"{'Card':>4} {'Value':>15} {'Pile':>4} {'Current':>15} {'Target':>15} {'New Sum':>15} {'Improvement':>12}")
print("-" * 90)

for i, imp in enumerate(potential_improvements[:20]):  # 上位20件
    print(f"{imp['card_idx']:4d} {imp['card_value']:15,} {imp['pile']:4d} {imp['current_sum']:15,} {imp['target']:15,} {imp['new_sum']:15,} {imp['improvement']:12,}")

print()

# 特に大きな改善が期待できるケースの詳細分析
significant_improvements = [imp for imp in potential_improvements if imp['improvement'] > 1000000000]  # 10億以上の改善

if significant_improvements:
    print(f"=== 特に大きな改善が期待できるケース（改善量10億以上）===")
    print(f"該当ケース数: {len(significant_improvements)}")

    for i, imp in enumerate(significant_improvements[:5]):  # 上位5件の詳細
        print(f"\n{i+1}. Card {imp['card_idx']} (値: {imp['card_value']:,}) -> 山{imp['pile']}")
        print(f"   現在の山の合計: {imp['current_sum']:,}")
        print(f"   目標値: {imp['target']:,}")
        print(f"   不足量: {imp['deficit']:,}")
        print(f"   カード追加後の合計: {imp['new_sum']:,}")
        print(f"   現在の誤差: {imp['current_error']:,}")
        print(f"   追加後の誤差: {imp['new_error']:,}")
        print(f"   改善量: {imp['improvement']:,}")

# 結果をファイルに保存
with open('analysis_result.txt', 'w', encoding='utf-8') as f:
    f.write("=== AHC053 詳細分析結果 ===\n")
    f.write(f"カード総数: {N}\n")
    f.write(f"山の数: {M}\n")
    f.write(f"総誤差: {total_error:,}\n")
    f.write(f"廃棄カード数: {len(discarded_cards)} ({len(discarded_cards)/N*100:.1f}%)\n\n")

    f.write("=== 廃棄カード一覧 ===\n")
    for i, (card_idx, value) in enumerate(discarded_cards):
        f.write(f"{i+1:2d}. Card {card_idx:3d}: {value:15,}\n")
    f.write("\n")

    f.write("=== 各山の状況（誤差の大きい順）===\n")
    f.write(f"{'Pile':>4} {'Current Sum':>15} {'Target':>15} {'Error':>12} {'Status':>15} {'Cards':>5}\n")
    f.write("-" * 80 + "\n")

    for pile_info in pile_analysis:
        pile_num = pile_info['pile']
        current = pile_info['current_sum']
        target = pile_info['target']
        error = pile_info['error']
        card_count = pile_info['card_count']

        if pile_info['deficit'] > 0:
            status = f"不足{pile_info['deficit']:,}"
        elif pile_info['excess'] > 0:
            status = f"超過{pile_info['excess']:,}"
        else:
            status = "一致"

        f.write(f"{pile_num:4d} {current:15,} {target:15,} {error:12,} {status:>15s} {card_count:5d}\n")

    f.write("\n=== 廃棄カードによる改善可能性（上位20件）===\n")
    f.write(f"{'Card':>4} {'Value':>15} {'Pile':>4} {'Improvement':>12}\n")
    f.write("-" * 50 + "\n")

    for imp in potential_improvements[:20]:
        f.write(f"{imp['card_idx']:4d} {imp['card_value']:15,} {imp['pile']:4d} {imp['improvement']:12,}\n")

    if significant_improvements:
        f.write(f"\n=== 特に大きな改善ケース（改善量10億以上）===\n")
        for i, imp in enumerate(significant_improvements[:10]):
            f.write(f"\n{i+1}. Card {imp['card_idx']} -> 山{imp['pile']} (改善: {imp['improvement']:,})\n")

print(f"\n分析結果を 'analysis_result.txt' に保存しました。")

# 最後に焼きなまし実装に問題がありそうかの判定
if significant_improvements:
    print(f"\n*** 警告：焼きなまし実装に問題の可能性 ***")
    print(f"廃棄カードの中に明らかに改善できるものが {len(significant_improvements)} 件見つかりました。")
    print(f"これは焼きなまし法またはスコア関数に実装バグがある可能性を示しています。")
else:
    print(f"\n*** 焼きなまし実装は正常と思われます ***")
    print(f"廃棄カードによる大幅な改善ケースは見つかりませんでした。")
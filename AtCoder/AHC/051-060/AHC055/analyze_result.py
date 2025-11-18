# 結果の分析
weapon_usage = {}  # weapon_id -> count
total_bare_hands = 0

with open('result_sol3.txt', 'r') as f:
    for line in f:
        parts = line.strip().split()
        if len(parts) == 2:
            w, b = parts
            if w == '-1':
                total_bare_hands += 1
            else:
                weapon_usage[w] = weapon_usage.get(w, 0) + 1

print(f"Total attacks: {total_bare_hands + sum(weapon_usage.values())}")
print(f"Bare hands: {total_bare_hands} ({100.0 * total_bare_hands / (total_bare_hands + sum(weapon_usage.values())):.2f}%)")
print(f"With weapons: {sum(weapon_usage.values())} ({100.0 * sum(weapon_usage.values()) / (total_bare_hands + sum(weapon_usage.values())):.2f}%)")
print(f"\nWeapons used: {len(weapon_usage)}")
print(f"Weapons not used: {200 - len(weapon_usage)}")

# 使われなかった武器
used_weapons = set(weapon_usage.keys())
all_weapons = set(str(i) for i in range(200))
unused = all_weapons - used_weapons
print(f"\nUnused weapons: {sorted([int(x) for x in unused])[:20]}...")  # 最初の20個

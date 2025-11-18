#!/usr/bin/env python3
import sys
import math
from pulp import LpProblem, LpMinimize, LpVariable, LpBinary, lpSum, PULP_CBC_CMD, LpStatusOptimal

def solve():
    input_data = sys.stdin.read().strip().split()
    N = int(input_data[0])
    L = int(input_data[1])
    T = list(map(int, input_data[2:2+N]))
    
    # 問題を定義: "feasibility problem" (目的関数はとりあえず0)
    prob = LpProblem("cleaning_assignment", LpMinimize)
    
    # 変数 Xodd[i][j], Xeven[i][j] in {0,1}
    #   Xodd[i][j] = 1 ⇒ 社員iの「奇数回目の行き先」は社員j
    #   Xeven[i][j] = 1 ⇒ 社員iの「偶数回目の行き先」は社員j
    Xodd = []
    Xeven = []
    for i in range(N):
        Xodd.append([
            LpVariable(f"Xodd_{i}_{j}", cat=LpBinary) for j in range(N)
        ])
        Xeven.append([
            LpVariable(f"Xeven_{i}_{j}", cat=LpBinary) for j in range(N)
        ])
    
    # 目的関数は一旦「誤差なしの厳密割り当てが可能かどうか」を探るので0にしておく
    prob.setObjective(lpSum([]))
    
    # 制約1: 各社員iについて、odd行き先はちょうど1つ、even行き先もちょうど1つ
    for i in range(N):
        prob.addConstraint(lpSum(Xodd[i][j] for j in range(N)) == 1,
                           name=f"odd_one_{i}")
        prob.addConstraint(lpSum(Xeven[i][j] for j in range(N)) == 1,
                           name=f"even_one_{i}")
    
    # 制約2: 各社員jの「入ってくる本数」を T_j (ただし j=0 だけ T_0-1 ) に
    #   odd辺( i→a_i ) は  ceil(T_i/2)回分, even辺( i→b_i ) は floor(T_i/2)回分
    for j in range(N):
        # 社員jへの流入を合計した式
        incoming_expr = []
        for i in range(N):
            # i の odd 回数: ceil(T_i/2)
            odd_count = (T[i] + 1)//2
            # i の even 回数: floor(T_i/2)
            even_count = T[i]//2
            
            incoming_expr.append(odd_count * Xodd[i][j])
            incoming_expr.append(even_count * Xeven[i][j])
        
        # j=0 は "T_0 - 1" にする (初週の外部スタート分を除く)
        if j == 0:
            prob.addConstraint(lpSum(incoming_expr) == T[0] - 1,
                               name=f"inflow_0")
        else:
            prob.addConstraint(lpSum(incoming_expr) == T[j],
                               name=f"inflow_{j}")
    
    # 解く
    solver = PULP_CBC_CMD(msg=0)  # ソルバー(ここではCBC)を使う。msg=0でログ非表示
    res = prob.solve(solver)
    
    if res != LpStatusOptimal:
        print("No solution (or not optimal) found.", file=sys.stderr)
        # 必要に応じてスラック変数を入れた定式化に切り替えるなどの処理を。
        return
    
    # 解の取り出し
    #  それぞれ Xodd[i][j], Xeven[i][j] = 1 となった j が a_i, b_i となる
    a = [-1]*N
    b = [-1]*N
    for i in range(N):
        for j in range(N):
            val_odd = Xodd[i][j].varValue
            val_even = Xeven[i][j].varValue
            if val_odd > 0.5:
                a[i] = j
            if val_even > 0.5:
                b[i] = j
    
    # 出力: 各社員 i について (a_i, b_i)
    for i in range(N):
        print(a[i], b[i])


if __name__ == "__main__":
    solve()

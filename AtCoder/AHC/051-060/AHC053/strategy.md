# AHC053 解法方針

## 問題の核心的特徴

### 制約の分析
- **巨大な数値**: B値は10¹⁵オーダー（L = 10¹⁵ - 2×10¹², U = 10¹⁵ + 2×10¹²）
- **カード枚数**: N = 500枚（比較的多い）
- **山の数**: M = 50個（適度な数）
- **選択の自由度**: A値は1以上U以下で自由選択、カードの廃棄も可能
- **B値の特性**: 昇順ソート済み、隣接する値の差分情報も活用可能

### 得点関数の特性
- 誤差 E = Σⱼ₌₁ᴹ |Sⱼ - Bⱼ| の最小化が目標
- 対数的な得点関数により、小さな誤差の改善が大きな得点向上につながる
- 各山での誤差を独立に最適化できる

## Phase 1: すぐに実装できる基本解法

### 1.1 シンプルな固定A値 + 貪欲割り当て
```cpp
// 実装時間: 30分程度
// 期待得点: 低いが確実に動作

1. A値をすべて同じ値（例：U/100）に設定
2. 各カードを最も近いB値の山に貪欲に割り当て
3. 基本的な入出力処理を実装
```

**メリット**:
- 実装が簡単で確実に動作
- デバッグが容易
- 他の手法の比較基準になる

### 1.2 B値分析ベースのA値設定
```cpp
1. B値の平均値を計算: avg = Σ Bⱼ / M
2. A値を avg/500 程度に設定（各山に平均10枚程度配置想定）
3. 貪欲割り当てを実行
```

## Phase 2: 確実に改善できる手法

### 2.1 数学的アプローチ - GCD（最大公約数）ベース

#### GCD活用法
```cpp
ll g = gcd(B₁, B₂, ..., Bₘ);  // 全B値のGCD
vector<ll> candidates;

// GCDの約数を候補に追加
for(ll d = 1; d * d <= g; d++) {
    if(g % d == 0) {
        candidates.push_back(d);
        if(d != g/d) candidates.push_back(g/d);
    }
}

// B値の差分のGCDも考慮
ll diff_gcd = gcd(B₂-B₁, B₃-B₂, ..., Bₘ-Bₘ₋₁);
// diff_gcdの約数も候補に追加
```

**理論的根拠**: GCDの整数倍の和で任意のB値を厳密に表現可能

#### 階層的基底選択
```cpp
// 大きな単位から小さな単位へ
vector<ll> basis;
basis.push_back(g);                    // 最大公約数
basis.push_back(g / small_factor);     // 中程度の単位
basis.push_back(1);                    // 最小単位（微調整用）

// 各基底に対してカード枚数を適切に分配
for(ll base : basis) {
    int count = estimate_optimal_count(base, B_values);
    for(int i = 0; i < count; i++) A.push_back(base);
}
```

### 2.2 動的プログラミングによる最適割り当て

#### ナップサック型DP
```cpp
// 各山に対して独立に最適化
for(int j = 0; j < M; j++) {
    ll target = B[j];
    // dp[sum] = 最小使用カード数
    map<ll, int> dp;
    dp[0] = 0;

    for(ll a : A_values) {
        auto new_dp = dp;
        for(auto [sum, count] : dp) {
            if(sum + a <= target + tolerance) {
                if(!new_dp.count(sum + a) || new_dp[sum + a] > count + 1) {
                    new_dp[sum + a] = count + 1;
                }
            }
        }
        dp = new_dp;
    }

    // targetに最も近い合計を選択
    ll best_sum = find_closest_sum(dp, target);
    assign_cards_to_pile(j, best_sum);
}
```

### 2.3 局所探索による改善

#### シミュレーテッドアニーリング
```cpp
class SimulatedAnnealing {
    double temperature = 1000.0;
    double cooling_rate = 0.99;

    void optimize() {
        while(timer.get() < time_limit) {
            // 近傍解の生成
            auto new_solution = generate_neighbor(current);
            double delta = evaluate(new_solution) - evaluate(current);

            if(delta < 0 || rnd(0.0, 1.0) < exp(-delta / temperature)) {
                current = new_solution;
                if(evaluate(current) < best_score) {
                    best_solution = current;
                }
            }
            temperature *= cooling_rate;
        }
    }

    Solution generate_neighbor(const Solution& sol) {
        // 近傍操作の例：
        // 1. カードを別の山に移動
        // 2. カードを廃棄/復活
        // 3. A値を微調整（小さい範囲で）
    }
};
```

## Phase 3: 高度だが効果的な可能性のある手法

### 3.1 ハイブリッド数学的最適化

#### 素因数分解ベース
```cpp
// B値を素因数分解して効率的な基底を構築
map<ll, int> prime_factors;
for(ll b : B_values) {
    auto factors = factorize(b);
    for(auto [p, cnt] : factors) {
        prime_factors[p] = max(prime_factors[p], cnt);
    }
}

// 重要な素因数の累乗を基底として使用
vector<ll> basis;
for(auto [prime, max_count] : prime_factors) {
    for(int exp = 1; exp <= max_count; exp++) {
        basis.push_back(pow(prime, exp));
    }
}
```

#### 線形計画法的定式化
```cpp
// 各A値の使用回数を変数として
// minimize Σⱼ |Σᵢ xᵢⱼ * Aᵢ - Bⱼ|
// subject to: Σⱼ xᵢⱼ ≤ 1 (各カードは最大1回使用)
//            xᵢⱼ ∈ {0, 1}

// 近似解法として緩和問題を解いてから離散化
```

### 3.2 メタヒューリスティック

#### 遺伝的アルゴリズム
```cpp
class GeneticAlgorithm {
    struct Individual {
        vector<ll> A_values;      // カードの値
        vector<int> assignment;   // カードの割り当て
        double fitness;

        void mutate() {
            // A値の突然変異
            if(rnd(0.0, 1.0) < 0.1) {
                int idx = rnd(0, A_values.size());
                A_values[idx] += rnd(-1000, 1000);
            }
            // 割り当ての突然変異
            if(rnd(0.0, 1.0) < 0.2) {
                int idx = rnd(0, assignment.size());
                assignment[idx] = rnd(0, M + 1);  // 0 = 廃棄
            }
        }
    };

    Individual crossover(const Individual& parent1, const Individual& parent2) {
        // 一様交叉または一点交叉
        Individual child;
        for(int i = 0; i < N; i++) {
            if(rnd(0, 2) == 0) {
                child.A_values[i] = parent1.A_values[i];
                child.assignment[i] = parent1.assignment[i];
            } else {
                child.A_values[i] = parent2.A_values[i];
                child.assignment[i] = parent2.assignment[i];
            }
        }
        return child;
    }
};
```

### 3.3 マルチスタート＋局所探索

#### 複数の初期解からの最適化
```cpp
vector<Solution> best_solutions;

// 異なる戦略で初期解を生成
best_solutions.push_back(greedy_solution());
best_solutions.push_back(gcd_based_solution());
best_solutions.push_back(random_solution());
best_solutions.push_back(dp_based_solution());

// 各初期解から局所探索
for(auto& sol : best_solutions) {
    simulated_annealing(sol);
    hill_climbing(sol);
}

// 最良解を選択
Solution final_solution = *min_element(best_solutions.begin(),
                                      best_solutions.end(),
                                      [](const auto& a, const auto& b) {
                                          return evaluate(a) < evaluate(b);
                                      });
```

## 実装優先度と時間配分

### 実装ロードマップ
1. **Phase 1（30-45分）**: 基本動作の確保
   - 入出力処理
   - シンプルな貪欲法
   - デバッグ環境整備

2. **Phase 2（60-90分）**: 確実な改善
   - GCDベースA値最適化
   - 局所探索（SA または HC）
   - 基本的なDP実装

3. **Phase 3（残り時間）**: 高度な最適化
   - 複数手法の組み合わせ
   - パラメータチューニング
   - エッジケース対応

### 実装上の注意点

#### 数値精度
```cpp
// 10^15オーダーの計算でオーバーフローに注意
using ll = long long;  // 必須
// 必要に応じて__int128やbigintを使用
```

#### 時間管理
```cpp
Timer timer(1900);  // 100msマージン
while(timer && improve_solution()) {
    // 最適化処理
}
```

#### デバッグ支援
```cpp
#ifdef _DEBUG
void debug_solution(const Solution& sol) {
    debug("Error:", calculate_error(sol));
    debug("A values:", sol.A_values);
    debug("Assignment distribution:", count_assignment(sol));
}
#endif
```

## 期待される成果

### Phase 1完了時
- 基本動作確認
- 参考点数の獲得

### Phase 2完了時
- 上位50%程度の性能
- 安定した解法の確立

### Phase 3完了時
- 上位20%を目指せる水準
- コンテスト上位入賞の可能性

## 追加考察事項

### B値の分布に応じた戦略
- B値の分散が小さい場合: 細かい刻みのA値が効果的
- B値の分散が大きい場合: 階層的な基底が効果的
- 規則的なパターンがある場合: パターン特化の最適化

### リアルタイム適応
```cpp
// B値を受け取った後の戦略調整
void adapt_strategy(const vector<ll>& B) {
    ll variance = calculate_variance(B);
    if(variance < threshold_small) {
        use_fine_grained_strategy();
    } else if(variance > threshold_large) {
        use_hierarchical_strategy();
    } else {
        use_balanced_strategy();
    }
}
```

---

## 2025-09-13 考察：A値分布の最適化

### 現在の実装の問題点

現在のA値生成（main.cpp:529-536）では以下の問題があります：

1. **均等な乱数分布**: 全てのA[i]が同じような値域で生成される
2. **B値の特性未活用**: 昇順ソート済みのB値や隣接差分を活用していない
3. **不適切な粒度**: 10^15オーダーに対して細かすぎる変動（10%）

### 期待値に基づく理論的分析

B[i]は[L,U]の一様乱数であるため：
- B値の期待値: E[B] = (L + U) / 2 ≈ 10^15
- 各山への期待カード数: N/M = 500/50 = 10枚
- 理想的なA値の期待値: E[A] = E[B] / 10 ≈ 10^14

**重要な洞察**: M個のLを各B[i]に効率的に分配する階層的戦略が有効

### 提案：階層的A値分布戦略

#### 仮説
3層構造のA値分布を提案：

1. **大単位カード (40%, 200枚)**:
   - 値: L/2 ≈ 5×10^14
   - 役割: 各B[i]の基本値として使用

2. **中単位カード (40%, 200枚)**:
   - 値: L/20 ≈ 2.5×10^13
   - 役割: 中程度の調整に使用

3. **小単位カード (20%, 100枚)**:
   - 値: L/200 ≈ 2.5×10^12
   - 役割: 細かい微調整に使用

#### 理論的根拠

この分布により：
- 各B[i] ≈ 10^15に対して、大単位1-2枚 + 中単位数枚 + 小単位数枚で近似可能
- 値のばらつきを抑制しながら柔軟な組み合わせが実現
- 期待値E[A] = (0.4×L/2 + 0.4×L/20 + 0.2×L/200) ≈ 0.2L + 0.02L + 0.001L ≈ 0.221L ≈ 2.2×10^14

この期待値は理論値10^14の約2倍ですが、廃棄戦略により適切に調整可能。

#### 期待される効果

1. **表現力の向上**: 大中小の組み合わせでほぼ任意のB値を近似可能
2. **探索効率の改善**: SA等の局所探索で有効な近傍操作が増加
3. **安定性の向上**: 極端な外れ値の出現確率を低減

### 次のアクション

この仮説を実装し、現在の均等分布との性能比較を実施する。
4点を全探索する方針について書きます。

<br>

相異なる4点 $A$, $B$, $C$, $D$ を順番につないだ時、それが正方形をなす条件は以下の通りです。

- 4辺 $AB$, $BC$, $CD$, $DA$ の長さが等しい
- 対角線 $AC$, $BD$ の長さが等しい

今回の制約では、候補となる点の数は最大でも $9^2 = 81$個で、そこから順番を考慮して4つ選ぶ方法は $_{81}P_4 = 39,929,760$通りです。

<br>

よって、**ある程度高速な言語であれば** 4点の順列を全探索することでも、この問題を解くことができます。

この解法では、同じ正方形を1つあたり8回（4始点 × 2方向）数えるため、探索の結果を8で割る必要があります。

<br>

#### 公式解説の方法との差分

公式解説の方法では、2点を決め打って残り2点の座標を計算して求めていました。

本解説の方針では、実行時間が非常に大きく延びる代わりに、座標の計算が不要になります。

これは、座標に対する計算が苦手な場合に、時間のロスを避けられる利点があります。

<br>

#### Python3 での実装例 (1394ms, [提出結果](https://atcoder.jp/contests/abc275/submissions/36074505))
PyPy3 での提出であれば、制限時間に間に合います。
```py
import itertools

N = 9

points = []
for i in range(N):
    S = input()
    for j in range(N):
        if S[j] == '#':
            points.append((i, j))

ans = 0
for a,b,c,d in itertools.permutations(points, 4):
    edge1 = (a[0]-b[0])**2 + (a[1]-b[1])**2
    edge2 = (b[0]-c[0])**2 + (b[1]-c[1])**2
    edge3 = (c[0]-d[0])**2 + (c[1]-d[1])**2
    edge4 = (d[0]-a[0])**2 + (d[1]-a[1])**2
    diag1 = (a[0]-c[0])**2 + (a[1]-c[1])**2
    diag2 = (b[0]-d[0])**2 + (b[1]-d[1])**2
    if edge1 == edge2 == edge3 == edge4 and diag1 == diag2:
        ans += 1

print(ans//8)
```
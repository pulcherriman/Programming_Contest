# ABC331 結果
000000- 74:05 281st
perf.2086  Rate: 1986->1996 :)

## 自分の解法

### A 3:24
 3分(?)

### B 4:44 (+1:20)
 DPした(??)

### C 14:28 (+9:44)
 累積和のindexを二分探索した(???)

### D 29:33 (+15:05)
 領域を9つに分割して鬼の場合分けをした(????)

### E 44:20 (+14:47)
 主菜を全探索、副菜を降順に見て、OKだったら次の主菜へ。の貪欲
 O(N^2)っぽいけど、この貪欲は高々L回しか弾かれないのでO(N+L)

### F 74:05 (+29:45)
 左右からのロリハで判定したいが、更新があるのでハッシュを事前に持てない
 ハッシュ計算に寄与する各項の値だけ持っておいて、一点更新+区間和を高速にできればいい→セグ木

### G -
コンプガチャだ！　解けません

# ABC343 結果 (Unrated)
- 0002100 81:03+15:00 
- 82nd perf.2400相当

## 自分の解法

### A 0:43
- 脳死でループ書いたけど、(a+b ? a+b-1 : 1) とかxorとかでいい

### B 1:48 (+1:05)
- やる

### C 5:13 (+3:25)
- 知 っ て た（立法数）。
- i=1~1e6 まで、i^3を回文判定する全探索

### D 14:12+2 (+9:59+10:00)
- mapで個数管理しながらやるだけ
- pbdsの未定義動作を踏むコードを書いてしまい2ペナ（カス）

### E -
- 知 っ て た（立法数） ２。
- Dのペナで萎えた後にこれはちょっと...... → パス

### G 34:33 (+20:21)
- dist[i][j] =「Siの後ろにSjをつなげるとき増える文字数」とするとTSPになる
- 包含している文字列がある場合は存在ごと消すといい
- 最短超文字列問題。AHCで見た。

### F 55:36 (+21:03)
- セグ木に{最大値, 2番目の値, 最大値の個数, 2番目の値の個数}を持たせる。パワー。

### E 81:03+1 (+25:27+5:00)
- 配置を決めると、各重複部分の面積は四則演算で求まるので、配置を全探索。
- 多少無駄なことをしても、計算量は意外と大丈夫（解析せずとも入力例2が動けばよい）
- が、あまりにも好きではない......w
# 1日目
- 無理そうで草
- 各日の連結成分についてまとめられるかも
  - でかい成分でも事前に収穫機械を置いておくと消えちゃうのでまとめて消すのが大事？
### 貪欲
- 一番価値が大きい奴$Veg[i]$を見る
- それに連結数が多い日を探索
  - ここ前計算ポイント？
- その日に$Veg[i]$に収穫機を持っていく
- そこまでに連結成分に収穫機を置かない
### 誤読
- 連結している野菜全部取れるわけじゃないやんけ！！！！！！
  - 収穫機があって連結している
- そうなるとあんまり連結できない
  - 1ターンに1個しか動かせないので、下手につなげようとすると準備段階で消しちゃう
  - 
### やりたいこと

#### 収穫機が1つの時
- 現在の最強を貪欲に取って、そこまで悪くならない

```
Score: 7522484
常に今ある中で最大の値のところに収穫機を移動させる
```

**ターンxに新たに生える場所に事前に機械を置いといて、ターンxの操作ではその周りの野菜に収穫機を配置する**
- 連結できるのは一度に1つの連結成分のみ
- 消せるのは、既存の野菜**1つ**+新規の野菜**1つ以上**の連結成分

### 誤読2
- 連結しているのは野菜なくてもいいやんけ！
(書く)

### 焼きなまし...?
- 移動元をほかのに変えてみる焼きなまし
- 14021405
- 
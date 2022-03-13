export interface InputData {
  S: number; // 形状の種類数
  C: number; // 色の種類数
  H: number; // フックの数
  initialScore: number; // スコアの初期値
  a: number; // ハンガーの取付・取り外し1回ごとにスコアから引かれる値
  b: number; // 空きフックの個数1個につきスコアから引かれる値
  N_sc: number[][]; // (形状s,色c)ごとの生産数
  K_s: number[]; // 形状ごとのハンガーの数
  A_ss: number[][]; // 形状が変わるときの必要空きフック数
  B_cc: number[][]; // 色が変わるときの必要空きフック数
  N_sum: number; // 合計生産数
}

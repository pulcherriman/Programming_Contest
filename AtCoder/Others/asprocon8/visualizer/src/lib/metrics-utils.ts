import { InputData, Plan, Instruction, Metrics, Violation } from '../models';
import { ViolationBuilder } from './violation-utils';

const outputViolationBuilder = new ViolationBuilder('output file');

function getSetupTime(
  input: InputData,
  i1: Instruction,
  i2: Instruction
): number {
  return Math.max(input.A_ss[i1.s][i2.s], input.B_cc[i1.c][i2.c]);
}

type MetricsResult =
  | {
      data: Metrics;
      violation: null;
    }
  | {
      data: null;
      violation: Violation;
    };

export function calculate(input: InputData, plan: Plan): MetricsResult {
  let score = 0;
  const K = plan.K;
  const C = input.C;
  const S = input.S;
  const H = input.H;

  // planのチェック
  for (let i = 0; i < K; ++i) {
    const x = plan.instructions[i];
    if (x.s == -2 || x.s == -1) continue;
    if (x.s < 0 || x.s >= S || x.c < 0 || x.c >= C) {
      return {
        data: null,
        violation: outputViolationBuilder.invalidNumber(
          i + 2,
          `x_${i + 2}`,
          `${x.s + 1} ${x.c + 1}`
        ),
      };
    }
  }

  // シミュレーション
  const t = new Array<number>(H).fill(-1); // フックhに付けられているハンガーの種類
  const r = new Array<number>(S); // 使用可能なハンガーsの個数
  for (let i = 0; i < S; i++) {
    r[i] = input.K_s[i];
  }
  let prevInstruction: Instruction = { s: 0, c: 0 }; // 前回空きフックではなかったときのオーダー
  let space = 100000; // 現在空きフックがいくつ連続しているか
  const productCount = new Array<Array<number>>(S);
  for (let i = 0; i < S; i++) {
    productCount[i] = new Array<number>(C).fill(0);
  }
  let X = 0;

  for (let i = 0; i < K; i++) {
    const h = i % H;
    const x = plan.instructions[i];
    if (t[h] >= 0) {
      // ハンガーの回収
      if (x.s == -1 || (x.s >= 0 && t[h] != x.s)) {
        r[t[h]]++;
        X++;
        t[h] = -1;
      }
    }
    // ハンガーの取り付け
    if (x.s >= 0 && t[h] != x.s) {
      if (--r[x.s] < 0) {
        return {
          data: null,
          violation: outputViolationBuilder.notEnoughHangerViolation(i + 2),
        };
      }
      X++;
      t[h] = x.s;
    }
    if (x.s >= 0) {
      if (getSetupTime(input, prevInstruction, x) > space) {
        return {
          data: null,
          violation: outputViolationBuilder.notEnoughIntervalViolation(i + 2),
        };
      }
      prevInstruction = x;
      space = 0;
      productCount[x.s][x.c]++;
    } else {
      space++;
    }
  }

  for (let s = 0; s < S; s++) {
    for (let c = 0; c < C; c++) {
      if (productCount[s][c] != input.N_sc[s][c]) {
        return {
          data: null,
          violation: outputViolationBuilder.wrongProductCountViolation(
            s + 1,
            c + 1,
            input.N_sc[s][c],
            productCount[s][c]
          ),
        };
      }
    }
  }

  const Y = K - input.N_sum;
  score = input.initialScore - input.a * X - input.b * Y;
  if (score < 1) {
    score = 1;
  }

  console.log('IMOJUDGE<<<' + String(score) + '>>>');

  return {
    data: {
      score,
      hangerSwapCount: X,
      emptyHookCount: Y,
      instructionCount: K,
    },
    violation: null,
  };
}

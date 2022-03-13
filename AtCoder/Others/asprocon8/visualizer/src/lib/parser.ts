import { Violation, InputData, Instruction, Plan } from '../models';
import { ViolationBuilder } from './violation-utils';

const inputViolationBuilder = new ViolationBuilder('input file');
const outputViolationBuilder = new ViolationBuilder('output file');

export type InputResult =
  | {
      data: InputData;
      violation: null;
    }
  | {
      data: null;
      violation: Violation;
    };

export function parseInput(text: string): InputResult {
  const lines = text.split('\n');
  if (lines.length < 1) {
    return {
      data: null,
      violation: inputViolationBuilder.notEnoughData(1),
    };
  }

  let tmp = lines[0].split(' ');
  if (tmp.length < 5) {
    return {
      data: null,
      violation: inputViolationBuilder.notEnoughData(1),
    };
  }
  if (tmp.length > 5) {
    return {
      data: null,
      violation: inputViolationBuilder.tooManyData(1),
    };
  }

  const S = Number(tmp[0]);
  if (S < 1) {
    return {
      data: null,
      violation: inputViolationBuilder.invalidNumber(1, 'S', S),
    };
  }

  const C = Number(tmp[1]);
  if (C < 1) {
    return {
      data: null,
      violation: inputViolationBuilder.invalidNumber(1, 'C', C),
    };
  }

  const H = Number(tmp[2]);
  // TODO: 制約を満たすサンプルデータセットを作成。
  // if (H < 100 || H > 1000) {
  //   return {
  //     data: null,
  //     violation: inputViolationBuilder.invalidNumber(1, 'H', H),
  //   };
  // }

  const initialScore = 10000000;

  const a = Number(tmp[3]);
  // TODO: 制約を満たすサンプルデータセットを作成。
  // if (a < 1 || a > 100) {
  //   return {
  //     data: null,
  //     violation: inputViolationBuilder.invalidNumber(1, 'a', a),
  //   };
  // }

  const b = Number(tmp[4]);
  // TODO: 制約を満たすサンプルデータセットを作成。
  // if (b < 1 || b > 100) {
  //   return {
  //     data: null,
  //     violation: inputViolationBuilder.invalidNumber(1, 'b', b),
  //   };
  // }

  if (lines.length < 2 + 2 * S + C) {
    return {
      data: null,
      violation: inputViolationBuilder.notEnoughData(lines.length + 1),
    };
  }

  const N_sc: number[][] = [];
  let N_sum = 0;
  for (let s = 0; s < S; ++s) {
    tmp = lines[s + 1].split(' ');
    if (tmp.length < C) {
      return {
        data: null,
        violation: inputViolationBuilder.notEnoughData(2 + s),
      };
    }
    N_sc[s] = tmp.map(Number);
    N_sum += N_sc[s].reduce((prev, current) => prev + current, 0);
  }
  // TODO: 制約を満たすサンプルデータセットを作成。
  // if (N_sum < 1000 || N_sum > 5000) {
  //   return {
  //     data: null,
  //     violation: inputViolationBuilder.invalidNumber(-1, 'N_sum', N_sum),
  //   };
  // }

  tmp = lines[S + 1].split(' ');
  if (tmp.length < S) {
    return {
      data: null,
      violation: inputViolationBuilder.notEnoughData(2 + S),
    };
  }
  const K_s = tmp.map(Number);
  // TODO: 制約を満たすサンプルデータセットを作成。
  // for (let i = 0; i < S; ++i) {
  //   if (K_s[i] < 10 || K_s[i] > 200) {
  //     return {
  //       data: null,
  //       violation: inputViolationBuilder.invalidNumber(
  //         2 + S,
  //         `K_${i + 1}`,
  //         K_s[i]
  //       ),
  //     };
  //   }
  // }

  const A_ss: number[][] = [];
  for (let s1 = 0; s1 < S; ++s1) {
    tmp = lines[s1 + S + 2].split(' ');
    if (tmp.length < S) {
      return {
        data: null,
        violation: inputViolationBuilder.notEnoughData(3 + S + s1),
      };
    }
    A_ss[s1] = tmp.map(Number);
    // TODO: 制約を満たすサンプルデータセットを作成。
    // for (let s2 = 0; s2 < S; ++s2) {
    //   if (s1 == s2) continue;
    //   if (A_ss[s1][s2] < 1 || A_ss[s1][s2] > 10) {
    //     return {
    //       data: null,
    //       violation: inputViolationBuilder.invalidNumber(
    //         3 + S + s1,
    //         `A_{${s1 + 1},${s2 + 1}}`,
    //         A_ss[s1][s2]
    //       ),
    //     };
    //   }
    // }
  }
  const B_cc: number[][] = [];
  for (let c1 = 0; c1 < C; ++c1) {
    tmp = lines[c1 + 2 * S + 2].split(' ');
    if (tmp.length < C) {
      return {
        data: null,
        violation: inputViolationBuilder.notEnoughData(3 + 2 * S + c1),
      };
    }
    B_cc[c1] = tmp.map(Number);
    // TODO: 制約を満たすサンプルデータセットを作成。
    // for (let c2 = 0; c2 < C; ++c2) {
    //   if (c1 == c2) continue;
    //   if (B_cc[c1][c2] < 10 || B_cc[c1][c2] > 100) {
    //     return {
    //       data: null,
    //       violation: inputViolationBuilder.invalidNumber(
    //         3 + 2 * S + c1,
    //         `B_{${c1 + 1},${c2 + 1}}`,
    //         B_cc[c1][c2]
    //       ),
    //     };
    //   }
    // }
  }
  return {
    data: {
      S,
      C,
      H,
      initialScore,
      a,
      b,
      N_sc,
      K_s,
      A_ss,
      B_cc,
      N_sum,
    },
    violation: null,
  };
}

export type OutputResult =
  | {
      data: Plan;
      violation: null;
    }
  | {
      data: null;
      violation: Violation;
    };

export function parseOutput(text: string): OutputResult {
  const lines = text.split('\n');
  if (lines.length < 1) {
    return {
      data: null,
      violation: outputViolationBuilder.notEnoughData(1),
    };
  }

  const K = parseInt(lines[0]);
  if (K > 1e6) {
    return {
      data: null,
      violation: outputViolationBuilder.invalidNumber(1, 'K', K),
    };
  }
  if (lines[0].split(' ').length > 1 || K <= 0 || isNaN(K)) {
    return {
      data: null,
      violation: outputViolationBuilder.missingInstructionCount(),
    };
  }

  if (lines.length < K + 1) {
    return {
      data: null,
      violation: outputViolationBuilder.notEnoughData(lines.length + 1),
    };
  }

  const instructions: Instruction[] = [];
  for (let i = 0; i < K; ++i) {
    const tmp = lines[i + 1].split(' ');
    const s = Number(tmp[0]);
    if (s == -2) {
      instructions.push({ s: -2, c: -1 });
    } else if (s == -1) {
      instructions.push({ s: -1, c: -1 });
    } else if (s > 0) {
      if (tmp.length < 2) {
        return {
          data: null,
          violation: outputViolationBuilder.notEnoughData(2 + i),
        };
      }
      const c = Number(tmp[1]);
      instructions.push({ s: s - 1, c: c - 1 });
    } else {
      return {
        data: null,
        violation: outputViolationBuilder.invalidNumber(
          2 + i,
          `x_${i + 1}`,
          lines[i + 1]
        ),
      };
    }
  }
  return {
    data: {
      K,
      instructions,
    },
    violation: null,
  };
}

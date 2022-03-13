export interface Instruction {
  s: number; // 形状 または -1 または -2
  c: number; // 色
}

export interface Plan {
  K: number; // 指示数
  instructions: Instruction[];
}

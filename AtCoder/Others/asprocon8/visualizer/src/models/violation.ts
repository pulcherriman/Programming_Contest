export type FileName = 'input file' | 'output file';
export type ViolationType =
  | NotEnoughDataViolation
  | TooManyDataViolation
  | InvalidNumberViolation
  | MissingInstructionCountViolation
  | NotEnoughHangerViolation
  | NotEnoughIntervalViolation
  | WrongProductCountViolation;

class Violation {
  constructor(public readonly fileName: FileName) {}
}

class ViolationAt extends Violation {
  constructor(fileName: FileName, public readonly line: number) {
    super(fileName);
  }
}

export class NotEnoughDataViolation extends ViolationAt {
  public readonly type = 'NotEnoughDataViolation' as const;
  constructor(fileName: FileName, line: number) {
    super(fileName, line);
  }
}

export class TooManyDataViolation extends ViolationAt {
  public readonly type = 'TooManyDataViolation' as const;
  constructor(fileName: FileName, line: number) {
    super(fileName, line);
  }
}

export class InvalidNumberViolation extends ViolationAt {
  public readonly type = 'InvalidNumberViolation' as const;
  constructor(
    fileName: FileName,
    line: number,
    public readonly variableName: string,
    public readonly invalidValue: number | string
  ) {
    super(fileName, line);
  }
}

export class MissingInstructionCountViolation extends Violation {
  public readonly type = 'MissingInstructionCountViolation' as const;
  constructor() {
    super('output file');
  }
}

export class NotEnoughHangerViolation extends ViolationAt {
  public readonly type = 'NotEnoughHangerViolation' as const;
  constructor(line: number) {
    super('output file', line);
  }
}

export class NotEnoughIntervalViolation extends ViolationAt {
  public readonly type = 'NotEnoughIntervalViolation' as const;
  constructor(line: number) {
    super('output file', line);
  }
}

export class WrongProductCountViolation extends Violation {
  public readonly type = 'WrongProductCountViolation' as const;
  constructor(
    public readonly shape: number,
    public readonly color: number,
    public readonly correctCount: number,
    public readonly wrongCount: number
  ) {
    super('output file');
  }
}

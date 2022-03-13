/* eslint-disable @typescript-eslint/explicit-module-boundary-types */

import {
  FileName,
  InvalidNumberViolation,
  MissingInstructionCountViolation,
  NotEnoughDataViolation,
  NotEnoughHangerViolation,
  NotEnoughIntervalViolation,
  TooManyDataViolation,
  WrongProductCountViolation,
} from '../models/violation';

export class ViolationBuilder {
  constructor(public readonly fileName: FileName) {}

  notEnoughData(line: number) {
    return new NotEnoughDataViolation(this.fileName, line);
  }

  tooManyData(line: number) {
    return new TooManyDataViolation(this.fileName, line);
  }

  invalidNumber(
    line: number,
    variableName: string,
    invalidValue: number | string
  ) {
    return new InvalidNumberViolation(
      this.fileName,
      line,
      variableName,
      invalidValue
    );
  }

  missingInstructionCount() {
    console.assert(
      this.fileName == 'output file',
      'missingInstructionCount called where fileName is input file'
    );
    return new MissingInstructionCountViolation();
  }

  notEnoughHangerViolation(line: number) {
    console.assert(
      this.fileName == 'output file',
      'notEnoughHangerViolation called where fileName is input file'
    );
    return new NotEnoughHangerViolation(line);
  }

  notEnoughIntervalViolation(line: number) {
    console.assert(
      this.fileName == 'output file',
      'notEnoughIntervalViolation called where fileName is input file'
    );
    return new NotEnoughIntervalViolation(line);
  }

  wrongProductCountViolation(
    shape: number,
    color: number,
    correctCount: number,
    wrongCount: number
  ) {
    console.assert(
      this.fileName == 'output file',
      'wrongProductCountViolation called where fileName is input file'
    );
    return new WrongProductCountViolation(
      shape,
      color,
      correctCount,
      wrongCount
    );
  }
}

/* eslint-enable @typescript-eslint/explicit-module-boundary-types */

import * as React from 'react';
import { useSelector } from 'react-redux';
import { useTranslation } from 'react-i18next';

import { State } from '../modules';
import { Metrics } from '../components/molecules';
import { Violation } from '../models';
import '../lib/str-ext';

function getLineStr(line: number, local: string) {
  switch (local) {
    case 'en':
      if (line == 1) {
        return '1st line';
      } else if (line == 2) {
        return '2nd line';
      } else if (line == 3) {
        return '3rd line';
      } else {
        return `${line}th line`;
      }
    case 'ja':
      return `${line}行目`;
  }
}

const wrapperUseTranslation = () => useTranslation();
function getLocalizedMessage(
  violation: Violation,
  t: ReturnType<typeof wrapperUseTranslation>['t'],
  i18n: ReturnType<typeof wrapperUseTranslation>['i18n']
) {
  const lineStr = (line: number) => {
    return getLineStr(line, i18n.language);
  };
  const msg = (msgAfterFileName: string) => {
    return `${violation.fileName}: ${msgAfterFileName}`;
  };

  switch (violation.type) {
    case 'NotEnoughDataViolation':
      return msg(
        `${lineStr(violation.line)}: ${t('violation.notEnoughDataMessage')}`
      );
    case 'TooManyDataViolation':
      return msg(
        `${lineStr(violation.line)}: ${t('violation.tooManyDataMessage')}`
      );
    case 'InvalidNumberViolation':
      return msg(
        `${lineStr(violation.line)}: ${t('violation.invalidNumberMessage')} (${
          violation.variableName
        }=${violation.invalidValue})`
      );
    case 'MissingInstructionCountViolation':
      return msg(`${t('violation.missingInstructionCountMessage')}`);
    case 'NotEnoughHangerViolation':
      return msg(
        `${lineStr(violation.line)}: ${t('violation.notEnoughHangerMessage')}`
      );
    case 'NotEnoughIntervalViolation':
      return msg(
        `${lineStr(violation.line)}: ${t('violation.notEnoughIntervalMessage')}`
      );
    case 'WrongProductCountViolation':
      return msg(
        t('violation.wrongProductCountMessage').format(
          `${violation.shape}`,
          `${violation.color}`,
          `${violation.correctCount}`,
          `${violation.wrongCount}`
        )
      );
    default:
      return 'unknown error';
  }
}

const ConnectedMetrics: React.FC = () => {
  const { t, i18n } = useTranslation();
  const { data, violation } = useSelector((state: State) => state);
  const message = violation ? getLocalizedMessage(violation, t, i18n) : null;
  return <Metrics data={data} violation={{ message }} />;
};

export default ConnectedMetrics;

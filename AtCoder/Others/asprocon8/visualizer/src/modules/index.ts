import { Data, Violation } from '../models';
import { Parser, MetricsUtils } from '../lib';

export type State = {
  data: Data | null;
  violation: Violation | null;
};

export function createInitialState(): State {
  return {
    data: null,
    violation: null,
  };
}

export const RELOAD = 'asprova/data/reload' as const;

// eslint-disable-next-line @typescript-eslint/explicit-module-boundary-types
export function reload(inputText: string, outputText: string) {
  return {
    type: RELOAD,
    payload: {
      inputText,
      outputText,
    },
  };
}

function createState(inputText: string, outputText: string) {
  const inputResult = Parser.parseInput(inputText);
  if (inputResult.violation) {
    return { data: null, violation: inputResult.violation };
  }
  const outputResult = Parser.parseOutput(outputText);
  if (outputResult.violation) {
    return { data: null, violation: outputResult.violation };
  }
  const metricsResult = MetricsUtils.calculate(
    inputResult.data,
    outputResult.data
  );
  if (metricsResult.violation) {
    return { data: null, violation: metricsResult.violation };
  }
  return {
    data: {
      input: inputResult.data,
      plan: outputResult.data,
      metrics: metricsResult.data,
    },
    violation: null,
  };
}

export type Action = Readonly<ReturnType<typeof reload>>;

export default function reducer(
  state = createInitialState(),
  action: Action
): State {
  switch (action.type) {
    case RELOAD:
      return createState(action.payload.inputText, action.payload.outputText);
    default:
      return state;
  }
}

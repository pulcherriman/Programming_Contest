import { InputData } from './input';
import { Plan } from './plan';
import { Metrics } from './metrics';

export interface Data {
  input: InputData;
  plan: Plan;
  metrics: Metrics;
}

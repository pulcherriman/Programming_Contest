import { createStore as create } from 'redux';

import appReducer, { createInitialState } from './modules';

// eslint-disable-next-line @typescript-eslint/explicit-module-boundary-types
export function createStore() {
  return create(appReducer, createInitialState());
}

export default createStore();

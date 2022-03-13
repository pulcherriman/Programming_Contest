import * as React from 'react';
import { useSelector } from 'react-redux';
import { Chart } from '../components/organisms';
import { State } from '../modules';

const ConnectedChart: React.FC = () => {
  const { data, violation } = useSelector((state: State) => state);
  return <Chart data={data} violation={violation} />;
};

export default ConnectedChart;

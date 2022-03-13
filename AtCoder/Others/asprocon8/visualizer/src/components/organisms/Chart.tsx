import * as React from 'react';
import { Box, VStack, useColorMode } from '@chakra-ui/react';
import { Application } from 'pixi.js';

import { Tooltip, ScaleButtons } from '../atoms';
import { ChartView } from '../../lib';
import { Data, Violation } from '../../models';

type Props = {
  data: Data | null;
  violation: Violation | null;
};

const Chart: React.FC<Props> = ({ data, violation }) => {
  const [app, setApp] = React.useState<Application | null>(null);
  const [chartView, setChartView] = React.useState<ChartView | null>(null);
  const [scale, setScale] = React.useState(0);
  const { colorMode } = useColorMode();
  const divRef = React.useRef<HTMLDivElement>(null);

  React.useEffect(() => {
    const currentRef = divRef.current;
    if (!currentRef) return;

    currentRef.innerHTML = '';

    const app = new Application({
      width: currentRef.clientWidth,
      height: currentRef.clientHeight,
      backgroundAlpha: 0,
      antialias: true,
      resizeTo: currentRef,
    });

    currentRef.appendChild(app.view);

    setApp(app);
    setChartView(new ChartView(app));

    return () => {
      app.destroy();
    };
  }, []);

  React.useEffect(() => {
    if (!app) return;
    if (!chartView) return;

    if (violation) {
      chartView.hide();
      return;
    }

    if (!data) {
      return;
    }

    chartView.setColorMode(colorMode);
    chartView.update(data);
    chartView.show();
  }, [chartView, data, violation, colorMode]);

  React.useEffect(() => {
    if (!chartView) return;
    chartView.scale = scale;
  }, [chartView, scale]);

  return (
    <VStack my="2">
      <ScaleButtons scale={scale} setScale={setScale} />
      <Box
        my="8"
        w="100%"
        h="640"
        borderWidth="1px"
        borderRadius="lg"
        ref={divRef}
      ></Box>
      <Tooltip />
    </VStack>
  );
};

export default Chart;

import * as React from 'react';
import { HStack, Spacer, Button } from '@chakra-ui/react';

type Props = {
  scale: number;
  setScale: (value: number) => void;
};

const scaleMin = -20;
const scaleMax = 10;

const ScaleButtons: React.FC<Props> = ({ scale, setScale }) => {
  const onMinusButtonClicked = React.useCallback<
    React.MouseEventHandler<HTMLButtonElement>
  >(() => {
    setScale(Math.max(scale - 1, scaleMin));
  }, [scale, setScale]);

  const onResetButtonClicked = React.useCallback<
    React.MouseEventHandler<HTMLButtonElement>
  >(() => {
    setScale(0);
  }, [scale, setScale]);

  const onPlusButtonClicked = React.useCallback<
    React.MouseEventHandler<HTMLButtonElement>
  >(() => {
    setScale(Math.min(scale + 1, scaleMax));
  }, [scale, setScale]);

  return (
    <HStack w="100%">
      <Spacer />
      <Button size="sm" colorScheme="gray" onClick={onMinusButtonClicked}>
        -
      </Button>
      <Button size="sm" colorScheme="gray" onClick={onResetButtonClicked}>
        .
      </Button>
      <Button size="sm" colorScheme="gray" onClick={onPlusButtonClicked}>
        +
      </Button>
    </HStack>
  );
};

export default ScaleButtons;

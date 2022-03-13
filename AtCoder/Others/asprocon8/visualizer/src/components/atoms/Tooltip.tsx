import * as React from 'react';
import { Box, useColorModeValue } from '@chakra-ui/react';

const Tooltip: React.FC = () => {
  return (
    <Box
      id="tooltip"
      p="4"
      bg={useColorModeValue('bg.light', 'bg.dark')}
      position="absolute"
      visibility="hidden"
      borderWidth="1px"
      borderRadius="lg"
      textAlign="start"
      pointerEvents="none"
    ></Box>
  );
};

export default Tooltip;

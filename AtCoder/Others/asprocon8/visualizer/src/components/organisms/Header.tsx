import * as React from 'react';
import { HStack, Divider, VStack, Spacer } from '@chakra-ui/react';

import { Title, Lang, ThemeButton } from '../atoms';
import { Form, Metrics } from '../../containers';

const Header: React.FC = () => {
  return (
    <VStack alignItems="start">
      <HStack w="100%">
        <Title />
        <Spacer />
        <Lang />
        <ThemeButton />
      </HStack>
      <Form />
      <Divider />
      <Metrics />
    </VStack>
  );
};

export default Header;

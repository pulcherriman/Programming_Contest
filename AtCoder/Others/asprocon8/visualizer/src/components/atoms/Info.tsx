import * as React from 'react';
import {
  Popover,
  PopoverTrigger,
  Button,
  Portal,
  PopoverContent,
  PopoverHeader,
  PopoverCloseButton,
  PopoverBody,
  Box,
  Text,
} from '@chakra-ui/react';
import { InfoIcon } from '@chakra-ui/icons';
import { useTranslation } from 'react-i18next';

import { InputData } from '../../models';

type Props = {
  input: InputData | null;
};

const Info: React.FC<Props> = ({ input }) => {
  const { t } = useTranslation();
  return (
    <Popover>
      <PopoverTrigger>
        <Button
          leftIcon={<InfoIcon />}
          colorScheme="gray"
          size="md"
          isDisabled={input == null}
        >
          info
        </Button>
      </PopoverTrigger>
      <Portal>
        <PopoverContent>
          <PopoverHeader>{t('info.title')}</PopoverHeader>
          <PopoverCloseButton />
          <PopoverBody>
            <Box>
              <Text>
                {`S: ${input?.S} (${t('info.shapeNumDescription')})`}
                <br />
                {`C: ${input?.C} (${t('info.colorNumDescription')})`}
                <br />
                {`H: ${input?.H} (${t('info.hookNumDescription')})`}
                <br />
                {`a: ${input?.a} (${t('info.hangerPenaltyDescription')})`}
                <br />
                {`b: ${input?.b} (${t('info.hookPenaltyDescription')})`}
              </Text>
            </Box>
          </PopoverBody>
        </PopoverContent>
      </Portal>
    </Popover>
  );
};

export default Info;

import * as React from 'react';
import {
  InputGroup,
  InputLeftAddon,
  InputRightAddon,
  SimpleGrid,
  Input,
  useDisclosure,
  HStack,
} from '@chakra-ui/react';
import { useTranslation } from 'react-i18next';

import { Dialog, Info } from '../atoms';
import { Data } from '../../models';

type FormattedResult = {
  score: string;
  hangerSwapCount: string;
  emptyHookCount: string;
  instructionCount: string;
};

function formatNumber(num: number) {
  if (!isFinite(num)) return '<invalid>';
  return num.toString().replace(/(\d)(?=(\d\d\d)+(?!\d))/g, '$1,');
}

type Props = {
  data: Data | null;
  violation: {
    message: string | null;
  };
};

const Metrics: React.FC<Props> = ({ data, violation }) => {
  const { t } = useTranslation();
  const [result, setResult] = React.useState<FormattedResult | null>(null);
  const { isOpen, onOpen, onClose } = useDisclosure();

  React.useEffect(() => {
    if (violation.message) {
      setResult(null);
      onOpen();
      return;
    }

    if (!data) {
      setResult(null);
      return;
    }

    setResult({
      score: formatNumber(data.metrics.score),
      emptyHookCount: formatNumber(data.metrics.emptyHookCount),
      instructionCount: formatNumber(data.metrics.instructionCount),
      hangerSwapCount: formatNumber(data.metrics.hangerSwapCount),
    });
  }, [data, violation]);

  let scoreRightAddon = null;
  if (violation.message) {
    scoreRightAddon = (
      <InputRightAddon bgColor="wa" color="black">
        WA
      </InputRightAddon>
    );
  } else if (result) {
    scoreRightAddon = (
      <InputRightAddon bgColor="ac" color="black">
        AC
      </InputRightAddon>
    );
  }

  return (
    <>
      <SimpleGrid minW="80%" columns={[1, 1, 1, 2]} spacing="4" paddingTop="2">
        <InputGroup>
          <InputLeftAddon>
            {t('metrics.hangerSwappingCountLabel')}
          </InputLeftAddon>
          <Input type="text" isReadOnly value={result?.hangerSwapCount ?? ''} />
        </InputGroup>
        <InputGroup>
          <InputLeftAddon>{t('metrics.numOfEmptyHookLabel')}</InputLeftAddon>
          <Input type="text" isReadOnly value={result?.emptyHookCount ?? ''} />
        </InputGroup>
        <InputGroup>
          <InputLeftAddon>{t('metrics.numOfInstructionsLabel')}</InputLeftAddon>
          <Input
            type="text"
            isReadOnly
            value={result?.instructionCount ?? ''}
          />
        </InputGroup>
        <HStack>
          <InputGroup>
            <InputLeftAddon bgColor="primary">
              {t('metrics.scoreLabel')}
            </InputLeftAddon>
            <Input type="text" isReadOnly value={result?.score ?? ''} />
            {scoreRightAddon}
          </InputGroup>
          <Info input={data?.input ?? null} />
        </HStack>
      </SimpleGrid>
      <Dialog title="Violation" isOpen={isOpen} onClose={onClose}>
        {violation.message}
      </Dialog>
    </>
  );
};

export default Metrics;

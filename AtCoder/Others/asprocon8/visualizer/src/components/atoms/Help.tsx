import * as React from 'react';
import {
  Button,
  Heading,
  UnorderedList,
  ListItem,
  Image,
  useDisclosure,
} from '@chakra-ui/react';
import { QuestionIcon } from '@chakra-ui/icons';
import { useTranslation } from 'react-i18next';

import { Dialog } from '.';

const Help: React.FC = () => {
  const { t } = useTranslation();
  const { isOpen, onOpen, onClose } = useDisclosure();
  const onHelpButtonClicked = React.useCallback<
    React.MouseEventHandler<HTMLButtonElement>
  >(() => {
    onOpen();
  }, [onOpen]);

  return (
    <>
      <Button
        leftIcon={<QuestionIcon />}
        marginStart="4"
        colorScheme="gray"
        size="md"
        onClick={onHelpButtonClicked}
      >
        help
      </Button>
      <Dialog title="Help" isOpen={isOpen} onClose={onClose} size="3xl">
        <Heading my="2" as="h6" size="md">
          {t('help.usage.title')}
        </Heading>
        <UnorderedList>
          <ListItem>{t('help.usage.texts.0')}</ListItem>
          <Image src="chart.png" alt="chart.png" />
          <ListItem>{t('help.usage.texts.1')}</ListItem>
          <ListItem>{t('help.usage.texts.2')}</ListItem>
          <ListItem>{t('help.usage.texts.3')}</ListItem>
          <ListItem>{t('help.usage.texts.4')}</ListItem>
          <ListItem>{t('help.usage.texts.5')}</ListItem>
          <ListItem>{t('help.usage.texts.6')}</ListItem>
        </UnorderedList>
        <Heading marginTop="4" marginBottom="2" as="h6" size="md">
          {t('help.caution.title')}
        </Heading>
        <UnorderedList>
          <ListItem>{t('help.caution.texts.0')}</ListItem>
          <ListItem>{t('help.caution.texts.1')}</ListItem>
          <ListItem>{t('help.caution.texts.2')}</ListItem>
          <ListItem>{t('help.caution.texts.3')}</ListItem>
        </UnorderedList>
      </Dialog>
    </>
  );
};

export default Help;

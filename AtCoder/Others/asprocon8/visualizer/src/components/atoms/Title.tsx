import * as React from 'react';
import { Heading } from '@chakra-ui/react';
import { useTranslation } from 'react-i18next';

const Title: React.FC = () => {
  const { t } = useTranslation();
  return (
    <Heading as="h1" size="lg">
      {t('header.title')}
    </Heading>
  );
};

export default Title;

import * as React from 'react';
import styled from '@emotion/styled';
import { useTheme, useColorModeValue } from '@chakra-ui/react';
import { useTranslation } from 'react-i18next';

const Lang: React.FC = () => {
  const { i18n } = useTranslation();
  const theme = useTheme();
  const onClick = React.useCallback<
    React.MouseEventHandler<HTMLButtonElement>
  >(() => {
    i18n.changeLanguage(i18n.language == 'en' ? 'ja' : 'en');
  }, [i18n]);

  const lang = i18n.language;
  const selectedColor = useColorModeValue(
    theme.colors.black,
    theme.colors.white
  );
  const unSelectedColor = useColorModeValue(
    theme.colors.blackAlpha[600],
    theme.colors.whiteAlpha[400]
  );

  return (
    <Button onClick={onClick}>
      <Span color={lang == 'ja' ? selectedColor : unSelectedColor}>JA</Span> -{' '}
      <Span color={lang == 'en' ? selectedColor : unSelectedColor}>EN</Span>
    </Button>
  );
};

const Button = styled.button({
  ':before': {
    content: `""`,
    paddingLeft: '0.5rem',
  },
  ':after': {
    content: `""`,
    paddingRight: '0.5rem',
  },
});

type SpanProps = {
  color: string;
};

const Span = styled.span<SpanProps>(({ color }) => ({
  color: color,
}));

export default Lang;

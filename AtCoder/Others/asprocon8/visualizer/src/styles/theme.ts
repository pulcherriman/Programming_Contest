import { extendTheme, type ThemeConfig } from '@chakra-ui/react';
import { mode } from '@chakra-ui/theme-tools';

const colors = {
  bg: {
    light: '#fffffe',
    dark: '#0f0e17',
  },
  primary: '#e53170',
  secondary: '#a7a9be',
  ac: '#5cb85c',
  wa: '#f0ad4e',
};

const styles = {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  global: (props: any) => ({
    body: {
      bg: mode('bg.light', 'bg.dark')(props),
    },
  }),
};

const components = {
  Popover: {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    baseStyle: (props: any) => ({
      content: {
        bg: mode('bg.light', 'bg.dark')(props),
      },
    }),
  },
  Modal: {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    baseStyle: (props: any) => ({
      dialog: {
        bg: mode('bg.light', 'bg.dark')(props),
      },
    }),
  },
};

const config: ThemeConfig = {
  initialColorMode: 'light',
  useSystemColorMode: false,
};

const theme = extendTheme({
  colors,
  styles,
  components,
  config,
});

export default theme;

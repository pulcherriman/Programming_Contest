import * as React from 'react';
import { Provider } from 'react-redux';
import { ChakraProvider, Box } from '@chakra-ui/react';
import { I18nextProvider } from 'react-i18next';
import i18n from './locales/config';
import store from './store';
import theme from './styles/theme';

import { Header } from './components/organisms';
import { Chart } from './containers';

const App: React.FC = () => {
  return (
    <I18nextProvider i18n={i18n}>
      <Provider store={store}>
        <ChakraProvider theme={theme}>
          <Box mx="4%" py="16">
            <Header />
            <Chart />
          </Box>
        </ChakraProvider>
      </Provider>
    </I18nextProvider>
  );
};

export default App;

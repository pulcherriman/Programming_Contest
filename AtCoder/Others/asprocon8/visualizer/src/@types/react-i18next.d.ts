import 'react-i18next';

import en from '../locales/en.json';
import ja from '../locales/ja.json';

declare module 'react-i18next' {
  interface CustomTypeOptions {
    defaultNS: 'en';
    resources: {
      en: typeof en;
      ja: typeof ja;
    };
  }
}

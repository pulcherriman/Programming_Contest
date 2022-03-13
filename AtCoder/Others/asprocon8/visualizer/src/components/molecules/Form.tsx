import * as React from 'react';
import { Box, Button, SimpleGrid } from '@chakra-ui/react';
import { RepeatIcon } from '@chakra-ui/icons';

import { FileInput, Help } from '../atoms';

type TmpData = {
  inputText: string | null;
  outputText: string | null;
};

interface ReloadAction {
  (inputText: string, outputText: string): void;
}

type Props = {
  actions: {
    reload: ReloadAction;
  };
};

const Form: React.FC<Props> = ({ actions }) => {
  const [tmpData, setTmpData] = React.useState<TmpData>({
    inputText: null,
    outputText: null,
  });
  const inputFileRef = React.useRef<HTMLInputElement>(null);
  const outputFileRef = React.useRef<HTMLInputElement>(null);

  const onInputFileChanged = React.useCallback(
    (text: string) => {
      setTmpData({ inputText: text, outputText: tmpData.outputText });
      if (!tmpData.inputText && tmpData.outputText) {
        // first load
        actions.reload(text, tmpData.outputText);
      }
    },
    [tmpData, setTmpData, actions]
  );

  const onOutputFileChanged = React.useCallback(
    (text: string) => {
      setTmpData({ inputText: tmpData.inputText, outputText: text });
      if (!tmpData.outputText && tmpData.inputText) {
        // first load
        actions.reload(tmpData.inputText, text);
      }
    },
    [tmpData, setTmpData, actions]
  );

  const onReloadButtonClicked = React.useCallback<
    React.MouseEventHandler<HTMLButtonElement>
  >(async () => {
    const inputText = await inputFileRef.current?.files?.item(0)?.text();
    if (!inputText) return;
    const outputText = await outputFileRef.current?.files?.item(0)?.text();
    if (!outputText) return;

    actions.reload(inputText, outputText);
  }, [actions]);

  const isButtonDisabled = !tmpData.inputText || !tmpData.outputText;

  return (
    <SimpleGrid columns={[1, 1, 2, 2, 3]} spacing="4" py="2" alignItems="end">
      <FileInput
        title="input"
        onChange={onInputFileChanged}
        refInput={inputFileRef}
      />
      <FileInput
        title="output"
        onChange={onOutputFileChanged}
        refInput={outputFileRef}
      />
      <Box>
        <Button
          leftIcon={<RepeatIcon />}
          colorScheme="blue"
          size="md"
          isDisabled={isButtonDisabled}
          onClick={onReloadButtonClicked}
        >
          reload
        </Button>
        <Help />
      </Box>
    </SimpleGrid>
  );
};

export default Form;

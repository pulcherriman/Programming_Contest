import * as React from 'react';
import { VStack, Text, Input } from '@chakra-ui/react';

type Props = {
  title: string;
  onChange: (text: string) => void;
  refInput: React.RefObject<HTMLInputElement>;
};

const FileInput: React.FC<Props> = ({ title, onChange, refInput }) => {
  const onFileChanged = React.useCallback<
    React.ChangeEventHandler<HTMLInputElement>
  >(
    async (e) => {
      const file = e.target.files?.item(0);
      if (!file) return;
      const text = await file.text();
      onChange(text);
    },
    [onChange]
  );

  return (
    <VStack alignItems="start" spacing="2">
      <Text size="sm">{title}</Text>
      <Input
        type="file"
        variant="outline"
        h="12"
        w="80"
        paddingTop="2.5"
        onChange={onFileChanged}
        ref={refInput}
      />
    </VStack>
  );
};

export default FileInput;

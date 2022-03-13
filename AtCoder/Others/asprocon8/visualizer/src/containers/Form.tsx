import * as React from 'react';
import { useDispatch } from 'react-redux';
import { reload } from '../modules';
import { Form } from '../components/molecules';

const ConnectedForm: React.FC = () => {
  const dispatch = useDispatch();

  const actions = React.useMemo(
    () => ({
      reload(inputText: string, outputText: string) {
        dispatch(reload(inputText, outputText));
      },
    }),
    [dispatch]
  );

  return <Form actions={actions} />;
};

export default ConnectedForm;

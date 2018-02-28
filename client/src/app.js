// @flow
import React from 'react';
import { render } from 'react-dom';

import Environment from './env';
import App from './ui/App';

const root = document.querySelector('#root');
if (root !== null) {
  render(
    <App env={new Environment()} />,
    root,
  );
}

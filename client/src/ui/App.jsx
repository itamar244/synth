// @flow
import React, { Component } from 'react';

import KeyboardCommunication from './KeyboardCommunication';
import type Environment from '../env';

type Props = {
  env: Environment,
};

export default class App extends Component<Props> {
  render() {
    return (
      <div>
        <KeyboardCommunication {...this.props} />
      </div>
    );
  }
}

// @flow
import React, { Component } from 'react';
import { PolySynth, Distortion } from 'tone';

import KeyboardCommunication from './KeyboardCommunication';
import type Environment from '../env';
import * as msg from '../serialport_messages';

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

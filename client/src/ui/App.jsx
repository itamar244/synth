// @flow
import React, { Component } from 'react';

import KeyboardCommunication, {
  type Props as KeyboardCommunicationProps,
} from './KeyboardCommunication';

export default class App extends Component<KeyboardCommunicationProps> {
  render() {
    return (
      <div>
        <KeyboardCommunication {...this.props} />
      </div>
    );
  }
}

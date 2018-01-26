// @flow
import React, { Component } from 'react';

import * as keyboards from '../create_synth_keyboard';

export type Props = {
  synth: Object,
  port?: Object,
};

type KeyboardType = 'synth' | 'port';

type State = {
  type: KeyboardType,
  detach: null | () => mixed,
};

export default class KeyboardCommunication extends Component<Props, State> {
  state = {
    type: 'synth',
    detach: null,
  }

  toggleType = () => {
    this.setState((prevState: State) => {
      const type = this.otherType(prevState);
      if (prevState.detach !== null) prevState.detach();

      return {
        type,
        detach: this.attachSynthKeyboard(type),
      };
    });
  }

  otherType(state: State = this.state): KeyboardType {
    return state.type === 'synth' ? 'port' : 'synth';
  }

  attachSynthKeyboard(type: KeyboardType) {
    if (type === 'synth') {
      return keyboards.localSynthKeyboard(this.props.synth);
    }
    if (this.props.port != null) {
      return keyboards.serialPortSynthKeyboard(this.props.port);
    }
    return null;
  }

  componentDidMount() {
    this.setState({
      detach: this.attachSynthKeyboard(this.state.type),
    });
  }

  render() {
    return (
      <button onClick={this.toggleType}>
        switch to {this.otherType()}
      </button>
    );
  }
}

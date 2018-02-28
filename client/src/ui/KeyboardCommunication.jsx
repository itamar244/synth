// @flow
import React, { Component } from 'react';

import * as keyboards from '../create_synth_keyboard';
import Environment from '../env';

export type Props = {
  env: Environment,
};

type KeyboardType = 'synth' | 'port';

type State = {
  type: KeyboardType,
  detach: () => mixed,
};

const otherType = type => type === 'synth' ? 'port' : 'synth';

export default class KeyboardCommunication extends Component<Props, State> {
  state = {
    type: 'synth',
    detach: this.attachSynthKeyboard('synth'),
  };

  toggleType = () => {
    this.setState((prevState: State) => {
      const type = otherType(prevState.type);
      setTimeout(prevState.detach);

      return {
        type,
        detach: this.attachSynthKeyboard(type),
      };
    });
  };

  attachSynthKeyboard(type: KeyboardType) {
    switch (type) {
      case 'synth':
        return keyboards.localSynthKeyboard(this.props.env);
      case 'port':
        return keyboards.serialPortSynthKeyboard(this.props.env.port);
      default:
        throw TypeError(`type '${type}' shoud only be of 'synth' or 'port'`)
    }
  }

  render() {
    return (
      <button onClick={this.toggleType}>
        Switch to {otherType(this.state.type)}
      </button>
    );
  }
}

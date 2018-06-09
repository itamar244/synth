// @flow
import type Environment from '../env';
import * as keyboard from '../create_synth_keyboard.js'
import ToggleButton from './toggle_button';

export default class App extends HTMLElement {
  button: ToggleButton<'synth' | 'port'>;
  detach = null;
  paragraph = document.createElement('p');

  constructor(env: Environment) {
    super();
    this.button = new ToggleButton(['synth', 'port'], {
      synth: () => {
        if (this.detach !== null) setTimeout(this.detach);
        this.detach = keyboard.serialPortSynthKeyboard(env.port);
      },

      port: () => {
        if (this.detach !== null) setTimeout(this.detach);
        this.detach = keyboard.localSynthKeyboard(env);
      },
    });
    this.append(this.button, this.paragraph);
    env.on('recording-change', this.onRecordingChange);
  }

  onRecordingChange = (isStarted: bool) => {
    this.paragraph.textContent =
      isStarted ? 'Started Recording' : '';
  }
}

customElements.define('sy-app', App);

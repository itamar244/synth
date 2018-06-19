// @flow
import type Environment from '../env';
import * as keyboard from '../create_synth_keyboard.js'
import ToggleButton from './toggle_button';

export default class App extends HTMLElement {
  button: ToggleButton<'synth' | 'port'>;
  env: Environment;
  detach = null;
  paragraph = document.createElement('p');

  constructor(env: Environment) {
    super();
    this.env = env
    this.button = new ToggleButton(['port', 'synth'], {
      synth: this.changeKeyboardType(keyboard.localSynthKeyboard),

      port: this.changeKeyboardType(keyboard.serialPortSynthKeyboard),
    });

    this.append(this.button, this.paragraph);
    this.env.on('recording-change', this.onRecordingChange);
  }

  changeKeyboardType = (handler: typeof keyboard.localSynthKeyboard) => () => {
    if (this.detach !== null) setTimeout(this.detach);
    this.detach = handler(this.env);
  }

  onRecordingChange = (isStarted: bool) => {
    this.paragraph.textContent =
      isStarted ? 'Started Recording' : '';
  }
}

customElements.define('sy-app', App);

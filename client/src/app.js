// @flow
import Environment from './env';
import * as keyboard from './create_synth_keyboard.js'
import ToggleButton from './ui/toggle_button';

const env = new Environment();
let detach = null;

const root = document.querySelector('#root');
if (root !== null) {
  root.append(new ToggleButton(['synth', 'port'], {
    synth() {
      if (detach !== null) setTimeout(detach);
      detach = keyboard.serialPortSynthKeyboard(env.port);
    },

    port() {
      if (detach !== null) setTimeout(detach);
      detach = keyboard.localSynthKeyboard(env);
    }
  }));
}

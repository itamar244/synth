// @flow
import { arrayToMap } from './utils';
import parseToNote from './parse_to_note';
import type Environment from './env';
import type { SerialPort } from './serialport';
import * as msg from './serialport_messages';

// KEYS:
// C    Db   D    Eb   E    F    Gb   G    Ab   A    Bb   B    C
const KEY_VALUES = arrayToMap([
  'z', 's', 'x', 'd', 'c', 'v', 'g', 'b', 'h', 'n', 'j', 'm',
  'q', '2', 'w', '3', 'e', 'r', '5', 't', '6', 'y', '7', 'u', 'i',
]);


const attachKeyListeners = (onKeyDown, onKeyUp) => {
  const pressedKeys = new Set();
  const callOnKeyDownEvents = (key, options) => {
    for (const option of options) {
      if (key === option[0]) {
        onKeyDown(msg[option[1]], 0);
        return;
      }
    }
  }

  const keydown = ({ key }: KeyboardEvent) => {
    const tone = KEY_VALUES.get(key);

    if (tone != null) {
      if (!pressedKeys.has(tone)) {
        pressedKeys.add(tone);
        onKeyDown(msg.ADD_TONE, tone);
      }
    } else if (pressedKeys.size === 0) {
      callOnKeyDownEvents(key, [
        ['-', 'DECREMENT_OCTAVE'],
        ['=', 'INCREMENT_OCTAVE'],
        ['[', 'SWITCH_BACKWARD_SYNTH_TYPE'],
        [']', 'SWITCH_FORWARD_SYNTH_TYPE'],
        ['0', 'RESET_STORE'],
      ]);
    }
  };

  const keyup = ({ key }: KeyboardEvent) => {
    const tone = KEY_VALUES.get(key);

    if (tone != null) {
      pressedKeys.delete(tone);
      onKeyUp(tone);
    }
  };

  document.addEventListener('keyup', keyup);
  document.addEventListener('keydown', keydown);

  return () => {
    pressedKeys.forEach(onKeyUp);
    document.removeEventListener('keyup', keyup);
    document.removeEventListener('keydown', keydown);
  };
};

export function serialPortSynthKeyboard(port: SerialPort) {
  return attachKeyListeners(
    (type, tone) => port.send(type, tone),
    tone => port.send(msg.REMOVE_TONE, tone),
  );
}

export function localSynthKeyboard(env: Environment) {
  const getTone = tone => tone + currentOctave * 12;
  let currentOctave = 4;

  return attachKeyListeners(
    (type, tone) => {
      if (type === msg.DECREMENT_OCTAVE) {
        currentOctave--;
      } else if (type === msg.INCREMENT_OCTAVE) {
        currentOctave++;
      } else {
        env.handleMessage(type, getTone(tone));
      }
    },
    tone => env.handleMessage(msg.REMOVE_TONE, getTone(tone)),
  );
}

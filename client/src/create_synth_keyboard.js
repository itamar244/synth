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

const callOnKeyDownEvents = (key, callback, options) => {
  for (const option of options) {
    if (key === option[0]) {
      callback(msg[option[1]]);
      return;
    }
  }
}

const attachKeyListeners = (onKeyDown, onKeyUp, onInternalKeyDown) => {
  const pressedKeys = new Set();

  const keydown = ({ key }: KeyboardEvent) => {
    const note = KEY_VALUES.get(key);

    if (note != null) {
      if (!pressedKeys.has(note)) {
        pressedKeys.add(note);
        onKeyDown(msg.ADD_NOTE, note);
      }
    } else if (pressedKeys.size === 0) {
      callOnKeyDownEvents(key, type => onKeyDown(type, 0), [
        ['-', 'DECREMENT_OCTAVE'],
        ['=', 'INCREMENT_OCTAVE'],
        ['0', 'RESET_STORE'],
        [';', 'START_RECORDING'],
        ["'", 'STOP_RECORDING'],
      ]);
      callOnKeyDownEvents(key, onInternalKeyDown, [
        ['[', 'SWITCH_BACKWARD_SYNTH_TYPE'],
        [']', 'SWITCH_FORWARD_SYNTH_TYPE'],
      ]);
    }
  };

  const keyup = ({ key }: KeyboardEvent) => {
    const note = KEY_VALUES.get(key);

    if (note != null) {
      pressedKeys.delete(note);
      onKeyUp(note);
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

export function serialPortSynthKeyboard(env: Environment) {
  return attachKeyListeners(
    (type, note) => env.port.send(type, note),
    note => env.port.send(msg.REMOVE_NOTE, note),
    type => env.internalMessage(type),
  );
}

export function localSynthKeyboard(env: Environment) {
  const getNote = note => note + currentOctave * 12;
  let currentOctave = 4;

  return attachKeyListeners(
    (type, note) => {
      if (type === msg.DECREMENT_OCTAVE) {
        currentOctave--;
      } else if (type === msg.INCREMENT_OCTAVE) {
        currentOctave++;
      } else {
        env.handleMessage(type, getNote(note));
      }
    },
    note => env.handleMessage(msg.REMOVE_NOTE, getNote(note)),
    type => env.internalMessage(type),
  );
}

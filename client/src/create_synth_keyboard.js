// @flow
import { arrayToMap } from './utils';
import parseToNote from './parse_to_note';

// NOTES:
// C    Db   D    Eb    E   F    Gb   G    Ab   A    Bb   B    C
const KEY_VALUES = arrayToMap([
  'z', 's', 'x', 'd', 'c', 'v', 'g', 'b', 'h', 'n', 'j', 'm',
  'q', '2', 'w', '3', 'e', 'r', '5', 't', '6', 'y', '7', 'u', 'i',
]);
const REMOVE_TONE = 0;
const ADD_TONE = 1;
const DECREMENT_OCTAVE = 2;
const INCREMENT_OCTAVE = 3;

const attachKeyListeners = (onKeyDown, onKeyUp) => {
  const pressedKeys = new Set();

  const keydown = ({ key }: KeyboardEvent) => {
    const tone = KEY_VALUES.get(key);

    if (tone != null) {
      if (!pressedKeys.has(tone)) {
        pressedKeys.add(tone);
        onKeyDown(ADD_TONE, tone);
      }
    } else if (pressedKeys.size === 0) {
      if (key === '-' || key === '_') {
        onKeyDown(DECREMENT_OCTAVE, 0);
      } else if (key === '=' || key === '+') {
        onKeyDown(INCREMENT_OCTAVE, 0);
      }
    }
  };

  const keyup = (event: KeyboardEvent) => {
    const tone = KEY_VALUES.get(event.key);

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

export const serialPortSynthKeyboard = (port: Object) =>
  attachKeyListeners(
    (type, tone) => port.write([type, tone]),
    tone => port.write([REMOVE_TONE, tone]),
  );

const getNote = tone => parseToNote(tone + currentOctave * 12);
let currentOctave = 3;

export const localSynthKeyboard = (synth: Object) =>
  attachKeyListeners(
    (type, tone) => {
      switch (type) {
        case ADD_TONE: synth.triggerAttack(getNote(tone)); break;
        case DECREMENT_OCTAVE: currentOctave--; break;
        case INCREMENT_OCTAVE: currentOctave++; break;
      }
    },
    tone => synth.triggerRelease(getNote(tone)),
  );

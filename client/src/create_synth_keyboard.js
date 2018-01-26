// @flow
import parseNote from './parse_note';

// NOTES:
// C    Db   D    Eb    E   F    Gb   G    Ab   A    Bb   B    C
const KEY_VALUES = [
  'z', 's', 'x', 'd', 'c', 'v', 'g', 'b', 'h', 'n', 'j', 'm',
  'q', '2', 'w', '3', 'e', 'r', '5', 't', '6', 'y', '7', 'u', 'i',
];
const REMOVE_TONE = 0;
const ADD_TONE = 1;
const DECREMENT_OCTAVE = 2;
const INCREMENT_OCTAVE = 3;

const keyListener =
  (listener: (number, string) => mixed) => (event: KeyboardEvent) =>
    listener(KEY_VALUES.indexOf(event.key.toLowerCase()), event.key);

const attachKeyListeners = (
  onKeyDown: (type: number, tone: number) => mixed,
  onKeyUp: (tone: number) => mixed,
) => {
  const pressedKeys: Set<number> = new Set();

  const keydown = keyListener((tone, key) => {
    if (tone !== -1) {
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
  });

  const keyup = keyListener((tone) => {
    if (tone !== -1) {
      pressedKeys.delete(tone);
      onKeyUp(tone);
    }
  });

  document.addEventListener('keyup', keyup);
  document.addEventListener('keydown', keydown);

  return () => {
    pressedKeys.forEach(onKeyUp);
    document.removeEventListener('keyup', keyup);
    document.removeEventListener('keydown', keydown);
  };
}

/**
 * create a keyboard communication with the arduino device
 * @param {SerialPort} port
 */
export const serialPortSynthKeyboard = (port: Object) =>
  attachKeyListeners(
    (type, tone) => port.write([type, tone]),
    tone => port.write([REMOVE_TONE, tone]),
  );


const getNote = tone => parseNote(tone + currentOctave * 12);
let currentOctave = 3;

/**
 * create a keyboard communication with the synthesizer master
 * @param {PolySynth} synth
 */
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

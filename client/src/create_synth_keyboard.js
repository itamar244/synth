// @flow
const KEY_VALUES = [
// NOTES:
// C    Db   D    Eb    E   F    Gb   G    Ab   A    Bb   B    C
  'z', 's', 'x', 'd', 'c', 'v', 'g', 'b', 'h', 'n', 'j', 'm',
  'q', '2', 'w', '3', 'e', 'r', '5', 't', '6', 'y', '7', 'u', 'i'
];
const REMOVE_TONE = 0;
const ADD_TONE = 1;
const DECREMENT_OCTAVE = 2;
const INCREMENT_OCTAVE = 3;

function getNoteFromKey(key: string): null | number {
  const indexOfKey = KEY_VALUES.indexOf(key.toLowerCase());
  return indexOfKey > -1 ? indexOfKey : null;
}

/**
 * create a keyboard communication with the arduino device
 * @param {SerialPort} port
 */
export default function createSynthKeyboard(port: Object) {
  const PRESSED_KEYS = [];

  const writeOctaveStateChange = (messageType: number) => {
    if (PRESSED_KEYS.length === 0) {
      port.write([messageType, 0]);
    }
  }

  document.addEventListener('keydown', (event: KeyboardEvent) => {
    const { key } = event;
    const note = getNoteFromKey(key);

    if (note !== null && !PRESSED_KEYS.includes(note)) {
      PRESSED_KEYS.push(note);
      port.write([ADD_TONE, note]);
    } else if (key === '-' || key === '_') {
      writeOctaveStateChange(DECREMENT_OCTAVE);
    } else if (key === '=' || key === '+') {
      writeOctaveStateChange(INCREMENT_OCTAVE);
    }
  });

  document.addEventListener('keyup', (event: KeyboardEvent) => {
    const note = getNoteFromKey(event.key);

    if (note !== null) {
      PRESSED_KEYS.splice(PRESSED_KEYS.indexOf(note), 1);
      port.write([REMOVE_TONE, note]);
    }
  });
}

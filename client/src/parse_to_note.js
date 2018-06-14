// @flow
const NOTES = ['C', 'Db', 'D', 'Eb', 'E', 'F', 'Gb', 'G', 'Ab', 'A', 'Bb', 'B'];

/**
 * receives a number and returns its representing key
 * in the following format: <KEY><OCTAVE>
 */
export default (note: number): string =>
  NOTES[note % 12] + String(note / 12 | 0);

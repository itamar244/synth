// @flow
const NOTES = ['C', 'Db', 'D', 'Eb', 'E', 'F', 'Gb', 'G', 'Ab', 'A', 'Bb', 'B'];

/**
 * receives a number and returns its representing key
 * in the following format: <KEY><OCTAVE>
 */
export default (tone: number): string =>
  NOTES[tone % 12] + String(Math.floor(tone / 12));

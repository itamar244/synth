const NOTES = ['C', 'Db', 'D', 'Eb', 'E', 'F', 'Gb', 'G', 'Ab', 'A', 'Bb', 'B'];

export default function parseNote(num) {
  return NOTES[num % 12] + Math.floor(num / 12);
}

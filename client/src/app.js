// @flow
import { PolySynth, Distortion } from 'tone';
import SerialPort, { parsers } from 'serialport';
import parseNote from './parse_note';
import createSynthKeyboard from './create_synth_keyboard';

const port = new SerialPort('/dev/ttyACM0');
const parser = port.pipe(new parsers.ByteLength({ length: 2 }));
const dist = new Distortion(0.8).toMaster();
const synth = new PolySynth()
    .set({
      oscillator: {
        type: 'sine',
      }
    })
    .connect(dist)
    .toMaster();

createSynthKeyboard(port);

parser.on('data', (data: Buffer) => {
  switch (data[0]) {
    case 1:
      synth.triggerAttack(parseNote(data[1]));
      break;
    case 0:
      synth.triggerRelease(parseNote(data[1]));
      break;
  }
});

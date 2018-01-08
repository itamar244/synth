import { PolySynth, Distortion } from 'tone';
import SerialPort, { parsers } from 'serialport';
import parseNote from './parse_note';

const port = new SerialPort('/dev/ttyACM0');
const parser = port.pipe(new parsers.ByteLength({ length: 2 }));
// const dist = new Distortion(0.8).toMaster();
const synth =
  new PolySynth()
    .set({
      oscillator: {
        type: 'sine',
      }
    })
    // .connect(dist)
    .toMaster();
window.synth = synth;

parser.on('data', (data) => {
  // console.log(data);
  const num = data[1];
  switch (data[0]) {
    case 1:
      synth.triggerAttack(parseNote(num));
      break;
    case 0:
      synth.triggerRelease(parseNote(num));
      break;
  }
});

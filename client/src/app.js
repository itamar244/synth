// @flow
import React from 'react';
import { render } from 'react-dom';
import { PolySynth, Distortion } from 'tone';
import SerialPort, { parsers } from 'serialport';

import App from './ui/App';
import parseNote from './parse_note';

let port;
try {
  port = new SerialPort('/dev/ttyACM0');
  const parser = port.pipe(new parsers.ByteLength({ length: 2 }));

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
} catch (e) {}

const dist = new Distortion(0.2).toMaster();
const synth = new PolySynth()
    .set({
      oscillator: {
        type: 'sine',
      }
    })
    .connect(dist)
    .toMaster();

const root = document.querySelector('#root');
if (root !== null) {
  render(
    <App port={port} synth={synth} />,
    root,
  );
}

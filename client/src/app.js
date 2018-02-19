// @flow
import React from 'react';
import { render } from 'react-dom';
import { PolySynth, Distortion } from 'tone';
import SerialPort, { parsers } from 'serialport';

import App from './ui/App';
import parseToNote from './parse_to_note';

let port;
try {
  port = new SerialPort('/dev/ttyACM0');
  const parser = port.pipe(new parsers.ByteLength({ length: 2 }));

  parser.on('data', (data: Buffer) => {
    switch (data[0]) {
      case 1:
        synth.triggerAttack(parseToNote(data[1]));
        break;
      case 0:
        synth.triggerRelease(parseToNote(data[1]));
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

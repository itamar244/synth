// @flow
import EventEmitter from 'events';
import {
  PolySynth,
  Synth,
  FMSynth,
  DuoSynth,
} from 'tone';

import parseToNote from './parse_to_note';
import { circularIndex } from './utils';
import createSerialPort from './serialport';
import * as msg from './serialport_messages';

const SYNTHES = [
  Synth,
  FMSynth,
  DuoSynth,
];

export default class Environment extends EventEmitter {
  synth: PolySynth;
  port = createSerialPort();
  curSynth = 0;

  constructor() {
    super();
    this.initSynth();
    this.port.subscribe(this.handleMessage)
  }

  updatePolySynth(change: number) {
    this.curSynth = circularIndex(this.curSynth, change, SYNTHES.length);
    this.initSynth();
  }

  initSynth() {
    this.synth = new PolySynth(4, SYNTHES[this.curSynth])
      .set('oscillator', { type: 'sine' })
      .toMaster();
  }

  handleMessage = (type: number, data: number) => {
    switch (type) {
      case msg.REMOVE_TONE:
        this.synth.triggerRelease(parseToNote(data));
        break;
      case msg.ADD_TONE:
        this.synth.triggerAttack(parseToNote(data));
        break;
      case msg.LOG_DATA:
        console.log(`loged ${data}`);
        break;
      case msg.SWITCH_BACKWARD_SYNTH_TYPE:
        this.updatePolySynth(-1);
        break;
      case msg.SWITCH_FORWARD_SYNTH_TYPE:
        this.updatePolySynth(1);
        break;
      case msg.START_RECORDING:
        this.emit('recording-change', true);
        break;
      case msg.STOP_RECORDING:
        this.emit('recording-change', false);
        break;
    }
  }
}

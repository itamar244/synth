// @flow
import SerialPortClass, { parsers } from 'serialport';

import Environment from './env';

type RequestHandler = (type: number, data: number) => mixed;
export type SerialPort = {
  send: RequestHandler,
  subscribe(listener: RequestHandler): mixed,
}

export default function createSerialPort(): SerialPort {
  const port = new SerialPortClass('/dev/ttyACM0');
  const parser = port.pipe(new parsers.ByteLength({ length: 2 }));

  return {
    send: (type, data) => port.write([type, data]),
    subscribe: listener =>
      parser.on('data', data => listener(data[0], data[1])),
  }
}

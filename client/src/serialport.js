// @flow
import os from 'os';
import SerialPortClass, { parsers } from 'serialport';

type RequestHandler = (type: number, data: number) => mixed;

export type SerialPort = {
  +send: RequestHandler,
  +subscribe: (listener: RequestHandler) => mixed,
}

function createSerialPortForPath(path: string): SerialPort {
  const port = new SerialPortClass(path);
  const parser = port.pipe(new parsers.ByteLength({ length: 2 }));

  return {
    send: (type, data) => port.write([type, data]),
    subscribe: listener =>
      parser.on('data', data => listener(data[0], data[1])),
  };
}

export default function createSerialPort(): SerialPort {
  const platform = os.platform();

  return createSerialPortForPath(
    platform === 'win32' ? 'COM5' : '/dev/ttyACM0',
  );
}

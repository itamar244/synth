// @flow
import zmq from 'zeromq';

type RequestHandler = (type: number, data: number) => mixed;

export type SerialPort = {
  +send: RequestHandler,
  +subscribe: (listener: RequestHandler) => mixed,
}

export default function createSerialPort(): SerialPort {
  const puller = zmq.socket('pull');
  puller.connect('tcp://127.0.0.1:1234');

  return {
    send: (type, data) => {},
    subscribe: listener =>
      puller.on('message', data => listener(data[0], data[1])),
  };
}

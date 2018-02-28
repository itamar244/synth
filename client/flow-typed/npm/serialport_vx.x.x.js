// flow-typed signature: b4eea1789a812b2a36ee8cf07f0a378e
// flow-typed version: <<STUB>>/serialport_v^6.0.4/flow_v0.66.0

/**
 * This is an autogenerated libdef stub for:
 *
 *   'serialport'
 *
 * Fill this stub out by replacing all the `any` types.
 *
 * Once filled out, we encourage you to share your work with the
 * community by sending a pull request to:
 * https://github.com/flowtype/flow-typed
 */

declare module 'serialport' {
  declare type Bytes = Buffer;

  declare class Listenable<Data> {
    on(type: string, listener: (data: Data) => mixed): void;
  }

  declare class Parser<Data> extends Listenable<Data> {}

  declare class SerialPort extends Listenable<string> {
    constructor(path: string): void;
    write(buffer: Bytes | number[]): void;
    pipe<T>(parser: Parser<T>): Parser<T>;
  }

  declare class ByteLength extends Parser<Bytes> {
    constructor(props?: { length: number }): void;
  }

  declare export var parsers: {|
    +ByteLength: typeof ByteLength,
  |};

  declare export default Class<SerialPort> & typeof parsers;
}

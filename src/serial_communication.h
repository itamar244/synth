// Sends and receives data through the serial port.
//
// The data transfer protocol:
// - Each request consists from 2 bytes.
// - The first byte is the request type.
// - The second byte is the data of request.
#pragma once

#include "env.h"

namespace synth {
namespace serial {

enum Message {
	kRemoveNote      = 0,
	kAddNote         = 1,
	kDecrementOctave = 2,
	kIncrementOctave = 3,
	kLogData         = 4,
	kResetStore      = 5,
	kStartRecording  = 6,
	kStopRecording   = 7,
};

void Receive(Environment& env);

inline void Send(Message message, uint8_t data) {
	char buffer[] = {char(message), char(data)};
	Serial.write(buffer, 2);
}
inline void Send(uint8_t data[]) {
	Send(Message(data[0]), data[1]);
}

inline void Log(uint8_t data) {
	Send(kLogData, data);
}

} // namespace serial
} // namespace synth

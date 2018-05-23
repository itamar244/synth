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
	kRemoveTone      = 0,
	kAddTone         = 1,
	kDecrementOctave = 2,
	kIncrementOctave = 3,
	kLogData         = 4,
	kResetStore      = 5,
};

void Receive(Environment& env);

inline void Send(Message message, uint8_t data) {
	char buffer[] = {char(message), char(data)};
	Serial.write(buffer, 2);
}

inline void Log(uint8_t data) {
	Send(kLogData, data);
}

} // namespace serial
} // namespace synth

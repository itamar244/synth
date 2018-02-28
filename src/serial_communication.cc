#include "serial_communication.h"
#include <Arduino.h>
#include "env.h"

namespace synth {
namespace serial {

void Receive(Environment& env) {
	uint8_t request_data[2];
	Serial.readBytes(request_data, 2);

	switch (Message(request_data[0])) {
		case kRemoveTone:
			env.RemoveToneWithOctave(request_data[1]);
			break;
		case kAddTone:
			env.AddToneWithOctave(request_data[1]);
			break;
		case kDecrementOctave:
			env.DecrementOctave();
			break;
		case kIncrementOctave:
			env.IncrementOctave();
			break;
		default:
			Send(Message(request_data[0]), request_data[1]);
			break;
	}
}

} // namespace serial
} // namespace synth

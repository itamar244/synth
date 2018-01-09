#include "serial_communication.h"
#include <Arduino.h>
#include "env.h"

enum RequestType {
	kRemoveTone      = 0,
	kAddTone         = 1,
	kDecrementOctave = 2,
	kIncrementOctave = 3,
};

void synth::HandleSerialCommunication(Environment& env) {
	uint8_t request_data[2];
	Serial.readBytes(request_data, 2);

	switch (RequestType(request_data[0])) {
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
	}
}

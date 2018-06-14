#include "serial_communication.h"
#include <Arduino.h>
#include "env.h"
#include "store.h"

namespace synth {
namespace serial {

void Receive(Environment& env) {
	uint8_t request_data[2];
	Serial.readBytes(request_data, 2);

	switch (Message(request_data[0])) {
		case kRemoveNote:
			env.RemoveNoteWithOctave(request_data[1]);
			break;
		case kAddNote:
			env.AddNoteWithOctave(request_data[1]);
			break;
		case kDecrementOctave:
			env.DecrementOctave();
			break;
		case kIncrementOctave:
			env.IncrementOctave();
			break;
		case kResetStore:
			store::ClearAll();
			break;
		case kStartRecording:
			env.StartRecording();
			Send(request_data);
			break;
		case kStopRecording:
			env.StopRecording();
			Send(request_data);
			break;
		default:
			Send(request_data);
			break;
	}
}

} // namespace serial
} // namespace synth

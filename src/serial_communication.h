/**
 * Handles data which received from the client and updates the
 * `Environment` instance according to the request.
 *
 * The data transfer protocol:
 * - Each request consists from 2 bytes.
 * - The first byte is the request type.
 * - The second byte is the data of request.
 */
#pragma once

#include "env.h"

namespace synth {

enum SerialRequestType {
	kRemoveTone      = 0,
	kAddTone         = 1,
	kDecrementOctave = 2,
	kIncrementOctave = 3,
};

void HandleSerialCommunication(Environment& env);

} // namespace synth

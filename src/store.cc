#include "store.h"
#include "serial_communication.h"

namespace synth {
namespace store {

namespace {

// starts uninitialized. initialized when cur size is first called
uint16_t* cur_size = nullptr;

} // namespace

// going through all bytes
// store could be a sparsed array so stopping when reaching an empty address
uint16_t* __SizePtr() {
	if (cur_size != nullptr) return cur_size;
	uint16_t size = 0;

	for (uint16_t i = 0; i < MaxSize(); i++) {
		if (__GetActual(i) != 0) {
			size = i + 1;
		}
	}

	return (cur_size = new uint16_t(size));
}


void Init() {
	cur_size = new uint16_t(0);

	EEPROM.write(0, 123);
	EEPROM.write(1, 234);

	ClearAll();
}

} // namespace store
} // namespace synth

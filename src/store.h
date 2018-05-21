// EEPROM wrapper for simplicity and consistency, to be used as consistent
// store. The following rules are applied to managing data.
//
// The first two adresses are for validating if the memory is inited or not,
// if they are 123 and 234 than it does inited.
//
// Every "empty" address contains the value 0,
// and for getting and setting values the value is increased by 1.
//
// The memory could be a "sparsed array", some adresses are "empty",
// so when calculating the size every item should be checked.
#pragma once

#include <EEPROM.h>
#include <Arduino.h>
#include <stdint.h>

namespace synth {
namespace store {

// Getting the current store size.
// Using pointer for caching techniques.
uint16_t* __SizePtr();

void Init();

/* An inited memory starts with the bytes 123 and then 234
 * if memory doesn't start with the two chosen values it wil be reseted to 0
 * called in setup */
inline void MaybeInit() {
	if (EEPROM.read(0) != 123 || EEPROM.read(1) != 234) {
		Init();
	}
}

inline uint16_t MaxSize() {
	return EEPROM.length() - 2;
}

inline uint16_t Size() {
	return *__SizePtr();
}

inline uint8_t __GetActual(uint16_t pos) {
	return EEPROM.read(pos + 2);
}

inline uint8_t Get(uint16_t pos) {
	return __GetActual(pos) - 1;
}

inline void Set(uint16_t pos, uint8_t value) {
	EEPROM.update(pos + 2, value + 1);
}

inline void Clear(uint16_t pos) {
	EEPROM.update(pos + 2, 0);
}

inline void Push(uint8_t value) {
	Set(Size(), value);
	(*__SizePtr())++;
}

inline void ClearAll() {
	for (uint16_t i = 0; i < MaxSize(); i++) {
		Clear(i);
	}
}

template<class Callback>
inline void IterateAllBytes(const Callback& callback) {
	for (uint16_t i = 0, size = Size(); i < size; i++) {
		callback(Get(i));
	}
}

} // namespace store
} // namespace synth

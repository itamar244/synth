#pragma once
#include <stdint.h>
#include <avr/pgmspace.h>

namespace synth {

struct PGMArray {
	PGMArray(const uint8_t* data, const uint16_t& size)
			: data_(data), size_(size) {}

	inline uint8_t operator[](uint16_t index) const {
		return pgm_read_word_near(data_ + index);
	}

	inline uint16_t size() const { return size_; }

private:
	const uint8_t* data_;
	const uint16_t size_;
};

} // namespace synth

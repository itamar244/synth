// Timer class for other class to work with timing techniques.
// Should not be directly instantiated but inherited by other classes
// use internally.
//
// Main Timer features are keeping a moment, cheking how much time has passed
// and if needed to change the kept moment to the current time.
// all time work is done with milliseconds.
//
// `PassedTime` to check how many millis have passed since last saved moment.
#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace synth {

class Timer {
protected:
	// how many millis have passed since last saved moment.
	inline uint32_t PassedTime() const {
		return millis() - last_moment_;
	}

	// update the saved to moment to now
	inline void UpdateTime() {
		last_moment_ = millis();
	}

	// update the saved to moment to now and return how much time has passed
	inline uint32_t GetUpdateTime() {
		uint32_t passed_time = PassedTime();
		last_moment_ += passed_time;
		return passed_time;
	}

private:
	uint32_t last_moment_ = millis();
};

} // namespace synth

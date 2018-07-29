#pragma once

#include <cstdlib>
#include <cstdint>
#include <functional>
#include <limits>

namespace synth {
namespace store {

void Init();
void MaybeInit();

inline std::size_t MaxSize() {
	return std::numeric_limits<std::size_t>::max();
}

std::size_t Size();
float Get(std::size_t pos);
void Iterate(std::function<void(float)> func);
void Push(float value);

template<class... Values>
inline void Push(float value, Values... values) {
	Push(value);
	Push(values...);
}

} // namespace store
} // namespace synth

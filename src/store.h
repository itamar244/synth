#pragma once

#include <cstdlib>
#include <cstdint>
#include <limits>

namespace synth {
namespace store {

bool __IsInited();
void Init();
std::size_t Size();
wchar_t __GetActual(std::size_t pos);
void Set(std::size_t pos, uint8_t value);

inline void MaybeInit() {
	if (!__IsInited()) {
		Init();
	}
}

inline std::size_t MaxSize() {
	return std::numeric_limits<std::size_t>::max();
}


inline wchar_t Get(std::size_t pos) {
	return __GetActual(pos) - 1;
}

void Push(wchar_t value);

template<class... Values>
inline void Push(uint8_t value, Values... values) {
	Push(value);
	Push(values...);
}
//
// inline void ClearAll() {
// 	__SizeRef() = 0;
// 	for (std::size_t i = 0; i < MaxSize(); i++) {
// 		Clear(i);
// 	}
// }
//
// template<class Callback>
// inline void IterateAllBytes(const Callback& callback) {
// 	for (std::size_t i = 0, size = Size(); i < size; i++) {
// 		callback(Get(i));
// 	}
// }

} // namespace store
} // namespace synth

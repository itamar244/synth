#pragma once

#include <StandardCplusplus.h>
#include <algorithm>

namespace synth {
namespace utils {

template<class T, class V>
inline bool HasItem(const T& iterable, const V& item) {
	return std::find(iterable.begin(), iterable.end(), item) != iterable.end();
}

template<class Ptr>
inline void DeletePtr(Ptr& ptr) {
	delete ptr;
	ptr = nullptr;
}

} // namespace utils
} // namespace synth

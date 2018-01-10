#pragma once

#include <StandardCplusplus.h>
#include <algorithm>

namespace synth {
namespace utils {

template<class T, class V>
inline bool HasItem(const T& iterable, const V& item) {
	return std::find(iterable.begin(), iterable.end(), item) != iterable.end();
}

} // namespace utils
} // namespace synth

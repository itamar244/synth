// Small functions that called or might be called many times
// in different locations in the project.
#pragma once

#include <StandardCplusplus.h>
#include <algorithm>

namespace synth {
namespace utils {

template<class Iterable, class V>
inline typename Iterable::iterator FindItem(
		const Iterable& iterable,
		const V& item) {
	return std::find(iterable.begin(), iterable.end(), item);
}

template<class Iterable, class V>
inline bool HasItem(const Iterable& iterable, const V& item) {
	return FindItem(iterable, item) != iterable.end();
}

// A normalized `delete` operator that also set the pointer to nullptr,
// because `delete` only deallocate memory.
template<class Ptr>
inline void DeletePtr(Ptr& ptr) {
	delete ptr;
	ptr = nullptr;
}

} // namespace utils
} // namespace synth

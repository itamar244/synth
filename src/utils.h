// Small functions that called or might be called many times
// in different locations in the project.
#pragma once

#include <cstring>
#include <algorithm>
#include <vector>

namespace synth {
namespace utils {

template<class Iterable>
inline typename Iterable::const_iterator FindItem(
		const Iterable& iterable,
		const typename Iterable::value_type& item) {
	return std::find(iterable.begin(), iterable.end(), item);
}

template<class Iterable, class V>
inline bool HasItem(const Iterable& iterable, const V& item) {
	return FindItem(iterable, item) != iterable.end();
}

template<class Ptr>
inline void SetPtr(Ptr& ptr, const Ptr& value) {
	if (ptr != nullptr) {
		delete ptr;
	}
	ptr = value;
}

// A normalized `delete` operator that also set the pointer to nullptr,
// because `delete` only deallocate memory.
template<class Ptr>
inline void DeletePtr(Ptr& ptr) {
	delete ptr;
	ptr = nullptr;
}

template<class Ptr>
inline void MaybeDeletePtr(Ptr& ptr) {
	if (ptr != nullptr) {
		DeletePtr(ptr);
	}
}

template<class Iterator>
auto Advance(Iterator it, unsigned n) -> decltype(*it) {
	for (unsigned i = 0; i < n; i++) {
		++it;
	}

	return *it;
}


}

} // namespace utils
} // namespace synth

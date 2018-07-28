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

template<class Iterator>
auto Advance(Iterator it, unsigned n) -> decltype(*it) {
	for (unsigned i = 0; i < n; i++) {
		++it;
	}

	return *it;
}

template<class Lhs, class Rhs>
inline bool Is(const Lhs& lhs, const Rhs& rhs) {
	return lhs == rhs;
}

inline bool Is(const char* lhs, const char* rhs) {
	return std::strcmp(lhs, rhs) == 0;
}

} // namespace utils
} // namespace synth

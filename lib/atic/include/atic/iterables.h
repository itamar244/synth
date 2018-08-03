#pragma once

#include <functional>

namespace atic {

template<class Iterator>
auto Advance(Iterator it, unsigned n) -> decltype(*it) {
	for (unsigned i = 0; i < n; i++) {
		++it;
	}

	return *it;
}

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

template<class T, class U>
using _ValueTypeMap = typename U::value_type(const typename T::value_type&);

template<class T, class U>
U MapIterable(
	const T& origin,
	const std::function<_ValueTypeMap<T, U> >& pred
) {
	U mapped;

	for (const auto& val : origin) {
		mapped.push_back(pred(val));
	}
	return mapped;
}

} // namespace atic

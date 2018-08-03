#pragma once

#include <functional>

namespace atic {

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

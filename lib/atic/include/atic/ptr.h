#pragma once

#include <cstring>
#include <algorithm>

namespace atic {

template<class Ptr>
inline void SetPtr(Ptr& ptr, const Ptr& value) {
	if (ptr != nullptr) {
		delete ptr;
	}
	ptr = value;
}

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

} // namespace atic

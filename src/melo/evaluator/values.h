#pragma once

#include "../ast.h"
#include "../phrase.h"
#include "section_walker.h"

namespace melo::evaluator {

#define MELO_EVALUATOR_VALUE_TYPES(V)                                          \
	V(SectionValue)                                                              \

enum ValueType : uint8_t {
#define DECLARE_TYPE_ENUM(TYPE) k##TYPE,
	MELO_EVALUATOR_VALUE_TYPES(DECLARE_TYPE_ENUM)
#undef DECLARE_TYPE_ENUM
};

#define FR_DECL(NAME)	struct NAME;
	MELO_EVALUATOR_VALUE_TYPES(FR_DECL)
#undef FR_DECL

struct Value {
	const ValueType type;

#define V(NAME)                                                                \
	inline NAME* As##NAME() {                                                    \
		return type == k##NAME ? reinterpret_cast<NAME*>(this) : nullptr;          \
	}                                                                            \
	inline bool Is##NAME() { return As##NAME() != nullptr; }

	MELO_EVALUATOR_VALUE_TYPES(V)
#undef V

protected:
	Value(ValueType type) : type(type) {}
};

struct SectionValue : public Value {
	const ast::Section* section;

	SectionValue(const ast::Section* section)
			: Value(kSectionValue), section(section) {}
}

}  // namespace melo::evaluator

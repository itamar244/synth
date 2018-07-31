#include "./ast.h"

namespace melo::ast {

#define V(NAME)                                                                \
	NAME* AstNode::As##NAME() {                                                  \
		return type == k##NAME ? reinterpret_cast<NAME*>(this) : nullptr;          \
	}

MELO_AST_NODE_TYPES(V)
#undef V

} // namespace melo::ast

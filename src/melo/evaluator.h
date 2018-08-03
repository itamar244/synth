#pragma once

#include "ast.h"
#include "phrase.h"

namespace melo {

class Evaluator {
public:
	Evaluator(ast::BlockPtr& program);
	Evaluator(ast::BlockPtr&& program);

	inline void Next() { ++pos_; }

	bool HasNextPhrase();
	Phrase GetNextPhrase();

private:
	// used to keep the unique_ptr if the constructor argument is a movable value
	ast::BlockPtr maybe_ast_container_;
	ast::Block& program_;
	ast::Block& main_body_;
	std::size_t pos_ = 0;
};

}  // namespace melo

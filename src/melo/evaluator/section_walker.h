#pragma once

#include <memory>
#include "../ast.h"
#include "../phrase.h"

namespace melo::evaluator {

class SectionWalker {
public:
	SectionWalker(ast::ExpressionPtr& section);

	inline void Next() {
		phrase_cache_ = nullptr;
		++pos_;
	}

	bool HasNextPhrase();
	Phrase GetCurPhrase();

private:
	ast::ExpressionPtr section_unique_ptr_;
	ast::Section* section_;

	std::unique_ptr<Phrase> phrase_cache_ = nullptr;
	std::size_t pos_ = 0;
};

}  // namespace melo::evaluator

#include "section_walker.h"
#include <memory>
#include "evaluator.h"

namespace melo::evaluator {

SectionWalker::SectionWalker(ast::ExpressionPtr& section)
 		: section_unique_ptr_(std::move(section))
		, section_(section_unique_ptr_->AsSection()) {}

bool SectionWalker::HasNextPhrase() const {
	auto& phrases = section_->phrases;

	return pos_ < phrases.size();
}

Phrase SectionWalker::GetCurPhrase() {
	if (phrase_cache_ == nullptr) {
		auto& phrases = section_->phrases;

		phrase_cache_ =
			std::make_unique<Phrase>(PhraseNodeToPhrase(phrases.at(pos_)));
	}

	return *phrase_cache_;
}

} // namespace melo::evaluator

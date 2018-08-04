#pragma once

#include <memory>
#include "../ast.h"
#include "../phrase.h"
#include "section_walker.h"
#include "utils.h"

namespace melo::evaluator {

class Module {
public:
	Module(ast::BlockPtr&& program)
			: program_(std::move(program))
			, main_walker_(GetMain(program_)->AsSection()) {}

	inline SectionWalker& main_walker() { return main_walker_; }
	// FIXME:
	inline float speed() { return 1; }

private:
	ast::BlockPtr program_;
	SectionWalker main_walker_;
};

}  // namespace melo::evaluator

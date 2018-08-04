#pragma once

#include <exception>
#include <map>
#include <memory>
#include <string>
#include "../ast.h"
#include "../phrase.h"
#include "section_walker.h"
#include "utils.h"
#include "values.h"

namespace melo::evaluator {

class Module {
public:
	Module(ast::BlockPtr&& program);

	inline SectionWalker& main_walker() { return main_walker_; }
	// FIXME:
	inline const Value* Get(const std::string name) {
		auto pair = exports_.find(name);
		if (pair == exports_.end()) {
			throw std::logic_error("no such '" + name + "' export");
		}
		return pair->second;
	}

private:
	std::map<std::string, Value*> exports_;
	ast::BlockPtr program_;
	SectionWalker main_walker_;
};

}  // namespace melo::evaluator

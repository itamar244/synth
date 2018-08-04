#include <istream>
#include "ast.h"
#include "evaluator/evaluator.h"
#include "evaluator/section_walker.h"
#include "parser/parser.h"
#include "parser/state.h"

namespace melo {

ast::BlockPtr Parse(std::istream& stream) {
	return parser::Parser(parser::State::Create(stream)).Parse();
}

evaluator::SectionWalker CreateMainSectionWalker(std::istream& stream) {
	auto ast = Parse(stream);
	return {evaluator::GetMain(ast)};
}

} // namespace melo

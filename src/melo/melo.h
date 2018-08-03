#include <istream>
#include "ast.h"
#include "evaluator.h"
#include "parser/parser.h"
#include "parser/state.h"

namespace melo {

ast::BlockPtr Parse(std::istream& stream) {
	return parser::Parser(parser::State::Create(stream)).Parse();
}

Evaluator CreateEvaluator(ast::BlockPtr& program) {
	return {program};
}

Evaluator CreateEvaluator(std::istream& stream) {
	return {Parse(stream)};
}

} // namespace melo

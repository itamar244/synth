#include <iostream>
#include "ast.h"
#include "parser/parser.h"

namespace melo {

ast::BlockPtr Parse(std::istream& stream) {
	std::string input(std::istreambuf_iterator<char>(stream), {});
	return parser::Parser(input).Parse();
}

} // namespace melo

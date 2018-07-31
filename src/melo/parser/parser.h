#pragma once

#include <memory>
#include <string>
#include "../ast.h"
#include "state.h"
#include "tokenizer.h"

namespace melo::parser {

class Parser {
public:
	Parser(const std::string& state);
	ast::BlockPtr Parse();

private:
	State::Ptr state_;
	Tokenizer t_;

	ast::BlockPtr ParseBlock(bool top_level);

	// expressions
	ast::ExpressionPtr ParseExpression();
	ast::IdentifierPtr ParseIdentifier();
	ast::LengthLiteralPtr ParseLengthLiteral();
	ast::SectionPtr ParseSection();
	ast::PhrasePtr ParsePhrase();

	// statements
	ast::StatementPtr ParseStatement(bool top_level);
	ast::FunctionDeclarationPtr ParseFunctionDeclaration();
	ast::ReturnPtr ParseReturn();
};

} // namespace melo::parser

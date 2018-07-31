#include "./tokenizer.h"
#include <cctype>
#include <string>
#include "./token_types.h"

namespace melo::parser {

void Tokenizer::Next() {
	SkipSpace();
	char ch = state_->CurChar();

	state_->start = state_->pos;
	if (state_->pos >= state_->size()) {
		FinishToken(tt::eof);
	} else if (std::isdigit(ch) || ch == '.') {
		ReadNumber();
	} else if (isalpha(ch) || ch == '_') {
		ReadIdentifier();
	} else {
		GetTokenFromChar(ch);
	}
}

void Tokenizer::GetTokenFromChar(char ch) {
	state_->pos += 1;

	switch (ch) {
		case '=':
			return FinishToken(tt::eq, "=");
		case ',':
			return FinishToken(tt::comma);
		case '(':
			return FinishToken(tt::parenL);
		case ')':
			return FinishToken(tt::parenR);
		case '{':
			return FinishToken(tt::braceL);
		case '}':
			return FinishToken(tt::braceR);
		case '[':
			return FinishToken(tt::bracketL);
		case ']':
			return FinishToken(tt::bracketR);
		case ';':
			return FinishToken(tt::semi);
		default:
			FinishTokenWithValue(tt::error);
	}
}

/**
 * reads identifier in current position from input
 * rules are letters and underscore are allowed,
 * also numbers are allowed but not at first character.
 * some checks if first character isn't number should be done
 * but they are done in already in `nextToken`
 */
void Tokenizer::ReadIdentifier() {
	char ch;

	do {
		state_->pos += 1;
		ch = state_->CurChar();
	} while (std::isalnum(ch) || ch ==  '_');

	const std::string word = state_->input.substr(
		state_->start,
		state_->pos - state_->start
	);
	const auto keyword = keywords.find(word);

	if (keyword != keywords.end()) {
		FinishToken(keyword->second);
	} else {
		FinishToken(tt::name, word);
	}
}

void Tokenizer::ReadNumber() {
	for (;;) {
		char ch = state_->CurChar();

		if (std::isdigit(ch)) {
			state_->pos += 1;
		} else if (ch == '.') {
			state_->pos += 1;
			break;
		} else {
			break;
		}
	}

	FinishTokenWithValue(tt::num);
}

void Tokenizer::SkipLine() {
	char ch = state_->CurChar();

	while (ch != '\n' && state_->pos < state_->size()) {
		state_->pos += 1;
		ch = state_->CurChar();
	}
}

void Tokenizer::FinishToken(TokenType type, std::string value) {
	state_->type = type;
	state_->value = value;
}

void Tokenizer::FinishTokenWithValue(TokenType type) {
	FinishToken(
		type,
		state_->input.substr(state_->start, state_->pos - state_->start)
	);
}

void Tokenizer::SkipSpace() {
	bool isSpaceCode = true;

	while (isSpaceCode) {
		switch (state_->CurChar()) {
			case ' ':
			case '\t':
				state_->pos += 1;
				break;
			case '\n':
				state_->pos += 1;
				state_->line += 1;
				state_->lineStart = state_->pos;
				break;
			case '#':
				state_->pos += 1;
				SkipLine();
				break;
			default:
				isSpaceCode = false;
		}
	}
}

} // namespace melo::parser

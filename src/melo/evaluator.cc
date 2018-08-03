#include "evaluator.h"
#include <map>
#include <memory>
#include <string>
#include "phrase.h"
#include "../utils.h"

namespace melo {

namespace {

ast::Block& GetMainBody(ast::BlockPtr& program) {
	for (auto& statement : program->statements) {
		if (auto func = statement->AsFunctionDeclaration()) {
			if (func->id->name == "main") {
				return *func->body;
			}
		}
	}

	throw std::logic_error("no 'main' function in ast");
}

const std::map<char, uint8_t> kNotesToInt({
	{'C', 0}, {'D', 2}, {'E', 4}, {'F', 5}, {'G', 7}, {'A', 9}, {'B', 11},
});

inline float LengthToFloat(const ast::LengthLiteralPtr& length) {
	auto size = length->value.size();
	bool plus_half = *length->value.crbegin() == '.';

	if (plus_half) --size;
	auto buffer = length->value.substr(0, size).c_str();
	float length_value = 32 / float(std::atoi(buffer));

	return plus_half ? length_value * 1.5 : length_value;
}

inline uint8_t StringToNote(const std::string& str) {
	uint8_t pos = 0;
	uint8_t base = kNotesToInt.find(str[pos++])->second;
	if (str[pos] == 'b' || str[pos] == '#') {
		base += str[pos++] == '#' ? +1 : -1;
	}

	uint8_t octave = std::atoi(str.data() + pos);

	return base + octave * 12;
}

inline Phrase ToPhrase(const ast::PhrasePtr& phrase) {
	return {
		utils::MapIterable<decltype(phrase->notes), std::list<uint8_t> >(
				phrase->notes, [](const ast::IdentifierPtr& id) {
					return StringToNote(id->name);
				}),
		LengthToFloat(phrase->length),
	};
}

} // namespace

Evaluator::Evaluator(ast::BlockPtr& program_ptr)
		: program_(*program_ptr)
		, main_body_(GetMainBody(program_ptr))
		, maybe_ast_container_(nullptr) {}

Evaluator::Evaluator(ast::BlockPtr&& program_ptr)
 		: maybe_ast_container_(std::move(program_ptr))
		, program_(*maybe_ast_container_)
		, main_body_(GetMainBody(program_ptr)) {}

bool Evaluator::HasNextPhrase() {
	auto section = main_body_.statements.at(0)->AsReturn()->expr->AsSection();
	auto& phrases = section->phrases;

	return pos_ < phrases.size();
}

Phrase Evaluator::GetNextPhrase() {
	auto section = main_body_.statements.at(0)->AsReturn()->expr->AsSection();
	auto& phrases = section->phrases;
	Phrase phrase;

	return ToPhrase(phrases.at(pos_));
}

}  // namespace melo

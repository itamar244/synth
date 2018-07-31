#pragma once

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include "./token_types.h"

namespace melo::parser {

struct State {
  using Ptr = std::shared_ptr<State>;

	const std::string input;
	TokenType type = tt::eof;
	uint32_t pos = 0;
	uint32_t line = 0;
	uint32_t start = 0;
	uint32_t lineStart = 0;
	std::string value = "";

	State(const std::string& input)
		: input(input) {}

	inline std::string::size_type size() const {
		return input.size();
	}

	inline const char CurChar() const {
		return pos >= size() ? '\x00' : input.at(pos);
	}
};

} // namespace melo::parser

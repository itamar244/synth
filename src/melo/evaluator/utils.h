#pragma once

#include <map>
#include <string>
#include "../ast.h"
#include "../phrase.h"

namespace melo::evaluator {

using Scope = std::map<std::string, ast::Expression>;

ast::ExpressionPtr& GetMain(ast::BlockPtr& program);
Phrase PhraseNodeToPhrase(const ast::PhraseLiteralPtr& phrase);

}  // namespace melo::evaluator

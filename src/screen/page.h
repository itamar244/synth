/**
 * seperating enum class Page from `screen/pages.h`.
 * the seperation fixes many circular dependencies
 */
#pragma once

namespace synth {
namespace screen {

enum class Page {
  INDEX,
  KEYBOARD,
};

} // namespace synth
} // namespace screen

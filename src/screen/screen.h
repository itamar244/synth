/**
 * the main logic of the screen module.
 * Controller is the screen controller
 */
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "env.h"
#include "screen/button.h"

namespace synth::screen {

enum class Route;

class Controller {
public:
  Controller();

	inline bool is_touched() const { return is_touched_; }
  inline Route route() const { return route_; }
  inline void set_route(Route next) {
    route_ = next;
    is_painted_ = false;
  }

  void Paint(Environment&, sf::RenderWindow&);
  void Touch(
			Environment& env, sf::RenderWindow& window, sf::Vector2i point_vec);
  void Touchend(Environment&, sf::RenderWindow&);

private:
  std::vector<Button> buttons_;
  Route route_;
  bool is_painted_ = false, is_touched_ = false;
};

} // namespace synth::screen

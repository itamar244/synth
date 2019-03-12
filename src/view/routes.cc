/**
 * exported functions for repeated patterns
 * that are used in `view/pages/` files to
 * generate view output.
 */
#include "view/routes.h"
#include <cstring>
#include <SFML/Graphics.hpp>
#include "view/button.h"
#include "view/elements.h"

namespace synth::view {

void PaintMenuLoop(
		sf::RenderWindow& window,
		const PaintMenuNames& names,
		std::vector<Button>& buttons,
		uint8_t& i) {
	for (auto& name : names) {
		auto name_len = name.size();
		float x = 30, y = (i++) * 45 + 20;
		float width = 80, height = 35;


		if (name_len > 4) {
			width = name_len * 12 + 36;
		}
		Button button = { x, y, width, height };
		buttons.push_back(button);

		window.draw(RectElement(button, sf::Color::Red));
		window.draw(TextElement(name, x + 10, y + 10));
	}
}

std::vector<Button> PaintMenu(
		sf::RenderWindow& window, const PaintMenuNames& names) {
	std::vector<Button> buttons;
	uint8_t i = 0;
	buttons.reserve(names.size());

	PaintMenuLoop(window, names, buttons, i);

	return buttons;
}

std::vector<Button> PaintMenu(
		sf::RenderWindow& window,
		const std::initializer_list<PaintMenuNames>& names_list) {
	std::vector<Button> buttons;
	uint8_t i = 0;

	for (auto& names : names_list) {
		PaintMenuLoop(window, names, buttons, i);
	}

	return buttons;
}

std::vector<Button> PaintKeyboard(
		sf::RenderWindow& window, const PaintMenuNames& names) {
	std::vector<Button> buttons;
	auto name_it = names.begin();

	buttons.reserve(names.size() + 1);

	for (uint8_t i = 0; i < names.size() && i < 11; i++, name_it++) {
		const float x = (i % 3) * 100 + 30;
		const float y = (i / 3) * 50 + 40;
		const float width = 50, height = 40;
		Button button = { x, y, width, height };

		buttons.push_back(button);
		window.draw(RectElement(button, sf::Color::Red));
		window.draw(
			TextElement(*name_it, x + (21 - (*name_it).size() * 3), y + 10));
	}

	auto dimensions = window.getSize();
	Button menu = { dimensions.x - 100, dimensions.y - 50, 100, 40 };
	buttons.push_back(menu);
	window.draw(RectElement(menu, sf::Color::Red));
	window.draw(TextElement("Back", menu.x + 18, menu.y + 10));

	return buttons;
}

} // namespace synth::view

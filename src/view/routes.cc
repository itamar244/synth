/**
 * exported functions for repeated patterns
 * that are used in `view/pages/` files to
 * generate view output.
 */
#include "view/routes.h"
#include <cstring>
#include <SFML/Graphics.hpp>
#include "view/button.h"

namespace synth::view {

void ClearButtonClicks(std::vector<Button>& buttons) {
	for (auto& button : buttons) {
		if (button.is_pressed) {
			button.is_pressed = false;
		}
	}
}

sf::RectangleShape CreateRectShape(
		const Button& button, sf::Color color) {
	sf::RectangleShape shape{ sf::Vector2f{ button.width, button.height } };
	shape.setPosition(button.x, button.y);
	shape.setFillColor(color);
	return shape;
}

sf::Text CreateText(const std::string& str, float x, float y) {
	// TODO: might fix this ugly trick
	static sf::Font font;
	static bool loaded = false;
	if (!loaded) {
		font.loadFromFile("/usr/share/fonts/truetype/tlwg/Loma.ttf");
		loaded = true;
	}
	sf::Text text(str, font);

	text.setFont(font);
	text.setString(str);
	text.setPosition(x, y - 5);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	return text;
}

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

		window.draw(CreateRectShape(button, sf::Color::Red));
		window.draw(CreateText(name, x + 10, y + 10));
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
		window.draw(CreateRectShape(button, sf::Color::Red));
		window.draw(
			CreateText(*name_it, x + (21 - (*name_it).size() * 3), y + 10));
	}

	auto dimensions = window.getSize();
	Button menu = { dimensions.x - 100, dimensions.y - 50, 100, 40 };
	buttons.push_back(menu);
	window.draw(CreateRectShape(menu, sf::Color::Red));
	window.draw(CreateText("Back", menu.x + 18, menu.y + 10));

	return buttons;
}

} // namespace synth::view

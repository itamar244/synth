#include "view/elements.h"

namespace synth::view {

void DrawableGroup::draw(
		sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& item : items_) {
		target.draw(*item, states);
	}
}

sf::RectangleShape RectElement(
		const Button& button, sf::Color color) {
	sf::RectangleShape shape{ sf::Vector2f{ button.width, button.height } };
	shape.setPosition(button.x, button.y);
	shape.setFillColor(color);
	return shape;
}

sf::Text TextElement(const std::string& str, float x, float y) {
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

DrawableGroup ButtonElement(
		const std::string& text, sf::Color color, float x, float y) {
	DrawableGroup group;

	group.Add(
			RectElement({x - 15, y - 5, float(text.size() * 12 + 15), 30}, color));
	group.Add(TextElement(text, x, y));
	return group;
}


} // namespace synth::view

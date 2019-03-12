// functions to create common drawables elements
#pragma once

#include <list>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "view/button.h"

namespace synth::view {

class DrawableGroup : public sf::Drawable {
public:
	template<class T>
	inline void Add(const T& item) {
		items_.push_back(std::make_unique<const T>(item));
	}

	virtual void draw(
			sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::list<std::unique_ptr<const sf::Drawable> > items_;
};

sf::RectangleShape RectElement(const Button& button, sf::Color color);
sf::Text TextElement(const std::string& str, float x, float y);
DrawableGroup ButtonElement(
		const std::string& str, sf::Color color, float x, float y);

} // namespace synth::view

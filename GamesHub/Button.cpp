#include "Button.h"


Button::Button(const sf::Vector2f& position, const std::string& name) {
	rect.setSize(sf::Vector2f(140.0f, 40.0f));
	rect.setPosition(position);
	rect.setFillColor(sf::Color::White);

	if (!font.loadFromFile("stdfont.ttf")) {
		//error
	}
	text.setFont(font);
	text.setString(name);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(position.x + 10.0f, position.y + 5.0f));
}

void Button::draw(sf::RenderWindow& window) const {

	window.draw(rect);
	window.draw(text);
}

bool Button::checkButtonClicked(sf::Vector2i mouse_pos) const {
	sf::FloatRect bounding_box = rect.getGlobalBounds();
	return bounding_box.contains(sf::Vector2f(mouse_pos.x, mouse_pos.y));
}
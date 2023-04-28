#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {

private:
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;

public:
	Button(const sf::Vector2f& position, const std::string& name);
	void draw(sf::RenderWindow& window) const;
	bool checkButtonClicked(sf::Vector2i mouse_pos) const;
};


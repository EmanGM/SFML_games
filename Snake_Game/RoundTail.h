#pragma once
#include <SFML/Graphics.hpp>


enum direction {
	Right,
	Left,
	Up,
	Down,
};


class RoundTail {

private:
	sf::RectangleShape quadrado;
	sf::CircleShape redondo;
	sf::Vector2f size;
	sf::Vector2f position;
	direction direcao;
	void move();


public:
	RoundTail(sf::Vector2f size);
	void setDirection(sf::Vector2f position);
	void setPosition(const sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
};


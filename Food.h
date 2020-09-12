#pragma once
//#include "Snake.h"
#include <SFML\Graphics.hpp>

class Snake;

class Food
{
private:
	sf::RectangleShape comida;
	sf::Vector2i windowSize;

public:

	sf::Vector2f position;
	sf::Vector2f cellSize;

	Food(sf::RenderWindow& janela, sf::Vector2f cellSize, sf::Color cor);
	void newPosition(Snake& snake);
	void draw(sf::RenderWindow& window);
	~Food();
};



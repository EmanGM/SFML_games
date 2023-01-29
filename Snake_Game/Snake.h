#pragma once

#include "Food.h"
#include "RoundTail.h"
#include <SFML\Graphics.hpp>




class Snake {

private:
	sf::RectangleShape* body;
	sf::CircleShape eye;
	RoundTail tail;
	sf::Vector2f curentPosition;
	sf::Vector2f size;
	direction direcao;
	void updatePosition();

	friend void Food::newPosition(Snake& snake);

public:
	Snake(sf::Vector2f cellSize);
	void draw(sf::RenderWindow& window);
	int length;
	float velocity;
	void move();
	void changeDirection(direction direcao);
	void aumentarTamanho(int aumento, Food food);
	bool checkFoodColision(Food food);
	bool stopGame(sf::RenderWindow& window);
	~Snake();
};


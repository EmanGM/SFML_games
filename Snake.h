#pragma once

#include "Food.h"
#include <SFML\Graphics.hpp>

enum direction {
	Right,
	Left,
	Up,
	Down,
};


class Cauda {
private:
	sf::RectangleShape quadrado;
	sf::CircleShape redondo;
	sf::Vector2f size;
	sf::Vector2f position;
	direction direcao;
	void move();


public:
	Cauda(sf::Vector2f size);
	void setDirection(sf::Vector2f position);
	void setPosition(const sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
};


class Snake
{
private:
	sf::RectangleShape* corpo;
	sf::CircleShape olho;
	Cauda cauda;
	sf::Vector2f curentPosition;
	sf::Vector2f size;
	direction direcao;
	void updatePosition();

	friend void Food::newPosition(Snake& snake);

public:
	Snake(sf::Vector2f cellSize);
	int length;
	float velocity;
	void draw(sf::RenderWindow& window);
	void move();
	void changeDirection(direction direcao);
	void aumentarTamanho(int aumento, Food food);
	bool checkFoodColision(Food food);
	bool stopGame(sf::RenderWindow& window);
	~Snake();
};


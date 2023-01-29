#include "Snake.h"
#include "Food.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#define HEAD 0


Snake::Snake(sf::Vector2f cellSize) : tail(cellSize)
{
	body = new sf::RectangleShape[4];
	length = 4;
	this->size.x = cellSize.x - 1;
	this->size.y = cellSize.y - 1;

	int startX = rand() % 15;
	for (int i = 0; i < length; i++) {
		(body + i)->setSize(this->size);
		(*(body + i)).setFillColor(sf::Color::Red);
		(body + i)->setOutlineThickness(1);
		(body + i)->setOutlineColor(sf::Color::Black);
		body[i].setPosition(sf::Vector2f(1.0f + startX * cellSize.x, cellSize.y * ((length - 1) - i) + 1));
	}
	updatePosition();

	//Eye:
	eye.setRadius(2.0f);
	eye.setFillColor(sf::Color::Black);
	eye.setPosition(sf::Vector2f(curentPosition.x + 5, curentPosition.y + 5));
	direcao = Down;

	updatePosition();
}

void Snake::move() {

	int tempSize = this->length - 1;
	sf::Vector2f* temp = new sf::Vector2f[tempSize];
	for (int i = 0; i < tempSize; i++) {
		temp[i].x = body[i].getPosition().x;
		temp[i].y = body[i].getPosition().y;
	}

	switch (direcao) {

	case Left:
		body[HEAD].move(sf::Vector2f(- size.x - 1, 0));
		eye.move(sf::Vector2f(- size.x - 1.0f, 0));
		break;
	case Right:
		body[HEAD].move(sf::Vector2f(size.x + 1, 0));
		eye.move(sf::Vector2f(size.x + 1, 0));
		break;
	case Up:
		body[HEAD].move(sf::Vector2f(0, - size.y - 1));
		eye.move(sf::Vector2f(0, - size.y - 1));
		break;
	case Down:
		body[HEAD].move(sf::Vector2f(0, size.y + 1));
		eye.move(sf::Vector2f(0, size.y + 1));
		break;
	}
	updatePosition();

	for (int i = 1; i < this->length; i++) {
		body[i].setPosition(temp[i - 1].x, temp[i - 1].y);
	}


	tail.setPosition(body[length - 1].getPosition());
	tail.setDirection(body[length - 2].getPosition());
}

void Snake::changeDirection(direction direc) {

	if (direc == Left) {
		if (direcao != Left && direcao != Right) {
			direcao = Left;
			eye.setPosition(sf::Vector2f(curentPosition.x + 5, curentPosition.y + 5));
		}
	}
	else if (direc == Right) {
		if (direcao != Right && direcao != Left) {
			direcao = Right;
			eye.setPosition(sf::Vector2f(curentPosition.x + 15, curentPosition.y + 5));
		}
	}
	else if (direc == Up) {
		if (direcao != Up && direcao != Down) {
			direcao = Up;
			eye.setPosition(sf::Vector2f(curentPosition.x + 5, curentPosition.y + 5));
		}
	}
	else if (direc == Down) {
		if (direcao != Down && direcao != Up) {
			direcao = Down;
			eye.setPosition(sf::Vector2f(curentPosition.x + 15, curentPosition.y + 15));
		}
	}
}

bool Snake::checkFoodColision(Food food) {

	return food.position.x == curentPosition.x - 1 && food.position.y == curentPosition.y - 1;
}

void Snake::aumentarTamanho(int aumento, Food food) {

	this->length += aumento;
	int aumentar = this->length;
	sf::RectangleShape* temp = new sf::RectangleShape[aumentar];
	for (int i = 0; i < aumento; i++) {
		temp[i].setSize(size);
		temp[i].setFillColor(sf::Color::Red);
		temp[i].setPosition(sf::Vector2f(food.position.x + 1, food.position.y + 1));
		temp[i].setOutlineThickness(1);
		temp[i].setOutlineColor(sf::Color::Black);
	}
	for (int i = aumento; i < length; i++) {
		*(temp + i) = *(body + (i - aumento));
	}

	delete[] body;
	body = new sf::RectangleShape[this->length];


	for (int i = 0; i < this->length; i++) {
		*(body + i) = *(temp + i);
	}

	tail.setPosition((body + (length - 1))->getPosition());

	delete[] temp;
}

bool Snake::stopGame(sf::RenderWindow& window) {

	if (curentPosition.x < 0 || curentPosition.x > window.getSize().x || curentPosition.y < 0 || curentPosition.y > window.getSize().y) {
		return true;
	}

	for (int i = 3; i < this->length; i++) {
		if (curentPosition.x == (body + i)->getPosition().x && curentPosition.y == (body + i)->getPosition().y) {
			return true;
		}
	}
	return false;
}

void Snake::updatePosition() {
	curentPosition.x = body[HEAD].getPosition().x;
	curentPosition.y = body[HEAD].getPosition().y;
}

void Snake::draw(sf::RenderWindow& window) {

	for (int i = 0; i < this->length - 1; i++) {
		window.draw(*(body + i));
	}
	window.draw(eye);
	tail.draw(window);
}


Snake::~Snake()
{
}
#include "Snake.h"
#include "Food.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#define HEAD 0


Snake::Snake(sf::Vector2f cellSize) : cauda(cellSize)
{
	corpo = new sf::RectangleShape[4];
	length = 4;
	this->size.x = cellSize.x - 1;
	this->size.y = cellSize.y - 1;

	int startX = rand() % 15;
	for (int i = 0; i < length; i++) {
		(corpo + i)->setSize(this->size);
		(*(corpo + i)).setFillColor(sf::Color::Red);
		(corpo + i)->setOutlineThickness(1);
		(corpo + i)->setOutlineColor(sf::Color::Black);
		corpo[i].setPosition(sf::Vector2f(1.0f + startX * cellSize.x, cellSize.y * ((length - 1) - i) + 1));
	}

	//Olho:
	olho.setRadius(2.0f);
	olho.setFillColor(sf::Color::Black);
	olho.setPosition(sf::Vector2f(size.x - 8, size.y * 4 - 8));
	direcao = Down;

	updatePosition();
}

void Snake::move() {

	int tempSize = this->length - 1;
	sf::Vector2f* temp = new sf::Vector2f[tempSize];
	for (int i = 0; i < tempSize; i++) {
		temp[i].x = corpo[i].getPosition().x;
		temp[i].y = corpo[i].getPosition().y;
	}

	switch (direcao) {

	case Left:
		corpo[HEAD].setPosition(sf::Vector2f(curentPosition.x - size.x - 1, curentPosition.y));
		break;
	case Right:
		corpo[HEAD].setPosition(sf::Vector2f(curentPosition.x + size.x + 1, curentPosition.y));
		break;
	case Up:
		corpo[HEAD].setPosition(sf::Vector2f(curentPosition.x, curentPosition.y - size.y - 1));
		break;
	case Down:
		corpo[HEAD].setPosition(sf::Vector2f(curentPosition.x, curentPosition.y + size.y + 1));
		break;
	}
	updatePosition();

	for (int i = 1; i < this->length; i++) {
		corpo[i].setPosition(temp[i - 1].x, temp[i - 1].y);
	}
	olho.setPosition(sf::Vector2f(curentPosition.x + 5, curentPosition.y + 5));


	cauda.setPosition(corpo[length - 1].getPosition());
	cauda.setDirection(corpo[length - 2].getPosition());
}

void Snake::changeDirection(direction direc) {

	if (direc == Left) {
		if (direcao != Left && direcao != Right) {
			direcao = Left;
		}
	}
	else if (direc == Right) {
		if (direcao != Right && direcao != Left) {
			direcao = Right;
		}
	}
	else if (direc == Up) {
		if (direcao != Up && direcao != Down) {
			direcao = Up;
		}
	}
	else if (direc == Down) {
		if (direcao != Down && direcao != Up) {
			direcao = Down;
		}
	}
}

bool Snake::checkFoodColision(Food food) {

	if (food.position.x == curentPosition.x - 1 && food.position.y == curentPosition.y - 1) {
		return true;
	}

	return false;
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
		*(temp + i) = *(corpo + (i - aumento));
	}

	delete[] corpo;
	corpo = new sf::RectangleShape[this->length];


	for (int i = 0; i < this->length; i++) {
		*(corpo + i) = *(temp + i);
	}

	cauda.setPosition((corpo + (length - 1))->getPosition());

	delete[] temp;
}

bool Snake::stopGame(sf::RenderWindow& window) {

	if (curentPosition.x < 0) {
		return true;
	}
	else if (curentPosition.x > window.getSize().x) {
		return true;
	}
	else if (curentPosition.y < 0) {
		return true;
	}
	else if (curentPosition.y > window.getSize().y) {
		return true;
	}

	for (int i = 3; i < this->length; i++) {
		if (curentPosition.x == (corpo + i)->getPosition().x && curentPosition.y == (corpo + i)->getPosition().y) {
			return true;
		}
	}
	return false;
}

void Snake::updatePosition() {
	curentPosition.x = corpo[HEAD].getPosition().x;
	curentPosition.y = corpo[HEAD].getPosition().y;
}

void Snake::draw(sf::RenderWindow& window) {

	for (int i = 0; i < this->length - 1; i++) {
		window.draw(*(corpo + i));
	}
	window.draw(olho);
	cauda.draw(window);
}


Snake::~Snake()
{
}




//Classe cauda:

Cauda::Cauda(sf::Vector2f size) {
	this->size.x = size.x - 1.0f;
	this->size.y = size.y - 1.0f;
	this->position.x = 1.0f - size.x;
	this->position.y = 1.0f - size.y;

	quadrado.setSize(sf::Vector2f(this->size.x, this->size.y / 2));
	redondo.setRadius(this->size.x / 2);
	quadrado.setPosition(position);
	redondo.setPosition(position);
	quadrado.setFillColor(sf::Color::Red);
	redondo.setFillColor(sf::Color::Red);
	quadrado.setOutlineThickness(1);
	//caudaRedonda.setOutlineThickness(1);
	quadrado.setOutlineColor(sf::Color::Black);
	//caudaRedonda.setOutlineColor(sf::Color::Black);

	direcao = Down;
}

void Cauda::setDirection(sf::Vector2f position) {
	
	if (direcao == Up || direcao == Down) {
		if (position.x > this->position.x) {
			direcao = Right;
		}
		else if (position.x < this->position.x) {
			direcao = Left;
		}
	}
	else if (direcao == Right || direcao == Left) {
		if (position.y > this->position.y) {
			direcao = Down;
		}
		else if (position.y < this->position.y) {
			direcao = Up;
		}
	}
	move();
}


void Cauda::move() {
	switch (direcao)
	{
	case Up:
		quadrado.setRotation(0);
		quadrado.setPosition(position);
		break;
	case Down:
		quadrado.setRotation(0);
		quadrado.setPosition(position.x, position.y + (size.y / 2));
		break;
	case Right:
		quadrado.setRotation(90);
		quadrado.setPosition(position.x + size.x, position.y);
		break;
	case Left:
		quadrado.setRotation(90);
		quadrado.setPosition(position.x + (size.x / 2), position.y);
		break;
	default:
		break;
	}
	redondo.setPosition(position);
}


void Cauda::setPosition(const sf::Vector2f newPosition) {
	position = newPosition;
	move();
}

void Cauda::draw(sf::RenderWindow& window) {
	window.draw(quadrado);
	window.draw(redondo);
}
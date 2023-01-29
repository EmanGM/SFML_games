#include "RoundTail.h"


RoundTail::RoundTail(sf::Vector2f size) {
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

void RoundTail::setDirection(sf::Vector2f position) {

	if (direcao == Up || direcao == Down) {
		if (position.x > this->position.x) {
			direcao = Right;
		} else if (position.x < this->position.x) {
			direcao = Left;
		}
	} else if (direcao == Right || direcao == Left) {
		if (position.y > this->position.y) {
			direcao = Down;
		} else if (position.y < this->position.y) {
			direcao = Up;
		}
	}
	move();
}


void RoundTail::move() {
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


void RoundTail::setPosition(const sf::Vector2f newPosition) {
	position = newPosition;
	move();
}

void RoundTail::draw(sf::RenderWindow& window) {
	window.draw(quadrado);
	window.draw(redondo);
}


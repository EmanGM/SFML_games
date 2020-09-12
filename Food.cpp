#include "Food.h"
#include "Snake.h"
#include <iostream>
#include <SFML\Graphics.hpp>


Food::Food(sf::RenderWindow& janela, sf::Vector2f cellSize, sf::Color cor)
{
	windowSize.x = janela.getSize().x;
	windowSize.y = janela.getSize().y;
	this->cellSize = cellSize;
	position.x = rand() % (int)(windowSize.x / this->cellSize.x) * this->cellSize.x;
	position.y = rand() % (int)(windowSize.y / this->cellSize.y) * this->cellSize.y;
	//std::cout << "Pozisao X " << position.x << "\n" << "Pozisao Y " << position.y << "\n\n";
	comida.setSize(cellSize);
	comida.setFillColor(cor);
	comida.setPosition(position);
}

void Food::newPosition(Snake& snake) {

	position.x = rand() % (int)(windowSize.x / this->cellSize.x) * this->cellSize.x;
	position.y = rand() % (int)(windowSize.y / this->cellSize.y) * this->cellSize.y;
	//std::cout << "Pozisao X " << position.x << "\n" << "Pozisao Y " << position.y << "\n\n";
	for (int i = 0; i < snake.length; i++) {
		if (snake.corpo[i].getPosition().x - 1 == position.x && snake.corpo[i].getPosition().y - 1 == position.y) {
			newPosition(snake);
		}
	}
	comida.setPosition(position);
}

void Food::draw(sf::RenderWindow& window) {

	window.draw(comida);
}

Food::~Food()
{
}

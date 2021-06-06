#include "Objetos.h"



Tijolo::Tijolo()
{
	brick.setSize(sf::Vector2f(65.0f, 30.0f));
	brick.setFillColor(sf::Color(255, 0, 0, 240));
	brick.setOutlineThickness(2);
	brick.setOutlineColor(sf::Color(100, 100, 100, 255));
	brick.setPosition(sf::Vector2f(40.0f, 30.0f));
	brick.setOrigin(brick.getSize().x / 2, brick.getSize().y / 2);
	vida = true;
}

void Tijolo::setPosition(sf::Vector2f position) {

	brick.setPosition(position);
}

sf::Vector2f Tijolo::getPosition() {
	return brick.getPosition();
}

sf::Vector2f Tijolo::getHalfSize() {
	sf::Vector2f HalfSize;
	HalfSize.x = brick.getSize().x / 2;
	HalfSize.y = brick.getSize().y / 2;
	return HalfSize;
}

void Tijolo::draw(sf::RenderWindow& janela) {
	janela.draw(brick);
}

Tijolo::~Tijolo()
{
}

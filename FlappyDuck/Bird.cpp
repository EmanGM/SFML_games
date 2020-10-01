#include "Bird.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Tubo.h"


Bird::Bird() : raio(18.0f)
{
	bird.setRadius(raio);
	//bird.setFillColor(sf::Color::Yellow);
	position.x = 350.0f;
	position.y = 225.0f;
	//std::cout << position.x << "   " << position.y << std::endl;
	bird.setPosition(position);
	bird.setOrigin(sf::Vector2f(raio, raio));
	//bird.setPosition(sf::Vector2f(0.0f, 200.0f));

	if (!Texture.loadFromFile("rubberDucky.png")) {
		//Texture.loadFromFile("..\\Release\\rubberDucky.png");
	}
	bird.setTexture(&Texture);

	velocidadeVertical = 0;
}

void Bird::getDown() {

	velocidadeVertical += 0.1f;
	position.x += 0.0f;
	position.y += velocidadeVertical;
	bird.setPosition(position);
	bird.rotate(2.0f * velocidadeVertical);
}

void Bird::Up() {

	velocidadeVertical = 0;
	position.x += 0.0f;
	position.y -= 3.5f;
	bird.setPosition(position);
	bird.rotate(-6.5f);
}

bool Bird::Colizion(Tubo& cano) {

	for (int i = 0; i < 2; i++) {

		sf::Vector2f otherPosition = cano.getPosition(i);
		sf::Vector2f otherHalfSize = cano.getHalfSize(i);

		sf::Vector2f thisPosition = position;
		sf::Vector2f thisHalfSize;
		thisHalfSize.x = raio - 2.0f;
		thisHalfSize.y = raio - 2.0f;

		float deltaX = otherPosition.x - thisPosition.x;
		float deltaY = otherPosition.y - thisPosition.y;

		float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (intersectX < 0.0f && intersectY < 0.0f) {
			return true;
		}
	}

	if (position.y > 550) {
		return true;
	}
	return false;
}

void Bird::draw(sf::RenderWindow& janela) {

	janela.draw(bird);
}

Bird::~Bird()
{
}

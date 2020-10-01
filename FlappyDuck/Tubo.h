#pragma once
#include <SFML\Graphics.hpp>

class Tubo
{
private:
	sf::RectangleShape tuboCima;
	sf::RectangleShape tuboBaixo;
	sf::Vector2f size[2];
	sf::Vector2f position[2];
	const float space = 80.0;

public:

	Tubo(int sitio, float XStart);
	void UpDate();
	Tubo operator= (const Tubo& objeto);
	void draw(sf::RenderWindow& janela);
	float getXPosistion();
	sf::Vector2f getPosition(bool isCeil);
	sf::Vector2f getHalfSize(bool isCeil);
	~Tubo();
};



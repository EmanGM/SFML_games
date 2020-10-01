#pragma once
#include <SFML\Graphics.hpp>
#include "Tubo.h"

class Bird
{

private:
	sf::Vector2f position;
	sf::Texture Texture;
	float raio;
	float velocidadeVertical;

public:
	sf::CircleShape bird;
	Bird();
	void getDown();
	void Up();
	bool Colizion(Tubo& cano);
	void draw(sf::RenderWindow& janela);
	~Bird();
};



#pragma once
#include <SFML\Graphics.hpp>
#include "Objetos.h"

class PowerUp
{
private:
	sf::Clock clock;
	sf::Time time;
	int tempo;
    sf::Texture *text;

public:
	sf::CircleShape powerUp;
	sf::Vector2f position;
	float raio;
	int tipo;
	bool visivel;

	PowerUp(sf::Vector2f tijoloPosition, sf::Texture* Text);
	void move();
	bool UpTime();
	void setInvisible();
	sf::Vector2f getPosition();
	bool colisaoRaquete(Racket& raquete);
	void draw(sf::RenderWindow& janela);
	~PowerUp();
};


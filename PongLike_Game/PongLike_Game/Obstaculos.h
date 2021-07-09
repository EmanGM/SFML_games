#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Obstaculo {
protected:

	sf::Vector2f centerPosition;
	sf::Time timeTotal;
	sf::Clock clockTime;
	sf::Time timeAnimation;
	sf::Clock clockAnimation;
	const float animationTime, aliveTime;
	int animationTimes;

public:

	Obstaculo(const float animationTime, const float aliveTime);
	virtual bool animate();
	virtual void checkCollision(Ball &ball);
	virtual void draw(sf::RenderWindow& janela);
};



class Barrier : public Obstaculo
{
private:
	sf::RectangleShape rect;
	const sf::Vector2f size;

public:

	Barrier(const float animationTime, const float aliveTime);
	void checkCollision(Ball &ball);
	bool animate();
	void draw(sf::RenderWindow &janela);
};



class Oil : public Obstaculo
{
private:
	sf::CircleShape cir;
	const float radius;
	sf::Texture texture;

public:

	Oil(const float animationTime, const float aliveTime);
	void checkCollision(Ball &bola);
	bool animate();
	void draw(sf::RenderWindow& janela);
};



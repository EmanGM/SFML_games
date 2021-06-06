#pragma once
#include <SFML\Graphics.hpp>

#define GameLimit 1700
#define AsteroidesGap 80
#define AsteroidesBarrier (GameLimit - AsteroidesGap * 2)

#define tier1_Velocity  1.8f
#define tier2_Velocity  1.0f
#define tier3_Velocity  0.6f



class Asteroides
{
private:
	sf::CircleShape esfera;
	sf::Texture* textura;
	int Tier;
	float velocidade;
	//sf::Vector2f direcao;
	bool isInside;

public:
	float raio;
	sf::Vector2f position;
	sf::Vector2f direcao;

	Asteroides(int tier, bool isInside, sf::Texture* Texture);
	sf::Vector2f getDirection() {
		return direcao;
	}
	sf::Vector2f getPosition() {
		//return position;
		return esfera.getPosition();
	}
	int getTier() {
		return Tier;
	}
	sf::FloatRect getBoundingBox() {
		return esfera.getGlobalBounds();
	}
	bool isInGame() {
		return isInside;
	}
	void setAngleDirection(sf::Vector2f direction, float angle);
	void setPosition(sf::Vector2f position);
	void move();
	void draw(sf::RenderWindow& janela);
	~Asteroides();
};



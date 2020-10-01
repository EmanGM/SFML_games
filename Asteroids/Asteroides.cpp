#include <SFML\Graphics.hpp>
#include <iostream>
#include "Asteroides.h"



Asteroides::Asteroides(int tier, bool isInside, sf::Texture* Texture)
{
	Tier = tier;
	raio = 10.0f;
	velocidade = 0.0f;
	switch (Tier)
	{
	case 1:
		raio = 40.0f;
		velocidade = tier1_Velocity;
		break;
	case 2:
		raio = 30.0f;
		velocidade = tier2_Velocity;
		break;
	case 3:
		raio = 20.0f;
		velocidade = tier3_Velocity;
		break;
	default:
		break;
	}


	//definições do asteroide:
	esfera.setRadius(raio);
	esfera.setOrigin(sf::Vector2f(raio, raio));

	//Direção:
	sf::Vector2f direct;
	direct.x = ((rand() % 200) - 100) / 100.0f;
	direct.y = ((rand() % 200) - 100) / 100.0f;
	float lowDist = sqrt(pow(direct.x, 2) + pow(direct.y, 2));
	direcao.x = (velocidade * direct.x) / lowDist;
	direcao.y = (velocidade * direct.y) / lowDist;


	//criação de zonas de nascimento
	this->isInside = isInside;
	switch (rand() % 4)
	{
	case 0: //left side
		position.x = rand() % AsteroidesGap;
		position.y = rand() % GameLimit;
		if (isInside == false) {
			direcao.x = -abs(direcao.x);
		}
		else {
			direcao.x = abs(direcao.x);
		}
		break;
	case 1: //up side
		position.x = rand() % AsteroidesBarrier + AsteroidesGap;
		position.y = rand() % AsteroidesGap;
		if (isInside == false) {
			direcao.y = -abs(direcao.y);
		}
		else {
			direcao.y = abs(direcao.y);
		}
		break;
	case 2: //bottom side
		position.x = rand() % AsteroidesBarrier + AsteroidesGap;
		position.y = rand() % AsteroidesGap + (AsteroidesBarrier + AsteroidesGap);
		if (isInside == false) {
			direcao.y = abs(direcao.y);
		}
		else {
			direcao.y = -abs(direcao.y);
		}
		break;
	case 3: //right side
		position.x = rand() % AsteroidesGap + (AsteroidesBarrier + AsteroidesGap);
		position.y = rand() % GameLimit;
		if (isInside == false) {
			direcao.x = abs(direcao.x);
		}
		else {
			direcao.x = -abs(direcao.x);
		}
		break;
	}

	position.x -= (GameLimit / 2);
	position.y -= (GameLimit / 2);
	esfera.setPosition(position);


	//Textura:
	this->textura = Texture;
	esfera.setTexture(textura);

	int asteroide[2];
	asteroide[0] = rand() % 8;
	asteroide[1] = rand() % 8;
	sf::Vector2u TextSize = textura->getSize();
	TextSize.x /= 8;
	TextSize.y /= 8;
	//std::cout << TextSize.x << "  " << TextSize.y << "\n";
	esfera.setTextureRect(sf::IntRect(TextSize.x * asteroide[0], TextSize.y * asteroide[1], TextSize.x, TextSize.y));
	//std::cout << TextSize.x * asteroide[0] << "  " << TextSize.y * asteroide[1] << "\n";
}


void Asteroides::move() {

	esfera.move(direcao);
	position += direcao;
}

void Asteroides::setAngleDirection(sf::Vector2f direction, float angle) {

	float radians = 180 / 3.14159268f * angle;
	sf::Vector2f direct = direcao;
	direcao.x = cos(radians) * direct.x - sin(radians) * direct.y;
	direcao.y = sin(radians) * direct.x + cos(radians) * direct.y;
}

void Asteroides::setPosition(sf::Vector2f position) {

	this->position = position;
	esfera.setPosition(this->position);
}

void Asteroides::draw(sf::RenderWindow& janela) {
	janela.draw(esfera);
}

Asteroides::~Asteroides()
{
}


#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#define VisionSize 800
#define GameLimit 1700
#define NaveLimit 1540


class Tiro {
public:
	sf::RectangleShape tiro;
	sf::Vector2f position;
	sf::Vector2f diretor;
	//const float velocity = 5.0f;
	Tiro();
	void initPoint(sf::Vector2f pistolCenter);
	void setDirection(sf::Vector2f& direcao);
	void move();
};

enum posicao {
	frente,
	tras,
	//direita,
	//esquerda
};

class Player
{
private:

	sf::RectangleShape nave;
	sf::RectangleShape pistol;
	sf::Vector2f NavePosition;
	sf::Vector2f NaveDirection;
	sf::Vector2f PistolPosition;
	sf::Vector2f PistolDirection;
	float angle;
	float velocidade;
	float aceleracao;


public:

	sf::Texture textura;
	std::vector<Tiro> tiros;

	Player(sf::Texture& Tex);
	void ShootDirection(sf::Vector2f mouse);
	void Shoot();
	sf::Vector2f getPistolPosition();
	sf::Vector2f getNavePosition();
	sf::Vector2f getCenter();
	void acelerar(posicao lado);
	void move();
	void rotate(float angle);
	void restart();
	void draw(sf::RenderWindow& janela);
};




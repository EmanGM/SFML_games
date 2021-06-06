#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <deque>
#include "Objetos.h"
#include "PowerUp.h"




class Racket;
class Ball;
class PowerUp;

class Nivel
{

private:
	Tijolo blocos[12][7];
	int totalBlocks;
	int control;
	Racket raquete;
	std::deque<Bola> bolas;
	float BallVelocity;
	sf::Texture BrickTexture;
	sf::Texture PowerUpsTexturas[4];
	sf::SoundBuffer buffer[3];
	sf::Sound som;
	sf::Sound perder;
	sf::Sound Rackt;
	sf::Time tempoRestart;
	sf::Clock relogio;
	std::deque<PowerUp> PowerUps;

public:
	//Nivel() {}
	Nivel(int arr[][7], float velocidade);
	void restart();
	int run();
	void setBlockColor(int posX, int posY, sf::Color& cor);
	void BolaColidirRaquete(Bola &bola);
	void BolaColidirTijolos(Bola &bola, int a, int b);
	void draw(sf::RenderWindow& janela);

	~Nivel();
};


#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Barra
{
public:
	sf::RectangleShape barra;
	sf::Vector2f size;
	float position;

	Barra();
	void setStartingPosition(float startPosition);
	void move(float offset);
	void draw(sf::RenderWindow& janela);
	~Barra();
};



class Player
{
public:
	Barra paddle;
	int score;
	sf::Font font;
	sf::Text pontos;
	sf::SoundBuffer buffer;
	sf::Sound som;
	sf::Time tempoRestart;
	sf::Clock relogio;
	Player(float Posição_inicial, float text_position, sf::SoundBuffer& som);
	void reset();
	float getTime();
	void makeSound();
	void draw(sf::RenderWindow& janela);
	~Player();

private:

};





